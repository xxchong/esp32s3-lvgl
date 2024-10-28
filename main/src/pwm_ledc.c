#include <esp_log.h>
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_err.h"

#define LED_GPIO  GPIO_NUM_15   //屏幕背光

#define TAG     "LEDC"


#define LEDC_TIMER              LEDC_TIMER_0            //定时器0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE     //低速模式
#define LEDC_OUTPUT_IO          (LED_GPIO)              //选择GPIO端口
#define LEDC_CHANNEL            LEDC_CHANNEL_0          //PWM通道
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT       //分辨率
#define LEDC_DUTY               (4095)                  //最大占空比值，这里是2^13-1
#define LEDC_FREQUENCY          (5000)                  //PWM周期


// 初始化 LEDC
void ledc_init(void)
{
    // 准备 LEDC 定时器配置
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,//模式
        .timer_num        = LEDC_TIMER,//定时器
        .duty_resolution  = LEDC_DUTY_RES,//分辨率
        .freq_hz         = LEDC_FREQUENCY,//频率
        .clk_cfg         = LEDC_AUTO_CLK //自动时钟
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // 准备 LEDC 通道配置
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE, //模式 
        .channel        = LEDC_CHANNEL,//通道
        .timer_sel      = LEDC_TIMER,//定时器
        .intr_type      = LEDC_INTR_DISABLE,//中断
        .gpio_num       = LED_GPIO,//GPIO
        .duty           = 8191, // 初始占空比设为0
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

}



// 设置背光亮度 (0-100)
void set_backlight(uint8_t brightness)
{
    // 将 0-100 的值映射到 13 位分辨率 (0-8191)
    uint32_t duty = (8191 * brightness) / 100;
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
    ESP_LOGI(TAG, "设置背光亮度: %d%%", brightness);
}