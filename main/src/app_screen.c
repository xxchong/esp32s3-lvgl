#include "sys.h"

/*函数声明*/
static void app_screen_scroll_event_cb(lv_event_t *e);
void app_screen_load_page(const char *app);
static void app_screen_btn_icon_cb(lv_event_t *e);
static void app_screen_scroll_layout(lv_obj_t *parent);
static void app_screen_grid_layout(lv_obj_t *parent);

/*app_screen 结构体*/
typedef struct
{
    lv_obj_t *app_screen_page;
    lv_obj_t *grid;
} app_screen_t;

lv_obj_t *btns[APP_COUNTS];/*按钮*/
const char *apps[] = {APP_NAMES};/*应用名称*/
const char *symbols[] = {APP_SYMBOL};/*应用图标*/
/*网格布局*/
static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
app_screen_t *app_screen;

/*函数指针*/
typedef lv_obj_t *(*page_creator_fn)(void);
/*页面配置结构体*/
typedef struct
{
    const char *name;
    page_creator_fn creator;
    lv_obj_t **page_ptr;
} page_config_t;

static page_config_t page_configs[10]; /*确保数组大小足够*/


static void init_page_configs(void)
{
    page_configs[0] = (page_config_t){"Game", create_game_app, &lv_page->game_page};
    page_configs[1] = (page_config_t){"Setting", create_setting_app, &lv_page->setting_page};
    page_configs[2] = (page_config_t){"Serial", create_serial_app, &lv_page->serial_page};
    page_configs[3] = (page_config_t){"Music", create_music_app, &lv_page->music_page};
    page_configs[4] = (page_config_t){"Tools", tools_list_create, &lv_page->tools_page};
    page_configs[5] = (page_config_t){"Calendar", create_calendar_app, &lv_page->calender_page};
    page_configs[6] = (page_config_t){"MQTT", create_mqtt_app, &lv_page->mqtt_page};
    page_configs[7] = (page_config_t){"BlueTooth", create_bluetooth_app, &lv_page->bluetooth_page};
    page_configs[8] = (page_config_t){"Weather", create_weather_app, &lv_page->weather_page};
    page_configs[9] = (page_config_t){"Clock", create_clock_app, &lv_page->clock_page};
    page_configs[10] = (page_config_t){NULL, NULL, NULL}; // 结束标记
}

void app_screen_load_page(const char *app)
{
    printf("load_page: %s\n", app);
    const page_config_t *config = page_configs;

    // 查找匹配的页面配置
    while (config->name != NULL)
    {
        if (strcmp(app, config->name) == 0)
        {
            // 创建新页面
            *config->page_ptr = config->creator();
            // 统一的切换动画处理
            lv_scr_load_anim(*config->page_ptr, LV_SCR_LOAD_ANIM_MOVE_LEFT, 30, 0, true);
            return;
        }
        config++;
    }
}

uint8_t btn_index = 0;

static void app_screen_btn_icon_cb(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    const char *app = (const char *)lv_event_get_user_data(e);
    for (size_t i = 0; i < APP_COUNTS; i++)
    {
        if (btns[i] == btn)
        {
            btn_index = i;
            app_screen_load_page(apps[i]);
            return;
        }
    }
}

lv_obj_t *create_app_screen(void)
{
    init_page_configs(); // 初始化页面配置

    if (app_screen != NULL)
    {
        free(app_screen);
        app_screen = NULL;
    }
    if (app_screen == NULL)
    {
        app_screen = (app_screen_t *)calloc(1, sizeof(app_screen_t));
    }

    app_screen->app_screen_page = create_page("App");
    lv_obj_set_size(app_screen->app_screen_page, 240, 280);
    lv_obj_set_style_pad_all(app_screen->app_screen_page, 0, 0);

#ifdef USE_GRID_PAGE2
    create_flex_app(app_screen->app_screen_page);
    lv_obj_set_scrollbar_mode(app_screen->app_screen_page, LV_SCROLLBAR_MODE_OFF);
#else
    app_screen_scroll_layout(app_screen->app_screen_page);
#endif

    return app_screen->app_screen_page;
}

static void app_screen_scroll_event_cb(lv_event_t *e)
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

        // 添加高度缩放效果
        float scale = 1.0f - (float)x / (float)r * 0.3f;
        int32_t height = 65 * scale;
        lv_obj_set_height(child, height);
    }
}

static void app_screen_scroll_layout(lv_obj_t *parent)
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
    lv_obj_add_event_cb(cont, app_screen_scroll_event_cb, LV_EVENT_SCROLL, NULL);
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
        lv_color_hex(0xFF61B9),  // 玫瑰粉
        lv_color_hex(0x61FF61)  // 绿色

    };

    for (uint32_t i = 0; i < APP_COUNTS; i++)
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
        lv_obj_add_event_cb(btns[i], app_screen_btn_icon_cb, LV_EVENT_SHORT_CLICKED, (void *)apps[i]);
    }
    lv_event_send(cont, LV_EVENT_SCROLL, NULL);
    lv_obj_scroll_to_view(lv_obj_get_child(cont, 0), LV_ANIM_OFF);
}

#ifdef USE_GRID_PAGE2
static void app_screen_grid_layout(lv_obj_t *parent)
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
        lv_obj_add_event_cb(btns[i], app_screen_btn_icon_cb, LV_EVENT_SHORT_CLICKED, apps[i]);
    }
}
#endif