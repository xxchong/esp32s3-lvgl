#include "sys.h"

#define TAG "DOUBAO_API"
#define API_URL "http://ark.cn-beijing.volces.com/api/v3/chat/completions"
#define API_KEY "Bearer 6c08f4da-bae0-4acf-b0da-2b863fd36a4b"
#define MODEL_ID "ep-20250107145907-w88pn"

// 添加全局缓冲区指针和长度
static char *g_response_buffer = NULL;
static size_t g_buffer_size = 0;
static size_t g_response_len = 0;

// HTTP 事件处理回调函数
static esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    static char *output_buffer;  // Buffer to store response of http request
    static int output_len;       // Stores number of bytes read
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            // ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            // ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            // ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            // ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            // ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            // 确保不会溢出
            if (g_response_len + evt->data_len < g_buffer_size) {
                memcpy(g_response_buffer + g_response_len, evt->data, evt->data_len);
                g_response_len += evt->data_len;
                g_response_buffer[g_response_len] = 0; // 确保字符串结束
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
            // ESP_LOGI(TAG, "Response: %s", g_response_buffer);
            break;
        case HTTP_EVENT_DISCONNECTED:
            // ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            break;
        case HTTP_EVENT_REDIRECT:
            // ESP_LOGI(TAG, "HTTP_EVENT_REDIRECT");
            break;
        default:
            // ESP_LOGI(TAG, "HTTP_EVENT_UNKNOWN: %d", evt->event_id);
            break;
    }
    return ESP_OK;
}

/* 创建doubao请求体*/
char * create_doubao_request_body(const char *message)
{
    cJSON *root = cJSON_CreateObject();  //创建一个json对象
    cJSON *messages = cJSON_CreateArray();  //创建一个消息数组

    // 添加system消息
    cJSON *system_msg = cJSON_CreateObject();  //创建一个system消息对象
    cJSON_AddStringToObject(system_msg, "role", "system");
    cJSON_AddStringToObject(system_msg, "content", "You are a helpful assistant.");
    cJSON_AddItemToArray(messages, system_msg);  //将system消息对象添加到消息数组中
    
    // 添加user消息
    cJSON *user_msg = cJSON_CreateObject();
    cJSON_AddStringToObject(user_msg, "role", "user");
    cJSON_AddStringToObject(user_msg, "content", message);
    cJSON_AddItemToArray(messages, user_msg); //user消息对象添加到消息数组中

    cJSON_AddStringToObject(root, "model", MODEL_ID);  //模型ID添加到根对象中
    cJSON_AddItemToObject(root, "messages", messages); //消息数组添加到根对象中
    cJSON_AddBoolToObject(root, "stream", false);       //  stream 字段

    char *request_body = cJSON_Print(root);
    cJSON_Delete(root);
    return request_body;
}



esp_err_t chat_with_doubao(const char *message, char *response_buffer, size_t buffer_size) {
    // 设置全局变量
    g_response_buffer = response_buffer;
    g_buffer_size = buffer_size;
    g_response_len = 0;
    memset(g_response_buffer, 0, buffer_size);  // 清空缓冲区
    
    esp_http_client_config_t config = {
        .url = API_URL,
        .method = HTTP_METHOD_POST,
        .transport_type = HTTP_TRANSPORT_OVER_TCP,
        .timeout_ms = 20000,
        .event_handler = _http_event_handler,  // 添加事件处理器
    };
    
    esp_http_client_handle_t client = esp_http_client_init(&config);
    if (client == NULL) {
        ESP_LOGE(TAG, "Failed to initialize HTTP client");
        return ESP_FAIL;
    }
    
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_header(client, "Authorization", API_KEY);
    
    char *request_body = create_doubao_request_body(message);
    ESP_LOGI(TAG, "Request body: %s", request_body);
    esp_http_client_set_post_field(client, request_body, strlen(request_body));
    
    esp_err_t err = esp_http_client_perform(client);
    ESP_LOGI(TAG, "HTTP perform result: %d", err);
    
    if (err == ESP_OK) {
        int status_code = esp_http_client_get_status_code(client);
        ESP_LOGI(TAG, "HTTP Status Code: %d", status_code);
        
        if (status_code == 200) {
            ESP_LOGI(TAG, "Response received, length: %d", g_response_len);
            free(request_body);
            esp_http_client_cleanup(client);
            return ESP_OK;
        }
    }
    
    ESP_LOGE(TAG, "Failed to get response: %s", esp_err_to_name(err));
    free(request_body);
    esp_http_client_cleanup(client);
    return ESP_FAIL;
}




void Doubao_Prase_Json(char *response)
{
    cJSON *root = cJSON_Parse(response);
    if (root == NULL) {
        ESP_LOGE(TAG, "JSON解析错误");
        return;
    }

    // 获取 choices 数组
    cJSON *choices = cJSON_GetObjectItem(root, "choices");
    if (choices && cJSON_IsArray(choices)) {
        // 获取第一个选项
        cJSON *first_choice = cJSON_GetArrayItem(choices, 0);
        if (first_choice) {
            // 获取 message 对象
            cJSON *message = cJSON_GetObjectItem(first_choice, "message");
            if (message) {
                // 从 message 中获取 content
                cJSON *content = cJSON_GetObjectItem(message, "content");
                if (content && cJSON_IsString(content)) {
                    ESP_LOGI(TAG, "content: %s", content->valuestring);
                }
            }
        }
    }

    cJSON_Delete(root);
}
