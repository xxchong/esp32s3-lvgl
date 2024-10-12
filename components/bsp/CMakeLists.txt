idf_component_register(SRCS "st7789_driver.c" "button_driver.c" "lv_port.c"
                       INCLUDE_DIRS "include"
                       REQUIRES driver esp_lcd freertos lvgl )

