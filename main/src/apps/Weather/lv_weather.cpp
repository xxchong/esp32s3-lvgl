// #include <Arduino.h>
// #include <lvgl.h>
// #include <icon.h>
// #include "fragment.h"
// #include "util.h"
// #include "apps/Weather/lv_weather.h"
// #include "weather.h"
// /*将天气代码映射到相应的天气图标符号。 */
// const std::unordered_map<int, const char *> weather_icon_map = {
//     // 哈希表数据结构
//     {100, USER_WEATHER_SYMBOL_100}, // 晴天
//     {101, USER_WEATHER_SYMBOL_101}, // 多云
//     {102, USER_WEATHER_SYMBOL_102}, // 少云
//     {103, USER_WEATHER_SYMBOL_103}, // 晴间多云
//     {104, USER_WEATHER_SYMBOL_104}, // 阴天
//     {150, USER_WEATHER_SYMBOL_150}, // 晴
//     {151, USER_WEATHER_SYMBOL_151}, // 多云
//     {152, USER_WEATHER_SYMBOL_152}, // 少云
//     {153, USER_WEATHER_SYMBOL_153}, // 晴间多云
//     {300, USER_WEATHER_SYMBOL_300}, // 阵雨
//     {301, USER_WEATHER_SYMBOL_301}, // 强阵雨
//     {302, USER_WEATHER_SYMBOL_302}, // 雷阵雨
//     {303, USER_WEATHER_SYMBOL_303}, // 强雷阵雨
//     {304, USER_WEATHER_SYMBOL_304}, // 雷阵雨伴有冰雹
//     {305, USER_WEATHER_SYMBOL_305}, // 小雨
//     {306, USER_WEATHER_SYMBOL_306}, // 中雨
//     {307, USER_WEATHER_SYMBOL_307}, // 大雨
//     {308, USER_WEATHER_SYMBOL_308}, // 极端降雨
//     {309, USER_WEATHER_SYMBOL_309}, // 毛毛雨/细雨
//     {310, USER_WEATHER_SYMBOL_310}, // 暴雨
//     {311, USER_WEATHER_SYMBOL_311}, // 大暴雨
//     {312, USER_WEATHER_SYMBOL_312}, // 特大暴雨
//     {313, USER_WEATHER_SYMBOL_313}, // 冻雨
//     {314, USER_WEATHER_SYMBOL_314}, // 小到中雨
//     {315, USER_WEATHER_SYMBOL_315}, // 中到大雨
//     {316, USER_WEATHER_SYMBOL_316}, // 大到暴雨
//     {317, USER_WEATHER_SYMBOL_317}, // 暴雨到大暴雨
//     {318, USER_WEATHER_SYMBOL_318}, // 大暴雨到特大暴雨
//     {350, USER_WEATHER_SYMBOL_350}, // 阵雨
//     {351, USER_WEATHER_SYMBOL_351}, // 强阵雨
//     {399, USER_WEATHER_SYMBOL_399}, // 雨
//     {400, USER_WEATHER_SYMBOL_400}, // 小雪
//     {401, USER_WEATHER_SYMBOL_401}, // 中雪
//     {402, USER_WEATHER_SYMBOL_402}, // 大雪
//     {403, USER_WEATHER_SYMBOL_403}, // 暴雪
//     {404, USER_WEATHER_SYMBOL_404}, // 雨夹雪
//     {405, USER_WEATHER_SYMBOL_405}, // 雨雪天气
//     {406, USER_WEATHER_SYMBOL_406}, // 阵雨夹雪
//     {407, USER_WEATHER_SYMBOL_407}, // 阵雪
//     {408, USER_WEATHER_SYMBOL_408}, // 小到中雪
//     {409, USER_WEATHER_SYMBOL_409}, // 中到大雪
//     {410, USER_WEATHER_SYMBOL_410}, // 大到暴雪
//     {456, USER_WEATHER_SYMBOL_456}, // 阵雨夹雪
//     {457, USER_WEATHER_SYMBOL_457}, // 阵雪
//     {499, USER_WEATHER_SYMBOL_499}, // 雪
//     {500, USER_WEATHER_SYMBOL_500}, // 薄雾
//     {501, USER_WEATHER_SYMBOL_501}, // 雾
//     {502, USER_WEATHER_SYMBOL_502}, // 霾
//     {503, USER_WEATHER_SYMBOL_503}, // 扬沙
//     {504, USER_WEATHER_SYMBOL_504}, // 浮尘
//     {507, USER_WEATHER_SYMBOL_507}, // 沙尘暴
//     {508, USER_WEATHER_SYMBOL_508}, // 强沙尘暴
//     {509, USER_WEATHER_SYMBOL_509}, // 浓雾
//     {510, USER_WEATHER_SYMBOL_510}, // 强浓雾
//     {511, USER_WEATHER_SYMBOL_511}, // 中度霾
//     {512, USER_WEATHER_SYMBOL_512}, // 重度霾
//     {513, USER_WEATHER_SYMBOL_513}, // 严重霾
//     {514, USER_WEATHER_SYMBOL_514}, // 大雾
//     {515, USER_WEATHER_SYMBOL_515}, // 特强浓雾
//     {800, USER_WEATHER_SYMBOL_800}, // 新月
//     {801, USER_WEATHER_SYMBOL_801}, // 蛾眉月
//     {802, USER_WEATHER_SYMBOL_802}, // 上弦月
//     {803, USER_WEATHER_SYMBOL_803}, // 盈凸月
//     {804, USER_WEATHER_SYMBOL_804}, // 满月
//     {805, USER_WEATHER_SYMBOL_805}, // 亏凸月
//     {806, USER_WEATHER_SYMBOL_806}, // 下弦月
//     {807, USER_WEATHER_SYMBOL_807}, // 残月
//     {900, USER_WEATHER_SYMBOL_900}, // 热
//     {901, USER_WEATHER_SYMBOL_901}, // 冷
//     {999, USER_WEATHER_SYMBOL_999}, // 未知
// };

