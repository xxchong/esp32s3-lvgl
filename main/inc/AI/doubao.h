#ifndef __DOUBAO_H__
#define __DOUBAO_H__

#include "esp_err.h"

char * create_doubao_request_body(const char *message);
esp_err_t chat_with_doubao(const char *message, char *response_buffer, size_t buffer_size);

#endif