/*
 * @Author: xxchong 2106997706@qq.com
 * @Date: 2024-11-04 16:19:58
 * @LastEditors: xxchong 2106997706@qq.com
 * @LastEditTime: 2024-11-07 15:36:26
 * @FilePath: \lv_port_pc_eclipse-release-v8.3\gui\src\MQTT.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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
    back_to_app_screen(mqtt_app->mqtt_page);
}

lv_obj_t *create_mqtt_app(void)
{
    if (mqtt_app != NULL)
    {
        free(mqtt_app);
        mqtt_app = NULL;
    }
    if (mqtt_app == NULL)
    {
        mqtt_app = (Mqtt *)calloc(1, sizeof(Mqtt));
    }
    //  lv_indev_set_group(indev, mqtt_app->group);
    mqtt_app->mqtt_page = create_page("MQTT"); //创建主页面
    create_status_bar(mqtt_app->mqtt_page); //创建状态栏


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
