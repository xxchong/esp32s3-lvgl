#ifndef _LV_PORT_H_
#define _LV_PORT_H_

#include "lvgl.h"

extern lv_indev_t *button_indev;
esp_err_t lv_port_init(void);

#endif