// LV_FONT_DECLARE(weather_font_cn_12_t);
// LV_FONT_DECLARE(weather_font_cn_10_t);
// LV_FONT_DECLARE(weather_font_cn_15_t);
// LV_FONT_DECLARE(weather_font_cn_40_t);
// LV_FONT_DECLARE(weather_font_60_t);
// LV_FONT_DECLARE(weather_font_cn_20_t);
// LV_FONT_DECLARE(weather_font_cn_18_t);

// static void lv_weather_update_icon(uint8_t threedays, int weatherid);
// extern SemaphoreHandle_t xBinarySemaphore;
// extern lv_indev_t *indev;
// extern lv_obj_t *user_area;
// extern lv_group_t *group;
// const char *Date[3] = {"今天", "明天", "后天"};

// typedef struct
// {
//     lv_group_t *group;
//     lv_obj_t *btn_return;
//     lv_obj_t *label_btn;
//     lv_obj_t *label_Gps;
//     lv_obj_t *root;
//     lv_obj_t *label_update_time;
//     lv_obj_t *label_cerrent_max_min_temp;
//     lv_obj_t *label_location;
//     lv_obj_t *label_weather_text;
//     lv_obj_t *label_current_temp;
//     lv_obj_t *label_current_icon;
//     lv_obj_t *label;
//     lv_obj_t *label_max_temp[3];
//     lv_obj_t *label_min_temp[3];
//     lv_obj_t *label_weather_icon[3];
//     lv_obj_t *bar_weather[3];
//     lv_obj_t *label_threedays_cont;
// } lv_weather_t;

// static lv_weather_t *weather_app;
// static lv_obj_t *day_cont[4];
// static void btn_return_cb(lv_event_t *e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t *obj = lv_event_get_target(e);

//     if(obj == weather_app->btn_return)
//     {
//         size_t size = lv_fragment_manager_get_stack_size(manager);
//         Serial.printf("当前栈内有%d个内容\n", size); // 添加调试信息
//         if (size > 1)                                // 大于二级界面
//         {
//         }
//         else if (size == 1) // 二级界面
//         {
//             lv_fragment_manager_pop(manager); // 弹出当前片段
//             Return_root_page();
//         }
//     }else if(obj == weather_app->root)
//     {
//         lv_group_focus_obj(weather_app->btn_return);
//     }

// }

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
//     Serial.printf("天气ID: %d, 图标已更新\n", weatherid);
// }

// void update_weather_data(void)
// {
//     char temp_str[20];

//     // 添加调试信息
//     Serial.printf("当前温度: %d, 更新时间: %s\n", WeatherData_current.temp, WeatherData_current.updateTime.c_str());

//     lv_label_set_text(weather_app->label_weather_text, WeatherData_current.text.c_str());
//     lv_label_set_text(weather_app->label_update_time, (WeatherData_current.updateTime + " 更新").c_str());

//     snprintf(temp_str, sizeof(temp_str), "%d°", WeatherData_current.temp);
//     lv_label_set_text(weather_app->label_current_temp, temp_str);

