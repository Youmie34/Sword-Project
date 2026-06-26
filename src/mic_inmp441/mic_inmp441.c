#include "mic_inmp441.h"

static const char *TAG_MIC_INMP441 = "mic_inmp441";

void analyze_audio(uint8_t *buffer, size_t len_bytes)
{
    int32_t *samples = (int32_t *)buffer;
    size_t num_samples = len_bytes / sizeof(int32_t); // Z.B. 1024 Samples bei 4096 Bytes

    uint32_t sum_abs = 0;
    uint32_t max_val = 0;

    for (size_t i = 0; i < num_samples; i++)
    {
        int32_t val = samples[i];

        // Entferne die unteren 8 Bit (INMP441 liefert 24-bit linksbündig in 32-bit Register)
        val = (val >> 8) & 0xFFFFFF;

        // Betrag nehmen (Absolutwert für Pegelmessung)
        uint32_t abs_val = (val < 0) ? -val : val;

        sum_abs += abs_val;
        if (abs_val > max_val)
            max_val = abs_val;
    }

    float average_level = (float)sum_abs / num_samples;
    uint16_t peak_dbfs = (uint16_t)((max_val * 100.0f) / 32768.0f); // Prozentualer Spitzenpegel

    ESP_LOGI(TAG_MIC_INMP441, "Avg Level: %lu | Peak: %u%% | Samples: %d",
             (unsigned long)average_level, peak_dbfs, num_samples);
}