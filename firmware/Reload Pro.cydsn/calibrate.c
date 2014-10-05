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

void calibrate_opamp_offset_trim(settings_t *settings_t, int microamps) {
    state.calibrating = 1;
	int high_value = microamps / DEFAULT_DAC_HIGH_GAIN;
	int low_value = 100000 / DEFAULT_DAC_HIGH_GAIN; // Approx 100mA
    int high_current, low_current;

    IDAC_Low_SetValue(0);

	// Find the best setting for the opamp trim
    int min_offset = -(1 << 30);
    int min_offset_idx = 0;
	for(int i = 0; i < 32; i++) {
		CY_SET_REG32(Opamp_cy_psoc4_abuf__OA_OFFSET_TRIM, i);
		
        IDAC_High_SetValue(high_value);
        vTaskDelay(configTICK_RATE_HZ / 2);
        high_current = get_current_usage();

        IDAC_High_SetValue(low_value);
        vTaskDelay(configTICK_RATE_HZ / 2);
        low_current = get_current_usage();

        int offset = (high_value * low_current - low_value * high_current) / (high_value - low_value);
		if(offset <= 0 && offset > min_offset) {
            min_offset = offset;
            min_offset_idx = i;
		}
	}
    set_opamp_offset_trim(settings, min_offset_idx);
    
	set_current(0);
    state.calibrating = 0;
}

void calibrate_dacs(settings_t *settings, int microamps) {
    state.calibrating = 1;
	int high_value = microamps / DEFAULT_DAC_HIGH_GAIN;
	int low_value = 100000 / DEFAULT_DAC_HIGH_GAIN; // Approx 100mA
    int high_current, low_current;

    IDAC_Low_SetValue(0);

	// Calculate offset and gain for IDAC_High 
    IDAC_High_SetValue(high_value);
	vTaskDelay(configTICK_RATE_HZ);
	high_current = get_current_usage();

	IDAC_High_SetValue(low_value);
	vTaskDelay(configTICK_RATE_HZ);
	low_current = get_current_usage();
	
	settings->dac_high_gain = (high_current - low_current) / (high_value - low_value);
	settings->dac_offset = high_current - high_value * settings->dac_high_gain;
	
	// Calculate gain for IDAC_Low
	IDAC_Low_SetValue(127);
	vTaskDelay(configTICK_RATE_HZ * 2);
	settings->dac_low_gain = (get_current_usage() - low_current) / 127;
	
	// Reset for 0 output
	set_current(0);
    state.calibrating = 0;
}

void set_opamp_offset_trim(settings_t *settings, int trim) {
	settings->opamp_offset_trim = trim;
	CY_SET_REG32(Opamp_cy_psoc4_abuf__OA_OFFSET_TRIM, settings->opamp_offset_trim);
}