//     // 检查 WeatherData_threedays 数组的大小
//     if (sizeof(WeatherData_threedays) / sizeof(WeatherData_threedays[0]) >= 3)
//     {
//         snprintf(temp_str, sizeof(temp_str), "%d° / %d°", WeatherData_threedays[0].tempMin, WeatherData_threedays[0].tempMax);
//         lv_label_set_text(weather_app->label_cerrent_max_min_temp, temp_str);

//         for (int i = 0; i < 3; i++)
//         {
//             snprintf(temp_str, sizeof(temp_str), "%d°", WeatherData_threedays[i].tempMax);
//             lv_label_set_text(weather_app->label_max_temp[i], temp_str);

//             snprintf(temp_str, sizeof(temp_str), "%d°", WeatherData_threedays[i].tempMin);
//             lv_label_set_text(weather_app->label_min_temp[i], temp_str);

//             lv_weather_update_icon(i + 1, WeatherData_threedays[i].iconDay);
//         }
//     }
//     else
//     {
//         Serial.println("WeatherData_threedays 数组大小不足");
//     }

//     lv_weather_update_icon(0, WeatherData_current.icon);

//     for (int i = 0; i < 3; i++)
//     {
//         lv_bar_set_start_value(weather_app->bar_weather[i], -WeatherData_threedays[i].tempMin, LV_ANIM_ON);
//         lv_bar_set_value(weather_app->bar_weather[i], WeatherData_threedays[i].tempMax, LV_ANIM_ON);
//     }
// }

// void create_weather_app(lv_obj_t *parent)
// {
//     if (weather_app == NULL)
//     {
//         weather_app = (lv_weather_t *)malloc(sizeof(lv_weather_t));
//         if (weather_app == NULL)
//         {
//             // 处理内存分配失败的情况
//             printf("Failed to allocate memory for weather_app\n");
//             return;
//         }
//         // 初始化成员变量
//         weather_app->group = NULL;
//         weather_app->btn_return = NULL;
//         weather_app->label_btn = NULL;
//         weather_app->root = NULL;
//         weather_app->label_location = NULL;
//         weather_app->label_weather_text = NULL;
//         weather_app->label_Gps = NULL;
//         weather_app->label = NULL;
//         weather_app->label_threedays_cont = NULL;
//         weather_app->label_current_icon = NULL;
//         weather_app->label_update_time = NULL;
//         weather_app->label_cerrent_max_min_temp = NULL;
//         weather_app->label_current_temp = NULL;

//         // 初始化数组成员
//         for (int i = 0; i < 3; i++)
//         {
//             weather_app->label_max_temp[i] = NULL;
//             weather_app->label_min_temp[i] = NULL;
//             weather_app->label_weather_icon[i] = NULL;
//             weather_app->bar_weather[i] = NULL;
//         }
//     }

//     weather_app->group = lv_group_create();
//     lv_indev_set_group(indev, weather_app->group);

//     weather_app->root = lv_obj_create(parent);
//     lv_obj_set_size(weather_app->root, 240, 255);
//     lv_obj_set_style_bg_color(weather_app->root, lv_color_hex(0x1ac0fb), 0);
//     lv_obj_center(weather_app->root);
//     lv_obj_set_style_bg_opa(weather_app->root, 130, 0);
//     lv_obj_set_style_pad_all(weather_app->root, 0, 0);
//     lv_obj_set_scrollbar_mode(weather_app->root, LV_SCROLLBAR_MODE_OFF); // 关闭滚动条

//     // 创建返回按钮
//     weather_app->btn_return = lv_btn_create(parent);
//     lv_obj_set_size(weather_app->btn_return, 15, 15);

//     remove_styles(weather_app->btn_return, false, true, true, true);
//     lv_obj_set_style_bg_color(weather_app->btn_return, lv_color_white(), 0);
//     lv_obj_set_style_border_width(weather_app->btn_return, 1, 0);
//     lv_obj_set_style_border_color(weather_app->btn_return, lv_color_black(), 0);

//     lv_obj_align_to(weather_app->btn_return, weather_app->root, LV_ALIGN_TOP_LEFT, 2, 2);

//     // 创建按钮上的标签
//     weather_app->label_btn = lv_label_create(weather_app->btn_return);
//     lv_obj_set_style_text_font(weather_app->label_btn, &my_symbol_font_10_t, 0);
//     lv_label_set_text(weather_app->label_btn, USER_SYMBOL_RETURN2);
//     lv_obj_center(weather_app->label_btn);
//     lv_obj_set_style_text_color(weather_app->label_btn, lv_color_black(), 0);
//     lv_obj_add_event_cb(weather_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

