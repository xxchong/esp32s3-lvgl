#include "sys.h"

static uint8_t Now_Hour, Now_Minute, Now_Second;
static uint16_t Now_Ms;

typedef struct
{
    lv_obj_t *bg;
    lv_obj_t *gui_hour;
    lv_obj_t *gui_minute;
    lv_obj_t *gui_second;
} watch_1_t;

static watch_1_t *watch_1;

LV_IMG_DECLARE(watch_bg);
LV_IMG_DECLARE(minute);
LV_IMG_DECLARE(hour);
LV_IMG_DECLARE(second);

static lv_obj_t *obj1;
static lv_obj_t *bar;
lv_obj_t *tetx;

lv_timer_t *clock_watch_time_timer = NULL;

void watch_1_time_refresh(void)
{
    if (watch_1 == NULL)
    {
        return;
    }

    get_now_time();
    if (timeinfo == NULL)
    {
        return;
    }

    if (watch_1->gui_second)
    {
        lv_img_set_angle(watch_1->gui_second, 60 * timeinfo->tm_sec);
    }
    if (watch_1->gui_hour)
    {
        lv_img_set_angle(watch_1->gui_hour, 300 * timeinfo->tm_hour + timeinfo->tm_min * 5);
    }
    if (watch_1->gui_minute)
    {
        lv_img_set_angle(watch_1->gui_minute, 60 * timeinfo->tm_min);
    }
}

lv_obj_t *lv_clock_watch_1(lv_obj_t *parent, bool is_preview)
{
    if (watch_1 != NULL)
    {
        free(watch_1);
        watch_1 = NULL;
    }
    if (watch_1 == NULL)
    {
        watch_1 = (watch_1_t *)calloc(1, sizeof(watch_1_t));
    }

    if (clock_watch_time_timer != NULL)
    {
        lv_timer_del(clock_watch_time_timer);
        clock_watch_time_timer = NULL;
    }

    lv_coord_t size = is_preview ? 200 : 300;

    lv_obj_set_style_bg_color(parent, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(parent, LV_OPA_COVER, LV_PART_MAIN);
    watch_1->bg = lv_img_create(parent);
    lv_obj_center(watch_1->bg);
    lv_img_set_src(watch_1->bg, &watch_bg);

    watch_1->gui_hour = lv_img_create(watch_1->bg);
    lv_obj_center(watch_1->gui_hour);
    lv_img_set_src(watch_1->gui_hour, &hour);

    watch_1->gui_minute = lv_img_create(watch_1->bg);
    lv_obj_center(watch_1->gui_minute);
    lv_img_set_src(watch_1->gui_minute, &minute);

    watch_1->gui_second = lv_img_create(watch_1->bg);
    lv_obj_center(watch_1->gui_second);
    lv_img_set_src(watch_1->gui_second, &second);

    lv_img_set_angle(watch_1->gui_hour, 300 * Now_Hour);
    lv_img_set_angle(watch_1->gui_minute, 60 * Now_Minute);
    lv_img_set_angle(watch_1->gui_second, 60 * Now_Second);

    lv_img_set_zoom(watch_1->bg, size);
    lv_img_set_zoom(watch_1->gui_hour, size);
    lv_img_set_zoom(watch_1->gui_minute, size);
    lv_img_set_zoom(watch_1->gui_second, size);

    if (!is_preview)
    {
        // clock_watch_time_timer = lv_timer_create(time_refresh, 1000, NULL);
    }

    return watch_1->bg;
}
