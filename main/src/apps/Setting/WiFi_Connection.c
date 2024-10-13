// #include "sys.h"
// #define MAX_NETWORKS 30
// #define MAX_SSID_LENGTH 64
// extern lv_indev_t *indev;
// // extern SemaphoreHandle_t xBinarySemaphore_scan_wifi;
// LV_IMG_DECLARE(refresh);

// typedef struct
// {
//     lv_group_t *group;
//     lv_obj_t *btn_return;
//     lv_obj_t *label_btn;
//     lv_obj_t *scna_wifi_list;
//     lv_obj_t *scan_btn;
//     lv_obj_t *cont;
//     lv_obj_t *wifi_switch;
//     lv_obj_t *label;
//     lv_timer_t *timer;
//     lv_obj_t *label_scan;
//     lv_obj_t *btn_scan;

// } WiFi_app_t;

// static WiFi_app_t *wifi_app;
// lv_obj_t *wifi_btns_to_connect[MAX_NETWORKS]; // 定义列表按钮数组

// // 按钮的回调事件
// static void btn_return_cb(lv_event_t *e)
// {
//     size_t size = lv_fragment_manager_get_stack_size(manager);
//     printf("当前栈内有%d个内容\n", size); // 添加调试信息
//     if (size > 1)                                // 大于二级界面
//     {
//         lv_indev_set_group(indev, last_group);                                           // 将indev返回给上一级页面
//         lv_fragment_manager_pop(manager);                                                // 返回tools
//         my_fragment_t *fragment = (my_fragment_t *)lv_fragment_manager_get_top(manager); /*弹出来后返回一级界面后重新创建的界面获取之前保存的索引位置(不会清除)*/

//         if (fragment == NULL)
//         {
//             printf("fragment is NULL\n");
//             return; // 处理空指针情况
//         }
//         uint8_t last_index = fragment->last_focused_index; // 获取最后一次聚焦的索引位置
//         const char *name = fragment->name;
//         set_focus(setting_list_btns, 3, last_index);
//     }
//     else if (size == 1) // 二级界面
//     {
//         lv_fragment_manager_pop(manager); // 弹出当前片段
//         Return_root_page();
//     }
// }
// // 动画回调函数，更新图标的旋转角度
// static void icon_rotate_anim_cb(void *var, int32_t v)
// {
//     lv_img_set_angle((lv_obj_t *)var, v); // 0 表示不改变其他变换属性
// }

// // 创建并启动动画
// void start_icon_rotate_anim(lv_obj_t *icon)
// {
//     static lv_anim_t a;
//     lv_anim_init(&a);
//     lv_anim_set_var(&a, icon);
//     lv_anim_set_exec_cb(&a, icon_rotate_anim_cb);
//     lv_anim_set_values(&a, 0, 3600); // 从 0 度旋转到 360 度
//     lv_anim_set_time(&a, 2000);     // 动画持续时间，单位为毫秒
//     lv_anim_set_repeat_count(&a, 2); // 重复动画两次
//     lv_anim_start(&a);
// }

// static void add_wifi_list_cb(lv_timer_t *t)
// {
//     printf("add_wifi_list_cb\n");

//     // lv_group_t *group = lv_timer_get_user_data(t);
//     lv_list_add_text(wifi_app->scna_wifi_list, "Nearby Wlans");
//     for (int i = 0; i < network_count && i < MAX_NETWORKS; i++)
//     {
//             printf("ssid:%s\n",ssids[i]);
//         // if (ssids[i] != nullptr)
//         // {
//             wifi_btns_to_connect[i] = lv_list_add_btn(wifi_app->scna_wifi_list, LV_SYMBOL_WIFI, ssids[i]);
//             if (wifi_btns_to_connect[i])
//             {
//                 lv_obj_set_style_radius(wifi_btns_to_connect[i], 5, 0);
//                 lv_obj_set_style_border_width(wifi_btns_to_connect[i], 1, 0);
//                 lv_obj_set_style_pad_all(wifi_btns_to_connect[i], 8, 0);
//                 // lv_obj_set_style_margin_all(wifi_btns_to_connect[i], 1, 0); // 调节外边距
//                  lv_group_add_obj(wifi_app->group, wifi_btns_to_connect[i]);
//                 // userdata[i].ssid = networks[i].ssid;
//                 // userdata[i].group = group;
//                 // lv_obj_add_event_cb(wifi_btns_to_connect[i], wifi_btns_to_connect_cb, LV_EVENT_CLICKED, &userdata[i]);
//              }
//         // }
//     }
// }

// // 在按钮的事件回调中启动动画
// void btn_event_cb(lv_event_t *e)
// {

//     lv_event_code_t code = lv_event_get_code(e);
//     // lv_group_t *group = lv_obj_get_group(lv_event_get_target(e));
  
//     if (code == LV_EVENT_CLICKED)
//     {
//         // start_icon_rotate_anim(wifi_app->scan_label); // 扫描动画
//         // if (xSemaphoreGive(xBinarySemaphore_scan_wifi) == pdTRUE)
//         // {
//         //     printf("scan wifi\n");
//         // }

//         // 清空现有列表
//         lv_obj_clean(wifi_app->scna_wifi_list);
//         wifi_app->timer = lv_timer_create(add_wifi_list_cb, 5000, NULL);
//         lv_timer_reset(wifi_app->timer);
//         lv_timer_set_repeat_count(wifi_app->timer, 1);
   
//     }
// }


