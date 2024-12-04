/*******************************************************************************
 * Size: 25 px
 * Bpp: 1
 * Opts: --bpp 1 --size 25 --no-compress --font iconfont.ttf --range 59409,58884,58925 --format lvgl -o app_tools_icon_25_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef APP_TOOLS_ICON_25_T
#define APP_TOOLS_ICON_25_T 1
#endif

#if APP_TOOLS_ICON_25_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E604 "" */
    0x0, 0x3c, 0x0, 0x0, 0x13, 0x0, 0x0, 0x16,
    0x80, 0x0, 0xb, 0x40, 0x6, 0x95, 0xae, 0x2,
    0xd2, 0xd5, 0x32, 0x51, 0x6b, 0xe5, 0x28, 0xb4,
    0x62, 0x92, 0x5a, 0x30, 0x25, 0x2d, 0x18, 0xa,
    0x56, 0x8c, 0x25, 0x2b, 0x42, 0x24, 0xa5, 0xa0,
    0xe4, 0xa2, 0xd0, 0x0, 0x1, 0x68, 0x0, 0x0,
    0xb4, 0x0, 0x0, 0x99, 0x0, 0x0, 0x9e, 0x40,
    0x0, 0x4f, 0x20, 0x0, 0x27, 0xc8, 0x0, 0x13,
    0xe8, 0x0, 0x9, 0xe4, 0x0, 0x6, 0x2, 0x0,
    0x1, 0x86, 0x0, 0x0, 0x3c, 0x0, 0x0,

    /* U+E62D "" */
    0x7f, 0xff, 0x40, 0x0, 0x6f, 0xff, 0x34, 0x0,
    0x9a, 0x0, 0x4d, 0x0, 0x26, 0xff, 0xf3, 0x0,
    0x1, 0xbd, 0xdc, 0xd2, 0xaa, 0x6f, 0x77, 0x30,
    0x0, 0x1b, 0xdd, 0xcd, 0x2a, 0xa6, 0xf7, 0x53,
    0x0, 0x29, 0xbd, 0xd4, 0xd2, 0xaa, 0x6f, 0x77,
    0x30, 0x0, 0x17, 0xff, 0xf0,

    /* U+E811 "" */
    0x1, 0xfe, 0x0, 0x1c, 0xe, 0x1, 0xcf, 0xcc,
    0xc, 0xc8, 0x8, 0x24, 0x0, 0x11, 0xa8, 0x2,
    0x65, 0x18, 0x4, 0xa8, 0x70, 0x13, 0xa0, 0xf0,
    0x26, 0x81, 0x20, 0x9b, 0x4, 0x86, 0x68, 0x12,
    0x9, 0xa0, 0x34, 0x26, 0x80, 0x29, 0x25, 0x0,
    0x64, 0x96, 0x0, 0x32, 0x20, 0x0, 0x90, 0x44,
    0xc, 0x80, 0xcf, 0xcc, 0x1, 0xc0, 0xe0, 0x0,
    0xfc, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 400, .box_w = 25, .box_h = 25, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 79, .adv_w = 400, .box_w = 17, .box_h = 21, .ofs_x = 4, .ofs_y = -1},
    {.bitmap_index = 124, .adv_w = 400, .box_w = 22, .box_h = 21, .ofs_x = 2, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x29, 0x20d
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58884, .range_length = 526, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t app_tools_icon_25_t = {
#else
lv_font_t app_tools_icon_25_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 25,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if APP_TOOLS_ICON_25_T*/

