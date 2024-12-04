
#ifndef __TOOLS_H
#define __TOOLS_H

#include "icon.h"

#define TOOLS_LIST_COUNT 3
LV_FONT_DECLARE(app_tools_cn_font_16_t);

#define LIST_ICON USER_APP_SYMBOL_CALCULATOR,USER_APP_SYMBOL_THERMOMETER,USER_APP_SYMBOL_COMPASS

#define LIST_NAME "计算器", "温湿度", "指南针"

extern lv_obj_t *tools_list_btns[TOOLS_LIST_COUNT]; // 定义列表按钮数组

lv_obj_t *tools_list_create(void);

#endif
