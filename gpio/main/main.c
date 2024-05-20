#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define GPIO_OUTPUT_IO_0   18
#define GPIO_OUTPUT_IO_1   19
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))

void app_main(void)
{
	gpio_config_t led = {};


	led.intr_type = GPIO_INTR_DISABLE;
	led.mode = GPIO_MODE_OUTPUT;
	led.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
	led.pull_down_en = 0;
	led.pull_up_en = 0;

	gpio_config(&led);


    while (1) {
        gpio_set_level(GPIO_OUTPUT_IO_0, 1);
        gpio_set_level(GPIO_OUTPUT_IO_1, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_OUTPUT_IO_0,0);
        gpio_set_level(GPIO_OUTPUT_IO_1, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
