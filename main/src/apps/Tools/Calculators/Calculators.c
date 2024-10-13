#include "sys.h"
#include <math.h>

extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
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
    size_t size = lv_fragment_manager_get_stack_size(manager);
    printf("当前栈内有%d个内容\n", size); // 添加调试信息
    if (size > 1)                                // 大于二级界面
    {
        lv_indev_set_group(indev, last_group);                                           // 将indev返回给上一级页面
        lv_fragment_manager_pop(manager);                                                // 返回tools
        my_fragment_t *fragment = (my_fragment_t *)lv_fragment_manager_get_top(manager); /*弹出来后返回一级界面后重新创建的界面获取之前保存的索引位置(不会清除)*/

        if (fragment == NULL)
        {
            printf("fragment is NULL\n");
            return; // 处理空指针情况
        }
        uint8_t last_index = fragment->last_focused_index; // 获取最后一次聚焦的索引位置
        const char *name = fragment->name;
        set_focus(tools_list_btns, 3, last_index);
    }
    else if (size == 1) // 二级界面
    {
        lv_fragment_manager_pop(manager); // 弹出当前片段
        Return_root_page();
    }
}


void calculators_create(lv_obj_t *parent)
{
    if (calculators_app == NULL)
    {
        calculators_app = (Calculators *)malloc(sizeof(Calculators));
        if (calculators_app == NULL)
        {
            printf("Failed to allocate memory for calculators_app\n");
            return;
        }
        calculators_app->group = NULL;
        calculators_app->btn_return = NULL;
        calculators_app->label_btn = NULL;
        calculators_app->btnmatrix = NULL;
        calculators_app->textarea = NULL;
        calculators_app->expression[0] = '\0';
        calculators_app->result = 0;
        calculators_app->is_new_input = true;
    }
    calculators_app->group = lv_group_create();
    lv_indev_set_group(indev, calculators_app->group);

    // 创建返回按钮
    calculators_app->btn_return = lv_btn_create(parent);
    lv_obj_set_size(calculators_app->btn_return, 15, 15);
    remove_styles(calculators_app->btn_return, false, true, true, true);
    lv_obj_set_style_bg_color(calculators_app->btn_return, lv_color_white(), 0);
    lv_obj_set_style_border_width(calculators_app->btn_return, 1, 0);
    lv_obj_set_style_border_color(calculators_app->btn_return, lv_color_black(), 0);
    lv_obj_align_to(calculators_app->btn_return, parent, LV_ALIGN_TOP_LEFT, 2, 2);

    calculators_app->label_btn = lv_label_create(calculators_app->btn_return);
    lv_obj_set_style_text_font(calculators_app->label_btn, &my_symbol_font_10_t, 0);
    lv_label_set_text(calculators_app->label_btn, USER_SYMBOL_RETURN2);
    lv_obj_center(calculators_app->label_btn);
    lv_obj_set_style_text_color(calculators_app->label_btn, lv_color_black(), 0);

    lv_obj_add_event_cb(calculators_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(calculators_app->group, calculators_app->btn_return);

    // 创建输入输出框
    calculators_app->textarea = lv_textarea_create(parent);
    lv_obj_set_size(calculators_app->textarea, 230, 70);
    lv_obj_align(calculators_app->textarea, LV_ALIGN_TOP_MID, 0, 20);
    lv_textarea_set_text(calculators_app->textarea, "");
    lv_obj_add_state(calculators_app->textarea, LV_STATE_DISABLED);
    lv_obj_set_style_text_font(calculators_app->textarea, &lv_font_montserrat_30, 0);

    // 创建按钮矩阵
    calculators_app->btnmatrix = lv_btnmatrix_create(parent);
    lv_obj_set_style_pad_all(calculators_app->btnmatrix, 2, 0);
    lv_obj_set_size(calculators_app->btnmatrix, 240, 140);
    lv_btnmatrix_set_map(calculators_app->btnmatrix, btnm_map);
    lv_btnmatrix_set_btn_width(calculators_app->btnmatrix, 16, 2);
    lv_obj_set_style_radius(calculators_app->btnmatrix, LV_RADIUS_CIRCLE, LV_PART_ITEMS);
    lv_obj_align(calculators_app->btnmatrix, LV_ALIGN_BOTTOM_MID, 0, -5);
    lv_obj_set_style_text_font(calculators_app->btnmatrix, &lv_font_montserrat_20, 0);
    lv_group_add_obj(calculators_app->group, calculators_app->btnmatrix);

}