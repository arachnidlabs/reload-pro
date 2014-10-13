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
#include <task.h>

extern xTaskHandle comms_task;
extern xTaskHandle ui_task;

extern xQueueHandle ui_queue;
extern xQueueHandle comms_queue;

typedef enum {
	UI_EVENT_NONE,
	UI_EVENT_BUTTONPRESS,
	UI_EVENT_UPDOWN,
	UI_EVENT_TICK,
	UI_EVENT_LIMIT,
    UI_EVENT_BOOTLOAD,
} ui_event_type;

typedef enum {
    LIMIT_TYPE_OVERTEMP,
    LIMIT_TYPE_UNDERVOLT,
} limit_type;

typedef struct {
	ui_event_type type;
	int int_arg;
    portTickType duration;
	portTickType when;
} ui_event;

#define MAX_COMMS_LINE_LENGTH 40

typedef enum {
	COMMS_EVENT_LINE_RX,
	COMMS_EVENT_MONITOR_DATA,
	COMMS_EVENT_OVERTEMP,
    COMMS_EVENT_UNDERVOLT,
} comms_event_type;

typedef struct {
	comms_event_type type;
} comms_event;


void vTaskUI(void *pvParameters);
void vTaskComms(void *pvParameters);
void start_adc();

/* [] END OF FILE */
