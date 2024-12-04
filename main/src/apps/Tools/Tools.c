#include "sys.h"
typedef struct
{
    lv_obj_t *tools_page;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_btn;
    lv_obj_t *btns[TOOLS_LIST_COUNT];    // 改为按钮数组，移除原来的 tools_list 相关变量
} Tools;
static void btn_click_event(lv_event_t *e); // 列表按钮回调事件


const char *tools_list_icon[] = {LIST_ICON};         // 图标数组
const char *LIST_LABEL_NAME[] = {LIST_NAME};                  // app名称数组
lv_obj_t *tools_list_btns[TOOLS_LIST_COUNT]; // 定义列表按钮数组
static Tools *tools_app;

static void btn_click_event(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *app_name = (lv_obj_t *)lv_event_get_user_data(e);
    const char *name = lv_label_get_text(app_name);
    if (strcmp(name, "计算器") == 0)
    {
        lv_page->calculator_page = calculators_create();
        lv_scr_load_anim(lv_page->calculator_page, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, true);
    }
}


static void btn_return_cb(lv_event_t *e)
{
    back_to_app_screen(lv_page->tools_page);
}

lv_obj_t *tools_list_create(void)
{
    if (tools_app != NULL)
    {
        free(tools_app);
        tools_app = NULL;
    }
    if (tools_app == NULL)
    {
        tools_app = (Tools *)calloc(1, sizeof(Tools));

    }

    tools_app->tools_page = create_page("Tools");
    create_status_bar(tools_app->tools_page);
    lv_obj_set_style_text_color(lv_obj_get_child(tools_app->tools_page, 0), lv_color_white(), 0);
    lv_obj_set_style_text_color(lv_obj_get_child(tools_app->tools_page, 1), lv_color_white(), 0);
    lv_obj_set_style_text_color(lv_obj_get_child(tools_app->tools_page, 2), lv_color_white(), 0);

    tools_app->btn_return = create_app_btn_return(tools_app->tools_page);
    lv_obj_set_style_text_color(lv_obj_get_child(tools_app->btn_return, 0), lv_color_white(), 0);
    lv_obj_add_event_cb(tools_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    // 设置页面背景为黑色
    lv_obj_set_style_bg_color(tools_app->tools_page, lv_color_hex(0x000000), LV_PART_MAIN);

    for (int i = 0; i < TOOLS_LIST_COUNT; i++)
    {
        // 创建按钮
        tools_app->btns[i] = lv_btn_create(tools_app->tools_page);
        lv_obj_set_size(tools_app->btns[i], 220, 45);
        lv_obj_align(tools_app->btns[i], LV_ALIGN_TOP_MID, 0, 60 + i * 50);
        
        // 设置按钮样式
        lv_obj_set_style_bg_color(tools_app->btns[i], lv_color_hex(0x101010), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(tools_app->btns[i], LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_bg_color(tools_app->btns[i], lv_color_hex(0x303030), LV_STATE_PRESSED);
        
        // 创建图标
        lv_obj_t *icon = lv_label_create(tools_app->btns[i]);
        lv_obj_set_style_text_font(icon, &app_tools_icon_25_t, 0);
        lv_obj_set_style_text_color(icon, lv_color_hex(0x1E90FF), LV_PART_MAIN);
        lv_label_set_text(icon, tools_list_icon[i]);
        lv_obj_align(icon, LV_ALIGN_LEFT_MID, 10, 0);
        
        // 创建文本标签
        lv_obj_t *app_name = lv_label_create(tools_app->btns[i]);
        lv_obj_set_style_text_font(app_name, &app_tools_cn_font_16_t, 0);
        lv_obj_set_style_text_color(app_name, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        lv_label_set_text(app_name, LIST_LABEL_NAME[i]);
        lv_obj_align(app_name, LV_ALIGN_LEFT_MID, 40, 0);

        // 添加点击事件
        lv_obj_add_event_cb(tools_app->btns[i], btn_click_event, LV_EVENT_CLICKED, app_name);
    }

    return tools_app->tools_page;
}

