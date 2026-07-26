#ifndef SD_SPI_H
#define SD_SPI_H

#include "driver/sdspi_host.h"
#include "driver/gpio.h"
#include "sdmmc_cmd.h"
#include "../common/common.h"
#include "../pins/pins.h"

extern sdmmc_host_t sd_host;
extern sdspi_device_config_t slot_config;
extern spi_bus_config_t sd_bus_cfg;

void init_spi();
void init_sd_cs();
void deinit_spi();

#endif // SD_SPI_H