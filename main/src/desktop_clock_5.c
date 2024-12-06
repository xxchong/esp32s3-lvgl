#include "sys.h"

typedef struct
{
    lv_obj_t *meter;
    lv_obj_t *label_hour, *label_minute, *label_center;
    lv_obj_t *arc_battery, *arc_battery_label;
    lv_obj_t *arc_steps, *arc_steps_label;
    lv_obj_t *arc_temp, *arc_temp_label;
    lv_obj_t *arc_heart, *arc_heart_label;
    lv_obj_t *weather_text, *weather_temp, *weather_location;
    lv_obj_t *label_date;
    lv_obj_t *label_icon_steps, *label_icon_heart, *label_icon_target, *label_icon_battery;
    lv_meter_scale_t *scale;
} watch_5_t;

LV_FONT_DECLARE(watch_5_font_cn_14_t);
LV_FONT_DECLARE(watch_5_font_cn_10_t);
LV_FONT_DECLARE(watch_5_font_50_t);
LV_FONT_DECLARE(watch_5_font_30_t);

static watch_5_t *watch_5;
static const char *watch_weekdays[7] = {"周日", "周一", "周二", "周三", "周四", "周五", "周六"};
lv_timer_t *clock_watch_time_timer_5 = NULL;
static lv_style_t style_arc_label;
static lv_style_t style_weather_label;
// 添加刻度动画执行回调函数
static void tick_length_anim_cb(void *var, int32_t value)
{
    lv_obj_t *meter = (lv_obj_t *)var;
    lv_meter_set_scale_ticks(watch_5->meter, watch_5->scale, 61, 1, value, lv_color_white());
    lv_meter_set_scale_major_ticks(watch_5->meter, watch_5->scale, 5, 0, value, lv_color_white(), -2);
}

void send_anim_meter_event(void)
{
    lv_event_send(watch_5->meter, LV_EVENT_VALUE_CHANGED, NULL);
}

static void anim_meter_event_cb(lv_event_t *e)
{
    // 创建刻度长度动画
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, watch_5->meter);
    lv_anim_set_time(&a, 700);     // 动画持续1秒
    lv_anim_set_delay(&a, 10);     // 延迟200ms开始
    lv_anim_set_values(&a, 12, 4); // 从长度10变化到4
    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_set_exec_cb(&a, tick_length_anim_cb);
    lv_anim_start(&a);
}
static void set_time_label(void)
{
    get_now_time();
    char buf[64];

    // 检查指针和结构体是否有效
    if (!watch_5 || !timeinfo)
    {
        return;
    }

    // 检查label对象是否存在
    if (watch_5->label_hour)
    {
        sprintf(buf, "%02d", timeinfo->tm_hour);
        lv_label_set_text(watch_5->label_hour, buf);
    }

    if (watch_5->label_minute)
    {
        sprintf(buf, "%02d", timeinfo->tm_min);
        lv_label_set_text(watch_5->label_minute, buf);
    }
}

void watch_5_time_refresh(void)
{
    set_time_label();
}

static void init_styles(bool is_preview)
{
    const lv_font_t *font = (is_preview) ? &watch_5_font_cn_10_t : &watch_5_font_cn_14_t;
    lv_style_reset(&style_arc_label);
    lv_style_init(&style_arc_label);
    lv_style_set_text_color(&style_arc_label, lv_color_white());
    lv_style_set_text_font(&style_arc_label, &lv_font_montserrat_16);
    lv_style_reset(&style_weather_label);
    lv_style_init(&style_weather_label);
    lv_style_set_text_color(&style_weather_label, lv_color_white());
    lv_style_set_text_font(&style_weather_label, font);
}

static lv_obj_t *create_arc(lv_obj_t *parent, int32_t range_min, int32_t range_max, int32_t value, int32_t size, int32_t width, int16_t rotation,
                            lv_color_t color_value)
{
    lv_obj_t *arc = lv_arc_create(parent);
    lv_arc_set_range(arc, range_min, range_max);
    lv_obj_set_style_arc_color(arc, color_value, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc, lv_color_hex(0x474747), LV_PART_MAIN);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
    lv_arc_set_bg_angles(arc, 0, 80);   // 改为80度，留出间隔
    lv_arc_set_angles(arc, 0, 80);      // 改为80度，留出间隔
    lv_arc_set_rotation(arc, rotation); // 旋转到合适位置
    lv_arc_set_value(arc, value);
    lv_obj_set_size(arc, size, size);
    lv_obj_set_style_arc_width(arc, width, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(arc, width, LV_PART_MAIN);
    return arc;
}

static lv_obj_t *create_time_label(lv_obj_t *parent, const char *text, const lv_font_t *font, lv_color_t color_value)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_style_text_font(label, font, 0);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, color_value, 0);
    return label;
}

