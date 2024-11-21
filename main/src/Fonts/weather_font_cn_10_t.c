/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: --bpp 1 --size 10 --no-compress --font 微软雅黑.ttf --symbols 广州市海珠区茂名今日明天后天气去预报温度湿度更新近三 --range 32-127 --format lvgl -o weather_font_cn_10_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef WEATHER_FONT_CN_10_T
#define WEATHER_FONT_CN_10_T 1
#endif

#if WEATHER_FONT_CN_10_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfd,

    /* U+0022 "\"" */
    0xf0,

    /* U+0023 "#" */
    0x28, 0xa7, 0xca, 0xfd, 0x45, 0x14,

    /* U+0024 "$" */
    0x22, 0x7a, 0xa6, 0x33, 0x3f, 0x20,

    /* U+0025 "%" */
    0x64, 0x94, 0x98, 0x68, 0x16, 0x19, 0x29, 0x46,

    /* U+0026 "&" */
    0x30, 0x48, 0x4a, 0x32, 0xca, 0x84, 0x8c, 0x73,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x4a, 0x49, 0x24, 0x48,

    /* U+0029 ")" */
    0x48, 0x92, 0x49, 0x48,

    /* U+002A "*" */
    0x23, 0x65,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+002C "," */
    0x68,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x11, 0x22, 0x24, 0x44, 0x88,

    /* U+0030 "0" */
    0x76, 0xe3, 0x18, 0xc7, 0x6e,

    /* U+0031 "1" */
    0xe1, 0x8, 0x42, 0x10, 0x9f,

    /* U+0032 "2" */
    0x70, 0x42, 0x11, 0x11, 0x1f,

    /* U+0033 "3" */
    0xe1, 0x16, 0x11, 0x1e,

    /* U+0034 "4" */
    0x18, 0x62, 0x92, 0x4b, 0xf0, 0x82,

    /* U+0035 "5" */
    0xf8, 0x8e, 0x11, 0x1e,

    /* U+0036 "6" */
    0x3a, 0x21, 0x6c, 0xc6, 0x2e,

    /* U+0037 "7" */
    0xf8, 0x44, 0x22, 0x10, 0x88,

    /* U+0038 "8" */
    0x74, 0x62, 0xed, 0x46, 0x2e,

    /* U+0039 "9" */
    0x74, 0x63, 0x17, 0x84, 0x5c,

    /* U+003A ":" */
    0x84,

    /* U+003B ";" */
    0x40, 0x68,

    /* U+003C "<" */
    0x19, 0x30, 0xc1, 0x80,

    /* U+003D "=" */
    0xf8, 0x3e,

    /* U+003E ">" */
    0x83, 0x6, 0x4c, 0x0,

    /* U+003F "?" */
    0xe1, 0x12, 0x44, 0x4,

    /* U+0040 "@" */
    0x1e, 0x31, 0x97, 0x74, 0x9a, 0x4d, 0x26, 0x97,
    0xbe, 0x60, 0x1e, 0x0,

    /* U+0041 "A" */
    0x10, 0x50, 0xa1, 0x44, 0x4f, 0x91, 0x41,

    /* U+0042 "B" */
    0xf4, 0xa5, 0xc9, 0xc6, 0x3e,

    /* U+0043 "C" */
    0x3d, 0x8, 0x20, 0x82, 0x4, 0x4f,

    /* U+0044 "D" */
    0xf2, 0x28, 0x61, 0x86, 0x18, 0xbc,

    /* U+0045 "E" */
    0xf8, 0x8f, 0x88, 0x8f,

    /* U+0046 "F" */
    0xf8, 0x8f, 0x88, 0x88,

    /* U+0047 "G" */
    0x3d, 0x8, 0x27, 0x86, 0x14, 0x4f,

    /* U+0048 "H" */
    0x86, 0x18, 0x7f, 0x86, 0x18, 0x61,

    /* U+0049 "I" */
    0xe9, 0x24, 0x97,

    /* U+004A "J" */
    0x24, 0x92, 0x4e,

    /* U+004B "K" */
    0x8c, 0xa9, 0x8e, 0x52, 0x51,

    /* U+004C "L" */
    0x88, 0x88, 0x88, 0x8f,

    /* U+004D "M" */
    0xc3, 0xc3, 0xc3, 0xa5, 0xa5, 0x99, 0x99, 0x89,

    /* U+004E "N" */
    0xc7, 0x1a, 0x69, 0x96, 0x58, 0xe1,

    /* U+004F "O" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0050 "P" */
    0xf4, 0x63, 0x1f, 0x42, 0x10,

    /* U+0051 "Q" */
    0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38,
    0x8, 0x7,

    /* U+0052 "R" */
    0xf2, 0x28, 0xa2, 0xf2, 0x48, 0xa3,

    /* U+0053 "S" */
    0x7c, 0x20, 0x83, 0x4, 0x3e,

    /* U+0054 "T" */
    0xf9, 0x8, 0x42, 0x10, 0x84,

    /* U+0055 "U" */
    0x86, 0x18, 0x61, 0x86, 0x1c, 0xde,

    /* U+0056 "V" */
    0x86, 0x89, 0x12, 0x42, 0x85, 0xc, 0x8,

    /* U+0057 "W" */
    0x84, 0x53, 0x14, 0xc9, 0x2a, 0x52, 0x8c, 0xa3,
    0x30, 0xc4,

    /* U+0058 "X" */
    0x45, 0x22, 0x8c, 0x30, 0xa4, 0xb1,

    /* U+0059 "Y" */
    0x8a, 0x25, 0x14, 0x20, 0x82, 0x8,

    /* U+005A "Z" */
    0xfc, 0x21, 0x84, 0x21, 0x84, 0x3f,

    /* U+005B "[" */
    0xea, 0xaa, 0xb0,

    /* U+005C "\\" */
    0x88, 0x44, 0x42, 0x21, 0x11,

    /* U+005D "]" */
    0xd5, 0x55, 0x70,

    /* U+005E "^" */
    0x21, 0x94, 0x98, 0x80,

    /* U+005F "_" */
    0xf0,

    /* U+0060 "`" */
    0x48,

    /* U+0061 "a" */
    0x61, 0x3d, 0x9f,

    /* U+0062 "b" */
    0x84, 0x21, 0x6c, 0xc6, 0x33, 0xf0,

    /* U+0063 "c" */
    0x7c, 0x88, 0xc7,

    /* U+0064 "d" */
    0x8, 0x42, 0xfc, 0xc6, 0x31, 0x78,

    /* U+0065 "e" */
    0x74, 0x7f, 0xc, 0xb8,

    /* U+0066 "f" */
    0x29, 0x74, 0x92, 0x40,

    /* U+0067 "g" */
    0x7e, 0x63, 0x18, 0xbc, 0x33, 0xf0,

    /* U+0068 "h" */
    0x84, 0x21, 0x6c, 0xc6, 0x31, 0x88,

    /* U+0069 "i" */
    0x9f, 0x80,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0xe0,

    /* U+006B "k" */
    0x84, 0x21, 0x2a, 0x63, 0x94, 0x90,

    /* U+006C "l" */
    0xff, 0x80,

    /* U+006D "m" */
    0xef, 0x26, 0x4c, 0x99, 0x32, 0x40,

    /* U+006E "n" */
    0xb6, 0x63, 0x18, 0xc4,

    /* U+006F "o" */
    0x74, 0x63, 0x18, 0xb8,

    /* U+0070 "p" */
    0xb6, 0x63, 0x19, 0xfa, 0x10, 0x80,

    /* U+0071 "q" */
    0x7e, 0x63, 0x18, 0xbc, 0x21, 0x8,

    /* U+0072 "r" */
    0xf2, 0x49, 0x0,

    /* U+0073 "s" */
    0x78, 0xc3, 0x1e,

    /* U+0074 "t" */
    0x4b, 0xa4, 0x93,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xbc,

    /* U+0076 "v" */
    0x8a, 0x54, 0xa5, 0x10,

    /* U+0077 "w" */
    0x99, 0x9a, 0x5a, 0x6a, 0x66, 0x24,

    /* U+0078 "x" */
    0xca, 0x88, 0x45, 0x64,

    /* U+0079 "y" */
    0x8a, 0x54, 0xa3, 0x10, 0x84, 0xc0,

    /* U+007A "z" */
    0xf0, 0x88, 0x84, 0x78,

    /* U+007B "{" */
    0x69, 0x25, 0x12, 0x4c,

    /* U+007C "|" */
    0xff, 0xf0,

    /* U+007D "}" */
    0xc9, 0x24, 0x52, 0x58,

    /* U+007E "~" */
    0xed, 0xc0,

    /* U+007F "" */
    0x0,

    /* U+4E09 "三" */
    0x7f, 0x0, 0x0, 0xf, 0xe0, 0x0, 0x0, 0x1,
    0xff,

    /* U+4ECA "今" */
    0x8, 0x5, 0x2, 0x23, 0x27, 0x0, 0x1f, 0xc0,
    0x10, 0x8, 0x4, 0x0, 0x0,

    /* U+533A "区" */
    0xff, 0xc0, 0x28, 0x92, 0x88, 0xc4, 0xb2, 0x8d,
    0x0, 0xff, 0x80,

    /* U+53BB "去" */
    0x8, 0x1f, 0xe0, 0x80, 0x20, 0xff, 0xc6, 0x1,
    0x20, 0x84, 0x7f, 0x80, 0x20,

    /* U+540D "名" */
    0x10, 0x1f, 0xd8, 0x72, 0x40, 0xc3, 0xfe, 0x82,
    0x41, 0x3f, 0x80,

    /* U+540E "后" */
    0x0, 0x9c, 0xc4, 0x1, 0xff, 0x40, 0x10, 0x5,
    0xf9, 0x42, 0x90, 0xa7, 0xe0,

    /* U+5929 "天" */
    0x7f, 0x84, 0x2, 0x1f, 0xf0, 0x80, 0xa0, 0x50,
    0xc6, 0xc0, 0x80,

    /* U+5DDE "州" */
    0x24, 0x92, 0x49, 0x36, 0xda, 0xd9, 0x24, 0x92,
    0x89, 0x84, 0x80,

    /* U+5E02 "市" */
    0x0, 0x4, 0x3f, 0xe1, 0x7, 0xf2, 0x49, 0x24,
    0x92, 0x4b, 0x4, 0x0,

    /* U+5E7F "广" */
    0x0, 0x2, 0x1f, 0xe8, 0x4, 0x2, 0x1, 0x0,
    0x80, 0x80, 0x40, 0x0,

    /* U+5EA6 "度" */
    0x0, 0x1f, 0xf5, 0x11, 0xff, 0x51, 0x17, 0xc7,
    0xf9, 0x44, 0x8e, 0x2e, 0x70,

    /* U+62A5 "报" */
    0x5f, 0x94, 0x2f, 0x39, 0x40, 0x5f, 0xbd, 0x25,
    0x51, 0x4c, 0xdc, 0x80,

    /* U+65B0 "新" */
    0x21, 0xbf, 0x5, 0x43, 0xf0, 0x27, 0xbf, 0x47,
    0x52, 0xa4, 0x69, 0x0,

    /* U+65E5 "日" */
    0xff, 0x6, 0xc, 0x1f, 0xf0, 0x60, 0xc1, 0xfe,

    /* U+660E "明" */
    0xef, 0xd4, 0x6b, 0xfd, 0x1a, 0x8d, 0x7f, 0xa3,
    0x21, 0x23, 0x80,

    /* U+66F4 "更" */
    0xff, 0x84, 0x1f, 0xc9, 0x27, 0xf3, 0xf9, 0x24,
    0x60, 0xcf, 0x80,

    /* U+6C14 "气" */
    0x20, 0x1f, 0xe4, 0x2, 0xfc, 0xff, 0x0, 0x40,
    0x10, 0x5, 0x1, 0xc0,

    /* U+6D77 "海" */
    0x88, 0x15, 0xea, 0xf9, 0x4a, 0x3f, 0xd5, 0x25,
    0x2a, 0x7f, 0x83, 0x80,

    /* U+6E29 "温" */
    0x5f, 0x8c, 0x21, 0xfb, 0x42, 0x1f, 0x97, 0xe5,
    0x69, 0x5a, 0xbf, 0xc0,

    /* U+6E7F "湿" */
    0x9f, 0x30, 0xaf, 0xcb, 0xe0, 0xa3, 0x56, 0x6d,
    0x14, 0xbf, 0x80,

    /* U+73E0 "珠" */
    0xa, 0x13, 0xe5, 0x23, 0x88, 0x5f, 0x91, 0xc6,
    0xb2, 0x4a, 0x2, 0x0,

    /* U+8302 "茂" */
    0x12, 0x3f, 0xf1, 0x61, 0xff, 0x44, 0x11, 0x44,
    0x25, 0x39, 0xb1, 0x80,

    /* U+8FD1 "近" */
    0x4f, 0x9a, 0x0, 0x83, 0x3f, 0x49, 0x12, 0x45,
    0x91, 0x44, 0xbf, 0xc0,

    /* U+9884 "预" */
    0xff, 0x91, 0x13, 0xff, 0x55, 0xaa, 0xd5, 0x2a,
    0x8a, 0xd8, 0x80};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 47, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 50, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 70, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 3, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 94, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 15, .adv_w = 142, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 139, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 41, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 32, .adv_w = 53, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 36, .adv_w = 53, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 40, .adv_w = 73, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 42, .adv_w = 119, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 46, .adv_w = 39, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 47, .adv_w = 69, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 48, .adv_w = 39, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 68, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 54, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 94, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 94, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 39, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 39, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 106, .adv_w = 119, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 110, .adv_w = 119, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 112, .adv_w = 119, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 116, .adv_w = 77, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 165, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 132, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 100, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 122, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 88, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 85, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 124, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 47, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 63, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 102, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 82, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 156, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 98, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 130, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 227, .adv_w = 104, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 92, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 92, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 108, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 163, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 97, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 99, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 53, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 287, .adv_w = 67, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 292, .adv_w = 53, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 295, .adv_w = 119, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 299, .adv_w = 72, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 300, .adv_w = 47, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 301, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 91, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 55, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 333, .adv_w = 99, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 43, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 43, .box_w = 3, .box_h = 12, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 346, .adv_w = 87, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 43, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 150, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 99, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 102, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 374, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 380, .adv_w = 61, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 74, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 60, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 99, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 84, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 126, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 81, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 413, .adv_w = 79, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 53, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 421, .adv_w = 43, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 423, .adv_w = 53, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 427, .adv_w = 119, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 429, .adv_w = 47, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 439, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 452, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 463, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 476, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 487, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 500, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 511, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 522, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 534, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 546, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 559, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 571, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 583, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 591, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 602, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 613, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 625, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 637, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 649, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 660, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 672, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 684, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 696, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1}};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0xc1, 0x531, 0x5b2, 0x604, 0x605, 0xb20, 0xfd5,
    0xff9, 0x1076, 0x109d, 0x149c, 0x17a7, 0x17dc, 0x1805, 0x18eb,
    0x1e0b, 0x1f6e, 0x2020, 0x2076, 0x25d7, 0x34f9, 0x41c8, 0x4a7b};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
    {
        {.range_start = 32, .range_length = 96, .glyph_id_start = 1, .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY},
        {.range_start = 19977, .range_length = 19068, .glyph_id_start = 97, .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 24, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY}};

