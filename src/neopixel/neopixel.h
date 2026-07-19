#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include "../../include/led_strip/led_strip.h"
#include "colors/colors.h"

extern led_strip_config_t strip_config;
extern led_strip_rmt_config_t rmt_config;
extern led_strip_handle_t led_strip;

void init_neopixel();
void test_neo();

#endif // NEOPIXEL_H