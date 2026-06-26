#include "i2s_helper.h"

static const char *TAG_I2S_HELPER = "i2s_helper";
static i2s_chan_handle_t i2s_rx_handle = NULL;
static i2s_chan_handle_t i2s_tx_handle = NULL;

// i2s_config_t i2s_config = {
//     .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
//     .sample_rate = I2S_SAMPLE_RATE,
//     .bits_per_sample = I2S_BIT_DEPTH,
//     .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // Ground the L/R pin on the INMP441.
//     .communication_format = I2S_COMM_FORMAT_I2S,
//     .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
//     .dma_buf_count = I2S_DMA_BUF_COUNT,
//     .dma_buf_len = I2S_DMA_BUF_LEN,
//     .use_apll = false,
//     .tx_desc_auto_clear = false,
//     .fixed_mclk = 0,
// };

// i2s_pin_config_t pin_config = {
//     .mck_io_num = I2S_PIN_NO_CHANGE,
//     .bck_io_num = I2S_SCK_PIN,
//     .ws_io_num = I2S_WS_PIN,
//     .data_out_num = I2S_PIN_NO_CHANGE,
//     .data_in_num = I2S_DIN_PIN,
// };

i2s_std_config_t i2s_config = {
    .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(I2S_SAMPLE_RATE),
    .slot_cfg = I2S_STD_MSB_SLOT_DEFAULT_CONFIG(I2S_BIT_DEPTH, I2S_SLOT_MODE_MONO),
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
    // Create a new I2S RX channel
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    if (ESP_OK != i2s_new_channel(&chan_cfg, &i2s_tx_handle, &i2s_rx_handle))
    {
        ESP_LOGE(TAG_I2S_HELPER, "Failed to create I2S RX channel");
        return;
    }

    // Enable the I2S RX channel
    if (ESP_OK != i2s_channel_enable(i2s_rx_handle))
    {
        ESP_LOGE(TAG_I2S_HELPER, "Failed to enable I2S RX channel");
        return;
    }

    ESP_LOGI(TAG_I2S_HELPER, "I2S RX channel initialized successfully");
}

void input_data()
{
    size_t bytes_read = 0;
    uint8_t i2s_read_buffer[I2S_DMA_BUF_LEN * 4]; // Buffer to hold the read data

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

    ESP_LOGI(TAG_I2S_HELPER, "Read %d bytes from I2S", bytes_read);
    // Process the read data as needed
    // TODO: write data in file and save on sd card
}