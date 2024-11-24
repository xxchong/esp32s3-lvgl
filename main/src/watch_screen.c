
#include "sys.h"

static void watch_cont(lv_obj_t *parent);
static void delete_watch_list(lv_timer_t *timer);
static void watch_close_cb(lv_event_t *e);
static void watch_select_cb(lv_event_t *e);
static void watch_switch_event_cb(lv_event_t *e);
static void create_watch_1(lv_obj_t *parent, bool is_preview);
static void create_watch_2(lv_obj_t *parent, bool is_preview);
static void create_watch_3(lv_obj_t *parent, bool is_preview);
static void create_watch_4(lv_obj_t *parent, bool is_preview);
static void create_watch_5(lv_obj_t *parent, bool is_preview);
static lv_obj_t *g_watch_list = NULL; // 切换表盘的选择容器

static uint8_t gloabl_current_watch_id = 0;

// 函数指针类型
typedef void (*watch_create_fn)(lv_obj_t *, bool);

// 函数指针数组
static const watch_create_fn watch_creators[] = {
    create_watch_1,
    create_watch_2,
    create_watch_3,
    create_watch_4,
    create_watch_5};
typedef struct
{
    lv_obj_t *watch_screen_page;

} watch_screen_t;

watch_screen_t *watch_screen;

lv_timer_t *watch_screen_time_timer = NULL;

static void watch_screen_time_refresh(lv_timer_t *timer)
{
    switch (gloabl_current_watch_id)
    {
    case 0:
        watch_1_time_refresh();
        break;
    case 1:
        watch_2_time_refresh();
        break;
    case 2:
        watch_3_time_refresh();
        break;
    case 3:
        watch_4_time_refresh();
        break;
    case 4:
        watch_5_time_refresh();
        break;
    }
}

void del_watch_screen_time_timer(void)
{
    if (watch_screen_time_timer)
    {
        lv_timer_del(watch_screen_time_timer);
        watch_screen_time_timer = NULL;
    }
}

lv_obj_t *create_watch_screen(void)
{
    if (watch_screen == NULL)
    {
        watch_screen = (watch_screen_t *)malloc(sizeof(watch_screen_t));
        memset(watch_screen, 0, sizeof(watch_screen_t));
    }

    watch_screen->watch_screen_page = create_page("Watch");

    watch_cont(watch_screen->watch_screen_page);

    return watch_screen->watch_screen_page;
}

