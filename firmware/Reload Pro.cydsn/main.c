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

#include <project.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "tasks.h"
#include "config.h"
#include "splashscreen.h"

state_t state;
xTaskHandle adc_task;
xTaskHandle comms_task;
xTaskHandle ui_task;

static const settings_t settings_data = {
	.dac_gains = {DEFAULT_DAC_LOW_GAIN, DEFAULT_DAC_HIGH_GAIN},
	.dac_offsets = {0, 0},
	.opamp_offset_trim = DEFAULT_OPAMP_OFFSET_TRIM,
	
	.adc_current_offset = DEFAULT_ADC_CURRENT_OFFSET,
	.adc_current_gain = DEFAULT_ADC_CURRENT_GAIN,
	
	.adc_voltage_offset = DEFAULT_ADC_VOLTAGE_OFFSET,
	.adc_voltage_gain = DEFAULT_ADC_VOLTAGE_GAIN,
	
	.backlight_brightness = 32,
	.lcd_contrast = 11,
};
const settings_t *settings;

void prvHardwareSetup();

void auto_calibrate() {
	IDAC_Start();
	IDAC_SetValue(255);
	IDAC_Mux_Start();
	Opamp_Mux_Start();
	
	ADC_Start();
	ADC_SetChanMask(1 << 3);
	
	IDAC_Mux_Select(0);
	Opamp_Mux_Select(0);
	ADC_StartConvert();
	ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
	ADC_StopConvert();
	int highGain = ADC_GetResult16(3);
	highGain /= 255;
	
	IDAC_Mux_Select(1);
	Opamp_Mux_Select(1);
	ADC_StartConvert();
	ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
	ADC_StopConvert();
	int lowGain = ADC_GetResult16(3);
	lowGain /= 255;	
}

void auto_calibrate_opamp() {
	IDAC_Start();
	IDAC_SetValue(255);
	Opamp_Start();
	IDAC_Mux_Start();
	Opamp_Mux_Start();
	Opamp_FB_Mux_Start();
	
	IDAC_Mux_Select(1);
	Opamp_Mux_Select(1);
	Opamp_FB_Mux_Select(1);
	
	ADC_Start();
	ADC_SetChanMask((1 << 3) | (1 << 4));
	
	for(int i = 0; i < 64; i++) {
		CY_SET_REG32(Opamp_cy_psoc4_abuf__OA_OFFSET_TRIM, i);
		ADC_StartConvert();
		ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
		ADC_StopConvert();
		int input = ADC_GetResult16(3);
		int output = ADC_GetResult16(4);
		int offset = input - output;
	}
}

void main()
{
	settings = &settings_data;
	
    CyGlobalIntEnable;

	Backlight_Write(1);
	
	disp_reset_Write(0);
	CyDelayUs(10);
	disp_reset_Write(1);
	CyDelayUs(10);
	Display_Start();
	Display_SetContrast(settings->lcd_contrast);
	
	#ifdef USE_SPLASHSCREEN
	load_splashscreen();
	#endif
	
	auto_calibrate_opamp();

	IDAC_Start();
	IDAC_Mux_Start();
	set_output_mode(OUTPUT_MODE_FEEDBACK);
	Opamp_Mux_Start();
	Opamp_FB_Mux_Start();
	Opamp_FB_Mux_Select(0);
		
	start_adc();

	setup();
	
	xTaskCreate(vTaskUI, (signed portCHAR *) "UI", 178, NULL, tskIDLE_PRIORITY + 2, &ui_task);
	xTaskCreate(vTaskComms, (signed portCHAR *) "UART", 141, NULL, tskIDLE_PRIORITY + 2, &comms_task);
	
	prvHardwareSetup();
	vTaskStartScheduler();
}

/* ---------------------------------------------------------------------------
 * FreeRTOS support and configuration functions
 * --------------------------------------------------------------------------- */

void prvHardwareSetup( void )
{
	/* Port layer functions that need to be copied into the vector table. */
	extern void xPortPendSVHandler( void );
	extern void xPortSysTickHandler( void );
	extern void vPortSVCHandler( void );
	extern cyisraddress CyRamVectors[];

	/* Install the OS Interrupt Handlers. */
	CyRamVectors[ 11 ] = ( cyisraddress ) vPortSVCHandler;
	CyRamVectors[ 14 ] = ( cyisraddress ) xPortPendSVHandler;
	CyRamVectors[ 15 ] = ( cyisraddress ) xPortSysTickHandler;
}

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	/* The stack space has been execeeded for a task, considering allocating more. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

void vApplicationMallocFailedHook( void )
{
	/* The heap space has been execeeded. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

/* [] END OF FILE */
