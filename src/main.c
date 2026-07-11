#include "file_helper/file_helper.h"
#include "i2s_helper/i2s_helper.h"
#include "common/common.h"
#include "sd_spi/sd_spi.h"
#include "sd_mount/sd_mount.h"
#include "pins/pins.h"

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
    periph_init();
    create_test_files_on_sd();
    list_files();
    deinit_periph();
}