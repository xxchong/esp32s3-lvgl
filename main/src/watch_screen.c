#include "sys.h"


/*函数声明*/
static void watch_cont(lv_obj_t *parent);
static void watch_close_cb(lv_event_t *e);
static void watch_select_cb(lv_event_t *e);
static void watch_switch_event_cb(lv_event_t *e);
static bool create_watch_list(lv_obj_t *cont);
static bool create_watch_option(int index);
static void setup_watch_list_properties(lv_obj_t *list);
static void watch_screen_time_refresh(lv_timer_t *timer);

/*表盘创建函数声明*/
static void create_watch_1(lv_obj_t *parent, bool is_preview);
static void create_watch_2(lv_obj_t *parent, bool is_preview);
static void create_watch_3(lv_obj_t *parent, bool is_preview);
static void create_watch_4(lv_obj_t *parent, bool is_preview);
static void create_watch_5(lv_obj_t *parent, bool is_preview);
// 常量定义
#define MAX_WATCH_FACES 5   /*表盘数量*/
#define WATCH_OPTION_WIDTH 200 /*表盘宽度*/
#define WATCH_OPTION_HEIGHT 240 /*表盘高度*/
#define WATCH_OPTION_SPACING 20 /*表盘间距*/
#define WATCH_LIST_WIDTH 240 /*表盘列表宽度*/
#define WATCH_LIST_HEIGHT 280 /*表盘列表高度*/

/*函数指针*/
typedef void (*watch_create_fn)(lv_obj_t *, bool);
typedef void (*watch_refresh_fn)(void);

/*全局状态管理结构体*/
typedef struct {
    lv_obj_t *watch_screen_page;
    lv_obj_t *watch_list;
    lv_timer_t *time_refresh_timer;
} watch_screen_t;

uint8_t current_watch_id;

/*全局变量*/
static watch_screen_t *g_watch_screen = NULL;


/*表盘创建函数数组*/
static const watch_create_fn watch_creators[] = {
    create_watch_1, create_watch_2, create_watch_3, create_watch_4, create_watch_5
};

// 创建主屏幕
lv_obj_t *create_watch_screen(void)
{
    if (g_watch_screen != NULL)
    {
        free(g_watch_screen);
        g_watch_screen = NULL;
    }
    if (g_watch_screen == NULL) {
        g_watch_screen = (watch_screen_t *)calloc(1, sizeof(watch_screen_t));
        if (!g_watch_screen) return NULL;
    }

    g_watch_screen->watch_screen_page = create_page("Watch");
    if (!g_watch_screen->watch_screen_page) {
        free(g_watch_screen);
        return NULL;
    }

    watch_cont(g_watch_screen->watch_screen_page);
    return g_watch_screen->watch_screen_page;
}

// 删除时间刷新定时器
void del_watch_screen_time_timer(void)
{
    if (g_watch_screen && g_watch_screen->time_refresh_timer) {
        lv_timer_del(g_watch_screen->time_refresh_timer);
        g_watch_screen->time_refresh_timer = NULL;
    }
}

