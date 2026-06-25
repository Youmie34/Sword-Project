#include "file_helper.h"

// TODO: delete
//  TinyWavHeader header = {
//      .ChunkID = {'R', 'I', 'F', 'F'},
//      .ChunkSize = 0,
//      .Format = {'W', 'A', 'V', 'E'},
//      .Subchunk1ID = {'f', 'm', 't', ' '},
//      .Subchunk1Size = 16,
//      .AudioFormat = 1,
//      .NumChannels = NUM_CHANNELS,
//      .SampleRate = SAMPLE_RATE,
//      .ByteRate = BIT_RATE,
//      .BlockAlign = BLOCK_ALIGN,
//      .BitsPerSample = SAMPLING_RATE,
//      .Subchunk2ID = {'d', 'a', 't', 'a'},
//      .Subchunk2Size = 0};

void create_file_on_sd(const char *filename)
{
    char full_path[30];
    snprintf(full_path, sizeof(full_path), "%s/%s", MOUNT_PATH, filename);

    FILE *file = fopen(full_path, "w");
    if (file == NULL)
    {
        printf("Failed to create file: %s\n", full_path);
        return;
    }

    fprintf(file, "Hello from ESP32-S3\n");
    fclose(file);

    printf("Created file: %s\n", full_path);
}

void write_wave_file(const char *filename, const int16_t *data, size_t len)
{
    int err = 0;

    err = tinywav_open_write(&tw,
                             NUM_CHANNELS, SAMPLE_RATE,
                             TW_INT16, TW_INLINE,
                             filename);

    tinywav_isOpen(&tw);
    // tinywav_write_f(&tw, (void *)data, len);
}

void create_test_files_on_sd(void)
{
    char filename[32];

    for (uint8_t i = 1; i <= SAMPLE_AMOUNT; i++)
    {
        snprintf(filename, sizeof(filename), "test_%d.txt", i);
        create_file_on_sd(filename);
    }
}