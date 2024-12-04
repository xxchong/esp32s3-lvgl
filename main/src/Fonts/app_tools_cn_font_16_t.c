/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --font MiSans-Normal.ttf --symbols 计算器温湿度指南针 --format lvgl -o app_tools_cn_font_16_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef APP_TOOLS_CN_FONT_16_T
#define APP_TOOLS_CN_FONT_16_T 1
#endif

#if APP_TOOLS_CN_FONT_16_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+5357 "南" */
    0x3, 0x0, 0xc, 0xf, 0xff, 0xc0, 0xc0, 0x3,
    0x1, 0xff, 0xe4, 0x84, 0x91, 0x22, 0x5f, 0xe9,
    0xc, 0x24, 0x30, 0x97, 0xfa, 0x43, 0x9, 0xc,
    0x24, 0x37, 0x80,

    /* U+5668 "器" */
    0x7d, 0xf2, 0x28, 0x91, 0x44, 0xfb, 0xe0, 0x24,
    0x1, 0x23, 0xff, 0xe1, 0xb0, 0xf0, 0x7b, 0xef,
    0x91, 0x44, 0x8a, 0x27, 0xdf, 0x22, 0x88,

    /* U+5EA6 "度" */
    0x3, 0x0, 0x4, 0x7, 0xff, 0xd2, 0x8, 0x48,
    0x21, 0xff, 0xf4, 0x82, 0x13, 0xf8, 0x40, 0x1,
    0x7f, 0xc5, 0x83, 0x11, 0x10, 0x83, 0x82, 0x7b,
    0xeb, 0x0, 0x80,

    /* U+6307 "指" */
    0x22, 0x0, 0x88, 0x62, 0x3e, 0x3e, 0x81, 0x22,
    0x4, 0x8f, 0xe2, 0x0, 0xe, 0x0, 0x73, 0xfa,
    0x88, 0x22, 0x20, 0x88, 0xfe, 0x22, 0x8, 0x8f,
    0xee, 0x20, 0x80,

    /* U+6E29 "温" */
    0x47, 0xf0, 0x90, 0x41, 0x41, 0x1, 0xfc, 0xc4,
    0x11, 0x9f, 0xc0, 0x0, 0x0, 0x0, 0x2f, 0xf8,
    0xa5, 0x26, 0x94, 0x92, 0x52, 0x49, 0x49, 0x7f,
    0xf0,

    /* U+6E7F "湿" */
    0x0, 0x0, 0xcf, 0xf8, 0xd0, 0x10, 0xa0, 0x20,
    0x7f, 0xd8, 0x80, 0x8d, 0xff, 0x0, 0x58, 0x0,
    0xb2, 0x69, 0x68, 0x92, 0xd1, 0x15, 0xc2, 0x2b,
    0x8, 0x16, 0x13, 0xff, 0x80,

    /* U+7B97 "算" */
    0x0, 0x0, 0xc2, 0x3, 0xef, 0xd2, 0x48, 0xbf,
    0xf0, 0x80, 0x43, 0xff, 0x8, 0x4, 0x3f, 0xf0,
    0xff, 0xc0, 0x84, 0x2, 0x10, 0xff, 0xfc, 0x41,
    0x6, 0x4, 0x0,

    /* U+8BA1 "计" */
    0x40, 0x40, 0x81, 0x1, 0x4, 0x0, 0x10, 0x0,
    0x43, 0x9f, 0xf2, 0x4, 0x8, 0x10, 0x20, 0x40,
    0x81, 0x2, 0xc4, 0xe, 0x10, 0x30, 0x40, 0x1,
    0x0,

    /* U+9488 "针" */
    0x20, 0x41, 0x2, 0x1f, 0x10, 0x80, 0x88, 0x4,
    0x3d, 0xfc, 0x81, 0x4, 0x8, 0xfc, 0x41, 0x2,
    0x8, 0x10, 0x58, 0x83, 0x84, 0x10, 0x20
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 27, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 50, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 77, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 104, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 129, .adv_w = 256, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 158, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 185, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 210, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x311, 0xb4f, 0xfb0, 0x1ad2, 0x1b28, 0x2840, 0x384a,
    0x4131
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 21335, .range_length = 16690, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 9, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t app_tools_cn_font_16_t = {
#else
lv_font_t app_tools_cn_font_16_t = {
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



#endif /*#if APP_TOOLS_CN_FONT_16_T*/

