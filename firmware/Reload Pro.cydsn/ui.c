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

#include "tasks.h"
#include "Display_font.h"
#include "config.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>
#include <stdlib.h>

xQueueHandle ui_queue;

typedef struct state_func_t {
	struct state_func_t (*func)(const void*);
	const void *arg;
} state_func;

typedef struct {
	const char *caption;
	const state_func action;
} menuitem;

static state_func splashscreen(const void*);
static state_func ui_main(const void*);
static state_func menu(const void*);
static state_func calibrate(const void*);

#define STATE_MAIN (state_func){ui_main, NULL}
#define STATE_SPLASHSCREEN (state_func){splashscreen, NULL}
#define STATE_CALIBRATE (state_func){calibrate, NULL}

const menuitem main_menu[] = {
	{"C/C Load    ", {ui_main, NULL}},
	{"Calibrate   ", {calibrate, NULL}},
	{NULL, {NULL, NULL}},
};

#define STATE_MAIN_MENU (state_func){menu, main_menu}

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

static void format_number(int num, const char suffix, char *out) {
	if(num < 0)
		num = 0;
	
	int magnitude = 1;
	while(num >= 1000000) {
		num /= 1000;
		magnitude++;
	}
	
	int whole = num / 1000, remainder = num % 1000;
	if(whole < 10) {
		// Format: x.xx
		sprintf(out, "%1d.%02d", whole, remainder / 10);
	} else if(whole < 100) {
		// Format: xx.x
		sprintf(out, "%02d.%1d", whole, remainder / 100);
	} else {
		// Format: xxx
		sprintf(out, "%03d", whole);
	}
	
	if(magnitude == 1) {
		strcat(out, (const char[]){'m', suffix, '\0'});
	} else {
		strcat(out, (const char[]){suffix, ' ', '\0'});
	}
}

static void adjust_current_setpoint(int delta) {
	int step;
	if(state.current_setpoint < CURRENT_LOWRANGE_THRESHOLD) {
		step = CURRENT_LOWRANGE_STEP;
	} else if(state.current_setpoint > CURRENT_LOWRANGE_THRESHOLD) {
		step = CURRENT_FULLRANGE_STEP;
	} else if(delta < 0) {
		step = CURRENT_LOWRANGE_STEP;
	} else {
		step = CURRENT_FULLRANGE_STEP;
	}
	set_current(state.current_setpoint + delta * step);
}

static void next_event(ui_event *event) {
	xQueueReceive(ui_queue, event, portMAX_DELAY);
}

static void draw_menu(const menuitem *items, int selected) {
	if((selected & ~0x3) > 0) {
		Display_DrawText(0, 148, FONT_GLYPH_UARR, 0);
	} else {
		Display_DrawText(0, 148, " ", 0);
	}
	
	// Find the block of items the selected element is in
	const menuitem *current = &items[selected & ~0x3];
	selected &= 0x3;
	
	for(int i = 0; i < 4; i++) {
		if(current->caption != NULL) {
			Display_DrawText(i * 2, 0, current->caption, i == selected);
			current++;
		} else {
			Display_Clear(i * 2, 0, i * 2 + 2, 160);
		}
	}
	
	if(current->caption != NULL) {
		Display_DrawText(6, 148, FONT_GLYPH_DARR, 0);
	} else {
		Display_DrawText(6, 148, " ", 0);
	}
}

static void draw_status(display_config *config, const char *type) {
	char buf[8];

	// Draw the main info
	format_number(config->main.func(), config->main.suffix, buf);
	Display_DrawBigNumbers(0, 0, buf);
	strcat(buf, " ");
	if(strchr(buf, '.') == NULL)
		// Clear any detritus left over from longer strings
		Display_Clear(0, 108, 4, 120);
	
	// Draw the two smaller displays
	format_number(config->secondary[0].func(), config->secondary[0].suffix, buf);
	strcat(buf, " ");
	Display_DrawText(6, 0, buf, 0);
	
	format_number(config->secondary[1].func(), config->secondary[1].suffix, buf);
	if(strlen(buf) == 5)
		strcat(buf, " ");
	Display_DrawText(6, 90, buf, 0);
	
	// Draw the type in the top right
	Display_DrawText(0, 160 - strlen(type) * 12, type, 1);
}

static state_func menu(const void *arg) {
	const menuitem *items = (const menuitem *)arg;
	
	Display_ClearAll();
	
	int selected = 0;
	ui_event event;
	while(1) {
		draw_menu(items, selected);
		next_event(&event);
		switch(event.type) {
		case UI_EVENT_UPDOWN:
			if(event.int_arg < 0) {
				// Move up the menu
				if(selected + event.int_arg >= 0) {
					selected += event.int_arg;
				} else {
					selected = 0;
				}
			} else {
				// Move down the menu (but not past the end)
				for(int i = 0; i < event.int_arg; i++) {
					if(items[selected + 1].caption == NULL)
						break;
					selected++;
				}
			}
			break;
		case UI_EVENT_BUTTONPRESS:
			if(event.int_arg == 1)
				return items[selected].action;
		default:
			break;
		}
	}
}

static state_func splashscreen(const void *arg) {
	vTaskDelay(configTICK_RATE_HZ * 3);
	return STATE_MAIN;
}

