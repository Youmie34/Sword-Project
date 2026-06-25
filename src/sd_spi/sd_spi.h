#ifndef SD_SPI_H
#define SD_SPI_H

#include "driver/sdspi_host.h"
#include "driver/gpio.h"
#include "sdmmc_cmd.h"

#define SD_MISO 7
#define SD_MOSI 6
#define SD_CLK 5
#define SD_CS 4

extern sdmmc_host_t sd_host;
extern sdspi_device_config_t slot_config;
extern spi_bus_config_t sd_bus_cfg;

void init_sd_cs();

#endif // SD_SPI_H