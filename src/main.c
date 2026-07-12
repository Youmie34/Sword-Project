#include "file_helper/file_helper.h"
#include "i2s_helper/i2s_helper.h"
#include "mic_inmp441/mic_inmp441.h"
#include "common/common.h"
#include "sd_spi/sd_spi.h"
#include "sd_mount/sd_mount.h"
#include "ml/ml.h"
#include "pins/pins.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG_MAIN = "main";

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

    uint32_t file_index = 1;
    char filename[32];

    while (true)
    {
        check_input();

        if (flag_input)
        {
            snprintf(filename, sizeof(filename), "record_%lu.wav", (unsigned long)file_index++);
            ESP_LOGI(TAG_MAIN, "Touch active, start recording: %s", filename);

            record_wav(filename);

            list_files();

            // Simple debounce after releasing the touch sensor.
            vTaskDelay(pdMS_TO_TICKS(200));
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(20));
        }
    }
}