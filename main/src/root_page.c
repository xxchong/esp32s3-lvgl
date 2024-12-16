#include "sys.h"

static void animate_in_x(lv_obj_t *obj, int delay, int anim_time, lv_anim_path_cb_t path_cb, lv_coord_t start, lv_coord_t end);
static void animate_in_y(lv_obj_t *obj, int delay, int anim_time, lv_anim_path_cb_t path_cb, lv_coord_t start, lv_coord_t end);
static void create_widgets_with_animation(lv_obj_t *parent);

static lv_obj_t *clock_widget2;
static lv_obj_t *wooden_fish_widget;
static lv_obj_t *weather_widget;
static lv_obj_t *clock_widget1;

root_page_t *root_page;

lv_timer_t *root_page_time_timer = NULL;

static void root_page_time_refresh(lv_timer_t *timer)
{
    if (root_page != NULL) {
        clock_widget_time_refresh();
    }
}
void del_root_page_time_timer(void)
{
    if (root_page_time_timer != NULL)
    {
        lv_timer_del(root_page_time_timer);
        root_page_time_timer = NULL;
    }
}

// 定义回调函数
static void screen_switch_event_cb(lv_event_t *e)
{
    animate_in_y(wooden_fish_widget, 0, 700, lv_anim_path_ease_out, 340, 220);
    animate_in_x(clock_widget1, 0, 700, lv_anim_path_ease_out, -100, 15);
    animate_in_x(weather_widget, 0, 700, lv_anim_path_ease_out, 240, 130);
    animate_in_y(clock_widget2, 0, 700, lv_anim_path_ease_out, -100, 10);
}

lv_obj_t *create_root(void)
{
    if (root_page != NULL)
    {
        free(root_page);
        root_page = NULL;
        del_root_page_time_timer();
    }

    root_page = (root_page_t *)calloc(1, sizeof(root_page_t));
    root_page->root_page = create_page("Root");
    create_widgets_with_animation(root_page->root_page);
    lv_obj_remove_style(root_page->root_page, NULL, LV_PART_SCROLLBAR);
    lv_obj_add_event_cb(root_page->root_page, screen_switch_event_cb, LV_EVENT_SCREEN_LOADED, NULL);
    lv_obj_clear_flag(root_page->root_page, LV_OBJ_FLAG_SCROLLABLE);

    if (root_page_time_timer == NULL)
    {
        root_page_time_timer = lv_timer_create(root_page_time_refresh, 1000, NULL);
    }

    return root_page->root_page;
}
// 创建动画
static void animate_in_y(lv_obj_t *obj, int delay, int anim_time, lv_anim_path_cb_t path_cb, lv_coord_t start, lv_coord_t end)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_time(&a, anim_time); // 动画持续时间
    lv_anim_set_delay(&a, delay);    // 动画延迟
    lv_anim_set_values(&a, start, end);
    lv_anim_set_path_cb(&a, path_cb);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_start(&a);
}

// 创建动画
static void animate_in_x(lv_obj_t *obj, int delay, int anim_time, lv_anim_path_cb_t path_cb, lv_coord_t start, lv_coord_t end)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_time(&a, anim_time); // 动画持续时间
    lv_anim_set_delay(&a, delay);    // 动画延迟
    lv_anim_set_values(&a, start, end);
    lv_anim_set_path_cb(&a, path_cb);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_start(&a);
}

static void create_widgets_with_animation(lv_obj_t *parent)
{
    clock_widget2 = create_clock_widget2(parent);
    clock_widget1 = create_clock_widget1(parent);
    weather_widget = create_weather_widget_app(parent);
    wooden_fish_widget = create_wooden_fish_widget(parent);
    // 初始位置设置
    lv_obj_set_y(clock_widget2, -100); // 从顶部移入
    lv_obj_set_y(clock_widget1, 110);
    lv_obj_set_x(clock_widget1, -100); // 从左侧移入
    lv_obj_set_y(weather_widget, 110);
    lv_obj_set_x(weather_widget, lv_obj_get_width(parent) + 100); // 从右侧移入
    // 初始位置设置
    lv_obj_set_x(wooden_fish_widget, lv_obj_get_width(parent) / 2 - 60);
    lv_obj_set_y(wooden_fish_widget, lv_obj_get_height(parent) + 100); // 设置初始Y位置在父对象底部之下
}
