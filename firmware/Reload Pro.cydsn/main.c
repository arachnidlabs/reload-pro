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
	.dac_low_gain = DEFAULT_DAC_LOW_GAIN,
	.dac_high_gain = DEFAULT_DAC_HIGH_GAIN,
	.dac_low_offset = 0,
	.dac_high_offset = 0,
	.opamp_offset_trim = DEFAULT_OPAMP_OFFSET_TRIM,
	
	.adc_current_offset = DEFAULT_ADC_CURRENT_OFFSET,
	.adc_current_gain = DEFAULT_ADC_CURRENT_GAIN,
	
	.adc_voltage_offset = DEFAULT_ADC_VOLTAGE_OFFSET,
	.adc_voltage_gain = DEFAULT_ADC_VOLTAGE_GAIN,
	
	.backlight_brightness = 32,
	.lcd_contrast = 32,
};
const settings_t *settings;

void prvHardwareSetup();

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
	

	IDAC_High_Start();
	IDAC_Low_Start();
	set_output_mode(OUTPUT_MODE_FEEDBACK);
		
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
