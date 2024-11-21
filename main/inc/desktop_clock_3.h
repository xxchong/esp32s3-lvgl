

#ifndef __DESKTOP_CLOCK_3_H
#define __DESKTOP_CLOCK_3_H

#include "icon.h"
LV_FONT_DECLARE(watch_2_cn_font_22_t); 
LV_FONT_DECLARE(watch_2_cn_font_14_t); 
LV_FONT_DECLARE(watch_2_font_95_t); 
LV_FONT_DECLARE(watch_2_font_65_t); 
lv_obj_t * lv_clock_watch_2(lv_obj_t *parent,bool is_preview);
extern lv_timer_t *clock_watch_time_timer_2;

#endif
