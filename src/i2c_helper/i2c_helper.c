#include "i2c_helper.h"

static const char *TAG = "i2c_helper";

i2c_master_bus_handle_t bus_handle;
i2c_master_dev_handle_t dev_handle;

i2c_master_bus_config_t i2c_mst_config = {
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .i2c_port = AUTO_SELECT_I2C_PORT,
    .scl_io_num = I2C_SCK_PIN,
    .sda_io_num = I2C_SDA_PIN,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
};

i2c_device_config_t dev_cfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = LIS3DSH_ADDRESS,
    .scl_speed_hz = I2C_MASTER_FREQ_HZ,
};

void i2c_master_init()
{
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));

    ESP_LOGI(TAG, "I2C initialized successfully");
}

void i2c_deinit()
{
    ESP_ERROR_CHECK(i2c_master_bus_rm_device(dev_handle));
    ESP_ERROR_CHECK(i2c_del_master_bus(bus_handle));

    ESP_LOGI(TAG, "I2C deinitialized successfully");
}

esp_err_t i2c_write_register(uint8_t reg_addr, uint8_t data, size_t data_len)
{
    uint8_t write_buf[2] = {reg_addr, data};
    return i2c_master_transmit(dev_handle, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS);
}

esp_err_t i2c_read_register(uint8_t reg_addr, uint8_t data, size_t data_len)
{
    return i2c_master_transmit_receive(dev_handle, &reg_addr, 1, data, data_len, I2C_MASTER_TIMEOUT_MS);
}