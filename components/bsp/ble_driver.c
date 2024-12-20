#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gatt_common_api.h"
#include "ble_driver.h"
#include "string.h"
#include "stdint.h"
#include "stdio.h"
#define TAG "BLE_GATT"


#define PROFILE_NUM     1 // 定义应用的数量
#define PROFILE_APP_IDX 0 // 定义应用索引
#define ESP_APP_ID      0x55 // 定义应用程序ID
#define SVC_INST_ID    0 // 定义服务实例ID号
#define CHAR_VAL_LEN_MAX 100 // 定义特征值长度最大值
#define CHAR_DECLARATION_SIZE   (sizeof(uint8_t)) // 定义特征声明大小
#define ADV_CONFIG_FLAG      (1 << 0) // 定义广播配置标志
#define SCAN_RSP_CONFIG_FLAG (1 << 1) // 定义扫描响应配置标志

static uint8_t adv_config_done = 0; // 定义广播配置完成标志
static uint16_t handle_table[HRS_IDX_NB_GATT]; // 定义特征句柄表

/* 定义服务和特征UUID */
static const uint16_t GATT_SERVICE_UUID = 0x00FF; // 定义服务UUID
static const uint16_t GATT_CHAR_A_UUID = 0xFF01; // 定义特征A UUID
static const uint16_t GATT_CHAR_B_UUID = 0xFF02; // 定义特征B UUID

static const uint16_t primary_service_uuid         = ESP_GATT_UUID_PRI_SERVICE; // 定义主服务UUID
static const uint16_t character_declaration_uuid   = ESP_GATT_UUID_CHAR_DECLARE; // 定义特征声明UUID
static const uint16_t character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG; // 定义特征客户端配置UUID
static const uint8_t char_prop_read                = ESP_GATT_CHAR_PROP_BIT_READ; // 定义特征读属性
// static const uint8_t char_prop_write               = ESP_GATT_CHAR_PROP_BIT_WRITE;
static const uint8_t char_prop_read_write_notify   = ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
static const uint8_t heart_measurement_ccc[2]      = {0x00, 0x00}; // 定义特征的客户端配置特征值

/* 定义特征AB的值 */
static const uint8_t char_value[4]  = {0x44, 0x33, 0x22, 0x11};
static const uint8_t char_value2[4] = {0x11, 0x22, 0x33, 0x44};

// 应用回调函数声明
static void gatts_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

/* 蓝牙ble应用实例结构体 */
struct gatts_profile_inst {
    esp_gatts_cb_t gatts_cb; // 定义gatts回调函数
    uint16_t gatts_if; // 定义gatts接口
    uint16_t app_id; // 定义应���ID
    uint16_t conn_id; // 定义连接ID
    uint16_t service_handle; // 定义服务句柄
    esp_gatt_srvc_id_t service_id; // 定义服务ID
};

/* 定义蓝牙ble应用实例 */
static struct gatts_profile_inst gl_profile_tab[PROFILE_NUM] = {
    [PROFILE_APP_IDX] = {
        .gatts_cb = gatts_profile_event_handler,//gatts回调函数
        .gatts_if = ESP_GATT_IF_NONE,//gatts接口
    },
};

/* 广播数据 */
static uint8_t raw_adv_data[] = {
    0x02, 0x01, 0x06,           // 标准flags
    0x03, 0x03, 0xFF, 0x00,     // 服务UUID
    0x0C, 0x09, 'X', 'X', 'C', 'H', 'O', 'N', 'G', '-', 'B', 'L', 'E'
};

/* 扫描响应数据 */
static uint8_t raw_scan_rsp_data[] = {
    0x02, 0x01, 0x06,           // 标准flags
    0x03, 0x03, 0xFF, 0x00      // 服务UUID
};

/* 广播参数 */
static esp_ble_adv_params_t adv_params = {
    .adv_int_min = 0x20, // 定义广播间隔最小值,20ms
    .adv_int_max = 0x40, // 定义广播间隔最大值,40ms
    .adv_type = ADV_TYPE_IND, // 定义广播类型,定向广播
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC, // 定义设备地址类型,公有地址
    .channel_map = ADV_CHNL_ALL, // 定义广播通道,所有通道
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY // 定义广播过滤策略,允许扫描任何连接任何
};

