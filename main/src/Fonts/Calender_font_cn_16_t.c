/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --font STCAIYUN.TTF --symbols 周一二三四五六日 --format lvgl -o Calender_font_cn_16_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef CALENDER_FONT_CN_16_T
#define CALENDER_FONT_CN_16_T 1
#endif

#if CALENDER_FONT_CN_16_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+4E00 "一" */
    0x7f, 0xfd, 0x0, 0x6, 0x0, 0xc, 0x0, 0x18,
    0x0, 0x2f, 0xff, 0x80,

    /* U+4E09 "三" */
    0x3f, 0xfc, 0x40, 0x2, 0x40, 0x2, 0x40, 0x2,
    0x3f, 0xfc, 0x1f, 0xf8, 0x20, 0x4, 0x20, 0x4,
    0x20, 0x4, 0x1f, 0xf8, 0x7f, 0xfe, 0x80, 0x1,
    0x80, 0x1, 0x80, 0x1, 0x7f, 0xfe,

    /* U+4E8C "二" */
    0x3f, 0xfc, 0x40, 0x2, 0x40, 0x2, 0x40, 0x2,
    0x40, 0x2, 0x3f, 0xfc, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x7f, 0xfe, 0x80, 0x1, 0x80, 0x1,
    0x80, 0x1, 0x7f, 0xff,

    /* U+4E94 "五" */
    0x3f, 0xfc, 0x40, 0x2, 0x40, 0x2, 0x40, 0x2,
    0x3c, 0xfc, 0x38, 0xf8, 0x40, 0xc, 0x40, 0x4,
    0x38, 0xc4, 0x9, 0x44, 0x11, 0x44, 0xf1, 0xc7,
    0x80, 0x1, 0x80, 0x1, 0xff, 0xff,

    /* U+516D "六" */
    0x3, 0xc0, 0x4, 0x20, 0xfc, 0x3f, 0x80, 0x1,
    0x80, 0x1, 0xff, 0xff, 0x11, 0x84, 0x21, 0x84,
    0x21, 0x42, 0x42, 0x42, 0x42, 0x22, 0x84, 0x21,
    0x84, 0x11, 0xc8, 0x11, 0x70, 0xe,

    /* U+5468 "周" */
    0x3f, 0xfc, 0x80, 0x5, 0x6, 0xa, 0x73, 0x94,
    0x81, 0x29, 0x2, 0x55, 0x4, 0xab, 0xf5, 0x58,
    0x12, 0x90, 0x25, 0x22, 0x4c, 0x40, 0x98, 0x81,
    0x31, 0xfc, 0x5c, 0xf, 0x0,

    /* U+56DB "四" */
    0x7f, 0xfd, 0x80, 0xe, 0x3f, 0xcc, 0x48, 0x99,
    0x11, 0x32, 0x22, 0x64, 0x44, 0xd1, 0x8d, 0xc3,
    0xb, 0x8a, 0x16, 0x9c, 0x2c, 0xc7, 0x98, 0x0,
    0x38, 0x0, 0xdf, 0xff, 0x0,

    /* U+65E5 "日" */
    0x7f, 0xf6, 0x0, 0xe0, 0x3, 0x0, 0x18, 0xfc,
    0xc7, 0xe6, 0x0, 0x30, 0x1, 0x80, 0xc, 0x7e,
    0x63, 0xf3, 0x0, 0x18, 0x0, 0xe0, 0xd, 0xff,
    0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 256, .box_w = 15, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 12, .adv_w = 256, .box_w = 16, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 42, .adv_w = 256, .box_w = 16, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 70, .adv_w = 256, .box_w = 16, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 100, .adv_w = 256, .box_w = 16, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 130, .adv_w = 256, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 159, .adv_w = 256, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 188, .adv_w = 256, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = -3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x9, 0x8c, 0x94, 0x36d, 0x668, 0x8db, 0x17e5
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 19968, .range_length = 6118, .glyph_id_start = 1,
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
const lv_font_t Calender_font_cn_16_t = {
#else
lv_font_t Calender_font_cn_16_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if CALENDER_FONT_CN_16_T*/

