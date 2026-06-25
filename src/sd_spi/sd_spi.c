#include "sd_spi.h"

sdmmc_host_t sd_host = SDSPI_HOST_DEFAULT();
sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();

spi_bus_config_t sd_bus_cfg = {
    .mosi_io_num = SD_MOSI,
    .miso_io_num = SD_MISO,
    .sclk_io_num = SD_CLK,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
    .max_transfer_sz = 4000,
};

void init_sd_cs()
{
    slot_config.gpio_cs = SD_CS;
    slot_config.host_id = sd_host.slot;
}