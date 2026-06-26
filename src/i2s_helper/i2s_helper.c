#include "i2s_helper.h"

static const char *TAG_I2S_HELPER = "i2s_helper";
static i2s_chan_handle_t i2s_rx_handle = NULL;

// Reconfigure for PDM (correct for INMP441!)
i2s_pdm_rx_config_t pdm_rx_cfg = {
    .clk_cfg = I2S_PDM_RX_CLK_DEFAULT_CONFIG(44100), // Or 48000
    .slot_cfg = I2S_PDM_RX_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
    .gpio_cfg = {
        .din = I2S_DIN_PIN,
        .clk = I2S_SCK_PIN,
        .invert_flags = {
            .clk_inv = true,
        }},
};

void i2s_init()
{
    // Create a new I2S RX channel
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);

    ESP_LOGI(TAG_I2S_HELPER, "Creating I2S channel...");
    if (ESP_OK != i2s_new_channel(&chan_cfg, NULL, &i2s_rx_handle))
    {
        ESP_LOGE(TAG_I2S_HELPER, "Failed to create I2S channel");
        return;
    }

    // Initialize with PDM mode configuration
    ESP_LOGI(TAG_I2S_HELPER, "Initializing I2S PDM mode...");
    if (ESP_OK != i2s_channel_init_pdm_rx_mode(i2s_rx_handle, &pdm_rx_cfg))
    {
        ESP_LOGE(TAG_I2S_HELPER, "Failed to initialize I2S PDM mode");
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

void input_data()
{
    // Static buffer for PDM mode (16-bit samples = 2 bytes per sample)
    static uint8_t i2s_read_buffer[I2S_DMA_BUF_LEN * 2];
    size_t bytes_read = 0;

    if (i2s_rx_handle == NULL)
    {
        ESP_LOGE(TAG_I2S_HELPER, "I2S RX channel not initialized");
        return;
    }
    // Read data from I2S using the new API
    esp_err_t result = i2s_channel_read(i2s_rx_handle, i2s_read_buffer, sizeof(i2s_read_buffer), &bytes_read, TIMEOUT_MS);

    if (result != ESP_OK)
    {
        ESP_LOGE(TAG_I2S_HELPER, "Failed to read data from I2S: %s", esp_err_to_name(result));
        return;
    }
    //  Process the read data as needed
    analyze_audio(i2s_read_buffer, bytes_read);
    // TODO: write data in file and save on sd card
}