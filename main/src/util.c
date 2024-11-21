#include "sys.h"
#include "esp_sntp.h"
#include "esp_netif_sntp.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"

static const char *TAG = "util";
#define SNTP_SERVER "pool.ntp.org" // 阿里云NTP服务器
struct tm *timeinfo;

void remove_styles(lv_obj_t *parent, bool remove_border, bool remove_opa, bool remove_scrollbar, bool remove_shadow)
{
    if (parent == NULL)
        return;
    // 移除边框
    if (remove_border)
    {
        lv_obj_set_style_border_width(parent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    // 设置透明
    if (remove_opa)
    {
        lv_obj_set_style_bg_opa(parent, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    // 移除滚动条
    if (remove_scrollbar)
    {
        lv_obj_set_scrollbar_mode(parent, LV_SCROLLBAR_MODE_OFF);
    }

    // 移除阴影
    if (remove_shadow)
    {
        lv_obj_set_style_shadow_width(parent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}

// 列表返回菜单设置焦点
void set_focus(lv_obj_t **btns, int count, int last_index)
{
    if (last_index >= 0 && last_index < count)
    {
        if (btns[last_index] != NULL)
        { // 检查指针是否有效
            lv_group_focus_obj(btns[last_index]);
        }
        else
        {
            // printf("btns[%d] is NULL\n", last_index);
        }
    }
    else
    {
        lv_group_focus_obj(btns[0]); // 默认到第一个
    }
}

void initialize_sntp(void)
{
    ESP_LOGI(TAG, "初始化 SNTP");
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG(SNTP_SERVER);
    esp_netif_sntp_init(&config);

    // 等待获取时间
    time_t now = 0;
    struct tm timeinfo = {0};
    int retry = 0;
    const int retry_count = 15;

    while (timeinfo.tm_year < (2023 - 1900) && ++retry < retry_count)
    {
        ESP_LOGI(TAG, "等待系统时间同步... (%d/%d)", retry, retry_count);
        vTaskDelay(pdMS_TO_TICKS(1000));
        time(&now);
        localtime_r(&now, &timeinfo);
    }

    // 设置时区为中国时区
    setenv("TZ", "CST-8", 1);
    tzset();

    ESP_LOGI(TAG, "SNTP 初始化完成");
}

// 获取格式化的时间字符串
void get_time_string(char *buffer, size_t buffer_size)
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", &timeinfo);
}

struct tm get_timeinfo(void)
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    return timeinfo;
}

// 获取当前时间
void get_now_time(void)
{
    time_t now;
    time(&now);
    timeinfo = localtime(&now);
}

/*创建app的返回按钮*/
lv_obj_t *create_app_btn_return(lv_obj_t *parent)
{
    lv_obj_t *app_btn_return = lv_btn_create(parent);
    lv_obj_set_size(app_btn_return, 25, 25);

    remove_styles(app_btn_return, false, true, true, true);
    lv_obj_set_style_bg_color(app_btn_return, lv_color_white(), 0);
    lv_obj_set_style_border_width(app_btn_return, 0, 0);

    lv_obj_align_to(app_btn_return, parent, LV_ALIGN_TOP_LEFT, 2, 20);

    // 创建按钮上的标签
    lv_obj_t *label_btn = lv_label_create(app_btn_return);
    lv_obj_set_style_text_font(label_btn, &lv_font_montserrat_16, 0);
    lv_label_set_text(label_btn, LV_SYMBOL_LEFT);
    lv_obj_center(label_btn);
    lv_obj_set_style_text_color(label_btn, lv_color_black(), 0);

    return app_btn_return;
}

void gestureCallback(lv_event_t *event)
{
    lv_obj_t *screen = lv_event_get_current_target(event);
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    const char *name = lv_event_get_user_data(event);
    switch (dir)
    {
    case LV_DIR_LEFT:
        // printf(" %s LV_DIR_LEFT",name);
        break;
    case LV_DIR_RIGHT:

        if (lv_scr_act() != lv_page->root_page)
        {
            if (strcmp(name, "Game") == 0)
            {
                back_to_home(lv_page->game_page);
            }
            else if (strcmp(name, "Setting") == 0)
            {
                back_to_home(lv_page->setting_page);
            }
            else if (strcmp(name, "Serial") == 0)
            {
                back_to_home(lv_page->serial_page);
            }
            else if (strcmp(name, "Music") == 0)
            {
                back_to_home(lv_page->music_page);
            }
            else if (strcmp(name, "Tools") == 0)
            {
                back_to_home(lv_page->tools_page);
            }
            else if (strcmp(name, "Calendar") == 0)
            {
                back_to_home(lv_page->calender_page);
            }
            else if (strcmp(name, "MQTT") == 0)
            {
                back_to_home(lv_page->mqtt_page);
            }
            else if (strcmp(name, "BlueTooth") == 0)
            {
                back_to_home(lv_page->bluetooth_page);
            }
            else if (strcmp(name, "Weather") == 0)
            {
                back_to_home(lv_page->weather_page);
            }
            else if (strcmp(name, "Calculators") == 0)
            {
                lv_page->tools_page = tools_list_create();
                lv_scr_load_anim(lv_page->tools_page, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, true);
                cleanup_page(lv_page->calculator_page);
            }
            else if (strcmp(name, "Calculators2") == 0)
            {
            }
            else if (strcmp(name, "Calculators3") == 0)
            {
            }
            else if (strcmp(name, "WiFi") == 0)
            {
                lv_page->setting_page = create_setting_app();
                lv_scr_load_anim(lv_page->setting_page, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, true);
                cleanup_page(lv_page->wifi_page);
            } else if (strcmp(name, "Version") == 0)
            {
                lv_page->setting_page = create_setting_app();
                lv_scr_load_anim(lv_page->setting_page, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, true);
                cleanup_page(lv_page->version_page);
            }
        }
        else
        {
        }

        // printf(" %s LV_DIR_RIGHT",name);
        break;
    case LV_DIR_TOP:
        if (lv_scr_act() == lv_page->notification_page)
        {
            lv_page->root_page = create_root();

            lv_scr_load_anim(lv_page->root_page, LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0, true);

            cleanup_page(lv_page->notification_page);
        }

        break;
    case LV_DIR_BOTTOM:
        if (lv_scr_act() == lv_page->root_page)
        {
            lv_page->notification_page = create_notification();

            lv_scr_load_anim(lv_page->notification_page, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 300, 0, true);

            cleanup_page(lv_page->root_page);
        }
        break;
    }
}

void back_to_home(lv_obj_t *page)
{
    if (lv_page->game_page == lv_scr_act())
    {
        Stop_Game();
        printf("返回释放内存\n");
    }
    lv_page->root_page = create_root();
    lv_scr_load_anim(lv_page->root_page, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, true);
    lv_obj_set_tile(root_page->tileview, root_page->page2, 0);
    lv_obj_scroll_to_view(btns[btn_index], LV_ANIM_ON);
    cleanup_page(page);
}
lv_obj_t *create_page(const char *name)
{
    lv_obj_t *page = lv_obj_create(NULL);
    lv_obj_set_size(page, 240, 280);
    lv_obj_set_style_pad_all(page, 0, 0);
    lv_obj_set_style_border_width(page, 0, 0);

    // 注册手势回调
    lv_obj_add_event_cb(page, gestureCallback, LV_EVENT_GESTURE, name);

    return page;
}

void stop_watch_timer(void)
{
   
    if (clock_watch_time_timer != NULL)
    {
        lv_timer_pause(clock_watch_time_timer);
        lv_timer_del(clock_watch_time_timer);
        clock_watch_time_timer = NULL;
    }

    if (clock_watch_time_timer_2)
    {
        lv_timer_pause(clock_watch_time_timer_2);
        lv_timer_del(clock_watch_time_timer_2);
        clock_watch_time_timer_2 = NULL;
    }
    if(clock_watch_time_timer_3 )
    {
        lv_timer_pause(clock_watch_time_timer_3);
        lv_timer_del(clock_watch_time_timer_3);
        clock_watch_time_timer_3 = NULL;
    }

    if(clock_watch_time_timer_4 )
    {
        lv_timer_pause(clock_watch_time_timer_4);
        lv_timer_del(clock_watch_time_timer_4);
        clock_watch_time_timer_4 = NULL;
    }
   
    
}

void cleanup_page(lv_obj_t *page)
{
    if (time_timer)
    {
        lv_timer_del(time_timer);
        time_timer = NULL;
    }
    if (page == lv_page->root_page)
    {
        if (clock_widget_time_timer)
        {
            lv_timer_pause(clock_widget_time_timer);
            lv_timer_del(clock_widget_time_timer);
            clock_widget_time_timer = NULL;
        }
        if (clock_watch_time_timer)
        {
            lv_timer_pause(clock_watch_time_timer);
            lv_timer_del(clock_watch_time_timer);
            clock_watch_time_timer = NULL;
        }
    }

    lv_obj_clean(page);
}
