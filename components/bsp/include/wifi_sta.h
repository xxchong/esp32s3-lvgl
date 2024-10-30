#ifndef _WIFI_STA_H_
#define _WIFI_STA_H_
#include "esp_err.h"
#include "stdbool.h"

// WIFI STA初始化
esp_err_t wifi_sta_init(void);
bool is_wifi_connected(void);
#endif
