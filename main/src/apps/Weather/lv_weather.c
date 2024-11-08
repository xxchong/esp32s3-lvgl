#include "sys.h"

#include "weather_http.h"

extern now_weather_info_t now_weather_info;
extern three_day_weather_info_t three_day_weather_info[3];

LV_FONT_DECLARE(weather_font_cn_12_t);
LV_FONT_DECLARE(weather_font_cn_10_t);
LV_FONT_DECLARE(weather_font_cn_15_t);
LV_FONT_DECLARE(weather_font_cn_40_t);
LV_FONT_DECLARE(weather_font_60_t);
LV_FONT_DECLARE(weather_font_cn_20_t);
LV_FONT_DECLARE(weather_font_cn_18_t);

// static void lv_weather_update_icon(uint8_t threedays, int weatherid);
// extern SemaphoreHandle_t xBinarySemaphore;
extern lv_indev_t *indev;
extern lv_obj_t *user_area;
extern lv_group_t *group;
const char *Date[3] = {"今天", "明天", "后天"};

bool in_weather_app = false;

typedef struct
{
    lv_obj_t *weather_page;
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_btn;
    lv_obj_t *label_Gps;
    lv_obj_t *label_update_time;
    lv_obj_t *label_cerrent_max_min_temp;
    lv_obj_t *label_location;
    lv_obj_t *label_weather_text;
    lv_obj_t *label_current_temp;
    lv_obj_t *label_current_icon;
    lv_obj_t *label;
    lv_obj_t *label_max_temp[3];
    lv_obj_t *label_min_temp[3];
    lv_obj_t *label_weather_icon[3];
    lv_obj_t *bar_weather[3];
    lv_obj_t *label_threedays_cont;
} lv_weather_t;

static lv_weather_t *weather_app;
static lv_obj_t *day_cont[4];

static void btn_return_cb(lv_event_t *e)
{
    back_to_home(lv_page->weather_page);
}

// static void lv_weather_update_icon(uint8_t threedays, int weatherid)
// {
//     auto it = weather_icon_map.find(weatherid);

//     if (it != weather_icon_map.end())
//     {
//         if (threedays == 0)
//         {
//             lv_label_set_text(weather_app->label_current_icon, it->second);
//         }
//         else if (threedays == 1)
//         {
//             lv_label_set_text(weather_app->label_weather_icon[0], it->second);
//         }
//         else if (threedays == 2)
//         {
//             lv_label_set_text(weather_app->label_weather_icon[1], it->second);
//         }
//         else if (threedays == 3)
//         {
//             lv_label_set_text(weather_app->label_weather_icon[2], it->second);
//         }
//     }
//     printf("天气ID: %d, 图标已更新\n", weatherid);
// }

// void update_weather_data(void)
// {

//     // 添加调试信息
//     printf("当前温度: %s, 更新时间: %s\n", now_weather_info.temp, now_weather_info.time);

//     char update_str[64]; // 增加到64字节
//     char temp_str[32];   // 增加到32字节
//     snprintf(update_str, sizeof(update_str), "%s 更新", now_weather_info.time);
//     lv_label_set_text(weather_app->label_update_time, update_str);

//     // 当前温度
//     snprintf(temp_str, sizeof(temp_str), "%s°", now_weather_info.temp);
//     lv_label_set_text(weather_app->label_current_temp, temp_str);

//     // 检查 WeatherData_threedays 数组的大小
//     // 三天温度
//     if (sizeof(three_day_weather_info) / sizeof(three_day_weather_info[0]) >= 3)
//     {
//         snprintf(temp_str, sizeof(temp_str), "%s° / %s°",
//                  three_day_weather_info[0].tempMin,
//                  three_day_weather_info[0].tempMax);
//         lv_label_set_text(weather_app->label_cerrent_max_min_temp, temp_str);

//         for (int i = 0; i < 3; i++)
//         {
//             snprintf(temp_str, sizeof(temp_str), "%s°", three_day_weather_info[i].tempMax);
//             lv_label_set_text(weather_app->label_max_temp[i], temp_str);

//             snprintf(temp_str, sizeof(temp_str), "%s°", three_day_weather_info[i].tempMin);
//             lv_label_set_text(weather_app->label_min_temp[i], temp_str);
//         }
//     }
//     else
//     {
//         printf("WeatherData_threedays 数组大小不足");
//     }

//     // lv_weather_update_icon(0, now_weather_info.icon);

//     for (int i = 0; i < 3; i++)
//     {
//         lv_bar_set_start_value(weather_app->bar_weather[i], atoi(three_day_weather_info[i].tempMin), LV_ANIM_ON);
//         lv_bar_set_value(weather_app->bar_weather[i], atoi(three_day_weather_info[i].tempMax), LV_ANIM_ON);
//     }
// }

