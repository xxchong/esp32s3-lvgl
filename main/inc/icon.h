
#ifndef ICON_H
#define ICON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"
#define USE_MY_SYMBOL_FONT_10_T
#define USE_MY_SYMBOL_FONT_12_T
#define USE_MY_SYMBOL_FONT_14_T
#define USE_MY_SYMBOL_FONT_16_T
#define USE_MY_SYMBOL_FONT_20_T
#define USE_MY_SYMBOL_FONT_24_T
#define USE_MY_SYMBOL_FONT_28_T
#define USE_MY_SYMBOL_FONT_32_T
#define USE_MY_SYMBOL_FONT_36_T
#define USE_MY_SYMBOL_FONT_40_T
#define USE_ADD_SYMBOL_40_T

#define USE_MUSIC_FONT_22_T

#define USE_WEATHER_SYMBOL_FONT_14_T

#define USE_WEATHER_SYMBOL_FONT_20_T
#define USE_WEATHER_SYMBOL_FONT_30_T

#define USE_WEATHER_SYMBOL_FONT_40_T
#define USE_WEATHER_SYMBOL_FONT_60_T

    /**
     * 音乐图标UTF-8定义
     */
#define USER_SYMBOL_VOLUME "\xEE\x98\x89"   // Unicode: 0xe609  播放器音量
#define USER_SYMBOL_SHUFFLE "\xEE\x98\xA2"  // Unicode: 0xe622  随机播放
#define USER_SYMBOL_REPEAT "\xEE\x98\x82"   // Unicode: 0xe602  单曲循环
#define USER_SYMBOL_PLAYLIST "\xEE\x98\x91" // Unicode: 0xe611  顺序播放
#define USER_SYMBOL_PREV "\xEE\x98\x8A"     // Unicode: 0xe60a  播放器上一首
#define USER_SYMBOL_NEXT "\xEE\x98\x95"     // Unicode: 0xe615  播放器下一首
    /**
     * 天气图标UTF-8定义
     */
