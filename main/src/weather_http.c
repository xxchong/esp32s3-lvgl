#include <string.h>
#include <stdlib.h>
#include "esp_log.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_http_client.h"
#include "esp_tls.h"
#include "cJSON.h"
#include "weather_http.h"
#include "uzlib/include/uzlib.h"
static const char *TAG = "WEATHER_HTTP";

// 响应数据缓冲区
static char weather_url[256];
static uint8_t compressed_buffer[COMPRESSED_BUFFER_SIZE];  // 压缩缓冲区
static uint8_t decompressed_buffer[DECOMPRESSED_BUFFER_SIZE]; // 解压缩缓冲区

// HTTP 事件处理函数
static esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    static int output_len = 0;  // 用于跟踪已接收的数据长度
    switch (evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGE(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
            output_len = 0;  // 重置输出长度
            memset(compressed_buffer, 0, COMPRESSED_BUFFER_SIZE);  // 清空缓冲区
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", 
                     evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {  // 检查是否是分块传输
                if (output_len + evt->data_len <= COMPRESSED_BUFFER_SIZE - 1) {
                    memcpy(compressed_buffer + output_len, evt->data, evt->data_len);
                    output_len += evt->data_len;
                    compressed_buffer[output_len] = 0;
                    ESP_LOGI(TAG, "Accumulated data length: %d", output_len);
                } else {
                    ESP_LOGE(TAG, "Buffer full! output_len=%d, new_len=%d", output_len, evt->data_len);
                    return ESP_FAIL;
                }
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            break;
        default:
            ESP_LOGI(TAG, "Unhandled event: %d", evt->event_id);
            break;
    }
    return ESP_OK;
}

// 解压缩函数
static int decompress_data(const uint8_t *compressed_data, size_t compressed_size, 
                         uint8_t *output_buffer, size_t output_size) 
{
    // 跳过gzip头（通常是10字节）
    const int GZIP_HEADER_SIZE = 10;
    if (compressed_size <= GZIP_HEADER_SIZE) {
        ESP_LOGE(TAG, "Compressed data too small");
        return -1;
    }

    // 初始化解压缩状态
    struct uzlib_uncomp d;
    uzlib_uncompress_init(&d, NULL, 0);

    // 设置源和目标缓冲区，跳过gzip头
    d.source = compressed_data + GZIP_HEADER_SIZE;
    d.source_limit = compressed_data + compressed_size - 8;  // 减去8字节的gzip尾部
    d.dest = output_buffer;
    d.dest_limit = output_buffer + output_size;

    // 执行解压缩
    while (1) {
        int res = uzlib_uncompress(&d);
        if (res == TINF_DONE) break;
        if (res != TINF_OK) {
            ESP_LOGE(TAG, "Decompression failed with error: %d", res);
            return -1;
        }
        // 检查是否还有空间
        if (d.dest >= d.dest_limit) {
            ESP_LOGE(TAG, "Output buffer full");
            return -1;
        }
    }

    return d.dest - output_buffer;
}

// 解析实时的JSON数据
static void parse_now_weather_json(const char *json_data, now_weather_info_t *info) 
{
    if (!info || !json_data) return;

    cJSON *root = cJSON_Parse(json_data);
    if (root == NULL) {
        ESP_LOGE(TAG, "JSON parsing error");
        return;
    }
    // 获取updateTime
    cJSON *updateTime = cJSON_GetObjectItem(root, "updateTime");
        if (updateTime && updateTime->valuestring) {
        char *time_ptr = strstr(updateTime->valuestring, "T");
        if (time_ptr) {
            // 跳过'T'字符，复制后面的5个字符（HH:mm）
            strncpy(info->time, time_ptr + 1, 5);
            info->time[5] = '\0';  // 确保字符串结束
        } else {
            strncpy(info->time, updateTime->valuestring, sizeof(info->time) - 1);
            info->time[sizeof(info->time) - 1] = '\0';
        }
    }
    // 获取now对象中的数据
    cJSON *now = cJSON_GetObjectItem(root, "now");
    if (now) {
        cJSON *temp = cJSON_GetObjectItem(now, "temp");
        cJSON *text = cJSON_GetObjectItem(now, "text");
        cJSON *icon = cJSON_GetObjectItem(now, "icon");
        cJSON *feels_like = cJSON_GetObjectItem(now, "feelsLike");

        if (temp && temp->valuestring) {
            strncpy(info->temp, temp->valuestring, sizeof(info->temp) - 1);
            info->temp[sizeof(info->temp) - 1] = '\0';
        }
        if (text && text->valuestring) {
            strncpy(info->text, text->valuestring, sizeof(info->text) - 1);
            info->text[sizeof(info->text) - 1] = '\0';
        }
        if (icon && icon->valuestring) {
            strncpy(info->icon, icon->valuestring, sizeof(info->icon) - 1);
            info->icon[sizeof(info->icon) - 1] = '\0';
        }
        if (feels_like && feels_like->valuestring) {
            strncpy(info->feels_like, feels_like->valuestring, sizeof(info->feels_like) - 1);
            info->feels_like[sizeof(info->feels_like) - 1] = '\0';
        }
    }
    // 释放JSON解析使用的内存
    cJSON_Delete(root);
}



// 解析3天的JSON数据
static void parse_3D_weather_json(const char *json_data, three_day_weather_info_t *info) 
{
    if (!info || !json_data) return;

    cJSON *root = cJSON_Parse(json_data);
    if (root == NULL) {
        ESP_LOGE(TAG, "JSON parsing error");
        return;
    }

    // 获取daily数组
    cJSON *daily = cJSON_GetObjectItem(root, "daily");
    if (daily && cJSON_IsArray(daily)) {
        // 遍历最多3天的数据
        int days = cJSON_GetArraySize(daily);
        days = (days > 3) ? 3 : days;  // 确保不超过3天
        
        for (int i = 0; i < days; i++) {
            cJSON *day = cJSON_GetArrayItem(daily, i);
            if (day) {
           
                // 获取最高温度
                cJSON *tempMax = cJSON_GetObjectItem(day, "tempMax");
                if (tempMax && tempMax->valuestring) {
                    strncpy(info[i].tempMax, tempMax->valuestring, sizeof(info[i].tempMax) - 1);
                }
                // 获取最低温度
                cJSON *tempMin = cJSON_GetObjectItem(day, "tempMin");
                if (tempMin && tempMin->valuestring) {
                    strncpy(info[i].tempMin, tempMin->valuestring, sizeof(info[i].tempMin) - 1);
                }
                // 获取白天天气文本
                cJSON *textDay = cJSON_GetObjectItem(day, "textDay");
                if (textDay && textDay->valuestring) {
                    strncpy(info[i].text, textDay->valuestring, sizeof(info[i].text) - 1);
                }
                // 获取白天天气图标
                cJSON *iconDay = cJSON_GetObjectItem(day, "iconDay");
                if (iconDay && iconDay->valuestring) {
                    strncpy(info[i].icon, iconDay->valuestring, sizeof(info[i].icon) - 1);
                }
            }
        }
    }
    // 释放JSON解析使用的内存
    cJSON_Delete(root);
}

// 初始化天气HTTP客户端
// 2. URL构建时明确指定协议
esp_err_t weather_http_init(weather_type_t type)
{
    memset(weather_url, 0, sizeof(weather_url));
    const char *path = (type == WEATHER_TYPE_NOW) ? WEATHER_PATH_NOW : WEATHER_PATH_3D;
    
    int ret = snprintf(weather_url, sizeof(weather_url),
                      "https://%s/v7/weather/%s?location=%s&key=%s",
                      WEATHER_API_HOST, path, WEATHER_LOCATION, WEATHER_API_KEY);
                      
    if (ret < 0 || ret >= sizeof(weather_url)) {
        ESP_LOGE(TAG, "URL buffer overflow");
        return ESP_FAIL;
    }
    
    ESP_LOGI(TAG, "Weather URL: %s", weather_url);  // 打印URL进行调试
    return ESP_OK;
}

esp_err_t get_http_data(void)
{
    esp_http_client_config_t config = {
            .url = weather_url,
            .transport_type = HTTP_TRANSPORT_OVER_SSL,
            .event_handler = _http_event_handler,
            .user_data = compressed_buffer,
            .buffer_size = COMPRESSED_BUFFER_SIZE,
            .timeout_ms = 5000,
            .skip_cert_common_name_check = true,
        };

     esp_http_client_handle_t client = esp_http_client_init(&config);
    if (client == NULL) {
        return ESP_FAIL;
    }

    esp_http_client_set_header(client, "Accept", "application/json");
    esp_http_client_set_header(client, "Accept-Encoding", "gzip");

    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        int status_code = esp_http_client_get_status_code(client);
        int content_length = esp_http_client_get_content_length(client);
        
        if (status_code == 200 && content_length > 0) {
            // 解压数据
            int decompressed_length = decompress_data(
                compressed_buffer, 
                content_length,
                decompressed_buffer,
                sizeof(decompressed_buffer)
            );
            if (decompressed_length > 0) {
                // 确保字符串结束
                decompressed_buffer[decompressed_length] = '\0';
            }
        }
    }
    esp_http_client_cleanup(client);
    return err;
}



