- ble cpnnectivity
- is2 connectivity/ inmp441 support
- collect training datafor edge impulse
- sleep mode
- // i2s_config_t i2s_config = {
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