#include "sys.h"

// extern lv_group_t *group;
static void animate_in_x(lv_obj_t *obj, int delay, int anim_time, lv_anim_path_cb_t path_cb, lv_coord_t start, lv_coord_t end);
static void animate_in_y(lv_obj_t *obj, int delay, int anim_time, lv_anim_path_cb_t path_cb, lv_coord_t start, lv_coord_t end);
void create_widgets_with_animation(lv_obj_t *parent);
void create_page_with_animation(lv_obj_t *parent);
static void page2_scroll(lv_obj_t *parent);
static void scroll_event_cb(lv_event_t *e);
static void create_flex_app(lv_obj_t *parent);

lv_obj_t *user_area;
static lv_obj_t *grid;
lv_obj_t *btns[APP_COUNTS];
const char *apps[] = {APP_NAMES};
const char *symbols[] = {APP_SYMBOL};
lv_obj_t *root;

// 设置网格布局
static lv_coord_t col_dsc[] = {LV_GRID_FR(1),
                               LV_GRID_FR(1),
                               LV_GRID_FR(1),
                               LV_GRID_TEMPLATE_LAST};
static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

root_page_t *root_page;

static lv_obj_t *clock_widget2;
static lv_obj_t *wooden_fish_widget;
static lv_obj_t *weather_widget;
static lv_obj_t *clock_widget1;

void load_page(const char *app)
{

    if (strcmp(app, "Game") == 0)
    {
        // printf("Game\n");
        lv_page->game_page = create_game_app();
        cleanup_page(lv_page->root_page);
        lv_scr_load_anim(lv_page->game_page, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, true);
    }
    else if (strcmp(app, "Setting") == 0)
    {
        // printf("Setting\n");
        lv_page->setting_page = create_setting_app();
        cleanup_page(lv_page->root_page);
        lv_scr_load_anim(lv_page->setting_page, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, true);
    }
    else if (strcmp(app, "Serial") == 0)
    {
        // printf("Serial\n");
        lv_page->serial_page = create_serial_app();
        cleanup_page(lv_page->root_page);
        lv_scr_load_anim(lv_page->serial_page, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, true);
    }
    else if (strcmp(app, "Music") == 0)
    {
        // printf("Music\n");
        lv_page->music_page = create_music_app();
        cleanup_page(lv_page->root_page);
        lv_scr_load_anim(lv_page->music_page, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, true);
    }
    else if (strcmp(app, "Tools") == 0)
    {
        // printf("Tools\n");
        lv_page->tools_page = tools_list_create();
        cleanup_page(lv_page->root_page);
        lv_scr_load_anim(lv_page->tools_page, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, true);
    }
    else if (strcmp(app, "Calendar") == 0)
    {
        // printf("Calendar\n");
        lv_page->calender_page = create_calendar_app();
        cleanup_page(lv_page->root_page);
        lv_scr_load_anim(lv_page->calender_page, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, true);
    }
    else if (strcmp(app, "MQTT") == 0)
    {
        // printf("MQTT\n");
        lv_page->mqtt_page = create_mqtt_app();
        cleanup_page(lv_page->root_page);
        lv_scr_load_anim(lv_page->mqtt_page, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, true);
    }
    else if (strcmp(app, "BlueTooth") == 0)
    {
        // printf("BlueTooth\n");
        lv_page->bluetooth_page = create_bluetooth_app();
        cleanup_page(lv_page->root_page);
        lv_scr_load_anim(lv_page->bluetooth_page, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, true);
    }
    else if (strcmp(app, "Weather") == 0)
    {
        // printf("Weather\n");
        // 先检查并释放旧页面

        lv_page->weather_page = create_weather_app();
        lv_scr_load_anim(lv_page->weather_page, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, true);

        cleanup_page(lv_page->root_page);
    }
    else if (strcmp(app, "Calculators1") == 0)
    {
    }
    else if (strcmp(app, "Calculators2") == 0)
    {
    }
    else if (strcmp(app, "Calculators3") == 0)
    {
    }
    else if (strcmp(app, "WiFi1") == 0)
    {
    }
}

uint8_t btn_index = 0;

static void btn_cb(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    const char *app = lv_event_get_user_data(e);

    for (size_t i = 0; i < APP_COUNTS; i++)
    {
        if (btns[i] == btn)
        {
            btn_index = i;
            printf("btn_index: %d\n", btn_index);
            load_page(apps[i]);
        }
    }

    // load_page(app);

    /**************************************************改版本弃用fragment*****************************************************/
    // 进入fragment，开启平铺视图的滚动功能
    //  printf(" item %d  %s PRESSED\n", item, apps[item]);
    //  launch_app_fragment(apps[item], true);
    /************************************************************************************************************************/
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
    if (root_page == NULL)
    {
        root_page = (root_page_t *)malloc(sizeof(root_page_t));
        if (root_page == NULL)
        {
            printf("root_page malloc failed\n");
            return NULL;
        }
        root_page->root_page = NULL;
        root_page->tileview = NULL;
        root_page->page1 = NULL;
        root_page->page2 = NULL;
        root_page->label = NULL;
        root_page->page0 = NULL;
    }

    root_page->root_page = create_page("Home"); // 创建主页面

    // lv_obj_remove_style(root_page->root_page, NULL, LV_PART_SCROLLBAR);

    /*禁用滚动*/

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

    // lv_obj_set_size(root_page->page2, 240, 265);
    lv_obj_set_style_pad_all(root_page->tileview, 0, 0);
    lv_obj_set_style_pad_all(root_page->page0, 0, 0);
    lv_obj_set_style_pad_all(root_page->page1, 0, 0);
    lv_obj_set_style_pad_all(root_page->page2, 0, 0);

    lv_obj_t *label_page0 = lv_label_create(root_page->page0);
    lv_obj_set_style_bg_color(label_page0, lv_color_hex(0x202020), 0);
    lv_clock_demo(root_page->page0);

    lv_obj_set_size(root_page->page1, 240, 280);
    lv_obj_set_style_bg_color(root_page->page1, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(root_page->page1, LV_OPA_COVER, 0);
    create_widgets_with_animation(root_page->page1);

    // create_flex_app(root_page->page2);
    // lv_obj_set_scrollbar_mode(root_page->page2, LV_SCROLLBAR_MODE_OFF);
    // lv_obj_remove_style(root_page->tileview, NULL, LV_PART_SCROLLBAR);
    page2_scroll(root_page->page2);

    return root_page->root_page;
}

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
    // lv_obj_set_style_border_width(user_area, 1, 0);

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

        // 添加高度缩放效果
        float scale = 1.0f - (float)x / (float)r * 0.3f;
        int32_t height = 60 * scale;
        lv_obj_set_height(child, height);
    }
}

static void page2_scroll(lv_obj_t *parent)
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
        lv_obj_add_event_cb(btns[i], btn_cb, LV_EVENT_SHORT_CLICKED, apps[i]);
    }

    lv_event_send(cont, LV_EVENT_SCROLL, NULL);
    lv_obj_scroll_to_view(lv_obj_get_child(cont, 0), LV_ANIM_OFF);
}