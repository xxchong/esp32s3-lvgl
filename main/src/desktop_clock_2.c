#include "sys.h"

typedef struct
{
    lv_obj_t *label_hour, *label_minute, *label_center;
    lv_obj_t *arc_temp, *arc_temp_label;
    lv_obj_t *arc_battery, *arc_battery_label;
    lv_obj_t *arc_Steps, *arc_Steps_label;
    lv_obj_t *label_date;
    lv_obj_t *label_step_icon, *label_temp_icon, *label_battery_icon;
} watch_2_t;

static uint8_t Now_Hour, Now_Minute;
static watch_2_t *watch_2;
static lv_style_t style_watch_2_time_font, style_watch_2_date_font;
static lv_style_t style_watch_2_icon_font, style_watch_2_label_font;
lv_timer_t *clock_watch_time_timer_2 = NULL;

static const char *watch_weekdays[7] = {"周日", "周一", "周二", "周三", "周四", "周五", "周六"};

static void set_time_label(void)
{
    get_now_time();
    char buf[64];
    sprintf(buf, "%02d", timeinfo->tm_hour);
    lv_label_set_text(watch_2->label_hour, buf);

    sprintf(buf, "%02d", timeinfo->tm_min);
    lv_label_set_text(watch_2->label_minute, buf);

    sprintf(buf, "%s %d日", watch_weekdays[timeinfo->tm_wday], timeinfo->tm_mday);
    lv_label_set_text(watch_2->label_date, buf);
}

void watch_2_time_refresh(void)
{

    set_time_label();
}

static void src_cb(lv_event_t *e)
{
    char buf[64];
    lv_obj_t *obj = lv_event_get_target(e);

    if (obj == watch_2->arc_Steps)
    {
        sprintf(buf, "%d", lv_arc_get_value(watch_2->arc_Steps));
        lv_label_set_text(watch_2->arc_Steps_label, buf);
    }
    else if (obj == watch_2->arc_temp)
    {
        sprintf(buf, "%d°", lv_arc_get_value(watch_2->arc_temp));
        lv_label_set_text(watch_2->arc_temp_label, buf);
    }
    else if (obj == watch_2->arc_battery)
    {
        sprintf(buf, "%d%%", lv_arc_get_value(watch_2->arc_battery));
        lv_label_set_text(watch_2->arc_battery_label, buf);
    }
}

static void init_styles(bool is_preview)
{
    const lv_font_t *time_font = is_preview ? &watch_2_font_65_t : &watch_2_font_95_t;
    const lv_font_t *small_font = is_preview ? &lv_font_montserrat_12 : &lv_font_montserrat_16;
    const lv_font_t *small_font_cn = is_preview ? &watch_2_cn_font_14_t : &watch_2_cn_font_22_t;

    // 时间字体样式
    lv_style_reset(&style_watch_2_time_font);
    lv_style_init(&style_watch_2_time_font);
    lv_style_set_text_font(&style_watch_2_time_font, time_font);
    lv_style_set_text_color(&style_watch_2_time_font, lv_color_hex(0xe71d35));

    // 日期字体样式
    lv_style_reset(&style_watch_2_date_font);
    lv_style_init(&style_watch_2_date_font);
    lv_style_set_text_font(&style_watch_2_date_font, small_font_cn);
    lv_style_set_text_color(&style_watch_2_date_font, lv_color_white());

    // 图标字体样式
    lv_style_reset(&style_watch_2_icon_font);
    lv_style_init(&style_watch_2_icon_font);
    lv_style_set_text_font(&style_watch_2_icon_font, small_font);
    lv_style_set_text_color(&style_watch_2_icon_font, lv_color_hex(0xe71d35));

    // 标签字体样式
    lv_style_reset(&style_watch_2_label_font);
    lv_style_init(&style_watch_2_label_font);
    lv_style_set_text_font(&style_watch_2_label_font, small_font);
    lv_style_set_text_color(&style_watch_2_label_font, lv_color_white());
}

