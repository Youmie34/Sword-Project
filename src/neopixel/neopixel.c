#include "neopixel.h"
#include "../pins/pins.h"

static const char *TAG_NEOPIXEL = "neopixel";
float brightness_corrected = powf(BRIGHTNESS / 255.0f, 2.8f); // normalize and use gamma correction for brightness adjustment

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
    ESP_LOGI(TAG_NEOPIXEL, "Initializing Neopixel...");

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    led_strip_clear(led_strip);

    ESP_LOGI(TAG_NEOPIXEL, "Neopixel initialized successfully.");
}

color_t apply_brightness(color_t color)
{
    color_t adjusted = {
        .red = (uint8_t)(color.red * brightness_corrected),
        .green = (uint8_t)(color.green * brightness_corrected),
        .blue = (uint8_t)(color.blue * brightness_corrected),
    };
    return adjusted;
}

void show_neopixel(led_strip_handle_t led_strip, color_t color)
{
    ESP_LOGI(TAG_NEOPIXEL, "Lighting up the neopixels...");

    led_strip_clear(led_strip);

    for (uint32_t i = 0; i < strip_config.max_leds; i++)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, i, color.red, color.green, color.blue));
    }
    ESP_ERROR_CHECK(led_strip_refresh(led_strip));
}

void wipe_neopixel(led_strip_handle_t led_strip, color_t color)
{
    // ESP_LOGI(TAG_NEOPIXEL, "Lighting up the neopixels...");

    color_t dimmed = apply_brightness(color);

    for (int i = 0; i < strip_config.max_leds; i++)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, i, dimmed.red, dimmed.green, dimmed.blue));
        ESP_ERROR_CHECK(led_strip_refresh(led_strip));
        vTaskDelay(pdMS_TO_TICKS(30));
    }
}