// void create_wifi_list(lv_obj_t *parent)
// {
//     // 确保 setting_app 已经被分配内存
//     if (wifi_app == NULL)
//     {
//         wifi_app = (WiFi_app_t *)malloc(sizeof(WiFi_app_t));
//         if (wifi_app == NULL)
//         {
//             // 处理内存分配失败的情况
//             printf("Failed to allocate memory for tools_app\n");
//             return;
//         }
//         // 初始化成员变量
//         wifi_app->group = NULL;
//         wifi_app->btn_return = NULL;
//         wifi_app->label_btn = NULL;
//         wifi_app->scna_wifi_list = NULL;
//         wifi_app->scan_btn = NULL;
//         wifi_app->cont = NULL;
//         wifi_app->wifi_switch = NULL;
//         wifi_app->timer = NULL;
//         wifi_app->label = NULL;
//         wifi_app->label_scan = NULL;
//         wifi_app->btn_scan = NULL;
//     }
//     wifi_app->group = lv_group_create();
//     lv_indev_set_group(indev, wifi_app->group);

//     // 创建返回按钮
//     wifi_app->btn_return = lv_btn_create(parent);
//     lv_obj_set_size(wifi_app->btn_return, 15, 15);

//     remove_styles(wifi_app->btn_return, false, true, true, true);
//     lv_obj_set_style_bg_color(wifi_app->btn_return, lv_color_white(), 0);
//     lv_obj_set_style_border_width(wifi_app->btn_return, 1, 0);
//     lv_obj_set_style_border_color(wifi_app->btn_return, lv_color_black(), 0);
//     lv_obj_align_to(wifi_app->btn_return, parent, LV_ALIGN_TOP_LEFT, 2, 5);

//     // 创建按钮上的标签
//     wifi_app->label_btn = lv_label_create(wifi_app->btn_return);
//     lv_obj_set_style_text_font(wifi_app->label_btn, &my_symbol_font_10_t, 0);
//     lv_label_set_text(wifi_app->label_btn, USER_SYMBOL_RETURN2);
//     lv_obj_center(wifi_app->label_btn);
//     lv_obj_set_style_text_color(wifi_app->label_btn, lv_color_black(), 0);

//     // 配置按钮事件（如果需要）
//     lv_obj_add_event_cb(wifi_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);
//     lv_group_add_obj(wifi_app->group, wifi_app->btn_return);

//     wifi_app->cont = lv_obj_create(parent);
//     lv_obj_set_style_radius(wifi_app->cont, 5, 0);
//     lv_obj_set_style_pad_all(wifi_app->cont, 0, 0);
//     lv_obj_set_size(wifi_app->cont, 240, 234);
//     lv_obj_align(wifi_app->cont, LV_ALIGN_BOTTOM_MID, 0, 0);
//     lv_obj_set_style_border_width(wifi_app->cont, 1, 0);
//     lv_obj_set_scrollbar_mode(wifi_app->cont,LV_SCROLLBAR_MODE_OFF);

//      wifi_app->label = lv_label_create(wifi_app->cont);
//     lv_obj_set_style_text_font(wifi_app->label, &lv_font_montserrat_20, 0);
//     lv_obj_set_style_pad_all(wifi_app->label, 0, 0);
//     lv_label_set_text(wifi_app->label, "WLAN");
//     lv_obj_align(wifi_app->label, LV_ALIGN_TOP_LEFT, 14, 8);



//     wifi_app->wifi_switch = lv_switch_create(wifi_app->cont);
//     lv_obj_set_size(wifi_app->wifi_switch, 50, 30);
//     lv_obj_align(wifi_app->wifi_switch, LV_ALIGN_TOP_RIGHT, -14, 5);


//     wifi_app->btn_scan = lv_btn_create(wifi_app->cont);
//     lv_obj_set_size(wifi_app->btn_scan, 30, 30);
//     lv_obj_align_to(wifi_app->btn_scan, wifi_app->wifi_switch, LV_ALIGN_OUT_LEFT_MID, -6, 0);
//     lv_obj_set_style_bg_color(wifi_app->btn_scan, lv_color_white(), 0);
//     lv_obj_set_style_border_width(wifi_app->btn_scan, 0, 0);
//     lv_obj_set_style_shadow_opa(wifi_app->btn_scan, 0, 0);
//     lv_obj_add_event_cb(wifi_app->btn_scan, btn_event_cb, LV_EVENT_CLICKED, NULL);

//     wifi_app->label_scan = lv_label_create(wifi_app->btn_scan);
//     lv_obj_set_style_text_font(wifi_app->label_scan, &lv_font_montserrat_20, 0);
//     lv_label_set_text(wifi_app->label_scan, LV_SYMBOL_REFRESH);
//     lv_obj_center(wifi_app->label_scan);
//     lv_obj_set_style_text_color(wifi_app->label_scan, lv_color_black(), 0);




//     wifi_app->scna_wifi_list = lv_list_create(wifi_app->cont);
//     lv_obj_set_size(wifi_app->scna_wifi_list, 236, 200);
//     lv_obj_align(wifi_app->scna_wifi_list,LV_ALIGN_TOP_MID,0,39);
//     lv_obj_set_style_pad_all(wifi_app->scna_wifi_list, 0, 0);
//     lv_obj_set_style_text_font(wifi_app->scna_wifi_list,&lv_font_montserrat_16,0);
//     // lv_list_add_text(wifi_app->scna_wifi_list," Nearby wlans");
//     lv_obj_set_style_radius( wifi_app->scna_wifi_list,5,0);

//     lv_group_add_obj(wifi_app->group,wifi_app->wifi_switch);
//     lv_group_add_obj(wifi_app->group,wifi_app->btn_scan);


















   
  
// }