/* 属性表 */
static const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB_GATT] = {
    // 服务声明
    [IDX_SVC_GATT] = {{ESP_GATT_AUTO_RSP}, {
        ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid, 
        ESP_GATT_PERM_READ,
        sizeof(uint16_t), sizeof(GATT_SERVICE_UUID), 
        (uint8_t *)&GATT_SERVICE_UUID
    }},
    // 特征A声明
    [IDX_CHAR_A_GATT] = {{ESP_GATT_AUTO_RSP}, {
        ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
        ESP_GATT_PERM_READ,
        CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, 
        (uint8_t *)&char_prop_read_write_notify
    }},
    // 特征A值
    [IDX_CHAR_VAL_A_GATT] = {{ESP_GATT_AUTO_RSP}, {
        ESP_UUID_LEN_16, (uint8_t *)&GATT_CHAR_A_UUID,
        ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
        CHAR_VAL_LEN_MAX, sizeof(char_value),
        (uint8_t *)char_value
    }},
    // 特征A的CCCD
    [IDX_CHAR_CFG_A_GATT] = {{ESP_GATT_AUTO_RSP}, {
        ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
        ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
        sizeof(uint16_t), sizeof(heart_measurement_ccc),
        (uint8_t *)heart_measurement_ccc
    }},

    // 特征B声明
    [IDX_CHAR_B_GATT] = {{ESP_GATT_AUTO_RSP}, {
        ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
        ESP_GATT_PERM_READ,
        CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
        (uint8_t *)&char_prop_read
    }},
    // 特征B值
    [IDX_CHAR_VAL_B_GATT] = {{ESP_GATT_AUTO_RSP}, {
        ESP_UUID_LEN_16, (uint8_t *)&GATT_CHAR_B_UUID,
        ESP_GATT_PERM_READ,
        CHAR_VAL_LEN_MAX, sizeof(char_value2),
        (uint8_t *)char_value2
    }},
};


/* GAP事件处理函数 ,主要用于广播和扫描响应的配置和启动 */
static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{

    switch (event) {
        case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT: //广播数据配置完成
            ESP_LOGI(TAG, "广播数据配置完成");
            adv_config_done &= (~ADV_CONFIG_FLAG);  //(~ADV_CONFIG_FLAG:1111 1110) 与运算,将ADV_CONFIG_FLAG的最低位置0
            if (adv_config_done == 0) {
                esp_ble_gap_start_advertising(&adv_params);
            }
            break;
            
        case ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
            ESP_LOGI(TAG, "扫描响应数据配置完成");
            adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);//(~SCAN_RSP_CONFIG_FLAG:1111 1101) 与运算,将SCAN_RSP_CONFIG_FLAG的最低位置0
            if (adv_config_done == 0) {
                esp_ble_gap_start_advertising(&adv_params);
            }
            break;
            
        case ESP_GAP_BLE_ADV_START_COMPLETE_EVT: //广播开始完成
            if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
                ESP_LOGE(TAG, "广播开始失败, status = %d", param->adv_start_cmpl.status);
            } else {
                ESP_LOGI(TAG, "广播开始成功");
            }
            break;

        case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:  // 广播停止完成事件
            if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
                ESP_LOGE(TAG, "广播停止失败");
            }
            else {
                ESP_LOGI(TAG, "广播停止成功");
            }
            break;            
        default:
            ESP_LOGI(TAG, "未处理GAP事件: %d", event);
            break;
    }
}



