#ifndef __UTIL_H
#define __UTIL_H
void remove_styles(lv_obj_t *parent, bool remove_border, bool remove_opa, bool remove_scrollbar, bool remove_shadow);
void set_focus(lv_obj_t **btns, int count, int last_index);
void initialize_sntp(void);
void get_time_string(char* buffer, size_t buffer_size);
#endif