//     weather_app->label_Gps = lv_label_create(weather_app->root);
//     lv_label_set_text(weather_app->label_Gps, LV_SYMBOL_GPS);
//     lv_obj_set_style_text_font(weather_app->label_Gps, &lv_font_montserrat_14, 0);
//     lv_obj_align(weather_app->label_Gps, LV_ALIGN_TOP_MID, 0, 5);

//     weather_app->label_location = lv_label_create(weather_app->root);
//     lv_obj_set_style_text_font(weather_app->label_location, &weather_font_cn_18_t, 0);
//     lv_label_set_text(weather_app->label_location, "广州市");
//     lv_obj_align_to(weather_app->label_location, weather_app->label_Gps, LV_ALIGN_OUT_BOTTOM_MID, 0, 2);

//     weather_app->label_update_time = lv_label_create(weather_app->root);
//     lv_obj_set_style_text_font(weather_app->label_update_time, &weather_font_cn_15_t, 0);
//     lv_label_set_text(weather_app->label_update_time, "00:20 更新");
//     lv_obj_align_to(weather_app->label_update_time, weather_app->label_location, LV_ALIGN_OUT_BOTTOM_MID, 0, 2);

//     weather_app->label_current_icon = lv_label_create(weather_app->root);
//     lv_obj_set_style_text_font(weather_app->label_current_icon, &weather_font_60_t, 0);
//     lv_label_set_text(weather_app->label_current_icon, USER_WEATHER_SYMBOL_100);
//     lv_obj_set_style_text_color(weather_app->label_current_icon, lv_color_hex(0xee8665), 0);
//     lv_obj_align_to(weather_app->label_current_icon, weather_app->label_update_time, LV_ALIGN_OUT_BOTTOM_MID, 0, 2);

//     weather_app->label_current_temp = lv_label_create(weather_app->root);
//     lv_obj_set_style_text_font(weather_app->label_current_temp, &weather_font_cn_40_t, 0);
//     lv_label_set_text(weather_app->label_current_temp, "30°");
//     lv_obj_align_to(weather_app->label_current_temp, weather_app->label_current_icon, LV_ALIGN_OUT_BOTTOM_MID, 5, 10);

//     weather_app->label_cerrent_max_min_temp = lv_label_create(weather_app->root);
//     lv_obj_set_style_text_font(weather_app->label_cerrent_max_min_temp, &lv_font_montserrat_20, 0);
//     lv_label_set_text(weather_app->label_cerrent_max_min_temp, "10° / 30°");
//     lv_obj_align_to(weather_app->label_cerrent_max_min_temp, weather_app->label_current_temp, LV_ALIGN_OUT_BOTTOM_MID, -4, 5);

//     weather_app->label_weather_text = lv_label_create(weather_app->root);
//     lv_obj_set_style_text_font(weather_app->label_weather_text, &weather_font_cn_20_t, 0);
//     lv_label_set_text(weather_app->label_weather_text, "未知");
//     lv_obj_align_to(weather_app->label_weather_text, weather_app->label_cerrent_max_min_temp, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

//     weather_app->label_threedays_cont = lv_obj_create(weather_app->root);
//     lv_obj_set_style_pad_all(weather_app->label_threedays_cont, 0, 0);
//     lv_obj_set_size(weather_app->label_threedays_cont, 225, 130);
//     lv_obj_set_style_bg_color(weather_app->label_threedays_cont, lv_color_hex(0x586293), 0);
//     lv_obj_align_to(weather_app->label_threedays_cont, weather_app->label_weather_text, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);
//     lv_obj_set_style_bg_opa(weather_app->label_threedays_cont, 80, 0);
//     lv_obj_set_style_border_width(weather_app->label_threedays_cont, 0, 0);
//     lv_obj_set_style_radius(weather_app->label_threedays_cont, 8, 0);

//     lv_obj_set_scrollbar_mode(weather_app->label_threedays_cont, LV_SCROLLBAR_MODE_OFF);

//     for (int i = 0; i < 4; i++)
//     {
//         day_cont[i] = lv_obj_create(weather_app->label_threedays_cont);
//         lv_obj_set_size(day_cont[i], 225, 31);
//         lv_obj_set_style_pad_all(day_cont[i], 0, 0);
//         lv_obj_set_style_bg_opa(day_cont[i], 0, 0);
//         lv_obj_set_scrollbar_mode(day_cont[i], LV_SCROLLBAR_MODE_OFF);

//         // 设置下边框为白色
//         lv_obj_set_style_border_color(day_cont[i], lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_opa(day_cont[i], 80, 0); // 设置边框透明度
//         lv_obj_set_style_border_width(day_cont[i], 1, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_side(day_cont[i], LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);