#define USER_WEATHER_SYMBOL_100 "\xEF\x84\x81" // Unicode:0xf101
#define USER_WEATHER_SYMBOL_101 "\xEF\x84\x82" // Unicode:0xf102
#define USER_WEATHER_SYMBOL_102 "\xEF\x84\x83" // Unicode:0xf103
#define USER_WEATHER_SYMBOL_103 "\xEF\x84\x84" // Unicode:0xf104
#define USER_WEATHER_SYMBOL_104 "\xEF\x84\x85" // Unicode:0xf105
#define USER_WEATHER_SYMBOL_150 "\xEF\x84\x86" // Unicode:0xf106
#define USER_WEATHER_SYMBOL_151 "\xEF\x84\x87" // Unicode:0xf107
#define USER_WEATHER_SYMBOL_152 "\xEF\x84\x88" // Unicode:0xf108
#define USER_WEATHER_SYMBOL_153 "\xEF\x84\x89" // Unicode:0xf109
#define USER_WEATHER_SYMBOL_300 "\xEF\x84\x8A" // Unicode:0xf10a
#define USER_WEATHER_SYMBOL_301 "\xEF\x84\x8B" // Unicode:0xf10b
#define USER_WEATHER_SYMBOL_302 "\xEF\x84\x8C" // Unicode:0xf10c
#define USER_WEATHER_SYMBOL_303 "\xEF\x84\x8D" // Unicode:0xf10d
#define USER_WEATHER_SYMBOL_304 "\xEF\x84\x8E" // Unicode:0xf10e
#define USER_WEATHER_SYMBOL_305 "\xEF\x84\x8F" // Unicode:0xf10f
#define USER_WEATHER_SYMBOL_306 "\xEF\x84\x90" // Unicode:0xf110
#define USER_WEATHER_SYMBOL_307 "\xEF\x84\x91" // Unicode:0xf111
#define USER_WEATHER_SYMBOL_308 "\xEF\x84\x92" // Unicode:0xf112
#define USER_WEATHER_SYMBOL_309 "\xEF\x84\x93" // Unicode:0xf113
#define USER_WEATHER_SYMBOL_310 "\xEF\x84\x94" // Unicode:0xf114
#define USER_WEATHER_SYMBOL_311 "\xEF\x84\x95" // Unicode:0xf115
#define USER_WEATHER_SYMBOL_312 "\xEF\x84\x96" // Unicode:0xf116
#define USER_WEATHER_SYMBOL_313 "\xEF\x84\x97" // Unicode:0xf117
#define USER_WEATHER_SYMBOL_314 "\xEF\x84\x98" // Unicode:0xf118
#define USER_WEATHER_SYMBOL_315 "\xEF\x84\x99" // Unicode:0xf119
#define USER_WEATHER_SYMBOL_316 "\xEF\x84\x9A" // Unicode:0xf11a
#define USER_WEATHER_SYMBOL_317 "\xEF\x84\x9B" // Unicode:0xf11b
#define USER_WEATHER_SYMBOL_318 "\xEF\x84\x9C" // Unicode:0xf11c
#define USER_WEATHER_SYMBOL_350 "\xEF\x84\x9D" // Unicode:0xf11d
#define USER_WEATHER_SYMBOL_351 "\xEF\x84\x9E" // Unicode:0xf11e
#define USER_WEATHER_SYMBOL_399 "\xEF\x84\x9F" // Unicode:0xf11f
#define USER_WEATHER_SYMBOL_400 "\xEF\x84\xA0" // Unicode:0xf120
#define USER_WEATHER_SYMBOL_401 "\xEF\x84\xA1" // Unicode:0xf121
#define USER_WEATHER_SYMBOL_402 "\xEF\x84\xA2" // Unicode:0xf122
#define USER_WEATHER_SYMBOL_403 "\xEF\x84\xA3" // Unicode:0xf123
#define USER_WEATHER_SYMBOL_404 "\xEF\x84\xA4" // Unicode:0xf124
#define USER_WEATHER_SYMBOL_405 "\xEF\x84\xA5" // Unicode:0xf125
#define USER_WEATHER_SYMBOL_406 "\xEF\x84\xA6" // Unicode:0xf126
#define USER_WEATHER_SYMBOL_407 "\xEF\x84\xA7" // Unicode:0xf127
#define USER_WEATHER_SYMBOL_408 "\xEF\x84\xA8" // Unicode:0xf128
#define USER_WEATHER_SYMBOL_409 "\xEF\x84\xA9" // Unicode:0xf129
#define USER_WEATHER_SYMBOL_410 "\xEF\x84\xAA" // Unicode:0xf12a
#define USER_WEATHER_SYMBOL_456 "\xEF\x84\xAB" // Unicode:0xf12b
#define USER_WEATHER_SYMBOL_457 "\xEF\x84\xAC" // Unicode:0xf12c
#define USER_WEATHER_SYMBOL_499 "\xEF\x84\xAD" // Unicode:0xf12d
#define USER_WEATHER_SYMBOL_500 "\xEF\x84\xAE" // Unicode:0xf12e
#define USER_WEATHER_SYMBOL_501 "\xEF\x84\xAF" // Unicode:0xf12f
#define USER_WEATHER_SYMBOL_502 "\xEF\x84\xB0" // Unicode:0xf130
#define USER_WEATHER_SYMBOL_503 "\xEF\x84\xB1" // Unicode:0xf131
#define USER_WEATHER_SYMBOL_504 "\xEF\x84\xB2" // Unicode:0xf132
#define USER_WEATHER_SYMBOL_507 "\xEF\x84\xB3" // Unicode:0xf133
#define USER_WEATHER_SYMBOL_508 "\xEF\x84\xB4" // Unicode:0xf134
#define USER_WEATHER_SYMBOL_509 "\xEF\x84\xB5" // Unicode:0xf135
#define USER_WEATHER_SYMBOL_510 "\xEF\x84\xB6" // Unicode:0xf136
#define USER_WEATHER_SYMBOL_511 "\xEF\x84\xB7" // Unicode:0xf137
#define USER_WEATHER_SYMBOL_512 "\xEF\x84\xB8" // Unicode:0xf138
#define USER_WEATHER_SYMBOL_513 "\xEF\x84\xB9" // Unicode:0xf139
#define USER_WEATHER_SYMBOL_514 "\xEF\x84\xBA" // Unicode:0xf13a
#define USER_WEATHER_SYMBOL_515 "\xEF\x84\xBB" // Unicode:0xf13b
#define USER_WEATHER_SYMBOL_800 "\xEF\x84\xBC" // Unicode:0xf13c
#define USER_WEATHER_SYMBOL_801 "\xEF\x84\xBD" // Unicode:0xf13d
#define USER_WEATHER_SYMBOL_802 "\xEF\x84\xBE" // Unicode:0xf13e
#define USER_WEATHER_SYMBOL_803 "\xEF\x84\xBF" // Unicode:0xf13f
#define USER_WEATHER_SYMBOL_804 "\xEF\x85\x80" // Unicode:0xf140
#define USER_WEATHER_SYMBOL_805 "\xEF\x85\x81" // Unicode:0xf141
#define USER_WEATHER_SYMBOL_806 "\xEF\x85\x82" // Unicode:0xf142
#define USER_WEATHER_SYMBOL_807 "\xEF\x85\x83" // Unicode:0xf143
#define USER_WEATHER_SYMBOL_900 "\xEF\x85\x84" // Unicode:0xf144
#define USER_WEATHER_SYMBOL_901 "\xEF\x85\x85" // Unicode:0xf145
#define USER_WEATHER_SYMBOL_999 "\xEF\x85\x86" // Unicode:0xf146
    /**
     * 应用图标UTF-8定义
     */

