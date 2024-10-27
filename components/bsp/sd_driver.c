#include "sd_driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "esp_system.h"
#include "driver/sdspi_host.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "sdmmc_cmd.h" // 添加这个头文件

static const char *TAG = "SD_DRIVER";

#define pin_CS 5
#define pin_MOSI 13
#define pin_MISO 12
#define pin_CLK 14
#define MOUNT_POINT "/sdcard" // 定义挂载点

void sdcard_init(void)
{
    esp_err_t ret;
    // 配置SPI总线
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = pin_MOSI,
        .miso_io_num = pin_MISO,
        .sclk_io_num = pin_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    ret = spi_bus_initialize(SPI3_HOST, &bus_cfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize SPI bus: %s", esp_err_to_name(ret));
        return;
    }
    // SD卡配置
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = SPI3_HOST;
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = pin_CS;
    slot_config.host_id = SPI3_HOST;
    // 挂载文件系统
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024};

    sdmmc_card_t *card;
    // 初始化SD卡 挂载fat文件系统 文件系统注册到ESP-IDF的虚拟文件系统（VFS）中
    ret = esp_vfs_fat_sdspi_mount(MOUNT_POINT, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(TAG, "文件系统挂载失败。"
                          "如果希望格式化SD卡，将 format_if_mount_failed 设置为 true。");
        }
        else
        {
            ESP_LOGE(TAG, "SD卡初始化失败 (%s)。"
                          "请确保SD卡线路上有上拉电阻。",
                     esp_err_to_name(ret));
        }
        return;
    }

    ESP_LOGI(TAG, "SD卡挂载成功");
    ESP_LOGI(TAG, "SD卡容量: %lluMB", ((uint64_t)card->csd.capacity) * card->csd.sector_size / (1024 * 1024));
    // 打印卡片信息
    sdmmc_card_print_info(stdout, card);
}

esp_err_t write_file_to_sd(const char *filename, const char *data)
{
    ESP_LOGI(TAG, "正在写入文件: %s", filename);

    char filepath[64];
    snprintf(filepath, sizeof(filepath), "%s/%s", MOUNT_POINT, filename);

    FILE *f = fopen(filepath, "w");
    if (f == NULL)
    {
        ESP_LOGE(TAG, "无法打开文件进行写入");
        return ESP_FAIL;
    }

    fprintf(f, "%s", data);
    fclose(f);

    ESP_LOGI(TAG, "文件写入成功");
    return ESP_OK;
}
esp_err_t read_file_from_sd(const char *filename, char *buffer, size_t buffer_size)
{
    ESP_LOGI(TAG, "正在读取文件: %s", filename);

    char filepath[64];
    snprintf(filepath, sizeof(filepath), "%s/%s", MOUNT_POINT, filename);

    FILE *f = fopen(filepath, "r");
    if (f == NULL)
    {
        ESP_LOGE(TAG, "无法打开文件进行读取");
        return ESP_FAIL;
    }

    size_t bytes_read = fread(buffer, 1, buffer_size - 1, f);
    fclose(f);

    if (bytes_read == 0)
    {
        ESP_LOGE(TAG, "读取文件失败");
        return ESP_FAIL;
    }

    buffer[bytes_read] = '\0'; // 确保字符串以null结尾
    ESP_LOGI(TAG, "文件读取成功");
    return ESP_OK;
}

void sd_write_and_read_test(void)
{
    char *data = "你好,这是张志鹏的第一个SD卡程序的测试功能";
    write_file_to_sd("xxchong.txt", data);
    char buffer[512];
    read_file_from_sd("xxchong.txt", buffer, sizeof(buffer));
    ESP_LOGI(TAG, "读取到的数据: %s", buffer);
}