//         lv_obj_align(day_cont[i], LV_ALIGN_TOP_LEFT, 0, i * 30); // 等距分布
//     }

//     weather_app->label = lv_label_create(day_cont[0]);
//     lv_obj_set_style_text_color(weather_app->label, lv_color_white(), 0);
//     lv_obj_set_style_text_font(weather_app->label, &weather_font_cn_18_t, 0);
//     lv_obj_set_style_text_opa(weather_app->label, 190, 0);
//     lv_obj_align(weather_app->label, LV_ALIGN_LEFT_MID, 6, 0);
//     lv_label_set_text(weather_app->label, "近三日天气预报");

//     for (int i = 0; i < 3; i++)
//     {
//         weather_app->label = lv_label_create(day_cont[i + 1]);
//         lv_obj_set_style_text_color(weather_app->label, lv_color_white(), 0);
//         lv_obj_set_style_text_font(weather_app->label, &weather_font_cn_18_t, 0);
//         lv_obj_set_style_text_color(weather_app->label, lv_color_white(), 0);
//         lv_obj_set_style_text_opa(weather_app->label, 190, 0);
//         lv_label_set_text(weather_app->label, Date[i]);
//         lv_obj_align(weather_app->label, LV_ALIGN_LEFT_MID, 1, 3);

//         weather_app->label_weather_icon[i] = lv_label_create(day_cont[i + 1]);
//         lv_obj_align_to(weather_app->label_weather_icon[i], weather_app->label, LV_ALIGN_OUT_RIGHT_MID, 1, -8);
//         lv_obj_set_style_text_font(weather_app->label_weather_icon[i], &weather_font_30_t, 0);
//         lv_obj_set_style_text_color(weather_app->label_weather_icon[i], lv_color_hex(0xf3b847), 0);
//         lv_label_set_text(weather_app->label_weather_icon[i], USER_WEATHER_SYMBOL_305);

//         weather_app->label_min_temp[i] = lv_label_create(day_cont[i + 1]);
//         lv_obj_set_style_text_font(weather_app->label_min_temp[i], &lv_font_montserrat_18, 0);
//         lv_obj_align_to(weather_app->label_min_temp[i], weather_app->label_weather_icon[i], LV_ALIGN_OUT_RIGHT_MID, 5, 0);
//         lv_label_set_text(weather_app->label_min_temp[i], "25°");
//         lv_obj_set_style_text_color(weather_app->label_min_temp[i], lv_color_white(), 0);

//         weather_app->bar_weather[i] = lv_bar_create(day_cont[i + 1]);
//         lv_obj_set_size(weather_app->bar_weather[i], 80, 6);    // 增加高度以便更好地显示
//         lv_bar_set_range(weather_app->bar_weather[i], -50, 50); // 设置范围为 -20°C 到 50°C
//         lv_bar_set_mode(weather_app->bar_weather[i], LV_BAR_MODE_RANGE);
//         lv_obj_align_to(weather_app->bar_weather[i], weather_app->label_min_temp[i], LV_ALIGN_OUT_RIGHT_MID, 2, 0);
//         lv_obj_set_style_bg_color(weather_app->bar_weather[i], lv_color_hex(0xffffff), LV_PART_MAIN);
//         lv_obj_set_style_bg_color(weather_app->bar_weather[i], lv_color_hex(0xf87931), LV_PART_INDICATOR);

//         weather_app->label_max_temp[i] = lv_label_create(day_cont[i + 1]);
//         lv_obj_set_style_text_font(weather_app->label_max_temp[i], &lv_font_montserrat_18, 0);
//         lv_obj_align_to(weather_app->label_max_temp[i], weather_app->bar_weather[i], LV_ALIGN_OUT_RIGHT_MID, 5, 0);
//         lv_label_set_text(weather_app->label_max_temp[i], "35°");
//         lv_obj_set_style_text_color(weather_app->label_max_temp[i], lv_color_white(), 0);

//         lv_bar_set_start_value(weather_app->bar_weather[i], -25, LV_ANIM_ON);
//         lv_bar_set_value(weather_app->bar_weather[i], 35, LV_ANIM_ON);
//     }

//     lv_group_add_obj(weather_app->group, weather_app->btn_return);
//     lv_group_add_obj(weather_app->group, weather_app->root);
//     // 添加事件回调以处理编码器返回
//     // lv_obj_add_event_cb(weather_app->root, btn_return_cb, LV_EVENT_CLICKED, NULL); // 处理返回事件

//     if (xSemaphoreGive(xBinarySemaphore) == pdTRUE)
//     {
//         printf("btn clicked\n");
//     }
//     // update_weather_data();
// }
