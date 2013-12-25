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
#include <stdlib.h>
#include <stdio.h>
#include "tasks.h"
#include "config.h"

state_t state;

volatile settings_t settings = {
	.dac_low_gain = DEFAULT_DAC_LOW_GAIN,
	.dac_high_gain = DEFAULT_DAC_HIGH_GAIN,
	.dac_offset = DEFAULT_DAC_OFFSET,
	.opamp_offset_trim = DEFAULT_OPAMP_OFFSET_TRIM,
	
	.adc_current_offset = DEFAULT_ADC_CURRENT_OFFSET,
	.adc_current_gain = DEFAULT_ADC_CURRENT_GAIN,
	
	.adc_voltage_offset = DEFAULT_ADC_VOLTAGE_OFFSET,
	.adc_voltage_gain = DEFAULT_ADC_VOLTAGE_GAIN,
};

void prvHardwareSetup();

CY_ISR(button_press_isr) {
	static ui_event event = {.type = UI_EVENT_BUTTONPRESS, .when = 0};
	event.int_arg = QuadButton_Read();
	QuadButton_ClearInterrupt();
	
	portTickType now = xTaskGetTickCountFromISR();
	if(now - event.when > configTICK_RATE_HZ / 10) {
		event.when = now;
		xQueueSendToBackFromISR(ui_queue, &event, NULL);
	}
}

// Maps current state (index) to next state for a forward transition.
const int8 quadrature_states[] = {0x1, 0x3, 0x0, 0x2};

CY_ISR(quadrature_event_isr) {
	static int8 last_levels = 3;
	static int8 count = 0;
	
	int levels = Quadrature_Read();
	Quadrature_ClearInterrupt();

	if(quadrature_states[last_levels] == levels) {
		count += 1;
		last_levels = levels;
	} else if(quadrature_states[levels] == last_levels) {
		count -= 1;
		last_levels = levels;
	}
	
	if(abs(count) >= 4) {
		ui_event event = {.type = UI_EVENT_UPDOWN, .when = xTaskGetTickCountFromISR(), .int_arg = count / 4};
		xQueueSendToBackFromISR(ui_queue, &event, NULL);
		count = count % 4;
	}
}

void main()
{
    CyGlobalIntEnable;
	
	backlight_Write(1);
	
	QuadratureISR_StartEx(quadrature_event_isr);
	QuadButtonISR_StartEx(button_press_isr);
	
	IDAC_Start();
	IDAC_Mux_Start();
	Opamp_Start();
	Opamp_Mux_Start();
	
	ADC_Start();
	ADC_StartConvert();
	UART_Start();
	
	disp_reset_Write(0);
	CyDelayUs(10);
	disp_reset_Write(1);
	CyDelayUs(10);
	Display_Start();
	
	setup();

	ui_queue = xQueueCreate(4, sizeof(ui_event));
	xTaskCreate(vTaskUI, (signed portCHAR *) "UI", configMINIMAL_STACK_SIZE + 60, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(vTaskComms, (signed portCHAR *) "UART", configMINIMAL_STACK_SIZE + 40, NULL, tskIDLE_PRIORITY + 1, NULL);
	//xTaskCreate(vTaskLCD, (signed portCHAR *) "LCD", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	
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
