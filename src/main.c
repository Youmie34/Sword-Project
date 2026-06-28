#include "file_helper/file_helper.h"
#include "i2s_helper/i2s_helper.h"
#include "common/common.h"
#include "sd_spi/sd_spi.h"
#include "sd_mount/sd_mount.h"

// static const char *TAG_MAIN = "main";

void app_main(void)
{
    // ESP_LOGI(TAG_MAIN, "Initializing SPI");

    // spi_bus_initialize(sd_host.slot, &sd_bus_cfg, SDSPI_DEFAULT_DMA);
    // init_sd_cs();

    // esp_vfs_fat_sdspi_mount(MOUNT_PATH, &sd_host, &slot_config, &sd_mount_config, NULL);
    // ESP_LOGI(TAG_MAIN, "Finished Mounting SD");

    // create_test_files_on_sd();
    // list_files();

    i2s_init();
    while (1)
    {
        input_data();
    }
    i2s_deinit();
}