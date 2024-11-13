#pragma once

#include "esp_err.h"
#include "stdbool.h"

esp_err_t audio_player_init(void);
esp_err_t audio_player_play_mp3(const char *filename);
void audio_player_stop(void);
void audio_player_pause(void);
void audio_player_resume(void);
bool audio_player_is_playing(void);
esp_err_t test_mp3_file_read(const char *filename);
esp_err_t test_mp3_file_read_and_decode(const char *filename);
