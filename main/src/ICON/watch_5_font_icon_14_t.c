/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --font iconfont.ttf --range 58981,59106,58891,58965 --format lvgl -o watch_5_font_icon_14_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef WATCH_5_FONT_ICON_14_T
#define WATCH_5_FONT_ICON_14_T 1
#endif

#if WATCH_5_FONT_ICON_14_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E60B "" */
    0x39, 0xe0, 0xff, 0xe3, 0xff, 0xc7, 0xff, 0x87,
    0xfe, 0xe7, 0xfe, 0x7, 0xf0, 0x7, 0xc0, 0x6,
    0x0,

    /* U+E655 "" */
    0x1f, 0xc0, 0xff, 0xc7, 0xff, 0x9e, 0xe, 0xff,
    0xff, 0xd9, 0xff, 0xff, 0xfd, 0xdf, 0xf7, 0x7d,
    0xc1, 0xe3, 0xff, 0x7, 0xf8, 0xf, 0xc0,

    /* U+E665 "" */
    0x4, 0x1, 0x0, 0xc0, 0x30, 0x1c, 0xf, 0x7,
    0xfb, 0xfc, 0xf, 0x3, 0x80, 0xc0, 0x20, 0x10,
    0x4, 0x0,

    /* U+E6E2 "" */
    0x3, 0x80, 0x38, 0x3, 0x80, 0xf0, 0x1f, 0xf3,
    0x6f, 0x36, 0x2, 0xf0, 0x4f, 0x8f, 0x98, 0x38,
    0x80, 0xc, 0x0, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 224, .box_w = 15, .box_h = 9, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 17, .adv_w = 224, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 40, .adv_w = 224, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 58, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x4a, 0x5a, 0xd7
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58891, .range_length = 216, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t watch_5_font_icon_14_t = {
#else
lv_font_t watch_5_font_icon_14_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if WATCH_5_FONT_ICON_14_T*/

