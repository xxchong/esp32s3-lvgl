#ifndef __SETTING_H
#define __SETTING_H

#define SETTING_LIST_COUNT 3

#define SETTING_LIST_ICON LV_SYMBOL_WIFI, LV_SYMBOL_WIFI, LV_SYMBOL_WIFI

#define SETTING_LIST_NAME "WiFi1", "WiFi2", "WiFi3"

extern lv_obj_t *setting_list_btns[SETTING_LIST_COUNT]; // 定义列表按钮数组

void create_setting_app(lv_obj_t *parent);

#endif
