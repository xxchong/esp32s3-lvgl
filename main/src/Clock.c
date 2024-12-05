#include "sys.h"

/*函数声明*/
static lv_obj_t *create_tabview(lv_obj_t *parent, lv_dir_t tab_pos, lv_coord_t tab_size, bool scroll_en, lv_color_t bg_color, lv_coord_t width, lv_coord_t height);
static void tab_btns_style(lv_obj_t *tab_btns);
static lv_obj_t *tabview_add_tab(lv_obj_t *tabview, const char *name);
static void create_Alarm(lv_obj_t *tab);
static void create_Stopwatch(lv_obj_t *tab);
static void create_Timer(lv_obj_t *tab);
static void alarm_item_event_cb(lv_event_t *e);


static Clock_app_t *clock_app;


/**********************************************************闹钟*********************************************************************/
/***********************************************************************************************************************************/

static time_picker_t *picker;

alarm_item_t alarm_items[10]; /*假设当前最大10个闹钟*/

// 在全局变量区域添加计数器
static uint8_t alarm_count = 0;  // 跟踪当前闹钟数量


// 添加开关状态改变的回调函数
static void switch_event_cb(lv_event_t *e)
{
    lv_obj_t *sw = lv_event_get_target(e);
    lv_obj_t *cont = lv_obj_get_parent(sw);
    lv_obj_t *alarm_list = lv_obj_get_parent(cont);
    
    // 获取当前闹钟项的索引
    uint32_t index = 0;
    lv_obj_t *child = NULL;
    child = lv_obj_get_child(alarm_list, 0);
    while(child != cont) {
        index++;
        child = lv_obj_get_child(alarm_list, index);
    }
    
    // 更新开关状态
    if (index < alarm_count) {
        alarm_items[index].enabled = lv_obj_has_state(sw, LV_STATE_CHECKED);
    }
}

// 修改删除确认对话框回调函数
static void delete_confirm_event_cb(lv_event_t *e)
{
    lv_obj_t *msgbox = lv_event_get_current_target(e);  
    lv_obj_t *cont = lv_obj_get_user_data(msgbox);      // 获取要删除的闹钟项容器
    
    if (lv_msgbox_get_active_btn(msgbox) == 1) {        // 获取按钮索引
        // 获取当前闹钟项的索引
        lv_obj_t *alarm_list = lv_obj_get_parent(cont);
        uint32_t index = 0;
        lv_obj_t *child = NULL;
        child = lv_obj_get_child(alarm_list, 0);
        while(child != cont) {
            index++;
            child = lv_obj_get_child(alarm_list, index);
        }
        lv_obj_del(cont);
        // 更新数组数据
        for(uint8_t i = index; i < alarm_count - 1; i++) {
            alarm_items[i] = alarm_items[i + 1];
        }
        alarm_count--;
    }
    // 获取消息框的父对象（可能是遮罩层）
    lv_obj_t *parent = lv_obj_get_parent(msgbox);
    // 删除消息框
    lv_obj_del(msgbox);
    
    if(parent != NULL && parent != lv_scr_act()) {
        lv_obj_del(parent);
    }
    
    // 强制刷新屏幕
    lv_obj_invalidate(lv_scr_act());
}

