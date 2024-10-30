#include <lvgl.h>
#include "esp_sntp.h"
#include "esp_netif_sntp.h"
#include <time.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"

static const char *TAG = "util";
#define SNTP_SERVER "ntp1.aliyun.com" // 阿里云NTP服务器

void remove_styles(lv_obj_t *parent, bool remove_border, bool remove_opa, bool remove_scrollbar, bool remove_shadow)
{
    if (parent == NULL)
        return;
    // 移除边框
    if (remove_border)
    {
        lv_obj_set_style_border_width(parent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    // 设置透明
    if (remove_opa)
    {
        lv_obj_set_style_bg_opa(parent, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    // 移除滚动条
    if (remove_scrollbar)
    {
        lv_obj_set_scrollbar_mode(parent, LV_SCROLLBAR_MODE_OFF);
    }

    // 移除阴影
    if (remove_shadow)
    {
        lv_obj_set_style_shadow_width(parent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}

// 列表返回菜单设置焦点
void set_focus(lv_obj_t **btns, int count, int last_index)
{
    if (last_index >= 0 && last_index < count)
    {
        if (btns[last_index] != NULL)
        { // 检查指针是否有效
            lv_group_focus_obj(btns[last_index]);
        }
        else
        {
            // printf("btns[%d] is NULL\n", last_index);
        }
    }
    else
    {
        lv_group_focus_obj(btns[0]); // 默认到第一个
    }
}

void initialize_sntp(void)
{
    ESP_LOGI(TAG, "初始化 SNTP");
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG(SNTP_SERVER);
    esp_netif_sntp_init(&config);

    // 等待获取时间
    time_t now = 0;
    struct tm timeinfo = {0};
    int retry = 0;
    const int retry_count = 15;

    while (timeinfo.tm_year < (2023 - 1900) && ++retry < retry_count)
    {
        ESP_LOGI(TAG, "等待系统时间同步... (%d/%d)", retry, retry_count);
        vTaskDelay(pdMS_TO_TICKS(1000));
        time(&now);
        localtime_r(&now, &timeinfo);
    }

    // 设置时区为中国时区
    setenv("TZ", "CST-8", 1);
    tzset();

    ESP_LOGI(TAG, "SNTP 初始化完成");
}

// 获取格式化的时间字符串
void get_time_string(char *buffer, size_t buffer_size)
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", &timeinfo);
}

struct tm get_timeinfo(void)
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    return timeinfo;
}
