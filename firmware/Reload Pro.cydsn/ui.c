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

#include "comms.h"
#include "calibrate.h"
#include "tasks.h"
#include "Display_font.h"
#include "config.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>
#include <stdlib.h>

xQueueHandle ui_queue;

typedef struct {
	void (*func)(char *);
	char *label;
} readout_function_impl;

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

typedef void (*void_func)();

static state_func cc_load(const void*);
static state_func menu(const void*);
static state_func ui_set_min_voltage(const void*);
static state_func ui_calibrate(const void*);
static state_func display_config(const void*);
static state_func set_contrast(const void *);
static state_func overlimit(const void*);
static state_func call_void_func(const void*);
static state_func upgrade(const void*);

#define STATE_MAIN {NULL, NULL, 0}
#define STATE_CC_LOAD {cc_load, NULL, 1}
#define STATE_MIN_VOLTAGE {ui_set_min_voltage, NULL, 0}
#define STATE_CALIBRATE {ui_calibrate, NULL, 0}
#define STATE_CONFIGURE_CC_DISPLAY {display_config, 0, 0}
#define STATE_SET_CONTRAST {set_contrast, NULL, 0}
#define STATE_LIMIT {overlimit, NULL, 0}
#define STATE_RESET_TOTALS {call_void_func, (void_func)reset_running_totals, 0}
#define STATE_UPGRADE {upgrade, NULL, 0}

#ifdef USE_SPLASHSCREEN
static state_func splashscreen(const void*);
#define STATE_SPLASHSCREEN {splashscreen, NULL, 0}
#endif

const menudata set_readout_menu = {
	"Choose value",
	{
		{"Set Current", {NULL, (void*)READOUT_CURRENT_SETPOINT, 0}},
		{"Act. Current", {NULL, (void*)READOUT_CURRENT_USAGE, 0}},
		{"Voltage", {NULL, (void*)READOUT_VOLTAGE, 0}},
		{"Power", {NULL, (void*)READOUT_POWER, 0}},
		{"Resistance", {NULL, (void*)READOUT_RESISTANCE, 0}},
		{"Total current", {NULL, (void*)READOUT_TOTAL_CURRENT, 0}},
		{"Total power", {NULL, (void*)READOUT_TOTAL_POWER, 0}},
		{"None", {NULL, (void*)READOUT_NONE, 0}},
        {"EXIT", STATE_MAIN},
		{NULL, {NULL, NULL, 0}},
	}
};

const menudata choose_readout_menu = {
	"Readouts",
	{
		{"Main disp.", {NULL, (void*)1, 0}},
		{"Left disp.", {NULL, (void*)2, 0}},
		{"Right disp.", {NULL, (void*)3, 0}},
        {"EXIT", STATE_MAIN},
		{NULL, {NULL, NULL, 0}},
	}
};

const menudata main_menu = {
	NULL,
	{
		{"C/C Load", STATE_CC_LOAD},
		{"Readouts", STATE_CONFIGURE_CC_DISPLAY},
        {"Min Voltage", STATE_MIN_VOLTAGE},
		{"Reset Totals", STATE_RESET_TOTALS},
		{"Contrast", STATE_SET_CONTRAST},
		{"Calibrate", STATE_CALIBRATE},
		{"Upgrade Mode", STATE_UPGRADE},
        {"EXIT", STATE_MAIN},
		{NULL, {NULL, NULL, 0}},
	}
};

#define STATE_MAIN_MENU {menu, &main_menu, 0}

xTimerHandle button_timer;

void button_timer_callback(xTimerHandle timer) {
    static ui_event event = {.type = UI_EVENT_LONG_BUTTONPRESS, .when = 0};
    xQueueSend(ui_queue, &event, 0);
}

CY_ISR(button_press_isr) {
	static ui_event event = {.type = UI_EVENT_BUTTONPRESS, .when = 0};
    static portTickType before = 0;

	event.int_arg = QuadButton_Read();
	QuadButton_ClearInterrupt();
	
    before = event.when;
    event.when = xTaskGetTickCountFromISR();
    
    // it is suggested to have debounce timer of 5-30 ms in different sources, so going with conservetive 30 ms value
	if(event.int_arg && (event.when - before >= (30 * configTICK_RATE_HZ / 1000)) && xTimerIsTimerActive(button_timer)) {
        xTimerStopFromISR(button_timer, NULL);
		xQueueSendToBackFromISR(ui_queue, &event, NULL);
	} else if(!event.int_arg) {
        // Button is pushed
        xTimerStartFromISR(button_timer, NULL);
    } else {
        xTimerStopFromISR(button_timer, NULL);
    }
}