static state_func ui_main(const void *arg) {
	Display_ClearAll();
	
	ui_event event;
	while(1) {
		next_event(&event);
		switch(event.type) {
		case UI_EVENT_BUTTONPRESS:
			if(event.int_arg == 1)
				return STATE_MAIN_MENU;
		case UI_EVENT_UPDOWN:
			adjust_current_setpoint(event.int_arg);
			break;
		default:
			break;
		}
		draw_status(&(display_config){{get_current_setpoint, 'A'}, {{get_current_usage, 'A'}, {get_voltage, 'V'}}}, "SET");
	}
}

// Calibrates the ADC voltage and current offsets.
// Run with nothing attached to the terminals.
void calibrate_offsets(settings_t *new_settings) {
	Display_DrawText(2, 0, "  1: Offset  ", 1);
	Display_DrawText(6, 38, FONT_GLYPH_ENTER ": Next", 0);

	// Wait for a button press
	ui_event event;
	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1)
		next_event(&event);
	
	new_settings->adc_voltage_offset = get_raw_voltage();
	new_settings->adc_current_offset = get_raw_current_usage();
}

// Calibrate the ADC voltage gain.
// Run with a known voltage across the terminals
void calibrate_voltage(settings_t *new_settings) {
	Display_DrawText(2, 0, "  2: Voltage ", 1);

	ui_event event;
	char buf[8];
	while(1) {
		next_event(&event);
		
		format_number((get_raw_voltage() - new_settings->adc_voltage_offset) * new_settings->adc_voltage_gain, 'V', buf);
		strcat(buf, " ");
		Display_DrawText(4, 43, buf, 0);
		
		switch(event.type) {
		case UI_EVENT_UPDOWN:
			new_settings->adc_voltage_gain += (new_settings->adc_voltage_gain * event.int_arg) / 500;
			break;
		case UI_EVENT_BUTTONPRESS:
			if(event.int_arg == 1)
				return;
		default:
			break;
		}
	}
}

// Calibrates the opamp and current DAC offsets.
// Run with a voltage source attached
void calibrate_opamp_dac_offsets(settings_t *new_settings) {
	Display_Clear(2, 0, 8, 160);
	Display_DrawText(4, 12, "Please wait", 0);
	IDAC_SetValue(0);

	// Find the best setting for the opamp trim
	for(int i = 0; i < 32; i++) {
		CY_SET_REG32(Opamp_cy_psoc4_abuf__OA_OFFSET_TRIM, i);
		CyDelay(100);
		
		int offset = ADC_GetResult16(0) - new_settings->adc_current_offset;
		if(offset <= 0) {
			new_settings->opamp_offset_trim = i;
			break;
		}
	}
	
	// Find the best setting for the DAC offsets
	for(int i = 0; i < 2; i++) {
		set_current_range(i);
		new_settings->dac_offsets[i] =  0;
		for(int j = 0; j < 256; j++) {
			IDAC_SetValue(j);
			CyDelay(100);

			int offset = ADC_GetResult16(0) - new_settings->adc_current_offset;
			if(offset > 0)
				break;
			new_settings->dac_offsets[i] = j;
		}
	}
	
	set_current_range(0);
	IDAC_SetValue(0);
}

void calibrate_current(settings_t *new_settings) {
	Display_Clear(4, 0, 8, 160);
	Display_DrawText(2, 0, "  3: Current ", 1);
	Display_DrawText(6, 38, FONT_GLYPH_ENTER ": Next", 0);
	
	set_current_range(1);
	IDAC_SetValue(30 + new_settings->dac_offsets[1]);
	
	ui_event event;
	char buf[8];
	int current;
	
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1) {
		next_event(&event);
		
		current = (get_raw_current_usage() - new_settings->adc_current_offset) * new_settings->adc_current_gain;
		format_number(current, 'A', buf);
		strcat(buf, " ");
		Display_DrawText(4, 43, buf, 0);
		
		switch(event.type) {
		case UI_EVENT_UPDOWN:
			new_settings->adc_current_gain += (new_settings->adc_current_gain * event.int_arg) / 500;
			break;
		default:
			break;
		}
	}
	
	new_settings->dac_gains[1] = current / 30;
	set_current_range(0);
	IDAC_SetValue(200 + new_settings->dac_offsets[0]);
	CyDelay(100);
	current = (ADC_GetResult16(0) - new_settings->adc_current_offset) * new_settings->adc_current_gain;
	new_settings->dac_gains[0] = current / 200;
	
	IDAC_SetValue(new_settings->dac_offsets[0]);
}

state_func calibrate(const void *arg) {
	set_current(0);
	
	settings_t new_settings;
	memcpy(&new_settings, settings, sizeof(settings_t));
	
	Display_ClearAll();
	Display_DrawText(0, 0, " CALIBRATION ", 1);
	
	calibrate_offsets(&new_settings);
	calibrate_voltage(&new_settings);
	calibrate_opamp_dac_offsets(&new_settings);
	calibrate_current(&new_settings);
	
	EEPROM_Write((uint8*)&new_settings, (uint8*)settings, sizeof(settings_t));
	
	return STATE_MAIN;
}

void vTaskUI( void *pvParameters ) {
	QuadratureISR_StartEx(quadrature_event_isr);
	QuadButtonISR_StartEx(button_press_isr);

	state_func state = STATE_SPLASHSCREEN;
	while(1) {
		state = state.func(state.arg);
	}
}


/* [] END OF FILE */
