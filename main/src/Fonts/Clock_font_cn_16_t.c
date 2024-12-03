/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --font SIMYOU.TTF --symbols 闹钟秒表计时器 --range 32-127 --format lvgl -o Clock_font_cn_16_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef CLOCK_FONT_CN_16_T
#define CLOCK_FONT_CN_16_T 1
#endif

#if CLOCK_FONT_CN_16_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xaa, 0xaa, 0xf,

    /* U+0022 "\"" */
    0x29, 0xa5, 0x28,

    /* U+0023 "#" */
    0x24, 0x89, 0x17, 0xf4, 0x49, 0x12, 0x24, 0xfe,
    0x91, 0x22, 0x40,

    /* U+0024 "$" */
    0x23, 0xab, 0x5a, 0x71, 0x86, 0x29, 0x6b, 0x57,
    0x10, 0x80,

    /* U+0025 "%" */
    0xc4, 0xa4, 0xa8, 0xa8, 0xa8, 0xb0, 0x56, 0x29,
    0x29, 0x29, 0x49, 0x46,

    /* U+0026 "&" */
    0x30, 0x48, 0x48, 0x48, 0x50, 0x26, 0xe4, 0xb4,
    0x94, 0x88, 0x8d, 0x76,

    /* U+0027 "'" */
    0xf6,

    /* U+0028 "(" */
    0x12, 0x44, 0x88, 0x88, 0x88, 0x84, 0x42, 0x20,

    /* U+0029 ")" */
    0x84, 0x42, 0x21, 0x11, 0x11, 0x12, 0x24, 0x80,

    /* U+002A "*" */
    0x10, 0x23, 0x5b, 0xe1, 0xf, 0xb5, 0x88, 0x10,

    /* U+002B "+" */
    0x10, 0x20, 0x40, 0x8f, 0xe2, 0x4, 0x8, 0x10,

    /* U+002C "," */
    0xf6,

    /* U+002D "-" */
    0xfe,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x4, 0x10, 0x82, 0x10, 0x42, 0x8, 0x21, 0x4,
    0x20, 0x82, 0x0,

    /* U+0030 "0" */
    0x31, 0x28, 0x61, 0x86, 0x18, 0x61, 0x86, 0x14,
    0x8c,

    /* U+0031 "1" */
    0x27, 0x8, 0x42, 0x10, 0x84, 0x21, 0x8, 0xe0,

    /* U+0032 "2" */
    0x7a, 0x18, 0x61, 0x4, 0x21, 0x8, 0x41, 0x8,
    0x7f,

    /* U+0033 "3" */
    0x7a, 0x18, 0x41, 0x8, 0xc0, 0x81, 0x6, 0x18,
    0xde,

    /* U+0034 "4" */
    0x8, 0x10, 0x61, 0x42, 0x89, 0x22, 0x44, 0xfe,
    0x10, 0x20, 0xe0,

    /* U+0035 "5" */
    0xfe, 0x8, 0x20, 0xbb, 0x30, 0x41, 0x6, 0x18,
    0x9e,

    /* U+0036 "6" */
    0x39, 0x28, 0x20, 0xbb, 0x38, 0x61, 0x86, 0x14,
    0x8e,

    /* U+0037 "7" */
    0x7d, 0xa, 0x20, 0x41, 0x2, 0x8, 0x10, 0x20,
    0x40, 0x81, 0x0,

    /* U+0038 "8" */
    0x7a, 0x18, 0x61, 0x48, 0xc5, 0xa3, 0x86, 0x18,
    0x5e,

    /* U+0039 "9" */
    0x72, 0x28, 0x61, 0x86, 0x1c, 0xdd, 0x4, 0x24,
    0x9c,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0x83, 0xc0,

    /* U+003C "<" */
    0x4, 0x21, 0x8, 0x42, 0x8, 0x10, 0x20, 0x40,
    0x81,

    /* U+003D "=" */
    0xfe, 0x0, 0x7, 0xf0,

    /* U+003E ">" */
    0x81, 0x2, 0x4, 0x8, 0x10, 0x84, 0x20, 0x84,
    0x20,

    /* U+003F "?" */
    0x7a, 0x18, 0x71, 0x4, 0x21, 0x4, 0x10, 0x3,
    0xc,

    /* U+0040 "@" */
    0x38, 0x8a, 0x2c, 0xda, 0xb5, 0x6a, 0xd5, 0xad,
    0x29, 0x19, 0xc0,

    /* U+0041 "A" */
    0x10, 0x18, 0x18, 0x28, 0x28, 0x24, 0x24, 0x3c,
    0x44, 0x44, 0x42, 0x46,

    /* U+0042 "B" */
    0x7c, 0x85, 0xa, 0x14, 0x4f, 0x11, 0x21, 0x42,
    0x85, 0xb, 0xe0,

    /* U+0043 "C" */
    0x3c, 0x89, 0xc, 0x8, 0x10, 0x20, 0x40, 0x81,
    0x5, 0x11, 0xc0,

    /* U+0044 "D" */
    0x78, 0x89, 0x12, 0x14, 0x28, 0x50, 0xa1, 0x42,
    0x89, 0x13, 0xc0,

    /* U+0045 "E" */
    0x7e, 0x42, 0x41, 0x40, 0x44, 0x7c, 0x44, 0x44,
    0x40, 0x41, 0x42, 0x7e,

    /* U+0046 "F" */
    0x7e, 0x42, 0x41, 0x40, 0x44, 0x7c, 0x44, 0x44,
    0x40, 0x40, 0x40, 0x40,

    /* U+0047 "G" */
    0x3c, 0x8a, 0x14, 0x8, 0x10, 0x23, 0xc2, 0x85,
    0x9, 0x11, 0xc0,

    /* U+0048 "H" */
    0x42, 0x42, 0x42, 0x42, 0x42, 0x7e, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x42,

    /* U+0049 "I" */
    0x71, 0x8, 0x42, 0x10, 0x84, 0x21, 0x8, 0xe0,

    /* U+004A "J" */
    0x1c, 0x10, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8,
    0x10, 0x20, 0x48, 0x9e, 0x0,

    /* U+004B "K" */
    0x46, 0x91, 0x22, 0x85, 0xe, 0x16, 0x24, 0x48,
    0x89, 0x12, 0x30,

    /* U+004C "L" */
    0x40, 0x81, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40,
    0x81, 0xb, 0xf0,

    /* U+004D "M" */
    0x62, 0x62, 0x66, 0x66, 0x6a, 0x6a, 0x5a, 0x5a,
    0x5a, 0x5a, 0x52, 0x42,

    /* U+004E "N" */
    0x62, 0x62, 0x62, 0x52, 0x52, 0x52, 0x4a, 0x4a,
    0x46, 0x46, 0x46, 0x42,

    /* U+004F "O" */
    0x38, 0x8a, 0x14, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x9, 0x11, 0xc0,

    /* U+0050 "P" */
    0x7c, 0x85, 0xa, 0x14, 0x28, 0x9e, 0x20, 0x40,
    0x81, 0x2, 0x0,

    /* U+0051 "Q" */
    0x38, 0x8a, 0x14, 0x18, 0x30, 0x60, 0xc1, 0xb3,
    0x95, 0x31, 0x41, 0x60,

    /* U+0052 "R" */
    0x7c, 0x42, 0x42, 0x42, 0x46, 0x78, 0x48, 0x48,
    0x44, 0x44, 0x44, 0x42,

    /* U+0053 "S" */
    0x7a, 0x28, 0x60, 0xc1, 0xc1, 0x83, 0x6, 0x18,
    0x7e,

    /* U+0054 "T" */
    0xff, 0x24, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x80,

    /* U+0055 "U" */
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x3c,

    /* U+0056 "V" */
    0x62, 0x44, 0x64, 0x24, 0x24, 0x24, 0x28, 0x18,
    0x18, 0x18, 0x10, 0x10,

    /* U+0057 "W" */
    0x49, 0x49, 0x4a, 0x4a, 0x4a, 0x36, 0x36, 0x36,
    0x34, 0x24, 0x24, 0x24,

    /* U+0058 "X" */
    0x66, 0x24, 0x24, 0x18, 0x18, 0x10, 0x18, 0x18,
    0x24, 0x24, 0x44, 0x46,

    /* U+0059 "Y" */
    0xc6, 0x89, 0x11, 0x42, 0x85, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x80,

    /* U+005A "Z" */
    0xfe, 0x10, 0x82, 0x10, 0x42, 0x8, 0x41, 0x8,
    0x7f,

    /* U+005B "[" */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0xf0,

    /* U+005C "\\" */
    0x82, 0x4, 0x10, 0x20, 0x82, 0x4, 0x10, 0x40,
    0x82, 0x4, 0x10, 0x40,

    /* U+005D "]" */
    0xf1, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xf0,

    /* U+005E "^" */
    0x69,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0x61,

    /* U+0061 "a" */
    0x79, 0x8, 0x11, 0xe4, 0x50, 0xa1, 0x3f,

    /* U+0062 "b" */
    0x0, 0x81, 0x2, 0x4, 0xb, 0x98, 0xa1, 0x42,
    0x85, 0xa, 0x27, 0xc0,

    /* U+0063 "c" */
    0x39, 0x28, 0x20, 0x82, 0x4, 0x5e,

    /* U+0064 "d" */
    0x0, 0x8, 0x10, 0x20, 0x47, 0x91, 0x42, 0x85,
    0xa, 0x14, 0x27, 0xe0,

    /* U+0065 "e" */
    0x3b, 0x18, 0x7f, 0x82, 0x4, 0x5e,

    /* U+0066 "f" */
    0x1e, 0x44, 0x81, 0x7, 0x84, 0x8, 0x10, 0x20,
    0x40, 0x83, 0x80,

    /* U+0067 "g" */
    0x7f, 0xa, 0x14, 0x2f, 0x90, 0x1e, 0x42, 0x84,
    0xf0,

    /* U+0068 "h" */
    0x40, 0x81, 0x2, 0x5, 0x8c, 0x91, 0x22, 0x44,
    0x89, 0x12, 0x20,

    /* U+0069 "i" */
    0x22, 0x0, 0x62, 0x22, 0x22, 0x26,

    /* U+006A "j" */
    0x8, 0x40, 0x0, 0x84, 0x21, 0x8, 0x42, 0x10,
    0xb8,

    /* U+006B "k" */
    0x40, 0x81, 0x2, 0x4, 0x49, 0x14, 0x28, 0x68,
    0x91, 0x12, 0x30,

    /* U+006C "l" */
    0x61, 0x8, 0x42, 0x10, 0x84, 0x21, 0x8, 0xe0,

    /* U+006D "m" */
    0xff, 0x24, 0x92, 0x49, 0x24, 0x92, 0x49, 0x24,
    0x92,

    /* U+006E "n" */
    0xd8, 0xc9, 0x12, 0x24, 0x48, 0x91, 0x22,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0070 "p" */
    0xdc, 0xc5, 0xa, 0x14, 0x28, 0x51, 0x3e, 0x40,
    0x80,

    /* U+0071 "q" */
    0x3c, 0x8a, 0x14, 0x28, 0x50, 0xa1, 0x3e, 0x4,
    0x8,

    /* U+0072 "r" */
    0xee, 0x64, 0x81, 0x2, 0x4, 0x8, 0x38,

    /* U+0073 "s" */
    0x7c, 0x60, 0xc3, 0x6, 0x3e,

    /* U+0074 "t" */
    0x0, 0x82, 0x1e, 0x20, 0x82, 0x8, 0x20, 0x91,
    0x80,

    /* U+0075 "u" */
    0x44, 0x89, 0x12, 0x24, 0x48, 0x91, 0x1f,

    /* U+0076 "v" */
    0xcd, 0x24, 0x92, 0x30, 0xc3, 0x8,

    /* U+0077 "w" */
    0xdb, 0x4a, 0x4a, 0x5c, 0x5c, 0x2c, 0x24, 0x24,

    /* U+0078 "x" */
    0x49, 0x23, 0x8, 0x31, 0x44, 0xb3,

    /* U+0079 "y" */
    0xcd, 0x24, 0x94, 0x30, 0xc1, 0x8, 0x23, 0x0,

    /* U+007A "z" */
    0xfa, 0x21, 0xc, 0x21, 0x14, 0x7f,

    /* U+007B "{" */
    0x34, 0x44, 0x44, 0x48, 0x84, 0x44, 0x44, 0x43,

    /* U+007C "|" */
    0xff, 0xff, 0xc0,

    /* U+007D "}" */
    0xc2, 0x22, 0x22, 0x21, 0x12, 0x22, 0x22, 0x2c,

    /* U+007E "~" */
    0x41, 0x40, 0x50, 0x40,

    /* U+5668 "器" */
    0x7e, 0x7c, 0x42, 0x84, 0x42, 0x84, 0x7f, 0x7c,
    0x3, 0x10, 0xff, 0xfe, 0x4, 0x40, 0x10, 0x30,
    0xe0, 0xe, 0x7e, 0x7c, 0x42, 0x84, 0x42, 0x84,
    0x42, 0x84, 0x7e, 0x7c,

    /* U+65F6 "时" */
    0x0, 0x10, 0xe0, 0x22, 0x20, 0x44, 0x7f, 0xf8,
    0x81, 0x11, 0x2, 0x22, 0x84, 0x7c, 0x88, 0x88,
    0x91, 0x10, 0xa2, 0x20, 0x44, 0x40, 0x88, 0x81,
    0x11, 0x22, 0x3e, 0x3c, 0x0,

    /* U+79D2 "秒" */
    0x0, 0x20, 0xf0, 0x40, 0x40, 0xa0, 0x89, 0x21,
    0x12, 0x5f, 0xa4, 0x84, 0x48, 0x8d, 0x11, 0x3a,
    0x22, 0xa8, 0x49, 0x40, 0x94, 0x81, 0x41, 0x0,
    0x82, 0x2, 0x4, 0x18, 0x9, 0xc0,

    /* U+8868 "表" */
    0x0, 0x80, 0x0, 0x80, 0x7f, 0xfe, 0x0, 0x80,
    0x3f, 0xfe, 0x0, 0x80, 0x0, 0x80, 0x7f, 0xff,
    0x2, 0x40, 0x4, 0x64, 0x18, 0x28, 0x68, 0x10,
    0x8, 0x8, 0x8, 0x44, 0xf, 0x83, 0x0, 0x0,
    0x0, 0x0,

    /* U+8BA1 "计" */
    0x0, 0x20, 0x10, 0x20, 0x8, 0x20, 0x0, 0x20,
    0xe0, 0x20, 0x10, 0x20, 0x17, 0xfe, 0x10, 0x20,
    0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x10, 0x20,
    0x12, 0x20, 0x14, 0x20, 0x18, 0x20, 0x0, 0x20,

    /* U+949F "钟" */
    0x20, 0x20, 0x40, 0x40, 0xf0, 0x82, 0xf, 0xf4,
    0x12, 0x20, 0x24, 0x5f, 0x48, 0x88, 0x91, 0x11,
    0x22, 0xfa, 0x44, 0x47, 0xf8, 0x81, 0x1, 0x2,
    0x2, 0x84, 0x6, 0x8, 0x0, 0x0,

    /* U+95F9 "闹" */
    0x40, 0x0, 0xbf, 0xf0, 0x0, 0x60, 0x81, 0xbf,
    0xf6, 0x8, 0x18, 0x20, 0x67, 0xf9, 0x92, 0x26,
    0x48, 0x99, 0x22, 0x64, 0x89, 0x92, 0xe6, 0x8,
    0x18, 0x22, 0x60, 0x6
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 128, .box_w = 2, .box_h = 12, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 128, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 7, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 128, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 28, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 128, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 53, .adv_w = 128, .box_w = 4, .box_h = 15, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 61, .adv_w = 128, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 69, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 77, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 85, .adv_w = 128, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 86, .adv_w = 128, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 87, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 128, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 99, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 128, .box_w = 5, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 128, .box_w = 2, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 128, .box_w = 1, .box_h = 10, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 196, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 209, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 128, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 351, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 431, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 522, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 531, .adv_w = 128, .box_w = 4, .box_h = 15, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 539, .adv_w = 128, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 551, .adv_w = 128, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 559, .adv_w = 128, .box_w = 4, .box_h = 2, .ofs_x = 2, .ofs_y = 12},
    {.bitmap_index = 560, .adv_w = 128, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 561, .adv_w = 128, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 12},
    {.bitmap_index = 562, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 625, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 128, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 642, .adv_w = 128, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 651, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 128, .box_w = 5, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 128, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 693, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 702, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 711, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 718, .adv_w = 128, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 723, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 732, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 739, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 759, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 767, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 128, .box_w = 4, .box_h = 16, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 781, .adv_w = 128, .box_w = 1, .box_h = 18, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 784, .adv_w = 128, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 792, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 796, .adv_w = 256, .box_w = 16, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 824, .adv_w = 256, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 853, .adv_w = 256, .box_w = 15, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 883, .adv_w = 256, .box_w = 16, .box_h = 17, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 917, .adv_w = 256, .box_w = 16, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 949, .adv_w = 256, .box_w = 15, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 979, .adv_w = 256, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = -3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0xf8e, 0x236a, 0x3200, 0x3539, 0x3e37, 0x3f91
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 22120, .range_length = 16274, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 7, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
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
const lv_font_t Clock_font_cn_16_t = {
#else
lv_font_t Clock_font_cn_16_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 20,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if CLOCK_FONT_CN_16_T*/

