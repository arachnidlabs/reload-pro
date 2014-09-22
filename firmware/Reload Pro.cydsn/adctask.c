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
static int dac_offset_correction = 0;
static portTickType last_update = 0;
static uint8 conversion_counter = 0;

uint8 adc_mix_ratio = ADC_MIX_RATIO;

#define TICK_RATE_HR (3600 * configTICK_RATE_HZ);

CY_ISR(ADC_ISR_func) {
	uint32 isr_flags = ADC_SAR_INTR_MASKED_REG;
	if(isr_flags & ADC_EOS_MASK) {
        if(conversion_counter < 100) {
            // Regular ADC
    		// Update IIR values for current and voltage
    		total_current = total_current - (total_current >> adc_mix_ratio) + ADC_GetResult16(ADC_CHAN_CURRENT_SENSE);
    		total_voltage = total_voltage - (total_voltage >> adc_mix_ratio) + ADC_GetResult16(ADC_CHAN_VOLTAGE_SENSE);
    		
#ifdef DAC_EC_FEEDBACK
            if(!state.calibrating) {
                int error = get_current_usage() - get_current_setpoint();
                dac_offset_correction += error >> DAC_EC_MIX_RATIO;
                if(dac_offset_correction > MAX_DAC_EC) {
                    dac_offset_correction = MAX_DAC_EC;
                } else if(dac_offset_correction < -MAX_DAC_EC) {
                    dac_offset_correction = -MAX_DAC_EC;
                }
                set_current(state.current_setpoint);
            }
#endif
      
            // Update running totals of microamp-ticks and microwatt-ticks
    		portTickType now = xTaskGetTickCount();
            if(now > last_update) {
        		int current = get_current_usage();
                int voltage = get_voltage();

        		remainder_microamp_ticks += current * (now - last_update);
        		total_microamp_hours += remainder_microamp_ticks / TICK_RATE_HR;
        		remainder_microamp_ticks %= TICK_RATE_HR;
        		
        		remainder_microwatt_ticks += (current / 1000) * (voltage / 1000) * (now - last_update);
        		total_microwatt_hours += remainder_microwatt_ticks / TICK_RATE_HR;
        		remainder_microwatt_ticks %= TICK_RATE_HR;

                last_update = now;
            }

            if(conversion_counter == 99) {
                // Switch to measuring FET current draw for overtemp; skip next conversion as inaccurate
                ADC_SetChanMask((1 << ADC_CHAN_OPAMP_OUT) | (1 << ADC_CHAN_FET_IN));
                ADC_SAR_CTRL_REG = (ADC_SAR_CTRL_REG & ~ADC_VREF_INTERNAL1024BYPASSED) | ADC_VREF_VDDA;
            }
        } else if(conversion_counter == 101) {
            if(get_output_mode() == OUTPUT_MODE_FEEDBACK) {
                // Undervolt detection.
                if(state.lower_voltage_limit != -1 && get_current_setpoint() > 0 && get_voltage() < state.lower_voltage_limit) {
                    set_output_mode(OUTPUT_MODE_OFF);
                    set_current(0);
        			xQueueSendToBackFromISR(ui_queue, &((ui_event){
        				.type=UI_EVENT_LIMIT,
        				.int_arg=LIMIT_TYPE_UNDERVOLT,
        				.when=xTaskGetTickCountFromISR()
        			}), NULL);
        			xQueueOverwriteFromISR(comms_queue, &((comms_event){
        				.type=COMMS_EVENT_UNDERVOLT,
        			}), NULL);
                }
                
        		// Overtemp detection.
                int16 opamp_out = ADC_GetResult16(ADC_CHAN_OPAMP_OUT);
                int16 fet_in = ADC_GetResult16(ADC_CHAN_FET_IN);
        		if(abs(opamp_out - fet_in) > 4) {
        			set_output_mode(OUTPUT_MODE_OFF);
                    set_current(0);

        			xQueueSendToBackFromISR(ui_queue, &((ui_event){
        				.type=UI_EVENT_LIMIT,
        				.int_arg=LIMIT_TYPE_OVERTEMP,
        				.when=xTaskGetTickCountFromISR()
        			}), NULL);
        			xQueueOverwriteFromISR(comms_queue, &((comms_event){
        				.type=COMMS_EVENT_OVERTEMP,
        			}), NULL);
        		}
            }
            ADC_SetChanMask((1 << ADC_CHAN_CURRENT_SENSE) | (1 << ADC_CHAN_VOLTAGE_SENSE) | (1 << ADC_CHAN_TEMP) | (1 << ADC_CHAN_CURRENT_SET));
            ADC_SAR_CTRL_REG = (ADC_SAR_CTRL_REG & ~ADC_VREF_VDDA) | ADC_VREF_INTERNAL1024BYPASSED;
        } else if(conversion_counter == 102) {
            // Switch back to regular measurement; discard reading as inaccurate
            conversion_counter = 0;
        }
        conversion_counter++;
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

int get_dac_offset_correction() {
    return dac_offset_correction;
}

void reset_running_totals() {
	total_microamp_hours = 0;
	total_microwatt_hours = 0;
}

/* [] END OF FILE */
