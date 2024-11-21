/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Opts: --bpp 1 --size 8 --no-compress --font 微软雅黑.ttf --symbols 今日次数功德+1 --format lvgl -o wooden_fish_font_cn_8_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef WOODEN_FISH_FONT_CN_8_T
#define WOODEN_FISH_FONT_CN_8_T 1
#endif

#if WOODEN_FISH_FONT_CN_8_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+002B "+" */
    0x27, 0xc8, 0x40,

    /* U+0031 "1" */
    0xc9, 0x24, 0xb8,

    /* U+4ECA "今" */
    0x8, 0x34, 0x52, 0x81, 0x7e, 0x2, 0x4, 0x8,

    /* U+529F "功" */
    0x9, 0xd1, 0xfa, 0x54, 0xad, 0x64, 0xb3,

    /* U+5FB7 "德" */
    0x8, 0x5e, 0x9e, 0x76, 0xc8, 0x7f, 0x73, 0x5c,

    /* U+6570 "数" */
    0xa4, 0x34, 0xfa, 0x7a, 0xca, 0xf6, 0x94, 0x66,
    0xc9,

    /* U+65E5 "日" */
    0xfe, 0x18, 0x7f, 0x86, 0x1f, 0xc0,

    /* U+6B21 "次" */
    0x90, 0x9e, 0x2a, 0xa, 0x98, 0x94, 0x22, 0x40
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 95, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 3, .adv_w = 75, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 14, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 21, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 29, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 38, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 44, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x6, 0x4e9f, 0x5274, 0x5f8c, 0x6545, 0x65ba, 0x6af6
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 43, .range_length = 27383, .glyph_id_start = 1,
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
const lv_font_t wooden_fish_font_cn_8_t = {
#else
lv_font_t wooden_fish_font_cn_8_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 9,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if WOODEN_FISH_FONT_CN_8_T*/

