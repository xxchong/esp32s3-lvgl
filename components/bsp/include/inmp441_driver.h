#ifndef __INMP441_DRIVER_H__
#define __INMP441_DRIVER_H__

#include "esp_err.h"
#include "driver/i2s_std.h"

typedef struct {
    i2s_chan_handle_t rx_handle;
    uint32_t sample_rate;
    bool is_initialized;
} inmp441_dev_t;
esp_err_t inmp441_init(uint32_t sample_rate);
esp_err_t inmp441_deinit(void);
esp_err_t inmp441_read_data(uint8_t *data, size_t size);


#endif