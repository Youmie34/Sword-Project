#include "neopixel.h"
#include "../pins/pins.h"

/// LED strip common configuration
led_strip_config_t strip_config = {
    .strip_gpio_num = NEO_DIN,                                   // The GPIO that connected to the LED strip's data line
    .max_leds = 60,                                              // The number of LEDs in the strip,
    .led_model = LED_MODEL_WS2812,                               // LED strip model, it determines the bit timing
    .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color component format is G-R-B
    .flags = {
        .invert_out = false, // don't invert the output signal
    }};

/// RMT backend specific configuration
led_strip_rmt_config_t rmt_config = {
    .clk_src = RMT_CLK_SRC_DEFAULT,    // different clock source can lead to different power consumption
    .resolution_hz = 10 * 1000 * 1000, // RMT counter clock frequency: 10MHz
    .mem_block_symbols = 64,           // the memory size of each RMT channel, in words (4 bytes)
    .flags = {
        .with_dma = false, // DMA feature is available on chips like ESP32-S3/P4
    }};

/// Create the LED strip object
led_strip_handle_t led_strip = NULL;

void init_neopixel()
{
    ESP_LOGI("NEOPIXEL", "Initializing Neopixel...");

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    led_strip_clear(led_strip);

    ESP_LOGI("NEOPIXEL", "Neopixel initialized successfully.");
}

void test_neo()
{
    if (led_strip == NULL)
    {
        ESP_LOGE("NEOPIXEL", "LED strip is not initialized");
        return;
    }

    ESP_LOGI("NEOPIXEL", "Lighting up the neopixels...");

    led_strip_clear(led_strip);

    for (uint32_t i = 0; i < strip_config.max_leds; i++)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, i, 0, 255, 0));
    }

    ESP_ERROR_CHECK(led_strip_refresh(led_strip));
}