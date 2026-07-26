#ifndef _PINS_H_
#define _PINS_H_

#include "../common/common.h"
#include "driver/gpio.h"

#define LED_PIN 3
#define input_pin 17
#define NEO_DIN 0
#define SD_MISO 7
#define SD_MOSI 6
#define SD_CLK 5
#define SD_CS 4
#define I2S_SCK_PIN 1 // BCLK (Serial Clock)
#define I2S_WS_PIN 38 // WS (Word Select)
#define I2S_DIN_PIN 2 // SD (Data Input)
#define I2C_SCK_PIN 22
#define I2C_SDA_PIN 21
#define INT1_PIN 39
#define INT2_PIN 36

extern volatile bool flag_input;

void init_pins();
void check_input();

#endif // _PINS_H_