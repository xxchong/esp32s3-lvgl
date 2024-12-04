/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --font MiSans-Normal.ttf --symbols 闹钟秒表计时器  --format lvgl -o Clock_font_cn_16_t.c
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

    /* U+5668 "器" */
    0x7d, 0xf2, 0x28, 0x91, 0x44, 0xfb, 0xe0, 0x24,
    0x1, 0x23, 0xff, 0xe1, 0xb0, 0xf0, 0x7b, 0xef,
    0x91, 0x44, 0x8a, 0x27, 0xdf, 0x22, 0x88,

    /* U+65F6 "时" */
    0x0, 0x27, 0xc1, 0x22, 0x9, 0x17, 0xf8, 0x82,
    0x45, 0x13, 0xec, 0x91, 0x24, 0x88, 0xa4, 0x41,
    0x22, 0x9, 0xf0, 0x48, 0x2, 0x0, 0xf0,

    /* U+79D2 "秒" */
    0x0, 0x41, 0xf1, 0x9, 0x15, 0x4, 0x56, 0xfd,
    0x48, 0xc9, 0x33, 0x24, 0x54, 0x92, 0x5c, 0x52,
    0x50, 0xc9, 0x6, 0x4, 0x30, 0x13, 0x0, 0x58,
    0x0,

    /* U+8868 "表" */
    0x3, 0x0, 0xc, 0x7, 0xff, 0xc0, 0xc0, 0x3,
    0x1, 0xff, 0xe0, 0x30, 0x3f, 0xff, 0x7, 0x0,
    0x34, 0x61, 0x8e, 0x1a, 0x10, 0x88, 0x30, 0x3c,
    0x31, 0x80, 0x0,

    /* U+8BA1 "计" */
    0x40, 0x40, 0x81, 0x1, 0x4, 0x0, 0x10, 0x0,
    0x43, 0x9f, 0xf2, 0x4, 0x8, 0x10, 0x20, 0x40,
    0x81, 0x2, 0xc4, 0xe, 0x10, 0x30, 0x40, 0x1,
    0x0,

    /* U+949F "钟" */
    0x20, 0x42, 0x2, 0x1e, 0x11, 0x7, 0xff, 0xa4,
    0x91, 0x24, 0x89, 0x3f, 0x49, 0xfb, 0xf9, 0x2,
    0x8, 0x10, 0x50, 0x83, 0x4, 0x0, 0x20,

    /* U+95F9 "闹" */
    0x80, 0x4, 0xff, 0x20, 0x10, 0x61, 0x82, 0x1b,
    0xfd, 0x82, 0x19, 0xfd, 0x92, 0x59, 0x25, 0x92,
    0x59, 0x25, 0x92, 0xd8, 0x21, 0x80, 0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 74, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 24, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 47, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 72, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 99, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 124, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 147, .adv_w = 256, .box_w = 12, .box_h = 15, .ofs_x = 2, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x5648, 0x65d6, 0x79b2, 0x8848, 0x8b81, 0x947f, 0x95d9
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 38362, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 8, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t Clock_font_cn_16_t = {
#else
lv_font_t Clock_font_cn_16_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if CLOCK_FONT_CN_16_T*/