static lv_obj_t *create_icon_label(lv_obj_t *parent, const char *text, const lv_font_t *font, lv_color_t color_value)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_style_text_font(label, font, 0);
    lv_obj_set_style_text_color(label, color_value, 0);
    lv_label_set_text(label, text);
    return label;
}

static void meter_delete_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    // 删除与该对象相关的所有动画
    lv_anim_del(obj, NULL);
}

lv_obj_t *lv_clock_watch_5(lv_obj_t *parent, bool is_preview)
{
    if (watch_5 != NULL)
    {
        free(watch_5);
        watch_5 = NULL;
    }
    if (watch_5 == NULL)
    {
        watch_5 = (watch_5_t *)calloc(1, sizeof(watch_5_t));
    }

    if (clock_watch_time_timer_5 != NULL)
    {
        lv_timer_del(clock_watch_time_timer_5);
        clock_watch_time_timer_5 = NULL;
    }

    const int arc_size = (is_preview) ? 100 : 170;
    const lv_font_t *font = (is_preview) ? &watch_5_font_30_t : &watch_5_font_50_t;
    const int time_width = (is_preview) ? 25 : 35;
    const int meter_size = (is_preview) ? 175 : 230;
    const int arc_offset = (is_preview) ? 15 : 6;
    const int arc_width = (is_preview) ? 8 : 14;

    lv_obj_set_style_bg_color(parent, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(parent, LV_OPA_COVER, LV_PART_MAIN);
    // 初始化样式
    init_styles(is_preview);

    watch_5->meter = lv_meter_create(parent);
    lv_obj_set_size(watch_5->meter, meter_size, meter_size);
    lv_obj_align(watch_5->meter, LV_ALIGN_CENTER, 0, 0);
    // 移除表盘的默认刻度样式
    lv_obj_remove_style(watch_5->meter, NULL, LV_PART_TICKS);
    // 移除表盘的默认项目样式
    lv_obj_remove_style(watch_5->meter, NULL, LV_PART_ITEMS);
    lv_obj_set_style_size(watch_5->meter, 0, LV_PART_INDICATOR);
    lv_obj_set_style_pad_all(watch_5->meter, 5, 0);

    lv_obj_set_style_bg_color(watch_5->meter, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_color(watch_5->meter, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(watch_5->meter, 1, LV_PART_MAIN);
    lv_obj_set_style_border_opa(watch_5->meter, LV_OPA_20, LV_PART_MAIN);

    /* 设置仪表刻度 */
    watch_5->scale = lv_meter_add_scale(watch_5->meter); /* 定义并添加刻度 */
    lv_obj_set_style_text_font(watch_5->meter, &lv_font_montserrat_8, LV_PART_TICKS);
    lv_obj_set_style_text_color(watch_5->meter, lv_color_white(), LV_PART_TICKS);
    // 设置刻度的角度范围，从270度开始（顶部），然后转360度形成完整圆
    lv_meter_set_scale_range(watch_5->meter, watch_5->scale, 1, 60, 360, 270);
    // 设置小刻度
    lv_meter_set_scale_ticks(watch_5->meter, watch_5->scale, 61, 1, 4, lv_color_white());
    lv_meter_set_scale_major_ticks(watch_5->meter, watch_5->scale, 5, 0, 4, lv_color_white(), -2); // 设置标签距离为-1，这样就不会显示数字标签

    lv_obj_set_style_bg_color(watch_5->meter, lv_color_white(), LV_PART_TICKS);
    lv_obj_set_style_bg_opa(watch_5->meter, LV_OPA_20, LV_PART_TICKS);

    // 微调旋转角度，使间隔均匀
    watch_5->arc_temp = create_arc(watch_5->meter, 0, 100, 20, arc_size, arc_width, 185, lv_color_hex(0xfae941));  // 左上
    watch_5->arc_heart = create_arc(watch_5->meter, 0, 100, 40, arc_size, arc_width, 275, lv_color_hex(0xfd2d20)); // 右上
    watch_5->arc_steps = create_arc(watch_5->meter, 0, 100, 60, arc_size, arc_width, 95, lv_color_hex(0x3585fe));  // 左下
    watch_5->arc_battery = create_arc(watch_5->meter, 0, 100, 80, arc_size, arc_width, 5, lv_color_hex(0x4bc12d)); // 右下

    lv_obj_align(watch_5->arc_temp, LV_ALIGN_CENTER, -arc_offset, -arc_offset);
    lv_obj_align(watch_5->arc_heart, LV_ALIGN_CENTER, arc_offset, -arc_offset);
    lv_obj_align(watch_5->arc_steps, LV_ALIGN_CENTER, -arc_offset, arc_offset);
    lv_obj_align(watch_5->arc_battery, LV_ALIGN_CENTER, arc_offset, arc_offset);

    watch_5->label_hour = create_time_label(watch_5->meter, "12", font, lv_color_white());
    watch_5->label_minute = create_time_label(watch_5->meter, "20", font, lv_color_white());
    watch_5->label_center = create_time_label(watch_5->meter, ":", font, lv_color_white());

    set_time_label();
    lv_obj_align(watch_5->label_hour, LV_ALIGN_CENTER, -time_width, -5);
    lv_obj_align(watch_5->label_minute, LV_ALIGN_CENTER, time_width, -5);
    lv_obj_align(watch_5->label_center, LV_ALIGN_CENTER, 0, -7);

    watch_5->weather_location = lv_label_create(watch_5->meter);
    lv_obj_add_style(watch_5->weather_location, &style_weather_label, 0);
    lv_label_set_text(watch_5->weather_location, "广州市");

    watch_5->weather_text = lv_label_create(watch_5->meter);
    lv_obj_add_style(watch_5->weather_text, &style_weather_label, 0);
    lv_label_set_text(watch_5->weather_text, "多云");

    watch_5->weather_temp = lv_label_create(watch_5->meter);
    lv_obj_add_style(watch_5->weather_temp, &style_weather_label, 0);
    lv_label_set_text(watch_5->weather_temp, "20°C");

    lv_obj_align_to(watch_5->weather_location, watch_5->label_hour, LV_ALIGN_OUT_TOP_LEFT, 8, -5);
    lv_obj_align_to(watch_5->weather_text, watch_5->weather_location, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_align_to(watch_5->weather_temp, watch_5->weather_text, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    watch_5->label_date = lv_label_create(watch_5->meter);
    lv_obj_add_style(watch_5->label_date, &style_weather_label, 0);
    lv_obj_add_style(watch_5->label_date, &style_weather_label, 0);
    lv_label_set_text(watch_5->label_date, "9月15 周三");
    lv_obj_align_to(watch_5->label_date, watch_5->label_center, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    watch_5->label_icon_battery = create_icon_label(watch_5->meter, USER_WATCH_5_SYMBOL_BATTERY_STATUS, &watch_5_font_icon_10_t, lv_color_hex(0xfae93f));
    watch_5->label_icon_steps = create_icon_label(watch_5->meter, USER_WATCH_5_SYMBOL_STEPS, &watch_5_font_icon_10_t, lv_color_hex(0xfd2e1e));
    watch_5->label_icon_heart = create_icon_label(watch_5->meter, USER_WATCH_5_SYMBOL_HEART_RATE, &watch_5_font_icon_10_t, lv_color_hex(0x3484fd));
    watch_5->label_icon_target = create_icon_label(watch_5->meter, USER_WATCH_5_SYMBOL_TARGET, &watch_5_font_icon_10_t, lv_color_hex(0x4bc22d));

    if (is_preview)
    {
        lv_obj_set_pos(watch_5->label_icon_battery, 35, 35);
        lv_obj_set_pos(watch_5->label_icon_steps, 115, 35);
        lv_obj_set_pos(watch_5->label_icon_heart, 40, 115);
        lv_obj_set_pos(watch_5->label_icon_target, 115, 115);
    }
    else
    {
        lv_obj_set_pos(watch_5->label_icon_battery, 55, 50);
        lv_obj_set_pos(watch_5->label_icon_steps, 150, 50);
        lv_obj_set_pos(watch_5->label_icon_heart, 50, 150);
        lv_obj_set_pos(watch_5->label_icon_target, 155, 150);
    }
    lv_obj_add_event_cb(watch_5->meter, anim_meter_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    // 添加删除事件回调
    lv_obj_add_event_cb(watch_5->meter, meter_delete_cb, LV_EVENT_DELETE, NULL);

    // 创建定时器（仅在非预览模式下）
    if (!is_preview)
    {
        // clock_watch_time_timer_5 = lv_timer_create(time_refresh, 30000, NULL); // 30s更新一次时间状态
    }
    return parent;
}