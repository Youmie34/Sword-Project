#ifndef I2S_HELPER_H
#define I2S_HELPER_H

// #include "driver/i2s.h" //depreciated
#include "driver/i2s_std.h"
#include "driver/i2s_pdm.h"
#include "driver/i2s_tdm.h"
#include "../common/common.h"

#define I2S_SAMPLE_RATE 44100
#define I2S_BIT_DEPTH 32     // INMP441 liefert oft 24 Bit, aber 32 ist Standard für DMA alignment
#define I2S_DMA_BUF_COUNT 8  // Mehr Puffer für stabilere Aufzeichnung bei höheren Sampling-Rates
#define I2S_DMA_BUF_LEN 1024 // Anzahl Samples pro Block.
                             // 1024 * 44100 ≈ 23ms Latenz.
                             // Kann erhöht werden (z.B. 2048 oder 4096) um CPU-Last zu senken,
                             // erhöht aber die Latenz.
#define I2S_SCK_PIN 1        // BCLK (Serial Clock) -> An INMP441 SCK
#define I2S_WS_PIN 38        // LRCLK (Word Select) -> An INMP441 L/R (GND oder VCC)
#define I2S_DIN_PIN 2        // SD (Data Input) -> An INMP441 SD

extern i2s_std_config_t i2s_config;
extern i2s_std_gpio_config_t pin_config;

void i2s_init();
void input_data();

#endif // I2S_HELPER_H