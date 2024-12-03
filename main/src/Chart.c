#include "sys.h"



typedef struct
{
    lv_obj_t *chart;
} chart_t;

static chart_t* chart;
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

    chart->chart = lv_chart_create(lv_scr_act());
    lv_obj_set_size(chart->chart, 240, 240);
    
    lv_obj_align(chart->chart, LV_ALIGN_CENTER, 0, 0);

    return chart->chart;
}