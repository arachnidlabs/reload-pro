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

	set_current(0);
	
	CY_SET_REG32(Opamp_cy_psoc4_abuf__OA_OFFSET_TRIM, settings->opamp_offset_trim);
}

void set_current(int setpoint) {
	if(setpoint < 0)
		setpoint = 0;
	state.current_setpoint = setpoint;

	setpoint -= settings->dac_offset;
	IDAC_High_SetValue(setpoint / settings->dac_high_gain);
	IDAC_Low_SetValue((setpoint % settings->dac_high_gain) / settings->dac_low_gain);
}

int get_current_setpoint() {
	return state.current_setpoint;
}

// Loads the splashscreen image
// ONLY RUN BEFORE STARTING THE RTOS KERNEL!
// (And after initializing the display)
#ifdef USE_SPLASHSCREEN
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

static output_mode current_output_mode = OUTPUT_MODE_FEEDBACK;

void set_output_mode(output_mode mode) {
	current_output_mode = mode;
	switch(mode) {
	case OUTPUT_MODE_OFF:
		// Stop the opamp and set the gate low 
		Opamp_Stop();
		Opamp_Out_Write(0);
		Opamp_Out_SetDriveMode(Opamp_Out_DM_STRONG);
		break;
	case OUTPUT_MODE_ON:
		// Stop the opamp and set the gate high
		Opamp_Stop();
		Opamp_Out_Write(1);
		Opamp_Out_SetDriveMode(Opamp_Out_DM_STRONG);
		break;
	case OUTPUT_MODE_FEEDBACK:
		// Start the opamp and set the pin to hi-z
		Opamp_Out_SetDriveMode(Opamp_Out_DM_ALG_HIZ);
		Opamp_Start();
		break;
	}
}

output_mode get_output_mode() {
	return current_output_mode;
}

/* [] END OF FILE */
