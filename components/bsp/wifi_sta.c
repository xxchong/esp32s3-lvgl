#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "wifi_sta.h"

#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

// 需要把这两个修改成你家WIFI，测试是否连接成功
// #define DEFAULT_WIFI_SSID "Pixel"
// #define DEFAULT_WIFI_PASSWORD "12345678"

static bool wifi_connected = false;

static const char *TAG = "wifi";

/** 事件回调函数
 * @param arg   用户传递的参数
 * @param event_base    事件类别
 * @param event_id      事件ID
 * @param event_data    事件携带的数据
 * @return 无
 */
static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        wifi_connected = false;
        esp_wifi_connect();
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        wifi_connected = true;
    }

    if (event_base == IP_EVENT) // IP相关事件
    {
        switch (event_id)
        {
        case IP_EVENT_STA_GOT_IP: // 只有获取到路由器分配的IP，才认为是连上了路由器
            ESP_LOGI(TAG, "get ip address");
            break;
        }
    }
}

// WIFI STA初始化
esp_err_t wifi_sta_init(const char *wifi_ssid,const char *pwd)
{
    ESP_ERROR_CHECK(esp_netif_init());                // 用于初始化tcpip协议栈
    ESP_ERROR_CHECK(esp_event_loop_create_default()); // 创建一个默认系统事件调度循环，之后可以注册回调函数来处理系统的一些事件
    esp_netif_create_default_wifi_sta();              // 使用默认配置创建STA对象

    // 初始化WIFI
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // 注册事件
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL));

    // WIFI配置
      // WIFI配置
    wifi_config_t wifi_config = {
        .sta = {  // 使用大括号初始化嵌套结构体
            .ssid = "",  // 确保字符串被正确初始化
            .password = "",  // 确保字符串被正确初始化
            .threshold.authmode = WIFI_AUTH_WPA2_PSK, // 加密方式
            .pmf_cfg = {
                .capable = true,
                .required = false
            }
        }
    };

    // 使用 strncpy 确保字符串安全复制
    strncpy((char *)wifi_config.sta.ssid, wifi_ssid, sizeof(wifi_config.sta.ssid) - 1);
    strncpy((char *)wifi_config.sta.password, pwd, sizeof(wifi_config.sta.password) - 1);

    // 启动WIFI
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));               // 设置工作模式为STA
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config)); // 设置wifi配置
    ESP_ERROR_CHECK(esp_wifi_start());                               // 启动WIFI

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    return ESP_OK;
}

bool is_wifi_connected(void)
{
    return wifi_connected;
}