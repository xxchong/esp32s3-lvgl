#ifndef _LV_PORT_H_
#define _LV_PORT_H_
#include "esp_err.h" // 添加这行来包含 esp_err_t 的定义

#include "lvgl.h"

extern lv_indev_t *indev;
esp_err_t lv_port_init(void);

#endif