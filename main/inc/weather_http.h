#ifndef WEATHER_HTTP_H
#define WEATHER_HTTP_H

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


// 定义最大缓冲区大小
#define COMPRESSED_BUFFER_SIZE   2048
#define DECOMPRESSED_BUFFER_SIZE 4096

// 和风天气 API 配置
#define WEATHER_API_HOST "devapi.qweather.com"
#define WEATHER_API_KEY "bed78ba604ae417c95529a7fb16a138a"
#define WEATHER_LOCATION "101280108"  // 地区代码
// API路径定义
#define WEATHER_PATH_NOW    "now"     // 实时天气路径
#define WEATHER_PATH_3D     "3d"      // 3天预报路径


// 天气类型枚举
typedef enum {
    WEATHER_TYPE_NOW = 0,
    WEATHER_TYPE_3D,
} weather_type_t;

// 实时天气信息结构体
typedef struct {
    char time[32];
    char temp[8];
    char text[32];
    char icon[8];
    char feels_like[8];
} now_weather_info_t;

// 3天预报天气信息结构体
typedef struct {
    char tempMax[8];
    char tempMin[8];
    char text[32];
    char icon[8];
} three_day_weather_info_t;


#define UPDATE_WEATHER_NOW_DONE_BIT BIT0
#define UPDATE_WEATHER_3D_DONE_BIT BIT1


esp_err_t get_http_data(void);
esp_err_t get_now_weather_data(now_weather_info_t *info);
esp_err_t get_3D_weather_data(three_day_weather_info_t *info);

void start_weather_update(void);
void cleanup_weather_update(void);


bool wait_update_weather_done(TickType_t wait_ticks);

#endif // WEATHER_HTTP_H
