#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define GPIO_LED 19 // port pin of on - board LED

void app_main()
{
    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT); // set GPIO as output

    while (1)
    {
        gpio_set_level(GPIO_LED, 0);           // set GPIO low , LED goes on
        vTaskDelay(1000 / portTICK_PERIOD_MS); // wait 100 ms
        gpio_set_level(GPIO_LED, 1);           // set GPIO high , LED goes off
        vTaskDelay(1000 / portTICK_PERIOD_MS); // wait 100 ms
    }
}