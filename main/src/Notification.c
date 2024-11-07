#include "sys.h"
LV_FONT_DECLARE(weather_font_cn_40_t);

// extern lv_indev_t *indev;
// extern lv_group_t *group;
extern lv_obj_t *root;

Notification_t *Notification;

static void time_refresh(lv_timer_t *timer)
{
    // struct tm timeinfo = get_timeinfo();
    // lv_label_set_text_fmt(Notification->label_time, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
}

static void my_slider_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    char buf[8];
    int val = (int)lv_slider_get_value(slider);

    // // 将滑块值从0-5映射到0-100范围
    // int brightness = (val * 100) / 5;                            // 将滑块值映射到0-100
    // brightness = brightness < 0 ? 0 : (brightness > 100 ? 100 : brightness); // 确保亮度值在0到100之间

    // printf("滑块值:%d, 亮度值:%d%%\n", val, val);

    // set_backlight(val);

    // // 更新显示的百分比
    // sprintf(buf, "%d%%", (int)((val * 100) / 5)); // 显示当前滑块值的百分比

    // ledcWrite(CHANNEL, pwm_value);

    // 更新滑块的值
    // lv_slider_set_value(slider, val, LV_ANIM_OFF); // 确保滑块的值被更新
}

lv_obj_t *create_notification(void)
{

    // 确保 gpio_app 已经被分配内存
    if (Notification == NULL)
    {
        Notification = (Notification_t *)malloc(sizeof(Notification_t));
        if (Notification == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for gpio_app\n");
            return NULL;
        }
        // 初始化成员变量
        Notification->bluetooth_btn = NULL;
        Notification->label = NULL;
        Notification->notification_page = NULL;
        Notification->slider_brightness = NULL;
        Notification->slider_volume = NULL;
        Notification->wifi_btn = NULL;
        Notification->group = NULL;
        Notification->label_time = NULL;
    }

    static lv_style_t style_btn_default;
    lv_style_init(&style_btn_default);
    lv_style_set_bg_color(&style_btn_default, lv_color_hex(0x708890));
    lv_style_set_radius(&style_btn_default, 10);
    lv_style_set_shadow_opa(&style_btn_default, 0);

    static lv_style_t style_btn_checked;
    lv_style_init(&style_btn_checked);
    lv_style_set_bg_color(&style_btn_checked, lv_color_hex(0x3482ff));

    static lv_style_t style_slider_part_main;
    lv_style_init(&style_slider_part_main);
    lv_style_set_bg_color(&style_slider_part_main, lv_color_hex(0x14351c));
    lv_style_set_radius(&style_slider_part_main, 10);

    static lv_style_t style_slider_part_indicator;
    lv_style_init(&style_slider_part_indicator);
    lv_style_set_bg_color(&style_slider_part_indicator, lv_color_hex(0xffffff));
    lv_style_set_radius(&style_slider_part_indicator, 10);

    static lv_style_t style_slider_part_knob;
    lv_style_init(&style_slider_part_knob);
    lv_style_set_bg_color(&style_slider_part_knob, lv_color_hex(0xffffff));
    lv_style_set_bg_opa(&style_slider_part_knob, LV_OPA_TRANSP);
    lv_style_set_border_width(&style_slider_part_knob, 0);
    lv_style_set_radius(&style_slider_part_knob, 0);

    Notification->notification_page = create_page("Notification");
    lv_obj_set_style_bg_color(Notification->notification_page, lv_color_hex(0x97a1b6), 0);

    Notification->label_time = lv_label_create(Notification->notification_page);
    lv_obj_set_style_text_font(Notification->label_time, &weather_font_cn_40_t, 0);
    lv_obj_set_style_text_color(Notification->label_time, lv_color_white(), 0);
    lv_label_set_text(Notification->label_time, "11:23");
    lv_obj_align(Notification->label_time, LV_ALIGN_TOP_MID, 0, 20);

    Notification->wifi_btn = lv_btn_create(Notification->notification_page);
    lv_obj_set_size(Notification->wifi_btn, 80, 50);
    lv_obj_align(Notification->wifi_btn, LV_ALIGN_LEFT_MID, 5, -30);
    lv_obj_add_style(Notification->wifi_btn, &style_btn_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(Notification->wifi_btn, &style_btn_checked, LV_STATE_CHECKED);
    Notification->label = lv_label_create(Notification->wifi_btn);
    lv_obj_set_style_text_font(Notification->label, &lv_font_montserrat_20, 0);
    lv_label_set_text(Notification->label, LV_SYMBOL_WIFI);
    lv_obj_center(Notification->label);
    lv_obj_add_flag(Notification->wifi_btn, LV_OBJ_FLAG_CHECKABLE); /* 开启状态切换 */

    Notification->bluetooth_btn = lv_btn_create(Notification->notification_page);
    lv_obj_set_size(Notification->bluetooth_btn, 80, 50);
    lv_obj_align_to(Notification->bluetooth_btn, Notification->wifi_btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 31);
    Notification->label = lv_label_create(Notification->bluetooth_btn);
    lv_obj_set_style_text_font(Notification->label, &lv_font_montserrat_20, 0);
    lv_label_set_text(Notification->label, LV_SYMBOL_BLUETOOTH);
    lv_obj_center(Notification->label);
    lv_obj_add_style(Notification->bluetooth_btn, &style_btn_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(Notification->bluetooth_btn, &style_btn_checked, LV_STATE_CHECKED);
    lv_obj_add_flag(Notification->bluetooth_btn, LV_OBJ_FLAG_CHECKABLE); /* 开启状态切换 */

    Notification->slider_volume = lv_slider_create(Notification->notification_page);
    lv_obj_set_size(Notification->slider_volume, 65, 132);             /* 高度>宽度时，滑块为纵向 */
    lv_slider_set_value(Notification->slider_volume, 50, LV_ANIM_OFF); /* 设置当前值 */
    lv_slider_set_range(Notification->slider_volume, 0, 100);          /* 设置范围值 */
    lv_obj_align_to(Notification->slider_volume, Notification->wifi_btn, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);
    Notification->label = lv_label_create(Notification->slider_volume);
    lv_obj_set_style_text_font(Notification->label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(Notification->label, lv_color_black(), 0);
    lv_label_set_text(Notification->label, LV_SYMBOL_VOLUME_MAX);
    lv_obj_align(Notification->label, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_add_style(Notification->slider_volume, &style_slider_part_indicator, LV_PART_INDICATOR);
    lv_obj_add_style(Notification->slider_volume, &style_slider_part_main, LV_PART_MAIN);
    lv_obj_add_style(Notification->slider_volume, &style_slider_part_knob, LV_PART_KNOB);

    Notification->slider_brightness = lv_slider_create(Notification->notification_page);
    lv_obj_set_size(Notification->slider_brightness, 65, 132);              /* 高度>宽度时，滑块为纵向 */
    lv_slider_set_range(Notification->slider_brightness, 0, 100);           /* 设置范围值 */
    lv_slider_set_value(Notification->slider_brightness, 100, LV_ANIM_OFF); /* 设置当前值 */
    lv_obj_align_to(Notification->slider_brightness, Notification->slider_volume, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    Notification->label = lv_label_create(Notification->slider_brightness);
    lv_obj_set_style_text_font(Notification->label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(Notification->label, lv_color_black(), 0);
    lv_label_set_text(Notification->label, LV_SYMBOL_EYE_OPEN);
    lv_obj_align(Notification->label, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_add_style(Notification->slider_brightness, &style_slider_part_main, LV_PART_MAIN);
    lv_obj_add_style(Notification->slider_brightness, &style_slider_part_indicator, LV_PART_INDICATOR);
    lv_obj_add_style(Notification->slider_brightness, &style_slider_part_knob, LV_PART_KNOB);
    lv_obj_add_event_cb(Notification->slider_brightness, my_slider_cb, LV_EVENT_VALUE_CHANGED, NULL); // 亮度回调函数

    lv_obj_set_style_outline_color(Notification->slider_brightness, lv_color_black(), LV_STATE_EDITED);
    lv_obj_set_style_outline_color(Notification->slider_volume, lv_color_black(), LV_STATE_EDITED);

    // lv_timer_create(time_refresh, 5000, NULL);
    return Notification->notification_page;
}