#include "sys.h"
static void animate_in_x(lv_obj_t *obj, int delay, int anim_time, lv_anim_path_cb_t path_cb, lv_coord_t start, lv_coord_t end);
static void animate_in_y(lv_obj_t *obj, int delay, int anim_time, lv_anim_path_cb_t path_cb, lv_coord_t start, lv_coord_t end);
void create_widgets_with_animation(lv_obj_t *parent);
void create_page_with_animation(lv_obj_t *parent);
static void page2_scroll_layout(lv_obj_t *parent);
static void scroll_event_cb(lv_event_t *e);
static void create_flex_app(lv_obj_t *parent);
static void watch_cont(lv_obj_t *parent);
static void delete_watch_list(lv_timer_t *timer);
static void watch_close_cb(lv_event_t *e);
static void watch_select_cb(lv_event_t *e);
static void watch_switch_event_cb(lv_event_t *e);
static void create_watch_1(lv_obj_t *parent,bool is_preview);
static void create_watch_2(lv_obj_t *parent,bool is_preview);
static void create_watch_3(lv_obj_t *parent,bool is_preview);
static void create_watch_4(lv_obj_t *parent,bool is_preview);
static lv_obj_t *g_watch_list = NULL;  // 切换表盘的选择容器


static lv_obj_t *grid;
lv_obj_t *btns[APP_COUNTS];
const char *apps[] = {APP_NAMES};
const char *symbols[] = {APP_SYMBOL};
// 设置网格布局
static lv_coord_t col_dsc[] = {LV_GRID_FR(1),LV_GRID_FR(1),LV_GRID_FR(1),LV_GRID_TEMPLATE_LAST};
static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

root_page_t *root_page;
static lv_obj_t *clock_widget2;
static lv_obj_t *wooden_fish_widget;
static lv_obj_t *weather_widget;
static lv_obj_t *clock_widget1;
static uint8_t gloabl_current_watch_id=1;


//函数指针类型
typedef void (*watch_create_fn)(lv_obj_t*, bool);

//函数指针数组
static const watch_create_fn watch_creators[] = {
    create_watch_1,
    create_watch_2,
    create_watch_3,
    create_watch_4
};
// 定义页面创建函数类型
typedef lv_obj_t* (*page_creator_fn)(void);
// 页面配置结构体
typedef struct {
    const char *name;
    page_creator_fn creator;
    lv_obj_t **page_ptr;
} page_config_t;

static page_config_t page_configs[10];  // 确保数组大小足够

static void init_page_configs(void) {
    page_configs[0] = (page_config_t){"Game", create_game_app, &lv_page->game_page};
    page_configs[1] = (page_config_t){"Setting", create_setting_app, &lv_page->setting_page};
    page_configs[2] = (page_config_t){"Serial", create_serial_app, &lv_page->serial_page};
    page_configs[3] = (page_config_t){"Music", create_music_app, &lv_page->music_page};
    page_configs[4] = (page_config_t){"Tools", tools_list_create, &lv_page->tools_page};
    page_configs[5] = (page_config_t){"Calendar", create_calendar_app, &lv_page->calender_page};
    page_configs[6] = (page_config_t){"MQTT", create_mqtt_app, &lv_page->mqtt_page};
    page_configs[7] = (page_config_t){"BlueTooth", create_bluetooth_app, &lv_page->bluetooth_page};
    page_configs[8] = (page_config_t){"Weather", create_weather_app, &lv_page->weather_page};
    page_configs[9] = (page_config_t){NULL, NULL, NULL};  // 结束标记
}

void load_page(const char *app) {
    const page_config_t *config = page_configs;
    
    // 查找匹配的页面配置
    while(config->name != NULL) {
        if(strcmp(app, config->name) == 0) {
            // 创建新页面
            *config->page_ptr = config->creator();
            // 统一的切换动画处理
            cleanup_page(lv_page->root_page);
            lv_scr_load_anim(*config->page_ptr, 
                            LV_SCR_LOAD_ANIM_MOVE_LEFT,
                            (strcmp(app, "Music") == 0) ? 30 : 300, // Music页面特殊处理
                            0, 
                            true);
            return;
        }
        config++;
    }
}

uint8_t btn_index = 0;

