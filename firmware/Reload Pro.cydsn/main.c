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

static const settings_t settings_data = {
	.dac_gains = {DEFAULT_DAC_LOW_GAIN, DEFAULT_DAC_HIGH_GAIN},
	.dac_offsets = {0, 0},
	.opamp_offset_trim = DEFAULT_OPAMP_OFFSET_TRIM,
	
	.adc_current_offset = DEFAULT_ADC_CURRENT_OFFSET,
	.adc_current_gain = DEFAULT_ADC_CURRENT_GAIN,
	
	.adc_voltage_offset = DEFAULT_ADC_VOLTAGE_OFFSET,
	.adc_voltage_gain = DEFAULT_ADC_VOLTAGE_GAIN,
};
const settings_t *settings;

void prvHardwareSetup();

void main()
{
	settings = &settings_data;
	
    CyGlobalIntEnable;
	
	backlight_Write(1);
			
	disp_reset_Write(0);
	CyDelayUs(10);
	disp_reset_Write(1);
	CyDelayUs(10);
	Display_Start();
	
	#ifdef USE_SPLASHSCREEN
	load_splashscreen();
	#endif
	
	IDAC_Start();
	IDAC_Mux_Start();
	Opamp_Start();
	Opamp_Mux_Start();

	setup();
	
	ui_queue = xQueueCreate(4, sizeof(ui_event));
	xTaskCreate(vTaskUI, (signed portCHAR *) "UI", configMINIMAL_STACK_SIZE + 100, NULL, tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(vTaskComms, (signed portCHAR *) "UART", configMINIMAL_STACK_SIZE + 40, NULL, tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(vTaskADC, (signed portCHAR *) "ADC", configMINIMAL_STACK_SIZE + 40, NULL, tskIDLE_PRIORITY + 1, NULL);
	
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
