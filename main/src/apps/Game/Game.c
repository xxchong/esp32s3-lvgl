#include "sys.h"

// extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_obj_t *game_page;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_desc;
    lv_obj_t *label_btn;
} Game;

static Game *game_app;

static void btn_return_cb(lv_event_t *e)
{
    Stop_Game();
    back_to_home(lv_page->game_page);
}

lv_obj_t *create_game_app(void)
{
    // 确保 game_app 已经被分配内存
    if (game_app == NULL)
    {
        game_app = (Game *)malloc(sizeof(Game));
        if (game_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for game_app\n");
            return NULL;
        }
        // 初始化成员变量
        game_app->game_page = NULL;
        game_app->group = NULL;
        game_app->btn_return = NULL;
        game_app->label_desc = NULL;
        game_app->label_btn = NULL;
    }

    game_app->game_page = create_page("Game"); // 创建主页面

    lv_obj_set_size(game_app->game_page, 240, 280);
    // create_status_bar(game_app->game_page);    // 创建状态栏

    // // 创建描述标签
    // game_app->label_desc = lv_label_create(game_app->game_page);
    // lv_obj_center(game_app->label_desc);
    // lv_obj_set_style_text_color(game_app->label_desc, lv_color_black(), 0);
    // lv_label_set_text_fmt(game_app->label_desc, "This is Game app");
    // printf("This is Game app\n");

    // 创建返回按钮
    game_app->btn_return = create_app_btn_return(game_app->game_page);
    lv_obj_set_style_text_color(lv_obj_get_child(game_app->btn_return, 0), lv_color_white(), 0);

    // 配置按钮事件（如果需要）
    lv_obj_add_event_cb(game_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    tetris_start_game(game_app->game_page, NULL);

    return game_app->game_page;
}
