#include "sys.h"

#define TAG "DOUBAO_API"
#define API_URL "http://ark.cn-beijing.volces.com/api/v3/chat/completions"
#define API_KEY "Bearer 6c08f4da-bae0-4acf-b0da-2b863fd36a4b"
#define MODEL_ID "ep-20250107145907-w88pn"


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
    cJSON_AddBoolToObject(root, "stream", true);       //  stream 字段

    char *request_body = cJSON_Print(root);
    cJSON_Delete(root);
    return request_body;
}



esp_err_t chat_with_doubao(const char *message, char *response_buffer, size_t buffer_size) {
    esp_http_client_config_t config = {
        .url = API_URL,
        .method = HTTP_METHOD_POST,
        .cert_pem = NULL,
        .skip_cert_common_name_check = true,
        .transport_type = HTTP_TRANSPORT_OVER_SSL,
        
    };
    
    ESP_LOGI(TAG, "Initializing HTTP client...");
    esp_http_client_handle_t client = esp_http_client_init(&config);
    if (client == NULL) {
        ESP_LOGE(TAG, "Failed to initialize HTTP client");
        return ESP_FAIL;
    }
    
    ESP_LOGI(TAG, "Setting headers...");
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_header(client, "Authorization", API_KEY);
    
    ESP_LOGI(TAG, "Creating request body...");
    char *request_body = create_doubao_request_body(message);
    esp_http_client_set_post_field(client, request_body, strlen(request_body));
    
    ESP_LOGI(TAG, "Performing request...");
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        int status_code = esp_http_client_get_status_code(client);
        if (status_code == 200) {
            // 读取响应
            int content_length = esp_http_client_get_content_length(client);
            if (content_length <= buffer_size) {
                int read_len = esp_http_client_read(client, response_buffer, buffer_size);
                response_buffer[read_len] = 0;  // Null terminate
            } else {
                ESP_LOGE(TAG, "Response buffer too small");
                err = ESP_FAIL;
            }
        } else {
            ESP_LOGE(TAG, "HTTP request failed with status code: %d", status_code);
            err = ESP_FAIL;
        }
    }
    
    // 清理资源
    free(request_body);
    esp_http_client_cleanup(client);
    return err;
}