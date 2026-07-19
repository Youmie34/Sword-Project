#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include "../../include/led_strip/led_strip.h"
#include "colors/colors.h"
#include <math.h>

#define BRIGHTNESS 50

extern led_strip_config_t strip_config;
extern led_strip_rmt_config_t rmt_config;
extern led_strip_handle_t led_strip;
extern float brightness_corrected;

void init_neopixel();
color_t apply_brightness(color_t color);
void show_neopixel(led_strip_handle_t led_strip, color_t color);
void wipe_neopixel(led_strip_handle_t led_strip, color_t color);

#endif // NEOPIXEL_H