// Maps current state (index) to next state for a forward transition.
const int8 quadrature_states[] = {0x1, 0x3, 0x0, 0x2};

CY_ISR(quadrature_event_isr) {
	static ui_event event = {.type = UI_EVENT_UPDOWN, .when = 0, .int_arg = 0};
    static int8 last_levels = 3;
	static int8 count = 0;
    static portTickType before = 0;
    
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
        before = event.when;
        event.when = xTaskGetTickCountFromISR();
        
        // calculate step size that is inversely proportional to the time that has passed since last click
        event.duration = event.when - before;
        if(event.duration < 1)
            event.duration = 1;
        
        event.int_arg = count / 4;
		xQueueSendToBackFromISR(ui_queue, &event, NULL);
		count = count % 4;
	}
}

static void format_number(int num, const char *suffix, char *out) {
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
		strcat(out, "m");
		strcat(out, suffix);
	} else {
		strcat(out, suffix);
		strcat(out, " ");
	}
}

static void adjust_current_setpoint(int delta, portTickType duration) {
    // Implement encoder acceleration
    int step = (((ENCODER_ACCEL_CONSTANT * configTICK_RATE_HZ) / 1000) / duration);
    if(step < 1)
        step = 1;
	set_current(state.current_setpoint + delta * step * CURRENT_STEP);
    uart_printf("set %d\r\n", state.current_setpoint / 1000);
}

static void next_event(ui_event *event) {
	static portTickType last_tick = 0;
	
	portTickType now = xTaskGetTickCount();
	if(now - last_tick >  configTICK_RATE_HZ / UI_TASK_FREQUENCY
        || !xQueueReceive(ui_queue, event, configTICK_RATE_HZ / UI_TASK_FREQUENCY - (now - last_tick))) {
		event->type = UI_EVENT_TICK;
		event->when = now;
		last_tick = now;
#ifdef USE_WATCHDOG
        CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);
#endif
	} else if(event->type == UI_EVENT_BOOTLOAD) {
        // Bootloading overrides everything
        upgrade(NULL); // Never returns
    }
}

static void draw_menu(const menudata *menu, int selected) {
	int start_row = 0;
	int height = 4;

	if(menu->title) {
		int8 padding = (158 - strlen(menu->title) * 12) / 2;
		Display_Clear(0, 2, 2, padding + 1, 0xFF);
		Display_DrawText(0, padding + 1, menu->title, 1);
		Display_Clear(0, 160 - padding - 1, 2, 160, 0xFF);
		start_row++;
		height--;
	}

	Display_DrawText(start_row * 2, 148, ((selected / height) > 0)?FONT_GLYPH_UARR:" ", 0);
	
	// Find the block of items the selected element is in
	const menuitem *current = &menu->items[selected - selected % height];
	selected %= height;
	
	for(int i = 0; i < height; i++) {
		if(current->caption != NULL) {
			Display_DrawText((i + start_row) * 2, 2, current->caption, i == selected);
			Display_Clear((i + start_row) * 2, strlen(current->caption) * 12 + 1, (i + start_row + 1) * 2, 148, (i == selected)*255);
			current++;
		} else {
			Display_Clear((i + start_row) * 2, 1, (i + start_row + 1) * 2, 160, 0);
		}
	}
	
	if(current->caption != NULL) {
		Display_DrawText(6, 148, FONT_GLYPH_DARR, 0);
	} else {
		Display_DrawText(6, 148, " ", 0);
	}
}

void print_nothing(char *buf) {
	strcpy(buf, "      ");
}

void print_setpoint(char *buf) {
	format_number(get_current_setpoint(), "A", buf);
}

void print_current_usage(char *buf) {
	format_number(get_current_usage(), "A", buf);
}

void print_voltage(char *buf) {
	format_number(get_voltage(), "V", buf);
}

