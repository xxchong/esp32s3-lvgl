/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --font MiSans-Normal.ttf --symbols 天气晴多云少间阴阵雨累强大中小特暴冻冷雪雾沙尘热未知  --format lvgl -o weather_font_cn_12_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef WEATHER_FONT_CN_12_T
#define WEATHER_FONT_CN_12_T 1
#endif

#if WEATHER_FONT_CN_12_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+4E2D "中" */
    0x8, 0x4, 0x3f, 0xf1, 0x18, 0x8c, 0x47, 0xfe,
    0x10, 0x8, 0x4, 0x2, 0x0,

    /* U+4E91 "云" */
    0x7f, 0x80, 0x0, 0x0, 0x0, 0xff, 0xc2, 0x1,
    0x20, 0x84, 0x61, 0x1f, 0xe0, 0x4,

    /* U+51B7 "冷" */
    0x86, 0x21, 0x44, 0x98, 0xd1, 0x2, 0x17, 0xe4,
    0x9, 0x24, 0x86, 0x20, 0xc0, 0x0,

    /* U+51BB "冻" */
    0x4, 0x21, 0x5, 0xfd, 0x20, 0xa, 0x4, 0x83,
    0xfd, 0x8, 0x4a, 0x94, 0xa9, 0x24, 0x38,

    /* U+591A "多" */
    0x8, 0x7, 0xe6, 0x18, 0x58, 0x7c, 0x23, 0xf3,
    0xb, 0x24, 0x6, 0xe, 0xc, 0x0,

    /* U+5927 "大" */
    0x8, 0x2, 0x0, 0x83, 0xff, 0x8, 0x3, 0x0,
    0xc0, 0x48, 0x31, 0x10, 0x28, 0x4,

    /* U+5929 "天" */
    0x7f, 0x82, 0x0, 0x80, 0x20, 0xff, 0xc3, 0x0,
    0xc0, 0x48, 0x33, 0x18, 0x28, 0x4,

    /* U+5C0F "小" */
    0x4, 0x0, 0x80, 0x94, 0x12, 0x42, 0x48, 0x88,
    0x91, 0x14, 0x22, 0x84, 0x20, 0x80, 0x70, 0x0,

    /* U+5C11 "少" */
    0x4, 0x0, 0x80, 0x92, 0x12, 0x44, 0x44, 0x88,
    0x61, 0x20, 0x8, 0x6, 0x3, 0x3, 0x80, 0x0,

    /* U+5C18 "尘" */
    0x8, 0xa, 0xc2, 0x9b, 0x23, 0x80, 0x0, 0x7,
    0xf8, 0x20, 0x8, 0x2, 0xf, 0xfc,

    /* U+5F3A "强" */
    0xef, 0x8a, 0x22, 0xfb, 0x8, 0x8f, 0xa4, 0xaf,
    0x28, 0xbe, 0x22, 0x8f, 0xee, 0x4,

    /* U+6674 "晴" */
    0x2, 0x1d, 0xfa, 0xbf, 0x51, 0xe, 0xdd, 0x5f,
    0xaa, 0x15, 0x7e, 0xef, 0xd1, 0x8, 0x27, 0x0,

    /* U+66B4 "暴" */
    0x7f, 0x90, 0x27, 0xf9, 0xfe, 0x12, 0x1f, 0xef,
    0xfc, 0x84, 0xda, 0xde, 0xe1, 0x80,

    /* U+672A "未" */
    0x8, 0x2, 0x7, 0xf8, 0x20, 0xff, 0xc3, 0x1,
    0xa0, 0xa4, 0x48, 0xa2, 0x10, 0x80,

    /* U+6C14 "气" */
    0x20, 0x1f, 0xf4, 0x2, 0xfe, 0x80, 0x3f, 0xc0,
    0x10, 0x4, 0x1, 0x40, 0x50, 0xc,

    /* U+6C99 "沙" */
    0x2, 0x8, 0x50, 0xaa, 0x45, 0x25, 0x24, 0x24,
    0x0, 0xa2, 0x8, 0x42, 0x11, 0x82, 0xc0, 0x0,

    /* U+70ED "热" */
    0x24, 0x1f, 0xf0, 0x92, 0x1a, 0x4e, 0xc8, 0x55,
    0x4a, 0x36, 0x86, 0x44, 0x8a, 0x4a, 0x49, 0x0,

    /* U+7279 "特" */
    0x22, 0x15, 0xfb, 0xc8, 0x51, 0xa, 0xfe, 0x61,
    0x3b, 0xf5, 0x44, 0x24, 0x84, 0x10, 0x8e, 0x0,

    /* U+77E5 "知" */
    0x40, 0x10, 0x7, 0xfe, 0x91, 0xa4, 0x49, 0x1f,
    0xc4, 0x91, 0x34, 0x56, 0xf4, 0xc6, 0x11,

    /* U+7D2F "累" */
    0x7f, 0xc8, 0x89, 0xff, 0x22, 0x27, 0xfc, 0x62,
    0x3, 0xc3, 0xfe, 0x5, 0xc, 0x9a, 0x70, 0x80,

    /* U+95F4 "间" */
    0x0, 0x13, 0xf4, 0x5, 0x1, 0xbe, 0x68, 0x9b,
    0xe6, 0x89, 0xa2, 0x6f, 0x98, 0x6, 0xf,

    /* U+9634 "阴" */
    0xf7, 0xd4, 0x6a, 0x34, 0xfa, 0x8c, 0xc6, 0x5f,
    0xf1, 0x88, 0xc4, 0x64, 0xe0,

    /* U+9635 "阵" */
    0x2, 0x1e, 0x42, 0x7f, 0xd2, 0xa, 0x51, 0x4a,
    0x27, 0xf4, 0x88, 0x91, 0x1f, 0xfe, 0x4, 0x40,
    0x80,

    /* U+96E8 "雨" */
    0xff, 0xc2, 0x0, 0x81, 0xfe, 0x88, 0xaa, 0xa9,
    0x9a, 0xaa, 0x99, 0xa2, 0x28, 0x98,

    /* U+96EA "雪" */
    0x7f, 0x82, 0xf, 0xff, 0xad, 0x8, 0xa, 0x87,
    0xf8, 0x2, 0x7f, 0x80, 0x27, 0xf8,

    /* U+96FE "雾" */
    0x3f, 0xc0, 0x40, 0x7f, 0xe5, 0x5a, 0x10, 0x3,
    0xfc, 0x4b, 0x5, 0xcc, 0x3f, 0xc1, 0x4, 0x63,
    0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 55, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 14, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 28, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 42, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 57, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 71, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 85, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 99, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 115, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 131, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 145, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 159, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 175, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 189, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 203, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 217, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 233, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 249, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 265, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 280, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 296, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 311, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 324, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 341, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 355, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 369, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x4e0d, 0x4e71, 0x5197, 0x519b, 0x58fa, 0x5907, 0x5909,
    0x5bef, 0x5bf1, 0x5bf8, 0x5f1a, 0x6654, 0x6694, 0x670a, 0x6bf4,
    0x6c79, 0x70cd, 0x7259, 0x77c5, 0x7d0f, 0x95d4, 0x9614, 0x9615,
    0x96c8, 0x96ca, 0x96de
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 38623, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 27, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t weather_font_cn_12_t = {
#else
lv_font_t weather_font_cn_12_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
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



#endif /*#if WEATHER_FONT_CN_12_T*/

