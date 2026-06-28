#ifndef SD_MOUNT_H
#define SD_MOUNT_H

#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "../common/common.h"
#include <dirent.h>
#include <stdio.h>
#include "../sd_spi/sd_spi.h"

#define MOUNT_PATH "/sdcard"

extern esp_vfs_fat_mount_config_t sd_mount_config;
extern DIR *sd_dir;
extern sdmmc_card_t *card;

void mount_sd_card();
void unmount_sd_card();
void open_directory();
void list_files();

#endif // SD_MOUNT_H