lv_obj_t *create_weather_app(void)
{
    if (weather_app == NULL)
    {
        weather_app = (lv_weather_t *)malloc(sizeof(lv_weather_t));
        if (weather_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for weather_app\n");
            return NULL;
        }
        // 初始化成员变量
        weather_app->weather_page = NULL;
        weather_app->group = NULL;
        weather_app->btn_return = NULL;
        weather_app->label_btn = NULL;
        weather_app->label_location = NULL;
        weather_app->label_weather_text = NULL;
        weather_app->label_Gps = NULL;
        weather_app->label = NULL;
        weather_app->label_threedays_cont = NULL;
        weather_app->label_current_icon = NULL;
        weather_app->label_update_time = NULL;
        weather_app->label_cerrent_max_min_temp = NULL;
        weather_app->label_current_temp = NULL;

        // 初始化数组成员
        for (int i = 0; i < 3; i++)
        {
            weather_app->label_max_temp[i] = NULL;
            weather_app->label_min_temp[i] = NULL;
            weather_app->label_weather_icon[i] = NULL;
            weather_app->bar_weather[i] = NULL;
        }
    }

    weather_app->weather_page = create_page("Weather"); // 创建主页面
    // create_status_bar(weather_app->weather_page);       // 创建状态栏
    lv_obj_set_style_bg_color(weather_app->weather_page, lv_color_hex(0x1b7ff1), 0);

    // 创建返回按钮
    weather_app->btn_return = create_app_btn_return(weather_app->weather_page);
    lv_obj_add_event_cb(weather_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    weather_app->label_Gps = lv_label_create(weather_app->weather_page);
    lv_label_set_text(weather_app->label_Gps, LV_SYMBOL_GPS);
    lv_obj_set_style_text_font(weather_app->label_Gps, &lv_font_montserrat_14, 0);
    lv_obj_align(weather_app->label_Gps, LV_ALIGN_TOP_MID, 0, 5);

    weather_app->label_location = lv_label_create(weather_app->weather_page);
    lv_obj_set_style_text_font(weather_app->label_location, &weather_font_cn_18_t, 0);
    lv_label_set_text(weather_app->label_location, "广州市");
    lv_obj_align_to(weather_app->label_location, weather_app->label_Gps, LV_ALIGN_OUT_BOTTOM_MID, 0, 2);

    weather_app->label_update_time = lv_label_create(weather_app->weather_page);
    lv_obj_set_style_text_font(weather_app->label_update_time, &weather_font_cn_15_t, 0);
    lv_label_set_text(weather_app->label_update_time, "00:20 更新");
    lv_obj_align_to(weather_app->label_update_time, weather_app->label_location, LV_ALIGN_OUT_BOTTOM_MID, 0, 2);

    weather_app->label_current_icon = lv_label_create(weather_app->weather_page);
    lv_obj_set_style_text_font(weather_app->label_current_icon, &weather_font_60_t, 0);
    lv_label_set_text(weather_app->label_current_icon, USER_WEATHER_SYMBOL_100);
    lv_obj_set_style_text_color(weather_app->label_current_icon, lv_color_hex(0xee8665), 0);
    lv_obj_align_to(weather_app->label_current_icon, weather_app->label_update_time, LV_ALIGN_OUT_BOTTOM_MID, 0, 2);

    weather_app->label_current_temp = lv_label_create(weather_app->weather_page);
    lv_obj_set_style_text_font(weather_app->label_current_temp, &weather_font_cn_40_t, 0);
    lv_label_set_text(weather_app->label_current_temp, "30°");
    lv_obj_align_to(weather_app->label_current_temp, weather_app->label_current_icon, LV_ALIGN_OUT_BOTTOM_MID, 5, 10);

    weather_app->label_cerrent_max_min_temp = lv_label_create(weather_app->weather_page);
    lv_obj_set_style_text_font(weather_app->label_cerrent_max_min_temp, &lv_font_montserrat_20, 0);
    lv_label_set_text(weather_app->label_cerrent_max_min_temp, "10° / 30°");
    lv_obj_align_to(weather_app->label_cerrent_max_min_temp, weather_app->label_current_temp, LV_ALIGN_OUT_BOTTOM_MID, -4, 5);

    weather_app->label_weather_text = lv_label_create(weather_app->weather_page);
    lv_obj_set_style_text_font(weather_app->label_weather_text, &weather_font_cn_20_t, 0);
    lv_label_set_text(weather_app->label_weather_text, "未知");
    lv_obj_align_to(weather_app->label_weather_text, weather_app->label_cerrent_max_min_temp, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    weather_app->label_threedays_cont = lv_obj_create(weather_app->weather_page);
    lv_obj_set_style_pad_all(weather_app->label_threedays_cont, 0, 0);
    lv_obj_set_size(weather_app->label_threedays_cont, 225, 130);
    lv_obj_set_style_bg_color(weather_app->label_threedays_cont, lv_color_hex(0x586293), 0);
    lv_obj_align_to(weather_app->label_threedays_cont, weather_app->label_weather_text, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);
    lv_obj_set_style_bg_opa(weather_app->label_threedays_cont, 80, 0);
    lv_obj_set_style_border_width(weather_app->label_threedays_cont, 0, 0);
    lv_obj_set_style_radius(weather_app->label_threedays_cont, 8, 0);

    lv_obj_set_scrollbar_mode(weather_app->label_threedays_cont, LV_SCROLLBAR_MODE_OFF);

    for (int i = 0; i < 4; i++)
    {
        day_cont[i] = lv_obj_create(weather_app->label_threedays_cont);
        lv_obj_set_size(day_cont[i], 225, 31);
        lv_obj_set_style_pad_all(day_cont[i], 0, 0);
        lv_obj_set_style_bg_opa(day_cont[i], 0, 0);
        lv_obj_set_scrollbar_mode(day_cont[i], LV_SCROLLBAR_MODE_OFF);

        // 设置下边框为白色
        lv_obj_set_style_border_color(day_cont[i], lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(day_cont[i], 80, 0); // 设置边框透明度
        lv_obj_set_style_border_width(day_cont[i], 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_side(day_cont[i], LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_obj_align(day_cont[i], LV_ALIGN_TOP_LEFT, 0, i * 30); // 等距分布
    }

    weather_app->label = lv_label_create(day_cont[0]);
    lv_obj_set_style_text_color(weather_app->label, lv_color_white(), 0);
    lv_obj_set_style_text_font(weather_app->label, &weather_font_cn_18_t, 0);
    lv_obj_set_style_text_opa(weather_app->label, 190, 0);
    lv_obj_align(weather_app->label, LV_ALIGN_LEFT_MID, 6, 0);
    lv_label_set_text(weather_app->label, "近三日天气预报");

    for (int i = 0; i < 3; i++)
    {
        weather_app->label = lv_label_create(day_cont[i + 1]);
        lv_obj_set_style_text_color(weather_app->label, lv_color_white(), 0);
        lv_obj_set_style_text_font(weather_app->label, &weather_font_cn_18_t, 0);
        lv_obj_set_style_text_color(weather_app->label, lv_color_white(), 0);
        lv_obj_set_style_text_opa(weather_app->label, 190, 0);
        lv_label_set_text(weather_app->label, Date[i]);
        lv_obj_align(weather_app->label, LV_ALIGN_LEFT_MID, 1, 3);

        weather_app->label_weather_icon[i] = lv_label_create(day_cont[i + 1]);
        lv_obj_align_to(weather_app->label_weather_icon[i], weather_app->label, LV_ALIGN_OUT_RIGHT_MID, 1, -8);
        lv_obj_set_style_text_font(weather_app->label_weather_icon[i], &weather_font_30_t, 0);
        lv_obj_set_style_text_color(weather_app->label_weather_icon[i], lv_color_hex(0xf3b847), 0);
        lv_label_set_text(weather_app->label_weather_icon[i], USER_WEATHER_SYMBOL_305);

        weather_app->label_min_temp[i] = lv_label_create(day_cont[i + 1]);
        lv_obj_set_style_text_font(weather_app->label_min_temp[i], &lv_font_montserrat_18, 0);
        lv_obj_align_to(weather_app->label_min_temp[i], weather_app->label_weather_icon[i], LV_ALIGN_OUT_RIGHT_MID, 5, 0);
        lv_label_set_text(weather_app->label_min_temp[i], "25°");
        lv_obj_set_style_text_color(weather_app->label_min_temp[i], lv_color_white(), 0);

        weather_app->bar_weather[i] = lv_bar_create(day_cont[i + 1]);
        lv_obj_set_size(weather_app->bar_weather[i], 80, 6);    // 增加高度以便更好地显示
        lv_bar_set_range(weather_app->bar_weather[i], -50, 50); // 设置范围为 -20°C 到 50°C
        lv_bar_set_mode(weather_app->bar_weather[i], LV_BAR_MODE_RANGE);
        lv_obj_align_to(weather_app->bar_weather[i], weather_app->label_min_temp[i], LV_ALIGN_OUT_RIGHT_MID, 2, 0);
        lv_obj_set_style_bg_color(weather_app->bar_weather[i], lv_color_hex(0xffffff), LV_PART_MAIN);
        lv_obj_set_style_bg_color(weather_app->bar_weather[i], lv_color_hex(0xf87931), LV_PART_INDICATOR);

        weather_app->label_max_temp[i] = lv_label_create(day_cont[i + 1]);
        lv_obj_set_style_text_font(weather_app->label_max_temp[i], &lv_font_montserrat_18, 0);
        lv_obj_align_to(weather_app->label_max_temp[i], weather_app->bar_weather[i], LV_ALIGN_OUT_RIGHT_MID, 5, 0);
        lv_label_set_text(weather_app->label_max_temp[i], "35°");
        lv_obj_set_style_text_color(weather_app->label_max_temp[i], lv_color_white(), 0);

        lv_bar_set_start_value(weather_app->bar_weather[i], -25, LV_ANIM_ON);
        lv_bar_set_value(weather_app->bar_weather[i], 35, LV_ANIM_ON);
    }

    // lv_group_add_obj(weather_app->group, weather_app->btn_return);
    // lv_group_add_obj(weather_app->group, weather_app->root);
    // 添加事件回调以处理编码器返回

    // if (xSemaphoreGive(xBinarySemaphore) == pdTRUE)
    // {
    //     printf("btn clicked\n");
    // }
    // update_weather_data();
    return weather_app->weather_page;
}
