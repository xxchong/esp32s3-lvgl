#ifndef __APP_SCREEN_H
#define __APP_SCREEN_H

#define APP_NAMES "Game", "Setting", "Serial", "Music", "Tools", "Calendar", "MQTT", "BlueTooth", "Weather"
#define APP_SYMBOL USER_SYMBOL_GAME2, USER_SYMBOL_SETTING, USER_SYMBOL_COM1, USER_SYMBOL_MUSIC2, USER_SYMBOL_TOOLS, USER_SYMBOL_CALENDAR, USER_SYMBOL_MQTT, USER_SYMBOL_BLUETOOTH1, USER_SYMBOL_WEATHER
#define APP_COUNTS 9

extern uint8_t btn_index;
extern lv_obj_t *btns[APP_COUNTS];
extern root_page_t *root_page;

lv_obj_t *create_app_screen(void);
#endif
