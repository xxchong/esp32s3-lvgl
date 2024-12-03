#include "sys.h"

/*函数声明*/
static lv_obj_t *create_tabview(lv_obj_t *parent, lv_dir_t tab_pos, lv_coord_t tab_size, bool scroll_en, lv_color_t bg_color, lv_coord_t width, lv_coord_t height);
static void tab_btns_style(lv_obj_t *tab_btns);
static lv_obj_t *tabview_add_tab(lv_obj_t *tabview, const char *name);
static void create_Alarm(lv_obj_t *tab);
static void create_Stopwatch(lv_obj_t *tab);
static void create_Timer(lv_obj_t *tab);

typedef struct
{
    lv_obj_t *clock_page;
    lv_obj_t *clock_tabview;
    lv_obj_t *tab_Alarm;
    lv_obj_t *tab_Stopwatch;
    lv_obj_t *tab_timer;
} Clock_app_t;

// 添加新的结构体用于保存时间选择器控件
typedef struct
{
    lv_obj_t *popup;
    lv_obj_t *hour_roller;
    lv_obj_t *minute_roller;
} time_picker_t;


static time_picker_t *picker;

#define minute_options "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n" \
                       "10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n" \
                       "20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n" \
                       "30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n" \
                       "40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n" \
                       "50\n51\n52\n53\n54\n55\n56\n57\n58\n59"

#define hour_options "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n" \
                     "10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n" \
                     "20\n21\n22\n23"

