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
#include <stdio.h>
#include "config.h"

#ifdef USE_SPLASHSCREEN
#include "splashscreen.h"
#include "lzfx.h"
#endif

void setup() {
	state.current_setpoint = -1;
	state.current_range = -1;

	set_current_range(0);
	set_current(0);
	
	CY_SET_REG32(Opamp_cy_psoc4_abuf__OA_OFFSET_TRIM, settings->opamp_offset_trim);
}

void set_current_range(int8 range) {
	if(state.current_range != range) {
		IDAC_Mux_Select(range);
		Opamp_Mux_Select(range);
		state.current_range = range;
		set_current(state.current_setpoint);
	}
}

void set_current(int setpoint) {
	if(setpoint < 0) {
		setpoint = 0;
	} else if(state.current_range == 0) {
		if(setpoint > CURRENT_LOWRANGE_MAX) {
			setpoint = CURRENT_LOWRANGE_MAX;
		} else {
			setpoint -= setpoint % CURRENT_LOWRANGE_STEP;
		}
	} else if(state.current_range == 1) {
		if(setpoint > CURRENT_FULLRANGE_MAX) {
			setpoint = CURRENT_FULLRANGE_MAX;
		} else {
			setpoint -= setpoint % CURRENT_FULLRANGE_STEP;
		}
	}
	
	IDAC_SetValue(setpoint / settings->dac_gains[state.current_range] - settings->dac_offsets[state.current_range]);
	state.current_setpoint = setpoint;
}

int get_current_setpoint() {
	return state.current_setpoint;
}

// Loads the splashscreen image
// ONLY RUN BEFORE STARTING THE RTOS KERNEL!
// (And after initializing the display)
#ifdef USE_SPLAHSCREEN
void load_splashscreen() {
	uint8 *page = pvPortMalloc(160 * 4);
	Display_SetCursorPosition(0, 0);
	for(int i = 0; i < 8; i++) {
		lzfx_decompress(
			splashscreen_data + splashscreen_indexes[i],
			splashscreen_indexes[i + 1] - splashscreen_indexes[i],
			page, &(unsigned int){160 * 4});
		Display_WritePixels(page, 160 * 4);
		CyDelay(1);
	}

	// Reset the heap to free the memory we used
	vPortInitialiseBlocks();
}
#endif

/* [] END OF FILE */
