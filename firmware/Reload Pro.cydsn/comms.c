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
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "project.h"
#include "tasks.h"
#include "config.h"
#include "commands.h"
#include "calibrate.h"
#include "semphr.h"
#include "comms.h"

#define ARGUMENT_SEPERATORS " "

xQueueHandle comms_queue;

// mutex to guard uart_printf, so that it can be used from both GUI and comms task
xSemaphoreHandle uart_write_mutex = NULL;

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

void uart_printf(char *fmt, ...) {
    static char formatted_string[MAX_RESPONSE_LENGTH + 1];

    if(uart_write_mutex != NULL) {
        
        // since INCLUDE_vTaskSuspend is set to 1, this will block until mutex is available
        xSemaphoreTake(uart_write_mutex, portMAX_DELAY);
            
        va_list argptr;
        va_start(argptr, fmt);
        vsnprintf(formatted_string, sizeof(formatted_string), fmt, argptr);
        va_end(argptr);
        UART_UartPutString(formatted_string);
        
        // release the krak^H^H^H^Hmutex!
        xSemaphoreGive(uart_write_mutex);
    }
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
	uart_printf("read %d %d\r\n", get_current_usage() / 1000, get_voltage() / 1000);
}

void write_invalid_command(const char *cmdname) {
	uart_printf("err Unknown command '%.7s'\r\n", cmdname);
}

void command_mode(char *args) {
	uart_printf("mode cc\r\n");
}

void command_set(char *args) {
	char *arg = strsep(&args, ARGUMENT_SEPERATORS);
	if(arg[0] != 0) {
        int newcurrent = atoi(arg);
        if(newcurrent < 0 || newcurrent * 1000 > CURRENT_MAX) {
            uart_printf("err set current must be between 0 and %d\r\n", CURRENT_MAX / 1000);
        } else {
    		set_current(newcurrent * 1000);
        	uart_printf("set %d\r\n", state.current_setpoint / 1000);
        }
	} else {
        uart_printf("err set usage: set <num>\r\n");
    }
}

void command_reset(char *args) {
	set_output_mode(OUTPUT_MODE_FEEDBACK);
	uart_printf("ok\r\n");
}

void command_read(char *args) {
	write_state_data();
}

void command_monitor(char *args) {
	char *newinterval = strsep(&args, ARGUMENT_SEPERATORS);
	if(newinterval[0] == 0) {
		uart_printf("err monitor expects at least one argument\r\n");
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
    uart_printf("info ui stack %d\r\n", (int)uxTaskGetStackHighWaterMark(ui_task));
    uart_printf("info comms stack %d\r\n", (int)uxTaskGetStackHighWaterMark(comms_task));
    uart_printf("info heap free %d\r\n", (int)xPortGetFreeHeapSize());
    uart_printf("info fet %d %d\r\n", (int)ADC_GetResult16(ADC_CHAN_OPAMP_OUT), (int)ADC_GetResult16(ADC_CHAN_FET_IN));
}

void command_calibration_progress(int current, int all) {
    // empty function to satisfy callback requirement
}

void command_calibrate(char *args) {
	char *subcommand = strsep(&args, ARGUMENT_SEPERATORS);
	if(subcommand[0] == '\0') {
		uart_printf("err cal expects at least one argument\r\n");
		return;
	} else if(subcommand[1] != '\0') {
		uart_printf("err cal: unrecognised subcommand\r\n");
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
    case 'O': // Set opamp offset trim
        if(args[0] == '\0') {
            uart_printf("cal O %d\r\n", settings->opamp_offset_trim);
            return;
        } else {
            set_opamp_offset_trim(&new_settings, atoi(args));
        }
        break;
    case 't': // Calibrate opamp offset trim
        calibrate_opamp_offset_trim(&new_settings, atoi(args), command_calibration_progress);
        break;
	default:
		uart_printf("err cal: unrecognised subcommand\r\n");
		return;
	}
	EEPROM_Write((uint8*)&new_settings, (uint8*)settings, sizeof(settings_t));
	uart_printf("ok\r\n");
}

void command_bootloader(char *buf) {
    uart_printf("ok\r\n");
    ui_event event;
    event.type = UI_EVENT_BOOTLOAD;
    xQueueSend(ui_queue, &event, 0);
}

void command_dump(char *buf) {
}

void command_version(char *buf) {
    uart_printf("version %hd.%hd\r\n", get_major_version(), get_minor_version());
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
    uart_write_mutex = xSemaphoreCreateMutex();
    
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
			uart_printf("overtemp\r\n");
			break;
        case COMMS_EVENT_UNDERVOLT:
            uart_printf("undervolt\r\n");
            break;
		}
	}		
}

/* [] END OF FILE */
