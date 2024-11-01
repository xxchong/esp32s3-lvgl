#ifndef _WIFI_STA_H_
#define _WIFI_STA_H_
#include "esp_err.h"
#include "stdbool.h"

// WIFI STA初始化
esp_err_t wifi_sta_init(const char *wifi_ssid,const char *pwd);
bool is_wifi_connected(void);
#endif
