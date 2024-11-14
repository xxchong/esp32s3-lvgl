#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "regex.h"

static const char *TAG = "wifi_scan";

void wifi_scan(void)
{
    // 配置扫描参数
    wifi_scan_config_t scan_config = {
        .ssid = NULL,
        .bssid = NULL,
        .channel = 0,
        .show_hidden = true};

    // 开始扫描
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));

    // 获取扫描结果
    uint16_t ap_count = 0;
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

    if (ap_count == 0)
    {
        ESP_LOGI(TAG, "No AP found");
        return;
    }

    wifi_ap_record_t *ap_records = malloc(sizeof(wifi_ap_record_t) * ap_count);
    if (ap_records == NULL)
    {
        ESP_LOGE(TAG, "Failed to malloc");
        return;
    }

    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_count, ap_records));

    // 打印扫描结果
    ESP_LOGI(TAG, "Found %d access points:", ap_count);
    ESP_LOGI(TAG, "               SSID              | Channel | RSSI |    MAC Address    | Auth Mode");
    ESP_LOGI(TAG, "----------------------------------------------------------------");

    for (int i = 0; i < ap_count; i++)
    {
        ESP_LOGI(TAG, "%-32s | %7d | %4d | %02x:%02x:%02x:%02x:%02x:%02x | %d",
                 (char *)ap_records[i].ssid,
                 ap_records[i].primary,
                 ap_records[i].rssi,
                 ap_records[i].bssid[0], ap_records[i].bssid[1], ap_records[i].bssid[2],
                 ap_records[i].bssid[3], ap_records[i].bssid[4], ap_records[i].bssid[5],
                 ap_records[i].authmode);
    }

    free(ap_records);
}