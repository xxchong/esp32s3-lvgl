#include "sys.h"


extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_btn;
    lv_obj_t *tools_list; // 工具列表
    lv_obj_t *label_name; // 列表按钮对象名
    lv_obj_t *icon;       // 按钮图标

} Tools;
static void btn_click_event(lv_event_t *e); // 列表按钮回调事件


const char *tools_list_icon[] = {LIST_ICON};         // 图标数组
const char *LIST_LABEL_NAME[] = {LIST_NAME};                  // app名称数组
lv_obj_t *tools_list_btns[TOOLS_LIST_COUNT]; // 定义列表按钮数组
static Tools *tools_app;

// 按钮的回调事件
static void btn_click_event(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *app_name  = (lv_obj_t *)lv_event_get_user_data(e);
    const char *name = lv_label_get_text(app_name);
    my_fragment_t *fragment = (my_fragment_t *)lv_fragment_manager_get_top(manager); // 获取当前fragment
    for (int i = 0; i < TOOLS_LIST_COUNT; i++)
    { // 进去新页面前获取当前按钮的索引
        if (tools_list_btns[i] == btn)
        {
            fragment->last_focused_index = i; // 将索引给fragment持有
            break;
        }
    }
    printf(name == NULL ? "按钮标签为空\n" : "%s CLICKED (index: %d)\n", name, fragment->last_focused_index);
    last_group = tools_app->group;
    launch_app_fragment(name, false);

}



static void btn_return_cb(lv_event_t *e)
{
    size_t size = lv_fragment_manager_get_stack_size(manager);
    printf("当前栈内有%d个内容\n", size); // 添加调试信息
    if (size > 1)                                // 大于二级界面
    {
    }
    else if (size == 1) // 二级界面
    {
        lv_fragment_manager_pop(manager); // 弹出当前片段
        Return_root_page();
    }
}

void tools_list_create(lv_obj_t *parent)
{
    if (tools_app == NULL)
    {
        tools_app = (Tools *)malloc(sizeof(Tools));
        if (tools_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for tools_app\n");
            return;
        }
        // 初始化成员变量
        tools_app->group=NULL;
        tools_app->btn_return = NULL;
        tools_app->label_btn = NULL;
        tools_app->tools_list = NULL;
        tools_app->label_name = NULL;
    }
    tools_app->group = lv_group_create();
    lv_indev_set_group(indev, tools_app->group);


    // 创建返回按钮
    tools_app->btn_return = lv_btn_create(parent);
    lv_obj_set_size(tools_app->btn_return, 15, 15);

    remove_styles(tools_app->btn_return, false, true, true, true);
    lv_obj_set_style_bg_color(tools_app->btn_return, lv_color_white(), 0);
    lv_obj_set_style_border_width(tools_app->btn_return, 1, 0);
    lv_obj_set_style_border_color(tools_app->btn_return, lv_color_black(), 0);
    lv_obj_align_to(tools_app->btn_return, parent, LV_ALIGN_TOP_LEFT, 2, 2);

    // 创建按钮上的标签
    tools_app->label_btn = lv_label_create(tools_app->btn_return);
    lv_obj_set_style_text_font(tools_app->label_btn, &my_symbol_font_10_t, 0);
    lv_label_set_text(tools_app->label_btn, USER_SYMBOL_RETURN2);
    lv_obj_center(tools_app->label_btn);
    lv_obj_set_style_text_color(tools_app->label_btn, lv_color_black(), 0);

    // 配置按钮事件（如果需要）
    lv_obj_add_event_cb(tools_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(tools_app->group, tools_app->btn_return);

    tools_app->tools_list = lv_list_create(parent);
    lv_obj_set_size(tools_app->tools_list, 240, 235);
    lv_obj_align(tools_app->tools_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    remove_styles(tools_app->tools_list, true, true, false, true);

    lv_obj_set_scrollbar_mode(tools_app->tools_list, LV_SCROLLBAR_MODE_AUTO); // 关闭滚动条
    lv_obj_set_style_text_font(tools_app->tools_list, &my_symbol_font_20_t, 0);

    for (int i = 0; i < TOOLS_LIST_COUNT; i++)
    {
        tools_list_btns[i] = lv_list_add_btn(tools_app->tools_list, tools_list_icon[i], NULL);
        lv_obj_t *app_name = lv_label_create(tools_list_btns[i]);
        lv_obj_set_style_text_font(app_name, &lv_font_montserrat_20, 0);

        lv_label_set_text(app_name, LIST_LABEL_NAME[i]);
        lv_obj_align(app_name, LV_ALIGN_CENTER, -5, 0);
        lv_group_add_obj(tools_app->group, tools_list_btns[i]);
        lv_obj_add_event_cb(tools_list_btns[i], btn_click_event, LV_EVENT_CLICKED, app_name);
    }
}

