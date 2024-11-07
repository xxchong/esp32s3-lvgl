#ifndef __CLOCK_WIDGET_H
#define __CLOCK_WIDGET_H

#include "icon.h"
lv_obj_t *create_clock_widget1(lv_obj_t *parent);
lv_obj_t *create_clock_widget2(lv_obj_t *parent);

extern lv_timer_t *clock_widget_time_timer;

#endif
