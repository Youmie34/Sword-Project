#ifndef I2S_HELPER_H
#define I2S_HELPER_H

// #include "driver/i2s.h" //depreciated
#include "driver/i2s_std.h"
#include "driver/i2s_pdm.h"
#include "driver/i2s_tdm.h"
#include "../common/common.h"
#include "../mic_inmp441/mic_inmp441.h"
#include "pins/pins.h"

#define I2S_SAMPLE_RATE 44100
#define I2S_BIT_DEPTH 32
#define I2S_DMA_BUF_COUNT 8  // Mehr Puffer für stabilere Aufzeichnung bei höheren Sampling-Rates
#define I2S_DMA_BUF_LEN 1024 // amount of samples per blog
#define I2S_SCK_PIN 1        // BCLK (Serial Clock)
#define I2S_WS_PIN 38        // WS (Word Select)
#define I2S_DIN_PIN 2        // SD (Data Input)
#define RECORD_TIME 3        // in seconds

extern i2s_std_config_t i2s_config;

void i2s_init();
void i2s_deinit();
void i2s_record_data();
void i2s_record_data_while_input_high();

#endif // I2S_HELPER_H