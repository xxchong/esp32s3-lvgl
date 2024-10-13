#include "sys.h"

extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_desc;
    lv_obj_t *label_btn;
    lv_obj_t *settiong_list; // 设置列表
    lv_obj_t *label_name;    // 列表按钮对象名
    lv_obj_t *icon;          // 按钮图标
} Setting;

static Setting *setting_app;

const char *setting_list_icon[] = {SETTING_LIST_ICON};       // 图标数组
const char *SETTING_LIST_LABEL_NAME[] = {SETTING_LIST_NAME}; // app名称数组
lv_obj_t *setting_list_btns[SETTING_LIST_COUNT];             // 定义列表按钮数组

static void btn_return_cb(lv_event_t *e)
{
    size_t size = lv_fragment_manager_get_stack_size(manager);
    printf("当前栈内有%d个内容\n", size); // 添加调试信息
    if (size > 1)                         // 大于二级界面
    {
    }
    else if (size == 1) // 二级界面
    {
        lv_fragment_manager_pop(manager); // 弹出当前片段
        Return_root_page();
    }
}
// 按钮的回调事件
static void btn_click_event(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *app_name = (lv_obj_t *)lv_event_get_user_data(e);
    const char *name = lv_label_get_text(app_name);
    my_fragment_t *fragment = (my_fragment_t *)lv_fragment_manager_get_top(manager); // 获取当前fragment
    for (int i = 0; i < SETTING_LIST_COUNT; i++)
    { // 进去新页面前获取当前按钮的索引
        if (setting_list_btns[i] == btn)
        {
            fragment->last_focused_index = i; // 将索引给fragment持有
            break;
        }
    }
    printf(name == NULL ? "按钮标签为空\n" : "%s CLICKED (index: %d)\n", name, fragment->last_focused_index);
    last_group = setting_app->group;
    launch_app_fragment(name, false);
}

void create_setting_app(lv_obj_t *parent)
{
    // 确保 setting_app 已经被分配内存
    if (setting_app == NULL)
    {
        setting_app = (Setting *)malloc(sizeof(Setting));
        if (setting_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for setting_app\n");
            return;
        }
        // 初始化成员变量
        setting_app->group = NULL;
        setting_app->btn_return = NULL;
        setting_app->label_desc = NULL;
        setting_app->label_btn = NULL;
        setting_app->settiong_list = NULL;
        setting_app->icon = NULL;
        setting_app->label_name = NULL;
    }
    setting_app->group = lv_group_create();
    lv_indev_set_group(indev, setting_app->group);

    // // 创建描述标签
    // setting_app->label_desc = lv_label_create(parent);
    // lv_obj_center(setting_app->label_desc);
    // lv_obj_set_style_text_color(setting_app->label_desc, lv_color_black(), 0);
    // lv_label_set_text_fmt(setting_app->label_desc, "This is Setting app");
    // printf("This is Setting app\n");

    // 创建返回按钮
    setting_app->btn_return = lv_btn_create(parent);
    lv_obj_set_size(setting_app->btn_return, 15, 15);

    remove_styles(setting_app->btn_return, false, true, true, true);
    lv_obj_set_style_bg_color(setting_app->btn_return, lv_color_white(), 0);
    lv_obj_set_style_border_width(setting_app->btn_return, 1, 0);
    lv_obj_set_style_border_color(setting_app->btn_return, lv_color_black(), 0);

    lv_obj_align_to(setting_app->btn_return, parent, LV_ALIGN_TOP_LEFT, 2, 2);

    // 创建按钮上的标签
    setting_app->label_btn = lv_label_create(setting_app->btn_return);
    lv_obj_set_style_text_font(setting_app->label_btn, &my_symbol_font_10_t, 0);
    lv_label_set_text(setting_app->label_btn, USER_SYMBOL_RETURN2);
    lv_obj_center(setting_app->label_btn);
    lv_obj_set_style_text_color(setting_app->label_btn, lv_color_black(), 0);
    lv_obj_add_event_cb(setting_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(setting_app->group, setting_app->btn_return);

    setting_app->settiong_list = lv_list_create(parent);
    lv_obj_set_style_text_font(setting_app->settiong_list, &lv_font_montserrat_20, 0);
    lv_obj_set_size(setting_app->settiong_list, 240, 236);
    lv_obj_align(setting_app->settiong_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    remove_styles(setting_app->settiong_list, true, true, false, true);

    lv_obj_set_scrollbar_mode(setting_app->settiong_list, LV_SCROLLBAR_MODE_AUTO); // 关闭滚动条

    for (int i = 0; i < SETTING_LIST_COUNT; i++)
    {
        setting_list_btns[i] = lv_list_add_btn(setting_app->settiong_list, setting_list_icon[i], NULL);
        lv_obj_t *app_name = lv_label_create(setting_list_btns[i]);
        lv_obj_set_style_text_font(app_name, &lv_font_montserrat_20, 0);

        lv_label_set_text(app_name, SETTING_LIST_LABEL_NAME[i]);
        lv_obj_align(app_name, LV_ALIGN_CENTER, -5, 0);
        lv_group_add_obj(setting_app->group, setting_list_btns[i]);
        lv_obj_add_event_cb(setting_list_btns[i], btn_click_event, LV_EVENT_CLICKED, app_name);
    }
}
