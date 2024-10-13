#include <lvgl.h>
void remove_styles(lv_obj_t *parent, bool remove_border, bool remove_opa, bool remove_scrollbar, bool remove_shadow)
{
    if (parent == NULL)
        return;
    // 移除边框
    if (remove_border)
    {
        lv_obj_set_style_border_width(parent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    // 设置透明
    if (remove_opa)
    {
        lv_obj_set_style_bg_opa(parent, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    // 移除滚动条
    if (remove_scrollbar)
    {
        lv_obj_set_scrollbar_mode(parent, LV_SCROLLBAR_MODE_OFF);
    }

    // 移除阴影
    if (remove_shadow)
    {
        lv_obj_set_style_shadow_width(parent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}


//列表返回菜单设置焦点
void set_focus(lv_obj_t **btns, int count, int last_index) {
    if (last_index >= 0 && last_index < count) {
        if (btns[last_index] != NULL) { // 检查指针是否有效
            lv_group_focus_obj(btns[last_index]);
        } else {
            // printf("btns[%d] is NULL\n", last_index);
        }
    } else {
        lv_group_focus_obj(btns[0]);  // 默认到第一个
    }
}