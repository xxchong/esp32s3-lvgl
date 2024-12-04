#ifndef ICON_H
#define ICON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl/lvgl.h"

#define USE_MUSIC_FONT_22_T
#define USE_WATCH_5_FONT_CN_10_T
#define USE_QWEATHER_FILL_SYMBOL_ICON_30_T
#define USE_QWEATHER_FILL_SYMBOL_ICON_60_T
#define USE_APP_ICON_36_T
#define USE_APP_SETTING_ICON_25_T


   /**
     * watchedUTF-8定义
     */
#define USER_WATCH_5_SYMBOL_BATTERY_STATUS "\xEE\x99\xA5"    // Unicode: 0xe665  电量
#define USER_WATCH_5_SYMBOL_STEPS "\xEE\x9B\xA2"            // Unicode: 0xe6e2  步数
#define USER_WATCH_5_SYMBOL_HEART_RATE "\xEE\x98\x8B"       // Unicode: 0xe60b  心率
#define USER_WATCH_5_SYMBOL_TARGET "\xEE\x99\x95"           // Unicode: 0xe655  目标任务


    /**
     * 音乐图标UTF-8定义
     */
#define USER_SYMBOL_VOLUME "\xEE\x98\x89"   // Unicode: 0xe609  播放器音量
#define USER_SYMBOL_SHUFFLE "\xEE\x98\xA2"  // Unicode: 0xe622  随机播放
#define USER_SYMBOL_REPEAT "\xEE\x98\x82"   // Unicode: 0xe602  单曲循环
#define USER_SYMBOL_PLAYLIST "\xEE\x98\x91" // Unicode: 0xe611  顺序播放
#define USER_SYMBOL_PREV "\xEE\x98\x8A" // Unicode: 0xe60a  播放器上一首
#define USER_SYMBOL_NEXT "\xEE\x98\x95" // Unicode: 0xe615  播放器下一首
    /**
     * 天气图标UTF-8定义
     */
