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
#include "max98357_driver.h"
#include <math.h>
#include "audio_player.h"
#include "file_iterator.h"
#include "wifi_scan_driver.h"

#include "Gui-Guider/generated/gui_guider.h"
#include "Gui-Guider/generated/events_init.h"
#include "ble_driver.h"
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
    if(count > 5)
    {
        count = 0;
    }

    switch (count)
    {
    case 1:
        lv_label_set_text(label, "到货时间好好干活u跟护士改革独爱高度谷歌和雕塑姑姑汉字，又称中文、中国字，别称方块字，是汉语的记录符号，属于表意文字的词素音节文字。世界上最古老的文字之一，已有6000年左右的历史 [25]。在形体上逐渐由图形变为笔画,象形变为象征，复杂变为简单；在造字原则上从表形、表意到形声。除极个别汉字外（如瓩、兛、兣、呎、嗧等），都是一个汉字一个音节 [1]。汉字是中华优秀传统文化的重要载体。 [26]现");
        break;
    case 2:
        lv_label_set_text(label, "欸哦我hi哦个i归通过撒花态度法国沙嗲回复规范国有八卦说：关于八卦的起源说法并不统一，有摹象说、星象说、数说和杨雄的“亥”为物之源说等等。《周易·系辞》云：“古者庖牺氏之王天下也，仰则观象于天，俯则观法于地，观鸟兽之文与地之宜，近取诸身，远取诸物，于是始作八卦，以通神明之德，以类万物之情。”这段话提到八卦源自庖牺氏对自然客观世界的摹象，这与“依类象形”而作的汉字的起源是相似的。孔安国《尚书》序（属伪作，但年代甚古）里说：“古者庖牺氏之王天下也，始画八卦，造书契，以代结绳之政，由是文籍生焉。”把八卦和书契（文字");
        break;
    case 3:
        lv_label_set_text(label, "啊速度去我国度全方位与对方球员打听打听刻契说：刻契是古人在结绳记事后又一种帮助记忆的实物记事法，多作契约用，比结绳记事进步多了。所谓“刻契”就是在木条上或竹条上刻上刻痕。《释名·释书契》：“契，刻也，刻识其数也。”《周易·系辞》郑玄注：“书之于木，刻其侧为契，各持其一，后以相符合。”郑玄又在《周礼·质人》注里说：“书契，取予市物之券也。其券之象书两札，刻其侧。”《列子·说符篇》：“宋人有游于道，得人遗契者，归而藏之，密数其齿。”所说的“齿”即是质契上所刻的齿痕。这种刻契具有记事记数的作用，可以作为契约的凭证，也");
        break;
    case 4:
        lv_label_set_text(label, "图画说：关于汉字的起源，历史上曾盛行“河图洛书说”。《周易·系辞上》：“河出图，洛出书，圣人则之。”《竹书纪年》指出：“黄帝轩辕五十年秋七月庚申，凤鸟至，帝祭于洛水”沈约注：“龙图出河，龟书出洛，赤文篆字，以授轩辕。” [5]《河图·玉版》：“仓颉为帝，");
        break;
    case 5:
        lv_label_set_text(label, "金文是指铸刻青铜器上的文字，也叫钟鼎文，始于殷商时期。商周是青铜器的时代，青铜器的礼器以鼎为代表，乐器以钟为代表，“钟鼎”是青铜器的代名词。所以，钟鼎文或金文就是指铸在或刻在青铜器上的铭文。");
        break;
    }


}
void lv_example_label(void)
{
    label = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label, 240);
    lv_obj_set_style_text_font(label, &flash_font_16_t, 0);
    lv_label_set_text(label, "到货时间好好干活u跟护士改革独爱高度谷歌和雕塑姑姑");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_timer_create(lv_example_label_timer, 1000, NULL);
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
        print_memory_info("Periodic Check");
        vTaskDelay(pdMS_TO_TICKS(10000)); // 每10秒检查一次
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
    // wifi_sta_init((const char *)WIFI_SSID, (const char *)WIFI_PASSWORD);
    // 等待WiFi连接
    // ESP_LOGI(TAG, "等待 WiFi 连接...");
    // while (!is_wifi_connected())
    // {
    //     vTaskDelay(pdMS_TO_TICKS(100));
    // }
    // ESP_LOGI(TAG, "WiFi 已连接");

    // vTaskDelay(pdMS_TO_TICKS(1000));
    // ESP_LOGI(TAG, "扫描WiFi");

    // wifi_scan();
    // initialize_sntp(); // 获取时间
    // 测试打印当前时间
    char timestr[64];
    get_time_string(timestr, sizeof(timestr));
    ESP_LOGI(TAG, "当前时间: %s", timestr);
    ESP_ERROR_CHECK(lv_port_init()); // 初始化LVGL
    st7789_lcd_backlight(true);      // 打开背光huioyhuyh
    ledc_init();                     // 初始化背光的pwm控制
    set_backlight(20);

    // ble_driver_init();
    // setup_ui(&guider_ui);
    // events_init(&guider_ui);

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
        8192,                     // 栈大小（字节）
        NULL,                     // 参数
        configMAX_PRIORITIES - 2, // 优先级
        &lvgl_task_handle,        // 任务句柄
        1                         // 在 Core 1 上运行
    );

    // 创建内存监控任务
    // xTaskCreate(
    //     memory_monitor_task, // 任务函数
    //     "memory_monitor",    // 任务名称
    //     4096,                // 栈大小
    //     NULL,                // 参数
    //     1,                   // 优先级
    //     NULL                 // 任务句柄
    // );
}
