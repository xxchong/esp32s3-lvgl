#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "st7789_driver.h"
#include "sys.h"
#include "lv_demos.h"
#include "inc/apps/Game/Tetris.h"

lv_group_t *group;

void lv_demo(void)
{
    // lv_obj_t *scr = lv_scr_act();
    // lv_obj_set_size(scr, 240, 280);
    group = lv_group_create();
    lv_group_remove_all_objs(group);
    lv_group_set_default(group);
    lv_indev_set_group(indev, group);
    // lv_obj_t *root = create_root(scr);
    // create_Notification();
    // create_second_page();
    // create_root(NULL);
    // lv_scr_load(root);

    lv_obj_t *disp = lv_obj_create(lv_scr_act());
    lv_obj_center(disp);
    lv_obj_set_size(disp, 240, 280);
    lv_obj_set_style_pad_all(disp, 0, 0);
    tetris_start_game(disp, group);
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
