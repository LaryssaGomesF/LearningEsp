#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"


void app_main(void) {

  adc_oneshot_unit_handle_t adc1_handle;
  adc_oneshot_unit_init_cfg_t init_config1 = {
      .unit_id = ADC_UNIT_1,
      .ulp_mode = ADC_ULP_MODE_DISABLE,
  };
  ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));
  
}
