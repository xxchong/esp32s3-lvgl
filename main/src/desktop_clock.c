#include "sys.h"

static lv_obj_t *gui_hour;
static lv_obj_t *gui_minute;
static lv_obj_t *gui_second;
static lv_obj_t *bg;
static uint8_t Now_Hour, Now_Minute, Now_Second;
static uint16_t Now_Ms;

LV_IMG_DECLARE(watch_bg);
LV_IMG_DECLARE(minute);
LV_IMG_DECLARE(hour);
LV_IMG_DECLARE(second);

static lv_obj_t *obj1;
static lv_obj_t *bar;
lv_obj_t *tetx;

lv_timer_t *clock_watch_time_timer = NULL;

static void time_refresh(lv_timer_t *timer)
{
    // printf("time:%d %d %d\r\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    get_now_time();
    lv_img_set_angle(gui_second, 60 * timeinfo->tm_sec);                        /* ˳ʱ뷽ת */
    lv_img_set_angle(gui_hour, 300 * timeinfo->tm_hour + timeinfo->tm_min * 5); /* ˳ʱ뷽ת */
    lv_img_set_angle(gui_minute, 60 * timeinfo->tm_min);                        /* ˳ʱ뷽ת */
}

void send_event(lv_timer_t *timer)
{
    get_now_time();

    lv_event_send(bg, LV_EVENT_REFRESH, NULL);
}

void lv_clock_demo(lv_obj_t *parent)
{
    lv_obj_set_style_bg_color(parent, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(parent, LV_OPA_COVER, LV_PART_MAIN);
    bg = lv_img_create(parent); //
    lv_obj_center(bg);
    lv_img_set_src(bg, &watch_bg);

    gui_hour = lv_img_create(bg); //
    lv_obj_center(gui_hour);
    lv_img_set_src(gui_hour, &hour);

    gui_minute = lv_img_create(bg); //
    lv_obj_center(gui_minute);
    lv_img_set_src(gui_minute, &minute);

    gui_second = lv_img_create(bg); //
    lv_obj_center(gui_second);
    lv_img_set_src(gui_second, &second);

    // get_now_time();
    // Now_Hour = timeinfo->tm_hour, Now_Minute = timeinfo->tm_min, Now_Second = timeinfo->tm_sec;
    lv_img_set_angle(gui_hour, 300 * Now_Hour);    /*  */
    lv_img_set_angle(gui_minute, 60 * Now_Minute); /*  */
    lv_img_set_angle(gui_second, 60 * Now_Second); /*  */

    lv_img_set_zoom(bg, 300);
    lv_img_set_zoom(gui_hour, 300);
    lv_img_set_zoom(gui_minute, 300);
    lv_img_set_zoom(gui_second, 300);

    // lv_obj_add_event_cb(bg, time_refresh, LV_EVENT_REFRESH, NULL);
    clock_watch_time_timer = lv_timer_create(time_refresh, 1000, NULL);
}
