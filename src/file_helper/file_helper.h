#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include "../sd_mount/sd_mount.h"
#include "../common/common.h"
#include "../../include/tinywav/tinywav.h"

#define SAMPLE_AMOUNT 5
#define NUM_CHANNELS 2
#define SAMPLE_RATE 44100 // 44.100kHz
#define SAMPLING_RATE 16  // 16 bit
#define BLOCK_ALIGN (NUM_CHANNELS * SAMPLING_RATE / 8)
#define BIT_RATE (SAMPLE_RATE * NUM_CHANNELS * SAMPLING_RATE / 8)

extern TinyWavHeader header;
extern TinyWav tw;

void create_file_on_sd(const char *filename);
void create_wave_file(const char *filename);
void create_test_files_on_sd(void);

#endif // FILE_HELPER_H