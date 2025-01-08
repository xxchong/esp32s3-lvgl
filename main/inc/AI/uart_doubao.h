#ifndef __UART_DOUBAO_H__
#define __UART_DOUBAO_H__

#include "esp_err.h"
esp_err_t uart_doubao_init(uint32_t baud_rate);
void create_uart_doubao_task(void);


#endif