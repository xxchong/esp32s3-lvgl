#ifndef _SD_DRIVER_H_
#define _SD_DRIVER_H_

#include "esp_log.h"
#include "esp_err.h"


#define MOUNT_POINT "/sdcard" // 定义挂载点

void sdcard_init(void);

esp_err_t write_file_to_sd(const char *filename, const char *data);
esp_err_t read_file_from_sd(const char *filename, char *buffer, size_t buffer_size);
void sd_write_and_read_test(void);
#endif
