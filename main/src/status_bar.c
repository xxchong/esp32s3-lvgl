#include <lvgl.h>
#include "util.h"
#include "icon.h"
#include "Notification.h"
#include "lv_port.h"
#include "esp_log.h"
#include "time.h"
static lv_obj_t *wifi_status;
static lv_obj_t *battery_status;
static lv_obj_t *current_time;
static lv_obj_t *notification;

static struct tm timeinfo;
// extern struct tm timeinfo;
// extern lv_indev_t *indev;
void time_refresh(lv_timer_t *timer)
{
    timeinfo = get_timeinfo();

    lv_label_set_text_fmt(current_time, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);

    // // 每5秒检查WiFi连接状态
    // if (WiFi.status() == WL_CONNECTED)
    // {
    //     lv_label_set_text(wifi_status, USER_SYMBOL_CONNECTEED_WIFI);
    // }
    // else
    // {
    //     lv_label_set_text(wifi_status, USER_SYMBOL_DISCONNECT_WIFI);
    // }
}

static void btn_cb(lv_event_t *e)
{
    lv_scr_load_anim(Notification->root, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 500, 100, false);
    // lv_scr_load(Notification->root);
    lv_indev_set_group(indev, Notification->group);
}

void lv_status_bar_create(lv_obj_t *status_bar)
{
    wifi_status = lv_label_create(status_bar);
    current_time = lv_label_create(status_bar);
    battery_status = lv_label_create(status_bar);
    notification = lv_btn_create(status_bar);
    lv_obj_set_style_text_font(wifi_status, &my_symbol_font_24_t, 0);
    lv_obj_set_style_text_color(wifi_status, lv_color_white(), 0);
    lv_obj_set_style_text_font(current_time, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(current_time, lv_color_white(), 0);
    lv_obj_set_style_text_font(battery_status, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(battery_status, lv_color_white(), 0);

    lv_obj_align(wifi_status, LV_ALIGN_LEFT_MID, 12, 0);
    lv_obj_align(current_time, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(battery_status, LV_ALIGN_RIGHT_MID, -12, 0);

    lv_obj_set_size(notification, 7, 7);
    lv_obj_set_style_radius(notification, LV_RADIUS_CIRCLE, 0);
    lv_obj_align_to(notification, current_time, LV_ALIGN_OUT_LEFT_MID, -13, 0);
    // lv_obj_set_style_bg_color(notification, lv_color_hex(0xff0000), LV_PART_MAIN);
    lv_obj_set_style_bg_color(notification, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_shadow_opa(notification, 0, 0);

    lv_obj_add_event_cb(notification, btn_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(notification, lv_color_hex(0xFF6600), LV_STATE_FOCUS_KEY);

    lv_label_set_text(wifi_status, USER_SYMBOL_CONNECTEED_WIFI);

    timeinfo = get_timeinfo();
    lv_label_set_text_fmt(current_time, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);

    lv_label_set_text(battery_status, "100%");

    lv_timer_create(time_refresh, 5000, NULL);
}