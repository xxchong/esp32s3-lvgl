/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --font 胖胖猪肉体.otf --symbols 0123456789: /周一二三四五六日 --format lvgl -o watch_3_font_cn_12_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef WATCH_3_FONT_CN_12_T
#define WATCH_3_FONT_CN_12_T 1
#endif

#if WATCH_3_FONT_CN_12_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002F "/" */
    0x8, 0x63, 0x8c, 0x71, 0x8c, 0x30,

    /* U+0030 "0" */
    0x38, 0x8b, 0x1e, 0x3c, 0x78, 0xd3, 0x1c,

    /* U+0031 "1" */
    0x7f, 0xf3, 0x33, 0x33,

    /* U+0032 "2" */
    0x7b, 0xf0, 0xc3, 0x19, 0xcf, 0xff,

    /* U+0033 "3" */
    0x7f, 0xf1, 0x8e, 0x3c, 0x3f, 0xde,

    /* U+0034 "4" */
    0x1c, 0x38, 0xf3, 0x6e, 0xff, 0xc3, 0x6,

    /* U+0035 "5" */
    0x7b, 0xfc, 0x3e, 0xc, 0x3f, 0xfe,

    /* U+0036 "6" */
    0x3c, 0xc3, 0x7, 0xec, 0x78, 0xd1, 0x9e,

    /* U+0037 "7" */
    0xff, 0xf1, 0xc6, 0x38, 0xc7, 0x18,

    /* U+0038 "8" */
    0x7d, 0x8f, 0x1b, 0xec, 0xf8, 0xf1, 0xbe,

    /* U+0039 "9" */
    0x79, 0x8b, 0x1e, 0x37, 0xe0, 0xc3, 0x3c,

    /* U+003A ":" */
    0xf0, 0xf0,

    /* U+4E00 "一" */
    0xff, 0xff, 0xfc,

    /* U+4E09 "三" */
    0x7f, 0x9f, 0xe0, 0x1, 0xfe, 0x7f, 0x80, 0x0,
    0x3, 0xff, 0xff, 0xc0,

    /* U+4E8C "二" */
    0x7f, 0xcf, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7, 0xff, 0xff, 0xe0,

    /* U+4E94 "五" */
    0x7f, 0xdf, 0xf8, 0x60, 0x3f, 0xc7, 0xf8, 0x73,
    0xe, 0x61, 0xcc, 0xff, 0xff, 0xfc,

    /* U+516D "六" */
    0xe, 0x1, 0xc3, 0xff, 0xff, 0xf0, 0x0, 0x63,
    0xc, 0x63, 0x8e, 0x60, 0xdc, 0x1d, 0x1, 0x0,

    /* U+5468 "周" */
    0x7f, 0xd9, 0xcf, 0x7f, 0xe7, 0x3d, 0xff, 0x80,
    0xf7, 0xde, 0xdb, 0xdf, 0xf3, 0x38,

    /* U+56DB "四" */
    0x3f, 0xcf, 0xff, 0x6d, 0xed, 0xbd, 0xb7, 0xe7,
    0xf0, 0x1e, 0x3, 0xff, 0xe0,

    /* U+65E5 "日" */
    0x7f, 0x60, 0xf0, 0x78, 0x3f, 0xfe, 0xf, 0x7,
    0x83, 0xff, 0xe0, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 96, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 127, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 127, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 127, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 30, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 127, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 127, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 89, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 192, .box_w = 11, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 75, .adv_w = 192, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 192, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 192, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 114, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 130, .adv_w = 192, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 144, .adv_w = 192, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 192, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xf, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1a, 0x4de0, 0x4de9, 0x4e6c,
    0x4e74, 0x514d, 0x5448, 0x56bb, 0x65c5
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 26054, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 21, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t watch_3_font_cn_12_t = {
#else
lv_font_t watch_3_font_cn_12_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 11,          /*The maximum line height required by the font*/
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



#endif /*#if WATCH_3_FONT_CN_12_T*/

