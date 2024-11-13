#ifndef _MAX98357_DRIVER_H_
#define _MAX98357_DRIVER_H_

#include "esp_log.h"
#include "esp_err.h"
#include "driver/i2s.h"
esp_err_t max98357_init(uint32_t sample_rate);
esp_err_t max98357_write_data(uint8_t *data, size_t size);
esp_err_t max98357_deinit(void);

typedef struct
{
    i2s_chan_handle_t tx_handle;
    uint32_t sample_rate;
    bool is_initialized;
    float volume; // 音量值 0.0 ~ 1.0
} max98357_dev_t;

extern max98357_dev_t *max98357_dev;
#endif
