#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/portmacro.h"
// 系统头文件
#include <string.h>
#include <stdio.h>
// ESP32 相关头文件
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"

#include "wifi_scan_driver.h"


static QueueHandle_t wifi_scan_queue = NULL;   //保存扫描结果的队列
static EventGroupHandle_t wifi_scan_event_group = NULL; //扫描完成事件组

// 检查SSID是否只包含ASCII字符
static bool is_ascii_ssid(const char* ssid) {
    while (*ssid) {
        if (*ssid < 0 || *ssid > 127) {
            return false;
        }
        ssid++;
    }
    return true;
}

static void wifi_scan_task(void* pvParameters) {
    wifi_scan_config_t scan_config = {
        .ssid = NULL,
        .bssid = NULL,
        .channel = 0,
        .show_hidden = false
    };

    // 开始扫描
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));

    uint16_t ap_count = 0;
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

    if (ap_count > 0) {
        wifi_ap_record_t *ap_records = malloc(sizeof(wifi_ap_record_t) * ap_count);
        if (ap_records != NULL) {
            ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_count, ap_records));
            
            // 清空队列
            xQueueReset(wifi_scan_queue);
            
            // 发送扫描结果到队列
            int sent_count = 0;
            for (int i = 0; i < ap_count && sent_count < MAX_WIFI_SSID; i++) {
                // 只处理ASCII字符的SSID
                if (is_ascii_ssid((char *)ap_records[i].ssid)) {
                    wifi_scan_result_t result;
                    strncpy(result.ssid, (char *)ap_records[i].ssid, sizeof(result.ssid) - 1);
                    result.ssid[sizeof(result.ssid) - 1] = '\0';
                    result.rssi = ap_records[i].rssi;
                    
                    if (xQueueSend(wifi_scan_queue, &result, 0) == pdTRUE) {
                        sent_count++;
                    }
                }
            }
            free(ap_records);
        }
    }
    
    // 设置扫描完成标志
    xEventGroupSetBits(wifi_scan_event_group, SCAN_DONE_BIT);
    vTaskDelete(NULL);
}

// 启动单次WiFi扫描
void start_wifi_scan(void) {
    if (!wifi_scan_queue) {
        wifi_scan_queue = xQueueCreate(MAX_WIFI_SSID, sizeof(wifi_scan_result_t));
    }
    
    if (!wifi_scan_event_group) {
        wifi_scan_event_group = xEventGroupCreate();
    }
    
    // 清除之前的扫描完成标志
    xEventGroupClearBits(wifi_scan_event_group, SCAN_DONE_BIT);
    
    // 创建扫描任务
    xTaskCreatePinnedToCore(wifi_scan_task, "wifi_scan", 4096, NULL, 5, NULL, 0);
}

// 等待扫描完成
bool wait_wifi_scan_done(TickType_t wait_ticks) {
    if (!wifi_scan_event_group) return false;
    
    EventBits_t bits = xEventGroupWaitBits(
        wifi_scan_event_group,
        SCAN_DONE_BIT,
        pdTRUE,  // 清除标志位
        pdFALSE,
        wait_ticks
    );
    
    return (bits & SCAN_DONE_BIT) != 0;//扫描完成
}

// 获取扫描结果
bool get_wifi_scan_result(char *ssid, int8_t *rssi) {
    if (!wifi_scan_queue) return false;
    
    wifi_scan_result_t result;
    if (xQueueReceive(wifi_scan_queue, &result, 0) == pdTRUE) {
        strcpy(ssid, result.ssid);
        *rssi = result.rssi;
        return true;
    }
    return false;
}

// 清理资源
void cleanup_wifi_scan(void) {
    if (wifi_scan_queue) {
        vQueueDelete(wifi_scan_queue);
        wifi_scan_queue = NULL;
    }
    
    if (wifi_scan_event_group) {
        vEventGroupDelete(wifi_scan_event_group);
        wifi_scan_event_group = NULL;
    }
}
