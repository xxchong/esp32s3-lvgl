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

void create_status_bar(lv_obj_t *parent)
{

    wifi_status = lv_label_create(parent);
    current_time = lv_label_create(parent);
    battery_status = lv_label_create(parent);
    lv_obj_set_style_text_font(wifi_status, &my_symbol_font_16_t, 0);
    lv_obj_set_style_text_color(wifi_status, lv_color_black(), 0);
    lv_obj_set_style_text_font(current_time, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(current_time, lv_color_black(), 0);
    lv_obj_set_style_text_font(battery_status, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(battery_status, lv_color_black(), 0);

    lv_obj_align(wifi_status, LV_ALIGN_TOP_LEFT, 12, 0);
    lv_obj_align(current_time, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_align(battery_status, LV_ALIGN_TOP_RIGHT, -12, 0);

    lv_label_set_text(wifi_status, USER_SYMBOL_CONNECTEED_WIFI);
    // timeinfo = get_timeinfo();
    lv_label_set_text_fmt(current_time, "%02d:%02d", 12, 22);

    lv_label_set_text(battery_status, LV_SYMBOL_BATTERY_3 " 100%");

    // lv_timer_create(time_refresh, 5000, NULL);
}