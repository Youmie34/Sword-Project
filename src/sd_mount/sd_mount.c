#include "sd_mount.h"

static const char *TAG_SD_MOUNT = "sd_mount";
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
        ESP_LOGE(TAG_SD_MOUNT, "Failed to open directory: %s", MOUNT_PATH);
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
            ESP_LOGI(TAG_SD_MOUNT, "%s", entry->d_name);
        }
        closedir(sd_dir);
    }
}