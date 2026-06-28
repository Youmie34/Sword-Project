#include "file_helper.h"

static const char *TAG_FILE_HELPER = "file_helper";
TinyWav tw;
char full_path[30];

// TinyWav tw = {
//     .f = NULL,
//     .h = {{0}},
//     .numChannels = NUM_CHANNELS,
//     .numFramesInHeader = 0,
//     .totalFramesReadWritten = 0,
//     .chanFmt = TW_INTERLEAVED,
//     .sampFmt = TW_INT16};

void create_file_on_sd(const char *filename)
{
    snprintf(full_path, sizeof(full_path), "%s/%s", MOUNT_PATH, filename);

    FILE *file = fopen(full_path, "w");

    if (file == NULL)
    {
        ESP_LOGE(TAG_FILE_HELPER, "Failed to create file: %s", full_path);
        return;
    }

    create_wave_file(filename);

    fclose(file);
}

void write_wav_data(const char *filename)
{
    // TODO: create_data
    // tinywav_write_f(&tw, data, data_size);
    float silence_frame[2] = {0.0f, 0.0f};

    for (int i = 0; i < SAMPLE_RATE; i++)
    {
        tinywav_write_f(&tw, silence_frame, 1);
    }
}

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

void check_file_exists(const char *fullpath)
{
    struct stat stat_buffer;

    if (stat(fullpath, &stat_buffer) == 0)
    {
        // Delete it if it exists
        f_unlink(fullpath);
        ESP_LOGI(TAG_FILE_HELPER, "File exists and has been deleted: %s", fullpath);
    }
}

FILE *open_file(const char *full_path)
{
    FILE *file = fopen(full_path, "a");

    if (file == NULL)
    {
        ESP_LOGE(TAG_FILE_HELPER, "Failed to open file: %s", full_path);
        return NULL;
    }

    ESP_LOGI(TAG_FILE_HELPER, "Opened file: %s", full_path);
    return file;
}