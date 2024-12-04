#include "lvgl/lvgl.h"
#include "util.h"
#include "icon.h"
#include "Notification.h"
#include "lv_port.h"
#include "esp_log.h"
#include "time.h"
static lv_obj_t *wifi_status;
static lv_obj_t *battery_status;
static lv_obj_t *current_time;

lv_timer_t *time_timer;

// 更新所有状态栏时间的回调函数
static void update_time_cb(lv_timer_t *timer)
{
    // 首先检查 label 是否有效
    if (!current_time || !lv_obj_is_valid(current_time))
    {
        // label 无效，暂停定时器
        if (time_timer)
        {
            lv_timer_pause(time_timer);
        }
        return;
    }

    // 确保对象是 label 类型
    if (!lv_obj_check_type(current_time, &lv_label_class))
    {
        if (time_timer)
        {
            lv_timer_pause(time_timer);
        }
        return;
    }

    // 获取当前时间
    get_now_time();

    // 更新时间标签
    char time_str[10];
    strftime(time_str, sizeof(time_str), "%H:%M", timeinfo);
    lv_label_set_text(current_time, time_str);
}

// 设置新的时间标签
void set_status_bar_time_label(lv_obj_t *label)
{
    if (!label || !lv_obj_check_type(label, &lv_label_class))
    {
        return;
    }

    current_time = label;

    // 如果定时器存在且被暂停，重新启动它
    if (time_timer && lv_timer_get_idle())
    {
        lv_timer_resume(time_timer);
    }

    // 立即更新一次时间
    update_time_cb(NULL);
}

void create_status_bar(lv_obj_t *parent)
{

    wifi_status = lv_label_create(parent);
    current_time = lv_label_create(parent);
    battery_status = lv_label_create(parent);
    lv_obj_set_style_text_font(wifi_status, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(wifi_status, lv_color_black(), 0);
    lv_obj_set_style_text_font(current_time, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(current_time, lv_color_black(), 0);
    lv_obj_set_style_text_font(battery_status, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(battery_status, lv_color_black(), 0);

    lv_obj_align(wifi_status, LV_ALIGN_TOP_LEFT, 40, 0);
    lv_obj_align(current_time, LV_ALIGN_TOP_MID, 0, 2);
    lv_obj_align(battery_status, LV_ALIGN_TOP_RIGHT, -20, 2);

    lv_label_set_text(wifi_status, LV_SYMBOL_WIFI);

    get_now_time();
    lv_label_set_text_fmt(current_time, "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);

    lv_label_set_text(battery_status, LV_SYMBOL_BATTERY_3 " 50%");

    set_status_bar_time_label(current_time);

    // time_timer = lv_timer_create(update_time_cb, 5000, NULL);
}