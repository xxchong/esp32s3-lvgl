
#include "sys.h"

// LV_IMG_DECLARE(kun_background);

// LV_IMG_DECLARE(kun);
LV_FONT_DECLARE(watch_3_font_35_t);
LV_FONT_DECLARE(watch_3_font_65_t);
LV_FONT_DECLARE(watch_3_font_cn_20_t);
LV_FONT_DECLARE(watch_3_font_cn_12_t);

typedef struct
{
    lv_obj_t *gif;
    lv_obj_t *labe_hour;
    lv_obj_t *labe_center;
    lv_obj_t *labe_minute;
    lv_obj_t *labe_date;
    lv_obj_t *img;
} watch_4_t;

static watch_4_t *watch_4;
static lv_style_t style_watch_4_label_time_font;
static lv_style_t style_watch_4_label_date_font;

lv_timer_t *clock_watch_time_timer_4 = NULL;

static const char *watch_weekdays[7] = {"周日", "周一", "周二", "周三", "周四", "周五", "周六"};

static void set_time_label(void)
{
    get_now_time();
    char buf[64];
    sprintf(buf, "%02d", timeinfo->tm_hour);
    lv_label_set_text(watch_4->labe_hour, buf);

    sprintf(buf, "%02d", timeinfo->tm_min);
    lv_label_set_text(watch_4->labe_minute, buf);

    sprintf(buf, "%s %d日", watch_weekdays[timeinfo->tm_wday], timeinfo->tm_mday);
    lv_label_set_text(watch_4->labe_date, buf);
}

void watch_4_time_refresh(void)
{
    set_time_label();
}

static void init_styles(bool is_preview)
{
    const lv_font_t *time_font = is_preview ? &watch_3_font_35_t : &watch_3_font_65_t;
    const lv_font_t *date_font = is_preview ? &watch_3_font_cn_12_t : &watch_3_font_cn_20_t;

    lv_style_reset(&style_watch_4_label_time_font);
    lv_style_init(&style_watch_4_label_time_font);
    lv_style_set_text_font(&style_watch_4_label_time_font, time_font);
    lv_style_set_text_color(&style_watch_4_label_time_font, lv_color_hex(0x908be5));

    lv_style_reset(&style_watch_4_label_date_font);
    lv_style_init(&style_watch_4_label_date_font);
    lv_style_set_text_font(&style_watch_4_label_date_font, date_font);
    lv_style_set_text_color(&style_watch_4_label_date_font, lv_color_hex(0x908be5));
}

lv_obj_t *lv_clock_watch_4(lv_obj_t *parent, bool is_preview)
{
    if (watch_4 == NULL)
    {
        watch_4 = (watch_4_t *)malloc(sizeof(watch_4_t));
        memset(watch_4, 0, sizeof(watch_4_t));
    }

    if (clock_watch_time_timer_4 != NULL)
    {
        lv_timer_del(clock_watch_time_timer_4);
        clock_watch_time_timer_4 = NULL;
    }

    // watch_4->img=lv_img_create(parent);
    // lv_img_set_src(watch_4->img, &kun_background);
    // lv_obj_align(watch_4->img, LV_ALIGN_TOP_MID, 0, 0);

    init_styles(is_preview);
    //  watch_4->gif = lv_gif_create(parent);
    //  lv_gif_set_src(watch_4->gif, &kun);
    //  lv_obj_align(watch_4->gif, LV_ALIGN_BOTTOM_MID, 0, 0);

    if (is_preview)
    {
        // lv_img_set_zoom(watch_4->gif, 200);
    }

    watch_4->labe_date = lv_label_create(parent);
    lv_obj_add_style(watch_4->labe_date, &style_watch_4_label_date_font, 0);

    watch_4->labe_center = lv_label_create(parent);
    lv_label_set_text(watch_4->labe_center, ":");
    lv_obj_add_style(watch_4->labe_center, &style_watch_4_label_time_font, 0);

    watch_4->labe_hour = lv_label_create(parent);
    lv_obj_add_style(watch_4->labe_hour, &style_watch_4_label_time_font, 0);

    watch_4->labe_minute = lv_label_create(parent);
    lv_obj_add_style(watch_4->labe_minute, &style_watch_4_label_time_font, 0);

    lv_obj_move_foreground(watch_4->labe_center); // 移至最顶层
    lv_obj_move_foreground(watch_4->labe_hour);   // 移至最顶层
    lv_obj_move_foreground(watch_4->labe_minute); // 移至最顶层

    set_time_label();

    if (is_preview)
    {
        lv_obj_align(watch_4->labe_center, LV_ALIGN_TOP_MID, 0, 32);
        lv_obj_align(watch_4->labe_hour, LV_ALIGN_TOP_LEFT, 20, 30);
        lv_obj_align(watch_4->labe_minute, LV_ALIGN_TOP_RIGHT, -20, 30);
        lv_obj_align(watch_4->labe_date, LV_ALIGN_TOP_MID, 0, 16);
        // lv_img_set_zoom(watch_4->img, 280);
    }
    else
    {
        lv_obj_align(watch_4->labe_center, LV_ALIGN_TOP_MID, 0, 35);
        lv_obj_align(watch_4->labe_hour, LV_ALIGN_TOP_LEFT, 20, 40);
        lv_obj_align(watch_4->labe_minute, LV_ALIGN_TOP_RIGHT, -20, 40);
        lv_obj_align(watch_4->labe_date, LV_ALIGN_TOP_MID, 0, 13);
    }

    if (!is_preview)
    {
        // clock_watch_time_timer_4 = lv_timer_create(time_refresh, 30000, NULL);
    }
    return parent;
}
