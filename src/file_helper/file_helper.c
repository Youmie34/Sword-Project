#include "file_helper.h"

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

void create_test_files_on_sd(void)
{
    char filename[32];

    for (uint8_t i = 1; i <= SAMPLE_AMOUNT; i++)
    {
        snprintf(filename, sizeof(filename), "test_%d.txt", i);
        create_file_on_sd(filename);
    }
}