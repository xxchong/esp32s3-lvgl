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
            if (!esp_http_client_is_chunked_response(evt->client)) {
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

// 解析JSON数据
static void parse_weather_json(const char *json_data, weather_info_t *info) 
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
        strncpy(info->time, updateTime->valuestring, sizeof(info->time) - 1);
        info->time[sizeof(info->time) - 1] = '\0';
    }

    // 获取now对象中的数据
    cJSON *now = cJSON_GetObjectItem(root, "now");
    if (now) {
        cJSON *temp = cJSON_GetObjectItem(now, "temp");
        cJSON *text = cJSON_GetObjectItem(now, "text");
        cJSON *icon = cJSON_GetObjectItem(now, "icon");

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
    }

    // 释放JSON解析使用的内存
    cJSON_Delete(root);
}

// 初始化天气HTTP客户端
esp_err_t weather_http_init(void)
{
    // 构建完整的URL
    snprintf(weather_url, sizeof(weather_url),
             "https://%s/v7/weather/now?location=%s&key=%s",
             WEATHER_API_HOST, WEATHER_LOCATION, WEATHER_API_KEY);
    
    ESP_LOGI(TAG, "Weather HTTP client initialized");
    return ESP_OK;
}

// 获取天气数据
esp_err_t weather_http_get_data(weather_info_t *info)
{
    if (!info) return ESP_ERR_INVALID_ARG;

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
                
                // 解析JSON数据
                parse_weather_json((char *)decompressed_buffer, info);
                
                // 打印提取的数据
                ESP_LOGI(TAG, "Time: %s", info->time);
                ESP_LOGI(TAG, "Temperature: %s°C", info->temp);
                ESP_LOGI(TAG, "Weather: %s", info->text);
                ESP_LOGI(TAG, "Icon: %s", info->icon);
            }
        }
    }

    esp_http_client_cleanup(client);
    return err;
}