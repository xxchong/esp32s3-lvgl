#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "driver/i2s_std.h"
#include "driver/gpio.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "max98357_driver.h"

static const char *TAG = "MAX98357_DRIVER";

// I2S配置
#define I2S_BCLK GPIO_NUM_4 // 位时钟
#define I2S_LRC GPIO_NUM_5  // 字选择
#define I2S_SDA GPIO_NUM_7 // 数据输出


 max98357_dev_t *max98357_dev = NULL;

esp_err_t max98357_init(uint32_t sample_rate)
{
    esp_err_t ret = ESP_OK;

    max98357_dev = calloc(1, sizeof(max98357_dev_t));
    if (max98357_dev == NULL)
    {
        return ESP_ERR_NO_MEM;
    }
    // I2S标准配置
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    ret = i2s_new_channel(&chan_cfg, &max98357_dev->tx_handle, NULL);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to create I2S channel");
        return ret;
    }

    // I2S标准模式配置
    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(sample_rate),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = I2S_BCLK,
            .ws = I2S_LRC,
            .dout = I2S_SDA,
            .din = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };

    ret = i2s_channel_init_std_mode(max98357_dev->tx_handle, &std_cfg);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to init I2S channel in STD mode");
        return ret;
    }

    ret = i2s_channel_enable(max98357_dev->tx_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to enable I2S channel");
        return ret;
    }

    max98357_dev->sample_rate = sample_rate;
    max98357_dev->is_initialized = true;

    ESP_LOGI(TAG, "MAX98357 initialized successfully");
    return ESP_OK;
}

esp_err_t max98357_write_data(uint8_t *data, size_t size)
{
    if (!max98357_dev || !max98357_dev->is_initialized)
    {
        return ESP_ERR_INVALID_STATE;
    }

    size_t bytes_written = 0;
    esp_err_t ret = i2s_channel_write(max98357_dev->tx_handle, data, size, &bytes_written, portMAX_DELAY);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to write data to I2S channel");
        return ret;
    }

    return ESP_OK;
}

esp_err_t max98357_deinit(void)
{
    if (!max98357_dev)
    {
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t ret = i2s_channel_disable(max98357_dev->tx_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to disable I2S channel");
        return ret;
    }

    ret = i2s_del_channel(max98357_dev->tx_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to delete I2S channel");
        return ret;
    }

    free(max98357_dev);
    max98357_dev = NULL;
    return ESP_OK;
}