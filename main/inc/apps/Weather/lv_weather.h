#ifndef __LV_WEATHER_H
#define __LV_WEATHER_H

#include "icon.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // 声明一个不透明指针类型来表示天气图标映射
    typedef struct WeatherIconMap WeatherIconMap;

    // 创建和销毁映射的函数
    WeatherIconMap *create_weather_icon_map(void);
    void destroy_weather_icon_map(WeatherIconMap *map);

    // 操作映射的函数
    void weather_icon_map_set(WeatherIconMap *map, int key, const char *value);
    const char *weather_icon_map_get(WeatherIconMap *map, int key);

    void create_weather_app(lv_obj_t *parent);
    void update_weather_data(void);

#ifdef __cplusplus
}
#endif

#endif