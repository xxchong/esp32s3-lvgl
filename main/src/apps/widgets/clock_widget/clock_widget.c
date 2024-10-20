#include "sys.h"

LV_FONT_DECLARE(clock_font_cn_24_t)
LV_FONT_DECLARE(clock_font_cn_36_t)
typedef struct
{
    lv_obj_t *root;
    lv_obj_t *meter;
    lv_meter_scale_t *scale_min;
    lv_meter_scale_t *scale_hour;
    lv_meter_indicator_t *lv_meterneedle_line_hour;
    lv_meter_indicator_t *lv_meterneedle_line_minute;
    lv_meter_indicator_t *lv_meterneedle_line_second;
} lv_clock_widget1_t;

typedef struct
{
    lv_obj_t *root;
    lv_obj_t *label_time;
    lv_obj_t *label_date;
    lv_obj_t *label_week;
} lv_clock_widget2_t;

static lv_clock_widget2_t *digital_clock_widget_app;

static lv_clock_widget1_t *clock_widget_app;

extern struct tm timeinfo;
const char *weekdays[7] = {"周日", "周一", "周二", "周三", "周四", "周五", "周六"};

// void clock_widget_time_refresh(lv_timer_t *timer)
// {
//     char temp[20];
//     getLocalTime(&timeinfo);

//     // 计算小时值（12小时制）
//     int hour_12 = timeinfo.tm_hour % 12;
//     if (hour_12 == 0)
//         hour_12 = 12; // 将0点转换为12点

//     // 计算小时指针的位置（考虑分钟的影响）
//     float hour_value = hour_12 + timeinfo.tm_min / 60.0f;

//     // 设置小时指针
//     lv_meter_set_indicator_value(clock_widget_app->meter, clock_widget_app->lv_meterneedle_line_hour, hour_value);

//     // 设置分钟指针
//     lv_meter_set_indicator_value(clock_widget_app->meter, clock_widget_app->lv_meterneedle_line_minute, timeinfo.tm_min);

//     // 设置秒指针
//     lv_meter_set_indicator_value(clock_widget_app->meter, clock_widget_app->lv_meterneedle_line_second, timeinfo.tm_sec);

//     sprintf(temp, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
//     lv_label_set_text(digital_clock_widget_app->label_time, temp);

//     sprintf(temp, "%02d.%02d", timeinfo.tm_mon + 1, timeinfo.tm_mday);
//     lv_label_set_text(digital_clock_widget_app->label_date, temp);

//     lv_label_set_text(digital_clock_widget_app->label_week, weekdays[timeinfo.tm_wday]);
// }

lv_obj_t *create_clock_widget1(lv_obj_t *parent)
{

    if (clock_widget_app == NULL)
    {
        clock_widget_app = (lv_clock_widget1_t *)malloc(sizeof(lv_clock_widget1_t));
        if (clock_widget_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for weather_app\n");
            return NULL;
        }
        // 初始化成员变量
        clock_widget_app->root = NULL;
        clock_widget_app->meter = NULL;
        clock_widget_app->scale_min = NULL;
        clock_widget_app->scale_hour = NULL;
        clock_widget_app->lv_meterneedle_line_hour = NULL;
        clock_widget_app->lv_meterneedle_line_minute = NULL;
        clock_widget_app->lv_meterneedle_line_second = NULL;
    }

    // 创建表盘对象
    clock_widget_app->root = lv_obj_create(parent);
    lv_obj_set_size(clock_widget_app->root, 100, 100);
    lv_obj_center(clock_widget_app->root);
    lv_obj_set_style_border_width(clock_widget_app->root, 0, 0);
    lv_obj_set_style_pad_all(clock_widget_app->root, 0, 0);
    lv_obj_set_style_bg_color(clock_widget_app->root, lv_color_black(), 0);

    clock_widget_app->meter = lv_meter_create(clock_widget_app->root);
    // 设置表盘大小为220x220像素
    lv_obj_set_size(clock_widget_app->meter, 98, 98);
    // 将表盘居中显示
    lv_obj_center(clock_widget_app->meter);

    // 移除表盘的默认刻度样式
    lv_obj_remove_style(clock_widget_app->meter, NULL, LV_PART_TICKS);
    // 移除表盘的默认项目样式
    lv_obj_remove_style(clock_widget_app->meter, NULL, LV_PART_ITEMS);
    lv_obj_set_style_size(clock_widget_app->meter, 7, LV_PART_INDICATOR);
    lv_obj_set_style_pad_all(clock_widget_app->meter, 5, 0);

    ////    // 创建分钟刻度
    clock_widget_app->scale_min = lv_meter_add_scale(clock_widget_app->meter);
    //    // 设置分钟刻度：61个刻度（0-60分钟），间隔1，长度10，颜色为灰色
    lv_meter_set_scale_ticks(clock_widget_app->meter, clock_widget_app->scale_min, 61, 1, 2, lv_palette_main(LV_PALETTE_GREY));
    //    // 设置分钟刻度范围：0-60，角度范围360度，起始角度270度
    lv_meter_set_scale_range(clock_widget_app->meter, clock_widget_app->scale_min, 0, 60, 360, 270);

    // 创建小时刻度
    clock_widget_app->scale_hour = lv_meter_add_scale(clock_widget_app->meter);
    // 设置小时刻度：12个刻度，无小刻度，颜色为灰色
    lv_meter_set_scale_ticks(clock_widget_app->meter, clock_widget_app->scale_hour, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));
    // 设置小时主刻度：每1个刻度为主刻度，长度2，宽度20，颜色为黑色，标签与刻度的距离为10
    lv_meter_set_scale_major_ticks(clock_widget_app->meter, clock_widget_app->scale_hour, 1, 2, 4, lv_color_black(), 6);
    // 设置小时刻度范围：1-12，角度范围330度，起始角度300度
    lv_meter_set_scale_range(clock_widget_app->meter, clock_widget_app->scale_hour, 1, 12, 330, 300);

    // 设置刻度标签的字体大小
    lv_obj_set_style_text_font(clock_widget_app->meter, &lv_font_montserrat_12, LV_PART_TICKS);

    clock_widget_app->lv_meterneedle_line_hour = lv_meter_add_needle_line(clock_widget_app->meter, clock_widget_app->scale_hour, 1, lv_color_black(), -20);

    clock_widget_app->lv_meterneedle_line_minute = lv_meter_add_needle_line(clock_widget_app->meter, clock_widget_app->scale_min, 1, lv_color_black(), -15);

    clock_widget_app->lv_meterneedle_line_second = lv_meter_add_needle_line(clock_widget_app->meter, clock_widget_app->scale_min, 1, lv_color_black(), -11);

    lv_meter_set_indicator_value(clock_widget_app->meter, clock_widget_app->lv_meterneedle_line_hour, 5);

    lv_meter_set_indicator_value(clock_widget_app->meter, clock_widget_app->lv_meterneedle_line_minute, 30);

    lv_meter_set_indicator_value(clock_widget_app->meter, clock_widget_app->lv_meterneedle_line_second, 40);

    return clock_widget_app->root;
}

