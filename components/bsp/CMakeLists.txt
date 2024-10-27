idf_component_register(SRCS "wifi_sta.c" "st7789_driver.c" "button_driver.c" "lv_port.c" "sd_driver.c" 
                       INCLUDE_DIRS "include"
                       REQUIRES driver esp_lcd freertos lvgl esp_wifi nvs_flash fatfs vfs lv_fs_if)