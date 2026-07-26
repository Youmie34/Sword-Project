#ifndef I2C_HELPER_H
#define I2C_HELPER_H

#include "hal/i2c_types.h"
#include "driver/i2c_master.h"
#include "driver/i2c_slave.h"
#include "../common/common.h"
#include "../pins/pins.h"
#include "lis3dsh/lis3dsh.h"

#define AUTO_SELECT_I2C_PORT -1
#define I2C_MASTER_FREQ_HZ 200000
#define I2C_MASTER_TIMEOUT_MS 1000

void i2c_master_init();
void i2c_deinit();
esp_err_t i2c_write_register(uint8_t reg_addr, uint8_t data, size_t data_len);
esp_err_t i2c_read_register(uint8_t reg_addr, uint8_t data, size_t data_len);

extern i2c_master_bus_config_t i2c_mst_config;
extern i2c_master_bus_handle_t bus_handle;
extern i2c_master_dev_handle_t dev_handle;

#endif // I2C_HELPER_H