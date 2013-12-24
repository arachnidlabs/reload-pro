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

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "project.h"
#include "tasks.h"
#include "config.h"

void vTaskComms(void *pvParameters) {
	portTickType lastWakeTime = xTaskGetTickCount();
	
	while(1) {
		char buf[40];

		sprintf(buf, "%d, %hd, %hd, %hd\r\n", state.current_setpoint, ADC_GetResult16(0), ADC_GetResult16(1), ADC_GetResult16(2));
		UART_UartPutString(buf);
				
		vTaskDelayUntil(&lastWakeTime, configTICK_RATE_HZ); // Once a second
	}		
}

/* [] END OF FILE */
