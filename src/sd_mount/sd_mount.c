#include "sd_mount.h"

esp_vfs_fat_mount_config_t sd_mount_config = {
    .format_if_mount_failed = false,
    .max_files = 10,
    .allocation_unit_size = 16 * 1024,
};