#include "sys.h"
#include "wifi_scan_driver.h"

LV_IMG_DECLARE(refresh);
typedef struct
{
    lv_obj_t *wifi_page;
    lv_obj_t *btn_return;
    lv_obj_t *wifi_switch_cont;
    lv_obj_t *wifi_switch;
    lv_obj_t *label_wifi;
    lv_obj_t *wifi_list;
    lv_timer_t *timer_upload_wifi_list;
    lv_obj_t *search_bar;    // 添加进度条对象
    lv_obj_t *keyboard;
    lv_obj_t *connect_window;
    lv_obj_t *mask;
    lv_obj_t *current_wifi_cont;    // 当前WiFi容器
    lv_obj_t *current_wifi_label;   // 当前WiFi标签
    lv_obj_t *btn_refresh;    // 刷新按钮


} WiFi_app_t;

static WiFi_app_t *wifi_app = NULL;


static bool wifi_switch_state = false;  


static lv_obj_t *last_btn = NULL;

static bool pwd_eye_state = false;

static  lv_obj_t *pwd_eye;
static lv_obj_t *password_input;

static void btn_cancel_cb(lv_event_t *e) {
    // 关闭密码输入窗口
    if(wifi_app->mask)
    {
        
        if(wifi_app->keyboard) {
            lv_obj_add_flag(wifi_app->keyboard, LV_OBJ_FLAG_HIDDEN);
            wifi_app->keyboard = NULL;
        }
        lv_obj_del(wifi_app->mask); // 删除遮罩层会同时删除其子对象(包括connect_window)   
    }
    lv_obj_scroll_to_view(last_btn, LV_ANIM_ON);
}


static void btn_pwd_eye_cb(lv_event_t *e)
{
    lv_obj_t *pwd_label = lv_event_get_user_data(e);
    pwd_eye_state = !pwd_eye_state;
    if(pwd_eye_state)
    {
        lv_textarea_set_password_mode(password_input, false);
        lv_label_set_text(pwd_label, LV_SYMBOL_EYE_OPEN);
    }else
    {
        lv_textarea_set_password_mode(password_input, true);
        lv_label_set_text(pwd_label, LV_SYMBOL_EYE_CLOSE);
    }


}
// 添加键盘回调函数
static void keyboard_cb(lv_event_t *e)
{
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = (lv_obj_t *)lv_event_get_user_data(e);
    if(kb == NULL) return;
    
    lv_keyboard_set_textarea(kb, ta);
    lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(kb);
}

// 添加键盘关闭回调函数
static void keyboard_close_cb(lv_event_t *e)
{
    lv_obj_t *kb = (lv_obj_t *)lv_event_get_user_data(e);
    if(kb == NULL) return;
    
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    lv_keyboard_set_textarea(kb, NULL);
}

static void btn_connect_cb(lv_event_t *e)
{
    printf("password is %s\n", lv_textarea_get_text(password_input));
}

