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
lv_group_t *group;

TaskHandle_t lvgl_task_handle;

static const char *TAG = "app—main";
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
       // lv_demo_benchmark();

       //     lv_obj_t *disp = lv_obj_create(lv_scr_act());
       //        lv_obj_center(disp);
       //        lv_obj_set_size(disp, 240, 280);
       //        lv_obj_set_style_pad_all(disp, 0, 0);
       //        tetris_start_game(disp, group);
}
// 测试读取函数
void lv_fs_test(void)
{
       lv_fs_file_t f;
       lv_fs_res_t res;
       res = lv_fs_open(&f, "S:xxchong.txt", LV_FS_MODE_RD);
       if (res != LV_FS_RES_OK)
       {
              ESP_LOGE(TAG, "打开错误");
       }
       else
       {
              ESP_LOGI(TAG, "打开成功");
              uint32_t read_num;
              uint8_t buf[512];
              res = lv_fs_read(&f, buf, sizeof(buf), &read_num);
              ESP_LOGI(TAG, "读取内容:%s", buf);
              lv_fs_close(&f);
       }
}
// ... existing code ...

void time_update_callback(TimerHandle_t xTimer)
{
       char timestr[64];
       get_time_string(timestr, sizeof(timestr));
       ESP_LOGI(TAG, "当前时间: %s", timestr);
}

void lv_task(void *pvParameters)
{
       while (1)
       {
              lv_task_handler();
              vTaskDelay(pdMS_TO_TICKS(10));
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

       lv_demo();
       // 创建并启动定时器
       //     TimerHandle_t timer = xTimerCreate("time_update", pdMS_TO_TICKS(1000), pdTRUE, NULL, time_update_callback);
       //     if (timer != NULL) {
       //         if (xTimerStart(timer, 0) != pdPASS) {
       //             ESP_LOGE(TAG, "定时器启动失败");
       //         } else {
       //             ESP_LOGI(TAG, "定时器启动成功");
       //         }
       //     } else {
       //         ESP_LOGE(TAG, "定时器创建失败");
       //     }

       // 创建 LVGL 任务
       xTaskCreatePinnedToCore(
           lv_task,           // 任务函数
           "lv_task_handler", // 任务名称
           8192,              // 栈大小（字节）
           NULL,              // 参数
           1,                 // 优先级
           &lvgl_task_handle, // 任务句柄
           1                  // 在 Core 1 上运行
       );

       // 打印各种类型的剩余RAM
       // 打印各种类型的剩余RAM
       //     printf("剩余内存信息：\n");
       // printf("1. 可用内部RAM (DRAM): %u 字节 (%.2f KB)\n",
       //        heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT),
       //        heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT) / 1024.0);

       // printf("2. 最大连续内部RAM块: %u 字节 (%.2f KB)\n",
       //        heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT),
       //        heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT) / 1024.0);

       // printf("3. 总共空闲RAM (包括外部PSRAM): %" PRIu32 " 字节 (%.2f KB)\n",
       //        esp_get_free_heap_size(),

       //        esp_get_free_heap_size() / 1024.0);

       // printf("4. 最小剩余堆大小: %" PRIu32 " 字节 (%.2f KB)\n",
       //        esp_get_minimum_free_heap_size(),
       //        esp_get_minimum_free_heap_size() / 1024.0);

       // printf("5. PSRAM: %u 字节 空闲RAM (%.2f KB)\n",
       //        (unsigned int)heap_caps_get_total_size(MALLOC_CAP_SPIRAM),
       //        heap_caps_get_free_size(MALLOC_CAP_SPIRAM) / 1024.0);

       // sd_write_and_read_test();
}
