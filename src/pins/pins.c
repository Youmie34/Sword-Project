#include "pins.h"

volatile bool input = false;

void init_pins()
{
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(input_pin, GPIO_MODE_INPUT);
}

void check_input()
{
    if (gpio_get_level(input_pin) == 1)
    {
        // gpio_set_level(LED_PIN, 1);
        input = true;
    }
    else
    {
        // gpio_set_level(LED_PIN, 0);
        input = false;
    }
}