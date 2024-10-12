
#ifndef _BUTTON_DRIVER_H_
#define _BUTTON_DRIVER_H_

#include "driver/gpio.h"
#include "esp_err.h"


void button_driver_init(void);
uint8_t get_button(void);



#endif

