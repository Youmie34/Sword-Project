#ifndef _PINS_H_
#define _PINS_H_

#include "../common/common.h"
#include "driver/gpio.h"

#define LED_PIN 3
#define input_pin 17
#define NEO_DIN 0

extern volatile bool flag_input;

void init_pins();
void check_input();

#endif // _PINS_H_