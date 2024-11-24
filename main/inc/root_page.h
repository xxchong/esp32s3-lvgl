
#ifndef __ROOT_PAGE_H
#define __ROOT_PAGE_H

typedef struct
{
    lv_obj_t *root_page;
} root_page_t;

lv_obj_t *create_root(void);
void del_root_page_time_timer(void);
#endif