static void watch_switch_event_cb(lv_event_t *e)
{
    lv_obj_t *cont = lv_event_get_target(e);

    del_watch_screen_time_timer();
    // 如果列表已存在，直接返回
    if (g_watch_list != NULL)
    {
        return;
    }

    // 创建水平滚动容器 - 注意创建在屏幕层级
    g_watch_list = lv_obj_create(lv_scr_act());
    if (g_watch_list == NULL)
    {
        return; // 创建失败时安全返回
    }

    lv_obj_set_size(g_watch_list, 240, 280);
    lv_obj_center(g_watch_list);
    lv_obj_set_style_bg_color(g_watch_list, lv_color_hex(0xe4e4e4), 0);
    lv_obj_set_style_border_width(g_watch_list, 0, 0);
    lv_obj_set_style_radius(g_watch_list, 0, 0);
    lv_obj_move_foreground(g_watch_list);

    // 设置滚动属性
    lv_obj_set_scroll_dir(g_watch_list, LV_DIR_HOR);
    lv_obj_set_scroll_snap_x(g_watch_list, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(g_watch_list, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_column(g_watch_list, 20, 0);
    lv_obj_set_flex_flow(g_watch_list, LV_FLEX_FLOW_ROW);

    // 创建表盘选项
    for (int i = 0; i < 5; i++)
    {
        lv_obj_t *watch_option = lv_obj_create(g_watch_list);
        if (watch_option == NULL)
        {
            continue;
        }

        lv_obj_clear_flag(watch_option, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(watch_option, 200, 240);
        lv_obj_set_style_radius(watch_option, 20, 0);
        lv_obj_set_style_bg_color(watch_option, lv_color_hex(0x222222), 0);
        lv_obj_set_style_bg_opa(watch_option, LV_OPA_50, 0);
        lv_obj_set_style_border_width(watch_option, 2, 0);
        lv_obj_set_style_border_color(watch_option, lv_color_hex(0x444444), 0);

        if (watch_creators[i])
        {
            watch_creators[i](watch_option, true);
            lv_obj_add_event_cb(watch_option, watch_select_cb, LV_EVENT_CLICKED, (void *)(uintptr_t)i);
        }
    }

    // 保存原始容器引用
    g_watch_list->user_data = cont;

    // 添加关闭事件（点击外部区域关闭）
    lv_obj_t *scr = lv_scr_act();
    if (scr)
    {
        lv_obj_add_event_cb(scr, watch_close_cb, LV_EVENT_CLICKED, NULL);
    }
}

static void watch_close_cb(lv_event_t *e)
{
    if (g_watch_list == NULL)
        return;

    lv_obj_t *target = lv_event_get_target(e);
    if (target == lv_scr_act())
    {
        // 移除屏幕的点击事件
        lv_obj_remove_event_cb(target, watch_close_cb);

        // 安全删除表盘列表
        if (g_watch_list)
        {
            lv_obj_del(g_watch_list);
            g_watch_list = NULL;
        }
    }
}

static void watch_select_cb(lv_event_t *e)
{
    if (g_watch_list == NULL)
        return;

    // 保存需要的数据
    lv_obj_t *main_cont = g_watch_list->user_data;
    uintptr_t watch_id = (uintptr_t)lv_event_get_user_data(e);

    // 移除屏幕的点击事件
    lv_obj_t *scr = lv_scr_act();
    if (scr)
    {
        lv_obj_remove_event_cb(scr, watch_close_cb);
    }

    // 移除所有事件回调并删除列表
    if (g_watch_list)
    {
        lv_obj_remove_event_cb(g_watch_list, NULL);
        lv_obj_del(g_watch_list);
        g_watch_list = NULL;
    }

    if (main_cont == NULL)
        return;

    // 更新当前表盘ID
    gloabl_current_watch_id = watch_id;

    // 更新主表盘显示
    lv_obj_clean(main_cont);
    lv_obj_set_style_bg_color(main_cont, lv_color_hex(0xe4e4e4), 0);
    lv_obj_set_style_bg_opa(main_cont, LV_OPA_COVER, 0);

    // 创建新表盘
    if (watch_id < sizeof(watch_creators) / sizeof(watch_creators[0]) && watch_creators[watch_id])
    {
        watch_creators[watch_id](main_cont, false);
    }

    // 重新添加长按事件
    lv_obj_add_event_cb(main_cont, watch_switch_event_cb, LV_EVENT_LONG_PRESSED, NULL);

    watch_screen_time_timer = lv_timer_create(watch_screen_time_refresh, 1000, NULL);
}
// 添加删除函数
static void delete_watch_list(lv_timer_t *timer)
{
    if (g_watch_list)
    {
        lv_obj_del(g_watch_list);
        g_watch_list = NULL;
    }
}

static void watch_cont(lv_obj_t *parent)
{
    watch_creators[gloabl_current_watch_id](parent, false);
    // 添加长按事件
    lv_obj_add_event_cb(parent, watch_switch_event_cb, LV_EVENT_LONG_PRESSED, NULL);

    watch_screen_time_timer = lv_timer_create(watch_screen_time_refresh, 1000, NULL);
}

static void create_watch_1(lv_obj_t *parent, bool is_preview)
{
    lv_clock_watch_1(parent, is_preview);
}
static void create_watch_2(lv_obj_t *parent, bool is_preview)
{
    lv_clock_watch_2(parent, is_preview);
}

static void create_watch_3(lv_obj_t *parent, bool is_preview)
{
    lv_clock_watch_3(parent, is_preview);
}

static void create_watch_4(lv_obj_t *parent, bool is_preview)
{
    lv_clock_watch_4(parent, is_preview);
}
static void create_watch_5(lv_obj_t *parent, bool is_preview)
{
    lv_clock_watch_5(parent, is_preview);
}
