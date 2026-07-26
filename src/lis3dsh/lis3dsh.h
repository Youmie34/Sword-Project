#ifndef LIS3DSH_H
#define LIS3DSH_H

#include "../i2c_helper/i2c_helper.h"

#define LIS3DSH_ADDRESS 0x1e

void lis3dsh_init();
void lis3dsh_read_data();

typedef struct
{
    uint8_t who_am_i;  // shows slave address of the device
    uint8_t ctrl_reg1; // SM1 setting
    uint8_t ctrl_reg2; // SM2 setting
    uint8_t ctrl_reg3; // Interrupt control register
    uint8_t ctrl_reg4; // axis setup
    uint8_t stat;      // interrupt status register
    uint8_t status;    // status register
} lis3dsh_cmd_t;

extern lis3dsh_cmd_t accelerometer_cmd;

#endif // LIS3DSH_H