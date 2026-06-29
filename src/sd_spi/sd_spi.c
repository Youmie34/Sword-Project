#include "sd_spi.h"

static const char *TAG_SD_SPI = "sd_spi";

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
    ESP_LOGI(TAG_SD_SPI, "SD card CS pin initialized");
}

void init_spi()
{
    esp_err_t ret = spi_bus_initialize(sd_host.slot, &sd_bus_cfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG_SD_SPI, "Failed to initialize SPI bus: %s", esp_err_to_name(ret));
        return;
    }
    ESP_LOGI(TAG_SD_SPI, "SPI bus initialized successfully");
}

void deinit_spi()
{
    if (ESP_OK != spi_bus_free(sd_host.slot))
    {
        ESP_LOGE(TAG_SD_SPI, "Failed to deinitialize SPI bus");
        return;
    }
    ESP_LOGI(TAG_SD_SPI, "SPI bus deinitialized");
}