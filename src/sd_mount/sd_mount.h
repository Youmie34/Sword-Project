#ifndef SD_MOUNT_H
#define SD_MOUNT_H

#include "esp_vfs_fat.h"

#define MOUNT_PATH "/sdcard"

extern esp_vfs_fat_mount_config_t sd_mount_config;

#endif // SD_MOUNT_H