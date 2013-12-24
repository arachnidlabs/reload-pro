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
#include "font.h"
#include "config.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>

xQueueHandle ui_queue;

typedef struct state_func_t {
	struct state_func_t (*func)(const void*);
	const void *arg;
} state_func;

typedef struct {
	const char *caption;
	const state_func action;
} menuitem;

static state_func ui_main(const void*);
static state_func menu(const void*);

#define STATE_MAIN (state_func){ui_main, NULL}

const menuitem main_menu[] = {
	{"Test 1      ", {ui_main, NULL}},
	{"Test 2      ", {ui_main, NULL}},
	{"Test 3      ", {ui_main, NULL}},
	{"Test 4      ", {ui_main, NULL}},
	{"Test 5      ", {ui_main, NULL}},
	{NULL, {NULL, NULL}},
};

#define STATE_MAIN_MENU (state_func){menu, main_menu}

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
		Display_DrawText(0, 148, (char[]){FONT_GLYPH_UARR, 0}, 0);
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
		Display_DrawText(6, 148, (char[]){FONT_GLYPH_DARR, 0}, 0);
	} else {
		Display_DrawText(6, 148, " ", 0);
	}
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
		}
	}
}

static state_func ui_main(const  void *arg) {
	Display_ClearAll();

	ui_event event;
	while(1) {
		int current = state.current_setpoint / 10000.0;
		char buf[4];
		sprintf(buf, "%d.%02d", current / 100, current % 100);
		Display_DrawBigNumbers(0, 0, buf);

		next_event(&event);
		switch(event.type) {
		case UI_EVENT_BUTTONPRESS:
			if(event.int_arg == 1)
				return STATE_MAIN_MENU;
		case UI_EVENT_UPDOWN:
			adjust_current_setpoint(event.int_arg);
			break;
		}
	}
}

void vTaskUI( void *pvParameters ) {
	state_func state = STATE_MAIN;
	while(1) {
		state = state.func(state.arg);
	}
/*		int16 delta = QuadDec_ReadCounter() - 0x8000;
		if(delta != 0) {
			QuadDec_WriteCounter(0x8000);
			
		}*/
}


/* [] END OF FILE */
