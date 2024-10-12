#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "lv_port.h"
#include "lvgl.h"
#include "lv_demos.h"
#include "st7789_driver.h"

// 主函数
void app_main(void)
{
    ESP_ERROR_CHECK(lv_port_init());    //初始化LVGL
    // lv_demo_widgets();              //初始化控件demo程序
    // lv_demo_stress();
    st7789_lcd_backlight(true);         //打开背光
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_task_handler();          //LVGL循环处理
    }
}
