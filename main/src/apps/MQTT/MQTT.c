#include "sys.h"
// extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_obj_t *mqtt_page;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_desc;
    lv_obj_t *label_btn;
} Mqtt;

static Mqtt *mqtt_app;

static void btn_return_cb(lv_event_t *e)
{
    back_to_home(lv_page->mqtt_page);
}

lv_obj_t *create_mqtt_app(void)
{
    // 确保 mqtt_app 已经被分配内存
    if (mqtt_app == NULL)
    {
        mqtt_app = (Mqtt *)malloc(sizeof(Mqtt));
        if (mqtt_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for mqtt_app\n");
            return NULL;
        }
        // 初始化成员变量
        mqtt_app->mqtt_page = NULL;
        mqtt_app->group = NULL;
        mqtt_app->btn_return = NULL;
        mqtt_app->label_desc = NULL;
        mqtt_app->label_btn = NULL;
    }
    //  lv_indev_set_group(indev, mqtt_app->group);
    mqtt_app->mqtt_page = create_page("MQTT"); // 创建主页面
    create_status_bar(mqtt_app->mqtt_page);    // 创建状态栏

    // 创建描述标签
    mqtt_app->label_desc = lv_label_create(mqtt_app->mqtt_page);
    lv_obj_center(mqtt_app->label_desc);
    lv_obj_set_style_text_color(mqtt_app->label_desc, lv_color_black(), 0);
    lv_label_set_text_fmt(mqtt_app->label_desc, "This is Mqtt app");
    printf("This is Mqtt app\n");

    // 创建返回按钮
    mqtt_app->btn_return = create_app_btn_return(mqtt_app->mqtt_page);

    // 配置按钮事件（如果需要）
    lv_obj_add_event_cb(mqtt_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);
    lv_group_add_obj(mqtt_app->group, mqtt_app->btn_return);
    return mqtt_app->mqtt_page;
}
