#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "st7789_driver.h"
#include "sys.h"
#include "lv_demos.h" // 添加这个头文件

lv_group_t *group;

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
    lv_scr_load(root);
}

// 主函数
void app_main(void)
{
    ESP_ERROR_CHECK(lv_port_init()); // 初始化LVGL
    lv_demo();
    st7789_lcd_backlight(true); // 打开背光huioyhuyh
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_task_handler(); // LVGL循环处理
    }
}
