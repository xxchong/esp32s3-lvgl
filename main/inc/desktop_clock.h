#ifndef __DESKTOP_CLOCK_H
#define __DESKTOP_CLOCK_H

#include "icon.h"
void create_desktop_clock_2(lv_obj_t *parent);
void lv_clock_demo(lv_obj_t *parent);

extern lv_timer_t *clock_watch_time_timer;

#endif
