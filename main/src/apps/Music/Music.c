
#include "sys.h"

// extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_obj_t *title;
    lv_obj_t *author;
    lv_obj_t *music_page;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *btn_next;
    lv_obj_t *btn_last;
    lv_obj_t *label_btn;
    lv_obj_t *arc;
    lv_obj_t *play;
    lv_obj_t *volume;
    lv_obj_t *shuffle;
    lv_obj_t *volume_slider; // 音量滑块
    bool is_volume_visible;  // 音量控制是否可见
} Music;

static Music *music_app;
static bool is_play = false;        // 记录当前播放状态
static int shuffle_index = 0;       // 记录当前播放的随机模式
static int current_music_index = 0; // 记录当前播放的音乐索引

const char *shuffle[3] = {USER_SYMBOL_PLAYLIST, USER_SYMBOL_SHUFFLE, USER_SYMBOL_REPEAT};

const char *Music_NAME[3] = {"Love Song", "Angel", "Lover"};
const char *Music_AUTHOR[3] = {"Khalil Fong", "David Tao", "Taylor Swift"};
static uint32_t volume_level = 50; // 默认音量值

static lv_style_t style_btn_label;
static lv_style_t style_btn;
static lv_style_t style_arc;

static void btn_return_cb(lv_event_t *e)
{
    back_to_home(lv_page->music_page);
}

// 添加回调函数声明
static void volume_hidden_ready_cb(lv_anim_t *a)
{
    lv_obj_add_flag((lv_obj_t *)a->var, LV_OBJ_FLAG_HIDDEN);
}

