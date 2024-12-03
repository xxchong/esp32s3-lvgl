#include "sys.h"


typedef struct {
    lv_obj_t *calculator_page;
    lv_obj_t *textarea;
    lv_obj_t *btnmatrix;
    bool is_new_input;
    double current_value;    // 当前累计值
    char last_operator;      // 上一个运算符
    bool has_last_value;     // 是否有上一个值
} Calculators;

static Calculators *calculators_app;

static const char *btnm_map[] = {"AC", LV_SYMBOL_LEFT, "%", "/", "\n",
                                "7", "8", "9", "x", "\n",
                                "4", "5", "6", "-", "\n",
                                "1", "2", "3", "+", "\n",
                                "0", ".", "=", ""};

// 辅助函数：判断是否为数字或小数点
static bool is_number_char(char c) {
    return isdigit(c) || c == '.';
}

// 辅助函数：获取两个数字和运算符
static bool get_numbers(const char* expr, double* num1, double* num2, char* op) {
    char* endptr;
    *num1 = strtod(expr, &endptr);
    
    // 跳过空格
    while (*endptr == ' ') endptr++;
    
    // 获取运算符
    *op = *endptr;
    if (*op == 'x') *op = '*';
    
    // 跳到第二个数字
    endptr++;
    while (*endptr == ' ') endptr++;
    
    *num2 = strtod(endptr, NULL);
    return true;
}

// 执行单步计算
static double perform_operation(double num1, double num2, char op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num2 != 0 ? num1 / num2 : 0;
        case '%': return num2 != 0 ? fmod(num1, num2) : 0;
        default: return num2;  // 如果没有运算符，返回第二个数
    }
}

// 格式化结果
static void format_result(double result, char* output, size_t size) {
    if (result == (int)result) {
        snprintf(output, size, "%d", (int)result);
    } else {
        snprintf(output, size, "%.6f", result);
        // 移除末尾的0
        char* p = output + strlen(output) - 1;
        while (*p == '0' && p > output) {
            *p-- = '\0';
        }
        if (*p == '.') *p = '\0';
    }
}

// 计算器按钮事件回调
static void calculator_event_cb(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_target(e);
    uint32_t id = lv_btnmatrix_get_selected_btn(obj);
    const char *txt = lv_btnmatrix_get_btn_text(obj, id);
    
    if (strcmp(txt, "AC") == 0) {
        // 清空所有状态
        lv_textarea_set_text(calculators_app->textarea, "");
        calculators_app->current_value = 0;
        calculators_app->last_operator = 0;
        calculators_app->has_last_value = false;
        calculators_app->is_new_input = false;
    }
    else if (strcmp(txt, LV_SYMBOL_LEFT) == 0) {
        // 退格
        const char* current = lv_textarea_get_text(calculators_app->textarea);
        size_t len = strlen(current);
        if (len > 0) {
            char* new_text = malloc(len);
            strncpy(new_text, current, len - 1);
            new_text[len - 1] = '\0';
            lv_textarea_set_text(calculators_app->textarea, new_text);
            free(new_text);
        }
    }
    else if (strcmp(txt, "+") == 0 || strcmp(txt, "-") == 0 || 
             strcmp(txt, "x") == 0 || strcmp(txt, "/") == 0 || 
             strcmp(txt, "%") == 0) {
        // 处理运算符
        const char* current = lv_textarea_get_text(calculators_app->textarea);
        double current_num = atof(current);
        
        if (calculators_app->has_last_value) {
            // 执行前一个运算
            calculators_app->current_value = perform_operation(
                calculators_app->current_value, 
                current_num, 
                calculators_app->last_operator
            );
        } else {
            calculators_app->current_value = current_num;
            calculators_app->has_last_value = true;
        }
        
        // 保存当前运算符
        calculators_app->last_operator = (strcmp(txt, "x") == 0) ? '*' : txt[0];
        
        // 显示当前结果
        char result_str[32];
        format_result(calculators_app->current_value, result_str, sizeof(result_str));
        lv_textarea_set_text(calculators_app->textarea, result_str);
        calculators_app->is_new_input = true;
    }
    else if (strcmp(txt, "=") == 0) {
        // 计算最终结果
        const char* current = lv_textarea_get_text(calculators_app->textarea);
        double current_num = atof(current);
        
        if (calculators_app->has_last_value && calculators_app->last_operator) {
            calculators_app->current_value = perform_operation(
                calculators_app->current_value, 
                current_num, 
                calculators_app->last_operator
            );
            
            // 显示结果
            char result_str[32];
            format_result(calculators_app->current_value, result_str, sizeof(result_str));
            lv_textarea_set_text(calculators_app->textarea, result_str);
            
            // 重置状态
            calculators_app->has_last_value = false;
            calculators_app->last_operator = 0;
            calculators_app->is_new_input = true;
        }
    }
    else {
        // 输入数字或小数点
        if (calculators_app->is_new_input) {
            lv_textarea_set_text(calculators_app->textarea, "");
            calculators_app->is_new_input = false;
        }
        lv_textarea_add_text(calculators_app->textarea, txt);
    }
}