void print_power(char *buf) {
	int power = (get_current_usage() / 1000) * (get_voltage() / 1000);
	format_number(power, "W", buf);
}

void print_resistance(char *buf) {
	int current = get_current_usage();
	if(current > 0) {
		format_number(((get_voltage() * 10) / (current / 100000)), FONT_GLYPH_OHM, buf);
	} else {
		strcpy(buf, "----" FONT_GLYPH_OHM);
	}
}

void print_amp_hours(char *buf) {
	format_number(get_microamp_hours(), "Ah", buf);
}

void print_watt_hours(char *buf) {
	format_number(get_microwatt_hours(), "Wh", buf);
}

const readout_function_impl readout_functions[] = {
	{print_nothing, ""},
	{print_setpoint, "SET"},
	{print_current_usage, "ACT"},
	{print_voltage, ""},
	{print_power, ""},
	{print_resistance, ""},
	{print_amp_hours, ""},
	{print_watt_hours, ""},
};

static void draw_status(const display_config_t *config) {
	char buf[8];

	// Draw the main info
	const readout_function_impl *readout = &readout_functions[config->readouts[0]];
	if(readout->func != print_nothing) {
		readout->func(buf);
		strcat(buf, " ");
		Display_DrawBigNumbers(0, 0, buf);
		if(strchr(buf, '.') == NULL)
			// Clear any detritus left over from longer strings
			Display_Clear(0, 108, 4, 120, 0);
	} else {
		Display_Clear(0, 0, 6, 120, 0);
		Display_Clear(4, 120, 6, 160, 0);
	}

	// Draw the type in the top right
	uint8 labelsize = strlen(readout->label) * 12;
	Display_DrawText(0, 160 - labelsize, readout->label, 1);
	if(labelsize < 36)
		Display_Clear(0, 124, 2, 160 - labelsize, 0);


    // Draw the type in the middle right
    if(get_output_mode() == OUTPUT_MODE_OFF) {
    	Display_DrawText(2, 160 - 36, "OFF", 1);
    } else {
        Display_Clear(2, 124, 4, 160, 0);
    }    
        
	// Draw the two smaller displays
	for(int i = 0; i < 2; i++) {
		readout = &readout_functions[config->readouts[i + 1]];
		readout->func(buf);
		if(strlen(buf) == 5)
			strcat(buf, " ");
		Display_DrawText(6, 88 * i, buf, 0);
	}
}

static state_func display_config(const void *arg) {
	const display_config_t *config = &settings->display_settings.numbered[(int)arg];
	
	state_func display = menu(&choose_readout_menu);
	if(display.arg == NULL)
		return display;
	
	state_func readout = menu(&set_readout_menu);
	if(readout.arg == NULL)
		return readout;
	
	EEPROM_Write((uint8*)&((readout_function){(readout_function)readout.arg}), (uint8*)&config->readouts[(int)display.arg - 1], sizeof(readout_function));
	
	return (state_func)STATE_MAIN;
}

static state_func call_void_func(const void *arg) {
	((void_func)arg)();
	return (state_func)STATE_MAIN;
}

static state_func set_contrast(const void *arg) {
	Display_ClearAll();
	Display_Clear(0, 2, 2, 160, 0xFF);
	Display_DrawText(0, 32, "Contrast", 1);
	Display_DrawText(6, 38, FONT_GLYPH_ENTER ": Done", 0);

	// Left and right ends of the bar
	Display_Clear(4, 15, 5, 16, 0xFF);
	Display_Clear(4, 145, 5, 146, 0xFF);
	
	int contrast = settings->lcd_contrast;
	ui_event event;
	while(1) {
		Display_Clear(4, 16, 5, 16 + contrast * 2, 0xFF);
		Display_Clear(4, 16 + contrast * 2, 5, 145, 0x81);
		
		next_event(&event);
		switch(event.type) {
		case UI_EVENT_UPDOWN:
			contrast += event.int_arg;
			if(contrast > 0x3F) {
				contrast = 0x3F;
			} else if(contrast < 0) {
				contrast = 0;
			}
			Display_SetContrast(contrast);
			break;
		case UI_EVENT_BUTTONPRESS:
			if(event.int_arg == 1) {
				EEPROM_Write((const uint8*)&contrast, (const uint8*)&settings->lcd_contrast, sizeof(int));
				return (state_func)STATE_MAIN;
			}
			break;
		case UI_EVENT_LIMIT:
			return (state_func){overlimit, (void *)event.int_arg, 0};
		default:
			break;
		}
	}
}

