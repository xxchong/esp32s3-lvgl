/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --font MiSans-Normal.ttf --symbols 手表型号固件版本主控芯片LVGL版本操作系统关于  --format lvgl -o version_font_cn_14_t.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef VERSION_FONT_CN_14_T
#define VERSION_FONT_CN_14_T 1
#endif

#if VERSION_FONT_CN_14_T

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0047 "G" */
    0x3c, 0x63, 0x40, 0x80, 0x80, 0x87, 0x81, 0x81,
    0x41, 0x63, 0x3e,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x82, 0xf,
    0xc0,

    /* U+0056 "V" */
    0xc0, 0xa0, 0xd0, 0x4c, 0x22, 0x21, 0x10, 0xc8,
    0x28, 0x14, 0x6, 0x2, 0x0,

    /* U+4E3B "主" */
    0x4, 0x0, 0x40, 0x2, 0xf, 0xff, 0x6, 0x0,
    0x60, 0x6, 0x7, 0xfe, 0x6, 0x0, 0x60, 0x6,
    0xf, 0xff,

    /* U+4E8E "于" */
    0x7f, 0xe0, 0x20, 0x2, 0x0, 0x20, 0xff, 0xf0,
    0x20, 0x2, 0x0, 0x20, 0x2, 0x0, 0x20, 0x2,
    0x1, 0xc0,

    /* U+4EF6 "件" */
    0x10, 0x80, 0x94, 0x9, 0x20, 0x4f, 0xf2, 0x48,
    0x36, 0x41, 0xa2, 0x14, 0x10, 0x2f, 0xf9, 0x4,
    0x8, 0x20, 0x41, 0x2, 0x8, 0x0,

    /* U+4F5C "作" */
    0x12, 0x1, 0x20, 0x27, 0xf2, 0x50, 0x69, 0x6,
    0x90, 0xe1, 0xfa, 0x10, 0x21, 0x2, 0x1f, 0x21,
    0x2, 0x10, 0x21, 0x0,

    /* U+5173 "关" */
    0x20, 0x41, 0x8, 0x9, 0x7, 0xfe, 0x4, 0x0,
    0x40, 0x4, 0xf, 0xff, 0x6, 0x0, 0x60, 0x9,
    0x3, 0xc, 0xc0, 0x70,

    /* U+53F7 "号" */
    0x3f, 0xc2, 0x4, 0x20, 0x43, 0xfc, 0x0, 0xf,
    0xff, 0x20, 0x3, 0xfc, 0x0, 0x40, 0x4, 0x0,
    0x40, 0xf8,

    /* U+56FA "固" */
    0xff, 0xf0, 0x86, 0x10, 0xdf, 0xd8, 0x43, 0x3e,
    0x64, 0x4c, 0x89, 0x9f, 0x30, 0x7, 0xff, 0xc0,
    0x10,

    /* U+578B "型" */
    0x0, 0x27, 0xea, 0x24, 0xa2, 0x4a, 0xfe, 0xa2,
    0x42, 0x44, 0x24, 0x4e, 0x2, 0x7, 0xfe, 0x2,
    0x0, 0x20, 0xff, 0xf0,

    /* U+624B "手" */
    0x0, 0x67, 0xf8, 0x2, 0x0, 0x20, 0x2, 0x7,
    0xfe, 0x2, 0x0, 0x20, 0xff, 0xf0, 0x20, 0x2,
    0x0, 0x20, 0x1c, 0x0,

    /* U+63A7 "控" */
    0x20, 0x82, 0x8, 0x2f, 0xff, 0x81, 0x21, 0x42,
    0x22, 0x3c, 0x1e, 0x0, 0x27, 0xe2, 0x8, 0x20,
    0x82, 0xff, 0xc0, 0x0,

    /* U+64CD "操" */
    0x20, 0x1, 0x3f, 0x89, 0x4, 0xe7, 0xc2, 0x77,
    0x94, 0xa4, 0xe5, 0x3c, 0xef, 0x2f, 0xf9, 0xe,
    0x8, 0xa8, 0x49, 0x36, 0x88, 0x80,

    /* U+672C "本" */
    0x2, 0x0, 0x10, 0x0, 0x80, 0xff, 0xe0, 0x70,
    0x3, 0x80, 0x2a, 0x2, 0x48, 0x12, 0x41, 0x11,
    0x17, 0xf6, 0x4, 0x0, 0x20, 0x0,

    /* U+7247 "片" */
    0x20, 0x82, 0x8, 0x20, 0x82, 0x8, 0x3f, 0xf2,
    0x0, 0x20, 0x3, 0xf8, 0x20, 0x82, 0x8, 0x40,
    0x84, 0x8, 0x80, 0x80,

    /* U+7248 "版" */
    0x50, 0x32, 0x9e, 0x14, 0x80, 0xa4, 0x7, 0xbf,
    0x21, 0x89, 0xa, 0x4e, 0x54, 0x52, 0xa2, 0xb2,
    0x15, 0x19, 0xab, 0x69, 0x31, 0x0,

    /* U+7CFB "系" */
    0x7f, 0xf0, 0x40, 0x18, 0xc7, 0xf0, 0x4, 0x81,
    0x84, 0x7f, 0xe0, 0x21, 0x12, 0x82, 0x26, 0x42,
    0x38, 0xe0,

    /* U+7EDF "统" */
    0x21, 0x2, 0x10, 0x4f, 0xfd, 0x20, 0xb2, 0x46,
    0x42, 0x4f, 0xe4, 0x28, 0xf2, 0x80, 0x29, 0x14,
    0x9e, 0x49, 0x18, 0x70,

    /* U+82AF "芯" */
    0x10, 0x81, 0x8, 0xff, 0xf1, 0x8, 0x4, 0x0,
    0x20, 0x12, 0x5, 0x22, 0x50, 0x25, 0xb, 0x90,
    0x91, 0x8, 0xf, 0x80,

    /* U+8868 "表" */
    0x4, 0x0, 0x40, 0xff, 0xf0, 0x40, 0x7f, 0xe0,
    0x40, 0xff, 0xf0, 0xe2, 0x1a, 0x63, 0x18, 0xd0,
    0xc1, 0x63, 0x18, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 65, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 164, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 147, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 224, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 224, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 70, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 92, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 112, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 132, .adv_w = 224, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 150, .adv_w = 224, .box_w = 11, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 167, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 187, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 207, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 227, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 249, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 271, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 291, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 313, .adv_w = 224, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 331, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 351, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 371, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x27, 0x2c, 0x36, 0x4e1b, 0x4e6e, 0x4ed6, 0x4f3c,
    0x5153, 0x53d7, 0x56da, 0x576b, 0x622b, 0x6387, 0x64ad, 0x670c,
    0x7227, 0x7228, 0x7cdb, 0x7ebf, 0x828f, 0x8848
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 34889, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 22, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    2, 4,
    3, 2,
    3, 4,
    4, 2
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -9, -9, -30, -8
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 4,
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
const lv_font_t version_font_cn_14_t = {
#else
lv_font_t version_font_cn_14_t = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
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



#endif /*#if VERSION_FONT_CN_14_T*/

