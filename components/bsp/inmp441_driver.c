#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2s_std.h"
#include "driver/gpio.h"
#include <string.h>
#include "inmp441_driver.h"

static const char *TAG = "INMP441_DRIVER";


// I2S引脚定义
#define I2S_BCLK GPIO_NUM_18  // 位时钟
#define I2S_LRC  GPIO_NUM_19  // 字选择(WS)
#define I2S_DIN  GPIO_NUM_21  // 数据输入
#define I2S_NUM  I2S_NUM_1    // 使用I2S_NUM_1，因为I2S_NUM_0已被MAX98357使用

static inmp441_dev_t *inmp441_dev = NULL;



esp_err_t inmp441_init(uint32_t sample_rate)
{
    esp_err_t ret = ESP_OK;

    inmp441_dev = calloc(1, sizeof(inmp441_dev_t));
    if (inmp441_dev == NULL)
    {
        return ESP_ERR_NO_MEM;
    }


    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM, I2S_ROLE_MASTER);
    ret = i2s_new_channel(&chan_cfg, &inmp441_dev->rx_handle, NULL);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to create I2S channel");
        return ret;
    }
    // I2S标准模式配置
    i2s_std_config_t std_cfg ={
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(sample_rate),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_MONO),//32位，单声道
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = I2S_BCLK, // 位时钟
            .ws = I2S_LRC, // 字选择,左右声道
            .dout = I2S_GPIO_UNUSED, // 数据输出 无
            .din = I2S_DIN, // 数据输入
            .invert_flags = {
                .mclk_inv = false, // 不反相
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };

    ret = i2s_channel_init_std_mode(inmp441_dev->rx_handle, &std_cfg);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize I2S channel");
        return ret;
    }

    ret = i2s_channel_enable(inmp441_dev->rx_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to enable I2S channel");
        return ret;
    }

    inmp441_dev->sample_rate = sample_rate;
    inmp441_dev->is_initialized = true;

    ESP_LOGI(TAG, "INMP441 initialized successfully");
    return ESP_OK;

}

esp_err_t inmp441_read_data(uint8_t *data, size_t size)
{
    if(!inmp441_dev || !inmp441_dev->is_initialized)
    {
        ESP_LOGE(TAG, "INMP441 is not initialized");
        return ESP_ERR_INVALID_STATE;  // 设备未初始化
    }

    esp_err_t ret = i2s_channel_read(inmp441_dev->rx_handle, data, size, NULL, portMAX_DELAY);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to read data from INMP441");
        return ret;
    }
    
    return ESP_OK;
}



esp_err_t inmp441_deinit(void)
{
    if (!inmp441_dev) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t ret = i2s_channel_disable(inmp441_dev->rx_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to disable I2S channel");
        return ret;
    }

    ret = i2s_del_channel(inmp441_dev->rx_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to delete I2S channel");
        return ret;
    }

    free(inmp441_dev);
    inmp441_dev = NULL;
    return ESP_OK;
}