static void btn_cb(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    const char *app = (const char *)lv_event_get_user_data(e);
    for (size_t i = 0; i < APP_COUNTS; i++)
    {
        if (btns[i] == btn)
        {
            btn_index = i;
            printf("btn_index: %d\n", btn_index);
            load_page(apps[i]);
        }
    }
}

// 定义回调函数
static void screen_switch_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    animate_in_y(clock_widget2, 0, 700, lv_anim_path_ease_out, -200, -90);
    animate_in_y(wooden_fish_widget, 0, 700, lv_anim_path_ease_out, 300, 225);
    animate_in_x(clock_widget1, 0, 700, lv_anim_path_ease_out, -300, -58);
    animate_in_x(weather_widget, 0, 700, lv_anim_path_ease_out, 300, 128);
}

lv_obj_t *create_root(void)
{
    init_page_configs();  // 初始化页面配置

    if (root_page == NULL)
    {
        root_page = (root_page_t *)malloc(sizeof(root_page_t));
        if (root_page == NULL)
        {
            printf("root_page malloc failed\n");
            return NULL;
        }
        memset(root_page, 0, sizeof(root_page_t));
    }

    root_page->root_page = create_page("Home"); // 创建主页面
    lv_obj_add_event_cb(root_page->root_page, screen_switch_event_cb, LV_EVENT_SCREEN_LOADED, NULL);
    /* 创建平铺视图页面 */
    root_page->tileview = lv_tileview_create(root_page->root_page);
    lv_obj_remove_style(root_page->tileview, NULL, LV_PART_SCROLLBAR); /* 移除滚动条 */

    root_page->page0 = lv_tileview_add_tile(root_page->tileview, 0, 0, LV_DIR_RIGHT);
    /* 添加页面 1 */
    root_page->page1 = lv_tileview_add_tile(root_page->tileview, 1, 0, LV_DIR_RIGHT | LV_DIR_LEFT);
    /* 添加页面 2 */
    root_page->page2 = lv_tileview_add_tile(root_page->tileview, 2, 0, LV_DIR_LEFT);

    lv_obj_set_size(root_page->tileview, 240, 280);
    lv_obj_align(root_page->tileview, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(root_page->tileview, screen_switch_event_cb, LV_EVENT_SCROLL, NULL);

    lv_obj_set_style_pad_all(root_page->tileview, 0, 0);
    lv_obj_set_style_pad_all(root_page->page0, 0, 0);
    lv_obj_set_style_pad_all(root_page->page1, 0, 0);
    lv_obj_set_style_pad_all(root_page->page2, 0, 0);

    watch_cont(root_page->page0);//创建表盘

    lv_obj_set_size(root_page->page1, 240, 280);
    lv_obj_set_style_bg_color(root_page->page1, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(root_page->page1, LV_OPA_COVER, 0);
    create_widgets_with_animation(root_page->page1);
    #ifdef USE_GRID_PAGE2
    create_flex_app(root_page->page2);
    lv_obj_set_scrollbar_mode(root_page->page2, LV_SCROLLBAR_MODE_OFF);
    #else
    page2_scroll_layout(root_page->page2);
    #endif
    return root_page->root_page;
}

 #ifdef USE_GRID_PAGE2
static void create_flex_app(lv_obj_t *parent)
{
    // 创建网格
    grid = lv_obj_create(parent);
    lv_obj_set_size(grid, 230, 240);
    lv_obj_center(grid);
    lv_obj_set_style_bg_color(grid, lv_color_hex(0x97a1b6), LV_PART_MAIN);
    remove_styles(grid, true, true, true, true);
    lv_obj_set_style_border_width(grid, 0, 0);
    lv_obj_set_style_pad_all(grid, 1, 0); // 设置整体内边距
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
    lv_obj_t *label;
    lv_obj_t *obj;
    lv_obj_t *label_symbol;

    uint32_t i;
    for (i = 0; i < APP_COUNTS; i++)
    {
        int row = i / 3;
        int col = i % 3;

        lv_obj_t *obj = lv_obj_create(grid);
        lv_obj_set_size(obj, 75, 75); // 增加单个图标区域的大小
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_CENTER, col, 1, LV_GRID_ALIGN_CENTER, row, 1);
        remove_styles(obj, true, true, true, true);
        lv_obj_set_style_pad_all(obj, 0, 0);
        lv_obj_remove_style(obj, NULL, LV_PART_SCROLLBAR);

        btns[i] = lv_btn_create(obj);
        lv_obj_set_size(btns[i], 50, 50); // 增加按钮的大小
        lv_obj_align(btns[i], LV_ALIGN_TOP_MID, 0, 4);
        lv_obj_set_style_outline_width(btns[i], 2, LV_STATE_FOCUS_KEY);
        lv_obj_set_style_outline_pad(btns[i], 4, LV_STATE_FOCUS_KEY);
        lv_obj_set_style_outline_color(btns[i], lv_color_white(), LV_STATE_FOCUS_KEY);
        lv_obj_set_style_bg_color(btns[i], lv_color_white(), 0);
        lv_obj_set_style_border_width(btns[i], 1, 0);
        lv_obj_set_style_border_color(btns[i], lv_color_white(), 0);
        lv_obj_set_style_radius(btns[i], 15, 0);
        lv_obj_set_style_bg_color(btns[i], lv_color_hex(0x87CEFA), LV_STATE_FOCUS_KEY);
        lv_obj_set_style_border_color(btns[i], lv_color_hex(0x87CEFA), LV_STATE_FOCUS_KEY);
        lv_obj_remove_style(btns[i], NULL, LV_PART_SCROLLBAR);

        lv_obj_t *label_symbol = lv_label_create(btns[i]);
        if (i == 5 || i == 8)
        {
            lv_obj_set_style_text_font(label_symbol, &add_symbol_40_t, 0);
        }
        else
        {
            lv_obj_set_style_text_font(label_symbol, &my_symbol_font_40_t, 0);
        }
        lv_label_set_text(label_symbol, symbols[i]);

        lv_obj_center(label_symbol);
        lv_obj_set_style_text_color(label_symbol, lv_color_black(), 0);

        lv_obj_t *label = lv_label_create(obj);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
        lv_label_set_text_fmt(label, "%s", apps[i]);
        lv_obj_set_style_text_color(label, lv_color_black(), 0);

        lv_obj_align_to(label, btns[i], LV_ALIGN_OUT_BOTTOM_MID, 0, 3);
        lv_obj_add_event_cb(btns[i], btn_cb, LV_EVENT_SHORT_CLICKED, apps[i]);
    }
}
#endif
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

void create_widgets_with_animation(lv_obj_t *parent)
{
    weather_widget = create_weather_widget_app(parent, NULL);
    clock_widget1 = create_clock_widget1(parent);
    clock_widget2 = create_clock_widget2(parent);
    wooden_fish_widget = create_wooden_fish_widget(parent, NULL);
    // 初始位置设置
    lv_obj_set_y(clock_widget2, -200); // 从顶部移入
    lv_obj_set_y(clock_widget1, 20);
    lv_obj_set_x(clock_widget1, -200); // 从左侧移入
    lv_obj_set_y(weather_widget, 111);
    lv_obj_set_x(weather_widget, lv_obj_get_width(parent) + 200); // 从右侧移入
    // 初始位置设置
    lv_obj_set_x(wooden_fish_widget, lv_obj_get_width(parent) / 2 - 60);
    lv_obj_set_y(wooden_fish_widget, lv_obj_get_height(parent) + 50); // 设置初始Y位置在父对象底部之下
}

static void scroll_event_cb(lv_event_t *e)
{
    lv_obj_t *cont = lv_event_get_target(e);
    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    int32_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;

    int32_t r = lv_obj_get_height(cont) * 7 / 10;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);

    for (uint32_t i = 0; i < child_cnt; i++)
    {
        lv_obj_t *child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        int32_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;
        int32_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        int32_t x;
        if (diff_y >= r)
        {
            x = r;
        }
        else
        {
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);
            x = r - res.i;
        }

        lv_obj_set_style_translate_x(child, x, 0);
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
        // 添加高度缩放效果
        float scale = 1.0f - (float)x / (float)r * 0.3f;
        int32_t height = 65 * scale;
        lv_obj_set_height(child, height);
    }
}

