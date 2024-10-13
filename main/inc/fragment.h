
#ifndef FRAGMENT_H
#define FRAGMENT_H

typedef struct my_fragment_t
{
    lv_fragment_t base;     // 基础片段结构
    const char *name;       // 片段名称
    void *state;            // 用于保存片段状态
    int last_focused_index; // 新增：保存最后聚焦的按钮索引
} my_fragment_t;

// 声明外部变量
extern const lv_fragment_class_t sample_cls;
// 外部声明片段管理器
extern lv_fragment_manager_t *manager;

extern lv_group_t *last_group;

lv_obj_t *create_fragments(lv_obj_t *parent);
void launch_app_fragment(const char *app_name, bool isMainInterface);
void Return_root_page(void);

#endif