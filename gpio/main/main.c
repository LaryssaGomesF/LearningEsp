#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


//OUTPUTS
#define GPIO_OUTPUT_IO_0   17
#define GPIO_OUTPUT_IO_1   18
#define GPIO_OUTPUT_IO_2   19
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1) | (1ULL<<GPIO_OUTPUT_IO_2))

//INPUTS
#define GPIO_INPUT_IO_0   23

void app_main(void)
{
	gpio_config_t leds = {
			.intr_type = GPIO_INTR_DISABLE,
			.mode = GPIO_MODE_OUTPUT,
			.pin_bit_mask = GPIO_OUTPUT_PIN_SEL,
			.pull_down_en = 0,
			.pull_up_en = 0,
	};

	gpio_config_t btn = {
			.intr_type = GPIO_INTR_DISABLE,
			.mode = GPIO_MODE_INPUT,
			.pin_bit_mask = GPIO_INPUT_IO_0,
			.pull_down_en = 0,
			.pull_up_en = 0,
	};


	gpio_config(&leds);
	gpio_config(&btn);

	while (1) {

		if(gpio_get_level(GPIO_INPUT_IO_0) == 1){
			gpio_set_level(GPIO_OUTPUT_IO_0, 0);
			gpio_set_level(GPIO_OUTPUT_IO_1, 1);
			gpio_set_level(GPIO_OUTPUT_IO_2, 0);

		}else{
			gpio_set_level(GPIO_OUTPUT_IO_0, 1);
			gpio_set_level(GPIO_OUTPUT_IO_1, 0);
			gpio_set_level(GPIO_OUTPUT_IO_2, 1);
		}

	}
}
