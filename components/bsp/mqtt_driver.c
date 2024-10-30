#include "esp_err.h"
#include "esp_log.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "wifi_sta.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include "mqtt_driver.h"

static const char* TAG = "mqtt";

/***********************************MQTT配置*******************************/
#define MQTT_ADDRESS    "mqtt://broker-cn.emqx.io"  //MQTT连接地址
#define MQTT_PORT       1883                        //MQTT连接端口号
#define MQTT_CLIENT     "mqttx_d11213"              //Client ID（设备唯一，大家最好自行改一下）
#define MQTT_USERNAME   "hello1"                    //MQTT用户名
#define MQTT_PASSWORD   "12345678"                  //MQTT密码
#define MQTT_PUBLIC_TOPIC      "/test/topic1"       //推送消息主题
#define MQTT_SUBSCRIBE_TOPIC    "/test/topic2"      //需要订阅的主题
/*************************************************************************/


//MQTT客户端操作句柄
static esp_mqtt_client_handle_t mqtt_client_handle = NULL;

//MQTT连接标志
static bool is_mqtt_connected = false;



static void mqtt_event_handler(void* event_handler_arg,esp_event_base_t event_base, int32_t event_id,void* event_data)
{
       esp_mqtt_event_handle_t event = event_data;
       esp_mqtt_client_handle_t client = event->client;


      switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:  //连接成功
            ESP_LOGI(TAG, "MQTT连接成功");
            is_mqtt_connected = true;
            //连接成功后，订阅测试主题
            esp_mqtt_client_subscribe_single(mqtt_client_handle,MQTT_SUBSCRIBE_TOPIC,1);
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
    esp_mqtt_client_config_t mqtt_cfg = {0};
    mqtt_cfg.broker.address.uri = MQTT_ADDRESS;
    mqtt_cfg.broker.address.port = MQTT_PORT;
    //Client ID
    mqtt_cfg.credentials.client_id = MQTT_CLIENT;
    //用户名
    mqtt_cfg.credentials.username = MQTT_USERNAME;
    //密码
    mqtt_cfg.credentials.authentication.password = MQTT_PASSWORD;
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
    return esp_mqtt_client_subscribe(mqtt_client_handle,topic,1);
}