#ifndef I2C_HELPER_H
#define I2C_HELPER_H

#include "hal/i2c_types.h"
#include "driver/i2c_master.h"
#include "driver/i2c_slave.h"
#include "../pins/pins.h"

void init_i2c();
void deinit_i2c();

#endif // I2C_HELPER_H