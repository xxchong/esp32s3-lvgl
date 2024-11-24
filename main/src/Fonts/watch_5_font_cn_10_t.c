/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: --bpp 1 --size 10 --no-compress --font 江城圆体 400W.ttf --symbols 广州市海珠区一二三四四五六日月周.1234567890°C 天气晴多云少间阴阵雨累强大中小特暴冻冷雪雾沙尘热未知- --format lvgl -o watch_5_font_cn_10_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef WATCH_5_FONT_CN_10_T
#define WATCH_5_FONT_CN_10_T 1
#endif

#if WATCH_5_FONT_CN_10_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+0030 "0" */
    0x76, 0xe3, 0x18, 0xc7, 0x6e,

    /* U+0031 "1" */
    0x3c, 0x92, 0x49,

    /* U+0032 "2" */
    0xe9, 0x11, 0x22, 0x4f,

    /* U+0033 "3" */
    0xe1, 0x16, 0x31, 0x1e,

    /* U+0034 "4" */
    0x11, 0x94, 0xa9, 0x7c, 0x42,

    /* U+0035 "5" */
    0x7a, 0x10, 0xe0, 0x84, 0x2e,

    /* U+0036 "6" */
    0x72, 0x21, 0x6c, 0xc7, 0x2e,

    /* U+0037 "7" */
    0xf8, 0x44, 0x22, 0x10, 0x84,

    /* U+0038 "8" */
    0x74, 0x62, 0xab, 0x46, 0x2e,

    /* U+0039 "9" */
    0x74, 0x63, 0x17, 0x84, 0x4e,

    /* U+0043 "C" */
    0x3a, 0x21, 0x8, 0x41, 0x7,

    /* U+00B0 "°" */
    0xf7, 0x80,

    /* U+4E00 "一" */
    0xff, 0x80,

    /* U+4E09 "三" */
    0x7f, 0x0, 0x0, 0x0, 0x7, 0xf0, 0x0, 0x1,
    0xff,

    /* U+4E2D "中" */
    0x8, 0x7f, 0xe2, 0x31, 0x18, 0x8f, 0xfc, 0x20,
    0x10, 0x8, 0x0,

    /* U+4E8C "二" */
    0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xfe,

    /* U+4E91 "云" */
    0x7f, 0x0, 0x0, 0x1f, 0xf1, 0x1, 0x10, 0x85,
    0xff, 0x0, 0x80,

    /* U+4E94 "五" */
    0xff, 0x8, 0x4, 0xf, 0xc2, 0x21, 0x10, 0x89,
    0xff,

    /* U+516D "六" */
    0x8, 0x4, 0x3f, 0xe0, 0x1, 0x21, 0x8, 0x84,
    0x81, 0x0, 0x0,

    /* U+51B7 "冷" */
    0x4, 0x35, 0x7, 0xc4, 0x13, 0xf1, 0x49, 0x24,
    0x16, 0x8, 0x0,

    /* U+51BB "冻" */
    0x8, 0xbf, 0x10, 0x14, 0x3f, 0x84, 0xa5, 0xa5,
    0xc,

    /* U+533A "区" */
    0xff, 0x41, 0x29, 0x13, 0x88, 0xc4, 0x92, 0x81,
    0xff,

    /* U+5468 "周" */
    0x7f, 0x41, 0x5f, 0x49, 0x57, 0x5f, 0x53, 0x9f,
    0x83,

    /* U+56DB "四" */
    0xff, 0xca, 0x65, 0x32, 0xba, 0x7c, 0x6, 0x3,
    0xff,

    /* U+591A "多" */
    0x10, 0x3e, 0x44, 0xb8, 0x14, 0xef, 0x31, 0x4a,
    0xc, 0x70,

    /* U+5927 "大" */
    0x8, 0x4, 0x3f, 0xe1, 0x1, 0x40, 0xa0, 0x88,
    0x82, 0x0, 0x80,

    /* U+5929 "天" */
    0xff, 0x84, 0x2, 0x1f, 0xf0, 0x80, 0xa0, 0xc8,
    0x86, 0x0, 0x80,

    /* U+5C0F "小" */
    0x4, 0x1, 0x2, 0x50, 0x92, 0x44, 0x91, 0x20,
    0x40, 0x10, 0x1c, 0x0,

    /* U+5C11 "少" */
    0x8, 0x25, 0x12, 0x51, 0x20, 0xa0, 0xd0, 0x10,
    0x30, 0xe0, 0x0,

    /* U+5C18 "尘" */
    0x9, 0x14, 0x52, 0x2, 0x0, 0x83, 0xf8, 0x21,
    0xff,

    /* U+5DDE "州" */
    0x24, 0x92, 0x59, 0xae, 0xd2, 0xd9, 0x25, 0x12,
    0x89, 0x80, 0x80,

    /* U+5E02 "市" */
    0x0, 0x4, 0x3f, 0xe1, 0x7, 0xf2, 0x49, 0x24,
    0x92, 0x4b, 0x4, 0x0,

    /* U+5E7F "广" */
    0x8, 0x3f, 0xd0, 0x8, 0x4, 0x2, 0x1, 0x1,
    0x0, 0x80, 0x0,

    /* U+5F3A "强" */
    0xef, 0x18, 0xbb, 0x91, 0xef, 0x51, 0x78, 0x94,
    0x7f, 0xe0, 0x80,

    /* U+65E5 "日" */
    0xff, 0x6, 0xc, 0x1f, 0xf0, 0x60, 0xff,

    /* U+6674 "晴" */
    0xdf, 0xd7, 0xe9, 0x1f, 0x7a, 0xf5, 0x79, 0x3c,
    0x22, 0x11, 0x0,

    /* U+66B4 "暴" */
    0x7f, 0x3f, 0x9f, 0xc4, 0x87, 0xf7, 0xfd, 0xb5,
    0x55, 0x59, 0x0,

    /* U+6708 "月" */
    0x3f, 0x21, 0x3f, 0x21, 0x21, 0x3f, 0x21, 0x41,
    0x87,

    /* U+672A "未" */
    0x8, 0x3f, 0x82, 0x1, 0xf, 0xf8, 0xe0, 0xa8,
    0x92, 0x88, 0x80,

    /* U+6C14 "气" */
    0x20, 0x3f, 0xdf, 0xdf, 0xc0, 0x20, 0x10, 0x8,
    0x3, 0x1, 0x80,

    /* U+6C99 "沙" */
    0x62, 0x2, 0x80, 0xa9, 0xca, 0x2, 0x89, 0xc2,
    0x11, 0x18, 0x8, 0x0,

    /* U+6D77 "海" */
    0x68, 0x3, 0xf1, 0x1, 0x3e, 0x1f, 0xca, 0xa5,
    0x49, 0x3f, 0x3, 0x80,

    /* U+70ED "热" */
    0x44, 0x7f, 0x11, 0x8c, 0xcc, 0xe2, 0x57, 0x45,
    0x12, 0x24, 0x0,

    /* U+7279 "特" */
    0xa2, 0x3b, 0xab, 0xe4, 0x27, 0xf9, 0x8, 0x94,
    0x42, 0x23, 0x0,

    /* U+73E0 "珠" */
    0xf4, 0x2f, 0x95, 0x1c, 0x85, 0xfa, 0x71, 0x39,
    0xea, 0x24, 0x0,

    /* U+77E5 "知" */
    0x40, 0x3f, 0xe9, 0x24, 0x9f, 0xc9, 0x24, 0xd2,
    0x9f, 0x80, 0x0,

    /* U+7D2F "累" */
    0x7f, 0xbf, 0xd2, 0x2f, 0xf1, 0x41, 0xcb, 0xfe,
    0x52, 0x48, 0x80,

    /* U+95F4 "间" */
    0xbf, 0x41, 0xbd, 0xa5, 0xbd, 0xa5, 0xbd, 0x81,
    0x83,

    /* U+9634 "阴" */
    0xef, 0xd1, 0xcf, 0xd1, 0xb1, 0xaf, 0xf1, 0x91,
    0x83,

    /* U+9635 "阵" */
    0xe4, 0x6f, 0xf2, 0x19, 0x4a, 0xfd, 0x12, 0x7f,
    0x4, 0x82, 0x0,

    /* U+96E8 "雨" */
    0xff, 0x84, 0x1f, 0xf1, 0x19, 0xbc, 0x46, 0x6f,
    0x11, 0x89, 0x80,

    /* U+96EA "雪" */
    0x7f, 0x7f, 0xe2, 0x3f, 0xf0, 0x83, 0xf9, 0xfc,
    0xfe,

    /* U+96FE "雾" */
    0x7f, 0x7f, 0xea, 0xaf, 0xe2, 0x46, 0xd9, 0xfc,
    0x22, 0x66, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 36, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 56, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 2, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 89, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 89, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 89, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 89, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 89, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 89, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 89, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 89, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 89, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 89, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 102, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 59, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 56, .adv_w = 160, .box_w = 9, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 58, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 78, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 97, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 117, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 128, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 137, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 155, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 174, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 185, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 196, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 208, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 219, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 239, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 251, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 262, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 273, .adv_w = 160, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 291, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 302, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 311, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 322, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 333, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 345, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 357, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 368, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 379, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 390, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 401, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 412, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 421, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 430, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 441, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 452, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xd, 0xe, 0x10, 0x11, 0x12, 0x13, 0x14,
    0x15, 0x16, 0x17, 0x18, 0x19, 0x23, 0x90, 0x4de0,
    0x4de9, 0x4e0d, 0x4e6c, 0x4e71, 0x4e74, 0x514d, 0x5197, 0x519b,
    0x531a, 0x5448, 0x56bb, 0x58fa, 0x5907, 0x5909, 0x5bef, 0x5bf1,
    0x5bf8, 0x5dbe, 0x5de2, 0x5e5f, 0x5f1a, 0x65c5, 0x6654, 0x6694,
    0x66e8, 0x670a, 0x6bf4, 0x6c79, 0x6d57, 0x70cd, 0x7259, 0x73c0,
    0x77c5, 0x7d0f, 0x95d4, 0x9614, 0x9615, 0x96c8, 0x96ca, 0x96de
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 38623, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 56, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
    .cmap_num = 1,
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
const lv_font_t watch_5_font_cn_10_t = {
#else
lv_font_t watch_5_font_cn_10_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if WATCH_5_FONT_CN_10_T*/

