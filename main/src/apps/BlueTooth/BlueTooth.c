#include <sys.h>

extern lv_indev_t *indev;
extern lv_obj_t *user_area;
typedef struct
{
    lv_group_t *group;
    lv_obj_t *btn_return;
    lv_obj_t *label_desc;
    lv_obj_t *label_btn;
} BlueTooth;

static BlueTooth *bluetooth_app;

static void btn_return_cb(lv_event_t *e)
{
    size_t size = lv_fragment_manager_get_stack_size(manager);
    printf("当前栈内有%d个内容\n", size); // 添加调试信息
    if (size > 1)                         // 大于二级界面
    {
    }
    else if (size == 1) // 二级界面
    {
        lv_fragment_manager_pop(manager); // 弹出当前片段
        Return_root_page();
    }
}

void create_bluetooth_app(lv_obj_t *parent)
{
    // 确保 bluetooth_app 已经被分配内存
    if (bluetooth_app == NULL)
    {
        bluetooth_app = (BlueTooth *)malloc(sizeof(BlueTooth));
        if (bluetooth_app == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for bluetooth_app\n");
            return;
        }
        // 初始化成员变量
        bluetooth_app->group = NULL;
        bluetooth_app->btn_return = NULL;
        bluetooth_app->label_desc = NULL;
        bluetooth_app->label_btn = NULL;
    }
    bluetooth_app->group = lv_group_create();
    lv_indev_set_group(indev, bluetooth_app->group);

    // 创建描述标签
    bluetooth_app->label_desc = lv_label_create(parent);
    lv_obj_center(bluetooth_app->label_desc);
    lv_obj_set_style_text_color(bluetooth_app->label_desc, lv_color_black(), 0);
    lv_label_set_text_fmt(bluetooth_app->label_desc, "This is BlueTooth app");
    printf("This is BlueTooth app\n");

    // 创建返回按钮
    bluetooth_app->btn_return = lv_btn_create(parent);
    lv_obj_set_size(bluetooth_app->btn_return, 15, 15);

    remove_styles(bluetooth_app->btn_return, false, true, true, true);
    lv_obj_set_style_bg_color(bluetooth_app->btn_return, lv_color_white(), 0);
    lv_obj_set_style_border_width(bluetooth_app->btn_return, 1, 0);
    lv_obj_set_style_border_color(bluetooth_app->btn_return, lv_color_black(), 0);

    lv_obj_align_to(bluetooth_app->btn_return, parent, LV_ALIGN_TOP_LEFT, 2, 2);

    // 创建按钮上的标签
    bluetooth_app->label_btn = lv_label_create(bluetooth_app->btn_return);
    lv_obj_set_style_text_font(bluetooth_app->label_btn, &my_symbol_font_10_t, 0);
    lv_label_set_text(bluetooth_app->label_btn, USER_SYMBOL_RETURN2);
    lv_obj_center(bluetooth_app->label_btn);
    lv_obj_set_style_text_color(bluetooth_app->label_btn, lv_color_black(), 0);

    // 配置按钮事件（如果需要）
    lv_obj_add_event_cb(bluetooth_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    lv_group_add_obj(bluetooth_app->group, bluetooth_app->btn_return);
}
