#include "sys.h"




typedef struct
{
    lv_obj_t *version_page;
    lv_obj_t *btn_return;
    lv_obj_t *label_btn;
    lv_obj_t *label_desc;
} Version_page_t;

static Version_page_t *version_app;


static void btn_return_cb(lv_event_t *e)
{
    //返回上一级
    lv_page->setting_page = create_setting_app();
    lv_scr_load_anim(lv_page->setting_page, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, true);
    cleanup_page(lv_page->version_page);
}

lv_obj_t *create_version_app(void)
{
    // 确保 serial_app 已经被分配内存
    if (version_app == NULL)
    {
        version_app = (Version_page_t *)malloc(sizeof(Version_page_t));
        if (version_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for serial_app\n");
            return NULL;
        }
        // 初始化成员变量
        version_app->version_page = NULL;
        version_app->btn_return = NULL;
        version_app->label_btn = NULL;
        version_app->label_desc = NULL;
    }
    version_app->version_page = create_page("Version"); //创建主页面
    create_status_bar(version_app->version_page); //创建状态栏    

    // 创建描述标签
    version_app->label_desc = lv_label_create(version_app->version_page);
    lv_obj_align(version_app->label_desc, LV_ALIGN_CENTER, 0, -60);
    lv_obj_set_style_text_color(version_app->label_desc, lv_color_black(), 0);
    lv_label_set_text_fmt(version_app->label_desc, "Xxchong OS\nVersion 1.0.0");
    printf("This is Version app\n");

    // 创建返回按钮
    version_app->btn_return = create_app_btn_return(version_app->version_page);
    // 配置按钮事件（如果需要）
    lv_obj_add_event_cb(version_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    return version_app->version_page;
}
