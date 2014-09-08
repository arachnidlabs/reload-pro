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
#include <stdlib.h>
#include "project.h"
#include "tasks.h"
#include "config.h"
#include "commands.h"
#include "calibrate.h"

#define ARGUMENT_SEPERATORS " "

xQueueHandle comms_queue;
static char *current_line;

void UART_ISR_func() {
	static char lines[2][MAX_COMMS_LINE_LENGTH];
	static uint8 bufidx = 0;
	static uint8 lineidx = 0;
	
	uint32 nchars = UART_SpiUartGetRxBufferSize();
	for(int i = 0; i < (int)nchars; i++) {
		char c = UART_UartGetChar();
		switch(c) {
		case '\n':
		case '\r':
			if(bufidx > 0) {
				lines[lineidx][bufidx] = 0;
				if(xQueueSendToBackFromISR(comms_queue, &(comms_event){.type=COMMS_EVENT_LINE_RX}, NULL) == pdPASS) {
					current_line = lines[lineidx];
					lineidx = (lineidx + 1) % 2;
				}
				bufidx = 0;
			}
			break;
		case 0:
			break;
		default:
			lines[lineidx][bufidx++] = c;
			break;
		}
	}
	
	UART_ClearRxInterruptSource(UART_GetRxInterruptSourceMasked());
}

static portTickType tick_interval = portMAX_DELAY;

static void next_event(comms_event *event, portTickType interval) {
	static portTickType last_tick = 0;
	
	portTickType now = xTaskGetTickCount();
	if(now - last_tick > interval || !xQueueReceive(comms_queue, event, interval - (now - last_tick))) {
		last_tick = xTaskGetTickCount();
		event->type = COMMS_EVENT_MONITOR_DATA;
	}
}

void write_state_data() {
	char response[32];
	sprintf(response, "read %d %d\r\n", get_current_usage() / 1000, get_voltage() / 1000);
	UART_UartPutString(response);
}

void write_invalid_command(const char *cmdname) {
	char response[32];
	sprintf(response, "err Unknown command '%.7s'\r\n", cmdname);
	UART_UartPutString(response);
}

void command_mode(char *args) {
	UART_UartPutString("mode cc\r\n");
}

void command_set(char *args) {
	char response[32];
	
	char *newsetpoint = strsep(&args, ARGUMENT_SEPERATORS);
	if(newsetpoint[0] != 0) {
		set_current(atoi(newsetpoint) * 1000);
	}
	
	sprintf(response, "set %d\r\n", state.current_setpoint / 1000);
	UART_UartPutString(response);
}

void command_reset(char *args) {
	set_output_mode(OUTPUT_MODE_FEEDBACK);
	UART_UartPutString("ok\r\n");
}

void command_read(char *args) {
	write_state_data();
}

void command_monitor(char *args) {
	char *newinterval = strsep(&args, ARGUMENT_SEPERATORS);
	if(newinterval[0] == 0) {
		UART_UartPutString("err monitor expects at least one argument\r\n");
	} else {
		int interval = atoi(newinterval);
		if(interval == 0) {
			tick_interval = portMAX_DELAY;
		} else {
			tick_interval = (configTICK_RATE_HZ * interval) / 1000;
		}
	}
}

void command_debug(char *args) {
	char response[32];
	
	sprintf(response, "info ui stack %d\n", (int)uxTaskGetStackHighWaterMark(ui_task));
	UART_UartPutString(response);
 	sprintf(response, "info comms stack %d\n", (int)uxTaskGetStackHighWaterMark(comms_task));
	UART_UartPutString(response);
	sprintf(response, "info heap free %d\n", (int)xPortGetFreeHeapSize());
	UART_UartPutString(response);
	sprintf(response, "info fet %d %d\n", (int)ADC_GetResult16(ADC_CHAN_OPAMP_OUT), (int)ADC_GetResult16(ADC_CHAN_FET_IN));
	UART_UartPutString(response);
}

void command_calibrate(char *args) {
	char *subcommand = strsep(&args, ARGUMENT_SEPERATORS);
	if(subcommand[0] == '\0') {
		UART_UartPutString("err cal expects at least one argument\r\n");
		return;
	} else if(subcommand[1] != '\0') {
		UART_UartPutString("err cal: unrecognised subcommand\r\n");
		return;
	}
	
	settings_t new_settings;
	memcpy(&new_settings, settings, sizeof(settings_t));
	switch(subcommand[0]) {
	case 'o':  // Offset calibration
		calibrate_offsets(&new_settings);
		break;
	case 'v':  // ADC voltage calibration
		calibrate_voltage(&new_settings, atoi(args));
		break;
	case 'i':  // ADC current calibration
		calibrate_current(&new_settings, atoi(args));
		break;
	case 'd':  // DAC calibration
		calibrate_dacs(&new_settings, atoi(args));
		break;
	default:
		UART_UartPutString("err cal: unrecognised subcommand\r\n");
		return;
	}
	EEPROM_Write((uint8*)&new_settings, (uint8*)settings, sizeof(settings_t));
	UART_UartPutString("ok\r\n");
}

void command_bootloader(char *buf) {
    UART_UartPutString("ok\r\n");
    ui_event event;
    event.type = UI_EVENT_BOOTLOAD;
    xQueueSend(ui_queue, &event, 0);
}

void handle_command(char *buf) {
	char *cmdname = strsep(&buf, ARGUMENT_SEPERATORS);
	const command_def *cmd = in_word_set(cmdname, strlen(cmdname));
	
	if(cmd == NULL) {
		write_invalid_command(cmdname);
	} else {
		cmd->handler(buf);
	}
}

void vTaskComms(void *pvParameters) {
	comms_queue = xQueueCreate(1, sizeof(comms_event));

	UART_ISR_StartEx(UART_ISR_func);
	UART_Start();

	while(1) {
		comms_event event;
		
		next_event(&event, tick_interval);
		switch(event.type) {
		case COMMS_EVENT_MONITOR_DATA:
			write_state_data();
			break;
		case COMMS_EVENT_LINE_RX:
			handle_command(current_line);
			break;
		case COMMS_EVENT_OVERTEMP:
			UART_UartPutString("overtemp\r\n");
			break;
        case COMMS_EVENT_UNDERVOLT:
            UART_UartPutString("undervolt\r\n");
            break;
		}
	}		
}

/* [] END OF FILE */
