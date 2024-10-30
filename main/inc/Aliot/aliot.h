#ifndef __ALIOT_H
#define __ALIOT_H
#include "esp_err.h"

void mqtt_init(void);
esp_err_t mqtt_publish(const char* topic,const char* data);
esp_err_t mqtt_subscribe(const char* topic);

#endif
