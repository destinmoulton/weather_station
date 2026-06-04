//
// Created by destin on 6/4/26.

#include "esp_rom_sys.h"
#include "driver/gpio.h"

/**
* Usage (non blocking):
xTaskCreate(
    [](void* arg) { pin_test_signal(gio_num_t(PIN), 1000); },
    "pin_test", 2048, NULL, 5, NULL
);
 */

void pin_test_signal(gpio_num_t pin, uint32_t freq_hz)
{
    // Configure the pin as a push-pull output
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);

    // Calculate half-period in microseconds
    uint32_t half_period_us = (1000000UL / freq_hz) / 2;

    while (true)
    {
        gpio_set_level(pin, 1);
        esp_rom_delay_us(half_period_us);
        gpio_set_level(pin, 0);
        esp_rom_delay_us(half_period_us);
    }
}
