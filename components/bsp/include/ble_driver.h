#ifndef __BLE_DRIVER_H_
#define __BLE_DRIVER_H_


// 定义特征索引
enum {
    IDX_SVC_GATT,
    
    IDX_CHAR_A_GATT,
    IDX_CHAR_VAL_A_GATT,
    IDX_CHAR_CFG_A_GATT,
    
    IDX_CHAR_B_GATT,
    IDX_CHAR_VAL_B_GATT,
    
    HRS_IDX_NB_GATT,
};

void ble_driver_init(void);




#endif


/*

app_main()
    │
    ├── esp_ble_gatts_app_register()
    │       │
    │       └── 触发 ESP_GATTS_REG_EVT
    │           │
    │           ├── gatts_event_handler 首先接收
    │           │   └── 调用 gatts_profile_event_handler
    │           │       │
    │           │       ├── 设置设备名称
    │           │       ├── 配置广播数据
    │           │       └── 创建属性表
    │           │
    │           └── 触发 ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT
    │               │
    │               └── gap_event_handler 处理
    │                   └── 开始广播
    │
    └── 等待客户端连接...
        │
        ├── 当客户端连接时:
        │   └── 触发 ESP_GATTS_CONNECT_EVT
        │
        ├── 当客户端读取特征值时:
        │   └── 触发 ESP_GATTS_READ_EVT
        │
        ├── 当客户端写入特征值时:
        │   └── 触发 ESP_GATTS_WRITE_EVT
        │
        └── 当客户端断开连接时:
            └── 触发 ESP_GATTS_DISCONNECT_EVT
*/