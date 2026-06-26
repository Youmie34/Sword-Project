#include "mic_inmp441.h"

static const char *TAG_MIC_INMP441 = "mic_inmp441";

void analyze_audio(uint8_t *buffer, size_t len_bytes)
{
    int16_t *samples = (int16_t *)buffer;

    ESP_LOGI(TAG_MIC_INMP441, "Raw sample[0]: %d | sample[1]: %d | sample[2]: %d",
             samples[0], samples[1], samples[2]);

    size_t num_samples = len_bytes / sizeof(int16_t);

    if (num_samples == 0)
    {
        ESP_LOGE(TAG_MIC_INMP441, "No samples to analyze");
        return;
    }

    // STEP 1: Calculate DC offset (average baseline) FIRST
    int32_t sum_dc = 0;
    for (size_t i = 0; i < num_samples; i++)
    {
        sum_dc += samples[i];
    }
    int16_t dc_offset = (int16_t)(sum_dc / num_samples);

    // STEP 2: Now analyze WITH offset removed
    uint32_t sum_ac = 0; // AC component (actual audio energy)
    int16_t max_val = INT16_MIN;
    int16_t min_val = INT16_MAX;

    for (size_t i = 0; i < num_samples; i++)
    {
        int16_t ac_sample = samples[i] - dc_offset; // Remove DC first!

        uint16_t abs_val = (ac_sample < 0) ? -ac_sample : ac_sample;
        sum_ac += abs_val;

        if (ac_sample > max_val)
            max_val = ac_sample;
        if (ac_sample < min_val)
            min_val = ac_sample;
    }

    // STEP 3: Calculate meaningful metrics
    float avg_level = (float)sum_ac / num_samples;
    int16_t peak_abs = (max_val > -min_val) ? max_val : -min_val;
    float peak_percent = ((float)peak_abs / 32768.0f) * 100.0f;

    ESP_LOGI(TAG_MIC_INMP441, "Avg: %.0f | Peak: %.1f%% | DC Off: %d | Min:%d Max:%d",
             avg_level, peak_percent, dc_offset, min_val, max_val);
}