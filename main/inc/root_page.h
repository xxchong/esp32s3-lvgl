#ifndef __ROOT_PAGE_H
#define __ROOT_PAGE_H

typedef struct
{
    lv_obj_t *tileview;
    lv_obj_t *page1;
    lv_obj_t *page2;
    lv_obj_t *label;
} root_page_t;

#define APP_NAMES "Game", "Setting", "Serial", "Music", "Tools", "Calendar", "MQTT", "BlueTooth", "Weather"
#define APP_SYMBOL USER_SYMBOL_GAME2, USER_SYMBOL_SETTING, USER_SYMBOL_COM1, USER_SYMBOL_MUSIC2, USER_SYMBOL_TOOLS, USER_SYMBOL_CALENDAR, USER_SYMBOL_MQTT, USER_SYMBOL_BLUETOOTH1, USER_SYMBOL_WEATHER
#define APP_COUNTS 9

root_page_t *create_root(lv_obj_t *parent);
void create_second_page(void);

#endif
