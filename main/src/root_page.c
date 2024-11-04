#include "sys.h"

extern lv_group_t *group;

lv_obj_t *user_area;
static lv_obj_t *flex;
lv_obj_t *btns[APP_COUNTS];
const char *apps[] = {APP_NAMES};
const char *symbols[] = {APP_SYMBOL};
lv_obj_t *root;
lv_obj_t *second_page;

static lv_obj_t *btn_right;
static lv_obj_t *btn_left;
static lv_obj_t *second_btn_right;
static lv_obj_t *second_btn_left;

lv_group_t *group_second_page;

static void btn_cb(lv_event_t *e)
{

    lv_obj_t *btn = lv_event_get_target(e);
    int item = 0;

    for (int i = 0; i < APP_COUNTS; i++)
    {
        if (btn == btns[i])
        {
            item = i;
            break;
        }
    }

    printf(" item %d  %s PRESSED\n", item, apps[item]);
    launch_app_fragment(apps[item], true);
}

static void btn_left_or_right_second_page_cb(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    if (btn == second_btn_right)
    {
        printf("btn_left\n");
        lv_indev_set_group(indev, group);
        lv_scr_load(root);
    }
    else if (btn == second_btn_left)
    {
        printf("btn_right\n");
        lv_indev_set_group(indev, group);
        lv_scr_load(root);
    }
}
void create_second_page(void)
{
    group_second_page = lv_group_create();

    second_page = lv_obj_create(NULL);
    lv_obj_set_size(second_page, 240, 280);
    remove_styles(second_page, true, false, true, true);
    lv_obj_set_style_pad_all(second_page, 0, 0);
    lv_obj_set_scrollbar_mode(second_page, LV_SCROLLBAR_MODE_OFF); // 关闭滚动条
    lv_obj_set_style_bg_color(second_page, lv_color_hex(0x5951e3), 0);
    lv_obj_set_style_bg_opa(second_page, 100, 0);
    lv_obj_set_style_border_width(second_page, 0, 0);

    second_btn_left = lv_btn_create(second_page);
    lv_obj_set_size(second_btn_left, 10, 25);
    lv_obj_align(second_btn_left, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_t *label_left = lv_label_create(second_btn_left);
    lv_label_set_text(label_left, LV_SYMBOL_LEFT);
    lv_obj_set_style_text_font(label_left, &lv_font_montserrat_14, 0);
    lv_obj_center(label_left);
    lv_obj_set_style_bg_color(second_btn_left, lv_color_hex(0x5951e3), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(second_btn_left, 0, 0);
    lv_obj_set_style_border_width(second_btn_left, 0, 0);
    lv_obj_set_style_shadow_opa(second_btn_left, 0, 0);

    second_btn_right = lv_btn_create(second_page);
    lv_obj_set_size(second_btn_right, 10, 25);
    lv_obj_align(second_btn_right, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_t *label_right = lv_label_create(second_btn_right);
    lv_label_set_text(label_right, LV_SYMBOL_RIGHT);
    lv_obj_set_style_text_font(label_right, &lv_font_montserrat_14, 0);
    lv_obj_center(label_right);
    lv_obj_set_style_bg_color(second_btn_right, lv_color_hex(0x5951e3), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(second_btn_right, 0, 0);
    lv_obj_set_style_border_width(second_btn_right, 0, 0);
    lv_obj_set_style_shadow_opa(second_btn_right, 0, 0);

    lv_obj_add_event_cb(second_btn_left, btn_left_or_right_second_page_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(second_btn_right, btn_left_or_right_second_page_cb, LV_EVENT_CLICKED, NULL);

    lv_group_add_obj(group_second_page, second_btn_left);
    lv_group_add_obj(group_second_page, second_btn_right);

    lv_obj_t *weather_widget = create_weather_widget_app(second_page, group_second_page);
    lv_obj_t *clock_widget1 = create_clock_widget1(second_page);
    lv_obj_t *clock_widget2 = create_clock_widget2(second_page);
    lv_obj_t *wooden_fish_widget = create_wooden_fish_widget(second_page, group_second_page);

    lv_obj_align(clock_widget2, LV_ALIGN_TOP_MID, 0, 7);
    lv_obj_align_to(clock_widget1, clock_widget2, LV_ALIGN_OUT_BOTTOM_LEFT, 2, 9);
    lv_obj_align_to(weather_widget, clock_widget1, LV_ALIGN_OUT_RIGHT_MID, 13, 0);
    lv_obj_align(wooden_fish_widget, LV_ALIGN_BOTTOM_MID, 0, -10);
}

static void btn_left_or_right_cb(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    if (btn == btn_left)
    {
        printf("btn_left\n");
        lv_indev_set_group(indev, group_second_page);
        lv_scr_load(second_page);
    }
    else if (btn == btn_right)
    {
        printf("btn_right\n");
        lv_indev_set_group(indev, group_second_page);
        lv_scr_load(second_page);
    }
}

static root_page_t *root_page;

root_page_t *create_root(lv_obj_t *parent)
{
    if (root_page == NULL)
    {
        root_page = (root_page_t *)malloc(sizeof(root_page_t));
        if (root_page == NULL)
        {
            printf("root_page malloc failed\n");
            return NULL;
        }
        root_page->tileview = NULL;
        root_page->page1 = NULL;
        root_page->page2 = NULL;
        root_page->label = NULL;
    }

    /* 创建平铺视图页面 */
    root_page->tileview = lv_tileview_create(parent);
    lv_obj_set_size(root_page->tileview, 240, 260);
    lv_obj_align(root_page->tileview, LV_ALIGN_TOP_MID, 0, 20);
    lv_obj_set_style_pad_all(root_page->tileview, 0, 0);

    /* 添加页面 1 */
    root_page->page1 = lv_tileview_add_tile(root_page->tileview, 0, 1, LV_DIR_VER);
    lv_obj_set_style_pad_all(root_page->page1, 0, 0);

    /* 添加页面 2 */
    root_page->page2 = lv_tileview_add_tile(root_page->tileview, 0, 2, LV_DIR_VER);
    lv_obj_set_style_pad_all(root_page->page2, 0, 0);

    lv_obj_remove_style(root_page->tileview, NULL, LV_PART_SCROLLBAR); /* 移除滚动条 */
    lv_obj_set_tile(root_page->tileview, root_page->page1, LV_ANIM_ON);

    lv_obj_t *weather_widget = create_weather_widget_app(root_page->page1, NULL);
    lv_obj_t *clock_widget1 = create_clock_widget1(root_page->page1);
    lv_obj_t *clock_widget2 = create_clock_widget2(root_page->page1);
    lv_obj_t *wooden_fish_widget = create_wooden_fish_widget(root_page->page1, NULL);

    lv_obj_align(clock_widget2, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_align(clock_widget1, LV_ALIGN_LEFT_MID, 10, 17);
    lv_obj_align(weather_widget, LV_ALIGN_RIGHT_MID, -10, 17);
    lv_obj_align(wooden_fish_widget, LV_ALIGN_BOTTOM_MID, 0, -2);

    // 创建网格
    flex = lv_obj_create(root_page->page2);
    lv_obj_set_size(flex, 230, 240);
    lv_obj_center(flex);
    lv_obj_set_style_bg_color(flex, lv_color_hex(0x97a1b6), LV_PART_MAIN);
    remove_styles(flex, true, true, true, true);
    lv_obj_set_style_border_width(flex, 0, 0);
    lv_obj_set_style_pad_all(flex, 1, 0); // 设置整体内边距
    // lv_obj_set_style_border_width(user_area, 1, 0);
    // 设置网格布局
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_grid_dsc_array(flex, col_dsc, row_dsc);

    lv_obj_t *label;
    lv_obj_t *obj;
    lv_obj_t *label_symbol;

    uint32_t i;
    for (i = 0; i < APP_COUNTS; i++)
    {
        int row = i / 3;
        int col = i % 3;

        lv_obj_t *obj = lv_obj_create(flex);
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

        // lv_obj_add_event_cb(btns[i], btn_cb, LV_EVENT_CLICKED, NULL);
    }

    return root_page;
}
