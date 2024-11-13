
#include "sys.h"
#include <math.h>

// extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_obj_t *calculator_page;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_btn;
    lv_obj_t *btnmatrix;
    lv_obj_t *textarea;
    char expression[100];
    long double result;
    bool is_new_input;
} Calculators;

static Calculators *calculators_app;

static const char *btnm_map[] = {"AC", LV_SYMBOL_LEFT, "%", "/", "\n", "7", "8",
                                 "9", "x", "\n", "4", "5", "6", "-", "\n",
                                 "1", "2", "3", "+", "\n", "0", ".", "=", ""};


static void btn_return_cb(lv_event_t *e)
{
    //返回上一级

    lv_page->tools_page = tools_list_create();

    lv_scr_load_anim(lv_page->tools_page, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, true);

    cleanup_page(lv_page->calculator_page);
}


lv_obj_t *calculators_create(void)
{
    if (calculators_app == NULL)
    {
        calculators_app = (Calculators *)malloc(sizeof(Calculators));
        if (calculators_app == NULL)
        {
            printf("Failed to allocate memory for calculators_app\n");
            return NULL;
        }
        calculators_app->calculator_page = NULL;
        calculators_app->group = NULL;
        calculators_app->btn_return = NULL;
        calculators_app->label_btn = NULL;
        calculators_app->btnmatrix = NULL;
        calculators_app->textarea = NULL;
        calculators_app->expression[0] = '\0';
        calculators_app->result = 0;
        calculators_app->is_new_input = true;
    }
 
    calculators_app->calculator_page = create_page("Calculators");


 
    // 创建输入输出框
    calculators_app->textarea = lv_textarea_create(calculators_app->calculator_page);
    lv_obj_set_size(calculators_app->textarea, 230, 60);
    lv_obj_align(calculators_app->textarea, LV_ALIGN_TOP_MID, 0, 2);
    lv_textarea_set_text(calculators_app->textarea, "");
    lv_obj_add_state(calculators_app->textarea, LV_STATE_DISABLED);
    lv_obj_set_style_text_font(calculators_app->textarea, &lv_font_montserrat_30, 0);

    // 创建按钮矩阵
    calculators_app->btnmatrix = lv_btnmatrix_create(calculators_app->calculator_page);
    lv_obj_set_style_pad_all(calculators_app->btnmatrix, 2, 0);
    lv_obj_set_size(calculators_app->btnmatrix, 240, 180);
    lv_btnmatrix_set_map(calculators_app->btnmatrix, btnm_map);
    lv_btnmatrix_set_btn_width(calculators_app->btnmatrix, 16, 2);
    lv_obj_set_style_radius(calculators_app->btnmatrix, LV_RADIUS_CIRCLE, LV_PART_ITEMS);
    lv_obj_align(calculators_app->btnmatrix, LV_ALIGN_BOTTOM_MID, 0, -5);
    lv_obj_set_style_text_font(calculators_app->btnmatrix, &lv_font_montserrat_20, 0);

    return calculators_app->calculator_page;

}