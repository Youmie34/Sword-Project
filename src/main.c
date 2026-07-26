#include "file_helper/file_helper.h"
#include "i2s_helper/i2s_helper.h"
#include "mic_inmp441/mic_inmp441.h"
#include "common/common.h"
#include "sd_spi/sd_spi.h"
#include "sd_mount/sd_mount.h"
#include "pins/pins.h"
#include "neopixel/neopixel.h"
#include "i2c_helper/i2c_helper.h"
#include "lis3dsh/lis3dsh.h"

// static const char *TAG_MAIN = "main";

void periph_init()
{
    i2c_master_init();
}

void deinit_periph()
{
    i2c_deinit();
}

void app_main(void)
{
}