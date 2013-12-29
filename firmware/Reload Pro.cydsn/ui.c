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

typedef void (*readout_function_impl)(char *);

const display_settings_t display_settings = {
	.cc = {
		.readouts = {READOUT_CURRENT_SETPOINT, READOUT_CURRENT_USAGE, READOUT_VOLTAGE},
	},
};

typedef struct state_func_t {
	struct state_func_t (*func)(const void*);
	const void *arg;
	const int8 is_main_state;
} state_func;

typedef enum {
	VALUE_TYPE_CURRENT_RANGE,
} value_type;

typedef struct {
	const char *caption;
	const state_func new_state;
} menuitem;

typedef struct {
	const char *title;
	const menuitem items[];
} menudata;

typedef struct {
	const value_type type;
	const void *target;
	const int value;
} valueconfig;

static state_func cc_load(const void*);
static state_func menu(const void*);
static state_func set_value(const void*);
static state_func calibrate(const void*);
static state_func display_config(const void*);

#define STATE_MAIN {NULL, NULL, 0}
#define STATE_CC_LOAD {cc_load, NULL, 1}
#define STATE_CALIBRATE {calibrate, NULL, 0}
#define STATE_CONFIGURE_CC_DISPLAY {display_config, &display_settings.cc, 0}

#ifdef USE_SPLASHSCREEN
static state_func splashscreen(const void*);
#define STATE_SPLASHSCREEN {splashscreen, NULL, 0}
#endif

const menudata set_range_menu = {
	"Set Range",
	{
		{"0-250mA", {set_value, &(const valueconfig){VALUE_TYPE_CURRENT_RANGE, NULL, 0}, 0}},
		{"0-6A", {set_value, &(const valueconfig){VALUE_TYPE_CURRENT_RANGE, NULL, 1}, 0}},
		{NULL, {NULL, NULL, 0}},
	}
};

#define STATE_SET_RANGE {menu, &set_range_menu, 0}

const menudata set_readout_menu = {
	"Choose value",
	{
		{"Set Current", {NULL, (void*)READOUT_CURRENT_SETPOINT, 0}},
		{"Act. Current", {NULL, (void*)READOUT_CURRENT_USAGE, 0}},
		{"Voltage", {NULL, (void*)READOUT_VOLTAGE, 0}},
		{"Power", {NULL, (void*)READOUT_POWER, 0}},
		{"None", {NULL, (void*)READOUT_NONE, 0}},
		{NULL, {NULL, NULL, 0}},
	}
};

const menudata choose_readout_menu = {
	"Readouts",
	{
		{"Main display", {NULL, (void*)0, 0}},
		{"Left display", {NULL, (void*)1, 0}},
		{"Right display", {NULL, (void*)2, 0}},
		{NULL, {NULL, NULL, 0}},
	}
};

const menudata main_menu = {
	NULL,
	{
		{"C/C Load", STATE_CC_LOAD},
		{"Set Range", STATE_SET_RANGE},
		{"Readouts", STATE_CONFIGURE_CC_DISPLAY},
		{"Calibrate", STATE_CALIBRATE},
		{NULL, {NULL, NULL, 0}},
	}
};

#define STATE_MAIN_MENU {menu, &main_menu, 0}

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
	if(state.current_range == 0) {
		set_current(state.current_setpoint + delta * CURRENT_LOWRANGE_STEP);
	} else {
		set_current(state.current_setpoint + delta * CURRENT_FULLRANGE_STEP);
	}
}

static void next_event(ui_event *event) {
	xQueueReceive(ui_queue, event, portMAX_DELAY);
}

static void draw_menu(const menudata *menu, int selected) {
	int start_row = 0;
	int height = 4;
	if(menu->title) {
		int8 padding = (160 - strlen(menu->title) * 12) / 2;
		Display_Clear(0, 0, 2, padding, 0xFF);
		Display_DrawText(0, padding, menu->title, 1);
		Display_Clear(0, 160 - padding, 2, 160, 0xFF);
		start_row++;
		height--;
	}

	if((selected / height) > 0) {
		Display_DrawText(start_row * 2, 148, FONT_GLYPH_UARR, 0);
	} else {
		Display_DrawText(start_row * 2, 148, " ", 0);
	}
	
	// Find the block of items the selected element is in
	const menuitem *current = &menu->items[selected - selected % height];
	selected %= height;
	
	for(int i = 0; i < height; i++) {
		if(current->caption != NULL) {
			Display_DrawText((i + start_row) * 2, 0, current->caption, i == selected);
			Display_Clear((i + start_row) * 2, strlen(current->caption) * 12, (i + start_row + 1) * 2, 142, (i == selected)*255);
			current++;
		} else {
			Display_Clear((i + start_row) * 2, 0, (i + start_row + 1) * 2, 160, 0);
		}
	}
	
	if(current->caption != NULL) {
		Display_DrawText(6, 148, FONT_GLYPH_DARR, 0);
	} else {
		Display_DrawText(6, 148, " ", 0);
	}
}

void print_setpoint(char *buf) {
	format_number(get_current_setpoint(), 'A', buf);
}

