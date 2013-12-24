/* ========================================
 *
 * Copyright Arachnid Labs, 2013
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <FreeRTOS.h>
#include <queue.h>

extern xQueueHandle ui_queue;

typedef enum {
	UI_EVENT_BUTTONPRESS,
	UI_EVENT_UPDOWN,
} ui_event_type;

typedef struct {
	ui_event_type type;
	int int_arg;
	portTickType when;
} ui_event;

void vTaskUI(void *pvParameters);
void vTaskComms(void *pvParameters);
void vTaskLCD(void *pvParameters);

/* [] END OF FILE */
