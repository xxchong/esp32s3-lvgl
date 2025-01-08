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
#include "aliot.h"
#include "system_monitor.h"
#include "boot.h"
#include "status_bar.h"
#include "root_page.h"
#include "Notification.h"
#include "max98357_driver.h"
#include <math.h>
#include "audio_player.h"
#include "file_iterator.h"
#include "wifi_scan_driver.h"

#include "Gui-Guider/generated/gui_guider.h"
#include "Gui-Guider/generated/events_init.h"
#include "ble_driver.h"
#include "AI/doubao.h"

lv_ui guider_ui;

lv_group_t *group;

TaskHandle_t lvgl_task_handle;
now_weather_info_t now_weather_info;
three_day_weather_info_t three_day_weather_info[3];

static const char *TAG = "app—main";

#define WIFI_SSID "Pixel"
#define WIFI_PASSWORD "12345678"

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
    if (lv_page == NULL)
    {
        lv_page = (page_t *)malloc(sizeof(page_t));
        memset(lv_page, 0, sizeof(page_t));
    }
    lv_page->boot_page = create_boot();
}

LV_FONT_DECLARE(flash_font_16_t);
static lv_obj_t *label;

static void lv_example_label_timer(lv_timer_t *timer)
{
    static int count = 0;
    count++;
    if(count > 2)
    {
        count = 0;
    }

    switch (count)
    {
    case 1:
        lv_label_set_text(label, "我和她从幼儿园就在一起玩，虽然我们之间经常发生矛盾，但是很快我们之间的矛盾一两天便迎刃而解。她小时侯长得很黑，我背地里经常叫她“非洲黑妹”。有时候，我开玩笑问她是不是非洲人，她则说，我白得像鬼，这句话使我哭笑不得。她的脸上被划过一道浅浅的疤，我问她是怎么回事，她说是她哥哥玩玩具剑不小心划到的。");
        break;
    case 2:
        lv_label_set_text(label, "我很少来我家玩，一次终于肯来我家了，我突发奇想，想和她合作做一个“满族头冠”，材料我家应有尽有。我拿出了两张大硬纸板，和大透明胶、剪刀、皱纸选自:作文大全 www.zuowenv.com。她做好了皱纸折成了纸");
        break;
 
    }


}
void lv_example_label(void)
{
    label = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label, 240);
    lv_obj_set_style_text_font(label, &flash_font_16_t, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_timer_create(lv_example_label_timer, 200, NULL);
}


void lv_task(void *pvParameters)
{
    //  init_page();
    // lv_scr_load(lv_page->boot_page);
    lv_example_label();
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
        // 内部内存 (DRAM)
        uint32_t internal_free = heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
        
        // 外部内存 (PSRAM)
        uint32_t psram_free = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
        
        // 总可用内存
        uint32_t total_free = esp_get_free_heap_size();

        ESP_LOGI(TAG, "内存状态:");
        ESP_LOGI(TAG, "- 内部可用: %" PRIu32 " bytes (%.2f KB)", internal_free, internal_free / 1024.0f);
        ESP_LOGI(TAG, "- 外部可用: %" PRIu32 " bytes (%.2f KB)", psram_free, psram_free / 1024.0f);
        ESP_LOGI(TAG, "- 总可用: %" PRIu32 " bytes (%.2f KB)", total_free, total_free / 1024.0f);
        
        // 每5秒更新一次
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
#define SAMPLE_RATE 44100



void max98357_set_volume(float volume)
{
    if (!max98357_dev)
        return;
    // 限制音量范围在 0.0 ~ 1.0
    max98357_dev->volume = (volume < 0.0f) ? 0.0f : ((volume > 1.0f) ? 1.0f : volume);
}
// 生成正弦波进行测试
// 修改生成波形的函数，加入音量控制
void generate_sine_wave(uint8_t *buffer, size_t length, float frequency)
{
    static float phase = 0.0f;
    int16_t *samples = (int16_t *)buffer;
    size_t samples_count = length / 2; // 16位采样

    for (size_t i = 0; i < samples_count; i++)
    {
        float angle = phase + (2.0f * M_PI * frequency * i) / SAMPLE_RATE;
        // 应用音量控制
        samples[i] = (int16_t)(sinf(angle) * 32767.0f * max98357_dev->volume);
    }

    phase = fmodf(phase + (2.0f * M_PI * frequency * samples_count) / SAMPLE_RATE, 2.0f * M_PI);
}
static TimerHandle_t weather_update_timer = NULL;
static void weather_update_timer_cb(TimerHandle_t xTimer)
{
    start_weather_update();
}

// AI响应回调函数
void ai_response_handler(const char* response)
{
    ESP_LOGI(TAG, "收到AI回复: %s", response);
    // 在这里处理AI的回复
    // 比如显示到屏幕上或者进行其他操作
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

     // 添加一些延时
    vTaskDelay(pdMS_TO_TICKS(100));


    // wifi STA工作模式初始化
    wifi_sta_init((const char *)WIFI_SSID, (const char *)WIFI_PASSWORD);
    // 等待WiFi连接
    ESP_LOGI(TAG, "等待 WiFi 连接...");
    while (!is_wifi_connected())
    {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    ESP_LOGI(TAG, "WiFi 已连接");

  
    uart_doubao_init(115200);
    create_uart_doubao_task();





 
    
    // 清理资源
    // ai_chat_cleanup();



    // vTaskDelay(pdMS_TO_TICKS(1000));
    // ESP_LOGI(TAG, "扫描WiFi");

    // wifi_scan();
    // initialize_sntp(); // 获取时间
    // 测试打印当前时间
    // char timestr[64];
    // get_time_string(timestr, sizeof(timestr));
    // ESP_LOGI(TAG, "当前时间: %s", timestr);
    // ESP_ERROR_CHECK(lv_port_init()); // 初始化LVGL
    // st7789_lcd_backlight(true);      // 打开背光huioyhuyh
    // ledc_init();                     // 初始化背光的pwm控制
    // set_backlight(20);

    // ble_driver_init();
    // setup_ui(&guider_ui);
    // events_init(&guider_ui);



    // weather_update_timer = xTimerCreate("weather_update", pdMS_TO_TICKS( 1000 * 12 ), pdTRUE, NULL, weather_update_timer_cb);

    // xTimerStart(weather_update_timer, 0);

    // start_weather_update();  // 立即触发一次更新

    // mqtt_init();

    // system_monitor_init();
    // 初始化系统监控，使用端口3333

    // 在需要时获取系统信息
    // system_info_t *info = get_latest_system_info();
    // printf("CPU: %.1f%%\n", info->cpu.usage);
    // 创建 LVGL 任务
    // xTaskCreatePinnedToCore(
    //     lv_task,                  // 任务函数
    //     "lv_task_handler",        // 任务名称
    //     8192,                     // 栈大小（字节）
    //     NULL,                     // 参数
    //     configMAX_PRIORITIES - 2, // 优先级
    //     &lvgl_task_handle,        // 任务句柄
    //     1                         // 在 Core 1 上运行
    // );

    // 创建内存监控任务
    xTaskCreatePinnedToCore(
        memory_monitor_task, // 任务函数
        "memory_monitor",    // 任务名称
        4096,                // 栈大小
        NULL,                // 参数
        5,                   // 优先级
        NULL,                 // 任务句柄
        1                    // 在 Core 1 上运行
    );
}
