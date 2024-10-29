#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "st7789_driver.h"
#include "sys.h"
#include "lv_demos.h"
#include "inc/apps/Game/Tetris.h"
#include "wifi_sta.h"
#include "nvs_flash.h"
#include "nvs.h"
#include <inttypes.h>
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "sd_driver.h"
#include "lv_conf.h"
#include "util.h"
#include "pwm_ledc.h"
#include "weather_http.h"
#include "esp_heap_caps.h"
#include "esp_system.h"
lv_group_t *group;

TaskHandle_t lvgl_task_handle;
now_weather_info_t now_weather_info;
three_day_weather_info_t three_day_weather_info[3];

static const char *TAG = "app—main";

// 添加内存监控函数
void print_memory_info(const char *message) {
    ESP_LOGI(TAG, "Memory Info - %s:", message);
    
    // 1. DRAM (内部RAM)
    ESP_LOGI(TAG, "Free Internal RAM (DRAM): %u bytes (%.2f KB)",
        heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT),
        heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT) / 1024.0);

    // 2. 最大连续内部RAM块
    ESP_LOGI(TAG, "Largest Free Internal Block: %u bytes (%.2f KB)",
        heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT),
        heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT) / 1024.0);

    // 3. 总空闲堆内存
    ESP_LOGI(TAG, "Total Free Heap: %" PRIu32 " bytes (%.2f KB)",
        esp_get_free_heap_size(),
        esp_get_free_heap_size() / 1024.0);

    // 4. 最小空闲堆大小
    ESP_LOGI(TAG, "Minimum Free Heap Ever: %" PRIu32 " bytes (%.2f KB)",
        esp_get_minimum_free_heap_size(),
        esp_get_minimum_free_heap_size() / 1024.0);

    // 5. PSRAM (如果有)
    #ifdef CONFIG_ESP32_SPIRAM_SUPPORT
    ESP_LOGI(TAG, "Free PSRAM: %u bytes (%.2f KB)",
        heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
        heap_caps_get_free_size(MALLOC_CAP_SPIRAM) / 1024.0);
    #endif
}

void lv_demo(void)
{
       lv_obj_t *scr = lv_scr_act();
       lv_obj_set_size(scr, 240, 280);
       group = lv_group_create();
       lv_group_remove_all_objs(group);
       lv_group_set_default(group);
       lv_indev_set_group(indev, group);
       lv_obj_t *root = create_root(scr);
       create_Notification();
       create_second_page();
       lv_scr_load(root);
}

void lv_task(void *pvParameters)
{
    
    lv_demo();
    while (1)
    {
        lv_task_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void memory_monitor_task(void *pvParameters) {
    while (1) {
        print_memory_info("Periodic Check");
        vTaskDelay(pdMS_TO_TICKS(10000));  // 每10秒检查一次
    }
}

// 主函数
void app_main(void)
{
    // NVS初始化（WIFI底层驱动有用到NVS，所以这里要初始化）
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    // wifi STA工作模式初始化
    wifi_sta_init();
    // 等待WiFi连接
    ESP_LOGI(TAG, "等待 WiFi 连接...");
    while (!is_wifi_connected())
    {
            vTaskDelay(pdMS_TO_TICKS(100));
    }
    ESP_LOGI(TAG, "WiFi 已连接");
    initialize_sntp(); // 获取时间
    // 测试打印当前时间
    char timestr[64];
    get_time_string(timestr, sizeof(timestr));
    ESP_LOGI(TAG, "当前时间: %s", timestr);
    ESP_ERROR_CHECK(lv_port_init()); // 初始化LVGL
    st7789_lcd_backlight(true);      // 打开背光huioyhuyh
    ledc_init();                     // 初始化背光的pwm控制
    get_now_weather_data(&now_weather_info);
    get_3D_weather_data(three_day_weather_info);
      

     
    //创建 LVGL 任务
    xTaskCreatePinnedToCore(
        lv_task,           // 任务函数
        "lv_task_handler", // 任务名称
        4096,              // 栈大小（字节）
        NULL,              // 参数
        1,                 // 优先级
        &lvgl_task_handle, // 任务句柄
        1                  // 在 Core 1 上运行
    );

    //创建内存监控任务
    xTaskCreate(
        memory_monitor_task,    // 任务函数
        "memory_monitor",       // 任务名称
        4096,                   // 栈大小
        NULL,                   // 参数
        1,                      // 优先级
        NULL                    // 任务句柄
    );

}
