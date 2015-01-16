#include <FreeRTOS.h>
#include <task.h>
#include "calibrate.h"
#include "config.h"

void calibrate_offsets(settings_t *newsettings) {
	newsettings->calibration_settings.adc_voltage_offset = get_raw_voltage();
	newsettings->calibration_settings.adc_current_offset = get_raw_current_usage();
}

void calibrate_voltage(settings_t *newsettings, int microvolts) {
	newsettings->calibration_settings.adc_voltage_gain = microvolts / (get_raw_voltage() - newsettings->calibration_settings.adc_voltage_offset) ;
}

void calibrate_current(settings_t *newsettings, int microamps) {
	newsettings->calibration_settings.adc_current_gain = microamps / (get_raw_current_usage() - newsettings->calibration_settings.adc_current_offset);
}

void calibrate_opamp_offset_trim(settings_t *newsettings, int microamps, progress_callback_t progress_callback) {
    state.calibrating = 1;
	int high_value = microamps / DEFAULT_DAC_HIGH_GAIN;
	int low_value = 100000 / DEFAULT_DAC_HIGH_GAIN; // Approx 100mA
    int high_current, low_current;
    IDAC_Low_SetValue(0);

	// Find the best setting for the opamp trim
    int min_offset = INT_MIN;
    int min_offset_idx = 0;
    
	for(int i = 0; i < MAX_OA_OFFSET_STEPS; i++) {
        progress_callback(i+1,MAX_OA_OFFSET_STEPS);
		CY_SET_REG32(Opamp_cy_psoc4_abuf__OA_OFFSET_TRIM, i);
		
        IDAC_High_SetValue(high_value);
        vTaskDelay(configTICK_RATE_HZ);
        high_current = get_raw_current_usage() - newsettings->calibration_settings.adc_current_offset;

        IDAC_High_SetValue(low_value);
        vTaskDelay(configTICK_RATE_HZ);
        low_current = get_raw_current_usage() - newsettings->calibration_settings.adc_current_offset;

        int offset = (high_value * low_current - low_value * high_current) / (high_value - low_value);
		if(offset <= 0 && offset > min_offset) {
            min_offset = offset;
            min_offset_idx = i;
		}
	}
    set_opamp_offset_trim(newsettings, min_offset_idx);

	set_current(0);
    state.calibrating = 0;
}

void calibrate_dacs(settings_t *newsettings, int microamps) {
    state.calibrating = 1;
	int high_value = microamps / DEFAULT_DAC_HIGH_GAIN;
	int low_value = 100000 / DEFAULT_DAC_HIGH_GAIN; // Approx 100mA
    int high_current, low_current;

    IDAC_Low_SetValue(0);

	// Calculate offset and gain for IDAC_High 
    IDAC_High_SetValue(high_value);
	vTaskDelay(configTICK_RATE_HZ * 2);
	high_current = (get_raw_current_usage() - newsettings->calibration_settings.adc_current_offset) * settings->calibration_settings.adc_current_gain;

	IDAC_High_SetValue(low_value);
	vTaskDelay(configTICK_RATE_HZ * 2);
	low_current = (get_raw_current_usage() - newsettings->calibration_settings.adc_current_offset) * settings->calibration_settings.adc_current_gain;
	
	newsettings->calibration_settings.dac_high_gain = (high_current - low_current) / (high_value - low_value);
	newsettings->calibration_settings.dac_offset = high_current - high_value * newsettings->calibration_settings.dac_high_gain;
	
	// Calculate gain for IDAC_Low
	IDAC_Low_SetValue(127);
	vTaskDelay(configTICK_RATE_HZ * 4);
	newsettings->calibration_settings.dac_low_gain = ((get_raw_current_usage() - newsettings->calibration_settings.adc_current_offset) * settings->calibration_settings.adc_current_gain - low_current) / 127;
	
	// Reset for 0 output
	set_current(0);
    state.calibrating = 0;
}

void set_opamp_offset_trim(settings_t *newsettings, int trim) {
	newsettings->calibration_settings.opamp_offset_trim = trim;
	CY_SET_REG32(Opamp_cy_psoc4_abuf__OA_OFFSET_TRIM, newsettings->calibration_settings.opamp_offset_trim);
}