static void page2_scroll_layout(lv_obj_t *parent)
{
    lv_obj_t *cont = lv_obj_create(parent);
    lv_obj_center(cont);
    // 设置容器为深色背景
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x171717), LV_PART_MAIN);
    lv_obj_set_size(cont, 240, 280);
    lv_obj_set_style_radius(cont, 0, 0);

    // 容器基础设置保持不变
    lv_obj_set_style_pad_all(cont, 0, 0);
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_set_style_clip_corner(cont, true, 0);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_row(cont, 10, 0);

    // 定义糖果色数组
    const lv_color_t candy_colors[] = {
        lv_color_hex(0xFF61D8), // 粉红
        lv_color_hex(0x61A8FF), // 天蓝
        lv_color_hex(0xFFB961), // 橙黄
        lv_color_hex(0x61FFB9), // 薄荷绿
        lv_color_hex(0xB961FF), // 紫色
        lv_color_hex(0xFF6161), // 珊瑚红
        lv_color_hex(0x61FFFF), // 青色
        lv_color_hex(0xFFFF61), // 柠檬黄
        lv_color_hex(0xFF61B9)  // 玫瑰粉
    };

    for (uint32_t i = 0; i < 9; i++)
    {
        btns[i] = lv_btn_create(cont);
        lv_obj_set_size(btns[i], lv_pct(90), 65);

        // 设置渐变背景
        static lv_grad_dsc_t grad;
        grad.dir = LV_GRAD_DIR_HOR;
        grad.stops_count = 2;
        grad.stops[0].color = lv_color_hex(0x1a1a1a);
        grad.stops[1].color = lv_color_hex(0x2d2d2d);
        grad.stops[0].frac = 0;
        grad.stops[1].frac = 255;
        lv_obj_set_style_bg_grad(btns[i], &grad, 0);
        // 按钮基础样式
        lv_obj_set_style_radius(btns[i], 12, 0);
        lv_obj_set_style_border_color(btns[i], candy_colors[i], 0); // 使用糖果色边框
        lv_obj_set_style_border_width(btns[i], 1, 0);
        lv_obj_set_style_border_opa(btns[i], LV_OPA_30, 0);
        // 添加发光效果
        lv_obj_set_style_shadow_width(btns[i], 15, 0);
        lv_obj_set_style_shadow_color(btns[i], candy_colors[i], 0); // 使用对应的糖果色阴影
        lv_obj_set_style_shadow_opa(btns[i], LV_OPA_20, 0);
        // 按钮按下状态
        lv_obj_set_style_bg_color(btns[i], lv_color_hex(0x333333), LV_STATE_PRESSED);
        lv_obj_set_style_border_opa(btns[i], LV_OPA_50, LV_STATE_PRESSED);
        lv_obj_set_style_shadow_opa(btns[i], LV_OPA_40, LV_STATE_PRESSED);
        // 图标
        lv_obj_t *label_symbol = lv_label_create(btns[i]);
        lv_obj_align(label_symbol, LV_ALIGN_LEFT_MID, 0, 0);
        if (i == 5 || i == 8)
        {
            lv_obj_set_style_text_font(label_symbol, &add_symbol_40_t, 0);
        }
        else
        {
            lv_obj_set_style_text_font(label_symbol, &my_symbol_font_40_t, 0);
        }
        lv_label_set_text(label_symbol, symbols[i]);
        // 设置图标颜色为对应的糖果色
        lv_obj_set_style_text_color(label_symbol, candy_colors[i], 0);

        // 文本标签
        lv_obj_t *label = lv_label_create(btns[i]);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);
        lv_label_set_text_fmt(label, "%s", apps[i]);
        // 设置文本为亮色
        lv_obj_set_style_text_color(label, lv_color_hex(0xeeeeee), 0);

        lv_obj_align_to(label, label_symbol, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
        lv_obj_add_event_cb(btns[i], btn_cb, LV_EVENT_SHORT_CLICKED, (void *)apps[i]);
    }
    lv_event_send(cont, LV_EVENT_SCROLL, NULL);
    lv_obj_scroll_to_view(lv_obj_get_child(cont, 0), LV_ANIM_OFF);
}

