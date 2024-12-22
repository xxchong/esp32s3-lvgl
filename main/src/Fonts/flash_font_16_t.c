/*
*---------------------------------------------------------------
*                        Lvgl Font Tool                         
*                                                               
* 注:使用unicode编码                                              
* 注:本字体文件由Lvgl Font Tool V0.4 生成                          
* 作者:阿里(qq:617622104)                                         
*---------------------------------------------------------------
*/


#include "lvgl/lvgl.h"
#include "esp_partition.h"
#include "esp_heap_caps.h"


typedef struct{
    uint16_t min;
    uint16_t max;
    uint8_t  bpp;
    uint8_t  reserved[3];
}x_header_t;
typedef struct{
    uint32_t pos;
}x_table_t;
typedef struct{
    uint8_t adv_w;
    uint8_t box_w;
    uint8_t box_h;
    int8_t  ofs_x;
    int8_t  ofs_y;
    uint8_t r;
}glyph_dsc_t;


static x_header_t __g_xbf_hd = {
    .min = 0x0009,
    .max = 0xffe5,
    .bpp = 4,
};


static uint8_t __g_font_buf[714];//如bin文件存在SPI FLASH可使用此buff

esp_partition_t* partition_res=NULL;
// static uint8_t *__user_font_getdata(int offset, int size)
// {
//     static uint8_t first_in = 1;  
//     if(first_in==1)
//     {      
//         partition_res=esp_partition_find_first(0x01,0x40,NULL);//这个函数第一个参数是我们分区表的第四行的，第二列的参数，第二个是第三列的值
//         first_in=0;
//         if (partition_res == NULL)
//         {
//             printf("Failed to open file for reading\n");
//             return NULL;
//         }
//         else
//         {
//              printf("Successfully open file for reading\n");
//         }
//     }
//     esp_err_t res=esp_partition_read(partition_res,offset,__g_font_buf,size);//读取数据
//     if(res!=ESP_OK)
//     {
//         printf("Failed to reading\n");
//     }

//     return __g_font_buf;
// }

// 添加PSRAM缓存指针
static uint8_t *font_psram_cache = NULL;
static size_t font_cache_size = 0;

// 修改数据获取函数
static uint8_t *__user_font_getdata(int offset, int size)
{
    static uint8_t first_in = 1;  
    if(first_in == 1)
    {      
        partition_res = esp_partition_find_first(0x01, 0x40, NULL);
        if (partition_res == NULL) {
            printf("Failed to open file for reading\n");
            return NULL;
        }

        // 获取分区大小并分配PSRAM
        size_t partition_size = partition_res->size;
        font_psram_cache = heap_caps_malloc(partition_size, MALLOC_CAP_SPIRAM);
        if (font_psram_cache == NULL) {
            printf("Failed to allocate PSRAM\n");
            return NULL;
        }
        font_cache_size = partition_size;

        // 一次性将整个字体文件读入PSRAM
        esp_err_t res = esp_partition_read(partition_res, 0, font_psram_cache, partition_size);
        if (res != ESP_OK) {
            printf("Failed to read font data to PSRAM\n");
            heap_caps_free(font_psram_cache);
            font_psram_cache = NULL;
            return NULL;
        }
        
        first_in = 0;
        printf("Successfully loaded font to PSRAM\n");
    }

    // 直接从PSRAM返回数据
    if (font_psram_cache && offset + size <= font_cache_size) {
        return &font_psram_cache[offset];
    }
    
    return NULL;
}



static const uint8_t * __user_font_get_bitmap(const lv_font_t * font, uint32_t unicode_letter) {
    if( unicode_letter>__g_xbf_hd.max || unicode_letter<__g_xbf_hd.min ) {
        return NULL;
    }
    uint32_t unicode_offset = sizeof(x_header_t)+(unicode_letter-__g_xbf_hd.min)*4;
    uint32_t *p_pos = (uint32_t *)__user_font_getdata(unicode_offset, 4);
    if( p_pos[0] != 0 ) {
        uint32_t pos = p_pos[0];
        glyph_dsc_t * gdsc = (glyph_dsc_t*)__user_font_getdata(pos, sizeof(glyph_dsc_t));
        return __user_font_getdata(pos+sizeof(glyph_dsc_t), gdsc->box_w*gdsc->box_h*__g_xbf_hd.bpp/8);
    }
    return NULL;
}


static bool __user_font_get_glyph_dsc(const lv_font_t * font, lv_font_glyph_dsc_t * dsc_out, uint32_t unicode_letter, uint32_t unicode_letter_next) {
    if( unicode_letter>__g_xbf_hd.max || unicode_letter<__g_xbf_hd.min ) {
        return NULL;
    }
    uint32_t unicode_offset = sizeof(x_header_t)+(unicode_letter-__g_xbf_hd.min)*4;
    uint32_t *p_pos = (uint32_t *)__user_font_getdata(unicode_offset, 4);
    if( p_pos[0] != 0 ) {
        glyph_dsc_t * gdsc = (glyph_dsc_t*)__user_font_getdata(p_pos[0], sizeof(glyph_dsc_t));
        dsc_out->adv_w = gdsc->adv_w;
        dsc_out->box_h = gdsc->box_h;
        dsc_out->box_w = gdsc->box_w;
        dsc_out->ofs_x = gdsc->ofs_x;
        dsc_out->ofs_y = gdsc->ofs_y;
        dsc_out->bpp   = __g_xbf_hd.bpp;
        return true;
    }
    return false;
}


//Alibaba PuHuiTi 3.0 45 Light,,-1
//字模高度：22
//XBF字体,外部bin文件
lv_font_t flash_font_16_t = {
    .get_glyph_bitmap = __user_font_get_bitmap,
    .get_glyph_dsc = __user_font_get_glyph_dsc,
    .line_height = 22,
    .base_line = 0,
};