/*-----------------
 *    KERNING
 *----------------*/

/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
    {
        3, 83,
        3, 84,
        8, 83,
        8, 84,
        9, 75,
        11, 34,
        11, 43,
        11, 68,
        11, 69,
        11, 70,
        11, 72,
        11, 80,
        11, 82,
        34, 11,
        34, 13,
        34, 28,
        34, 36,
        34, 40,
        34, 43,
        34, 48,
        34, 53,
        34, 54,
        34, 55,
        34, 56,
        34, 58,
        34, 59,
        34, 85,
        34, 87,
        34, 88,
        34, 90,
        35, 53,
        35, 58,
        36, 32,
        36, 36,
        36, 40,
        36, 48,
        36, 50,
        37, 13,
        37, 15,
        37, 34,
        37, 53,
        37, 57,
        37, 59,
        38, 34,
        38, 43,
        38, 53,
        38, 56,
        38, 57,
        39, 13,
        39, 15,
        39, 34,
        39, 43,
        39, 52,
        39, 53,
        39, 66,
        39, 71,
        40, 53,
        40, 55,
        40, 90,
        43, 13,
        43, 15,
        43, 34,
        43, 43,
        43, 66,
        44, 13,
        44, 28,
        44, 36,
        44, 40,
        44, 43,
        44, 48,
        44, 50,
        44, 57,
        44, 59,
        44, 68,
        44, 69,
        44, 70,
        44, 72,
        44, 80,
        44, 82,
        44, 85,
        44, 87,
        44, 88,
        44, 90,
        45, 11,
        45, 32,
        45, 34,
        45, 36,
        45, 40,
        45, 43,
        45, 48,
        45, 50,
        45, 53,
        45, 54,
        45, 55,
        45, 56,
        45, 58,
        45, 59,
        45, 85,
        45, 87,
        45, 88,
        45, 90,
        48, 13,
        48, 15,
        48, 34,
        48, 43,
        48, 53,
        48, 57,
        48, 58,
        48, 59,
        49, 13,
        49, 15,
        49, 34,
        49, 40,
        49, 43,
        49, 56,
        49, 57,
        49, 66,
        49, 68,
        49, 69,
        49, 70,
        49, 72,
        49, 80,
        49, 82,
        50, 13,
        50, 15,
        50, 34,
        50, 53,
        50, 57,
        50, 58,
        50, 59,
        51, 28,
        51, 36,
        51, 40,
        51, 43,
        51, 48,
        51, 50,
        51, 53,
        51, 58,
        51, 68,
        51, 69,
        51, 70,
        51, 72,
        51, 80,
        51, 82,
        52, 85,
        52, 87,
        52, 88,
        52, 90,
        53, 13,
        53, 15,
        53, 27,
        53, 28,
        53, 34,
        53, 36,
        53, 40,
        53, 43,
        53, 48,
        53, 50,
        53, 53,
        53, 55,
        53, 56,
        53, 57,
        53, 58,
        53, 66,
        53, 68,
        53, 69,
        53, 70,
        53, 71,
        53, 72,
        53, 78,
        53, 79,
        53, 80,
        53, 81,
        53, 82,
        53, 83,
        53, 84,
        53, 86,
        53, 87,
        53, 88,
        53, 89,
        53, 90,
        53, 91,
        54, 34,
        55, 13,
        55, 15,
        55, 34,
        55, 36,
        55, 40,
        55, 43,
        55, 48,
        55, 50,
        55, 52,
        55, 53,
        55, 66,
        55, 68,
        55, 69,
        55, 70,
        55, 72,
        55, 78,
        55, 79,
        55, 80,
        55, 81,
        55, 82,
        55, 83,
        55, 84,
        55, 86,
        56, 13,
        56, 15,
        56, 34,
        56, 53,
        56, 66,
        56, 68,
        56, 69,
        56, 70,
        56, 72,
        56, 80,
        56, 82,
        57, 13,
        57, 15,
        57, 28,
        57, 36,
        57, 40,
        57, 43,
        57, 48,
        57, 50,
        57, 53,
        58, 13,
        58, 15,
        58, 34,
        58, 36,
        58, 40,
        58, 43,
        58, 48,
        58, 50,
        58, 52,
        58, 53,
        58, 66,
        58, 68,
        58, 69,
        58, 70,
        58, 71,
        58, 72,
        58, 78,
        58, 79,
        58, 80,
        58, 81,
        58, 82,
        58, 83,
        58, 84,
        58, 86,
        59, 43,
        59, 53,
        59, 90,
        60, 75,
        67, 66,
        67, 71,
        67, 89,
        68, 43,
        68, 53,
        68, 58,
        70, 3,
        70, 8,
        71, 10,
        71, 13,
        71, 14,
        71, 15,
        71, 27,
        71, 28,
        71, 32,
        71, 62,
        71, 67,
        71, 73,
        71, 85,
        71, 87,
        71, 88,
        71, 89,
        71, 90,
        71, 94,
        72, 75,
        75, 75,
        76, 13,
        76, 14,
        76, 15,
        76, 27,
        76, 28,
        76, 68,
        76, 69,
        76, 70,
        76, 72,
        76, 80,
        76, 82,
        76, 85,
        79, 3,
        79, 8,
        80, 3,
        80, 8,
        80, 66,
        80, 71,
        80, 89,
        81, 66,
        81, 71,
        81, 89,
        82, 75,
        83, 13,
        83, 14,
        83, 15,
        83, 27,
        83, 28,
        83, 68,
        83, 69,
        83, 70,
        83, 71,
        83, 72,
        83, 78,
        83, 79,
        83, 80,
        83, 82,
        83, 84,
        83, 85,
        83, 87,
        83, 88,
        83, 89,
        83, 90,
        83, 91,
        85, 14,
        85, 32,
        85, 68,
        85, 69,
        85, 70,
        85, 72,
        85, 80,
        85, 82,
        85, 89,
        86, 3,
        86, 8,
        87, 13,
        87, 15,
        87, 66,
        87, 68,
        87, 69,
        87, 70,
        87, 72,
        87, 80,
        87, 82,
        88, 13,
        88, 15,
        88, 68,
        88, 69,
        88, 70,
        88, 72,
        88, 80,
        88, 82,
        89, 68,
        89, 69,
        89, 70,
        89, 72,
        89, 80,
        89, 82,
        90, 3,
        90, 8,
        90, 13,
        90, 15,
        90, 32,
        90, 68,
        90, 69,
        90, 70,
        90, 71,
        90, 72,
        90, 80,
        90, 82,
        90, 85,
        92, 75};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
    {
        -4, -6, -4, -6, 20, -14, -13, -9,
        -9, -9, -9, -9, -9, -11, 6, 6,
        -2, -2, 8, -2, -12, -2, -10, -6,
        -13, 5, -2, -4, -2, -3, -8, -6,
        0, -5, -5, -2, -5, -11, -11, -3,
        -8, -4, -4, 1, 6, 0, 2, 1,
        -13, -13, -11, -6, -2, 1, -6, 1,
        -4, -2, -2, -9, -9, -3, -6, -2,
        3, 3, -8, -8, 8, -8, -8, 3,
        3, -2, -2, -2, -2, -2, -2, -4,
        -6, -4, -8, -17, -9, 5, -6, -6,
        8, -6, -6, -10, -2, -10, -4, -11,
        5, -2, -9, -6, -6, -8, -8, -2,
        -1, -8, -3, -2, -4, -27, -27, -13,
        -1, -11, 3, -5, -6, -6, -6, -6,
        -6, -6, -6, -8, -11, -2, -8, -3,
        -1, -4, 7, -2, -2, 5, -2, -2,
        -4, -3, -4, -4, -5, -5, -5, -4,
        -6, -4, -2, -4, -11, -15, -2, -2,
        -13, -8, -8, -10, -8, -8, 3, 4,
        3, 0, 2, -18, -18, -18, -18, -8,
        -18, -15, -15, -18, -15, -18, -15, -13,
        -15, -9, -10, -15, -10, -11, -3, -17,
        -19, -10, -4, -4, -6, -1, -4, -2,
        3, -12, -11, -11, -11, -11, -6, -6,
        -11, -6, -11, -6, -6, -6, -10, -11,
        -6, 3, -6, -4, -4, -4, -4, -4,
        -4, 6, 5, 7, -2, -2, 8, -2,
        -2, 3, -15, -16, -13, -4, -4, -6,
        -4, -4, -2, 3, -17, -15, -15, -15,
        -2, -15, -12, -12, -15, -12, -15, -12,
        -11, -12, 7, 3, -4, 20, -2, -1,
        -2, 6, -9, -6, -9, -9, 12, -11,
        -9, -11, 7, 7, 6, 12, 1, 1,
        3, 3, 3, 1, 3, 7, 4, 3,
        7, -12, 7, 7, 7, -3, -2, -3,
        -3, -3, -2, -1, -9, -9, -12, -12,
        -2, -3, -2, -2, -3, -2, 9, -13,
        -11, -14, 7, 7, -2, -2, -2, 3,
        -2, 0, 0, -2, -2, 1, 5, 7,
        7, 5, 7, 3, -10, -4, -2, -2,
        -1, -1, -1, -1, 2, -6, -6, -10,
        -11, -3, -1, -1, -1, -1, -1, -1,
        -8, -9, 0, -1, -1, 0, 0, -1,
        -1, -1, -1, -1, -1, -1, 2, 2,
        -9, -11, -6, -1, -1, -1, 0, -1,
        -1, -1, 0, 17};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
    {
        .glyph_ids = kern_pair_glyph_ids,
        .values = kern_pair_values,
        .pair_cnt = 372,
        .glyph_ids_size = 0};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t weather_font_cn_10_t = {
#else
lv_font_t weather_font_cn_10_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt, /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt, /*Function pointer to get glyph's bitmap*/
    .line_height = 13,                              /*The maximum line height required by the font*/
    .base_line = 3,                                 /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc, /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};

#endif /*#if WEATHER_FONT_CN_10_T*/
