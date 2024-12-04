#ifndef __SETTING_H
#define __SETTING_H

#define SETTING_LIST_COUNT 3

LV_FONT_DECLARE(app_setting_cn_font_16_t);

#define SETTING_LIST_ICON USER_APP_SYMBOL_WIFI, USER_APP_SYMBOL_BT_SETTING, USER_APP_SYMBOL_VERSION

#define SETTING_LIST_NAME "WLAN", "蓝牙", "我的设备"

extern lv_obj_t *setting_list_btns[SETTING_LIST_COUNT]; // 定义列表按钮数组

lv_obj_t *create_setting_app(void);

#endif