#define USER_WEATHER_SYMBOL_100 "\xEE\xA4\x80" // Unicode:0xe900
#define USER_WEATHER_SYMBOL_101 "\xEE\xA4\x81" // Unicode:0xe901
#define USER_WEATHER_SYMBOL_102 "\xEE\xA4\x82" // Unicode:0xe902
#define USER_WEATHER_SYMBOL_103 "\xEE\xA4\x83" // Unicode:0xe903
#define USER_WEATHER_SYMBOL_104 "\xEE\xA4\x84" // Unicode:0xe904
#define USER_WEATHER_SYMBOL_150 "\xEE\xA4\x85" // Unicode:0xe905
#define USER_WEATHER_SYMBOL_151 "\xEE\xA4\x86" // Unicode:0xe906
#define USER_WEATHER_SYMBOL_152 "\xEE\xA4\x87" // Unicode:0xe907
#define USER_WEATHER_SYMBOL_153 "\xEE\xA4\x88" // Unicode:0xe908
#define USER_WEATHER_SYMBOL_300 "\xEE\xA4\x89" // Unicode:0xe909
#define USER_WEATHER_SYMBOL_301 "\xEE\xA4\x8A" // Unicode:0xe90a
#define USER_WEATHER_SYMBOL_302 "\xEE\xA4\x8B" // Unicode:0xe90b
#define USER_WEATHER_SYMBOL_303 "\xEE\xA4\x8C" // Unicode:0xe90c
#define USER_WEATHER_SYMBOL_304 "\xEE\xA4\x8D" // Unicode:0xe90d
#define USER_WEATHER_SYMBOL_305 "\xEE\xA4\x8E" // Unicode:0xe90e
#define USER_WEATHER_SYMBOL_306 "\xEE\xA4\x8F" // Unicode:0xe90f
#define USER_WEATHER_SYMBOL_307 "\xEE\xA4\x90" // Unicode:0xe910
#define USER_WEATHER_SYMBOL_308 "\xEE\xA4\x91" // Unicode:0xe911
#define USER_WEATHER_SYMBOL_309 "\xEE\xA4\x92" // Unicode:0xe912
#define USER_WEATHER_SYMBOL_310 "\xEE\xA4\x93" // Unicode:0xe913
#define USER_WEATHER_SYMBOL_311 "\xEE\xA4\x94" // Unicode:0xe914
#define USER_WEATHER_SYMBOL_312 "\xEE\xA4\x95" // Unicode:0xe915
#define USER_WEATHER_SYMBOL_313 "\xEE\xA4\x96" // Unicode:0xe916
#define USER_WEATHER_SYMBOL_314 "\xEE\xA4\x97" // Unicode:0xe917
#define USER_WEATHER_SYMBOL_315 "\xEE\xA4\x98" // Unicode:0xe918
#define USER_WEATHER_SYMBOL_316 "\xEE\xA4\x99" // Unicode:0xe919
#define USER_WEATHER_SYMBOL_317 "\xEE\xA4\x9A" // Unicode:0xe91a
#define USER_WEATHER_SYMBOL_318 "\xEE\xA4\x9B" // Unicode:0xe91b
#define USER_WEATHER_SYMBOL_350 "\xEE\xA4\x9C" // Unicode:0xe91c
#define USER_WEATHER_SYMBOL_351 "\xEE\xA4\x9D" // Unicode:0xe91d
#define USER_WEATHER_SYMBOL_399 "\xEE\xA4\x9E" // Unicode:0xe91e
#define USER_WEATHER_SYMBOL_400 "\xEE\xA4\x9F" // Unicode:0xe91f
#define USER_WEATHER_SYMBOL_401 "\xEE\xA4\xA0" // Unicode:0xe920
#define USER_WEATHER_SYMBOL_402 "\xEE\xA4\xA1" // Unicode:0xe921
#define USER_WEATHER_SYMBOL_403 "\xEE\xA4\xA2" // Unicode:0xe922
#define USER_WEATHER_SYMBOL_404 "\xEE\xA4\xA3" // Unicode:0xe923
#define USER_WEATHER_SYMBOL_405 "\xEE\xA4\xA4" // Unicode:0xe924
#define USER_WEATHER_SYMBOL_406 "\xEE\xA4\xA5" // Unicode:0xe925
#define USER_WEATHER_SYMBOL_407 "\xEE\xA4\xA6" // Unicode:0xe926
#define USER_WEATHER_SYMBOL_408 "\xEE\xA4\xA7" // Unicode:0xe927
#define USER_WEATHER_SYMBOL_409 "\xEE\xA4\xA8" // Unicode:0xe928
#define USER_WEATHER_SYMBOL_410 "\xEE\xA4\xA9" // Unicode:0xe929
#define USER_WEATHER_SYMBOL_456 "\xEE\xA4\xAA" // Unicode:0xe92a
#define USER_WEATHER_SYMBOL_457 "\xEE\xA4\xAB" // Unicode:0xe92b
#define USER_WEATHER_SYMBOL_499 "\xEE\xA4\xAC" // Unicode:0xe92c
#define USER_WEATHER_SYMBOL_500 "\xEE\xA4\xAD" // Unicode:0xe92d
#define USER_WEATHER_SYMBOL_501 "\xEE\xA4\xAE" // Unicode:0xe92e
#define USER_WEATHER_SYMBOL_502 "\xEE\xA4\xAF" // Unicode:0xe92f
#define USER_WEATHER_SYMBOL_503 "\xEE\xA4\xB0" // Unicode:0xe930
#define USER_WEATHER_SYMBOL_504 "\xEE\xA4\xB1" // Unicode:0xe931
#define USER_WEATHER_SYMBOL_507 "\xEE\xA4\xB2" // Unicode:0xe932
#define USER_WEATHER_SYMBOL_508 "\xEE\xA4\xB3" // Unicode:0xe933
#define USER_WEATHER_SYMBOL_509 "\xEE\xA4\xB4" // Unicode:0xe934
#define USER_WEATHER_SYMBOL_510 "\xEE\xA4\xB5" // Unicode:0xe935
#define USER_WEATHER_SYMBOL_511 "\xEE\xA4\xB6" // Unicode:0xe936
#define USER_WEATHER_SYMBOL_512 "\xEE\xA4\xB7" // Unicode:0xe937
#define USER_WEATHER_SYMBOL_513 "\xEE\xA4\xB8" // Unicode:0xe938
#define USER_WEATHER_SYMBOL_514 "\xEE\xA4\xB9" // Unicode:0xe939
#define USER_WEATHER_SYMBOL_515 "\xEE\xA4\xBA" // Unicode:0xe93a
#define USER_WEATHER_SYMBOL_900 "\xEE\xA4\xBB" // Unicode:0xe93b
#define USER_WEATHER_SYMBOL_901 "\xEE\xA4\xBC" // Unicode:0xe93c
#define USER_WEATHER_SYMBOL_999 "\xEE\xA4\xBD" // Unicode:0xe93d
    /**
     * 应用图标UTF-8定义
     */

