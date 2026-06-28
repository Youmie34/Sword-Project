#include "sd_mount.h"

static const char *TAG_SD_MOUNT = "sd_mount";
DIR *sd_dir = NULL;
sdmmc_card_t *card = NULL;

void mount_sd_card()
{
    esp_vfs_fat_mount_config_t sd_mount_config = {
        .format_if_mount_failed = true,
        .max_files = 10,
        .allocation_unit_size = 16 * 1024,
    };

    esp_err_t ret = esp_vfs_fat_sdspi_mount(MOUNT_PATH, &sd_host, &slot_config, &sd_mount_config, &card);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG_SD_MOUNT, "Failed to mount SD card: %s", esp_err_to_name(ret));
        return;
    }
    ESP_LOGI(TAG_SD_MOUNT, "SD card mounted successfully");
}

void unmount_sd_card()
{
    if (card != NULL)
    {
        esp_vfs_fat_sdcard_unmount(MOUNT_PATH, card);
        card = NULL;
    }
    ESP_LOGI(TAG_SD_MOUNT, "Card unmounted");
}

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