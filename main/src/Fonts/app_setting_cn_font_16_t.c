/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --font MiSans-Normal.ttf --symbols WLAN蓝牙我的设备 --format lvgl -o app_setting_cn_font_16_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef APP_SETTING_CN_FONT_16_T
#define APP_SETTING_CN_FONT_16_T 1
#endif

#if APP_SETTING_CN_FONT_16_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0041 "A" */
    0xc, 0x3, 0x0, 0xe0, 0x68, 0x13, 0x4, 0xc3,
    0x10, 0xfe, 0x60, 0x98, 0x24, 0xf, 0x1,

    /* U+004C "L" */
    0x81, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x81,
    0x2, 0x7, 0xf0,

    /* U+004E "N" */
    0x80, 0xe0, 0x78, 0x36, 0x19, 0xc, 0xc6, 0x33,
    0x9, 0x86, 0xc1, 0xe0, 0x70, 0x10,

    /* U+0057 "W" */
    0xc1, 0x2, 0x83, 0xd, 0xa, 0x12, 0x14, 0x26,
    0x2c, 0x44, 0xc9, 0x89, 0x12, 0x1a, 0x24, 0x14,
    0x38, 0x30, 0x60, 0x60, 0xc0, 0xc1, 0x80,

    /* U+5907 "备" */
    0x0, 0x0, 0x18, 0x0, 0x7f, 0xe1, 0xc0, 0x86,
    0xc6, 0x0, 0x70, 0x7, 0x3c, 0x70, 0x7, 0x3f,
    0xf8, 0x42, 0x10, 0x84, 0x21, 0xff, 0xc2, 0x10,
    0x87, 0xff, 0x8, 0x2, 0x0,

    /* U+6211 "我" */
    0x0, 0x80, 0x3a, 0x8f, 0x9, 0x4, 0x22, 0x10,
    0x83, 0xff, 0xf1, 0x8, 0x4, 0x22, 0x16, 0x91,
    0xf2, 0xcd, 0x6, 0x4, 0x31, 0x13, 0xc4, 0x58,
    0xa7, 0x1, 0x80,

    /* U+7259 "牙" */
    0xff, 0xfc, 0x1, 0x2, 0x4, 0x18, 0x10, 0x7f,
    0xfc, 0x5, 0x0, 0x24, 0x1, 0x90, 0xc, 0x40,
    0x61, 0x6, 0x4, 0x30, 0x10, 0x3, 0xc0,

    /* U+7684 "的" */
    0x20, 0x81, 0x4, 0x8, 0x41, 0xf3, 0xf8, 0xa0,
    0xc7, 0x6, 0x20, 0x31, 0x21, 0xf8, 0x8c, 0x42,
    0x62, 0x3, 0x10, 0x18, 0x80, 0xfc, 0x6, 0x3,
    0xc0,

    /* U+84DD "蓝" */
    0x8, 0x43, 0xff, 0xf0, 0x84, 0x0, 0x20, 0x48,
    0x81, 0x27, 0xf4, 0x96, 0x12, 0x84, 0x0, 0x0,
    0xff, 0xe2, 0x49, 0x89, 0x26, 0x24, 0x9b, 0xff,
    0xf0,

    /* U+8BBE "设" */
    0x0, 0x1, 0x87, 0xc3, 0x11, 0x6, 0x44, 0x3,
    0x10, 0x18, 0x7e, 0x0, 0x8, 0xfe, 0x22, 0x8,
    0x84, 0x42, 0x1b, 0xb, 0x38, 0x38, 0xe0, 0x8c,
    0x60, 0xc0, 0x40
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 168, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 26, .adv_w = 187, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 243, .box_w = 15, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 256, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 92, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 119, .adv_w = 256, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 142, .adv_w = 256, .box_w = 13, .box_h = 15, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 167, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 192, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xb, 0xd, 0x16, 0x58c6, 0x61d0, 0x7218, 0x7643,
    0x849c, 0x8b7d
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 65, .range_length = 35710, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 10, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    1, 4,
    2, 4,
    4, 1
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -17, -21, -17
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
const lv_font_t app_setting_cn_font_16_t = {
#else
lv_font_t app_setting_cn_font_16_t = {
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



#endif /*#if APP_SETTING_CN_FONT_16_T*/

