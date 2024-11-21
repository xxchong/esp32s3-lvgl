#ifndef __DESKTOP_CLOCK_1_H
#define __DESKTOP_CLOCK_1_H

#include "icon.h"
LV_FONT_DECLARE(desktop_watch_font_80_t);

lv_obj_t * lv_clock_watch_3(lv_obj_t *parent, bool is_preview);


extern lv_timer_t *clock_watch_time_timer_3;

#endif