// 获取实时的天气数据
esp_err_t get_now_weather_data(now_weather_info_t *info)
{
    if (!info) return ESP_ERR_INVALID_ARG;
    weather_http_init(WEATHER_TYPE_NOW);
    if (get_http_data() == ESP_OK) {
        // 解析JSON数据
        parse_now_weather_json((char *)decompressed_buffer, info);
        printf("now_weather_data: %s\n", info->temp);
        printf("now_weather_data: %s\n", info->text);
        printf("now_weather_data: %s\n", info->icon);
        printf("now_weather_data: %s\n", info->feels_like);
        printf("now_weather_data: %s\n", info->time);

         return ESP_OK;
    }
    return ESP_FAIL;
}

// 获取3天的天气数据
esp_err_t get_3D_weather_data(three_day_weather_info_t *info)
{
    if (!info) return ESP_ERR_INVALID_ARG;
    weather_http_init(WEATHER_TYPE_3D);
    if (get_http_data() == ESP_OK) {
        // 解析JSON数据
        parse_3D_weather_json((char *)decompressed_buffer, info);
        printf("3D_weather_data: %s\n", info[0].tempMax);
        printf("3D_weather_data: %s\n", info[0].tempMin);
        printf("3D_weather_data: %s\n", info[0].text);
        printf("3D_weather_data: %s\n", info[0].icon);
        printf("3D_weather_data: %s\n", info[1].tempMax);
        printf("3D_weather_data: %s\n", info[1].tempMin);
        printf("3D_weather_data: %s\n", info[1].text);
        printf("3D_weather_data: %s\n", info[1].icon);
        printf("3D_weather_data: %s\n", info[2].tempMax);
        printf("3D_weather_data: %s\n", info[2].tempMin);
        printf("3D_weather_data: %s\n", info[2].text);
        printf("3D_weather_data: %s\n", info[2].icon);
         return ESP_OK;
    }
    return ESP_FAIL;
}