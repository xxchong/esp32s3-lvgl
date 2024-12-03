
#include "sys.h"
/*蓝牙结构体*/
typedef struct
{
    lv_obj_t *bluetooth_page;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_desc;
    lv_obj_t *label_btn;
} BlueTooth;

static BlueTooth *bluetooth_app;

static void btn_return_cb(lv_event_t *e)
{
    back_to_app_screen(lv_page->bluetooth_page);
}

lv_obj_t *create_bluetooth_app(void)
{
    if (bluetooth_app != NULL)
    {
        free(bluetooth_app);
        bluetooth_app = NULL;
    }
    if (bluetooth_app == NULL)
    {
        bluetooth_app = (BlueTooth *)calloc(1, sizeof(BlueTooth));
        if (bluetooth_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for bluetooth_app\n");
            return NULL;
        }
    }

    bluetooth_app->bluetooth_page = create_page("BlueTooth"); //创建主页面
    create_status_bar(bluetooth_app->bluetooth_page); //创建状态栏
    // 创建描述标签
    bluetooth_app->label_desc = lv_label_create(bluetooth_app->bluetooth_page);
    lv_obj_center(bluetooth_app->label_desc);
    lv_obj_set_style_text_color(bluetooth_app->label_desc, lv_color_black(), 0);
    lv_label_set_text_fmt(bluetooth_app->label_desc, "This is BlueTooth app");
    // 创建返回按钮
    bluetooth_app->btn_return = create_app_btn_return(bluetooth_app->bluetooth_page);
    // 配置按钮事件（如果需要）
    lv_obj_add_event_cb(bluetooth_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);
    return bluetooth_app->bluetooth_page;
}

