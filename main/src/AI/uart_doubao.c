#include "driver/uart.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "AI/doubao.h"
#include "esp_log.h"
#include <inttypes.h>
#include "esp_heap_caps.h"
#include "esp_system.h"

#define UART_NUM UART_NUM_0
#define BUF_SIZE 1024
#define PROMPT_MAX_LEN 1024

static const char *TAG = "UART_DOUBAO";

esp_err_t uart_doubao_init(uint32_t baud_rate)
{
    // 配置串口
    uart_config_t uart_config = {
        .baud_rate = baud_rate,
        .data_bits = UART_DATA_8_BITS,       // 8位数据位
        .parity    = UART_PARITY_DISABLE,   // 无校验
        .stop_bits = UART_STOP_BITS_1,    // 1位停止位
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, // 无硬件流控制
        .source_clk = UART_SCLK_DEFAULT,       // 使用默认时钟源
    };
    ESP_ERROR_CHECK(uart_param_config(UART_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 0, NULL, 0));
    
    return ESP_OK;
}


void uart_task(void *pvParameters)
{
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
    char *prompt = (char *) malloc(PROMPT_MAX_LEN);
    size_t prompt_len = 0;
    
    // 分配响应缓冲区在 PSRAM 中
    char *response = (char *)heap_caps_malloc(32768, MALLOC_CAP_SPIRAM);
    if (response == NULL) {
        ESP_LOGE(TAG, "无法在 PSRAM 中分配内存");
        free(data);
        free(prompt);
        return;
    }else
    {
        ESP_LOGI(TAG, "在 PSRAM 中分配内存成功");
    }

    while (1) {
        // 读取串口数据
        int len = uart_read_bytes(UART_NUM, data, BUF_SIZE, pdMS_TO_TICKS(100));
        if (len > 0) {
            // 将接收到的数据追加到提示缓冲区
            for(int i = 0; i < len && prompt_len < PROMPT_MAX_LEN - 1; i++) {
                if(data[i] == '\n' || data[i] == '\r') {
                    if(prompt_len > 0) {
                        // 收到换行符，处理当前提示词
                        prompt[prompt_len] = '\0';
                        ESP_LOGI(TAG, "收到提问: %s", prompt);
                        
                        // 调用豆包 AI
                        esp_err_t err = chat_with_doubao(prompt, response, 32768);
                        if (err == ESP_OK) {
                            // 解析并打印响应
                            Doubao_Prase_Json(response);
                        } else {
                            ESP_LOGE(TAG, "与 AI 对话失败");
                        }
                        
                        // 重置提示缓冲区
                        prompt_len = 0;
                    }
                } else {
                    prompt[prompt_len++] = data[i];
                }
            }
        }
    }
    
    // 清理资源
    heap_caps_free(response);
    free(data);
    free(prompt);
}


void create_uart_doubao_task(void)
{
    xTaskCreatePinnedToCore(uart_task, "uart_task", 8192, NULL, 5, NULL,0);
}




   