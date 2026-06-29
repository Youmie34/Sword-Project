#include "i2s_helper.h"

static const char *TAG_I2S_HELPER = "i2s_helper";
static i2s_chan_handle_t i2s_rx_handle = NULL;

i2s_std_config_t i2s_config = {
    .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(I2S_SAMPLE_RATE),
    .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(
        I2S_DATA_BIT_WIDTH_32BIT,
        I2S_SLOT_MODE_MONO),
    .gpio_cfg = {
        .mclk = NC,
        .bclk = I2S_SCK_PIN,
        .ws = I2S_WS_PIN,
        .dout = NC,
        .din = I2S_DIN_PIN,
        .invert_flags = {
            .mclk_inv = 0,
            .bclk_inv = 0,
            .ws_inv = 0}}};

void i2s_init()
{
    i2s_config.slot_cfg.slot_mask = I2S_STD_SLOT_LEFT; // Only use left channel for mono

    // Create a new I2S RX channel
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);

    ESP_LOGI(TAG_I2S_HELPER, "Creating I2S channel...");
    if (ESP_OK != i2s_new_channel(&chan_cfg, NULL, &i2s_rx_handle))
    {
        ESP_LOGE(TAG_I2S_HELPER, "Failed to create I2S channel");
        return;
    }

    // Initialize with std mode configuration
    ESP_LOGI(TAG_I2S_HELPER, "Initializing I2S std mode...");
    if (ESP_OK != i2s_channel_init_std_mode(i2s_rx_handle, &i2s_config))
    {
        ESP_LOGE(TAG_I2S_HELPER, "Failed to initialize I2S std mode");
        return;
    }

    // Enable the I2S RX channel
    ESP_LOGI(TAG_I2S_HELPER, "Enabling I2S channel...");
    if (ESP_OK != i2s_channel_enable(i2s_rx_handle))
    {
        ESP_LOGE(TAG_I2S_HELPER, "Failed to enable I2S channel");
        return;
    }

    ESP_LOGI(TAG_I2S_HELPER, "I2S RX channel initialized successfully");
}

void i2s_deinit()
{
    if (ESP_OK != i2s_channel_disable(i2s_rx_handle))
    {
        ESP_LOGE(TAG_I2S_HELPER, "Failed to disable I2S channel");
        return;
    }

    if (ESP_OK != i2s_del_channel(i2s_rx_handle))
    {
        ESP_LOGE(TAG_I2S_HELPER, "Failed to delete I2S channel");
        return;
    }
}

void i2s_record_data()
{

    ESP_LOGI(TAG_I2S_HELPER, "Starting recording");
    int flash_wr_size = 0;

    uint32_t flash_rec_time = BIT_RATE * RECORD_TIME;

    size_t bytes_read = 0;
    static uint8_t i2s_readraw_buff[I2S_DMA_BUF_LEN * 2];           // Buffer for raw I2S data
    static float float_buff[I2S_DMA_BUF_LEN * 2 / sizeof(int32_t)]; // Buffer for float samples

    while (flash_wr_size < flash_rec_time)
    {
        // Read the RAW samples from the microphone
        if (i2s_channel_read(i2s_rx_handle, (char *)i2s_readraw_buff, sizeof(i2s_readraw_buff), &bytes_read, 1000) == ESP_OK)
        {
            // // int32 I2S → float32 [-1.0, 1.0]
            int num_samples = bytes_read / sizeof(int32_t);

            for (int i = 0; i < num_samples; i++)
            {
                int32_t raw = ((int32_t *)i2s_readraw_buff)[i];

                float sample = (float)raw / 8388608.0f; // 24 bit
                sample = apply_soft_limiter(sample);
                float_buff[i] = sample;
            }
            // tinywav konvertiert float32 → int16 (wegen TW_INT16) automatisch
            tinywav_write_f(&tw, float_buff, num_samples);
            flash_wr_size += num_samples * sizeof(int16_t); // int16 im File!
        }
        else
        {
            ESP_LOGE(TAG_I2S_HELPER, "Failed to read data from I2S channel");
            break;
        }
    }

    tinywav_close_write(&tw);
    ESP_LOGI(TAG_I2S_HELPER, "Recording done!");
}