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
#include "project.h"
#include <FreeRTOS.h>
#include <task.h>
#include <stdlib.h>
#include "tasks.h"
#include "config.h"

static int total_voltage = 0;
static int total_current = 0;
static int total_microwatt_hours = 0;
static int remainder_microwatt_ticks = 0;
static int total_microamp_hours = 0;
static int remainder_microamp_ticks = 0;
static portTickType last_update = 0;

uint8 adc_mix_ratio = ADC_MIX_RATIO;

#define TICK_RATE_HR (3600 * configTICK_RATE_HZ);

CY_ISR(ADC_ISR_func) {
	uint32 isr_flags = ADC_SAR_INTR_MASKED_REG;
	if(isr_flags & ADC_EOS_MASK) {
		// Update IIR values for current and voltage
		total_current = total_current - (total_current >> adc_mix_ratio) + ADC_GetResult16(ADC_CHAN_CURRENT_SENSE);
		total_voltage = total_voltage - (total_voltage >> adc_mix_ratio) + ADC_GetResult16(ADC_CHAN_VOLTAGE_SENSE);
		
		// Update running totals of microamp-ticks and microwatt-ticks
		portTickType now = xTaskGetTickCount();
		int current = get_current_usage();

		remainder_microamp_ticks += current * (now - last_update);
		total_microamp_hours += remainder_microamp_ticks / TICK_RATE_HR;
		remainder_microamp_ticks %= TICK_RATE_HR;
		
		remainder_microwatt_ticks += current * get_voltage() * (now - last_update);
		total_microwatt_hours += remainder_microwatt_ticks / TICK_RATE_HR;
		remainder_microwatt_ticks %= TICK_RATE_HR;

		last_update = now;
		
		// Overtemp detection. TODO: Fix this for ADC range issues.
		if(abs(ADC_GetResult16(ADC_CHAN_OPAMP_OUT) - ADC_GetResult16(ADC_CHAN_FET_IN)) > 10) {
			set_output_mode(OUTPUT_MODE_OFF);

			xQueueSendToBackFromISR(ui_queue, &((ui_event){
				.type=UI_EVENT_OVERTEMP,
				.int_arg=0,
				.when=xTaskGetTickCountFromISR()
			}), NULL);
			xQueueOverwriteFromISR(comms_queue, &((comms_event){
				.type=COMMS_EVENT_OVERTEMP,
			}), NULL);
		}
	}
	ADC_SAR_INTR_REG = isr_flags;
}

void start_adc() {
	ADC_Start();
	//ADC_SAR_INTR_MASK_REG = ADC_EOS_MASK;
	ADC_IRQ_StartEx(ADC_ISR_func);
	ADC_StartConvert();
}

int16 get_raw_current_usage() {
	return total_current >> adc_mix_ratio;
}

int get_current_usage() {
	int ret = ((total_current >> adc_mix_ratio) - settings->adc_current_offset) * settings->adc_current_gain;
	return (ret < 0)?0:ret;
}

int16 get_raw_voltage() {
	return total_voltage >> adc_mix_ratio;
}

int get_voltage() {
	int ret = ((total_voltage >> adc_mix_ratio) - settings->adc_voltage_offset) * settings->adc_voltage_gain;
	return (ret < 0)?0:ret;
}

int get_microamp_hours() {
	return total_microamp_hours;
}

int get_microwatt_hours() {
	return total_microwatt_hours;
}

void reset_running_totals() {
	total_microamp_hours = 0;
	total_microwatt_hours = 0;
}

/* [] END OF FILE */
