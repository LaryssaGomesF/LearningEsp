#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/gpio.h"
#include "driver/gptimer.h"

#define GPIO_OUTPUT_IO_0  17
#define GPIO_OUTPUT_IO_1  18
#define GPIO_OUTPUT_IO_2  19

#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1) | (1ULL<<GPIO_OUTPUT_IO_2))



void app_main(void)
{

	int state = 0;
	unsigned long long init = 0;
	uint64_t count = 0;

	gpio_config_t leds = {
			.intr_type = GPIO_INTR_DISABLE,
			.pin_bit_mask = GPIO_OUTPUT_PIN_SEL,
			.mode = GPIO_MODE_OUTPUT,
			.pull_down_en = 0,
			.pull_up_en = 0
	};




	gpio_config(&leds);

	gptimer_handle_t gptimer = NULL;
	gptimer_config_t timer_config = {
			.clk_src = GPTIMER_CLK_SRC_DEFAULT,
			.direction = GPTIMER_COUNT_UP,
			.resolution_hz = 1 * 1000 * 1000// 1MHz, 1 tick = 1us
	};



	ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));

	ESP_ERROR_CHECK(gptimer_enable(gptimer));
	ESP_ERROR_CHECK(gptimer_start(gptimer));


	while(1){

		ESP_ERROR_CHECK(gptimer_get_raw_count(gptimer, &count));
		if(count == 500){
			state = !state;
			ESP_ERROR_CHECK(gptimer_set_raw_count(gptimer, init));
		}
		gpio_set_level(GPIO_OUTPUT_IO_0, state);
		gpio_set_level(GPIO_OUTPUT_IO_1, !state);
		gpio_set_level(GPIO_OUTPUT_IO_2, state);
	}

}
