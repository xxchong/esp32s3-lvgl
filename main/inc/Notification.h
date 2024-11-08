#ifndef __NOTIFICATION_H
#define __NOTIFICATION_H
#define FREQ 2000    // 频率
#define CHANNEL 0    // 通道
#define RESOLUTION 8 // 分辨率
typedef struct
{
    lv_obj_t *notification_page;
    lv_obj_t *wifi_btn;
    lv_obj_t *led_btn;
    lv_obj_t *bluetooth_btn;
    lv_obj_t *slider_volume;
    lv_obj_t *slider_brightness;
    lv_obj_t *label;
    lv_group_t *group;
    lv_obj_t *label_time;

} Notification_t;
extern Notification_t *Notification;
lv_obj_t *create_notification(void);
#endif
