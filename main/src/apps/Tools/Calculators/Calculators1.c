#include "sys.h"


extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_btn;
} Calculators;

static Calculators *calculators_app;

static void btn_return_cb(lv_event_t *e)
{

}

void calculators_create1(lv_obj_t *parent)
{

    if (calculators_app != NULL)
    {
        free(calculators_app);
        calculators_app = NULL;
    }
    if (calculators_app == NULL)
    {
        calculators_app = (Calculators *)calloc(1, sizeof(Calculators));
    }
    // 创建返回按钮
    calculators_app->btn_return = lv_btn_create(parent);
    lv_obj_set_size(calculators_app->btn_return, 15, 15);

    remove_styles(calculators_app->btn_return, false, true, true, true);
    lv_obj_set_style_bg_color(calculators_app->btn_return, lv_color_white(), 0);
    lv_obj_set_style_border_width(calculators_app->btn_return, 1, 0);
    lv_obj_set_style_border_color(calculators_app->btn_return, lv_color_black(), 0);
    lv_obj_align_to(calculators_app->btn_return, parent, LV_ALIGN_TOP_LEFT, 2, 2);

    // 创建按钮上的标签
    calculators_app->label_btn = lv_label_create(calculators_app->btn_return);
    lv_obj_set_style_text_font(calculators_app->label_btn, &my_symbol_font_10_t, 0);
    lv_label_set_text(calculators_app->label_btn, USER_SYMBOL_RETURN2);
    lv_obj_center(calculators_app->label_btn);
    lv_obj_set_style_text_color(calculators_app->label_btn, lv_color_black(), 0);

    lv_obj_add_event_cb(calculators_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *kp= lv_keyboard_create(parent);				/* 创建文本区域部件 */
    lv_obj_set_size(kp, 240, 160);
    lv_obj_set_style_text_font(kp,&lv_font_montserrat_16,0);
    lv_obj_align(kp,LV_ALIGN_BOTTOM_MID,0,0);
}

