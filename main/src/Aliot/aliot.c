#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <inttypes.h>
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "aliot.h"
#include "mqtt_client.h"
#include "esp_log.h"

static const char *TAG = "Aliot";


/***********************************MQTT配置*******************************/
#define MQTT_ADDRESS    "mqtt://k0404bKWwjP.iot-as-mqtt.cn-shanghai.aliyuncs.com"  //MQTT连接地址
#define MQTT_PORT       1883                        //MQTT连接端口号
#define MQTT_CLIENT     "xxchong123|securemode=3,signmethod=hmacsha1,timestamp=12345|"              //Client ID（设备唯一，大家最好自行改一下）
#define MQTT_USERNAME   "ESP8266&k0404bKWwjP"    //MQTT用户名
#define MQTT_PASSWORD   "B08E9328ACF21AB1DE562A793B2B2690DE177A5E"                  //MQTT密码
#define MQTT_PUBLIC_TOPIC      "/k0404bKWwjP/ESP8266/user/update"       //推送消息主题
#define MQTT_SUBSCRIBE_TOPIC    "/k0404bKWwjP/ESP8266/user/get"      //需要订阅的主题
/*************************************************************************/


//MQTT客户端操作句柄
static esp_mqtt_client_handle_t mqtt_client_handle = NULL;

//MQTT连接标志
static bool is_mqtt_connected = false;

static const char mqtt_publish_data[] = "hello aliyun, here is xxchong";


static void mqtt_event_handler(void* event_handler_arg,esp_event_base_t event_base, int32_t event_id,void* event_data)
{
       esp_mqtt_event_handle_t event = event_data;
       esp_mqtt_client_handle_t client = event->client;
       int msg_id;

      switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:  //连接成功
            ESP_LOGI(TAG, "MQTT连接成功");
            is_mqtt_connected = true;
            //连接成功后，订阅测试主题
            //1. 连接成功后发消息到阿里云物联网平台
            msg_id = esp_mqtt_client_publish(client, MQTT_PUBLIC_TOPIC, mqtt_publish_data, strlen(mqtt_publish_data), 1, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);

            //2. 订阅阿里云物联网平台 user get topic
            msg_id = esp_mqtt_client_subscribe(client, MQTT_SUBSCRIBE_TOPIC, 0);
            ESP_LOGI(TAG, "execute subscribe event, msg_id=%d", msg_id);

            break;
        case MQTT_EVENT_DISCONNECTED:   //连接断开
            ESP_LOGI(TAG, "MQTT连接断开");
            is_mqtt_connected = false;
            break;
        case MQTT_EVENT_SUBSCRIBED:     //收到订阅消息ACK
            ESP_LOGI(TAG, "MQTT订阅消息ACK, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:   //收到解订阅消息ACK
            break;
        case MQTT_EVENT_PUBLISHED:      //收到发布消息ACK
            ESP_LOGI(TAG, "MQTT发布消息ACK, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            //收到消息   %.*s 是一个特殊的格式说明符，用于表示一个可变长度的字符串
            ESP_LOGI(TAG, "MQTT收到消息,TOPIC=%.*s,DATA=%.*s", event->topic_len, event->topic, event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            break;
    }
}

void mqtt_init(void)
{
    esp_mqtt_client_config_t mqtt_cfg ={
        .broker.address.uri = MQTT_ADDRESS,
        .broker.address.port = MQTT_PORT,
        //Client ID
        .credentials.client_id = MQTT_CLIENT,
        //用户名
        .credentials.username = MQTT_USERNAME,
        //密码
        .credentials.authentication.password = MQTT_PASSWORD,
        .session.keepalive = 120,
        .task.stack_size = 4096,
        .task.priority = 5,
    };

    ESP_LOGI(TAG,"mqtt connect->clientId:%s,username:%s,password:%s",mqtt_cfg.credentials.client_id,
    mqtt_cfg.credentials.username,mqtt_cfg.credentials.authentication.password);
    //设置mqtt配置，返回mqtt操作句柄
    mqtt_client_handle = esp_mqtt_client_init(&mqtt_cfg);
    //注册mqtt事件回调函数
    esp_mqtt_client_register_event(mqtt_client_handle, ESP_EVENT_ANY_ID, mqtt_event_handler, mqtt_client_handle);
    //启动mqtt连接
    esp_mqtt_client_start(mqtt_client_handle);  
}

esp_err_t mqtt_publish(const char* topic,const char* data)
{
    return esp_mqtt_client_publish(mqtt_client_handle,topic,data,0,0,false);
}
esp_err_t mqtt_subscribe(const char* topic)
{
    return esp_mqtt_client_subscribe_single(mqtt_client_handle,topic,1);
}