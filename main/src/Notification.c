#include "sys.h"
LV_FONT_DECLARE(weather_font_cn_40_t);

// extern lv_indev_t *indev;
// extern lv_group_t *group;
extern lv_obj_t *root;

Notification_t *Notification;
static lv_style_t style_btn_default;
static lv_style_t style_btn_checked;
static lv_style_t style_slider_part_main;
static lv_style_t style_slider_part_indicator;
static lv_style_t style_slider_part_knob;
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
    int brightness = (val * 100) / 5;                            // 将滑块值映射到0-100
    brightness = brightness < 0 ? 0 : (brightness > 100 ? 100 : brightness); // 确保亮度值在0到100之间

    printf("滑块值:%d, 亮度值:%d%%\n", val, val);

    set_backlight(val);

    // // 更新显示的百分比
    // sprintf(buf, "%d%%", (int)((val * 100) / 5)); // 显示当前滑块值的百分比

    // ledcWrite(CHANNEL, pwm_value);

    // 更新滑块的值
     lv_slider_set_value(slider, val, LV_ANIM_OFF); // 确保滑块的值被更新
}

void style_init(void)
{
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
        Notification->led_btn = NULL;
        Notification->group = NULL;
        Notification->label_time = NULL;
    }

    lv_style_reset(&style_btn_default);
    lv_style_reset(&style_btn_checked);
    lv_style_reset(&style_slider_part_main);
    lv_style_reset(&style_slider_part_indicator);
    lv_style_reset(&style_slider_part_knob);

    lv_style_init(&style_btn_default);
    lv_style_set_bg_color(&style_btn_default, lv_color_hex(0x16131f));
    // lv_style_set_bg_opa(&style_btn_default, 20);
    lv_style_set_radius(&style_btn_default, LV_RADIUS_CIRCLE);
    lv_style_set_shadow_opa(&style_btn_default, 0);

    lv_style_init(&style_btn_checked);
    lv_style_set_bg_color(&style_btn_checked, lv_color_hex(0x3482ff));

    lv_style_init(&style_slider_part_main);
    lv_style_set_bg_color(&style_slider_part_main, lv_color_hex(0x16131f));
    lv_style_set_radius(&style_slider_part_main, 10);
    // lv_style_set_border_width(&style_slider_part_main, 1);
    // lv_style_set_border_color(&style_slider_part_main, lv_color_hex(0xffffff));

    lv_style_init(&style_slider_part_indicator);
    lv_style_set_bg_color(&style_slider_part_indicator, lv_color_hex(0x3482ff));
    lv_style_set_radius(&style_slider_part_indicator, 10);

    lv_style_init(&style_slider_part_knob);
    lv_style_set_bg_color(&style_slider_part_knob, lv_color_hex(0x3482ff));
    lv_style_set_bg_opa(&style_slider_part_knob, LV_OPA_TRANSP);
    lv_style_set_border_width(&style_slider_part_knob, 0);
    lv_style_set_radius(&style_slider_part_knob, 0);

    Notification->notification_page = create_page("Notification");
    lv_obj_set_style_bg_color(Notification->notification_page, lv_color_black(), 0);

    Notification->label_time = lv_label_create(Notification->notification_page);
    lv_obj_set_style_text_font(Notification->label_time, &weather_font_cn_40_t, 0);
    lv_obj_set_style_text_color(Notification->label_time, lv_color_white(), 0);
    lv_label_set_text(Notification->label_time, "11:23");
    lv_obj_align(Notification->label_time, LV_ALIGN_TOP_MID, 0, 20);

    // 创建一个容器来包含这三个按钮
    lv_obj_t *btn_container = lv_obj_create(Notification->notification_page);
    lv_obj_set_size(btn_container, 240, 70);                         // 设置容器宽度为屏幕宽度
    lv_obj_align(btn_container, LV_ALIGN_TOP_MID, 0, 80);            // 设置容器位置
    lv_obj_set_scrollbar_mode(btn_container, LV_SCROLLBAR_MODE_OFF); // 禁用滚动条
    lv_obj_set_style_pad_all(btn_container, 0, 0);

    // 设置容器为flex布局
    lv_obj_set_flex_flow(btn_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(btn_container, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // 移除容器的背景和边框
    lv_obj_set_style_bg_opa(btn_container, 0, 0);
    lv_obj_set_style_border_width(btn_container, 0, 0);

    // WiFi按钮
    Notification->wifi_btn = lv_btn_create(btn_container);
    lv_obj_set_size(Notification->wifi_btn, 60, 60);
    lv_obj_add_style(Notification->wifi_btn, &style_btn_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(Notification->wifi_btn, &style_btn_checked, LV_STATE_CHECKED);
    Notification->label = lv_label_create(Notification->wifi_btn);
    lv_obj_set_style_text_font(Notification->label, &lv_font_montserrat_20, 0);
    lv_label_set_text(Notification->label, LV_SYMBOL_WIFI);
    lv_obj_center(Notification->label);
    lv_obj_add_flag(Notification->wifi_btn, LV_OBJ_FLAG_CHECKABLE);

    // 蓝牙按钮
    Notification->bluetooth_btn = lv_btn_create(btn_container);
    lv_obj_set_size(Notification->bluetooth_btn, 60, 60);
    Notification->label = lv_label_create(Notification->bluetooth_btn);
    lv_obj_set_style_text_font(Notification->label, &lv_font_montserrat_20, 0);
    lv_label_set_text(Notification->label, LV_SYMBOL_BLUETOOTH);
    lv_obj_center(Notification->label);
    lv_obj_add_style(Notification->bluetooth_btn, &style_btn_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(Notification->bluetooth_btn, &style_btn_checked, LV_STATE_CHECKED);
    lv_obj_add_flag(Notification->bluetooth_btn, LV_OBJ_FLAG_CHECKABLE);

    // LED按钮
    Notification->led_btn = lv_btn_create(btn_container);
    lv_obj_set_size(Notification->led_btn, 60, 60);
    lv_obj_add_style(Notification->led_btn, &style_btn_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(Notification->led_btn, &style_btn_checked, LV_STATE_CHECKED);
    Notification->label = lv_label_create(Notification->led_btn);
    lv_obj_set_style_text_font(Notification->label, &lv_font_montserrat_20, 0);
    lv_label_set_text(Notification->label, LV_SYMBOL_POWER);
    lv_obj_center(Notification->label);
    lv_obj_add_flag(Notification->led_btn, LV_OBJ_FLAG_CHECKABLE);

    lv_obj_add_state(Notification->led_btn, LV_STATE_CHECKED);
    lv_obj_add_state(Notification->bluetooth_btn, LV_STATE_CHECKED);
    lv_obj_add_state(Notification->wifi_btn, LV_STATE_CHECKED);

    Notification->slider_volume = lv_slider_create(Notification->notification_page);
    lv_obj_set_size(Notification->slider_volume, 200, 40);             /* 高度>宽度时，滑块为纵向 */
    lv_slider_set_range(Notification->slider_volume, 0, 100);          /* 设置范围值 */
    lv_slider_set_value(Notification->slider_volume, 50, LV_ANIM_OFF); /* 设置当前值 */
    lv_obj_align_to(Notification->slider_volume, btn_container, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    Notification->label = lv_label_create(Notification->slider_volume);
    lv_obj_set_style_text_font(Notification->label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(Notification->label, lv_color_white(), 0);
    lv_label_set_text(Notification->label, LV_SYMBOL_VOLUME_MAX);
    lv_obj_align(Notification->label, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_add_style(Notification->slider_volume, &style_slider_part_indicator, LV_PART_INDICATOR);
    lv_obj_add_style(Notification->slider_volume, &style_slider_part_main, LV_PART_MAIN);
    lv_obj_add_style(Notification->slider_volume, &style_slider_part_knob, LV_PART_KNOB);

    Notification->slider_brightness = lv_slider_create(Notification->notification_page);
    lv_obj_set_size(Notification->slider_brightness, 200, 40);             /* 高度>宽度时，滑块为纵向 */
    lv_slider_set_range(Notification->slider_brightness, 0, 100);          /* 设置范围值 */
    lv_slider_set_value(Notification->slider_brightness, 50, LV_ANIM_OFF); /* 设置当前值 */
    lv_obj_align_to(Notification->slider_brightness, Notification->slider_volume, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    Notification->label = lv_label_create(Notification->slider_brightness);
    lv_obj_set_style_text_font(Notification->label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(Notification->label, lv_color_white(), 0);
    lv_label_set_text(Notification->label, LV_SYMBOL_EYE_OPEN);
    lv_obj_align(Notification->label, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_add_style(Notification->slider_brightness, &style_slider_part_main, LV_PART_MAIN);
    lv_obj_add_style(Notification->slider_brightness, &style_slider_part_indicator, LV_PART_INDICATOR);
    lv_obj_add_style(Notification->slider_brightness, &style_slider_part_knob, LV_PART_KNOB);
    lv_obj_add_event_cb(Notification->slider_brightness, my_slider_cb, LV_EVENT_VALUE_CHANGED, NULL); // 亮度回调函数

    // lv_obj_set_style_outline_color(Notification->slider_brightness, lv_color_black(), LV_STATE_EDITED);
    // lv_obj_set_style_outline_color(Notification->slider_volume, lv_color_black(), LV_STATE_EDITED);

    //  lv_timer_create(time_refresh, 5000, NULL);
    return Notification->notification_page;
}