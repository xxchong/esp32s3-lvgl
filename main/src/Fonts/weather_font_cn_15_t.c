/*******************************************************************************
 * Size: 15 px
 * Bpp: 1
 * Opts: --bpp 1 --size 15 --no-compress --font 微软雅黑.ttf --symbols 0123456789: 更新 --format lvgl -o weather_font_cn_15_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef WEATHER_FONT_CN_15_T
#define WEATHER_FONT_CN_15_T 1
#endif

#if WEATHER_FONT_CN_15_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0030 "0" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+0031 "1" */
    0x31, 0xe0, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x23, 0xf8,

    /* U+0032 "2" */
    0x7c, 0x8c, 0x8, 0x10, 0x20, 0x82, 0x8, 0x20,
    0x83, 0xf8,

    /* U+0033 "3" */
    0x79, 0x18, 0x10, 0x20, 0x8f, 0x1, 0x1, 0x3,
    0xb, 0xe0,

    /* U+0034 "4" */
    0xc, 0xc, 0x14, 0x34, 0x24, 0x44, 0xc4, 0xff,
    0x4, 0x4, 0x4,

    /* U+0035 "5" */
    0x7e, 0x81, 0x2, 0x7, 0x80, 0x80, 0x81, 0x3,
    0xb, 0xe0,

    /* U+0036 "6" */
    0x1e, 0xc1, 0x4, 0xb, 0xd8, 0xe0, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+0037 "7" */
    0xfe, 0xc, 0x10, 0x60, 0x81, 0x6, 0x8, 0x30,
    0x40, 0x80,

    /* U+0038 "8" */
    0x3c, 0xc5, 0xa, 0x13, 0xc7, 0x91, 0xc1, 0x83,
    0x8d, 0xf0,

    /* U+0039 "9" */
    0x38, 0x8a, 0xc, 0x18, 0x38, 0xce, 0x81, 0x4,
    0x1b, 0xe0,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+65B0 "新" */
    0x10, 0x0, 0x30, 0xfb, 0xfd, 0x0, 0x2, 0x2,
    0x64, 0x4, 0x88, 0x3f, 0xd0, 0x4, 0x3e, 0xff,
    0x48, 0x11, 0x91, 0xb2, 0x22, 0x54, 0x4c, 0xa8,
    0x83, 0x21, 0xc, 0x42, 0x0,

    /* U+66F4 "更" */
    0x7f, 0xfc, 0x2, 0x0, 0x4, 0x1, 0xff, 0xc2,
    0x10, 0x87, 0xff, 0x8, 0x42, 0x10, 0x84, 0x3f,
    0xf8, 0x22, 0x10, 0x68, 0x0, 0x70, 0x0, 0xf8,
    0xe, 0x1f, 0x80};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 71, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 141, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 58, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 240, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 133, .adv_w = 240, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = -2}};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x19, 0x1a, 0x6590, 0x66d4};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
    {
        {.range_start = 32, .range_length = 26325, .glyph_id_start = 1, .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 14, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY}};

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
const lv_font_t weather_font_cn_15_t = {
#else
lv_font_t weather_font_cn_15_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt, /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt, /*Function pointer to get glyph's bitmap*/
    .line_height = 15,                              /*The maximum line height required by the font*/
    .base_line = 2,                                 /*Baseline measured from the bottom of the line*/
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

#endif /*#if WEATHER_FONT_CN_15_T*/
