

#include "sys.h"

// extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_obj_t *calender_page;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_desc;
    lv_obj_t *label_btn;
} Calender_t;

static Calender_t *calender_app;

static void btn_return_cb(lv_event_t *e)
{
    back_to_home(lv_page->calender_page);
}

lv_obj_t *create_calendar_app(void)
{
    // 确保 gpio_app 已经被分配内存
    if (calender_app == NULL)
    {
        calender_app = (Calender_t *)malloc(sizeof(Calender_t));
        if (calender_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for gpio_app\n");
            return NULL;
        }
        // 初始化成员变量
        calender_app->calender_page = NULL;
        calender_app->group = NULL;
        calender_app->btn_return = NULL;
        calender_app->label_desc = NULL;
        calender_app->label_btn = NULL;
    }

    calender_app->calender_page = create_page("Calendar"); // 创建主页面
    create_status_bar(calender_app->calender_page);        // 创建状态栏
    // 创建描述标签
    calender_app->label_desc = lv_label_create(calender_app->calender_page);
    lv_obj_center(calender_app->label_desc);
    lv_obj_set_style_text_color(calender_app->label_desc, lv_color_black(), 0);
    lv_label_set_text_fmt(calender_app->label_desc, "This is Calender app");
    printf("This is Calender app\n");

    // 创建返回按钮
    calender_app->btn_return = create_app_btn_return(calender_app->calender_page);

    // 配置按钮事件（如果需要）
    lv_obj_add_event_cb(calender_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    return calender_app->calender_page;
}