#define USER_SYMBOL_CALENDAR "\xEE\x99\x80" // Unicode: 0xe640
#define USER_SYMBOL_TIME "\xEE\x9A\x92"     // Unicode: 0xe692
#define USER_SYMBOL_WEATHER "\xEE\x99\xA2"  // Unicode: 0xe662

#define USER_SYMBOL_RETURN1 "\xEE\x98\x80"
#define USER_SYMBOL_GAME1 "\xEE\x98\x9E"
#define USER_SYMBOL_SEARCH "\xEE\x98\xA0"
#define USER_SYMBOL_GAME2 "\xEE\x98\xB4"
#define USER_SYMBOL_SETTING "\xEE\x99\xA0"
#define USER_SYMBOL_COM1 "\xEE\x98\xAC"
#define USER_SYMBOL_MUSIC1 "\xEE\x98\x9F"
#define USER_SYMBOL_COM2 "\xEE\x98\x8A"
#define USER_SYMBOL_MUSIC2 "\xEE\x9B\xAE"
#define USER_SYMBOL_TOOLS "\xEE\x99\x88"
#define USER_SYMBOL_DISCONNECT_WIFI "\xEE\x99\xB8"
#define USER_SYMBOL_RETURN2 "\xEE\x98\xA1"
#define USER_SYMBOL_RETURN3 "\xEE\x9A\xAD"
#define USER_SYMBOL_RETURN4 "\xEE\xA0\x80"
#define USER_SYMBOL_GPIO1 "\xEE\x99\xBD"
#define USER_SYMBOL_BLUETOOTH1 "\xEE\xA2\x9C"
#define USER_SYMBOL_MQTT "\xEE\x9B\xB5"
#define USER_SYMBOL_BLUETOOTH2 "\xEE\x98\xB3"
#define USER_SYMBOL_BATTERY "\xEE\x98\xB5"
#define USER_SYMBOL_GPIO2 "\xEE\x98\xB1"
#define USER_SYMBOL_CONNECTEED_WIFI "\xEE\xA3\x81"

#ifdef USE_MUSIC_FONT_22_T
    extern const lv_font_t music_font_22_t; //
#endif

#ifdef USE_WEATHER_SYMBOL_FONT_14_T
    extern const lv_font_t weather_font_14_t; //
#endif

#ifdef USE_WEATHER_SYMBOL_FONT_20_T
    extern const lv_font_t weather_font_20_t; //
#endif

#ifdef USE_WEATHER_SYMBOL_FONT_30_T
    extern const lv_font_t weather_font_30_t; //
#endif

#ifdef USE_WEATHER_SYMBOL_FONT_40_T
    extern const lv_font_t weather_font_40_t; //
#endif

#ifdef USE_WEATHER_SYMBOL_FONT_60_T
    extern const lv_font_t weather_font_60_t; //
#endif

#ifdef USE_ADD_SYMBOL_40_T
    extern const lv_font_t add_symbol_40_t; //
#endif

#ifdef USE_MY_SYMBOL_FONT_10_T
    extern const lv_font_t my_symbol_font_10_t; // ��������
#endif

#ifdef USE_MY_SYMBOL_FONT_12_T
    extern const lv_font_t my_symbol_font_12_t; // ��������
#endif

#ifdef USE_MY_SYMBOL_FONT_14_T
    extern const lv_font_t my_symbol_font_14_t; // ��������
#endif

#ifdef USE_MY_SYMBOL_FONT_16_T
    extern const lv_font_t my_symbol_font_16_t; // ��������
#endif

#ifdef USE_MY_SYMBOL_FONT_18_T
    extern const lv_font_t my_symbol_font_18_t; // ��������
#endif
#ifdef USE_MY_SYMBOL_FONT_20_T
    extern const lv_font_t my_symbol_font_20_t; // ��������
#endif
#ifdef USE_MY_SYMBOL_FONT_24_T
    extern const lv_font_t my_symbol_font_24_t; // ��������
#endif
#ifdef USE_MY_SYMBOL_FONT_28_T
    extern const lv_font_t my_symbol_font_28_t; // ��������
#endif
#ifdef USE_MY_SYMBOL_FONT_32_T
    extern const lv_font_t my_symbol_font_32_t; // ��������
#endif
#ifdef USE_MY_SYMBOL_FONT_36_T
    extern const lv_font_t my_symbol_font_36_t; // ��������
#endif
#ifdef USE_MY_SYMBOL_FONT_40_T
    extern const lv_font_t my_symbol_font_40_t; // ��������
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_TERMINAL_H */
