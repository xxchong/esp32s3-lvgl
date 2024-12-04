#ifndef __APP_SCREEN_H
#define __APP_SCREEN_H

#define APP_NAMES "Game", "Setting", "Serial", "Music", "Tools", "Calendar", "MQTT", "BlueTooth", "Weather", "Clock"
#define APP_SYMBOL USER_APP_SYMBOL_GAME, USER_APP_SYMBOL_SETTING, USER_APP_SYMBOL_SERIAL, USER_APP_SYMBOL_MUSIC, USER_APP_SYMBOL_TOOLS, USER_APP_SYMBOL_CALENDAR, USER_APP_SYMBOL_MQTT, USER_APP_SYMBOL_BT, USER_APP_SYMBOL_WEATHER, USER_APP_SYMBOL_CLOCK
#define APP_COUNTS 10

extern uint8_t btn_index;
extern lv_obj_t *btns[APP_COUNTS];
extern root_page_t *root_page;

lv_obj_t *create_app_screen(void);
#endif
