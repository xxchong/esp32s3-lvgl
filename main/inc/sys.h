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
#include "apps/GPIO/GPIO.h"
#include "apps/MQTT/MQTT.h"
#include "apps/Setting/Setting.h"
#include "apps/Setting/WiFi_Connection.h"

#include "apps/Serial/Serial.h"
#include "apps/Tools/Tools.h"
#include "apps/Tools/Calculators/Calculators.h"
#include "apps/Tools/Calculators/Calculators1.h"
#include "apps/Tools/Calculators/Calculators2.h"

#include "apps/Weather/lv_weather.h"
#include "apps/widgets/clock_widget/clock_widget.h"
#include "apps/widgets/weather_widget/weather_widget.h"
#include "apps/widgets/wooden_fish_widget/wooden_fish.h"
#include "lv_port.h"
#include "root_page.h"

#include "apps/Game/Tetris.h"
#include <stdbool.h>
#include <time.h>
#define USE_ENCODER_BY_BUTTON 1

#endif
