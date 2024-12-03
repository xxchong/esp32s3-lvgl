/*******************************************************************************
 * Size: 24 px
 * Bpp: 1
 * Opts: --bpp 1 --size 24 --no-compress --font seguiemj.ttf --symbols 0123456789:.  --format lvgl -o Clock_font_24_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef CLOCK_FONT_24_T
#define CLOCK_FONT_24_T 1
#endif

#if CLOCK_FONT_24_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002E "." */
    0xc0,

    /* U+0030 "0" */
    0x1f, 0x6, 0x31, 0x83, 0x30, 0x6c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x78, 0xf, 0x1, 0xe0,
    0x36, 0xc, 0xc1, 0x8c, 0x60, 0xf8,

    /* U+0031 "1" */
    0x4, 0x7f, 0xf3, 0xc, 0x30, 0xc3, 0xc, 0x30,
    0xc3, 0xc, 0x30, 0xc3,

    /* U+0032 "2" */
    0x3e, 0xc, 0x32, 0x3, 0x0, 0x60, 0xc, 0x1,
    0x80, 0x70, 0x1c, 0x7, 0x1, 0xc0, 0xf0, 0x38,
    0x6, 0x1, 0x80, 0x30, 0x7, 0xff,

    /* U+0033 "3" */
    0x7e, 0x10, 0xc0, 0x18, 0x6, 0x1, 0x80, 0x60,
    0x70, 0xf0, 0x3, 0x80, 0x70, 0xc, 0x3, 0x0,
    0xc0, 0x6c, 0x3b, 0xf8,

    /* U+0034 "4" */
    0x0, 0xc0, 0x1c, 0x3, 0xc0, 0x3c, 0x6, 0xc0,
    0xcc, 0xc, 0xc1, 0x8c, 0x30, 0xc6, 0xc, 0xe0,
    0xcf, 0xff, 0x0, 0xc0, 0xc, 0x0, 0xc0, 0xc,

    /* U+0035 "5" */
    0x7f, 0x98, 0x6, 0x1, 0x80, 0x60, 0x18, 0x7,
    0xe0, 0xe, 0x1, 0x80, 0x30, 0xc, 0x3, 0x0,
    0xc0, 0x6c, 0x33, 0xf8,

    /* U+0036 "6" */
    0x7, 0xc3, 0x0, 0xc0, 0x30, 0x6, 0x1, 0x80,
    0x33, 0xc7, 0x8e, 0xe0, 0xf8, 0xf, 0x1, 0xe0,
    0x34, 0x6, 0xc1, 0x8c, 0x70, 0xf8,

    /* U+0037 "7" */
    0xff, 0xe0, 0x1c, 0x3, 0x0, 0x60, 0x18, 0x3,
    0x0, 0xc0, 0x18, 0x6, 0x0, 0xc0, 0x18, 0x6,
    0x0, 0xc0, 0x30, 0x6, 0x1, 0x80,

    /* U+0038 "8" */
    0x1f, 0x6, 0x31, 0x83, 0x30, 0x66, 0xc, 0xe3,
    0xe, 0xe0, 0x70, 0x3f, 0x8e, 0x3b, 0x83, 0xe0,
    0x3c, 0x7, 0x80, 0xd8, 0x31, 0xf8,

    /* U+0039 "9" */
    0x1f, 0xe, 0x31, 0x83, 0x60, 0x2c, 0x7, 0x80,
    0xf8, 0x1b, 0x8f, 0x1f, 0x60, 0xc, 0x1, 0x80,
    0x60, 0xc, 0x3, 0x10, 0xc3, 0xf0,

    /* U+003A ":" */
    0xc0, 0x0, 0x3
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 105, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 83, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 207, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 207, .box_w = 6, .box_h = 16, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 207, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 207, .box_w = 10, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 207, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 207, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 207, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 207, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 207, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 207, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 83, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xe
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 15, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 2, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 48, .range_length = 11, .glyph_id_start = 3,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
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
const lv_font_t Clock_font_24_t = {
#else
lv_font_t Clock_font_24_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if CLOCK_FONT_24_T*/