static void watch_switch_event_cb(lv_event_t *e)
{
    lv_obj_t *cont = lv_event_get_target(e);
    // 如果列表已存在，直接返回
    if(g_watch_list != NULL) {
        return;
    }
    // 创建水平滚动容器 - 注意创建在屏幕层级
    g_watch_list = lv_obj_create(lv_scr_act());
    lv_obj_set_size(g_watch_list, 240, 280);
    lv_obj_center(g_watch_list);
    lv_obj_set_style_bg_color(g_watch_list, lv_color_hex(0xe4e4e4), 0);
    lv_obj_set_style_border_width(g_watch_list, 0, 0);
    lv_obj_set_style_radius(g_watch_list, 0, 0);
    // 确保选择界面显示在最上层
    lv_obj_move_foreground(g_watch_list);
    // 设置水平滚动
    lv_obj_set_scroll_dir(g_watch_list, LV_DIR_HOR);
    lv_obj_set_scroll_snap_x(g_watch_list, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(g_watch_list, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_column(g_watch_list, 20, 0);
    lv_obj_set_flex_flow(g_watch_list, LV_FLEX_FLOW_ROW);
    
    // 创建多个表盘选项
    for(int i = 0; i < 4; i++) {
        lv_obj_t *watch_option = lv_obj_create(g_watch_list);
        lv_obj_clear_flag(watch_option, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(watch_option, 200, 240);
        lv_obj_set_style_radius(watch_option, 20, 0);
        lv_obj_set_style_bg_color(watch_option, lv_color_hex(0x222222), 0);
        lv_obj_set_style_bg_opa(watch_option, LV_OPA_50, 0);
        lv_obj_set_style_border_width(watch_option, 2, 0);
        lv_obj_set_style_border_color(watch_option, lv_color_hex(0x444444), 0);
        
        watch_creators[i](watch_option, true);
        // 点击选择表盘
        lv_obj_add_event_cb(watch_option, watch_select_cb, LV_EVENT_CLICKED, (void*)(uintptr_t)i);
    }
    // 保存原始容器引用
    g_watch_list->user_data = cont;
    // 动画显示列表
    lv_obj_set_style_opa(g_watch_list, 0, 0);
    lv_obj_fade_in(g_watch_list, 300, 0);
}

static void watch_select_cb(lv_event_t *e)
{
    uintptr_t watch_id = (uintptr_t)lv_event_get_user_data(e);
    lv_obj_t *main_cont = g_watch_list->user_data;
    gloabl_current_watch_id = watch_id; // 保存选择的表盘ID
    stop_watch_timer(); //删除watch的定时器
    // 更新主表盘显示 - 完全清理所有子对象和样式
    lv_obj_clean(main_cont);
    lv_obj_set_style_bg_color(main_cont, lv_color_hex(0xe4e4e4), 0); // 重置背景色
    lv_obj_set_style_bg_opa(main_cont, LV_OPA_COVER, 0); // 确保不透明度为100%
    // 添加长按事件到表盘
    lv_obj_add_event_cb(main_cont, watch_switch_event_cb, LV_EVENT_LONG_PRESSED, NULL);
    
    // 根据选择的表盘ID设置不同的样式
    watch_creators[watch_id](main_cont,false);
    // 关闭选择界面
    lv_obj_fade_out(g_watch_list, 300, 0);
    // 使用定时器延迟删除对象
    lv_timer_t *timer = lv_timer_create(delete_watch_list, 300, NULL);
    lv_timer_set_repeat_count(timer, 1);
}

// 添加删除函数
static void delete_watch_list(lv_timer_t *timer)
{
    if(g_watch_list) {
        lv_obj_del(g_watch_list);
        g_watch_list = NULL;
    }
}

static void watch_cont(lv_obj_t *parent)
{
    lv_obj_set_size(parent, 240, 280);
    lv_obj_set_style_radius(parent, 0, 0);
    lv_obj_set_style_border_width(parent, 0, 0);
    lv_obj_set_style_pad_all(parent, 0, 0);
    watch_creators[gloabl_current_watch_id](parent,false);
    // 添加长按事件
    lv_obj_add_event_cb(parent, watch_switch_event_cb, LV_EVENT_LONG_PRESSED, NULL);
}


static void create_watch_1(lv_obj_t *parent,bool is_preview)
{
    lv_clock_demo(parent,is_preview);
}
static void create_watch_2(lv_obj_t *parent,bool is_preview)
{
   lv_clock_watch_2(parent,is_preview);
}

static void create_watch_3(lv_obj_t *parent,bool is_preview)
{
    lv_clock_watch_3(parent,is_preview);
}

static void create_watch_4(lv_obj_t *parent,bool is_preview)
{
    lv_clock_watch_4(parent,is_preview);
}
