#ifndef __LV_WEATHER_H
#define __LV_WEATHER_H

// 定义天气图标查找表结构
typedef struct
{
    int weather_id;
    const char *icon_symbol;
} weather_icon_map_t;


// 创建完整的天气图标查找表
static const weather_icon_map_t weather_icons[] = {
    // 晴雨相关
    {100, USER_WEATHER_SYMBOL_100}, // 晴
    {101, USER_WEATHER_SYMBOL_101}, // 多云
    {102, USER_WEATHER_SYMBOL_102}, // 少云
    {103, USER_WEATHER_SYMBOL_103}, // 晴间多云
    {104, USER_WEATHER_SYMBOL_104}, // 阴
    {150, USER_WEATHER_SYMBOL_150}, // 晴
    {151, USER_WEATHER_SYMBOL_151}, // 多云
    {152, USER_WEATHER_SYMBOL_152}, // 少云
    {153, USER_WEATHER_SYMBOL_153}, // 晴间多云

    // 雨相关
    {300, USER_WEATHER_SYMBOL_300}, // 阵雨
    {301, USER_WEATHER_SYMBOL_301}, // 强阵雨
    {302, USER_WEATHER_SYMBOL_302}, // 雷阵雨
    {303, USER_WEATHER_SYMBOL_303}, // 强雷阵雨
    {304, USER_WEATHER_SYMBOL_304}, // 雷阵雨伴有冰雹
    {305, USER_WEATHER_SYMBOL_305}, // 小雨
    {306, USER_WEATHER_SYMBOL_306}, // 中雨
    {307, USER_WEATHER_SYMBOL_307}, // 大雨
    {308, USER_WEATHER_SYMBOL_308}, // 极端降雨
    {309, USER_WEATHER_SYMBOL_309}, // 毛毛雨
    {310, USER_WEATHER_SYMBOL_310}, // 暴雨
    {311, USER_WEATHER_SYMBOL_311}, // 大暴雨
    {312, USER_WEATHER_SYMBOL_312}, // 特大暴雨
    {313, USER_WEATHER_SYMBOL_313}, // 冻雨
    {314, USER_WEATHER_SYMBOL_314}, // 小到中雨
    {315, USER_WEATHER_SYMBOL_315}, // 中到大雨
    {316, USER_WEATHER_SYMBOL_316}, // 大到暴雨
    {317, USER_WEATHER_SYMBOL_317}, // 暴雨到大暴雨
    {318, USER_WEATHER_SYMBOL_318}, // 大暴雨到特大暴雨
    {350, USER_WEATHER_SYMBOL_350}, // 阵雨
    {351, USER_WEATHER_SYMBOL_351}, // 强阵雨
    {399, USER_WEATHER_SYMBOL_399}, // 雨

    // 雪相关
    {400, USER_WEATHER_SYMBOL_400}, // 小雪
    {401, USER_WEATHER_SYMBOL_401}, // 中雪
    {402, USER_WEATHER_SYMBOL_402}, // 大雪
    {403, USER_WEATHER_SYMBOL_403}, // 暴雪
    {404, USER_WEATHER_SYMBOL_404}, // 雨夹雪
    {405, USER_WEATHER_SYMBOL_405}, // 雨雪天气
    {406, USER_WEATHER_SYMBOL_406}, // 阵雨夹雪
    {407, USER_WEATHER_SYMBOL_407}, // 阵雪
    {408, USER_WEATHER_SYMBOL_408}, // 小到中雪
    {409, USER_WEATHER_SYMBOL_409}, // 中到大雪
    {410, USER_WEATHER_SYMBOL_410}, // 大到暴雪
    {456, USER_WEATHER_SYMBOL_456}, // 阵雨夹雪
    {457, USER_WEATHER_SYMBOL_457}, // 阵雪
    {499, USER_WEATHER_SYMBOL_499}, // 雪

    // 特殊天气
    {500, USER_WEATHER_SYMBOL_500}, // 薄雾
    {501, USER_WEATHER_SYMBOL_501}, // 雾
    {502, USER_WEATHER_SYMBOL_502}, // 霾
    {503, USER_WEATHER_SYMBOL_503}, // 扬沙
    {504, USER_WEATHER_SYMBOL_504}, // 浮尘
    {507, USER_WEATHER_SYMBOL_507}, // 沙尘暴
    {508, USER_WEATHER_SYMBOL_508}, // 强沙尘暴
    {509, USER_WEATHER_SYMBOL_509}, // 浓雾
    {510, USER_WEATHER_SYMBOL_510}, // 强浓雾
    {511, USER_WEATHER_SYMBOL_511}, // 中度霾
    {512, USER_WEATHER_SYMBOL_512}, // 重度霾
    {513, USER_WEATHER_SYMBOL_513}, // 严重霾
    {514, USER_WEATHER_SYMBOL_514}, // 大雾
    {515, USER_WEATHER_SYMBOL_515}, // 特强浓雾

    // 其他
    {900, USER_WEATHER_SYMBOL_900}, // 热
    {901, USER_WEATHER_SYMBOL_901}, // 冷
    {999, USER_WEATHER_SYMBOL_999}  // 未知
};

// 获取查找表大小
#define WEATHER_ICONS_SIZE (sizeof(weather_icons) / sizeof(weather_icons[0]))


lv_obj_t *create_weather_app(void);
void update_weather_data(void);

#endif // __cplusplus
