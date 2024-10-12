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

static const char* TAG = "button_driver";


#define BUTTON_RIGHT_PIN GPIO_NUM_0  // 使用GPIO0作为按钮引脚
#define BUTTON_ENTER_PIN GPIO_NUM_1  // 使用GPIO0作为按钮引脚
#define BUTTON_LEFT_PIN GPIO_NUM_2  // 使用GPIO0作为按钮引脚

uint8_t get_button(void)
{
    if(gpio_get_level(BUTTON_RIGHT_PIN) == 0)
    {
        return 1;
        ESP_LOGI(TAG, "右键按下");
    }
    else if(gpio_get_level(BUTTON_ENTER_PIN) == 0)
    {
        return 2;
        ESP_LOGI(TAG, "确认键按下");
    }
    else if(gpio_get_level(BUTTON_LEFT_PIN) == 0)
    {
        return 3;
        ESP_LOGI(TAG, "左键按下");
    }
    return 0;
}



static void configure_button(void)
{
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_NEGEDGE;  // 下降沿触发
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