static Clock_app_t *clock_app;
/*创建tabview*/
static lv_obj_t *create_tabview(lv_obj_t *parent, lv_dir_t tab_pos, lv_coord_t tab_size, bool scroll_en, lv_color_t bg_color, lv_coord_t width, lv_coord_t height)
{
    lv_obj_t *tabview = lv_tabview_create(parent, tab_pos, tab_size);
    if (!scroll_en) // 禁用滑动切换功能
    {
        lv_obj_set_scroll_dir(lv_tabview_get_content(tabview), LV_DIR_NONE);
    }
    lv_obj_set_style_bg_color(tabview, bg_color, 0);
    lv_obj_set_size(tabview, width, height);
    lv_obj_set_style_pad_all(tabview, 0, 0);
    lv_obj_set_style_outline_width(tabview, 0, 0);
    return tabview;
}
/*tabview按钮样式*/
static void tab_btns_style(lv_obj_t *tab_btns)
{
    lv_obj_set_style_border_opa(tab_btns, LV_OPA_0, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(tab_btns, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(tab_btns, LV_OPA_0, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(tab_btns, 0, 0);
    lv_group_t *g = lv_group_create(); // 防止默认选中 ，实际无作用
    lv_group_add_obj(g, tab_btns);
}
/*添加tab*/
static lv_obj_t *tabview_add_tab(lv_obj_t *tabview, const char *name)
{
    return lv_tabview_add_tab(tabview, name);
}

/**********************************************************闹钟*********************************************************************/
/***********************************************************************************************************************************/

// 确认按钮回调函数
static void time_picker_confirm_event_cb(lv_event_t *e)
{
    char hour_str[3], minute_str[3], buf[32];
    lv_roller_get_selected_str(picker->hour_roller, hour_str, sizeof(hour_str));
    lv_roller_get_selected_str(picker->minute_roller, minute_str, sizeof(minute_str));
    printf("hour:%s,minute:%s\n", hour_str, minute_str);
    // 关闭弹窗
    lv_obj_del(picker->popup);
    if (picker != NULL)
    {
        free(picker);
        picker = NULL;
    }
}

// 取消按钮回调函数
static void time_picker_cancel_event_cb(lv_event_t *e)
{
    lv_obj_del(picker->popup);
    if (picker != NULL)
    {
        free(picker);
        picker = NULL;
    }
}

static lv_obj_t *create_alarm_roller(lv_obj_t *parent, lv_coord_t width, lv_coord_t height,lv_color_t bg_color)
{

    lv_obj_t *roller = lv_roller_create(parent);
    lv_obj_set_size(roller, width, height); // 设置固定宽度和高度

    lv_obj_set_style_text_align(roller, LV_TEXT_ALIGN_CENTER, 0); // 文本居中对齐
    lv_obj_set_style_bg_color(roller, bg_color, 0);
    lv_obj_set_style_text_color(roller, lv_color_hex(0x666666), 0); // 未选中项的颜色
    lv_obj_set_style_border_width(roller, 0, 0);
    lv_obj_set_style_bg_opa(roller, 0, LV_PART_SELECTED);
    lv_obj_set_style_text_color(roller, lv_color_white(), LV_PART_SELECTED);
    lv_obj_set_style_text_font(roller, &lv_font_montserrat_24, LV_PART_SELECTED);

    return roller;
}

static lv_obj_t *create_alarm_btn(lv_obj_t *parent, lv_coord_t width, lv_coord_t height, lv_color_t color, const char *text)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, width, height);
    lv_obj_set_style_bg_color(btn, color, 0);
    lv_obj_set_style_shadow_width(btn, 0, 0);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_center(label);
    lv_obj_add_event_cb(btn, time_picker_confirm_event_cb, LV_EVENT_CLICKED, NULL);
    return btn;
}

static void create_time_picker(void)
{
    if (picker != NULL)
    {
        free(picker);
        picker = NULL;
    }
    else
    {
        picker = (time_picker_t *)calloc(1, sizeof(time_picker_t));
    }

    // 创建弹窗
    picker->popup = lv_obj_create(clock_app->clock_page);
    lv_obj_set_size(picker->popup, 220, 260);
    lv_obj_center(picker->popup);
    lv_obj_set_style_bg_color(picker->popup, lv_color_hex(0x2c2c2e), 0);
    lv_obj_set_style_border_width(picker->popup, 0, 0);
    lv_obj_set_style_radius(picker->popup, 10, 0);

    // 创建"时"标签
    lv_obj_t *hour_label = lv_label_create(picker->popup);
    lv_label_set_text(hour_label, "Hour");
    lv_obj_set_style_text_color(hour_label, lv_color_white(), 0);

    // 创建"分"标签
    lv_obj_t *minute_label = lv_label_create(picker->popup);
    lv_label_set_text(minute_label, "Minute");
    lv_obj_set_style_text_color(minute_label, lv_color_white(), 0);

    // 创建小时选择器
    picker->hour_roller = create_alarm_roller(picker->popup, 80, 150,lv_color_hex(0x2c2c2e));
    lv_roller_set_options(picker->hour_roller, hour_options, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(picker->hour_roller, 5);
    lv_obj_align(picker->hour_roller, LV_ALIGN_LEFT_MID, 10, 0); // 调整位置

    // 创建分钟选择器
    picker->minute_roller = create_alarm_roller(picker->popup, 80, 150,lv_color_hex(0x2c2c2e));
    lv_roller_set_options(picker->minute_roller, minute_options, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(picker->minute_roller, 5);
    lv_obj_align(picker->minute_roller, LV_ALIGN_RIGHT_MID, -10, 0); // 调整位置

    lv_obj_align_to(minute_label, picker->minute_roller, LV_ALIGN_OUT_TOP_MID, 0, -10); // 调整位置
    lv_obj_align_to(hour_label, picker->hour_roller, LV_ALIGN_OUT_TOP_MID, 0, -10);     // 调整位置

    lv_obj_t *btn_confirm = create_alarm_btn(picker->popup, 50, 30, lv_color_hex(0x228df2), "enter");
    lv_obj_add_event_cb(btn_confirm, time_picker_confirm_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *btn_cancel = create_alarm_btn(picker->popup, 50, 30, lv_color_hex(0x228df2), "cancel");
    lv_obj_add_event_cb(btn_cancel, time_picker_cancel_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_align_to(btn_confirm, picker->minute_roller, LV_ALIGN_OUT_BOTTOM_MID, 0, 5); // 调整位置
    lv_obj_align_to(btn_cancel, picker->hour_roller, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);    // 调整位置
}
// 修改添加按钮的回调函数
static void alarm_add_event_cb(lv_event_t *e)
{
    create_time_picker();
}
static void create_Alarm(lv_obj_t *tab)
{
    // 创建添加按钮
    lv_obj_t *btn_add = lv_btn_create(tab);
    lv_obj_set_size(btn_add, 30, 30);
    lv_obj_align(btn_add, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_radius(btn_add, 25, 0);
    lv_obj_set_style_bg_color(btn_add, lv_color_hex(0x2c2c2e), 0);
    lv_obj_set_style_outline_width(btn_add, 0, 0);
    lv_obj_set_style_shadow_width(btn_add, 0, 0);
    lv_obj_set_style_border_width(btn_add, 0, 0);
    // 添加按钮标签
    lv_obj_t *label_add = lv_label_create(btn_add);
    lv_label_set_text(label_add, "+");
    lv_obj_center(label_add);
    lv_obj_set_style_text_color(label_add, lv_color_hex(0x3d79f9), 0);
    lv_obj_set_style_text_font(label_add, &lv_font_montserrat_24, 0);
    // 添加按钮点击事件
    lv_obj_add_event_cb(btn_add, alarm_add_event_cb, LV_EVENT_CLICKED, NULL);
}
/***********************************************************************************************************************************/
/***********************************************************************************************************************************/

/*************************************************************计时器****************************************************************/
/***********************************************************************************************************************************/

// 添加秒表相关的结构体
typedef struct
{
    lv_obj_t *time_label;  // 显示时间的标签
    lv_obj_t *btn_start;   // 开始/暂停按钮
    lv_obj_t *btn_lap;     // 计圈/清除按钮
    lv_obj_t *lap_list;    // 计圈记录列表
    uint32_t start_time;   // 开始时间
    uint32_t elapsed_time; // 经过的时间
    bool running;          // 运行状态
} stopwatch_t;
lv_timer_t *stopwatch_timer;

static stopwatch_t *stopwatch = NULL;



void stop_stopwatch_timer(void)
{
    if (stopwatch_timer != NULL)
    {
        lv_timer_del(stopwatch_timer);
        stopwatch_timer = NULL;
    }
}


// 格式化时间显示
static void format_time(uint32_t ms, char *buf)
{
    uint32_t ss = ms / 1000;
    uint32_t mm = ss / 60;
    uint32_t hh = mm / 60;
    ms %= 1000;
    ss %= 60;
    mm %= 60;
    sprintf(buf, "%02lu:%02lu:%02lu.%03lu", hh, mm, ss, ms);
}

// 定时器回调函数
static void stopwatch_timer_cb(lv_timer_t *timer)
{
    stopwatch_t *sw = (stopwatch_t *)timer->user_data;
    if (sw->running)
    {
        sw->elapsed_time = lv_tick_get() - sw->start_time;
        char buf[16];
        format_time(sw->elapsed_time, buf);
        lv_label_set_text(sw->time_label, buf);
    }
}

// 开始/暂停按钮回调
static void btn_start_event_cb(lv_event_t *e)
{
    stopwatch_t *sw = stopwatch;
    if (!sw->running)
    {
        // 开始计时
        sw->start_time = lv_tick_get() - sw->elapsed_time;
        sw->running = true;
        lv_obj_set_style_bg_color(sw->btn_start, lv_color_hex(0xff4757), 0);
        lv_obj_t *label = lv_obj_get_child(sw->btn_start, 0);
        lv_label_set_text(label, "pause");

        // 显示计圈按钮
        lv_obj_t *lap_label = lv_obj_get_child(sw->btn_lap, 0);
        lv_label_set_text(lap_label, "lap");
    }
    else
    {
        // 暂停计时
        sw->running = false;
        lv_obj_set_style_bg_color(sw->btn_start, lv_color_hex(0x2ed573), 0);
        lv_obj_t *label = lv_obj_get_child(sw->btn_start, 0);
        lv_label_set_text(label, "continue");

        // 显示清除按钮
        lv_obj_t *lap_label = lv_obj_get_child(sw->btn_lap, 0);
        lv_label_set_text(lap_label, "clear");
    }
}

// 计圈/清除按钮回调
static void btn_lap_event_cb(lv_event_t *e)
{
    stopwatch_t *sw = stopwatch;
    if (sw->running)
    {
        // 添加计圈记录
        char buf[32];
        format_time(sw->elapsed_time, buf);
        char lap_text[64];
        sprintf(lap_text, "lap %d    %s", (int)lv_obj_get_child_cnt(sw->lap_list) + 1, buf);
        lv_obj_t *lap_label = lv_label_create(sw->lap_list);
        lv_obj_set_style_text_color(lap_label, lv_color_white(), 0);
        lv_label_set_text(lap_label, lap_text);
        // 滚动到新添加的记录
        lv_obj_scroll_to_y(sw->lap_list, LV_COORD_MAX, LV_ANIM_ON);
    }
    else
    {
        lv_obj_set_style_bg_color(sw->btn_start, lv_color_hex(0x2ed573), 0);
        lv_obj_t *label = lv_obj_get_child(sw->btn_start, 0);
        lv_label_set_text(label, "start");
        // 清除所有记录
        sw->elapsed_time = 0;
        lv_label_set_text(sw->time_label, "00:00:00.000");
        lv_obj_clean(sw->lap_list);
    }
}

static void create_Stopwatch(lv_obj_t *tab)
{
    stop_stopwatch_timer(); // 先停止定时器
    if (stopwatch == NULL)
    {
        stopwatch = (stopwatch_t *)calloc(1, sizeof(stopwatch_t));
    }
    else
    {
        free(stopwatch);  // 这里释放后立即将指针设为 NULL
        stopwatch = NULL;
        stopwatch = (stopwatch_t *)calloc(1, sizeof(stopwatch_t)); // 需要重新分配
    }

    // 创建时间显示标签
    stopwatch->time_label = lv_label_create(tab);
    lv_obj_set_style_text_color(stopwatch->time_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(stopwatch->time_label, &Clock_font_24_t, 0);
    lv_label_set_text(stopwatch->time_label, "00:00:00.000");
    lv_obj_set_width(stopwatch->time_label, 240);
    lv_obj_set_style_text_align(stopwatch->time_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(stopwatch->time_label, LV_ALIGN_TOP_MID, 0, 20); // 修改为居中对齐并调整垂直位置

    // 创建开始按钮
    stopwatch->btn_start = lv_btn_create(tab);
    lv_obj_set_size(stopwatch->btn_start, 80, 40);
    lv_obj_align(stopwatch->btn_start, LV_ALIGN_BOTTOM_LEFT, 20, 10);
    lv_obj_set_style_bg_color(stopwatch->btn_start, lv_color_hex(0x2ed573), 0);
    lv_obj_t *start_label = lv_label_create(stopwatch->btn_start);
    lv_label_set_text(start_label, "start");
    lv_obj_center(start_label);
    lv_obj_add_event_cb(stopwatch->btn_start, btn_start_event_cb, LV_EVENT_CLICKED, NULL);

    // 创建计圈按钮
    stopwatch->btn_lap = lv_btn_create(tab);
    lv_obj_set_size(stopwatch->btn_lap, 80, 40);
    lv_obj_align(stopwatch->btn_lap, LV_ALIGN_BOTTOM_RIGHT, -20, 10);
    lv_obj_set_style_bg_color(stopwatch->btn_lap, lv_color_hex(0x5352ed), 0);
    lv_obj_t *lap_label = lv_label_create(stopwatch->btn_lap);
    lv_label_set_text(lap_label, "lap");
    lv_obj_center(lap_label);
    lv_obj_add_event_cb(stopwatch->btn_lap, btn_lap_event_cb, LV_EVENT_CLICKED, NULL);

    // 创建计圈记录列表
    stopwatch->lap_list = lv_obj_create(tab);
    lv_obj_set_size(stopwatch->lap_list, 230, 145);
    lv_obj_align_to(stopwatch->lap_list, stopwatch->time_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_set_style_bg_color(stopwatch->lap_list, lv_color_black(), 0);
    lv_obj_set_style_border_width(stopwatch->lap_list, 0, 0);
    lv_obj_set_style_pad_all(stopwatch->lap_list, 10, 0);
    lv_obj_set_flex_flow(stopwatch->lap_list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(stopwatch->lap_list, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    // 创建定时器
    stopwatch_timer = lv_timer_create(stopwatch_timer_cb, 10, stopwatch);
    stopwatch->running = false;
    stopwatch->elapsed_time = 0;
}
/***********************************************************************************************************************************/
/***********************************************************************************************************************************/


/*************************************************************计时器****************************************************************/
/***********************************************************************************************************************************/

// 添加新的结构体用于保存时间选择器控件
// 在timer_picker_t结构体中添加新的成员
typedef struct
{
    lv_obj_t *hour_roller;
    lv_obj_t *minute_roller;
    lv_obj_t *second_roller;
    lv_obj_t *btn_start;
    // 新增成员
    lv_obj_t *arc;
    lv_obj_t *time_label;
    lv_obj_t *btn_pause;
    lv_obj_t *btn_stop;
    uint32_t total_time;    // 总时间(ms)
    uint32_t remaining_time; // 剩余时间(ms)
    bool is_running;        // 运行状态
} timer_picker_t;

static timer_picker_t *timer_picker;
static lv_timer_t *countdown_timer = NULL;

// 格式化时间显示函数
static void format_countdown_time(uint32_t ms, char *buf)
{
    uint32_t ss = ms / 1000;
    uint32_t mm = ss / 60;
    uint32_t hh = mm / 60;
    ss %= 60;
    mm %= 60;
    sprintf(buf, "%02lu:%02lu:%02lu", hh, mm, ss);
}
// 修改定时器回调函数
static void countdown_timer_cb(lv_timer_t *timer)
{
    timer_picker_t *t = (timer_picker_t *)timer->user_data;
    if (t->is_running && t->remaining_time > 0)
    {
        // 每次减少1000ms (1秒)
        t->remaining_time -= 1000;
        
        if (t->remaining_time <= 0) {
            // 计时结束
            t->remaining_time = 0;
            t->is_running = false;
            lv_arc_set_value(t->arc, 0);
            lv_obj_set_style_text_font(t->time_label, &lv_font_montserrat_30, 0);
            lv_obj_set_style_text_color(t->time_label, lv_color_hex(0x61ff61), 0);
            lv_label_set_text(t->time_label, LV_SYMBOL_OK);
            
            if (countdown_timer) {
                lv_timer_del(countdown_timer);
                countdown_timer = NULL;
            }
        } else {
            // 继续计时
            uint32_t percentage = (t->remaining_time * 100) / t->total_time;
            lv_arc_set_value(t->arc, percentage);
            
            // 更新时间标签
            char buf[16];
            format_countdown_time(t->remaining_time, buf);
            lv_label_set_text(t->time_label, buf);
        }
    }
}


// 暂停按钮回调
static void timer_btn_pause_event_cb(lv_event_t *e)
{
    timer_picker_t *t = timer_picker;
    if (t->is_running)
    {
        // 暂停
        t->is_running = false;
        lv_obj_t *label = lv_obj_get_child(t->btn_pause, 0);
        lv_label_set_text(label, LV_SYMBOL_PLAY);
    }
    else
    {
        // 继续
        t->is_running = true;
        lv_obj_t *label = lv_obj_get_child(t->btn_pause, 0);
        lv_label_set_text(label, LV_SYMBOL_PAUSE);
    }
}
// 停止按钮回调
static void timer_btn_stop_event_cb(lv_event_t *e)
{
    timer_picker_t *t = timer_picker;
    t->is_running = false;
    
    // 删除定时器
    if (countdown_timer)
    {
        lv_timer_del(countdown_timer);
        countdown_timer = NULL;
    }
    
    // 显示选择器界面
    lv_obj_clear_flag(t->hour_roller, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(t->minute_roller, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(t->second_roller, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(t->btn_start, LV_OBJ_FLAG_HIDDEN);
    
    // 隐藏倒计时界面
    lv_obj_add_flag(t->arc, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(t->time_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(t->btn_pause, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(t->btn_stop, LV_OBJ_FLAG_HIDDEN);
}
// 修改开始按钮回调函数
static void timer_btn_start_event_cb(lv_event_t *e)
{
    timer_picker_t *t = timer_picker;
    
    // 获取选择的时间
    char h_str[3], m_str[3], s_str[3];
    lv_roller_get_selected_str(t->hour_roller, h_str, sizeof(h_str));
    lv_roller_get_selected_str(t->minute_roller, m_str, sizeof(m_str));
    lv_roller_get_selected_str(t->second_roller, s_str, sizeof(s_str));
    lv_obj_set_style_text_font(t->time_label, &Clock_font_24_t, 0);
    lv_obj_set_style_text_color(t->time_label, lv_color_white(), 0);


    // 计算总时间(ms)
    t->total_time = (atoi(h_str) * 3600 + atoi(m_str) * 60 + atoi(s_str)) * 1000;
    t->remaining_time = t->total_time;
    
    if (t->total_time > 0) // 如果总时间大于0
    {
       // 修改：将范围设置为0-100，用于百分比显示
        lv_arc_set_range(timer_picker->arc, 0, 100);
        // 初始值设为100%
        lv_arc_set_value(t->arc, 100);
        // 隐藏选择器界面
        lv_obj_add_flag(t->hour_roller, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(t->minute_roller, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(t->second_roller, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(t->btn_start, LV_OBJ_FLAG_HIDDEN);
        
        // 显示倒计时界面
        lv_obj_clear_flag(t->arc, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(t->time_label, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(t->btn_pause, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(t->btn_stop, LV_OBJ_FLAG_HIDDEN);
        
      
        // 启动定时器 (1000ms = 1秒)
        t->is_running = true;
        if (countdown_timer == NULL)
        {
            countdown_timer = lv_timer_create(countdown_timer_cb, 1000, t);
        }
    }
}

static lv_obj_t* create_timer_btn(lv_obj_t *parent,lv_coord_t width,lv_coord_t height,lv_color_t bg_color,const char *text,bool is_circle,lv_coord_t radius)
{

    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, width, height);
    if(is_circle)
    {
        lv_obj_set_style_radius(btn, LV_RADIUS_CIRCLE, 0);
    }else
    {
        lv_obj_set_style_radius(btn, radius, 0);
    }
    lv_obj_set_style_bg_color(btn, bg_color, 0);
    lv_obj_set_style_shadow_width(btn, 0, 0);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_center(label);
    
    return btn;
}

static void create_Timer(lv_obj_t *tab)
{
     if (timer_picker != NULL)
    {
        free(timer_picker);
        timer_picker = NULL;
    }
    if(timer_picker == NULL)
    {
        timer_picker = (timer_picker_t *)calloc(1, sizeof(timer_picker_t));
    }
    // 创建小时选择器
    timer_picker->hour_roller = create_alarm_roller(tab, 80, 150,lv_color_black()); //使用create_alarm_roller函数创建选择器 复用
    lv_roller_set_options(timer_picker->hour_roller, hour_options, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(timer_picker->hour_roller, 5);
    lv_obj_align(timer_picker->hour_roller, LV_ALIGN_LEFT_MID, 2, -20); // 调整位置

    // 创建分钟选择器
    timer_picker->minute_roller = create_alarm_roller(tab, 80, 150,lv_color_black());
    lv_roller_set_options(timer_picker->minute_roller, minute_options, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(timer_picker->minute_roller, 5);
    lv_obj_align(timer_picker->minute_roller, LV_ALIGN_CENTER, 0, -20); // 调整位置

    timer_picker->second_roller = create_alarm_roller(tab, 80, 150,lv_color_black());
    lv_roller_set_options(timer_picker->second_roller, minute_options, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(timer_picker->second_roller, 5);
    lv_obj_align(timer_picker->second_roller, LV_ALIGN_RIGHT_MID, -2, -20); // 调整位置

    timer_picker->btn_start = create_timer_btn(tab, 60, 40,lv_color_hex(0x2c2c2e),LV_SYMBOL_PLAY,false,10);
    lv_obj_align(timer_picker->btn_start, LV_ALIGN_BOTTOM_MID, 0, 10); // 调整位置
    lv_obj_add_event_cb(timer_picker->btn_start, timer_btn_start_event_cb, LV_EVENT_CLICKED, NULL);

    // 创建圆弧
    timer_picker->arc = lv_arc_create(tab);
    lv_obj_set_size(timer_picker->arc, 180, 180);
    lv_obj_center(timer_picker->arc);
    lv_arc_set_rotation(timer_picker->arc, 270);
    lv_arc_set_bg_angles(timer_picker->arc, 0, 360);
    lv_obj_clear_flag(timer_picker->arc, LV_OBJ_FLAG_CLICKABLE);    // 禁用点击
    lv_obj_clear_flag(timer_picker->arc, LV_OBJ_FLAG_GESTURE_BUBBLE); // 禁用手势冒泡

    lv_obj_set_style_arc_color(timer_picker->arc, lv_color_hex(0x1856c3), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(timer_picker->arc, 10, LV_PART_MAIN);        // 设置背景圆弧宽度
    lv_obj_set_style_arc_width(timer_picker->arc, 10, LV_PART_INDICATOR);   // 设置前景圆弧宽度
    lv_obj_remove_style(timer_picker->arc, NULL, LV_PART_KNOB);
    lv_obj_add_flag(timer_picker->arc, LV_OBJ_FLAG_HIDDEN);
    
    // 创建时间标签
    timer_picker->time_label = lv_label_create(tab);
    lv_obj_set_style_text_font(timer_picker->time_label, &Clock_font_24_t, 0);
    lv_obj_set_style_text_color(timer_picker->time_label, lv_color_white(), 0);
    lv_label_set_text(timer_picker->time_label, "00:00:00");
    lv_obj_center(timer_picker->time_label);
    lv_obj_add_flag(timer_picker->time_label, LV_OBJ_FLAG_HIDDEN);
    
    // 创建暂停按钮
    timer_picker->btn_pause = create_timer_btn(tab, 40, 40,lv_color_hex(0x2c2c2e),LV_SYMBOL_PAUSE,true,0);
    lv_obj_add_event_cb(timer_picker->btn_pause, timer_btn_pause_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_flag(timer_picker->btn_pause, LV_OBJ_FLAG_HIDDEN);
    
    // 创建停止按钮
    timer_picker->btn_stop = create_timer_btn(tab, 40, 40,lv_color_hex(0x2c2c2e),LV_SYMBOL_STOP,true,0);
    lv_obj_add_event_cb(timer_picker->btn_stop, timer_btn_stop_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_flag(timer_picker->btn_stop, LV_OBJ_FLAG_HIDDEN);

    lv_obj_align(timer_picker->btn_pause, LV_ALIGN_BOTTOM_LEFT, 20, 14);
    lv_obj_align(timer_picker->btn_stop, LV_ALIGN_BOTTOM_RIGHT, -20, 14);


}

/***********************************************************************************************************************************/
/***********************************************************************************************************************************/

/*创建时钟app页面*/
lv_obj_t *create_clock_app(void)
{
    if (clock_app != NULL)
    {
        free(clock_app);
        clock_app = NULL;
    }
    if (clock_app == NULL)
    {
        clock_app = (Clock_app_t *)calloc(1, sizeof(Clock_app_t));
    }

    clock_app->clock_page = create_page("Clock"); // 创建主页面

    clock_app->clock_tabview = create_tabview(clock_app->clock_page, LV_DIR_BOTTOM, 30, false, lv_color_black(), 240, 280);
    lv_obj_t *tab_btns = lv_tabview_get_tab_btns(clock_app->clock_tabview);
    tab_btns_style(tab_btns);

    clock_app->tab_Alarm = tabview_add_tab(clock_app->clock_tabview, "Alarm");
    clock_app->tab_Stopwatch = tabview_add_tab(clock_app->clock_tabview, "Stopwatch");
    clock_app->tab_timer = tabview_add_tab(clock_app->clock_tabview, "Timer");

    lv_obj_remove_style(clock_app->clock_tabview, NULL, LV_PART_SCROLLBAR);
    lv_obj_remove_style(clock_app->tab_Alarm, NULL, LV_PART_SCROLLBAR);
    lv_obj_remove_style(clock_app->tab_Stopwatch, NULL, LV_PART_SCROLLBAR);
    lv_obj_remove_style(clock_app->tab_timer, NULL, LV_PART_SCROLLBAR);

       // 添加这一行来禁用 tab_Stopwatch 的滚动
    lv_obj_set_scroll_dir(clock_app->tab_Stopwatch, LV_DIR_NONE);


    lv_obj_set_scroll_dir(clock_app->tab_timer, LV_DIR_NONE);

    create_Alarm(clock_app->tab_Alarm);
    create_Stopwatch(clock_app->tab_Stopwatch);
    create_Timer(clock_app->tab_timer);
    return clock_app->clock_page;
}
