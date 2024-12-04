#include "sys.h"
typedef struct
{
    lv_obj_t *tools_page;
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

static void btn_click_event(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *app_name = (lv_obj_t *)lv_event_get_user_data(e);
    const char *name = lv_label_get_text(app_name);
    if (strcmp(name, "Calculators") == 0)
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
    // tools_app->group = lv_group_create();
    // lv_indev_set_group(indev, tools_app->group);
    tools_app->tools_page = create_page("Tools"); //创建主页面
    create_status_bar(tools_app->tools_page); //创建状态栏


    // 创建返回按钮
    tools_app->btn_return = create_app_btn_return(tools_app->tools_page);
   

    // 配置按钮事件（如果需要）
    lv_obj_add_event_cb(tools_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);
    // lv_group_add_obj(tools_app->group, tools_app->btn_return);

    tools_app->tools_list = lv_list_create(tools_app->tools_page);
    lv_obj_set_size(tools_app->tools_list, 240, 235);
    lv_obj_align(tools_app->tools_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    remove_styles(tools_app->tools_list, true, true, false, true);

    lv_obj_set_scrollbar_mode(tools_app->tools_list, LV_SCROLLBAR_MODE_AUTO); // 关闭滚动条
    lv_obj_set_style_text_font(tools_app->tools_list, &lv_font_montserrat_20, 0);

    for (int i = 0; i < TOOLS_LIST_COUNT; i++)
    {
        tools_list_btns[i] = lv_list_add_btn(tools_app->tools_list, tools_list_icon[i], NULL);
        lv_obj_t *app_name = lv_label_create(tools_list_btns[i]);
        lv_obj_set_style_text_font(app_name, &lv_font_montserrat_20, 0);

        lv_label_set_text(app_name, LIST_LABEL_NAME[i]);
        lv_obj_align(app_name, LV_ALIGN_CENTER, -5, 0);
        lv_obj_add_event_cb(tools_list_btns[i], btn_click_event, LV_EVENT_CLICKED, app_name);
    }

    return tools_app->tools_page;
}

