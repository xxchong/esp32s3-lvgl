#include "sys.h"

// extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_obj_t *serial_page;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_desc;
    lv_obj_t *label_btn;
} Serial_t;

static Serial_t *serial_app;

static void btn_return_cb(lv_event_t *e)
{
    back_to_home(serial_app->serial_page);
}

lv_obj_t *create_serial_app(void)
{
    // 确保 serial_app 已经被分配内存
    if (serial_app == NULL)
    {
        serial_app = (Serial_t *)malloc(sizeof(Serial_t));
        if (serial_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for serial_app\n");
            return NULL;
        }
        // 初始化成员变量
        serial_app->serial_page = NULL;
        serial_app->group = NULL;
        serial_app->btn_return = NULL;
        serial_app->label_desc = NULL;
        serial_app->label_btn = NULL;
    }
    // lv_indev_set_group(indev, serial_app->group);
    serial_app->serial_page = create_page("Serial"); // 创建主页面
    create_status_bar(serial_app->serial_page);      // 创建状态栏

    // 创建描述标签
    serial_app->label_desc = lv_label_create(serial_app->serial_page);
    lv_obj_center(serial_app->label_desc);
    lv_obj_set_style_text_color(serial_app->label_desc, lv_color_black(), 0);
    lv_label_set_text_fmt(serial_app->label_desc, "This is Serial app");
    printf("This is Serial app\n");

    // 创建返回按钮
    serial_app->btn_return = create_app_btn_return(serial_app->serial_page);

    // 配置按钮事件（如果需要）
    lv_obj_add_event_cb(serial_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    return serial_app->serial_page;
}
