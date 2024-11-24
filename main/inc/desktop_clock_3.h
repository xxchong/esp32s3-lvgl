

#ifndef __DESKTOP_CLOCK_3_H
#define __DESKTOP_CLOCK_3_H

#include "icon.h"
LV_FONT_DECLARE(watch_2_cn_font_22_t);
LV_FONT_DECLARE(watch_2_cn_font_14_t);
LV_FONT_DECLARE(watch_2_font_95_t);
LV_FONT_DECLARE(watch_2_font_65_t);
lv_obj_t *lv_clock_watch_3(lv_obj_t *parent, bool is_preview);
void watch_3_time_refresh(void);

#endif
