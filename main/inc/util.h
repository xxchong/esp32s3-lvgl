#ifndef __UTIL_H
#define __UTIL_H
void remove_styles(lv_obj_t *parent, bool remove_border, bool remove_opa, bool remove_scrollbar, bool remove_shadow);
void set_focus(lv_obj_t **btns, int count, int last_index);
void initialize_sntp(void);
void get_time_string(char *buffer, size_t buffer_size);
struct tm get_timeinfo(void);
lv_obj_t *create_app_btn_return(lv_obj_t *parent);
void gestureCallback(lv_event_t *event);
lv_obj_t *create_page(const char *name);
void cleanup_page(lv_obj_t *page);
void back_to_home(lv_obj_t *page);
void get_now_time(void);
void stop_watch_timer(void);

extern struct tm *timeinfo;

#endif
