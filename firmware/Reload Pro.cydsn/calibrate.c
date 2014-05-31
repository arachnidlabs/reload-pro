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
	
}