static lv_obj_t *create_arc_with_labels(lv_obj_t *parent, int32_t range_max, int32_t value,
                                        const char *icon_text, const char *label_text,
                                        lv_coord_t size, lv_coord_t width,
                                        lv_obj_t **label_ptr, lv_obj_t **icon_ptr)
{
    lv_obj_t *arc = lv_arc_create(parent);
    lv_arc_set_range(arc, 0, range_max);
    lv_obj_set_style_arc_color(arc, lv_color_hex(0x0301fe), LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(arc, false, LV_PART_MAIN);
    lv_obj_set_style_arc_opa(arc, LV_OPA_50, LV_PART_MAIN);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
    lv_arc_set_rotation(arc, 180);
    lv_arc_set_value(arc, value);
    lv_obj_set_size(arc, size, size);
    lv_obj_set_style_arc_width(arc, width, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(arc, width, LV_PART_MAIN);

    // 创建图标标签
    lv_obj_t *icon = lv_label_create(arc);
    lv_obj_add_style(icon, &style_watch_2_icon_font, 0);
    lv_label_set_text(icon, icon_text);
    lv_obj_align(icon, LV_ALIGN_TOP_MID, 0, 0);
    *icon_ptr = icon; // 保存图标指针

    // 创建值标签
    lv_obj_t *label = lv_label_create(arc);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(label, &style_watch_2_label_font, 0);
    lv_label_set_text(label, label_text);
    *label_ptr = label; // 保存标签指针

    return arc;
}

lv_obj_t *lv_clock_watch_2(lv_obj_t *parent, bool is_preview)
{
    // 初始化watch_2结构体
    if (watch_2 == NULL)
    {
        watch_2 = (watch_2_t *)malloc(sizeof(watch_2_t));
        if (watch_2 == NULL)
        {
            printf("Failed to allocate memory for watch_2\n");
            return NULL;
        }
        memset(watch_2, 0, sizeof(watch_2_t));
    }

    if (clock_watch_time_timer_2 != NULL)
    {
        lv_timer_del(clock_watch_time_timer_2);
        clock_watch_time_timer_2 = NULL;
    }

    // 初始化样式
    init_styles(is_preview);

    // 设置背景
    lv_obj_set_style_bg_color(parent, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(parent, LV_OPA_COVER, LV_PART_MAIN);

    // 创建日期标签
    watch_2->label_date = lv_label_create(parent);
    lv_obj_add_style(watch_2->label_date, &style_watch_2_date_font, 0);

    // 创建时间标签
    watch_2->label_hour = lv_label_create(parent);
    // watch_2->label_center = lv_label_create(parent);
    watch_2->label_minute = lv_label_create(parent);

    lv_obj_add_style(watch_2->label_hour, &style_watch_2_time_font, 0);
    // lv_obj_add_style(watch_2->label_center, &style_watch_2_time_font, 0);
    lv_obj_add_style(watch_2->label_minute, &style_watch_2_time_font, 0);

    // lv_label_set_text(watch_2->label_center, ":");

    set_time_label();

    // 设置尺寸和偏移量
    lv_coord_t arc_size = is_preview ? 50 : 60;
    lv_coord_t arc_width = is_preview ? 3 : 6;
    lv_coord_t bottom_offset = is_preview ? -50 : -60;
    lv_coord_t side_offset = is_preview ? 5 : 20;

    // 创建三个arc控件及其标签
    watch_2->arc_Steps = create_arc_with_labels(parent, 20000, 5000,
                                                LV_SYMBOL_OK, "5000", arc_size, arc_width, &watch_2->arc_Steps_label, &watch_2->label_step_icon);
    watch_2->arc_temp = create_arc_with_labels(parent, 100, 50,
                                               LV_SYMBOL_GPS, "50°", arc_size, arc_width, &watch_2->arc_temp_label, &watch_2->label_temp_icon);
    watch_2->arc_battery = create_arc_with_labels(parent, 100, 100,
                                                  LV_SYMBOL_BATTERY_FULL, "100%", arc_size, arc_width, &watch_2->arc_battery_label, &watch_2->label_battery_icon);

    // 设置位置
    if (is_preview)
    {
        lv_obj_align(watch_2->label_date, LV_ALIGN_TOP_MID, 0, 15);
        lv_obj_align(watch_2->label_hour, LV_ALIGN_CENTER, -30, -30);
        // lv_obj_align(watch_2->label_center, LV_ALIGN_CENTER, 0, -35);
        lv_obj_align(watch_2->label_minute, LV_ALIGN_CENTER, 30, -30);
    }
    else
    {
        lv_obj_align(watch_2->label_date, LV_ALIGN_TOP_MID, 0, 30);
        lv_obj_align(watch_2->label_hour, LV_ALIGN_CENTER, -40, -40);
        // lv_obj_align(watch_2->label_center, LV_ALIGN_CENTER, 0, -50);
        lv_obj_align(watch_2->label_minute, LV_ALIGN_CENTER, 40, -40);
    }

    lv_obj_align(watch_2->arc_Steps, LV_ALIGN_BOTTOM_LEFT, side_offset, bottom_offset);
    lv_obj_align(watch_2->arc_temp, LV_ALIGN_BOTTOM_MID, 0, bottom_offset);
    lv_obj_align(watch_2->arc_battery, LV_ALIGN_BOTTOM_RIGHT, -side_offset, bottom_offset);

    // 添加事件回调
    lv_obj_add_event_cb(watch_2->arc_Steps, src_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(watch_2->arc_temp, src_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(watch_2->arc_battery, src_cb, LV_EVENT_VALUE_CHANGED, NULL);

    // 创建定时器（仅在非预览模式下）
    if (!is_preview)
    {
        // clock_watch_time_timer_2 = lv_timer_create(time_refresh,30000, NULL); //30s更新一次时间状态
    }

    return parent;
}