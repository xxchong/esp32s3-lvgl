#include "sys.h"

typedef struct
{
    lv_obj_t *chart_page;
    lv_obj_t *chart;
    lv_chart_series_t *ser1;
    lv_timer_t *timer;
} chart_t;

static chart_t* chart;

static void chart_timer_cb(lv_timer_t * timer)
{
    // 生成一个随机数据点(模拟传感器数据)
    int32_t value = rand() % 100;
    
    // 将新数据点添加到图表中
    lv_chart_set_next_value(chart->chart, chart->ser1, value);
}

lv_obj_t *create_chart_app(void)
{
    if (chart != NULL)
    {
        free(chart);
        chart = NULL;
    }
    if(chart == NULL)
    {
        chart = (chart_t *)calloc(1, sizeof(chart_t));
    }
    
    // 创建图表页面
    chart->chart_page = create_page("Chart");
    lv_obj_set_style_bg_color(chart->chart_page, lv_color_black(), LV_PART_MAIN);


    chart->chart = lv_chart_create(chart->chart_page);
    lv_obj_set_style_pad_all(chart->chart, 0, LV_PART_MAIN);  // 设置四周内边距

    lv_chart_set_update_mode(chart->chart, LV_CHART_UPDATE_MODE_SHIFT);    // 设置为SHIFT模式,新数据会使旧数据向左移动
    lv_obj_set_size(chart->chart, 200, 240);
    lv_obj_align(chart->chart, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_width(chart->chart, 0, LV_PART_INDICATOR); // 设置图表INDICATOR宽度为0

    // 创建数据系列
    chart->ser1 = lv_chart_add_series(chart->chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    
    // 配置图表参数
    lv_chart_set_point_count(chart->chart, 10);  // 显示10个数据点
    lv_chart_set_range(chart->chart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);  // Y轴范围0-100
    lv_chart_set_div_line_count(chart->chart, 6, 6); // 网格线
    
    
    
    
    lv_chart_set_axis_tick(chart->chart, LV_CHART_AXIS_PRIMARY_Y, 5, 3, 6, 1, true, 40); // 设置Y轴刻度
    lv_obj_set_style_bg_color(chart->chart, lv_color_black(), LV_PART_MAIN); // 设置背景颜色
    lv_obj_set_style_line_color(chart->chart, lv_color_white(), LV_PART_MAIN); // 设置线条颜色
    lv_obj_set_style_line_width(chart->chart, 2, LV_PART_ITEMS); // 设置折线线条宽度

    lv_obj_set_style_line_color(chart->chart, lv_color_white(), LV_PART_TICKS);//设置刻度线颜色
    lv_obj_set_style_text_color(chart->chart, lv_color_white(), LV_PART_TICKS);//设置刻度文字颜色

    
    lv_chart_set_next_value(chart->chart, chart->ser1, 10);

    // 创建定时器,每500ms更新一次数据
    chart->timer = lv_timer_create(chart_timer_cb, 200, NULL);

    return chart->chart_page;
}


void chart_delete(void)
{
    if(chart != NULL)
    {
        if(chart->timer != NULL)
        {
            lv_timer_del(chart->timer);
        }
        free(chart);
        chart = NULL;
    }
}