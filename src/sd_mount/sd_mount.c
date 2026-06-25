#include "sd_mount.h"

DIR *sd_dir = NULL;

esp_vfs_fat_mount_config_t sd_mount_config = {
    .format_if_mount_failed = false,
    .max_files = 10,
    .allocation_unit_size = 16 * 1024,
};

void open_directory()
{
    sd_dir = opendir(MOUNT_PATH);

    if (sd_dir == NULL)
    {
        printf("Failed to open directory: %s\n", MOUNT_PATH);
        return;
    }
}

void list_files()
{
    open_directory();

    if (sd_dir != NULL)
    {
        struct dirent *entry;
        while ((entry = readdir(sd_dir)) != NULL)
        {
            printf("%s\n", entry->d_name);
        }
        closedir(sd_dir);
    }
}

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