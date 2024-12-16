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
    chart->chart = lv_chart_create(chart->chart_page);
    
    // 设置图表大小和位置
    lv_obj_set_size(chart->chart, 200, 240);
    lv_obj_align(chart->chart, LV_ALIGN_RIGHT_MID, 0, 0);

    // 配置图表参数
    lv_chart_set_point_count(chart->chart, 10);  // 显示10个数据点
    lv_chart_set_range(chart->chart, LV_CHART_AXIS_PRIMARY_Y, -100, 100);  // Y轴范围0-100
    lv_chart_set_div_line_count(chart->chart, 5, 10); // 网格线
    
    // 创建数据系列
    chart->ser1 = lv_chart_add_series(chart->chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    
    // 设置为SHIFT模式,新数据会使旧数据向左移动
    lv_chart_set_update_mode(chart->chart, LV_CHART_UPDATE_MODE_SHIFT);
    
    // 创建定时器,每500ms更新一次数据
    chart->timer = lv_timer_create(chart_timer_cb, 100, NULL);

    lv_obj_set_style_size(chart->chart_page, 0, LV_PART_INDICATOR);
    lv_chart_set_axis_tick(chart->chart, LV_CHART_AXIS_PRIMARY_Y, 5, 3, 21, 1, true, 40);
    // lv_chart_set_zoom_y(chart->chart, 512);

    lv_obj_set_style_bg_color(chart->chart, lv_palette_main(LV_PALETTE_BLUE_GREY), LV_PART_MAIN);

    lv_obj_set_style_width(chart->chart, 0, LV_PART_INDICATOR);

    
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