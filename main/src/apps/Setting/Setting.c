#include "sys.h"

typedef struct
{
    lv_obj_t *setting_page;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_desc;
    lv_obj_t *label_btn;
    lv_obj_t *btns[SETTING_LIST_COUNT];    // 改为按钮数组
} Setting;

static Setting *setting_app;

const char *setting_list_icon[] = {SETTING_LIST_ICON};       // 图标数组
const char *SETTING_LIST_LABEL_NAME[] = {SETTING_LIST_NAME}; // app名称数组

static void btn_return_cb(lv_event_t *e)
{
    back_to_app_screen(lv_page->setting_page);
}
// 按钮的回调事件
static void btn_click_event(lv_event_t *e)
{
   lv_obj_t *app_name = lv_event_get_user_data(e);
   if (strcmp(lv_label_get_text(app_name), "WLAN") == 0)
   {
        lv_page->wifi_page = create_wifi_app();
        lv_scr_load_anim(lv_page->wifi_page, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, true);
   }else if (strcmp(lv_label_get_text(app_name), "我的设备") == 0)  
   {
        lv_page->version_page = create_version_app();
        lv_scr_load_anim(lv_page->version_page, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, true);
    }

}
lv_obj_t *create_setting_app(void)
{
    if (setting_app != NULL)
    {
        free(setting_app);
        setting_app = NULL;
    }
    if (setting_app == NULL)
    {
        setting_app = (Setting *)calloc(1, sizeof(Setting));
    }
    setting_app->setting_page = create_page("Setting"); //创建主页面
    create_status_bar(setting_app->setting_page); //创建状态栏
    lv_obj_set_style_text_color(lv_obj_get_child(setting_app->setting_page, 0), lv_color_white(), 0);
    lv_obj_set_style_text_color(lv_obj_get_child(setting_app->setting_page, 1), lv_color_white(), 0);
    lv_obj_set_style_text_color(lv_obj_get_child(setting_app->setting_page, 2), lv_color_white(), 0);


    // 创建返回按钮
    setting_app->btn_return = create_app_btn_return(setting_app->setting_page);
    lv_obj_set_style_text_color(lv_obj_get_child(setting_app->btn_return, 0), lv_color_white(), 0);
    lv_obj_add_event_cb(setting_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    // 设置页面背景为黑色
    lv_obj_set_style_bg_color(setting_app->setting_page, lv_color_hex(0x000000), LV_PART_MAIN);

    for (int i = 0; i < SETTING_LIST_COUNT; i++)
    {
        // 创建按钮
        setting_app->btns[i] = lv_btn_create(setting_app->setting_page);
        lv_obj_set_size(setting_app->btns[i], 220, 45);  // 设置按钮大小
        lv_obj_align(setting_app->btns[i], LV_ALIGN_TOP_MID, 0, 60 + i * 50);  // 设置按钮位置
        
        // 设置按钮样式
        lv_obj_set_style_bg_color(setting_app->btns[i], lv_color_hex(0x101010), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(setting_app->btns[i], LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_bg_color(setting_app->btns[i], lv_color_hex(0x303030), LV_STATE_PRESSED);
        
        // 创建图标
        lv_obj_t *icon = lv_label_create(setting_app->btns[i]);
        lv_obj_set_style_text_font(icon, &app_setting_icon_25_t, 0);
        lv_obj_set_style_text_color(icon, lv_color_hex(0x1E90FF), LV_PART_MAIN);
        lv_label_set_text(icon, setting_list_icon[i]);
        lv_obj_align(icon, LV_ALIGN_LEFT_MID, 10, 0);
        
        // 创建文本标签
        lv_obj_t *app_name = lv_label_create(setting_app->btns[i]);
        lv_obj_set_style_text_font(app_name, &app_setting_cn_font_16_t, 0);
        lv_obj_set_style_text_color(app_name, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        lv_label_set_text(app_name, SETTING_LIST_LABEL_NAME[i]);
        lv_obj_align(app_name, LV_ALIGN_LEFT_MID, 40, 0);

        // 添加点击事件
        lv_obj_add_event_cb(setting_app->btns[i], btn_click_event, LV_EVENT_CLICKED, app_name);
    }

    return setting_app->setting_page;
}
