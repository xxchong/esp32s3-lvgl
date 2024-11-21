/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --font SIMYOU.TTF --symbols 周一二三四五六日月 --range 32-127 --format lvgl -o Calender_font_cn_14_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef CALENDER_FONT_CN_14_T
#define CALENDER_FONT_CN_14_T 1
#endif

#if CALENDER_FONT_CN_14_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfe, 0xc0,

    /* U+0022 "\"" */
    0x7a, 0xa8, 0x0,

    /* U+0023 "#" */
    0x1, 0x2f, 0xd2, 0x49, 0x2f, 0xd2, 0x49, 0x20,

    /* U+0024 "$" */
    0x21, 0x1d, 0x5a, 0xf1, 0x86, 0x2d, 0x6a, 0xe2,
    0x10,

    /* U+0025 "%" */
    0xc9, 0x52, 0xc5, 0x85, 0xc2, 0x4c, 0x99, 0x52,
    0x98,

    /* U+0026 "&" */
    0x70, 0xa1, 0x43, 0x4, 0xd5, 0x2a, 0x4c, 0x92,
    0xd8,

    /* U+0027 "'" */
    0xd6,

    /* U+0028 "(" */
    0x24, 0x44, 0x88, 0x88, 0x88, 0x44, 0x20,

    /* U+0029 ")" */
    0x4, 0x22, 0x11, 0x11, 0x12, 0x24, 0x40,

    /* U+002A "*" */
    0x0, 0x8a, 0x9c, 0x23, 0xe2, 0x8,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x0,

    /* U+002C "," */
    0xd6,

    /* U+002D "-" */
    0xfe,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x0, 0x10, 0x42, 0x8, 0x41, 0x8, 0x21, 0x4,
    0x10, 0x0,

    /* U+0030 "0" */
    0x31, 0x28, 0x61, 0x86, 0x18, 0x61, 0x48, 0xc0,

    /* U+0031 "1" */
    0xe1, 0x8, 0x42, 0x10, 0x84, 0x23, 0x80,

    /* U+0032 "2" */
    0x74, 0x62, 0x11, 0x10, 0x88, 0x8f, 0xc0,

    /* U+0033 "3" */
    0x74, 0x62, 0x13, 0xc, 0x31, 0x8b, 0x80,

    /* U+0034 "4" */
    0x8, 0x62, 0x8a, 0x4a, 0x2f, 0xc2, 0x8, 0x20,

    /* U+0035 "5" */
    0xfc, 0x21, 0x6c, 0x84, 0x31, 0x8b, 0x80,

    /* U+0036 "6" */
    0x39, 0x28, 0x2e, 0xc6, 0x18, 0x61, 0x45, 0xe0,

    /* U+0037 "7" */
    0x7a, 0x21, 0x4, 0x10, 0x82, 0x8, 0x20, 0x80,

    /* U+0038 "8" */
    0x7a, 0x18, 0x71, 0x39, 0x68, 0x61, 0x85, 0xe0,

    /* U+0039 "9" */
    0x7a, 0x28, 0x61, 0x8d, 0xd0, 0x41, 0x49, 0xc0,

    /* U+003A ":" */
    0xc6,

    /* U+003B ";" */
    0x83, 0x0,

    /* U+003C "<" */
    0x0, 0xc8, 0x84, 0x42, 0x8, 0x20, 0x82,

    /* U+003D "=" */
    0xfe, 0x0, 0x7, 0xf0,

    /* U+003E ">" */
    0x4, 0x10, 0x41, 0x4, 0x44, 0x42, 0x20,

    /* U+003F "?" */
    0x7a, 0x18, 0x51, 0x8, 0xc2, 0x0, 0x20, 0x80,

    /* U+0040 "@" */
    0x39, 0x5b, 0x75, 0xd7, 0x5d, 0x6a, 0x44, 0xe0,

    /* U+0041 "A" */
    0x10, 0x20, 0xc1, 0x42, 0x89, 0x1e, 0x22, 0x44,
    0x88,

    /* U+0042 "B" */
    0x79, 0x14, 0x51, 0x79, 0x34, 0x51, 0x45, 0xe0,

    /* U+0043 "C" */
    0x3d, 0x18, 0x20, 0x82, 0x8, 0x20, 0x44, 0xe0,

    /* U+0044 "D" */
    0x71, 0x24, 0x51, 0x45, 0x14, 0x51, 0x49, 0xc0,

    /* U+0045 "E" */
    0x7c, 0x89, 0x2, 0x47, 0x89, 0x12, 0x20, 0x40,
    0xf8,

    /* U+0046 "F" */
    0x7d, 0x4, 0x12, 0x79, 0x24, 0x10, 0x41, 0x0,

    /* U+0047 "G" */
    0x3c, 0x8a, 0x4, 0x8, 0x11, 0xe1, 0x42, 0x44,
    0x70,

    /* U+0048 "H" */
    0x44, 0x89, 0x12, 0x27, 0xc8, 0x91, 0x22, 0x44,
    0x88,

    /* U+0049 "I" */
    0x71, 0x8, 0x42, 0x10, 0x84, 0x23, 0x80,

    /* U+004A "J" */
    0x1c, 0x10, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8,
    0x11, 0x23, 0x80,

    /* U+004B "K" */
    0x44, 0x91, 0x42, 0x87, 0xa, 0x12, 0x24, 0x44,
    0x88,

    /* U+004C "L" */
    0x41, 0x4, 0x10, 0x41, 0x4, 0x10, 0x41, 0xf0,

    /* U+004D "M" */
    0x44, 0xc9, 0xb3, 0x67, 0x4e, 0x9d, 0x2a, 0x54,
    0xa8,

    /* U+004E "N" */
    0x44, 0xc9, 0x92, 0xa5, 0x4a, 0x93, 0x26, 0x4c,
    0x88,

    /* U+004F "O" */
    0x31, 0x28, 0x61, 0x86, 0x18, 0x61, 0x48, 0xc0,

    /* U+0050 "P" */
    0x79, 0x14, 0x51, 0x45, 0xe4, 0x10, 0x41, 0x0,

    /* U+0051 "Q" */
    0x31, 0x28, 0x61, 0x86, 0x18, 0x69, 0x58, 0xa1,
    0xc0,

    /* U+0052 "R" */
    0x78, 0x89, 0x12, 0x27, 0x8a, 0x12, 0x24, 0x48,
    0x88,

    /* U+0053 "S" */
    0x7a, 0x18, 0x30, 0x70, 0x60, 0x41, 0x87, 0xe0,

    /* U+0054 "T" */
    0x7c, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20,

    /* U+0055 "U" */
    0x44, 0x89, 0x12, 0x24, 0x48, 0x91, 0x22, 0x44,
    0x70,

    /* U+0056 "V" */
    0x44, 0x89, 0x21, 0x42, 0x85, 0xc, 0x18, 0x10,
    0x20,

    /* U+0057 "W" */
    0x54, 0xa9, 0x52, 0xa7, 0x4d, 0x9a, 0x14, 0x28,
    0x50,

    /* U+0058 "X" */
    0x44, 0x90, 0xa1, 0x81, 0x2, 0xa, 0x14, 0x44,
    0x88,

    /* U+0059 "Y" */
    0x44, 0x88, 0xa1, 0x43, 0x2, 0x4, 0x8, 0x10,
    0x20,

    /* U+005A "Z" */
    0x7e, 0x10, 0x82, 0x10, 0x42, 0x8, 0x45, 0xf0,

    /* U+005B "[" */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x8f,

    /* U+005C "\\" */
    0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x82, 0x10,
    0x0,

    /* U+005D "]" */
    0xf1, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f,

    /* U+005E "^" */
    0xe0,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0x40,

    /* U+0061 "a" */
    0x72, 0x20, 0x9e, 0x8a, 0x27, 0xc0,

    /* U+0062 "b" */
    0x41, 0x4, 0x16, 0x65, 0x14, 0x51, 0x45, 0xe0,

    /* U+0063 "c" */
    0x74, 0x61, 0x8, 0x41, 0xe0,

    /* U+0064 "d" */
    0x8, 0x20, 0x9e, 0x8a, 0x28, 0xa2, 0x89, 0xf0,

    /* U+0065 "e" */
    0x74, 0x63, 0xf8, 0x45, 0xc0,

    /* U+0066 "f" */
    0x1c, 0x92, 0x1c, 0x20, 0x82, 0x8, 0x20, 0xc0,

    /* U+0067 "g" */
    0x7e, 0x28, 0xa2, 0xf3, 0xb, 0xe1, 0x78,

    /* U+0068 "h" */
    0x0, 0x81, 0x2, 0x5, 0xcc, 0x91, 0x22, 0x44,
    0x89, 0x10,

    /* U+0069 "i" */
    0x40, 0x24, 0x92, 0x48,

    /* U+006A "j" */
    0x10, 0x1, 0x11, 0x11, 0x11, 0x9e,

    /* U+006B "k" */
    0x0, 0x81, 0x2, 0x4, 0x8a, 0x14, 0x38, 0x48,
    0x91, 0x10,

    /* U+006C "l" */
    0x23, 0x8, 0x42, 0x10, 0x84, 0x21, 0x1c,

    /* U+006D "m" */
    0x7c, 0xa9, 0x52, 0xa5, 0x4a, 0x95, 0x0,

    /* U+006E "n" */
    0x58, 0xc9, 0x12, 0x24, 0x48, 0x91, 0x0,

    /* U+006F "o" */
    0x7a, 0x28, 0x61, 0x86, 0x37, 0x80,

    /* U+0070 "p" */
    0x59, 0x94, 0x51, 0x45, 0x16, 0x94, 0x40,

    /* U+0071 "q" */
    0x7a, 0x28, 0xa2, 0x8a, 0x27, 0x82, 0x8,

    /* U+0072 "r" */
    0x6c, 0x60, 0x81, 0x2, 0x4, 0x1c, 0x0,

    /* U+0073 "s" */
    0x7c, 0x70, 0xe0, 0xc7, 0xc0,

    /* U+0074 "t" */
    0x20, 0x87, 0x8, 0x20, 0x82, 0x9, 0x38,

    /* U+0075 "u" */
    0x44, 0x89, 0x12, 0x24, 0x48, 0x8f, 0x80,

    /* U+0076 "v" */
    0x45, 0x22, 0x8a, 0x30, 0x41, 0x0,

    /* U+0077 "w" */
    0xd4, 0xa9, 0x53, 0xa6, 0x85, 0xa, 0x0,

    /* U+0078 "x" */
    0x68, 0xa1, 0x4, 0x29, 0x24, 0x40,

    /* U+0079 "y" */
    0x8a, 0x45, 0x14, 0x60, 0x82, 0x10, 0xc0,

    /* U+007A "z" */
    0xfc, 0x84, 0x44, 0x27, 0xe0,

    /* U+007B "{" */
    0x29, 0x24, 0xb2, 0x49, 0x24, 0x40,

    /* U+007C "|" */
    0xff, 0xfe,

    /* U+007D "}" */
    0x89, 0x24, 0x9a, 0x49, 0x25, 0x0,

    /* U+007E "~" */
    0x40, 0x81, 0x80,

    /* U+4E00 "一" */
    0xff, 0xf0,

    /* U+4E09 "三" */
    0x3f, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xf, 0xff, 0x80,

    /* U+4E8C "二" */
    0x3f, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xff,
    0xc0,

    /* U+4E94 "五" */
    0x7f, 0xf8, 0x10, 0x0, 0x40, 0x1, 0x0, 0x3f,
    0xf0, 0x10, 0x40, 0x41, 0x1, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x81, 0x1f, 0xff,

    /* U+516D "六" */
    0x4, 0x0, 0x20, 0x0, 0x80, 0x4, 0xf, 0xff,
    0x0, 0x0, 0x42, 0x2, 0x8, 0x20, 0x41, 0x1,
    0x10, 0x8, 0x80, 0x28, 0x1, 0x0,

    /* U+5468 "周" */
    0x7f, 0xf4, 0x21, 0x5f, 0xf4, 0x21, 0x42, 0x17,
    0xff, 0x40, 0x15, 0xfd, 0x50, 0x55, 0x5, 0x5f,
    0xd8, 0x1, 0x80, 0xf0,

    /* U+56DB "四" */
    0xff, 0xf8, 0x91, 0x89, 0x18, 0x91, 0x89, 0x18,
    0x91, 0x89, 0x19, 0x1f, 0xe0, 0x18, 0x1, 0x80,
    0x1f, 0xff,

    /* U+65E5 "日" */
    0xff, 0xe0, 0x18, 0x6, 0x1, 0x80, 0x7f, 0xf8,
    0x6, 0x1, 0x80, 0x60, 0x1f, 0xfc,

    /* U+6708 "月" */
    0x3f, 0xe4, 0x4, 0x80, 0x90, 0x13, 0xfe, 0x40,
    0x48, 0x9, 0xff, 0x20, 0x24, 0x5, 0x80, 0xa0,
    0x18, 0x1e
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 112, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 112, .box_w = 1, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 112, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 6, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 112, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 23, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 112, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 42, .adv_w = 112, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 49, .adv_w = 112, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 56, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 62, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 69, .adv_w = 112, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 70, .adv_w = 112, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 71, .adv_w = 112, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 112, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 82, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 112, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 112, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 112, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 112, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 112, .box_w = 1, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 112, .box_w = 1, .box_h = 9, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 161, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 112, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 172, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 112, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 112, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 281, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 341, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 112, .box_w = 4, .box_h = 14, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 427, .adv_w = 112, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 436, .adv_w = 112, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 443, .adv_w = 112, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 444, .adv_w = 112, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 445, .adv_w = 112, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 446, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 112, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 112, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 493, .adv_w = 112, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 112, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 112, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 513, .adv_w = 112, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 550, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 557, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 564, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 112, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 583, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 603, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 616, .adv_w = 112, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 112, .box_w = 3, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 627, .adv_w = 112, .box_w = 1, .box_h = 15, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 629, .adv_w = 112, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 635, .adv_w = 112, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 638, .adv_w = 224, .box_w = 12, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 640, .adv_w = 224, .box_w = 14, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 660, .adv_w = 224, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 224, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 698, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 720, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 740, .adv_w = 224, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 758, .adv_w = 224, .box_w = 10, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 772, .adv_w = 224, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x9, 0x8c, 0x94, 0x36d, 0x668, 0x8db, 0x17e5,
    0x1908
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 19968, .range_length = 6409, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 9, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t Calender_font_cn_14_t = {
#else
lv_font_t Calender_font_cn_14_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if CALENDER_FONT_CN_14_T*/

