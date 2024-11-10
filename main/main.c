#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "st7789_driver.h"
#include "sys.h"
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
#include "aliot.h"
#include "system_monitor.h"
#include "boot.h"
#include "status_bar.h"
#include "root_page.h"
#include "Notification.h"
lv_group_t *group;

TaskHandle_t lvgl_task_handle;
now_weather_info_t now_weather_info;
three_day_weather_info_t three_day_weather_info[3];

static const char *TAG = "app—main";

#define WIFI_SSID "Mi 10S"
#define WIFI_PASSWORD "87654321"

// 添加内存监控函数
void print_memory_info(const char *message)
{
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
    ESP_LOGI(TAG, "Free PSRAM: %u bytes (%.2f KB)",
             heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
             heap_caps_get_free_size(MALLOC_CAP_SPIRAM) / 1024.0);
}

void Tetris_Game()
{
    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_size(scr, 240, 280);
    tetris_start_game(scr, NULL);
}
gesture_t *lv_gesture = NULL;
page_t *lv_page = NULL;

void init_page(void)
{
    if (lv_gesture == NULL)
    {
        lv_gesture = (gesture_t *)malloc(sizeof(gesture_t));
    }
    if (lv_page == NULL)
    {
        lv_page = (page_t *)malloc(sizeof(page_t));
    }

    lv_page->boot_page = create_boot();
    lv_page->root_page = create_root();
}
static void scroll_event_cb(lv_event_t *e)
{
    lv_obj_t *cont = lv_event_get_target(e);
    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    int32_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;

    int32_t r = lv_obj_get_height(cont) * 7 / 10;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);

    for (uint32_t i = 0; i < child_cnt; i++)
    {
        lv_obj_t *child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        int32_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;
        int32_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        int32_t x;
        if (diff_y >= r)
        {
            x = r;
        }
        else
        {
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);
            x = r - res.i;
        }

        lv_obj_set_style_translate_x(child, x, 0);

        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);

        // 添加高度缩放效果
        float scale = 1.0f - (float)x / (float)r * 0.3f;
        int32_t height = 50 * scale;
        lv_obj_set_height(child, height);
    }
}

/**
 * Translate the object as they scroll
 */
void example_scroll(void)
{
    lv_obj_t *cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(cont, 240, 280);
    lv_obj_center(cont);

    // 设置容器样式
    lv_obj_set_style_bg_color(cont, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_pad_all(cont, 0, 0);
    lv_obj_set_style_radius(cont, 20, 0);
    lv_obj_set_style_clip_corner(cont, true, 0);

    // 设置滚动属性
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    // 创建按钮
    for (uint32_t i = 0; i < 20; i++)
    {
        lv_obj_t *btn = lv_btn_create(cont);
        lv_obj_set_width(btn, lv_pct(90));
        lv_obj_set_height(btn, 50);

        // 设置按钮样式
        lv_obj_set_style_radius(btn, 10, 0);
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x2196f3), 0);
        lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);

        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "Button %" LV_PRIu32, i);
        lv_obj_center(label);
    }
    lv_event_send(cont, LV_EVENT_SCROLL, NULL);

    lv_obj_scroll_to_view(lv_obj_get_child(cont, 0), LV_ANIM_OFF);
}

void lv_demo(void)
{

    // lv_obj_t *scr = lv_scr_act();
    // lv_obj_set_size(scr, 240, 280);
    // // group = lv_group_create();
    // // lv_group_remove_all_objs(group);
    // // lv_group_set_default(group);
    // // lv_indev_set_group(indev, group);

    // // lv_obj_t *root = create_root(scr);
    // lv_obj_t *Notification = create_Notification(group);
    // // // lv_group_add_obj(group, Notification);
    // // // lv_group_focus_obj(Notification);
    // // // create_second_page();
    // lv_scr_load(Notification);
}

void lv_task(void *pvParameters)
{

    init_page();
    lv_scr_load(lv_page->boot_page);
    // example_scroll();
    while (1)
    {
        lv_task_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void memory_monitor_task(void *pvParameters)
{
    while (1)
    {
        print_memory_info("Periodic Check");
        vTaskDelay(pdMS_TO_TICKS(10000)); // 每10秒检查一次
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
    wifi_sta_init((const char *)WIFI_SSID, (const char *)WIFI_PASSWORD);
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
    set_backlight(20);
    get_now_weather_data(&now_weather_info);
    get_3D_weather_data(three_day_weather_info);

    // mqtt_init();

    // system_monitor_init();
    // 初始化系统监控，使用端口3333

    // 在需要时获取系统信息
    // system_info_t *info = get_latest_system_info();
    // printf("CPU: %.1f%%\n", info->cpu.usage);

    // 创建 LVGL 任务
    xTaskCreatePinnedToCore(
        lv_task,                  // 任务函数
        "lv_task_handler",        // 任务名称
        4096,                     // 栈大小（字节）
        NULL,                     // 参数
        configMAX_PRIORITIES - 2, // 优先级
        &lvgl_task_handle,        // 任务句柄
        1                         // 在 Core 1 上运行
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