// 修改长按事件回调函数
static void alarm_item_event_cb(lv_event_t *e)
{
    lv_obj_t *cont = lv_event_get_target(e);
    
    static const char *btns[] = {"取消", "确定", ""}; // 添加空字符串作为数组结束标志
    lv_obj_t *mbox = lv_msgbox_create(NULL, "警告", "确定删除这个闹钟?", btns, false);
    
    // 直接设置字体，无需检查
    lv_obj_set_style_text_font(mbox, &Clock_font_cn_16_t, 0);
    
    lv_obj_set_user_data(mbox, cont);
    
    // 设置对话框样式
    lv_obj_set_style_bg_color(mbox, lv_color_hex(0x2c2c2e), 0);
    lv_obj_set_style_text_color(mbox, lv_color_white(), 0);
    lv_obj_set_style_border_width(mbox, 0, 0);
    lv_obj_set_style_radius(mbox, 10, 0);
    
    // 获取并设置标题样式
    lv_obj_t *title = lv_msgbox_get_title(mbox);
    if(title) {  // 只检查对象是否存在
        lv_obj_set_style_text_font(title, &Clock_font_cn_16_t, 0);
        lv_obj_set_style_text_color(title, lv_color_hex(0xff4757), 0);
    }
    
    // 获取并设置文本样式
    lv_obj_t *text = lv_msgbox_get_text(mbox);
    if(text) {  // 只检查对象是否存在
        lv_obj_set_style_text_font(text, &Clock_font_cn_16_t, 0);
        lv_obj_set_style_text_color(text, lv_color_white(), 0);
        lv_obj_set_style_pad_top(text, 20, 0);
        lv_obj_set_style_pad_bottom(text, 20, 0);
    }
    
    // 获取并设置按钮样式
    lv_obj_t *btns_obj = lv_msgbox_get_btns(mbox);
    if(btns_obj) {  // 只检查对象是否存在
        lv_obj_set_style_bg_color(btns_obj, lv_color_hex(0x2c2c2e), 0);
        lv_obj_set_style_text_font(btns_obj, &Clock_font_cn_16_t, 0);
    }
    
    // 添加事件回调
    lv_obj_add_event_cb(mbox, delete_confirm_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    
    // 设置大小和位置
    lv_obj_set_size(mbox, 200, LV_SIZE_CONTENT);
    lv_obj_center(mbox);
}

// 修改创建闹钟项的函数，同时保存数据
static void create_alarm_item(lv_obj_t *parent, uint8_t hour, uint8_t minute) 
{
    if (alarm_count >= 10) return;  // 防止数组越界
    
    // 保存闹钟数据
    alarm_items[alarm_count].hour = hour;
    alarm_items[alarm_count].minute = minute;
    alarm_items[alarm_count].enabled = true;
    alarm_count++;
    
    // 创建闹钟项UI
    lv_obj_t *cont = lv_obj_create(parent);
    lv_obj_set_size(cont, 210, 50);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x2c2c2e), 0);
    lv_obj_set_style_radius(cont, 10, 0);
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_remove_style(cont, NULL, LV_PART_SCROLLBAR);
    lv_obj_set_scroll_dir(cont, LV_DIR_NONE);
    
    // 添加长按事件
    lv_obj_add_event_cb(cont, alarm_item_event_cb, LV_EVENT_LONG_PRESSED, NULL);
    
    // 创建时间标签
    lv_obj_t *time_label = lv_label_create(cont);
    char time_str[16];
    snprintf(time_str, sizeof(time_str), "%02d:%02d", hour, minute);
    lv_label_set_text(time_label, time_str);
    lv_obj_set_style_text_color(time_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(time_label, &Clock_font_24_t, 0);
    lv_obj_align(time_label, LV_ALIGN_LEFT_MID, 15, 0);
    
    // 创开关按钮
    lv_obj_t *sw = lv_switch_create(cont);
    lv_obj_set_size(sw, 40, 25);
    lv_obj_align(sw, LV_ALIGN_RIGHT_MID, -15, 0);
    lv_obj_set_style_bg_color(sw, lv_color_hex(0x404040), LV_PART_MAIN);
    lv_obj_set_style_bg_color(sw, lv_color_hex(0x00ff00), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_add_state(sw, LV_STATE_CHECKED);
}

// 修改确认按钮回调函数
static void time_picker_confirm_event_cb(lv_event_t *e)
{
    char hour_str[3], minute_str[3];
    /*获取设置的时间*/
    lv_roller_get_selected_str(picker->hour_roller, hour_str, sizeof(hour_str));    
    lv_roller_get_selected_str(picker->minute_roller, minute_str, sizeof(minute_str));
    
    // 获取闹钟列表容器
    lv_obj_t *alarm_list = lv_obj_get_child(clock_app->tab_Alarm, 0);
    
    // 创建新的闹钟项
    create_alarm_item(alarm_list, atoi(hour_str), atoi(minute_str));
    
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
    lv_obj_set_size(roller, width, height); 

    lv_obj_set_style_text_align(roller, LV_TEXT_ALIGN_CENTER, 0); // 文本居中对齐
    lv_obj_set_style_bg_color(roller, bg_color, 0);
    lv_obj_set_style_text_color(roller, lv_color_hex(0x666666), 0); // 未选中项的颜色
    lv_obj_set_style_border_width(roller, 0, 0);
    lv_obj_set_style_bg_opa(roller, 0, LV_PART_SELECTED);
    lv_obj_set_style_text_color(roller, lv_color_white(), LV_PART_SELECTED);
    lv_obj_set_style_text_font(roller, &lv_font_montserrat_24, LV_PART_SELECTED);
    lv_obj_set_style_text_font(roller, &lv_font_montserrat_16, 0);

    return roller;
}

static lv_obj_t *create_alarm_btn(lv_obj_t *parent, lv_coord_t width, lv_coord_t height, lv_color_t color, const char *text)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, width, height);
    lv_obj_set_style_bg_color(btn, color, 0);
    lv_obj_set_style_shadow_width(btn, 0, 0);
    lv_obj_t *label = lv_label_create(btn);
    lv_obj_set_style_text_font(label, &Clock_font_cn_16_t, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text(label, text);
    lv_obj_center(label);
    return btn;
}
/*闹钟*/
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
    lv_obj_set_style_text_font(hour_label, &Clock_font_cn_16_t, 0);
    lv_obj_set_style_text_color(hour_label, lv_color_white(), 0);
    lv_label_set_text(hour_label, "时");

    // 创建"分"标签
    lv_obj_t *minute_label = lv_label_create(picker->popup);
    lv_obj_set_style_text_font(minute_label, &Clock_font_cn_16_t, 0);
    lv_obj_set_style_text_color(minute_label, lv_color_white(), 0);
    lv_label_set_text(minute_label, "分");

    // 创建小时选择器
    picker->hour_roller = create_alarm_roller(picker->popup, 80, 150,lv_color_hex(0x2c2c2e));
    lv_roller_set_options(picker->hour_roller, hour_options, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(picker->hour_roller, 5);
    lv_obj_align(picker->hour_roller, LV_ALIGN_LEFT_MID, 10, 0); 

    // 创建分钟选择器
    picker->minute_roller = create_alarm_roller(picker->popup, 80, 150,lv_color_hex(0x2c2c2e));
    lv_roller_set_options(picker->minute_roller, minute_options, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(picker->minute_roller, 5);
    lv_obj_align(picker->minute_roller, LV_ALIGN_RIGHT_MID, -10, 0); 

    lv_obj_align_to(minute_label, picker->minute_roller, LV_ALIGN_OUT_TOP_MID, 0, -10); 
    lv_obj_align_to(hour_label, picker->hour_roller, LV_ALIGN_OUT_TOP_MID, 0, -10);     

    lv_obj_t *btn_confirm = create_alarm_btn(picker->popup, 50, 30, lv_color_hex(0x228df2), "确定");
    lv_obj_add_event_cb(btn_confirm, time_picker_confirm_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *btn_cancel = create_alarm_btn(picker->popup, 50, 30, lv_color_hex(0x228df2), "取消");
    lv_obj_add_event_cb(btn_cancel, time_picker_cancel_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_align_to(btn_confirm, picker->minute_roller, LV_ALIGN_OUT_BOTTOM_MID, 0, 5); 
    lv_obj_align_to(btn_cancel, picker->hour_roller, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);    
}
// 修改添加按钮的回调函数
static void alarm_add_event_cb(lv_event_t *e)
{
    create_time_picker();
}
static void create_Alarm(lv_obj_t *tab)
{
    // 禁用 tab 的滚动和滚动条
    lv_obj_set_scroll_dir(tab, LV_DIR_NONE);
    lv_obj_remove_style(tab, NULL, LV_PART_SCROLLBAR);
    
    // 创建一个容器来存放所有闹钟项
    lv_obj_t *alarm_list = lv_obj_create(tab);
    lv_obj_set_size(alarm_list, 230, 220);  // 留出底部空间给添加按钮
    lv_obj_align(alarm_list, LV_ALIGN_TOP_MID, 0, 3);
    lv_obj_set_style_bg_color(alarm_list, lv_color_black(), 0);
    lv_obj_set_style_border_width(alarm_list, 0, 0);
    lv_obj_set_style_pad_all(alarm_list, 10, 0);
   
    // 启用表垂直滚动和滚动条
    lv_obj_set_scroll_dir(alarm_list, LV_DIR_VER);
    
    // 设置为垂直方向的 flex 布局
    lv_obj_set_flex_flow(alarm_list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(alarm_list, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(alarm_list, 10, 0);  // 设置项目间距

    // 恢复保存的闹钟数据
    for (int i = 0; i < alarm_count; i++) {
        // 直接创建UI，不需要再次保存数据
        lv_obj_t *cont = lv_obj_create(alarm_list);
        lv_obj_set_size(cont, 210, 50);
        lv_obj_set_style_bg_color(cont, lv_color_hex(0x2c2c2e), 0);
        lv_obj_set_style_radius(cont, 10, 0);
        lv_obj_set_style_border_width(cont, 0, 0);
        lv_obj_remove_style(cont, NULL, LV_PART_SCROLLBAR);
        lv_obj_set_scroll_dir(cont, LV_DIR_NONE);
        
        // 创建时间标签
        lv_obj_t *time_label = lv_label_create(cont);
        char time_str[16];
        snprintf(time_str, sizeof(time_str), "%02d:%02d", 
                alarm_items[i].hour, alarm_items[i].minute);
        lv_label_set_text(time_label, time_str);
        lv_obj_set_style_text_color(time_label, lv_color_white(), 0);
        lv_obj_set_style_text_font(time_label, &Clock_font_24_t, 0);
        lv_obj_align(time_label, LV_ALIGN_LEFT_MID, 15, 0);
        
        // 创建开关按钮
        lv_obj_t *sw = lv_switch_create(cont);
        lv_obj_set_size(sw, 40, 25);
        lv_obj_align(sw, LV_ALIGN_RIGHT_MID, -15, 0);
        lv_obj_set_style_bg_color(sw, lv_color_hex(0x404040), LV_PART_MAIN);
        lv_obj_set_style_bg_color(sw, lv_color_hex(0x00ff00), LV_PART_INDICATOR | LV_STATE_CHECKED);
        if (alarm_items[i].enabled) {
            lv_obj_add_state(sw, LV_STATE_CHECKED);
        }
        // 添加长按事件
        lv_obj_add_event_cb(cont, alarm_item_event_cb, LV_EVENT_LONG_PRESSED, NULL);
    }

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





/*************************************************************秒表****************************************************************/
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

// 始/暂停按钮回调
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
        lv_label_set_text(label, "暂停");

        // 显计圈按钮
        lv_obj_t *lap_label = lv_obj_get_child(sw->btn_lap, 0);
        lv_label_set_text(lap_label, "计时");
    }
    else
    {
        // 暂停计时
        sw->running = false;
        lv_obj_set_style_bg_color(sw->btn_start, lv_color_hex(0x2ed573), 0);
        lv_obj_t *label = lv_obj_get_child(sw->btn_start, 0);
        lv_label_set_text(label, "继续");

        // 显示清除按钮
        lv_obj_t *lap_label = lv_obj_get_child(sw->btn_lap, 0);
        lv_label_set_text(lap_label, "清除");
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
        lv_obj_set_style_text_font(lap_label, &lv_font_montserrat_14, 0);
        lv_label_set_text(lap_label, lap_text);
        // 滚动到新添加的记录
        lv_obj_scroll_to_y(sw->lap_list, LV_COORD_MAX, LV_ANIM_ON);
    }
    else
    {
        lv_obj_set_style_bg_color(sw->btn_start, lv_color_hex(0x2ed573), 0);
        lv_obj_t *label = lv_obj_get_child(sw->btn_start, 0);
        lv_label_set_text(label, "开始");
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
        free(stopwatch);  // 这里释放后立即将指设为 NULL
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
    lv_label_set_text(start_label, "开始");
    lv_obj_set_style_text_font(start_label, &Clock_font_cn_16_t, 0);
    lv_obj_center(start_label);
    lv_obj_add_event_cb(stopwatch->btn_start, btn_start_event_cb, LV_EVENT_CLICKED, NULL);

    // 创建计圈按钮
    stopwatch->btn_lap = lv_btn_create(tab);
    lv_obj_set_size(stopwatch->btn_lap, 80, 40);
    lv_obj_align(stopwatch->btn_lap, LV_ALIGN_BOTTOM_RIGHT, -20, 10);
    lv_obj_set_style_bg_color(stopwatch->btn_lap, lv_color_hex(0x5352ed), 0);
    lv_obj_t *lap_label = lv_label_create(stopwatch->btn_lap);
    lv_label_set_text(lap_label, "计时");
    lv_obj_set_style_text_font(lap_label, &Clock_font_cn_16_t, 0);
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
            
            // 新时间标签
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
        
      
        // 启动定时 (1000ms = 1秒)
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
    lv_obj_set_style_text_font(timer_picker->btn_start, &lv_font_montserrat_14, 0);
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
    lv_obj_set_style_text_font(timer_picker->btn_pause, &lv_font_montserrat_14, 0);
    lv_obj_add_event_cb(timer_picker->btn_pause, timer_btn_pause_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_flag(timer_picker->btn_pause, LV_OBJ_FLAG_HIDDEN);
    
    // 创停止按钮
    timer_picker->btn_stop = create_timer_btn(tab, 40, 40,lv_color_hex(0x2c2c2e),LV_SYMBOL_STOP,true,0);
    lv_obj_set_style_text_font(timer_picker->btn_stop, &lv_font_montserrat_14, 0);
    lv_obj_add_event_cb(timer_picker->btn_stop, timer_btn_stop_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_flag(timer_picker->btn_stop, LV_OBJ_FLAG_HIDDEN);

    lv_obj_align(timer_picker->btn_pause, LV_ALIGN_BOTTOM_LEFT, 20, 14);
    lv_obj_align(timer_picker->btn_stop, LV_ALIGN_BOTTOM_RIGHT, -20, 14);


}

/***********************************************************************************************************************************/
/***********************************************************************************************************************************/

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

    lv_obj_set_style_text_font(clock_app->clock_tabview, &Clock_font_cn_16_t, 0);
    clock_app->tab_Alarm = tabview_add_tab(clock_app->clock_tabview, "闹钟");
    clock_app->tab_Stopwatch = tabview_add_tab(clock_app->clock_tabview, "秒表");
    clock_app->tab_timer = tabview_add_tab(clock_app->clock_tabview, "计时器");

    lv_obj_remove_style(clock_app->clock_tabview, NULL, LV_PART_SCROLLBAR);
    lv_obj_remove_style(clock_app->tab_Alarm, NULL, LV_PART_SCROLLBAR);
    lv_obj_remove_style(clock_app->tab_Stopwatch, NULL, LV_PART_SCROLLBAR);
    lv_obj_remove_style(clock_app->tab_timer, NULL, LV_PART_SCROLLBAR);

       // 添加这一行来禁用 tab_Stopwatch 的滚动
    lv_obj_set_scroll_dir(clock_app->tab_Stopwatch, LV_DIR_NONE);
    lv_obj_set_scroll_dir(clock_app->tab_timer, LV_DIR_NONE);
    lv_obj_set_scroll_dir(clock_app->tab_timer, LV_DIR_NONE);

    create_Alarm(clock_app->tab_Alarm);
    create_Stopwatch(clock_app->tab_Stopwatch);
    create_Timer(clock_app->tab_timer);
    return clock_app->clock_page;
}
