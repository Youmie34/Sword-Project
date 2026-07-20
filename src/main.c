#include "file_helper/file_helper.h"
#include "i2s_helper/i2s_helper.h"
#include "mic_inmp441/mic_inmp441.h"
#include "common/common.h"
#include "sd_spi/sd_spi.h"
#include "sd_mount/sd_mount.h"
#include "pins/pins.h"
#include "neopixel/neopixel.h"

// static const char *TAG_MAIN = "main";

void periph_init()
{
    init_pins();
    init_spi();
    init_sd_cs();
    mount_sd_card();
    i2s_init();
}

void deinit_periph()
{
    i2s_deinit();
    unmount_sd_card();
    deinit_spi();
}

void app_main(void)
{
    init_neopixel();

    while (1)
    {
        theater_chase_neopixel(led_strip, color_red);
        theater_chase_neopixel(led_strip, color_green);
        theater_chase_neopixel(led_strip, color_blue);
    }
}