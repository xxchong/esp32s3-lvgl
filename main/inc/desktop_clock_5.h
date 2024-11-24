
#ifndef __DESKTOP_CLOCK_5_H
#define __DESKTOP_CLOCK_5_H

#include "icon.h"

lv_obj_t *lv_clock_watch_5(lv_obj_t *parent, bool is_preview);
void send_anim_meter_event(void);

void watch_5_time_refresh(void);

#endif