void btn_cb_hadler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
        if (obj == music_app->play)
        {
            is_play = !is_play;
            lv_obj_t *label = lv_obj_get_child(obj, 0);
            if (lv_obj_check_type(label, &lv_label_class)) // 修改这行
            {
                lv_label_set_text(label, is_play ? LV_SYMBOL_PAUSE : LV_SYMBOL_PLAY);
            }
        }
        else if (obj == music_app->shuffle)
        {
            shuffle_index = (shuffle_index + 1) % 3;
            lv_obj_t *label = lv_obj_get_child(obj, 0);
            if (lv_obj_check_type(label, &lv_label_class)) // 修改这行
            {
                lv_label_set_text(label, shuffle[shuffle_index]);
            }
        }
        else if (obj == music_app->btn_next)
        {
            current_music_index = (current_music_index + 1) % 3; // 循环切换到下一首
            lv_obj_t *label = lv_obj_get_child(obj, 0);
            if (lv_obj_check_type(label, &lv_label_class))
            {
                lv_label_set_text(music_app->author, Music_AUTHOR[current_music_index]);
                lv_label_set_text(music_app->title, Music_NAME[current_music_index]);
            }
        }
        else if (obj == music_app->btn_last)
        {
            current_music_index = (current_music_index - 1 + 3) % 3; // 循环切换到上一首
            lv_obj_t *label = lv_obj_get_child(obj, 0);
            if (lv_obj_check_type(label, &lv_label_class))
            {
                lv_label_set_text(music_app->author, Music_AUTHOR[current_music_index]);
                lv_label_set_text(music_app->title, Music_NAME[current_music_index]);
            }
        }
        else if (obj == music_app->volume)
        {
            music_app->is_volume_visible = !music_app->is_volume_visible;
            if (music_app->is_volume_visible)
            {
                lv_obj_set_x(music_app->volume_slider, 20);
                lv_obj_clear_flag(music_app->volume_slider, LV_OBJ_FLAG_HIDDEN);

                // 创建显示动画
                lv_anim_t a;
                lv_anim_init(&a);
                lv_anim_set_var(&a, music_app->volume_slider);
                lv_anim_set_values(&a, 350, 205);
                lv_anim_set_time(&a, 800);
                lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
                lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
                lv_anim_start(&a);

                lv_anim_t b;
                lv_anim_init(&b);
                lv_anim_set_var(&b, music_app->volume_slider);
                lv_anim_set_values(&b, 0, 200);
                lv_anim_set_time(&b, 800);
                lv_anim_set_path_cb(&b, lv_anim_path_ease_out);
                lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t)lv_obj_set_width);
                lv_anim_start(&b);
            }
            else
            {
                // 创建隐藏动画

                lv_anim_t b;
                lv_anim_init(&b);
                lv_anim_set_var(&b, music_app->volume_slider);
                lv_anim_set_values(&b, 200, 0);
                lv_anim_set_time(&b, 300);
                lv_anim_set_path_cb(&b, lv_anim_path_ease_out);
                lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t)lv_obj_set_width);
                lv_anim_start(&b);

                lv_anim_t a;
                lv_anim_init(&a);
                lv_anim_set_var(&a, music_app->volume_slider);
                lv_anim_set_values(&a, 220, 280);
                lv_anim_set_time(&a, 300);
                lv_anim_set_path_cb(&a, lv_anim_path_ease_in);
                lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
                lv_anim_set_ready_cb(&a, volume_hidden_ready_cb);
                lv_anim_start(&a);
            }
        }
    }
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
        music_app->volume = NULL;
        music_app->shuffle = NULL;
        music_app->title = NULL;
        music_app->author = NULL;
        music_app->music_page = NULL;
        music_app->group = NULL;
        music_app->btn_return = NULL;
        music_app->label_btn = NULL;
        music_app->btn_next = NULL;
        music_app->btn_last = NULL;
        music_app->arc = NULL;
        music_app->play = NULL;
        music_app->volume_slider = NULL;
        music_app->is_volume_visible = false;
    }

    lv_style_reset(&style_btn_label);
    lv_style_reset(&style_btn);
    lv_style_reset(&style_arc);
    lv_style_init(&style_btn_label);
    lv_style_set_text_font(&style_btn_label, &music_font_22_t);

    lv_style_init(&style_btn);
    lv_style_set_bg_color(&style_btn, lv_color_black());
    lv_style_set_border_width(&style_btn, 0);
    lv_style_set_shadow_width(&style_btn, 0);

    lv_style_init(&style_arc);

    music_app->music_page = create_page("Music"); // 创建主页面
    // music_app->btn_return = create_app_btn_return(music_app->music_page);
    // lv_obj_set_style_text_color(lv_obj_get_child(music_app->btn_return, 0), lv_color_white(), 0);
    lv_obj_set_style_bg_color(music_app->music_page, lv_color_black(), 0);
    lv_obj_remove_style(music_app->music_page, NULL, LV_PART_SCROLLBAR);

    // lv_obj_add_event_cb(music_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    music_app->title = lv_label_create(music_app->music_page);
    lv_label_set_text(music_app->title, "Love Song");
    lv_obj_set_style_text_font(music_app->title, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(music_app->title, lv_color_white(), 0);
    lv_obj_align(music_app->title, LV_ALIGN_TOP_MID, 0, 20);

    music_app->author = lv_label_create(music_app->music_page);
    lv_label_set_text(music_app->author, "xxchong");
    lv_obj_set_style_text_font(music_app->author, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(music_app->author, lv_color_white(), 0);
    lv_obj_align_to(music_app->author, music_app->title, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    music_app->btn_last = lv_btn_create(music_app->music_page);
    lv_obj_set_size(music_app->btn_last, 50, 50);
    lv_obj_align(music_app->btn_last, LV_ALIGN_LEFT_MID, 0, 5);
    lv_obj_add_style(music_app->btn_last, &style_btn, 0);
    music_app->label_btn = lv_label_create(music_app->btn_last);
    lv_label_set_text(music_app->label_btn, USER_SYMBOL_PREV);
    lv_obj_center(music_app->label_btn);
    lv_obj_add_style(music_app->label_btn, &style_btn_label, 0);

    music_app->btn_next = lv_btn_create(music_app->music_page);
    lv_obj_set_size(music_app->btn_next, 50, 50);
    lv_obj_align(music_app->btn_next, LV_ALIGN_RIGHT_MID, 0, 5);
    lv_obj_add_style(music_app->btn_next, &style_btn, 0);
    music_app->label_btn = lv_label_create(music_app->btn_next);
    lv_label_set_text(music_app->label_btn, USER_SYMBOL_NEXT);
    lv_obj_center(music_app->label_btn);
    lv_obj_add_style(music_app->label_btn, &style_btn_label, 0);

    music_app->arc = lv_arc_create(music_app->music_page);
    lv_obj_set_size(music_app->arc, 100, 100);
    lv_arc_set_angles(music_app->arc, 135, 270);  /* 设置前景弧角度 */
    lv_arc_set_bg_angles(music_app->arc, 0, 360); /* 设置背景弧角度 */

    lv_arc_set_mode(music_app->arc, LV_ARC_MODE_NORMAL); /* 设置模式 */
    lv_obj_align(music_app->arc, LV_ALIGN_CENTER, 0, 0);
    lv_arc_set_rotation(music_app->arc, 270);
    lv_obj_remove_style(music_app->arc, NULL, LV_PART_KNOB);
    lv_obj_set_style_arc_color(music_app->arc, lv_color_hex(0x7083a5), LV_PART_MAIN);
    lv_obj_set_style_arc_color(music_app->arc, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(music_app->arc, 12, LV_PART_INDICATOR); // 设置弧形宽度
    lv_obj_set_style_arc_width(music_app->arc, 12, LV_PART_MAIN);      // 设置弧形宽度

    music_app->play = lv_btn_create(music_app->arc);
    lv_obj_set_size(music_app->play, 50, 50);
    lv_obj_center(music_app->play);
    lv_obj_add_style(music_app->play, &style_btn, 0);
    music_app->label_btn = lv_label_create(music_app->play);
    lv_obj_set_style_text_font(music_app->label_btn, &lv_font_montserrat_22, 0);
    lv_label_set_text(music_app->label_btn, LV_SYMBOL_PLAY);
    lv_obj_center(music_app->label_btn);

    music_app->volume = lv_btn_create(music_app->music_page);
    lv_obj_set_size(music_app->volume, 30, 30);
    lv_obj_align(music_app->volume, LV_ALIGN_BOTTOM_LEFT, 50, -15);
    lv_obj_add_style(music_app->volume, &style_btn, 0);
    music_app->label_btn = lv_label_create(music_app->volume);
    lv_obj_set_style_text_font(music_app->label_btn, &music_font_22_t, 0);
    lv_label_set_text(music_app->label_btn, USER_SYMBOL_VOLUME);
    lv_obj_center(music_app->label_btn);

    music_app->shuffle = lv_btn_create(music_app->music_page);
    lv_obj_set_size(music_app->shuffle, 30, 30);
    lv_obj_align(music_app->shuffle, LV_ALIGN_BOTTOM_RIGHT, -50, -15);
    lv_obj_add_style(music_app->shuffle, &style_btn, 0);
    music_app->label_btn = lv_label_create(music_app->shuffle);
    lv_obj_set_style_text_font(music_app->label_btn, &music_font_22_t, 0);
    lv_label_set_text(music_app->label_btn, shuffle[0]);
    lv_obj_center(music_app->label_btn);

    music_app->volume_slider = lv_slider_create(music_app->music_page);
    lv_obj_set_size(music_app->volume_slider, 1, 12);
    lv_obj_set_x(music_app->volume_slider, 120);
    lv_slider_set_range(music_app->volume_slider, 0, 100);
    lv_slider_set_value(music_app->volume_slider, volume_level, LV_ANIM_OFF);
    lv_obj_add_flag(music_app->volume_slider, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_style(music_app->volume_slider, NULL, LV_PART_KNOB);
    // 修改滑块样式设置
    lv_obj_set_style_bg_opa(music_app->volume_slider, LV_OPA_50, LV_PART_MAIN);
    lv_obj_set_style_bg_color(music_app->volume_slider, lv_color_hex(0x7083a5), LV_PART_MAIN);

    lv_obj_set_style_bg_opa(music_app->volume_slider, LV_OPA_COVER, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(music_app->volume_slider, lv_color_white(), LV_PART_INDICATOR);

    music_app->is_volume_visible = false;

    lv_obj_add_event_cb(music_app->play, btn_cb_hadler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(music_app->shuffle, btn_cb_hadler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(music_app->btn_last, btn_cb_hadler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(music_app->btn_next, btn_cb_hadler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(music_app->volume, btn_cb_hadler, LV_EVENT_CLICKED, NULL);

    return music_app->music_page;
}