#define USER_APP_SYMBOL_WEATHER "\xEE\xA8\xA7"   // Unicode: 0xea27  天气预报
#define USER_APP_SYMBOL_CLOCK "\xEE\x98\x94"      // Unicode: 0xe614  时间
#define USER_APP_SYMBOL_GAME "\xEE\x98\xB6"      // Unicode: 0xe636  游戏
#define USER_APP_SYMBOL_SETTING "\xEE\x98\x9B"   // Unicode: 0xe61b  设置
#define USER_APP_SYMBOL_CALENDAR "\xEE\x98\x90"  // Unicode: 0xe610  日历
#define USER_APP_SYMBOL_BT "\xEE\x98\xB7"        // Unicode: 0xe637  蓝牙
#define USER_APP_SYMBOL_TOOLS "\xEE\x9A\xA3"     // Unicode: 0xe6a3  工具箱
#define USER_APP_SYMBOL_MUSIC "\xEE\x98\x96"     // Unicode: 0xe616  音乐
#define USER_APP_SYMBOL_MQTT "\xEE\x9A\xAF"      // Unicode: 0xe6af  MQTT
#define USER_APP_SYMBOL_SERIAL "\xEE\x98\x8A"    // Unicode: 0xe60a  串口


/**
 * 应用图标UTF-8定义
 */
/**
 * 系统设置图标UTF-8定义
 */
#define USER_APP_SYMBOL_FIRMWARE "\xEE\x98\x8A"     // Unicode: 0xe60a  固件升级
#define USER_APP_SYMBOL_VERSION "\xEE\x9F\xA5"      // Unicode: 0xe7e5  版本号
#define USER_APP_SYMBOL_WIFI "\xEE\x98\x80"         // Unicode: 0xe600  WIFI
#define USER_APP_SYMBOL_GUIDE "\xEE\x9E\x8E"        // Unicode: 0xe78e  指南
#define USER_APP_SYMBOL_MODEL "\xEE\x9E\xA2"        // Unicode: 0xe7a2  型号
#define USER_APP_SYMBOL_BT_SETTING "\xEE\x98\xAF"   // Unicode: 0xe62f  蓝牙设置
#define USER_APP_SYMBOL_CPU "\xEE\x98\x84"          // Unicode: 0xe604  CPU
#define USER_APP_SYMBOL_OS "\xEE\x9A\x86"           // Unicode: 0xe686  操作系统
#define USER_APP_SYMBOL_SMARTWATCH "\xEE\x98\x85"   // Unicode: 0xe605  圆形智能手表

#ifdef USE_APP_SETTING_ICON_25_T
    extern const lv_font_t app_setting_icon_25_t; //
#endif


#ifdef USE_QWEATHER_FILL_SYMBOL_ICON_30_T
    extern const lv_font_t qweather_icon_fill_30_t; //
#endif

#ifdef USE_QWEATHER_FILL_SYMBOL_ICON_60_T
    extern const lv_font_t qweather_icon_fill_60_t; //
#endif

#ifdef USE_WATCH_5_FONT_CN_10_T
    extern const lv_font_t watch_5_font_icon_10_t; //
#endif


#ifdef USE_MUSIC_FONT_22_T
    extern const lv_font_t music_font_22_t; //
#endif



#ifdef USE_APP_ICON_36_T
    extern const lv_font_t app_icon_36_t; //
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_TERMINAL_H */
