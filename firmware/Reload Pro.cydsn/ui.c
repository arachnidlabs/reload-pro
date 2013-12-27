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

#define STATE_MAIN (state_func){ui_main, NULL}
#define STATE_SPLASHSCREEN (state_func){splashscreen, NULL}

const menuitem main_menu[] = {
	{"Test 1      ", {ui_main, NULL}},
	{"Test 2      ", {ui_main, NULL}},
	{"Test 3      ", {ui_main, NULL}},
	{"Test 4      ", {ui_main, NULL}},
	{"Test 5      ", {ui_main, NULL}},
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

static void draw_status(display_config *config) {
	char buf[8];

	// Draw the main info
	format_number(config->main.func(), config->main.suffix, buf);
	strcat(buf, " ");
	Display_DrawBigNumbers(0, 0, buf);
	
	// Draw the two smaller displays
	format_number(config->secondary[0].func(), config->secondary[0].suffix, buf);
	strcat(buf, " ");
	Display_DrawText(6, 0, buf, 0);
	
	format_number(config->secondary[1].func(), config->secondary[1].suffix, buf);
	if(strlen(buf) == 5)
		strcat(buf, " ");
	Display_DrawText(6, 90, buf, 0);
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
	Display_DrawText(0, 124, "SET", 1);

	ui_event event;
	while(1) {
		next_event(&event);
		switch(event.type) {
		case UI_EVENT_BUTTONPRESS:
			if(event.int_arg == 1)
				return STATE_MAIN_MENU;
		case UI_EVENT_UPDOWN:
			adjust_current_setpoint(event.int_arg);
			draw_status(&(display_config){{get_current_setpoint, 'A'}, {{get_current_usage, 'A'}, {get_voltage, 'V'}}});
			break;
		case UI_EVENT_ADC_READING:
			draw_status(&(display_config){{get_current_setpoint, 'A'}, {{get_current_usage, 'A'}, {get_voltage, 'V'}}});
			break;
		}
	}
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
