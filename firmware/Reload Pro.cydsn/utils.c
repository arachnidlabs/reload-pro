/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "config.h"

void setup() {
	state.current_setpoint = -1;
	state.current_range = -1;
	set_current(0);
	
	(*(reg32 *)Opamp_cy_psoc4_abuf__OA_OFFSET_TRIM) = 14;
}

void set_current_range(int range) {
	if(state.current_range != range) {
		IDAC_Mux_Select(range);
		Opamp_Mux_Select(range);
		state.current_range = range;
	}
}

void set_current(int setpoint) {
	if(setpoint < 0) {
		setpoint = 0;
	} else if(setpoint > CURRENT_MAX) {
		setpoint = CURRENT_MAX;
	}
	
	if(setpoint < CURRENT_LOWRANGE_THRESHOLD) {
		set_current_range(0);
		IDAC_SetValue((setpoint + settings.dac_offset) / settings.dac_low_gain);
	} else {
		IDAC_SetValue((setpoint + settings.dac_offset) / settings.dac_high_gain);
		set_current_range(1);
	}
	state.current_setpoint = setpoint;
}

int get_current_setpoint() {
	return state.current_setpoint;
}

int get_current_usage() {
	int ret = (ADC_GetResult16(0) + settings.adc_current_offset) * settings.adc_current_gain;
	if(ret < 0)
		ret = 0;
	return ret;
}

int get_voltage() {
	int ret = (ADC_GetResult16(1) + settings.adc_voltage_offset) * settings.adc_voltage_gain;
	if(ret < 0)
		ret = 0;
	return ret;
}

/* [] END OF FILE */