// 设置表盘��表属性
static void setup_watch_list_properties(lv_obj_t *list)
{
    lv_obj_set_size(list, WATCH_LIST_WIDTH, WATCH_LIST_HEIGHT);
    lv_obj_center(list);
    lv_obj_set_style_bg_color(list, lv_color_hex(0xe4e4e4), 0);
    lv_obj_set_style_border_width(list, 0, 0);
    lv_obj_set_style_radius(list, 0, 0);
    lv_obj_move_foreground(list);

    lv_obj_set_scroll_dir(list, LV_DIR_HOR);
    lv_obj_set_scroll_snap_x(list, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(list, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_column(list, WATCH_OPTION_SPACING, 0);
    lv_obj_set_flex_flow(list, LV_FLEX_FLOW_ROW);
}

// 创建单个表盘选项
static bool create_watch_option(int index)
{
    if (!g_watch_screen->watch_list) return false;

    lv_obj_t *watch_option = lv_obj_create(g_watch_screen->watch_list);
    if (!watch_option) return false;

    lv_obj_clear_flag(watch_option, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(watch_option, WATCH_OPTION_WIDTH, WATCH_OPTION_HEIGHT);
    lv_obj_set_style_radius(watch_option, 20, 0);
    lv_obj_set_style_bg_color(watch_option, lv_color_hex(0x222222), 0);
    lv_obj_set_style_bg_opa(watch_option, LV_OPA_50, 0);
    lv_obj_set_style_border_width(watch_option, 2, 0);
    lv_obj_set_style_border_color(watch_option, lv_color_hex(0x444444), 0);

    if (watch_creators[index]) {
        watch_creators[index](watch_option, true);
        lv_obj_add_event_cb(watch_option, watch_select_cb, LV_EVENT_CLICKED, (void *)(uintptr_t)index);
    }

    return true;
}

// 创建表盘列表
static bool create_watch_list(lv_obj_t *cont)
{
    // 删除时间刷新定时器
    if (g_watch_screen->time_refresh_timer) {
        lv_timer_del(g_watch_screen->time_refresh_timer);
        g_watch_screen->time_refresh_timer = NULL;
    }
    
    g_watch_screen->watch_list = lv_obj_create(lv_scr_act());
    if (!g_watch_screen->watch_list) return false;

    setup_watch_list_properties(g_watch_screen->watch_list);
    
    for (int i = 0; i < MAX_WATCH_FACES; i++) {
        if (!create_watch_option(i)) continue;
    }
    
    g_watch_screen->watch_list->user_data = cont;
    return true;
}

// 表盘切换事件回调
static void watch_switch_event_cb(lv_event_t *e)
{
    lv_obj_t *cont = lv_event_get_target(e);
    
    if (g_watch_screen->watch_list != NULL) return;
    
    if (!create_watch_list(cont)) return;
    
    lv_coord_t scroll_x = current_watch_id * (WATCH_OPTION_WIDTH + WATCH_OPTION_SPACING);
    lv_obj_scroll_to_x(g_watch_screen->watch_list, scroll_x, LV_ANIM_OFF);
    
    lv_obj_t *scr = lv_scr_act();
    if (scr) {
        lv_obj_add_event_cb(scr, watch_close_cb, LV_EVENT_CLICKED, NULL);
    }
}

// 关闭表盘列表回调
static void watch_close_cb(lv_event_t *e)
{
    if (!g_watch_screen->watch_list) return;

    lv_obj_t *target = lv_event_get_target(e);
    if (target == lv_scr_act()) {
        lv_obj_remove_event_cb(target, watch_close_cb);
        lv_obj_del(g_watch_screen->watch_list);
        g_watch_screen->watch_list = NULL;
    }
}

// 选择表���回调
static void watch_select_cb(lv_event_t *e)
{
    if (!g_watch_screen->watch_list) return;

    lv_obj_t *main_cont = g_watch_screen->watch_list->user_data;
    uintptr_t watch_id = (uintptr_t)lv_event_get_user_data(e);

    lv_obj_t *scr = lv_scr_act();
    if (scr) {
        lv_obj_remove_event_cb(scr, watch_close_cb);
    }

    if (g_watch_screen->watch_list) {
        lv_obj_del(g_watch_screen->watch_list);
        g_watch_screen->watch_list = NULL;
    }

    if (!main_cont) return;

   current_watch_id = watch_id;

    lv_obj_clean(main_cont);
    lv_obj_set_style_bg_color(main_cont, lv_color_hex(0xe4e4e4), 0);
    lv_obj_set_style_bg_opa(main_cont, LV_OPA_COVER, 0);
    lv_obj_add_event_cb(main_cont, watch_switch_event_cb, LV_EVENT_LONG_PRESSED, NULL);

    if (watch_id < MAX_WATCH_FACES && watch_creators[watch_id]) {
        watch_creators[watch_id](main_cont, false);
    }
    
    g_watch_screen->time_refresh_timer = lv_timer_create(watch_screen_time_refresh, 1000, NULL);
}

// 时间刷新回调
static void watch_screen_time_refresh(lv_timer_t *timer)
{
    static const watch_refresh_fn refresh_functions[] = {
        watch_1_time_refresh,
        watch_2_time_refresh,
        watch_3_time_refresh,
        watch_4_time_refresh,
        watch_5_time_refresh
    };
    
    if (current_watch_id < MAX_WATCH_FACES) {
        refresh_functions[current_watch_id]();
    }
}

// 创建主表盘容器
static void watch_cont(lv_obj_t *parent)
{
    watch_creators[current_watch_id](parent, false);
    lv_obj_add_event_cb(parent, watch_switch_event_cb, LV_EVENT_LONG_PRESSED, NULL);
    // 确保在创建新定时器前删除旧的定时器
    if (g_watch_screen->time_refresh_timer) {
        lv_timer_del(g_watch_screen->time_refresh_timer);
        g_watch_screen->time_refresh_timer = NULL;
    }
    g_watch_screen->time_refresh_timer = lv_timer_create(watch_screen_time_refresh, 1000, NULL);
    // 检查定时器是否创建成功
    if (!g_watch_screen->time_refresh_timer) {
        // 处理定时器创建失败的情况，例如通过日志记录或错误处理机制
    }
}


// 各个表盘的创建函数实现
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
    if(!is_preview)
    {
        send_anim_meter_event();
    }
}