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
    size_t size = lv_fragment_manager_get_stack_size(manager);
    printf("当前栈内有%d个内容\n", size); // 添加调试信息
    if (size > 1)                         // 大于二级界面
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

static void btn_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        printf("LV_EVENT_CLICKED\n");
    }
    else if (code == LV_EVENT_LONG_PRESSED)
    {
        printf("LV_EVENT_LONG_PRESSED\n");
    }
}
void calculators_create2(lv_obj_t *parent)
{
    if (calculators_app == NULL)
    {
        calculators_app = (Calculators *)malloc(sizeof(Calculators));
        if (calculators_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for tools_app\n");
            return;
        }
        // 初始化成员变量
        calculators_app->group = NULL;
        calculators_app->btn_return = NULL;
        calculators_app->label_btn = NULL;
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

    // 创建按钮上的标签
    calculators_app->label_btn = lv_label_create(calculators_app->btn_return);
    lv_obj_set_style_text_font(calculators_app->label_btn, &my_symbol_font_10_t, 0);
    lv_label_set_text(calculators_app->label_btn, USER_SYMBOL_RETURN2);
    lv_obj_center(calculators_app->label_btn);
    lv_obj_set_style_text_color(calculators_app->label_btn, lv_color_black(), 0);

    // 配置按钮事件（如果需要）
    lv_obj_add_event_cb(calculators_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(calculators_app->group, calculators_app->btn_return);

    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, btn_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn, btn_cb, LV_EVENT_LONG_PRESSED, NULL);
    lv_group_add_obj(calculators_app->group, btn);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
}
