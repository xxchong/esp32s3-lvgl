/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: --bpp 1 --size 10 --no-compress --font MiSans-Normal.ttf --symbols 广州市海珠区茂名今日明天后天气去预报温度湿度更新近三 --format lvgl -o weather_font_cn_10_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef WEATHER_FONT_CN_10_T
#define WEATHER_FONT_CN_10_T 1
#endif

#if WEATHER_FONT_CN_10_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+4E09 "三" */
    0x7f, 0x0, 0x0, 0xf, 0xe0, 0x0, 0x0, 0x1,
    0xff,

    /* U+4ECA "今" */
    0x18, 0x24, 0x52, 0x89, 0x7e, 0x2, 0x4, 0x8,

    /* U+533A "区" */
    0xff, 0x82, 0xa4, 0x98, 0x94, 0xa2, 0x80, 0xff,

    /* U+53BB "去" */
    0x8, 0x3f, 0x82, 0x1, 0xf, 0xf8, 0x80, 0x88,
    0xfe, 0x0, 0x0,

    /* U+540D "名" */
    0x10, 0x1f, 0x63, 0x14, 0x8, 0x7f, 0x21, 0x21,
    0x3f, 0x21,

    /* U+540E "后" */
    0x0, 0x3f, 0x90, 0xf, 0xf4, 0x2, 0xf9, 0x84,
    0xc2, 0x9f, 0x50, 0x80,

    /* U+5929 "天" */
    0x7f, 0x4, 0x2, 0x1f, 0xf0, 0x80, 0xa0, 0x50,
    0xc6, 0x80, 0x80,

    /* U+5DDE "州" */
    0x24, 0x92, 0x4d, 0xb6, 0xda, 0xd9, 0x24, 0x92,
    0x89, 0xc0, 0x80,

    /* U+5E02 "市" */
    0x8, 0x7f, 0xc2, 0xf, 0xe4, 0x92, 0x49, 0x24,
    0x96, 0x8, 0x0,

    /* U+5E7F "广" */
    0x4, 0x3f, 0xd0, 0x8, 0x4, 0x2, 0x1, 0x1,
    0x0, 0x80, 0x0,

    /* U+5EA6 "度" */
    0x4, 0x3f, 0xd4, 0x4f, 0xf5, 0x12, 0x71, 0xfc,
    0xa2, 0x8e, 0x59, 0xc0,

    /* U+62A5 "报" */
    0x5f, 0x51, 0x52, 0x5f, 0xd9, 0x56, 0x56, 0xd9,
    0x10,

    /* U+65B0 "新" */
    0x20, 0xff, 0x95, 0x1f, 0x82, 0x7f, 0xe9, 0xd5,
    0x5a, 0x6d, 0x4, 0x80,

    /* U+65E5 "日" */
    0xff, 0x6, 0xc, 0x1f, 0xf0, 0x60, 0xff, 0x82,

    /* U+660E "明" */
    0xef, 0xa9, 0xaf, 0xe9, 0xa9, 0xaf, 0xf1, 0xb3,

    /* U+66F4 "更" */
    0xff, 0x10, 0xfe, 0x7e, 0x92, 0x7e, 0x30, 0xcf,

    /* U+6C14 "气" */
    0x40, 0x7f, 0x80, 0xfe, 0x0, 0xfc, 0x4, 0x5,
    0x7, 0x3,

    /* U+6D77 "海" */
    0x0, 0x2f, 0xc4, 0x17, 0xe5, 0x51, 0xfd, 0x95,
    0x3f, 0x87, 0x0,

    /* U+6E29 "温" */
    0x5f, 0xf, 0xa4, 0x49, 0xc5, 0xf3, 0x59, 0xad,
    0x7f,

    /* U+6E7F "湿" */
    0x9f, 0x28, 0xa7, 0xcb, 0xe0, 0xa3, 0xda, 0x69,
    0x7f,

    /* U+73E0 "珠" */
    0x4, 0x5f, 0x54, 0x44, 0xff, 0x44, 0x4e, 0xd5,
    0x4,

    /* U+8302 "茂" */
    0xff, 0x80, 0x2, 0x4f, 0xf4, 0x92, 0x51, 0x13,
    0x35, 0xa3, 0x0,

    /* U+8FD1 "近" */
    0x9f, 0x28, 0x4, 0x1b, 0xe5, 0x22, 0x91, 0x89,
    0x7e,

    /* U+9884 "预" */
    0xff, 0xc8, 0x84, 0xfb, 0xea, 0x5a, 0x96, 0xa4,
    0x73, 0x23
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 160, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 160, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 36, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 46, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 58, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 69, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 80, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 91, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 102, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 114, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 123, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 135, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 143, .adv_w = 160, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 160, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 169, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 207, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 218, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 160, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xc1, 0x531, 0x5b2, 0x604, 0x605, 0xb20, 0xfd5,
    0xff9, 0x1076, 0x109d, 0x149c, 0x17a7, 0x17dc, 0x1805, 0x18eb,
    0x1e0b, 0x1f6e, 0x2020, 0x2076, 0x25d7, 0x34f9, 0x41c8, 0x4a7b
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 19977, .range_length = 19068, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 24, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t weather_font_cn_10_t = {
#else
lv_font_t weather_font_cn_10_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
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



#endif /*#if WEATHER_FONT_CN_10_T*/

