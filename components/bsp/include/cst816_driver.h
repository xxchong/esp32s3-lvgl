
#ifndef _CST816_DRIVER_H_
#define _CST816_DRIVER_H_

#include "driver/gpio.h"
#include "esp_err.h"



typedef struct
{
    int16_t x;
    int16_t y;
    int state;
}cst816t_data_t;


esp_err_t touch_driver_init(uint16_t x_limit,uint16_t y_limit);
void cst816t_read(int16_t *x,int16_t *y,int *state);

#endif

