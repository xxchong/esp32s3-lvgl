#include "sys.h"

// extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_obj_t *setting_page;
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
    back_to_home(lv_page->setting_page);
}
// 按钮的回调事件
static void btn_click_event(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *app_name = (lv_obj_t *)lv_event_get_user_data(e);
    const char *name = lv_label_get_text(app_name);
    // if (strcmp(name, "WiFi") == 0)
    // {
    //     lv_page->wifi_page = create_wifi_app();
    //     lv_scr_load_anim(lv_page->wifi_page, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, true);
    //     cleanup_page(lv_page->setting_page);
    // }
}

lv_obj_t *create_setting_app(void)
{
    // 确保 setting_app 已经被分配内存
    if (setting_app == NULL)
    {
        setting_app = (Setting *)malloc(sizeof(Setting));
        if (setting_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for setting_app\n");
            return NULL;
        }
        // 初始化成员变量
        setting_app->setting_page = NULL;
        setting_app->group = NULL;
        setting_app->btn_return = NULL;
        setting_app->label_desc = NULL;
        setting_app->label_btn = NULL;
        setting_app->settiong_list = NULL;
        setting_app->icon = NULL;
        setting_app->label_name = NULL;
    }
    setting_app->setting_page = create_page("Setting"); // 创建主页面
    create_status_bar(setting_app->setting_page);       // 创建状态栏        // lv_indev_set_group(indev, setting_app->group);

    
    // 创建返回按钮
    setting_app->btn_return = create_app_btn_return(setting_app->setting_page);

    lv_obj_add_event_cb(setting_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    setting_app->settiong_list = lv_list_create(setting_app->setting_page);
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

    return setting_app->setting_page;
}
