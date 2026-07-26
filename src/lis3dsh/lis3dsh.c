#include "lis3dsh.h"

lis3dsh_cmd_t accelerometer_cmd = {
    .who_am_i = 0x0F,
    .ctrl_reg1 = 0x21,
    .ctrl_reg2 = 0x22,
    .ctrl_reg3 = 0x23,
    .ctrl_reg4 = 0x20,
    .stat = 0x18,
    .status = 0x27};

void lis3dsh_init()
{
}

void lis3dsh_read_data()
{
}