static state_func ui_set_min_voltage(const void *arg) {
    Display_ClearAll();
	Display_Clear(0, 2, 2, 160, 0xFF);
	Display_DrawText(0, 20, "Min Voltage", 1);

    ui_event event;
    uint8_t on = state.lower_voltage_limit != -1;
    int vlim = on?state.lower_voltage_limit:get_voltage();
    vlim -= vlim % 100000;
    uint8_t stage = 0;
    char buf[8];
    
    while(stage == 0) {
        Display_DrawText(4, 30, "ON", on);
        Display_DrawText(4, 90, "OFF", !on);
        format_number(vlim, "V", buf);
        Display_DrawText(6, 48, buf, 0);
        
        next_event(&event);
        switch(event.type) {
        case UI_EVENT_UPDOWN:
            on ^= event.int_arg & 1;
            break;
        case UI_EVENT_BUTTONPRESS:
            if(event.int_arg != 1)
                break;
            if(on) {
                stage = 1;
            } else {
                state.lower_voltage_limit = -1;
                return (state_func)STATE_MAIN;
            }
            break;
        case UI_EVENT_LIMIT:
            return (state_func){overlimit, (void *)event.int_arg, 0};
        default:
            break;
        }
    }
    
    while(1) {
        format_number(vlim, "V", buf);
        buf[strlen(buf) - 1] = '\0';
        Display_DrawText(6, 48, buf, 1);

        next_event(&event);
        switch(event.type) {
        case UI_EVENT_UPDOWN:
            vlim += 100000 * event.int_arg;
            break;
        case UI_EVENT_BUTTONPRESS:
            if(event.int_arg != 1)
                break;
            state.lower_voltage_limit = vlim;
            return (state_func)STATE_MAIN;
        case UI_EVENT_LIMIT:
            return (state_func){overlimit, (void *)event.int_arg, 0};
        default:
            break;
        }
    }
}

static state_func overlimit(const void *arg) {
	Display_Clear(0, 0, 8, 160, 0xFF);
    switch((limit_type)arg) {
    case LIMIT_TYPE_OVERTEMP:
    	Display_DrawText(2, 6, "! OVERTEMP !", 1);
        break;
    case LIMIT_TYPE_UNDERVOLT:
        Display_DrawText(2, 0, "! UNDERVOLT !", 1);
        break;
    }
	Display_DrawText(6, 32, FONT_GLYPH_ENTER ": Reset", 1);
	
	ui_event event;
	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1) {
		next_event(&event);
		if(get_output_mode() == OUTPUT_MODE_FEEDBACK)
			return (state_func)STATE_MAIN;
	}
		
	set_current(0);
	set_output_mode(OUTPUT_MODE_FEEDBACK);
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
		case UI_EVENT_LIMIT:
			return (state_func){overlimit, (void *)event.int_arg, 0};
		default:
			break;
		}
	}

	return menu->items[selected].new_state;
}

#ifdef USE_SPLASHSCREEN
static state_func splashscreen(const void *arg) {
    ui_event event;
    for(int i = 0; i < 3 * UI_TASK_FREQUENCY; i++)
        next_event(&event);

    // Perform a factory reset if the button is held in at the end of the splashscreen.
    if(QuadButton_Read() == 0) {
        factory_reset();
    }
        
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
			if(event.int_arg == 1) {
                if(get_output_mode() != OUTPUT_MODE_FEEDBACK) {
                    set_output_mode(OUTPUT_MODE_FEEDBACK);
                } else {
				    set_output_mode(OUTPUT_MODE_OFF);
                }
            }
            break;
        case UI_EVENT_LONG_BUTTONPRESS:
            return (state_func)STATE_MAIN_MENU;
		case UI_EVENT_UPDOWN:
			adjust_current_setpoint(event.int_arg, event.duration);
			break;
		case UI_EVENT_LIMIT:
			return (state_func){overlimit, (void *)event.int_arg, 0};
		default:
			break;
		}
		draw_status(&settings->display_settings.named.cc);
		//CyDelay(200);
	}
}

