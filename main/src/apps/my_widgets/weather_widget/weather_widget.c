#include "sys.h"

LV_FONT_DECLARE(weather_font_cn_20_t);

typedef struct
{
    lv_group_t *group;
    lv_obj_t *btn;
    lv_obj_t *label_Gps;
    lv_obj_t *label_cerrent_max_min_temp;
    lv_obj_t *label_location;
    lv_obj_t *label_weather_text;
    lv_obj_t *label_current_temp;
    lv_obj_t *label_current_icon;
    lv_obj_t *label;
} lv_weather_widget_t;

static lv_weather_widget_t *weather_widget_app;

static void lv_weather_update_icon(int weatherid)
{

    for(size_t i = 0; i < WEATHER_ICONS_SIZE; i++) {
        if(weather_icons[i].weather_id == weatherid) {
            lv_label_set_text(weather_widget_app->label_current_icon, weather_icons[i].icon_symbol);
            return;
        }
    }
    lv_label_set_text(weather_widget_app->label_current_icon, USER_WEATHER_SYMBOL_999);
    printf("天气ID: %d, 图标已更新\n", weatherid);
}

void update_weather_widgetdata(void)
{
    char temp_str[64];
    lv_label_set_text(weather_widget_app->label_weather_text, now_weather_info.text);

    snprintf(temp_str, sizeof(temp_str), "%s°", now_weather_info.temp);
    lv_label_set_text(weather_widget_app->label_current_temp, temp_str);

    snprintf(temp_str, sizeof(temp_str), "%s° / %s°", three_day_weather_info[0].tempMin, three_day_weather_info[0].tempMax);
    lv_label_set_text(weather_widget_app->label_cerrent_max_min_temp, temp_str);

    lv_weather_update_icon(atoi(now_weather_info.icon));
}

static void update_weather_widgetdata_timer_cb(lv_timer_t *timer)
{
    // 检查天气更新是否完成
    if(wait_update_weather_done(pdMS_TO_TICKS(1000)))
    {
        lv_timer_del(timer); // 停止定时器
        update_weather_widgetdata(); // 更新天气数据显示
        cleanup_weather_update(); // 清理更新过程中的资源
    }
    else
    {
        // 如果未完成，则重新设置定时器，延长检查时间
        lv_timer_reset(timer);
    }
}

static void btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
        start_weather_update(); // 启动天气更新
        lv_timer_create(update_weather_widgetdata_timer_cb, 2000, NULL); // 创建定时器，每2秒检查一次
    }
}



lv_obj_t *create_weather_widget_app(lv_obj_t *parent)
{
    if (weather_widget_app != NULL)
    {
        free(weather_widget_app);
        weather_widget_app = NULL;
    }
    if (weather_widget_app == NULL)
    {
        weather_widget_app = (lv_weather_widget_t *)calloc(1, sizeof(lv_weather_widget_t));
    }

    weather_widget_app->btn = lv_btn_create(parent);
    lv_obj_set_size(weather_widget_app->btn, 100, 100);
    lv_obj_set_style_bg_color(weather_widget_app->btn, lv_color_hex(0x1b7ff1), 0);
    lv_obj_set_style_bg_opa(weather_widget_app->btn, 180, 0);
    lv_obj_set_style_pad_all(weather_widget_app->btn, 0, 0);
    lv_obj_set_style_border_width(weather_widget_app->btn, 0, 0);
    lv_obj_set_style_shadow_width(weather_widget_app->btn, 0, 0);
    lv_obj_set_style_radius(weather_widget_app->btn, 8, 0);
    lv_obj_add_event_cb(weather_widget_app->btn, btn_event_cb, LV_EVENT_CLICKED, NULL);

    weather_widget_app->label_current_temp = lv_label_create(weather_widget_app->btn);
    lv_obj_set_style_text_font(weather_widget_app->label_current_temp, &lv_font_montserrat_30, 0);
    lv_obj_align(weather_widget_app->label_current_temp, LV_ALIGN_TOP_LEFT, 3, 1);
    lv_label_set_text(weather_widget_app->label_current_temp, "24°");
    lv_obj_set_style_text_color(weather_widget_app->label_current_temp, lv_color_white(), 0);

    weather_widget_app->label_current_icon = lv_label_create(weather_widget_app->btn);
    lv_obj_set_style_text_color(weather_widget_app->label_current_icon, lv_color_hex(0xee8665), 0);
    lv_obj_set_style_text_font(weather_widget_app->label_current_icon, &qweather_icon_fill_30_t, 0);
    lv_obj_align_to(weather_widget_app->label_current_icon, weather_widget_app->label_current_temp, LV_ALIGN_OUT_RIGHT_MID, 10, -2);
    lv_label_set_text(weather_widget_app->label_current_icon, USER_WEATHER_SYMBOL_102);

    weather_widget_app->label_weather_text = lv_label_create(weather_widget_app->btn);
    lv_obj_set_style_text_font(weather_widget_app->label_weather_text, &weather_font_cn_20_t, 0);
    lv_obj_align_to(weather_widget_app->label_weather_text, weather_widget_app->label_current_temp, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_text(weather_widget_app->label_weather_text, "多云");
    lv_obj_set_style_text_color(weather_widget_app->label_weather_text, lv_color_white(), 0);

    weather_widget_app->label_cerrent_max_min_temp = lv_label_create(weather_widget_app->btn);
    lv_obj_set_style_text_font(weather_widget_app->label_cerrent_max_min_temp, &lv_font_montserrat_20, 0);
    lv_obj_align_to(weather_widget_app->label_cerrent_max_min_temp, weather_widget_app->label_weather_text, LV_ALIGN_OUT_BOTTOM_LEFT, -2, 0);
    lv_label_set_text(weather_widget_app->label_cerrent_max_min_temp, " 24°/ 30°");
    lv_obj_set_style_text_color(weather_widget_app->label_cerrent_max_min_temp, lv_color_white(), 0);

    weather_widget_app->label_location = lv_label_create(weather_widget_app->btn);
    lv_obj_set_style_text_font(weather_widget_app->label_location, &weather_font_cn_20_t, 0);
    lv_obj_align_to(weather_widget_app->label_location, weather_widget_app->label_cerrent_max_min_temp, LV_ALIGN_OUT_BOTTOM_LEFT, 2, 0);
    lv_label_set_text(weather_widget_app->label_location, "广州市");
    lv_obj_set_style_text_color(weather_widget_app->label_location, lv_color_white(), 0);

    weather_widget_app->label_Gps = lv_label_create(weather_widget_app->btn);
    lv_obj_set_style_text_font(weather_widget_app->label_Gps, &lv_font_montserrat_14, 0);
    lv_obj_align_to(weather_widget_app->label_Gps, weather_widget_app->label_location, LV_ALIGN_OUT_RIGHT_MID, 2, 1);
    lv_label_set_text(weather_widget_app->label_Gps, LV_SYMBOL_GPS);
    lv_obj_set_style_text_color(weather_widget_app->label_Gps, lv_color_white(), 0);

    update_weather_widgetdata();
    return weather_widget_app->btn;
}
