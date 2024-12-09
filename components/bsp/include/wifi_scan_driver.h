#ifndef __WIFI_SCAN_DRIVER_H
#define __WIFI_SCAN_DRIVER_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define SCAN_DONE_BIT BIT0
#define MAX_WIFI_SSID 30

typedef struct {
    char ssid[33];  // 32字节SSID + 1字节结束符
    int8_t rssi;    // 信号强度
} wifi_scan_result_t;


bool get_wifi_scan_result(char *ssid, int8_t *rssi);
void cleanup_wifi_scan(void);
bool wait_wifi_scan_done(TickType_t wait_ticks);
void start_wifi_scan(void);

#endif
