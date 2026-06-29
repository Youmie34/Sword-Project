#include "mic_inmp441.h"

static const char *TAG_MIC_INMP441 = "mic_inmp441";

void record_wav(const char *filename)
{
    ESP_LOGI(TAG_MIC_INMP441, "recording wav");

    create_tinywave_file(filename);

    i2s_record_data();

    ESP_LOGI(TAG_MIC_INMP441, "File written on SDCard");
}

float apply_soft_limiter(float sample)
{
    float abs_s = fabsf(sample);
    if (abs_s > LIMIT_THRESHOLD)
    {
        // Gentle compression: square curve above the threshold
        float sign = (sample >= 0) ? 1.0f : -1.0f;
        float excess = abs_s - LIMIT_THRESHOLD;
        sample = sign * (LIMIT_THRESHOLD + excess * 0.3f);
        // Hard clipping at 0.95 to prevent distortion
        if (fabsf(sample) > 0.95f)
        {
            sample = sign * 0.95f;
        }
    }
    return sample;
}