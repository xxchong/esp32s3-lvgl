#include "sys.h"




typedef struct
{
    lv_obj_t *version_page;
    lv_obj_t *btn_return;

} Version_page_t;

static Version_page_t *version_app;


static void btn_return_cb(lv_event_t *e)
{
    //返回上一级
    lv_page->setting_page = create_setting_app();
    lv_scr_load_anim(lv_page->setting_page, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, true);
}
lv_obj_t *create_version_app(void)
{
    if (version_app != NULL)
    {
        free(version_app);
        version_app = NULL;
    }
    if (version_app == NULL)
    {
        version_app = (Version_page_t *)calloc(1, sizeof(Version_page_t));
    }
    version_app->version_page = create_page("Version"); //创建主页面
    lv_obj_set_style_bg_color(version_app->version_page, lv_color_black(), 0);

    // 创建返回按钮
    version_app->btn_return = create_app_btn_return(version_app->version_page);
    lv_obj_set_style_text_color(lv_obj_get_child(version_app->btn_return, 0), lv_color_white(), 0);

    lv_obj_t* about_label = lv_label_create(version_app->version_page);
    lv_obj_set_style_text_font(about_label, &version_font_cn_16_t, 0);
    lv_obj_set_style_text_color(about_label, lv_color_white(), 0);
    lv_label_set_text(about_label, "关于");
    lv_obj_align(about_label, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_add_event_cb(version_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);

    // 创建标签
    lv_obj_t *labels[5];
    const char *titles[] = {"手表型号", "固件版本", "主控芯片", "操作系统", "LVGL版本"};
    const char *values[] = {"Xxchong-Watch", "V1.0.0", "esp32s3-n16r8", "FreeRTOS", "LVGL 8.3.10"};
    
    for(int i = 0; i < 5; i++) {
        // 创建一个容器作为背景
        lv_obj_t *cont = lv_obj_create(version_app->version_page);
        lv_obj_set_size(cont, 240, 36);  // 设置容器大小
        lv_obj_align(cont, LV_ALIGN_TOP_MID, 0, 60 + i * 40);  // 调整位置
        lv_obj_set_style_bg_color(cont, lv_color_make(40, 40, 40), 0);  // 深灰色背景
        lv_obj_set_style_border_width(cont, 1, 0);  // 设置边框宽度
        lv_obj_set_style_border_color(cont, lv_color_make(60, 60, 60), 0);  // 边框颜色
        lv_obj_set_style_radius(cont, 8, 0);  // 圆角
        lv_obj_set_style_pad_all(cont, 0, 0);  // 移除内边距
        
        // 创建标题标签
        labels[i] = lv_label_create(cont);  // 改为在容器内创建
        lv_obj_set_style_text_font(labels[i], &version_font_cn_16_t, 0);
        lv_obj_set_style_text_color(labels[i], lv_color_white(), 0);
        lv_label_set_text(labels[i], titles[i]);
        lv_obj_align(labels[i], LV_ALIGN_LEFT_MID, 20, 0);  // 相对容器左侧对齐
        
        // 创建值标签
        lv_obj_t *value_label = lv_label_create(cont);  // 改为在容器内创建
        lv_obj_set_style_text_color(value_label, lv_color_white(), 0);
        lv_label_set_text(value_label, values[i]);
        lv_obj_align(value_label, LV_ALIGN_RIGHT_MID, -20, 0);  // 相对容器右侧对齐
    }

    return version_app->version_page;
}