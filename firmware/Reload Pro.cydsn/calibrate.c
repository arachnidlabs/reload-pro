#include <FreeRTOS.h>
#include <task.h>
#include "calibrate.h"
#include "config.h"

void calibrate_offsets(settings_t *settings) {
	settings->adc_voltage_offset = get_raw_voltage();
	settings->adc_current_offset = get_raw_current_usage();
}

void calibrate_voltage(settings_t *settings, int microvolts) {
	settings->adc_voltage_gain = microvolts / get_raw_voltage();
}

void calibrate_current(settings_t *settings, int microamps) {
	settings->adc_current_gain = microamps / get_raw_current_usage();
}

void calibrate_dacs(settings_t *settings, int microamps) {
	int high_value = microamps / DEFAULT_DAC_HIGH_GAIN;
	IDAC_High_SetValue(high_value);
	IDAC_Low_SetValue(0);

	// Find the best setting for the opamp trim
	for(int i = 0; i < 32; i++) {
		CY_SET_REG32(Opamp_cy_psoc4_abuf__OA_OFFSET_TRIM, i);
		
		ADC_EnableInjection();
		ADC_IsEndConversion(ADC_WAIT_FOR_RESULT_INJ);
		int offset = ADC_GetResult16(ADC_CHAN_CURRENT_SENSE) - ADC_GetResult16(ADC_CHAN_CURRENT_SET);
		if(offset <= 0) {
			settings->opamp_offset_trim = i - 1;
			break;
		}
		vTaskDelay(configTICK_RATE_HZ / 100);
	}
	
	// Increase the per-sample contribution to the ADC averaging to speed things up for calibration
	adc_mix_ratio = 1; // 2 << 1 = 50% per sample means we need 100ms for 0.01% accuracy.

	// Calculate offset and gain for IDAC_High 
	vTaskDelay(configTICK_RATE_HZ / 10);
	int high_current = get_current_usage();

	int low_value = 100000 / DEFAULT_DAC_HIGH_GAIN; // Approx 100mA
	IDAC_High_SetValue(low_value);
	vTaskDelay(configTICK_RATE_HZ / 10);
	int low_current = get_current_usage();
	
	settings->dac_high_gain = (high_current - low_current) / (high_value - low_value);
	settings->dac_offset = high_current - high_value * settings->dac_high_gain;
	
	// Calculate gain for IDAC_Low
	IDAC_Low_SetValue(127);
	vTaskDelay(configTICK_RATE_HZ / 10);
	settings->dac_low_gain = (get_current_usage() - low_current) / 127;
	
	// Reset for 0 output
	set_current(0);
}
