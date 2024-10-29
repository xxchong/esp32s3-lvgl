#ifndef WEATHER_HTTP_H
#define WEATHER_HTTP_H

#include "esp_err.h"


// 定义最大缓冲区大小
#define COMPRESSED_BUFFER_SIZE   1024
#define DECOMPRESSED_BUFFER_SIZE 1024

// 和风天气 API 配置
#define WEATHER_API_HOST "devapi.qweather.com"
#define WEATHER_API_KEY "bed78ba604ae417c95529a7fb16a138a"
#define WEATHER_LOCATION "101280108"  // 地区代码

// 天气信息结构体
typedef struct {
    char time[32];
    char temp[8];
    char text[32];
    char icon[8];
} weather_info_t;

// 函数声明
esp_err_t weather_http_init(void);
esp_err_t weather_http_get_data(weather_info_t *info);

#endif // WEATHER_HTTP_H