/* GATTS Profile事件处理函数 */
static void gatts_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
    ESP_LOGI(TAG, "PROFILE_EVT, event %d", event);

    switch (event) {
        case ESP_GATTS_REG_EVT: // 注册事件
            ESP_LOGI(TAG, "ESP_GATTS_REG_EVT, status = %d, app_id = %d", param->reg.status, param->reg.app_id);
            
            // 设置设备名称
            esp_err_t set_dev_name_ret = esp_ble_gap_set_device_name("ESP_BLE32");
            if (set_dev_name_ret) {
                ESP_LOGE(TAG, "set device name failed, error code = %x", set_dev_name_ret);
            }
            
            // 配置广播数据
            esp_err_t raw_adv_ret = esp_ble_gap_config_adv_data_raw(raw_adv_data, sizeof(raw_adv_data));
            if (raw_adv_ret) {
                ESP_LOGE(TAG, "config raw adv data failed, error code = %x", raw_adv_ret);
            }
            adv_config_done |= ADV_CONFIG_FLAG;
            
            // 配置扫描响应数据
            esp_err_t raw_scan_ret = esp_ble_gap_config_scan_rsp_data_raw(raw_scan_rsp_data, sizeof(raw_scan_rsp_data));
            if (raw_scan_ret) {
                ESP_LOGE(TAG, "config raw scan rsp data failed, error code = %x", raw_scan_ret);
            }
            adv_config_done |= SCAN_RSP_CONFIG_FLAG;
            
            // 创建属性表
            esp_err_t create_attr_ret = esp_ble_gatts_create_attr_tab(gatt_db, gatts_if, HRS_IDX_NB_GATT, SVC_INST_ID);
            if (create_attr_ret) {
                ESP_LOGE(TAG, "create attr table failed, error code = %x", create_attr_ret);
            }
            break;

        case ESP_GATTS_READ_EVT: // 读事件
            ESP_LOGI(TAG, "ESP_GATTS_READ_EVT, handle = %d", param->read.handle);
            break;

        case ESP_GATTS_WRITE_EVT: // 写事件
            if (!param->write.is_prep) {
                ESP_LOGI(TAG, "收到写入事件, handle = %d, value len = %d", param->write.handle, param->write.len);
                // 处理CCCD写入
                if (handle_table[IDX_CHAR_CFG_A_GATT] == param->write.handle && param->write.len == 2) {
                    uint16_t descr_value = param->write.value[1] << 8 | param->write.value[0];
                    if (descr_value == 0x0001) { // 通知使能
                        ESP_LOGI(TAG, "notify enable");
                        // 这里可以添加通知发送逻辑
                    }
                }
                
                // 打印接收到的数据
                ESP_LOGI(TAG, "接收到的数据:");
                esp_log_buffer_hex(TAG, param->write.value, param->write.len);  // 以十六进制打印接收到的数据
                
                // 判断是哪个特征值被写入
                if (handle_table[IDX_CHAR_VAL_A_GATT] == param->write.handle) {
                    // 这里是特征A被写入的处理逻辑
                    ESP_LOGI(TAG, "特征A收到数据:");
                    // 这里可以处理接收到的数据
                    // param->write.value 包含写入的数据
                    // param->write.len 是数据长度
                }else if (handle_table[IDX_CHAR_VAL_B_GATT] == param->write.handle) {
                    // 这里是特征B被写入的处理逻辑
                    ESP_LOGI(TAG, "特征B收到数据:");
                    // 这里可以处理接收到的数据
                    // param->write.value 包含写入的数据
                    // param->write.len 是数据长度
                }
                // 发送写响应
                if (param->write.need_rsp) {
                    esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, ESP_GATT_OK, NULL);
                }
            }
            break;

        case ESP_GATTS_CONNECT_EVT: // 连接事件
            ESP_LOGI(TAG, "ESP_GATTS_CONNECT_EVT, conn_id = %d", param->connect.conn_id);
            gl_profile_tab[PROFILE_APP_IDX].conn_id = param->connect.conn_id;
            break;

        case ESP_GATTS_DISCONNECT_EVT: // 断开连接事件
            ESP_LOGI(TAG, "ESP_GATTS_DISCONNECT_EVT, reason = 0x%x", param->disconnect.reason);
            esp_ble_gap_start_advertising(&adv_params);
            break;

        case ESP_GATTS_CREAT_ATTR_TAB_EVT: // 创建属性表事件
            ESP_LOGI(TAG, "ESP_GATTS_CREAT_ATTR_TAB_EVT, status = %d, num_handle = %d", 
                    param->add_attr_tab.status, param->add_attr_tab.num_handle);
                    
            if (param->add_attr_tab.status != ESP_GATT_OK) {
                ESP_LOGE(TAG, "创建属性表失败");
                break;
            }
            // 将创建的属性表句柄复制到handle_table
            memcpy(handle_table, param->add_attr_tab.handles, sizeof(handle_table));
            // 启动服务
            esp_ble_gatts_start_service(handle_table[IDX_SVC_GATT]);
            break;

        default:
            break;
    }
}


/* GATTS事件处理函数 ,主要用于GATTS的注册和回调 */
static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
    ESP_LOGI(TAG, "EVT %d, gatts if %d", event, gatts_if);

    // 如果是注册事件，需要保存 gatts_if
    if (event == ESP_GATTS_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) {
            gl_profile_tab[PROFILE_APP_IDX].gatts_if = gatts_if;
            ESP_LOGI(TAG, "注册应用成功, app_id %04x, status %d\n",
                    param->reg.app_id,
                    param->reg.status);
        } else {
            ESP_LOGE(TAG, "注册应用失败, app_id %04x, status %d\n",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }
    do
    {
        int idx ;
        for (idx = 0; idx < PROFILE_NUM; idx++) {
        //gatts_if == ESP_GATT_IF_NONE 表示没有指定特定的gatts_if,需要调用每个应用的回调函数
        if (gatts_if == ESP_GATT_IF_NONE || gatts_if == gl_profile_tab[idx].gatts_if) {
            if (gl_profile_tab[idx].gatts_cb) {
                gl_profile_tab[idx].gatts_cb(event, gatts_if, param);
            }
        }
    }
    } while (0);

}



void ble_driver_init(void)
{
    esp_err_t err;
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    err = esp_bt_controller_init(&bt_cfg);
    if (err) {
        ESP_LOGE(TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(err));
        return;
    }

    err = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    if (err) {
        ESP_LOGE(TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(err));
        return;
    }

    err = esp_bluedroid_init();
    if (err) {
        ESP_LOGE(TAG, "%s init bluetooth failed: %s", __func__, esp_err_to_name(err));
        return;
    }

    err = esp_bluedroid_enable();
    if (err) {
        ESP_LOGE(TAG, "%s enable bluetooth failed: %s", __func__, esp_err_to_name(err));
        return;
    }

    err = esp_ble_gatts_register_callback(gatts_event_handler);
    if (err){
        ESP_LOGE(TAG, "gatts register error, error code = %x", err);
        return;
    }

    err = esp_ble_gap_register_callback(gap_event_handler);
    if (err){
        ESP_LOGE(TAG, "gap register error, error code = %x", err);
        return;
    }

    err = esp_ble_gatts_app_register(ESP_APP_ID);
    if (err){
        ESP_LOGE(TAG, "gatts app register error, error code = %x", err);
        return;
    }

    esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(500);
    if (local_mtu_ret){
        ESP_LOGE(TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
    }
}


