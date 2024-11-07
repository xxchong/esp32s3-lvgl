#ifndef __TOOLS_H
#define __TOOLS_H

#include "icon.h"

#define TOOLS_LIST_COUNT 3

#define LIST_ICON USER_SYMBOL_TOOLS, USER_SYMBOL_TOOLS, USER_SYMBOL_TOOLS

#define LIST_NAME "Calculators1", "Calculators2", "Calculators3"

extern lv_obj_t *tools_list_btns[TOOLS_LIST_COUNT]; // 定义列表按钮数组

lv_obj_t *tools_list_create(void);

#endif
