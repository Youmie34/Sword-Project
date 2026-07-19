#include <stdint.h>
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../ei_classifier_porting.h"

void ei_sleep(int ms) {
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

uint64_t ei_read_timer_us() {
    return esp_timer_get_time();
}

void ei_run_impulse_check_canceled() {
    // Optional: Add cancellation checks if needed
    // For now, do nothing (no cancellation)
}