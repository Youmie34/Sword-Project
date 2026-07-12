#include "file_helper.h"

static const char *TAG_FILE_HELPER = "file_helper";
TinyWav tw;
char full_path[64];

void create_tinywave_file(const char *filename)
{
    snprintf(full_path, sizeof(full_path), "%s/%s", MOUNT_PATH, filename);

    int err = tinywav_open_write(&tw,
                                 NUM_CHANNELS, SAMPLE_RATE,
                                 TW_INT16, TW_INTERLEAVED,
                                 full_path);

    if (err != 0)
    {
        ESP_LOGE(TAG_FILE_HELPER, "Failed to open wave file for writing: %s", full_path);
        return;
    }

    ESP_LOGI(TAG_FILE_HELPER, "Created wave file: %s", full_path);
}

void create_test_files_on_sd(void)
{
    char filename[32];

    for (uint8_t i = 1; i <= SAMPLE_AMOUNT; i++)
    {
        snprintf(filename, sizeof(filename), "test_%d.wav", i);
        record_wav(filename);
    }
}