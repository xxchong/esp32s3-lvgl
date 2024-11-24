
#include "sys.h"
#
LV_IMG_DECLARE(xdd);

typedef struct
{
    lv_obj_t *boot_page;
    lv_obj_t *boot_label;
    lv_obj_t *obj1;
    lv_obj_t *img;
    lv_obj_t *btn_start;
} BOOT_T;

static BOOT_T *boot;

static void set_size(void *var, int32_t v)
{
    /* 设置 obj1 对象宽度 */
    lv_obj_set_size((lv_obj_t *)var, v, v);
}

static void btn_start_cb(lv_event_t *e)
{
    lv_page->root_page = create_root();
    lv_scr_load_anim(lv_page->root_page, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
}
lv_obj_t *create_boot(void)
{
    if (boot == NULL)
    {
        boot = (BOOT_T *)malloc(sizeof(BOOT_T));
        if (boot == NULL)
        {
            printf("boot malloc failed\n");
        }
        boot->boot_page = NULL;
        boot->boot_label = NULL;
        boot->obj1 = NULL;
        boot->img = NULL;
        boot->btn_start = NULL;
    }

    boot->boot_page = lv_obj_create(NULL);
    lv_obj_set_size(boot->boot_page, 240, 280);
    lv_obj_set_style_pad_all(boot->boot_page, 0, 0);
    lv_obj_set_style_border_width(boot->boot_page, 0, 0);

    boot->obj1 = lv_obj_create(boot->boot_page);
    lv_obj_set_size(boot->obj1, 0, 0);
    lv_obj_set_style_radius(boot->obj1, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_border_width(boot->obj1, 1, 0);
    lv_obj_set_style_pad_all(boot->obj1, 0, 0);
    lv_obj_set_align(boot->obj1, LV_ALIGN_TOP_MID);

    boot->img = lv_img_create(boot->obj1);
    lv_img_set_src(boot->img, &xdd);
    lv_obj_center(boot->img);

    // 创建大小变化动画
    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, boot->obj1);
    lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)set_size);
    lv_anim_set_values(&a1, 0, 80);
    lv_anim_set_repeat_count(&a1, 1);
    lv_anim_set_time(&a1, 2000);
    lv_anim_set_path_cb(&a1, lv_anim_path_bounce);

    // 创建下落动画
    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, boot->obj1);
    lv_anim_set_exec_cb(&a2, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_values(&a2, 0, 30);
    lv_anim_set_repeat_count(&a2, 1);
    lv_anim_set_time(&a2, 2000);
    lv_anim_set_path_cb(&a2, lv_anim_path_bounce);

    boot->boot_label = lv_label_create(boot->boot_page);
    lv_label_set_text(boot->boot_label, "    Hello\nxxchong");
    lv_obj_set_style_text_color(boot->boot_label, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(boot->boot_label, &lv_font_montserrat_20, LV_STATE_DEFAULT);
    lv_obj_set_align(boot->boot_label, LV_ALIGN_TOP_MID);

    lv_anim_t a3;
    lv_anim_init(&a3);
    lv_anim_set_var(&a3, boot->boot_label);
    lv_anim_set_exec_cb(&a3, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_values(&a3, 0, 120);
    lv_anim_set_repeat_count(&a3, 1);
    lv_anim_set_time(&a3, 2000);
    lv_anim_set_path_cb(&a3, lv_anim_path_bounce);

    boot->boot_label = lv_label_create(boot->boot_page);
    lv_label_set_text(boot->boot_label, "https://github.com/xxchong/esp32s3-lvgl.git");
    lv_obj_set_style_text_color(boot->boot_label, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(boot->boot_label, &lv_font_montserrat_10, LV_STATE_DEFAULT);
    lv_obj_align(boot->boot_label, LV_ALIGN_TOP_MID, 0, 0);

    lv_anim_t a4;
    lv_anim_init(&a4);
    lv_anim_set_var(&a4, boot->boot_label);
    lv_anim_set_exec_cb(&a4, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_values(&a4, 280, 180);
    lv_anim_set_repeat_count(&a4, 1);
    lv_anim_set_time(&a4, 2000);
    lv_anim_set_path_cb(&a4, lv_anim_path_bounce);

    boot->btn_start = lv_btn_create(boot->boot_page);
    lv_obj_set_size(boot->btn_start, 60, 30);
    lv_obj_align(boot->btn_start, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_radius(boot->btn_start, 10, 0);
    lv_obj_set_style_bg_opa(boot->btn_start, 100, LV_STATE_DEFAULT);
    boot->boot_label = lv_label_create(boot->btn_start);
    lv_label_set_text(boot->boot_label, "Start");
    lv_obj_set_style_text_color(boot->boot_label, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(boot->boot_label, &lv_font_montserrat_14, LV_STATE_DEFAULT);
    lv_obj_center(boot->boot_label);

    lv_obj_add_event_cb(boot->btn_start, btn_start_cb, LV_EVENT_CLICKED, NULL);

    lv_anim_t a5;
    lv_anim_init(&a5);
    lv_anim_set_var(&a5, boot->btn_start);
    lv_anim_set_exec_cb(&a5, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_values(&a5, 280, 200);
    lv_anim_set_repeat_count(&a5, 1);
    lv_anim_set_time(&a5, 2000);
    lv_anim_set_path_cb(&a5, lv_anim_path_bounce);

    lv_anim_start(&a1);
    lv_anim_start(&a2);
    lv_anim_start(&a3);
    lv_anim_start(&a4);
    lv_anim_start(&a5);

    return boot->boot_page;
}
