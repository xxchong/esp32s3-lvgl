#include "sys.h"

// extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_obj_t *music_page;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_desc;
    lv_obj_t *label_btn;
} Music;

static Music *music_app;

static void btn_return_cb(lv_event_t *e)
{
    back_to_home(lv_page->music_page);
}

lv_obj_t *create_music_app(void)
{
    // 确保 music_app 已经被分配内存
    if (music_app == NULL)
    {
        music_app = (Music *)malloc(sizeof(Music));
        if (music_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for music_app\n");
            return NULL;
        }
        // 初始化成员变量
        music_app->music_page = NULL;
        music_app->group = NULL;
        music_app->btn_return = NULL;
        music_app->label_desc = NULL;
        music_app->label_btn = NULL;
    }
    // lv_indev_set_group(indev, music_app->group);
    //  lv_indev_set_group(indev, mqtt_app->group);
    music_app->music_page = create_page("Music"); // 创建主页面
    create_status_bar(music_app->music_page);     // 创建状态栏

    // 创建描述标签
    music_app->label_desc = lv_label_create(music_app->music_page);
    lv_obj_center(music_app->label_desc);
    lv_obj_set_style_text_color(music_app->label_desc, lv_color_black(), 0);
    lv_label_set_text_fmt(music_app->label_desc, "This is Music app");
    printf("This is Music app\n");

    // 创建返回按钮
    music_app->btn_return = create_app_btn_return(music_app->music_page);

    // 配置按钮事件（如果需要）
    lv_obj_add_event_cb(music_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    return music_app->music_page;
}
