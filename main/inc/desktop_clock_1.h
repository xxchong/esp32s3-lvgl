#ifndef __DESKTOP_CLOCK_1_H
#define __DESKTOP_CLOCK_1_H

#include "icon.h"
LV_FONT_DECLARE(desktop_watch_font_80_t);

lv_obj_t * lv_clock_watch_1(lv_obj_t *parent, bool is_preview);
void watch_1_time_refresh(void);

#endif

