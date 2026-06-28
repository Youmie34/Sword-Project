#include "i2s_helper.h"

static const char *TAG_I2S_HELPER = "i2s_helper";
static i2s_chan_handle_t i2s_rx_handle = NULL;

void i2s_init()
{
    // Create a new I2S RX channel
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);

    ESP_LOGI(TAG_I2S_HELPER, "Creating I2S channel...");
    if (ESP_OK != i2s_new_channel(&chan_cfg, NULL, &i2s_rx_handle))
    {
        ESP_LOGE(TAG_I2S_HELPER, "Failed to create I2S channel");
        return;
    }

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

void i2s_record_data(FILE *file)
{

    ESP_LOGI(TAG_I2S_HELPER, "Starting recording");
    int flash_wr_size = 0;

    uint32_t flash_rec_time = BIT_RATE * RECORD_TIME;

    size_t bytes_read = 0;
    static uint8_t i2s_readraw_buff[I2S_DMA_BUF_LEN * 2]; // Buffer for raw I2S data

    while (flash_wr_size < flash_rec_time)
    {
        // Read the RAW samples from the microphone
        if (i2s_channel_read(i2s_rx_handle, (char *)i2s_readraw_buff, sizeof(i2s_readraw_buff), &bytes_read, 1000) == ESP_OK)
        {
            // Write the samples to the WAV file
            fwrite(i2s_readraw_buff, bytes_read, 1, file);
            flash_wr_size += bytes_read;
        }
        else
        {
            ESP_LOGE(TAG_I2S_HELPER, "Failed to read data from I2S channel");
            break;
        }
    }
    fclose(file);
    ESP_LOGI(TAG_I2S_HELPER, "Recording done!");
}