void print_current_usage(char *buf) {
	format_number(get_current_usage(), 'A', buf);
}

void print_voltage(char *buf) {
	format_number(get_voltage(), 'V', buf);
}

void print_power(char *buf) {
	int power = (get_current_usage() / 1000) * (get_voltage() / 1000);
	format_number(power, 'W', buf);
}

const readout_function_impl readout_functions[] = {
	NULL,
	print_setpoint,
	print_current_usage,
	print_voltage,
	print_power,
};

static void draw_status(const display_config_t *config, const char *type) {
	char buf[8];

	// Draw the main info
	readout_function_impl readout = readout_functions[config->readouts[0]];
	if(readout != NULL) {
		readout(buf);
		strcat(buf, " ");
		Display_DrawBigNumbers(0, 0, buf);
		if(strchr(buf, '.') == NULL)
			// Clear any detritus left over from longer strings
			Display_Clear(0, 108, 4, 120, 0);
	} else {
		Display_Clear(0, 0, 6, 120, 0);
		Display_Clear(4, 120, 6, 160, 0);
	}
	
	// Draw the two smaller displays
	readout = readout_functions[config->readouts[1]];
	if(readout != NULL) {
		readout(buf);
		strcat(buf, " ");
	} else {
		strcpy(buf, "      ");
	}
	Display_DrawText(6, 0, buf, 0);
	
	readout = readout_functions[config->readouts[2]];
	if(readout != NULL) {
		readout(buf);
		if(strlen(buf) == 5)
			strcat(buf, " ");
	} else {
		strcpy(buf, "      ");
	}
	Display_DrawText(6, 90, buf, 0);
	
	// Draw the type in the top right
	Display_DrawText(0, 160 - strlen(type) * 12, type, 1);
}

static state_func set_value(const void *arg) {
	valueconfig *config = (valueconfig *)arg;
	switch(config->type) {
	case VALUE_TYPE_CURRENT_RANGE:
		set_current_range(config->value);
		break;
	}
	
	return (state_func)STATE_MAIN;
}

static state_func display_config(const void *arg) {
	display_config_t *config = (display_config_t*)arg;
	
	int idx = (int) menu(&choose_readout_menu).arg;
	readout_function func = (readout_function) menu(&set_readout_menu).arg;
	
	EEPROM_Write((uint8*)&func, (uint8*)&config->readouts[idx], sizeof(readout_function));
	
	return (state_func)STATE_MAIN;
}

static state_func menu(const void *arg) {
	const menudata *menu = (const menudata *)arg;
	
	Display_ClearAll();
	
	int selected = 0;
	ui_event event;
	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1) {
		draw_menu(menu, selected);
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
					if(menu->items[selected + 1].caption == NULL)
						break;
					selected++;
				}
			}
			break;
		default:
			break;
		}
	}

	return menu->items[selected].new_state;
}

#ifdef USE_SPLASHSCREEN
static state_func splashscreen(const void *arg) {
	vTaskDelay(configTICK_RATE_HZ * 3);
	return (state_func)STATE_CC_LOAD;
}
#endif

static state_func cc_load(const void *arg) {
	Display_ClearAll();
	
	ui_event event;
	while(1) {
		next_event(&event);
		switch(event.type) {
		case UI_EVENT_BUTTONPRESS:
			if(event.int_arg == 1)
				return (state_func)STATE_MAIN_MENU;
		case UI_EVENT_UPDOWN:
			adjust_current_setpoint(event.int_arg);
			break;
		default:
			break;
		}
		draw_status(&display_settings.cc, "SET");
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
	Display_Clear(2, 0, 8, 160, 0);
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
			new_settings->dac_offsets[i] = -j;
		}
	}
	
	set_current_range(0);
	IDAC_SetValue(0);
}

void calibrate_current(settings_t *new_settings) {
	Display_Clear(4, 0, 8, 160, 0);
	Display_DrawText(2, 0, "  3: Current ", 1);
	Display_DrawText(6, 38, FONT_GLYPH_ENTER ": Next", 0);
	
	set_current_range(1);
	IDAC_SetValue(42 + new_settings->dac_offsets[1]);
	
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
	
	new_settings->dac_gains[1] = current / 42;
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
	
	return (state_func){NULL, NULL, 0};
}

void vTaskUI( void *pvParameters ) {
	QuadratureISR_StartEx(quadrature_event_isr);
	QuadButtonISR_StartEx(button_press_isr);

	state_func main_state = STATE_CC_LOAD;
	#ifdef USE_SPLASHSCREEN
	state_func state = STATE_SPLASHSCREEN;
	#else
	state_func state = STATE_CC_LOAD;
	#endif
	
	while(1) {
		state_func new_state = state.func(state.arg);
		if(new_state.func == NULL) {
			memcpy(&state, &main_state, sizeof(state_func));
		} else {
			memcpy(&state, &new_state, sizeof(state_func));
		}
		
		if(state.is_main_state) {
			memcpy(&main_state, &state, sizeof(state_func));
		}
	}
}


/* [] END OF FILE */
