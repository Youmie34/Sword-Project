#include "file_helper.h"

static const char *TAG_FILE_HELPER = "file_helper";

void create_file_on_sd(const char *filename)
{
    char full_path[30];
    snprintf(full_path, sizeof(full_path), "%s/%s", MOUNT_PATH, filename);

    FILE *file = fopen(full_path, "w");

    if (file == NULL)
    {
        ESP_LOGE(TAG_FILE_HELPER, "Failed to create file: %s", full_path);
        return;
    }

    create_wave_file(filename);

    fclose(file);

    ESP_LOGI(TAG_FILE_HELPER, "Created file: %s", full_path);
}

void create_wave_file(const char *filename)
{
    char full_path[30];
    snprintf(full_path, sizeof(full_path), "%s/%s", MOUNT_PATH, filename);

    TinyWav tw;

    int err = tinywav_open_write(&tw,
                                 NUM_CHANNELS, SAMPLE_RATE,
                                 TW_INT16, TW_INTERLEAVED,
                                 full_path);

    if (err != 0)
    {
        ESP_LOGE(TAG_FILE_HELPER, "Failed to open wave file for writing: %s", full_path);
        return;
    }

    tinywav_close_write(&tw);

    ESP_LOGI(TAG_FILE_HELPER, "Created wave file: %s", full_path);
}

void create_test_files_on_sd(void)
{
    char filename[32];

    for (uint8_t i = 1; i <= SAMPLE_AMOUNT; i++)
    {
        snprintf(filename, sizeof(filename), "test_%d.wav", i);
        create_file_on_sd(filename);
    }
}