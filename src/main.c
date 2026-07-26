#include "file_helper/file_helper.h"
#include "i2s_helper/i2s_helper.h"
#include "mic_inmp441/mic_inmp441.h"
#include "common/common.h"
#include "sd_spi/sd_spi.h"
#include "sd_mount/sd_mount.h"
#include "pins/pins.h"
#include "neopixel/neopixel.h"
#include "i2c_helper/i2c_helper.h"

// static const char *TAG_MAIN = "main";

void periph_init()
{
    init_i2c();
}

void deinit_periph()
{
    deinit_i2c();
}

void app_main(void)
{
}