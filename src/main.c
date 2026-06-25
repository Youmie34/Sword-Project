#include "file_helper/file_helper.h"
#include "esp_err.h"
#include "esp_log.h"
#include "sd_spi/sd_spi.h"
#include "sd_mount/sd_mount.h"

static const char *TAG = "sdcard";

void app_main(void)
{
    ESP_LOGI(TAG, "Initializing SPI");

    spi_bus_initialize(sd_host.slot, &sd_bus_cfg, SDSPI_DEFAULT_DMA);
    init_sd_cs();
    // sdspi_host_init();

    esp_vfs_fat_sdspi_mount(MOUNT_PATH, &sd_host, &slot_config, &sd_mount_config, NULL);
    ESP_LOGI(TAG, "Finished!");

    create_test_files_on_sd();
    list_files();
}