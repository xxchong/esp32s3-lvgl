#ifndef __SYS_H
#define __SYS_H

#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"
#include "fragment.h"
#include "icon.h"
#include "Notification.h"
#include "status_bar.h"
#include "util.h"
#include "apps/BlueTooth/BlueTooth.h"
#include "apps/Music/Music.h"
#include "apps/Game/Game.h"
#include "apps/Calender/Calender.h"
#include "apps/MQTT/MQTT.h"
#include "apps/Setting/Setting.h"
#include "apps/Setting/WiFi_Connection.h"

#include "apps/Serial/Serial.h"
#include "apps/Tools/Tools.h"
#include "apps/Tools/Calculators/Calculators.h"
#include "apps/Tools/Calculators/Calculators1.h"
#include "apps/Tools/Calculators/Calculators2.h"

#include "apps/Weather/lv_weather.h"
#include "apps/my_widgets/clock_widget/clock_widget.h"
#include "apps/my_widgets/weather_widget/weather_widget.h"
#include "apps/my_widgets/wooden_fish_widget/wooden_fish.h"
#include "lv_port.h"
#include "root_page.h"
#include "pwm_ledc.h"
#include "weather_http.h"
#include "apps/Game/Tetris.h"
#include <stdbool.h>
#include <time.h>


#include "desktop_clock_1.h"
#include "desktop_clock_2.h"

#include "desktop_clock_3.h"

#include "desktop_clock_4.h"
#include "Version.h"

#define USE_ENCODER_BY_BUTTON 1

typedef struct
{
    lv_obj_t *scr;
    lv_obj_t *boot_container;
    lv_obj_t *notification;
} gesture_t;

typedef struct
{
  lv_obj_t *boot_page;
  lv_obj_t *root_page;
  lv_obj_t *bluetooth_page;
  lv_obj_t *mqtt_page;
  lv_obj_t *music_page;
  lv_obj_t *game_page;
  lv_obj_t *weather_page;
  lv_obj_t *tools_page;
  lv_obj_t *calender_page;
  lv_obj_t *serial_page;
  lv_obj_t *setting_page;
  lv_obj_t *notification_page;
  lv_obj_t *calculator_page;
  lv_obj_t *wifi_page;
  lv_obj_t *version_page;
}page_t;
extern gesture_t *lv_gesture;
extern page_t *lv_page;
extern now_weather_info_t now_weather_info;
extern three_day_weather_info_t three_day_weather_info[3];
extern root_page_t *root_page;
extern bool in_weather_app;
#endif
