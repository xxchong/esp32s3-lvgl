#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "lv_port.h"
#include "lvgl.h"
#include "lv_demos.h"
#include "st7789_driver.h"

void lv_demo(void)
{
    lv_obj_t *scr = lv_scr_act();
    lv_obj_t *btn = lv_btn_create(scr);
    lv_obj_center(btn);
    lv_obj_set_size(btn, 100, 50);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "Hello1");

    lv_obj_t *btn2 = lv_btn_create(scr);
    lv_obj_align_to(btn2, btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    label = lv_label_create(btn2);

    lv_group_t *group = lv_group_create();

    lv_indev_set_group(button_indev, group);
    lv_group_add_obj(group, btn);
    lv_group_add_obj(group, btn2);
}

// 主函数
void app_main(void)
{
    ESP_ERROR_CHECK(lv_port_init()); // 初始化LVGL
    // lv_demo_widgets();              //初始化控件demo程序
    // lv_demo_benchmark();
    lv_demo();
    st7789_lcd_backlight(true); // 打开背光huioyhuyh
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_task_handler(); // LVGL循环处理
    }
}
