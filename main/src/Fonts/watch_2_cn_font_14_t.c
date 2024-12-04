/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --font 联想小新潮酷体.ttf --symbols 周一二三四五六日月 0123456789 --format lvgl -o watch_2_cn_font_14_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef WATCH_2_CN_FONT_14_T
#define WATCH_2_CN_FONT_14_T 1
#endif

#if WATCH_2_CN_FONT_14_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0030 "0" */
    0x38, 0xfb, 0xbe, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0xdd, 0xf1, 0xc0,

    /* U+0031 "1" */
    0x37, 0xf7, 0x33, 0x33, 0x33, 0x33,

    /* U+0032 "2" */
    0x3c, 0xfb, 0x1e, 0x30, 0x61, 0xc7, 0x1c, 0x30,
    0xc3, 0xff, 0xf0,

    /* U+0033 "3" */
    0x3d, 0xff, 0x1e, 0x30, 0x67, 0x8f, 0x3, 0x7,
    0x8f, 0xfb, 0xe0,

    /* U+0034 "4" */
    0xe, 0xe, 0x1e, 0x3e, 0x36, 0x76, 0x66, 0xe6,
    0xff, 0xff, 0x6, 0x6,

    /* U+0035 "5" */
    0xff, 0xff, 0x6, 0xc, 0x1f, 0x3f, 0x83, 0x7,
    0x8d, 0xf1, 0xc0,

    /* U+0036 "6" */
    0x38, 0xfb, 0xbe, 0x3c, 0x1f, 0xbf, 0xe3, 0xc7,
    0x8d, 0xf9, 0xe0,

    /* U+0037 "7" */
    0xff, 0xfc, 0x30, 0x60, 0xc3, 0x6, 0xc, 0x30,
    0x60, 0xc3, 0x0,

    /* U+0038 "8" */
    0x3c, 0x7e, 0xc7, 0xc3, 0xc3, 0x7e, 0x7e, 0xc3,
    0xc3, 0xc3, 0x7e, 0x3c,

    /* U+0039 "9" */
    0x38, 0xfb, 0x1e, 0x3c, 0x78, 0xdf, 0xbf, 0x7,
    0x9d, 0xf3, 0xc0,

    /* U+4E00 "一" */
    0xff, 0xff, 0xff,

    /* U+4E09 "三" */
    0xff, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0, 0xff,
    0x9f, 0xf0, 0x0, 0x0, 0x0, 0x3, 0xff, 0xff,
    0xf0,

    /* U+4E8C "二" */
    0x7f, 0xcf, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1f, 0xff, 0xff, 0x80,

    /* U+4E94 "五" */
    0xff, 0xff, 0xfc, 0x70, 0xc, 0x7, 0xfc, 0xff,
    0x86, 0x30, 0xc6, 0x18, 0xc6, 0x1b, 0xff, 0xff,
    0xf0,

    /* U+516D "六" */
    0x6, 0x0, 0xc0, 0x0, 0x7f, 0xff, 0xfe, 0x40,
    0xc, 0x61, 0x8c, 0x60, 0xcc, 0x19, 0x83, 0x60,
    0x34, 0x0,

    /* U+5468 "周" */
    0x7f, 0xef, 0xfd, 0x99, 0xbf, 0xf6, 0x66, 0xff,
    0xd8, 0x1b, 0xff, 0x79, 0xef, 0x3d, 0xff, 0xb0,
    0x30,

    /* U+56DB "四" */
    0xff, 0xff, 0xff, 0x6d, 0xed, 0xbd, 0xb7, 0xb6,
    0xf6, 0xde, 0xdf, 0xdb, 0xf8, 0xf, 0xff, 0xff,
    0xf0,

    /* U+65E5 "日" */
    0xff, 0xff, 0xfc, 0xf, 0x3, 0xc0, 0xff, 0xff,
    0xff, 0x3, 0xc0, 0xf0, 0x3f, 0xff, 0xff,

    /* U+6708 "月" */
    0x7f, 0xdf, 0xf6, 0xd, 0x83, 0x7f, 0xdf, 0xf6,
    0xd, 0xff, 0x7f, 0xd8, 0x3e, 0xf, 0x3
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 112, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 12, .adv_w = 87, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 18, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 29, .adv_w = 139, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 40, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 52, .adv_w = 140, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 63, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 74, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 85, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 97, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 108, .adv_w = 208, .box_w = 12, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 111, .adv_w = 208, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 128, .adv_w = 208, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 144, .adv_w = 208, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 161, .adv_w = 208, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 179, .adv_w = 208, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 196, .adv_w = 208, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 213, .adv_w = 208, .box_w = 10, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 228, .adv_w = 208, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x19, 0x4de0, 0x4de9, 0x4e6c, 0x4e74, 0x514d,
    0x5448, 0x56bb, 0x65c5, 0x66e8
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 26345, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 20, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    9, 2,
    9, 6,
    9, 8
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -4, -11, -4
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 3,
    .glyph_ids_size = 0
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
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
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
const lv_font_t watch_2_cn_font_14_t = {
#else
lv_font_t watch_2_cn_font_14_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
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



#endif /*#if WATCH_2_CN_FONT_14_T*/

