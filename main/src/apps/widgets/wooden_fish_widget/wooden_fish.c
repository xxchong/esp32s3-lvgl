// #include <Arduino.h>
// #include <lvgl.h>
// #include <icon.h>
// #include "util.h"
// #include "apps/Weather/lv_weather.h"
// #include "weather.h"
// #include <unordered_map>
// #include "apps/widgets/wooden_fish_widget/wooden_fish.h"

// extern lv_indev_t *indev;
// extern lv_obj_t *user_area;

// LV_IMG_DECLARE(fish);
// LV_FONT_DECLARE(wooden_fish_font_cn_8_t);

// typedef struct
// {
//     lv_obj_t *cont;
//     lv_obj_t *btn;
//     lv_obj_t *imgbtn_fish;
//     lv_obj_t *label_today;
//     lv_obj_t *label_num;
//     lv_obj_t *add_1;
// } lv_wooden_fish_widget_t;

// static lv_wooden_fish_widget_t *wooden_fish_widget_app;

// static int32_t num = 0;
// static void btn_event_cb(lv_event_t *e)
// {
//     char num_str[10];
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t *btn = lv_event_get_target(e);

//     if (code == LV_EVENT_PRESSED)
//     {
//         lv_img_set_zoom(wooden_fish_widget_app->imgbtn_fish, 128);
//         lv_obj_clear_flag(wooden_fish_widget_app->add_1, LV_OBJ_FLAG_HIDDEN); // 显示 "功德+1" 标签
//     }
//     else if (code == LV_EVENT_RELEASED)
//     {
//         lv_img_set_zoom(wooden_fish_widget_app->imgbtn_fish, 178);
//         num++;
//         sprintf(num_str, "%d", num);
//         lv_label_set_text(wooden_fish_widget_app->label_num, num_str);
//         lv_obj_add_flag(wooden_fish_widget_app->add_1, LV_OBJ_FLAG_HIDDEN); // 隐藏 "功德+1" 标签
//     }
// }

// lv_obj_t *create_wooden_fish_widget(lv_obj_t *parent, lv_group_t *group)
// {
//     if (wooden_fish_widget_app == NULL)
//     {
//         wooden_fish_widget_app = (lv_wooden_fish_widget_t *)malloc(sizeof(lv_wooden_fish_widget_t));
//         if (wooden_fish_widget_app == NULL)
//         {
//             // 处理内存分配失败的情况
//             printf("Failed to allocate memory for weather_app\n");
//             return NULL;
//         }
//         // 初始化成员变量
//         wooden_fish_widget_app->add_1 = NULL;
//         wooden_fish_widget_app->cont = NULL;
//         wooden_fish_widget_app->imgbtn_fish = NULL;
//         wooden_fish_widget_app->label_num = NULL;
//         wooden_fish_widget_app->label_today = NULL;
//         wooden_fish_widget_app->btn = NULL;
//     }

//     wooden_fish_widget_app->cont = lv_obj_create(parent);
//     lv_obj_set_size(wooden_fish_widget_app->cont, 120, 55);
//     lv_obj_set_style_bg_color(wooden_fish_widget_app->cont, lv_color_black(), LV_PART_MAIN);
//     lv_obj_set_style_border_width(wooden_fish_widget_app->cont, 0, LV_PART_MAIN);
//     lv_obj_set_style_border_color(wooden_fish_widget_app->cont, lv_color_black(), LV_PART_MAIN);
//     lv_obj_set_style_radius(wooden_fish_widget_app->cont, 8, LV_PART_MAIN);
//     lv_obj_set_style_pad_all(wooden_fish_widget_app->cont, 0, LV_PART_MAIN);

//     wooden_fish_widget_app->label_today = lv_label_create(wooden_fish_widget_app->cont);
//     lv_obj_set_style_text_font(wooden_fish_widget_app->label_today, &wooden_fish_font_cn_8_t, LV_PART_MAIN);
//     lv_obj_set_style_text_color(wooden_fish_widget_app->label_today, lv_color_white(), LV_PART_MAIN);
//     lv_label_set_text(wooden_fish_widget_app->label_today, "今日次数");
//     lv_obj_align(wooden_fish_widget_app->label_today, LV_ALIGN_LEFT_MID, 12, -12);

//     wooden_fish_widget_app->label_num = lv_label_create(wooden_fish_widget_app->cont);
//     lv_obj_set_style_text_font(wooden_fish_widget_app->label_num, &lv_font_montserrat_20, LV_PART_MAIN);
//     lv_obj_set_style_text_color(wooden_fish_widget_app->label_num, lv_color_white(), LV_PART_MAIN);
//     lv_label_set_text(wooden_fish_widget_app->label_num, "0");
//     lv_obj_align_to(wooden_fish_widget_app->label_num, wooden_fish_widget_app->label_today, LV_ALIGN_OUT_BOTTOM_MID, -2, 0);

//     wooden_fish_widget_app->btn = lv_btn_create(wooden_fish_widget_app->cont);
//     lv_obj_set_size(wooden_fish_widget_app->btn, 26, 26);
//     lv_obj_set_style_bg_color(wooden_fish_widget_app->btn, lv_color_black(), LV_PART_MAIN);
//     lv_obj_set_style_border_width(wooden_fish_widget_app->btn, 0, LV_PART_MAIN);
//     lv_obj_set_style_pad_all(wooden_fish_widget_app->btn, 0, LV_PART_MAIN);
//     lv_obj_set_style_shadow_opa(wooden_fish_widget_app->btn, 0, 0);
//     lv_obj_align_to(wooden_fish_widget_app->btn, wooden_fish_widget_app->label_today, LV_ALIGN_OUT_RIGHT_MID, 8, 8);

//     wooden_fish_widget_app->imgbtn_fish = lv_img_create(wooden_fish_widget_app->btn);
//     lv_img_set_src(wooden_fish_widget_app->imgbtn_fish, &fish);
//     lv_obj_center(wooden_fish_widget_app->imgbtn_fish);
//     lv_img_set_zoom(wooden_fish_widget_app->imgbtn_fish, 178); /* 缩小2倍 */

//     wooden_fish_widget_app->add_1 = lv_label_create(wooden_fish_widget_app->cont);
//     lv_obj_set_style_text_font(wooden_fish_widget_app->add_1, &wooden_fish_font_cn_8_t, LV_PART_MAIN);
//     lv_obj_set_style_text_color(wooden_fish_widget_app->add_1, lv_color_white(), LV_PART_MAIN);
//     lv_label_set_text(wooden_fish_widget_app->add_1, "功德+1");
//     lv_obj_align_to(wooden_fish_widget_app->add_1, wooden_fish_widget_app->btn, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
//     lv_obj_add_flag(wooden_fish_widget_app->add_1, LV_OBJ_FLAG_HIDDEN); // 初始状态设置为隐藏

//     lv_obj_add_event_cb(wooden_fish_widget_app->btn, btn_event_cb, LV_EVENT_ALL, NULL);

//     lv_obj_clear_flag(wooden_fish_widget_app->cont, LV_OBJ_FLAG_SCROLLABLE);

//     lv_group_add_obj(group, wooden_fish_widget_app->btn);

//     return wooden_fish_widget_app->cont;
// }