lv_obj_t *create_clock_widget2(lv_obj_t *parent)
{

    if (digital_clock_widget_app == NULL)
    {
        digital_clock_widget_app = (lv_clock_widget2_t *)malloc(sizeof(lv_clock_widget2_t));
        if (digital_clock_widget_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for weather_app\n");
            return NULL;
        }
        digital_clock_widget_app->root = NULL;
        digital_clock_widget_app->label_time = NULL;
        digital_clock_widget_app->label_date = NULL;
        digital_clock_widget_app->label_week = NULL;
    }

    digital_clock_widget_app->root = lv_obj_create(parent);
    lv_obj_set_size(digital_clock_widget_app->root, 220, 90);
    lv_obj_center(digital_clock_widget_app->root);
    lv_obj_set_style_border_width(digital_clock_widget_app->root, 0, 0);
    lv_obj_set_style_pad_all(digital_clock_widget_app->root, 0, 0);
    lv_obj_set_style_bg_color(digital_clock_widget_app->root, lv_color_hex(0x202020), 0);
    lv_obj_set_style_radius(digital_clock_widget_app->root, 15, 0);

    digital_clock_widget_app->label_time = lv_label_create(digital_clock_widget_app->root);
    lv_obj_set_style_text_font(digital_clock_widget_app->label_time, &clock_font_cn_36_t, 0);
    lv_obj_set_style_text_color(digital_clock_widget_app->label_time, lv_color_white(), 0);
    lv_obj_align(digital_clock_widget_app->label_time, LV_ALIGN_TOP_MID, 0, 9);
    lv_label_set_text(digital_clock_widget_app->label_time, "00:00:00");

    digital_clock_widget_app->label_date = lv_label_create(digital_clock_widget_app->root);
    lv_obj_set_style_text_font(digital_clock_widget_app->label_date, &lv_font_montserrat_30, 0);
    lv_obj_set_style_text_color(digital_clock_widget_app->label_date, lv_color_hex(0xfa7878), 0);
    lv_obj_align(digital_clock_widget_app->label_date, LV_ALIGN_BOTTOM_MID, -35, -8);
    lv_label_set_text(digital_clock_widget_app->label_date, "05.01");

    digital_clock_widget_app->label_week = lv_label_create(digital_clock_widget_app->root);
    lv_obj_set_style_text_font(digital_clock_widget_app->label_week, &clock_font_cn_24_t, 0);
    lv_obj_set_style_text_color(digital_clock_widget_app->label_week, lv_color_hex(0x5096fc), 0);
    lv_obj_align(digital_clock_widget_app->label_week, LV_ALIGN_BOTTOM_MID, 48, -13);
    lv_label_set_text(digital_clock_widget_app->label_week, "周一");

    // lv_timer_create(clock_widget_time_refresh, 1000, NULL);

    return digital_clock_widget_app->root;
}
