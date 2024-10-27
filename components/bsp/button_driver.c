#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_commands.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include "button_driver.h"
#include "lvgl.h"

static const char *TAG = "button_driver";

#define BUTTON_RIGHT_PIN GPIO_NUM_9 // 使用GPIO0作为按钮引脚
#define BUTTON_ENTER_PIN GPIO_NUM_10 // 使用GPIO0作为按钮引脚
#define BUTTON_LEFT_PIN GPIO_NUM_11  // 使用GPIO0作为按钮引脚

static uint8_t last_button_state = 0;

uint8_t get_button(void)
{
    uint8_t current_state = 0;

    if (gpio_get_level(BUTTON_RIGHT_PIN) == 0)
    {
        current_state = 1;
    }
    else if (gpio_get_level(BUTTON_ENTER_PIN) == 0)
    {
        current_state = 2;
    }
    else if (gpio_get_level(BUTTON_LEFT_PIN) == 0)
    {
        current_state = 3;
    }

    if (current_state == 2) // 确认键特殊处理
    {
        ESP_LOGI(TAG, "确认键按下");
        return current_state;
    }

    if (current_state != 0 && current_state != last_button_state)
    {
        last_button_state = current_state;
        switch (current_state)
        {
        case 1:
            ESP_LOGI(TAG, "右键按下");
            break;
        case 3:
            ESP_LOGI(TAG, "左键按下");
            break;
        }
        return current_state;
    }

    if (current_state == 0)
    {
        last_button_state = 0;
    }

    return 0;
}
static void configure_button(void)
{
    gpio_config_t io_conf = {};
    // io_conf.intr_type = GPIO_INTR_NEGEDGE; // 下降沿触发
    io_conf.pin_bit_mask = (1ULL << BUTTON_RIGHT_PIN) | (1ULL << BUTTON_ENTER_PIN) | (1ULL << BUTTON_LEFT_PIN);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_LOGI(TAG, "按键配置完成");
}

void button_driver_init(void)
{
    configure_button();
}