#define CALIBRATION_CURRENT 2000000

// Calibrates the ADC voltage and current offsets.
// Run with nothing attached to the terminals.
static void ui_calibrate_offsets(settings_t *new_settings) {
    set_current(0);
	Display_DrawText(2, 0, " Remove Leads", 1);
	Display_DrawText(6, 38, FONT_GLYPH_ENTER ": Next", 0);

	// Wait for a button press
	ui_event event;
	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1)
		next_event(&event);
	
	calibrate_offsets(new_settings);
}

// Calibrate the ADC voltage gain.
// Run with a known voltage across the terminals
static void ui_calibrate_voltage(settings_t *new_settings) {
	Display_DrawText(2, 0, " Adj. voltage", 1);
	
	ui_event event;
	char buf[8];
	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1) {
		next_event(&event);
		
		format_number((get_raw_voltage() - new_settings->adc_voltage_offset) * new_settings->adc_voltage_gain, "V", buf);
		strcat(buf, " ");
		Display_DrawText(4, 43, buf, 0);
		
		switch(event.type) {
		case UI_EVENT_UPDOWN:
			new_settings->adc_voltage_gain += (new_settings->adc_voltage_gain * event.int_arg) / 500;
			break;
		default:
			break;
		}
	}
}

static void ui_calibrate_current(settings_t *new_settings) {
	Display_Clear(4, 0, 8, 160, 0);
	Display_DrawText(2, 0, " Adj. Current", 1);
	Display_DrawText(6, 38, FONT_GLYPH_ENTER ": Next", 0);

	set_current(CALIBRATION_CURRENT);
	
	ui_event event;
	char buf[8];
	int current;
	
	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1) {
		next_event(&event);
		
		current = (get_raw_current_usage() - new_settings->adc_current_offset) * new_settings->adc_current_gain;
		format_number(current, "A", buf);
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
}

// Calibrates the opamp and current DAC offsets.
// Run with a voltage source attached

void ui_calibration_progress(int current, int all) {
	Display_Clear(6, 16, 7, 16 + 129 * current / all, 0xFF);
}

static void ui_calibrate_dacs(settings_t *new_settings) {
	Display_Clear(2, 0, 8, 160, 0);
	Display_DrawText(3, 14, "Please wait", 0);
    
    // Draw a progress bar
    Display_Clear(6, 15, 7, 16, 0xFF);
	Display_Clear(6, 145, 7, 146, 0xFF);
    Display_Clear(6, 16, 7, 145, 0x81);
    calibrate_opamp_offset_trim(new_settings, CALIBRATION_CURRENT,ui_calibration_progress);
	calibrate_dacs(new_settings, CALIBRATION_CURRENT);
}

static state_func ui_calibrate(const void *arg) {
	set_current(0);
	
	settings_t new_settings;
	memcpy(&new_settings, settings, sizeof(settings_t));
	
	Display_ClearAll();
	Display_DrawText(0, 0, " CALIBRATION ", 1);
	
	ui_calibrate_offsets(&new_settings);
	ui_calibrate_voltage(&new_settings);
	ui_calibrate_current(&new_settings);
	ui_calibrate_dacs(&new_settings);
	
	EEPROM_Write((uint8*)&new_settings, (uint8*)settings, sizeof(settings_t));
	
	return (state_func){NULL, NULL, 0};
}

static state_func upgrade(const void *arg) {
#ifdef Bootloadable_START_BTLDR
    Display_ClearAll();
    Display_DrawText(0, 0, "UPGRADE MODE ", 1);
    Display_DrawText(4, 0, "Ready to recv", 0);
    Display_DrawText(6, 0, " f/w update  ", 0);
    Bootloadable_Load();  // Never returns...
#endif
    return (state_func){NULL, NULL, 0}; // ...yet, we should make compiler happy
}

void vTaskUI( void *pvParameters ) {
	ui_queue = xQueueCreate(2, sizeof(ui_event));

    button_timer = xTimerCreate((signed portCHAR *) "BUTTON", configTICK_RATE_HZ, pdFALSE, 0, button_timer_callback);
    
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
