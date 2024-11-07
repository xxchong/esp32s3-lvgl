#include "sys.h"

// extern SemaphoreHandle_t xBinarySemaphore;
extern lv_indev_t *indev;
extern lv_group_t *group;
extern lv_obj_t *user_area;

lv_group_t *last_group;

/*
 *fragment管理器类似栈，先进后出来
 */
// 声明片段构造函数
static void fragment_ctor(lv_fragment_t *self, void *args);
// 声明创建片段对象的函数
static lv_obj_t *fragment_create_obj(lv_fragment_t *self, lv_obj_t *parent);
// 声明容器删除时的回调函数
static void container_delete(lv_event_t *e);
// 定义根对象指针
static lv_obj_t *root = NULL;

// 定义片段类  片段的实例类
const lv_fragment_class_t sample_cls = {
    .constructor_cb = fragment_ctor,        // 设置构造函数回调
    .create_obj_cb = fragment_create_obj,   // 设置创建对象回调
    .instance_size = sizeof(my_fragment_t), // 设置实例大小
};

// extern lv_obj_t *grid;                                  // 主页面的用户容器
// extern lv_group_t *group;                               // 主页面的group

lv_fragment_manager_t *manager = NULL; // 全局片段管理器
// extern lv_obj_t *wifi_list_btns[WIFI_LIST_COUNT];       // 外部wifi列表按钮数组
// extern lv_obj_t *setting_list_btns[SETTING_LIST_COUNT]; // 外部wifi列表按钮数组

void Return_root_page(void)
{
    // 恢复主页面的group
    // lv_indev_set_group(indev, group);
    lv_obj_add_flag(root, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_tile(lv_obj_get_parent(lv_obj_get_parent(root)), lv_obj_get_parent(root), LV_ANIM_ON);
}

// 创建片段的主函数
lv_obj_t *create_fragments(lv_obj_t *parent)
{
    // 创建根对象
    root = lv_obj_create(parent);
    lv_obj_center(root);
    lv_obj_set_size(root, 240, 260);

    remove_styles(root, true, true, true, true);
    lv_obj_set_style_pad_all(root, 0, 0);
    // 创建片段管理器
    manager = lv_fragment_manager_create(NULL);
    // 添加删除事件回调，用于清理片段管理器
    lv_obj_add_event_cb(root, container_delete, LV_EVENT_DELETE, manager);
    lv_obj_add_flag(root, LV_OBJ_FLAG_HIDDEN);
    // 将根对象添加到新的 group
    return root;
}

// 启动应用片段
void launch_app_fragment(const char *app_name, bool isMainInterface)
{
    if (manager == NULL)
    {
        printf("错误：片段管理器未初始化\n");
        return;
    }

    size_t size = lv_fragment_manager_get_stack_size(manager);
    printf("current stack size:%d\n", size);

    if (lv_tileview_get_tile_act(root_page->tileview) == root_page->page2)
    {

        lv_obj_clear_flag(root, LV_OBJ_FLAG_HIDDEN);
        lv_fragment_t *new_fragment = lv_fragment_create(&sample_cls, (void *)app_name);
        lv_fragment_manager_push(manager, new_fragment, &root);

        size = lv_fragment_manager_get_stack_size(manager);
        printf("after push stack size:%d\n", size);
    }
}
// 片段构造函数实现
static void fragment_ctor(lv_fragment_t *self, void *args)
{
    LV_UNUSED(args);
    my_fragment_t *fragment = (my_fragment_t *)self;
    fragment->name = strdup((char *)args); // 复制传入的名称
    fragment->state = NULL;                // 初始化状态
    fragment->last_focused_index = 0;      // 初始化为0或其他适当的默认值
}

// 创建片段里面的内容对象
static lv_obj_t *fragment_create_obj(lv_fragment_t *self, lv_obj_t *parent)
{
    my_fragment_t *fragment = (my_fragment_t *)self;
    const char *name = fragment->name;
    // 创建一个容器作为页面的主体
    static lv_obj_t *page;
    page = lv_obj_create(parent);
    lv_obj_set_size(page, 240, 265);
    remove_styles(page, true, false, true, true);
    lv_obj_set_style_pad_all(page, 0, 0);
    // lv_obj_set_style_radius(page, 0, 0);

    // 根据 fragment 名称创建不同的内容
    // if (strcmp(name, "Game") == 0)
    // {
    //     create_game_app(page);
    // }
    // else if (strcmp(name, "Setting") == 0)
    // {
    //     create_setting_app(page);
    // }
    // else if (strcmp(name, "Serial") == 0)
    // {
    //     create_serial_app(page);
    // }
    // else if (strcmp(name, "Music") == 0)
    // {
    //     create_music_app(page);
    // }
    // else if (strcmp(name, "Tools") == 0)
    // {
    //     tools_list_create(page);
    // }
    // else if (strcmp(name, "Calendar") == 0)
    // {
    //     create_gpio_app(page);
    // }
    // else if (strcmp(name, "MQTT") == 0)
    // {
    //     create_mqtt_app(page);
    // }
    // else if (strcmp(name, "BlueTooth") == 0)
    // {
    //     // create_bluetooth_app(page);
    // }
    // else if (strcmp(name, "Weather") == 0)
    // {
    //     in_weather_app = true;
    //     create_weather_app(page);
    // }
    // else if (strcmp(name, "Calculators1") == 0)
    // {
    //     calculators_create(page);
    //     lv_obj_set_tile(root_page->tileview, root_page->page2, LV_ANIM_OFF);
    // }
    // else if (strcmp(name, "Calculators2") == 0)
    // {
    //     calculators_create1(page);
    //     lv_obj_set_tile(root_page->tileview, root_page->page2, LV_ANIM_OFF);

    // }
    // else if (strcmp(name, "Calculators3") == 0)
    // {
    //     calculators_create2(page);
    //     lv_obj_set_tile(root_page->tileview, root_page->page2, LV_ANIM_OFF);

    // }
    // else if (strcmp(name, "WiFi1") == 0)
    // {
    //     // create_wifi_list(page);
    // }

    return page;
}

// 容器删除时的回调函数实现
static void container_delete(lv_event_t *e)
{
    lv_fragment_manager_t *manager = (lv_fragment_manager_t *)lv_event_get_user_data(e); // 获取用户数据（片段管理器）
    lv_fragment_manager_del(manager);                                                    // 删除片段管理器
}