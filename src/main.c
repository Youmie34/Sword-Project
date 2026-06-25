
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

    list_files();
    create_file_on_sd("test.txt");
    list_files();
}