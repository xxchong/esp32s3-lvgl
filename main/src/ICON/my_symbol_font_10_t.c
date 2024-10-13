/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: --bpp 1 --size 10 --no-compress --font iconfont.ttf --range 58880,58910,58912,58932,58976,58924,58911,58890,59118,58952,59000,58913,59053,59392,59005,59548,59125,58931,58933,58929,59585 --format lvgl -o my_symbol_font_10_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef MY_SYMBOL_FONT_10_T
#define MY_SYMBOL_FONT_10_T 1
#endif

#if MY_SYMBOL_FONT_10_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E600 "" */
    0x3c, 0x3f, 0xbf, 0xdf, 0xfe, 0xff, 0xb9, 0xfc,
    0x7c,

    /* U+E60A "" */
    0xd, 0x3, 0x91, 0xfc, 0xfe, 0x3f, 0x57, 0xe6,
    0xe1, 0xc0, 0x0, 0x0,

    /* U+E61E "" */
    0x8, 0x2, 0x0, 0x83, 0xdf, 0xf3, 0xe8, 0xf9,
    0xc7, 0xc9, 0x61, 0x80,

    /* U+E61F "" */
    0x1e, 0x18, 0x67, 0xa, 0xf1, 0x92, 0x67, 0x98,
    0xc6, 0x6, 0x42, 0x8f, 0xc0,

    /* U+E620 "" */
    0x7, 0x8, 0x92, 0x1, 0x40, 0x18, 0x83, 0x8,
    0x70, 0xa, 0x2, 0x30, 0x81, 0xe0,

    /* U+E621 "" */
    0x40, 0x80, 0xfc, 0x82, 0x41, 0x1, 0x1, 0x2,
    0xfc,

    /* U+E62C "" */
    0x65, 0x5d, 0xec, 0x44, 0x60,

    /* U+E631 "" */
    0xff, 0xf0, 0x6, 0x5c, 0xd5, 0x99, 0x3, 0xe,
    0x69, 0x4d, 0x29, 0x8f, 0x30, 0x7, 0xff, 0x80,

    /* U+E633 "" */
    0x3e, 0x3f, 0xbd, 0xfc, 0x7f, 0x7f, 0x1f, 0xde,
    0xfe, 0x3e, 0x0,

    /* U+E634 "" */
    0x7f, 0x32, 0xa0, 0xb7, 0xdc, 0x18, 0x0,

    /* U+E635 "" */
    0xff, 0x40, 0xa7, 0x73, 0xb8, 0x17, 0xf8,

    /* U+E648 "" */
    0x3f, 0x8, 0x4f, 0xfe, 0xc7, 0xdf, 0xec, 0x78,
    0x6, 0x1, 0xff, 0xc0,

    /* U+E660 "" */
    0xe, 0x1, 0x41, 0xc7, 0x27, 0x25, 0x14, 0xa2,
    0xa4, 0x4a, 0x76, 0x20, 0x85, 0xd0, 0x44, 0x0,

    /* U+E678 "" */
    0x8, 0x3a, 0xe6, 0xec, 0xb0, 0x1, 0xe0, 0x0,
    0x30,

    /* U+E67D "" */
    0xf, 0x1f, 0xec, 0xf, 0x3, 0x40, 0xb0, 0x1c,
    0x7, 0x1, 0x7f, 0x83, 0xc0,

    /* U+E6AD "" */
    0x1c, 0x31, 0xb1, 0x71, 0x19, 0x8c, 0x27, 0x6,
    0xc6, 0x1c, 0x0,

    /* U+E6EE "" */
    0xf, 0x88, 0x47, 0xa2, 0x11, 0x3b, 0xa6, 0x52,
    0xc6,

    /* U+E6F5 "" */
    0x1e, 0x8, 0x46, 0x1b, 0x3, 0xda, 0x6e, 0x9c,
    0xd, 0xde,

    /* U+E800 "" */
    0x1e, 0x3f, 0x9d, 0xf8, 0x7e, 0x1f, 0xad, 0xfe,
    0xfe, 0x1e, 0x0,

    /* U+E89C "" */
    0xc, 0x5, 0x82, 0x2d, 0x61, 0xc0, 0xe1, 0xac,
    0x11, 0xb, 0x6, 0x0,

    /* U+E8C1 "" */
    0x3c, 0xc3, 0x3c, 0x42, 0x18, 0x0, 0x8};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 21, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 33, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 46, .adv_w = 160, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 60, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 69, .adv_w = 160, .box_w = 4, .box_h = 9, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 74, .adv_w = 160, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 90, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 101, .adv_w = 160, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 160, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 115, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 127, .adv_w = 160, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 143, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 165, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 176, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 160, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 206, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 218, .adv_w = 160, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1}};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xa, 0x1e, 0x1f, 0x20, 0x21, 0x2c, 0x31,
    0x33, 0x34, 0x35, 0x48, 0x60, 0x78, 0x7d, 0xad,
    0xee, 0xf5, 0x200, 0x29c, 0x2c1};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
    {
        {.range_start = 58880, .range_length = 706, .glyph_id_start = 1, .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 21, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY}};

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
const lv_font_t my_symbol_font_10_t = {
#else
lv_font_t my_symbol_font_10_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt, /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt, /*Function pointer to get glyph's bitmap*/
    .line_height = 11,                              /*The maximum line height required by the font*/
    .base_line = 2,                                 /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc, /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};

#endif /*#if MY_SYMBOL_FONT_10_T*/
