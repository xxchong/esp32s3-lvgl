
#ifndef __CLOCK_H
#define __CLOCK_H

LV_FONT_DECLARE(Clock_font_24_t)
LV_FONT_DECLARE(Clock_font_cn_16_t)

typedef struct
{
    lv_obj_t *clock_page;
    lv_obj_t *clock_tabview;
    lv_obj_t *tab_Alarm;
    lv_obj_t *tab_Stopwatch;
    lv_obj_t *tab_timer;
} Clock_app_t;

// 添加新的结构体用于保存时间选择器控件
typedef struct
{
    lv_obj_t *popup;
    lv_obj_t *hour_roller;
    lv_obj_t *minute_roller;
} time_picker_t;


// 添加闹钟项结构体
typedef struct {
    uint8_t hour;
    uint8_t minute;
    bool enabled;
} alarm_item_t;


#define minute_options "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n" \
                       "10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n" \
                       "20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n" \
                       "30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n" \
                       "40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n" \
                       "50\n51\n52\n53\n54\n55\n56\n57\n58\n59"

#define hour_options "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n" \
                     "10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n" \
                     "20\n21\n22\n23"

lv_obj_t* create_clock_app(void);
void cleanup_clock_app(void);
void stop_stopwatch_timer(void);


#endif