static void create_password_input_window(const char *wifi_name) {

    // 创建一个半透明的遮罩层
    wifi_app->mask = lv_obj_create(wifi_app->wifi_page);
    lv_obj_remove_style_all(wifi_app->mask);
    lv_obj_set_size(wifi_app->mask, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(wifi_app->mask, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(wifi_app->mask, LV_OPA_50, 0);
    lv_obj_clear_flag(wifi_app->mask, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(wifi_app->mask, LV_OBJ_FLAG_CLICKABLE); // 使遮罩层可接收点击事件



    // 创建密码输入窗口
    wifi_app->connect_window = lv_obj_create(wifi_app->mask);
    lv_obj_set_size(wifi_app->connect_window, 210, 240);
    lv_obj_align(wifi_app->connect_window, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(wifi_app->connect_window, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(wifi_app->connect_window, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_all(wifi_app->connect_window,0,0);


    lv_obj_t *title = lv_label_create(wifi_app->connect_window);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_12, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 6);
    lv_label_set_text_fmt(title, "Connect to \"%s\"", wifi_name);


    // 创建文本输入框
    password_input = lv_textarea_create(wifi_app->connect_window);
    lv_textarea_set_one_line(password_input, true);
    lv_obj_set_size(password_input, 180, 35);
    lv_obj_set_style_text_font(password_input, &lv_font_montserrat_12, 0);
    lv_obj_align_to(password_input, title, LV_ALIGN_OUT_BOTTOM_MID, 0, 12);
    lv_obj_remove_style(password_input, NULL, LV_PART_SCROLLBAR);
    lv_obj_set_style_border_width(password_input, 1, 0);
    lv_obj_set_style_radius(password_input, 5, 0);
    lv_textarea_set_placeholder_text(password_input, "Input Password");
    lv_obj_clear_flag(password_input, LV_OBJ_FLAG_SCROLLABLE);
    lv_textarea_set_password_mode(password_input, true);



    pwd_eye = lv_btn_create(wifi_app->connect_window);
    lv_obj_set_size(pwd_eye, 25, 25);
    lv_obj_align_to(pwd_eye, password_input, LV_ALIGN_OUT_RIGHT_MID, -24, 0);
    lv_obj_set_style_bg_color(pwd_eye, lv_color_white(), 0);
    lv_obj_set_style_radius(pwd_eye, 5, 0);
    lv_obj_set_style_shadow_width(pwd_eye, 0, 0);
    lv_obj_set_style_pad_all(pwd_eye, 0, 0);
    lv_obj_set_style_border_width(pwd_eye, 0, 0);



    lv_obj_t *pwd_label = lv_label_create(pwd_eye);
    lv_obj_set_style_text_font(pwd_label, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(pwd_label, lv_color_black(), 0);
    lv_label_set_text(pwd_label, LV_SYMBOL_EYE_CLOSE);
    lv_obj_center(pwd_label);

    lv_obj_add_event_cb(pwd_eye, btn_pwd_eye_cb, LV_EVENT_CLICKED, pwd_label);



    // 创建键盘
    wifi_app->keyboard = lv_keyboard_create(wifi_app->mask);
    lv_obj_add_flag(wifi_app->keyboard, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_size(wifi_app->keyboard, LV_PCT(100), LV_PCT(60));
    lv_obj_align(wifi_app->keyboard, LV_ALIGN_BOTTOM_MID, 0, 0);
    // lv_obj_set_style_bg_color(wifi_app->keyboard, lv_color_hex(0x252526), 0);
    // lv_obj_set_style_text_color(wifi_app->keyboard, lv_color_white(), 0);


    // 添加键盘的事件回调（当点击键盘的OK按钮时）
    lv_keyboard_set_textarea(wifi_app->keyboard, password_input);//设置关联的文本区域
    lv_obj_add_event_cb(wifi_app->keyboard, keyboard_close_cb, LV_EVENT_READY, wifi_app->keyboard);
    lv_obj_add_event_cb(wifi_app->keyboard, keyboard_close_cb, LV_EVENT_CANCEL, wifi_app->keyboard);
    // 添加文本区域的事件回调
    lv_obj_add_event_cb(password_input, keyboard_cb, LV_EVENT_FOCUSED, wifi_app->keyboard);
    lv_obj_add_event_cb(password_input, keyboard_close_cb, LV_EVENT_DEFOCUSED, wifi_app->keyboard);
    



    // 创建取消按钮
    lv_obj_t *btn_cancel = lv_btn_create(wifi_app->connect_window);
    lv_obj_set_size(btn_cancel, 60, 35);
    lv_obj_set_style_bg_color(btn_cancel, lv_color_hex(0x218ee9), 0);
    lv_obj_align(btn_cancel, LV_ALIGN_BOTTOM_LEFT, 15, -15);
    lv_obj_add_event_cb(btn_cancel, btn_cancel_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *label_cancel = lv_label_create(btn_cancel);
    lv_obj_set_style_text_font(label_cancel, &lv_font_montserrat_12, 0);
    lv_obj_center(label_cancel);
    lv_label_set_text(label_cancel, "Cancel");
    lv_obj_add_event_cb(btn_cancel, btn_cancel_cb, LV_EVENT_CLICKED, NULL);


    // 创建连接按钮
    lv_obj_t *btn_connect = lv_btn_create(wifi_app->connect_window);
    lv_obj_set_size(btn_connect, 60, 35);
    lv_obj_align(btn_connect, LV_ALIGN_BOTTOM_RIGHT, -15, -15);
    lv_obj_set_style_bg_color(btn_connect, lv_color_hex(0x218ee9), 0);
    lv_obj_add_event_cb(btn_connect, btn_connect_cb, LV_EVENT_CLICKED, password_input);

    lv_obj_t *label_connect = lv_label_create(btn_connect);
    lv_label_set_text(label_connect, "Connect");
    lv_obj_set_style_text_font(label_connect, &lv_font_montserrat_12, 0);
    lv_obj_center(label_connect);
}



static void connect_wifi_handler(lv_event_t *e)
{
    const char *wifi_name = (const char *)lv_event_get_user_data(e);
    lv_obj_t *btn = lv_event_get_target(e);
    last_btn = btn;
    printf("connect wifi name is %s\n", wifi_name);
    create_password_input_window(wifi_name);
}


// 添加进度条动画处理函数
static void search_anim_cb(void * var, int32_t v)
{
    lv_obj_t * bar = (lv_obj_t *)var;
    lv_bar_set_value(bar, v, LV_ANIM_ON);
}

static void btn_return_cb(lv_event_t *e)
{

    lv_page->setting_page = create_setting_app();
    lv_scr_load_anim(lv_page->setting_page, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, true);
    
}

static void timer_upload_wifi_list_handler(lv_timer_t *timer)
{

    // 等待扫描完成,最多等待3秒
    if (wait_wifi_scan_done(pdMS_TO_TICKS(3000))) {
        lv_obj_clean(wifi_app->wifi_list);
        
        char ssid[33];
        int8_t rssi;
        int count = 0;
        
        // 从队列中获取扫描结果并显示
        while (count < 30 && get_wifi_scan_result(ssid, &rssi)) {
            lv_obj_t *item = lv_list_add_btn(wifi_app->wifi_list, LV_SYMBOL_WIFI, NULL);
            
            lv_obj_t *label = lv_label_create(item);
            lv_label_set_text(label, ssid);
            lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
            lv_obj_set_style_text_color(label, lv_color_white(), 0);
            lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
            
            lv_obj_set_style_bg_color(item, lv_color_hex(0x252526), 0);
            lv_obj_set_style_text_color(lv_obj_get_child(item, 0), lv_color_white(), 0);
            lv_obj_set_style_border_width(item, 0, 0);
            lv_obj_add_event_cb(item, connect_wifi_handler, LV_EVENT_CLICKED, (void*)strdup(ssid));
            
            count++;
        }
        
        if (count > 0) {
            lv_obj_scroll_to_view(lv_obj_get_child(wifi_app->wifi_list, 0), LV_ANIM_ON);
        }
    }
    
    // 删除进度条
    if (wifi_app->search_bar) {
        lv_obj_del(wifi_app->search_bar);
        wifi_app->search_bar = NULL;
    }
    
    // 删除定时器
    if (wifi_app->timer_upload_wifi_list) {
        lv_timer_del(timer);
        wifi_app->timer_upload_wifi_list = NULL;
    }
    
    // 清理扫描资源
    cleanup_wifi_scan();
}


static void wifi_switch_cb(lv_event_t *e)
{
    bool switch_state = lv_obj_has_state(wifi_app->wifi_switch, LV_STATE_CHECKED);
    if(switch_state)
    {
        lv_obj_clear_flag(wifi_app->btn_refresh, LV_OBJ_FLAG_HIDDEN);

        // const char* current_wifi = get_current_wifi();
        // if(current_wifi != NULL) {
        lv_label_set_text_fmt(wifi_app->current_wifi_label, LV_SYMBOL_WIFI " Pixel5");
        lv_obj_clear_flag(wifi_app->current_wifi_cont, LV_OBJ_FLAG_HIDDEN);
        // } else {
        //     lv_obj_add_flag(wifi_app->current_wifi_cont, LV_OBJ_FLAG_HIDDEN);
        // }

        start_wifi_scan();




        // 创建并显示进度条
        wifi_app->search_bar = lv_bar_create(wifi_app->wifi_page);
        lv_obj_set_size(wifi_app->search_bar, 200, 4);
        lv_obj_align_to(wifi_app->search_bar, wifi_app->current_wifi_cont, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
        lv_obj_set_style_bg_color(wifi_app->search_bar, lv_color_white(), LV_PART_MAIN); // 浅绿色背景
        lv_obj_set_style_bg_color(wifi_app->search_bar, lv_color_hex(0x218ee9), LV_PART_INDICATOR); // 深绿色指示器
        
       // 创建循环加载动画
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, wifi_app->search_bar);
        lv_anim_set_exec_cb(&a, search_anim_cb);
        lv_anim_set_values(&a, 0, 100);
        lv_anim_set_time(&a, 500);           // 1秒完成一次
        lv_anim_set_playback_time(&a, 0);     // 不需要回放
        lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);  // 无限循环
        lv_anim_start(&a);

        // 创建定时器更新WiFi列表
        wifi_app->timer_upload_wifi_list = lv_timer_create(timer_upload_wifi_list_handler, 2000, NULL);
        lv_timer_set_repeat_count(wifi_app->timer_upload_wifi_list, 1);
        
       
    }else
    {
        lv_obj_add_flag(wifi_app->btn_refresh, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(wifi_app->current_wifi_cont, LV_OBJ_FLAG_HIDDEN);
        if(wifi_app->timer_upload_wifi_list != NULL)
        {
            lv_timer_del(wifi_app->timer_upload_wifi_list);
            wifi_app->timer_upload_wifi_list = NULL;  // 重要：设置为 NULL 避免悬空指针
        }

         if(wifi_app->search_bar) {
            lv_obj_del(wifi_app->search_bar);
            wifi_app->search_bar = NULL;
        }
        lv_obj_clean(wifi_app->wifi_list);
    }

}
// 添加刷新按钮的回调函数
static void btn_refresh_cb(lv_event_t *e)
{
    // 如果WiFi开关是打开的状态才执行刷新
    if(lv_obj_has_state(wifi_app->wifi_switch, LV_STATE_CHECKED))
    {
        // 清空现有列表
        lv_obj_clean(wifi_app->wifi_list);
        
        // 创建并显示进度条
        wifi_app->search_bar = lv_bar_create(wifi_app->wifi_page);
        lv_obj_set_size(wifi_app->search_bar, 200, 4);
        lv_obj_align_to(wifi_app->search_bar, wifi_app->current_wifi_cont, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
        lv_obj_set_style_bg_color(wifi_app->search_bar, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_bg_color(wifi_app->search_bar, lv_color_hex(0x218ee9), LV_PART_INDICATOR);
        
        // 创建循环加载动画
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, wifi_app->search_bar);
        lv_anim_set_exec_cb(&a, search_anim_cb);
        lv_anim_set_values(&a, 0, 100);
        lv_anim_set_time(&a, 500);
        lv_anim_set_playback_time(&a, 0);
        lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
        lv_anim_start(&a);

        // 创建定时器更新WiFi列表
        wifi_app->timer_upload_wifi_list = lv_timer_create(timer_upload_wifi_list_handler, 2000, NULL);
        lv_timer_set_repeat_count(wifi_app->timer_upload_wifi_list, 1);
    }
}


lv_obj_t *create_wifi_app(void)
{
    if (wifi_app != NULL)
    {
        free(wifi_app);
        wifi_app = NULL;
    }
    if (wifi_app == NULL)
    {
        wifi_app = (WiFi_app_t *)calloc(1, sizeof(WiFi_app_t));

    }


    wifi_app->wifi_page = create_page("WiFi");
    lv_obj_remove_style(wifi_app->wifi_page,NULL,LV_PART_SCROLLBAR);
    lv_obj_clear_flag(wifi_app->wifi_page, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(wifi_app->wifi_page, lv_color_black(), 0);

    // 创建返回按钮
    wifi_app->btn_return = create_app_btn_return(wifi_app->wifi_page);
    lv_obj_set_style_text_color(lv_obj_get_child(wifi_app->btn_return, 0), lv_color_hex(0x218ee9), 0);
    lv_obj_align_to(wifi_app->btn_return, wifi_app->wifi_page, LV_ALIGN_TOP_LEFT, 2,5);
    lv_obj_add_event_cb(wifi_app->btn_return, btn_return_cb, LV_EVENT_CLICKED, NULL);


    wifi_app->wifi_switch_cont = lv_obj_create(wifi_app->wifi_page);
    lv_obj_set_size(wifi_app->wifi_switch_cont, 220, 55);
    lv_obj_align(wifi_app->wifi_switch_cont, LV_ALIGN_TOP_MID, 0, 30);
    lv_obj_set_style_bg_color(wifi_app->wifi_switch_cont, lv_color_hex(0x252526), 0);
    lv_obj_clear_flag(wifi_app->wifi_switch_cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(wifi_app->wifi_switch_cont, lv_color_hex(0x252526), 0);
    lv_obj_set_style_radius(wifi_app->wifi_switch_cont, 10, 0);


    wifi_app->label_wifi = lv_label_create(wifi_app->wifi_switch_cont);
    lv_label_set_text(wifi_app->label_wifi, LV_SYMBOL_WIFI " Wi-Fi");
    lv_obj_set_style_text_color(wifi_app->label_wifi, lv_color_white(), 0);
    lv_obj_set_style_text_font(wifi_app->label_wifi, &lv_font_montserrat_14, 0);
    lv_obj_align(wifi_app->label_wifi, LV_ALIGN_LEFT_MID, 6, 0);   


    wifi_app->wifi_switch = lv_switch_create(wifi_app->wifi_switch_cont);
    lv_obj_align(wifi_app->wifi_switch, LV_ALIGN_RIGHT_MID, -6, 0);
    lv_obj_set_style_bg_color(wifi_app->wifi_switch, lv_color_hex(0x08df73), LV_STATE_CHECKED | LV_PART_INDICATOR);
    lv_obj_add_event_cb(wifi_app->wifi_switch, wifi_switch_cb, LV_EVENT_VALUE_CHANGED, NULL);


     // 创建刷新按钮
    wifi_app->btn_refresh = lv_btn_create(wifi_app->wifi_switch_cont);
    lv_obj_set_size(wifi_app->btn_refresh, 30, 30);
    lv_obj_align_to(wifi_app->btn_refresh, wifi_app->wifi_switch, LV_ALIGN_OUT_LEFT_MID, -10, 0);  // 位置可以根据需要调整
    lv_obj_set_style_bg_color(wifi_app->btn_refresh, lv_color_hex(0x252526), 0);
    lv_obj_set_style_border_width(wifi_app->btn_refresh, 0, 0);
    lv_obj_set_style_radius(wifi_app->btn_refresh, 6, 0);
    lv_obj_set_style_shadow_width(wifi_app->btn_refresh, 0, 0);
    lv_obj_add_flag(wifi_app->btn_refresh, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(wifi_app->btn_refresh, btn_refresh_cb, LV_EVENT_CLICKED, NULL);

    // 创建刷新图标
    lv_obj_t *refresh_label = lv_label_create(wifi_app->btn_refresh);
    lv_label_set_text(refresh_label, LV_SYMBOL_REFRESH);
    lv_obj_set_style_text_color(refresh_label, lv_color_white(), 0);
    lv_obj_center(refresh_label);



    // 创建当前WiFi连接容器
    wifi_app->current_wifi_cont = lv_obj_create(wifi_app->wifi_page);
    lv_obj_set_size(wifi_app->current_wifi_cont, 220, 35);
    lv_obj_align_to(wifi_app->current_wifi_cont, wifi_app->wifi_switch_cont, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_set_style_bg_color(wifi_app->current_wifi_cont, lv_color_hex(0x1d7ece), 0);
    lv_obj_clear_flag(wifi_app->current_wifi_cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(wifi_app->current_wifi_cont, lv_color_hex(0x1d7ece), 0);
    lv_obj_set_style_radius(wifi_app->current_wifi_cont, 10, 0);
    lv_obj_add_flag(wifi_app->current_wifi_cont, LV_OBJ_FLAG_HIDDEN); // 默认隐藏

    wifi_app->current_wifi_label = lv_label_create(wifi_app->current_wifi_cont);
    lv_obj_set_style_text_color(wifi_app->current_wifi_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(wifi_app->current_wifi_label, &lv_font_montserrat_14, 0);
    lv_obj_align(wifi_app->current_wifi_label, LV_ALIGN_LEFT_MID, 6, 0);

    // 调整 wifi_list 的位置
    wifi_app->wifi_list = lv_list_create(wifi_app->wifi_page);
    lv_obj_set_size(wifi_app->wifi_list, 235, 200);
    lv_obj_align_to(wifi_app->wifi_list, wifi_app->current_wifi_cont, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_set_style_bg_color(wifi_app->wifi_list, lv_color_black(), 0);
    lv_obj_set_style_border_width(wifi_app->wifi_list, 0, 0);
    lv_obj_set_scrollbar_mode(wifi_app->wifi_list, LV_SCROLLBAR_MODE_AUTO);
    lv_obj_set_style_pad_all(wifi_app->wifi_list, 0, 0);
    lv_obj_set_style_outline_width(wifi_app->wifi_list, 0, 0);

    return wifi_app->wifi_page;


}
