

#include "sys.h"

// extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_obj_t *calender_page;
    lv_obj_t *calender;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_desc;
    lv_obj_t *label_btn;
} Calender_t;

static Calender_t *calender_app;

static void btn_return_cb(lv_event_t *e)
{
    back_to_app_screen(lv_page->calender_page);
  
}
LV_FONT_DECLARE(Calender_font_cn_14_t)
static lv_calendar_date_t highlight_days[2]; /* 定义的日期,必须用全局或静态定义 */
const char* day_names[7] = { "日","一", "二","三","四","五","六"};


lv_obj_t *create_calendar_app(void)
{
    if (calender_app != NULL)
    {
        free(calender_app);
        calender_app = NULL;
    }
    if (calender_app == NULL)
    {
        calender_app = (Calender_t *)calloc(1, sizeof(Calender_t));
    }

    calender_app->calender_page = create_page("Calendar"); //创建主页面
    create_status_bar(calender_app->calender_page); //创建状态栏
    calender_app->calender = lv_calendar_create(calender_app->calender_page);
    lv_obj_set_size(calender_app->calender, 240, 260);
    lv_obj_align(calender_app->calender, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_calendar_set_today_date(calender_app->calender, timeinfo->tm_year+1900, timeinfo->tm_mon+1, timeinfo->tm_mday);
    /* 设置日历显示的月份 */
    lv_obj_t* header = lv_calendar_header_arrow_create(calender_app->calender);
    // 获取并修改header中的按钮
    lv_obj_t* btn_left = lv_obj_get_child(header, 0);  // 左箭头按钮
    lv_obj_t* btn_right = lv_obj_get_child(header, 2); // 右箭头按钮
    // 修改按钮样式
    lv_obj_set_style_bg_color(btn_left, lv_color_hex(0x0088FF), 0);
    lv_obj_set_style_bg_color(btn_right, lv_color_hex(0x0088FF), 0);
    lv_obj_set_style_text_color(btn_left, lv_color_hex(0x0088FF), 0);
    lv_obj_set_style_text_color(btn_right, lv_color_hex(0x0088FF), 0);
    // 调整按钮大小和圆角
    lv_obj_set_size(btn_left, 35, 35);
    lv_obj_set_size(btn_right, 35, 35);
    lv_obj_set_style_radius(btn_left, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_radius(btn_right, LV_RADIUS_CIRCLE, 0);
    // 创建新的标签
    lv_obj_t *label_left = lv_label_create(btn_left);
    lv_obj_t *label_right = lv_label_create(btn_right);
    lv_obj_set_style_text_color(label_left, lv_color_white(), 0);
    lv_obj_set_style_text_color(label_right, lv_color_white(), 0);
    // 设置标签文本
    lv_label_set_text(label_left, "<");
    lv_label_set_text(label_right, ">");
    // 居中对齐标签
    lv_obj_center(label_left);
    lv_obj_center(label_right);
    lv_obj_set_style_text_font(calender_app->calender, &Calender_font_cn_14_t, LV_STATE_DEFAULT);
    lv_calendar_set_day_names(calender_app->calender, day_names);
    lv_calendar_set_showed_date(calender_app->calender, timeinfo->tm_year+1900, timeinfo->tm_mon+1);
    lv_obj_update_layout(calender_app->calender);
    return calender_app->calender_page;
}
