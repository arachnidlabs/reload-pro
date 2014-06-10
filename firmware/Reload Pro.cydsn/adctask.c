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
uint8 adc_mix_ratio = ADC_MIX_RATIO;

CY_ISR(ADC_ISR_func) {
	uint32 isr_flags = ADC_SAR_INTR_MASKED_REG;
	if(isr_flags & ADC_EOS_MASK) {
		total_current = total_current - (total_current >> adc_mix_ratio) + ADC_GetResult16(ADC_CHAN_CURRENT_SENSE);
		total_voltage = total_voltage - (total_voltage >> adc_mix_ratio) + ADC_GetResult16(ADC_CHAN_VOLTAGE_SENSE);
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

/* [] END OF FILE */