// 创建计算器页面
lv_obj_t *calculators_create(void) {
    if (calculators_app != NULL) {
        free(calculators_app);
    }
    calculators_app = (Calculators *)calloc(1, sizeof(Calculators));
    
    // 初始化新增字段
    calculators_app->current_value = 0;
    calculators_app->last_operator = 0;
    calculators_app->has_last_value = false;
    calculators_app->is_new_input = false;
    
    calculators_app->calculator_page = create_page("Calculator");
    
    // 设置计算器页面背景为纯黑色
    lv_obj_set_style_bg_color(calculators_app->calculator_page, lv_color_hex(0x000000), 0);
    
    // 创建显示区域
    calculators_app->textarea = lv_textarea_create(calculators_app->calculator_page);
    lv_obj_set_size(calculators_app->textarea, 230, 70);
    lv_obj_align(calculators_app->textarea, LV_ALIGN_TOP_MID, 0, 2);
    lv_textarea_set_text(calculators_app->textarea, "");
    lv_obj_add_state(calculators_app->textarea, LV_STATE_DISABLED);
    lv_obj_set_style_text_font(calculators_app->textarea, &lv_font_montserrat_32, 0);
    
    // 显示区域样式
    lv_obj_set_style_bg_color(calculators_app->textarea, lv_color_hex(0x000000), 0);
    lv_obj_set_style_text_color(calculators_app->textarea, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_border_width(calculators_app->textarea, 0, 0);
    lv_obj_set_style_text_align(calculators_app->textarea, LV_TEXT_ALIGN_RIGHT, 0);
    
    // 创建按钮矩阵
    calculators_app->btnmatrix = lv_btnmatrix_create(calculators_app->calculator_page);
    lv_obj_set_style_pad_all(calculators_app->btnmatrix, 2, 0);
    lv_obj_set_size(calculators_app->btnmatrix, 240, 200);
    lv_btnmatrix_set_map(calculators_app->btnmatrix, btnm_map);
    lv_btnmatrix_set_btn_width(calculators_app->btnmatrix, 16, 2);
    lv_obj_align(calculators_app->btnmatrix, LV_ALIGN_BOTTOM_MID, 0, -5);
    lv_obj_set_style_text_font(calculators_app->btnmatrix, &lv_font_montserrat_28, 0);
    
    // 按钮矩阵整体样式
    lv_obj_set_style_bg_color(calculators_app->btnmatrix, lv_color_hex(0x000000), 0);
    lv_obj_set_style_text_color(calculators_app->btnmatrix, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_pad_row(calculators_app->btnmatrix, 8, 0);
    lv_obj_set_style_pad_column(calculators_app->btnmatrix, 8, 0);
    lv_obj_set_style_border_width(calculators_app->btnmatrix, 0, 0);
    
    // 普通数字按钮样式
    lv_obj_set_style_bg_color(calculators_app->btnmatrix, lv_color_hex(0x333333), LV_PART_ITEMS);
    lv_obj_set_style_bg_color(calculators_app->btnmatrix, lv_color_hex(0x4D4D4D), LV_PART_ITEMS | LV_STATE_PRESSED);
    lv_obj_set_style_border_width(calculators_app->btnmatrix, 0, LV_PART_ITEMS);
    lv_obj_set_style_text_color(calculators_app->btnmatrix, lv_color_hex(0xFFFFFF), LV_PART_ITEMS);
    
    // 运算符按钮样式
    uint32_t operator_ids[] = {3, 7, 11, 15, 18};
    for (int i = 0; i < sizeof(operator_ids)/sizeof(operator_ids[0]); i++) {
        lv_btnmatrix_set_btn_ctrl(calculators_app->btnmatrix, operator_ids[i], LV_BTNMATRIX_CTRL_CUSTOM_1);
    }
    lv_obj_set_style_bg_color(calculators_app->btnmatrix, lv_color_hex(0x007AFF), LV_PART_ITEMS | LV_BTNMATRIX_CTRL_CUSTOM_1);
    lv_obj_set_style_text_color(calculators_app->btnmatrix, lv_color_hex(0xFFFFFF), LV_PART_ITEMS | LV_BTNMATRIX_CTRL_CUSTOM_1);
    
    // 添加事件处理
    lv_obj_add_event_cb(calculators_app->btnmatrix, calculator_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    
    return calculators_app->calculator_page;
}