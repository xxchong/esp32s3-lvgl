idf_component_register(SRCS "lv_fs_fatfs.c" "lv_fs_if.c" "lv_fs_pc.c" "lv_fs_posix.c"
                       INCLUDE_DIRS "include"
                       REQUIRES driver freertos lvgl fatfs vfs bsp)