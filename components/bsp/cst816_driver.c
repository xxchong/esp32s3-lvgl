#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "cst816_driver.h"
static const char *TAG = "cst816t";

#define TOUCH_I2C_PORT  I2C_NUM_0  // I2C0
#define CST816T_ADDR    0x15
#define CST816T_SDA  GPIO_NUM_41
#define CST816T_SCL  GPIO_NUM_42

static esp_err_t i2c_read_reg(uint8_t reg_addr, uint8_t *data, size_t len);
esp_err_t cst816t_init(void);

//边界值
static uint16_t s_usLimitX = 0;
static uint16_t s_usLimitY = 0;



esp_err_t touch_driver_init(uint16_t x_limit,uint16_t y_limit)
{
    s_usLimitX = x_limit;
    s_usLimitY = y_limit;
    cst816t_init();
    return ESP_OK;
}







esp_err_t cst816t_init(void)
{
    i2c_config_t conf = {
        .mode               = I2C_MODE_MASTER,
        .sda_io_num         = CST816T_SDA,
        .sda_pullup_en      = GPIO_PULLUP_ENABLE,
        .scl_io_num         = CST816T_SCL,
        .scl_pullup_en      = GPIO_PULLUP_ENABLE,
        .master.clk_speed   = 400000,
    };


    ESP_ERROR_CHECK(i2c_param_config(TOUCH_I2C_PORT, &conf)); // 配置I2C参数
    ESP_ERROR_CHECK(i2c_driver_install(TOUCH_I2C_PORT, conf.mode, 0, 0, 0)); // 安装I2C驱动

    return ESP_OK;
}


void cst816t_read(int16_t *x,int16_t *y,int *state)
{
    uint8_t data_x[2];        
    uint8_t data_y[2];       
    uint8_t touch_pnt_cnt = 0;  // 触摸点数量
    static int16_t last_x = 0;  // 12位数据
    static int16_t last_y = 0;  // 12位数据
    i2c_read_reg(0x02,&touch_pnt_cnt,1);
    if (touch_pnt_cnt != 1) {    // 忽略无触摸或多点触摸
        *x = last_x;
        *y = last_y;
        *state = 0;
        return;
    }

    //读取X坐标
    i2c_read_reg(0x03, data_x, 2);

    //读取Y坐标
    i2c_read_reg(0x05, data_y, 2);

    //数据12bit
    int16_t current_x = ((data_x[0] & 0x0F) << 8) | (data_x[1] & 0xFF); 
    int16_t current_y = ((data_y[0] & 0x0F) << 8) | (data_y[1] & 0xFF); 

    if(last_x != current_x || current_y != last_y)
    {
        last_x = current_x;
        last_y = current_y;
        ESP_LOGI(TAG,"touch x:%d,y:%d",last_x,last_y);
    }


    if(last_x >= s_usLimitX)
        last_x = s_usLimitX - 1;
    if(last_y >= s_usLimitY)
        last_y = s_usLimitY - 1;

    *x = last_x;
    *y = last_y;
    *state = 1;
}


// 根据寄存器地址读取N字节
static esp_err_t i2c_read_reg(uint8_t reg_addr, uint8_t *data, size_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    if(cmd == NULL)
    {
        ESP_LOGE(TAG, "i2c_cmd_link_create failed");
        return ESP_FAIL;
    }

    // 第一阶段：写入寄存器地址
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (CST816T_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);

    // 第二阶段：读取数据
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (CST816T_ADDR << 1) | I2C_MASTER_READ, true);
    
    // 读取多个字节
    for(int i = 0; i < len; i++) {
        if(i == len - 1) {
            i2c_master_read_byte(cmd, &data[i], I2C_MASTER_NACK);  // 最后一个字节发送NACK
        } else {
            i2c_master_read_byte(cmd, &data[i], I2C_MASTER_ACK);   // 其他字节发送ACK
        }
    }

    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(TOUCH_I2C_PORT, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}