#include <project.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "tasks.h"
#include "config.h"
#include "splashscreen.h"

state_t state;
xTaskHandle adc_task;
xTaskHandle comms_task;
xTaskHandle ui_task;

const settings_t default_settings = {
    .settings_version = 0x03,
    
	.dac_low_gain = DEFAULT_DAC_LOW_GAIN,
	.dac_high_gain = DEFAULT_DAC_HIGH_GAIN,
	.dac_offset = DEFAULT_DAC_OFFSET,
	.opamp_offset_trim = DEFAULT_OPAMP_OFFSET_TRIM,
	
	.adc_current_offset = DEFAULT_ADC_CURRENT_OFFSET,
	.adc_current_gain = DEFAULT_ADC_CURRENT_GAIN,
	
	.adc_voltage_offset = DEFAULT_ADC_VOLTAGE_OFFSET,
	.adc_voltage_gain = DEFAULT_ADC_VOLTAGE_GAIN,
	
	.backlight_brightness = 32,
	.lcd_contrast = 26,
    
    .display_settings = {
        .named = {
            .cc = {
		        .readouts = {READOUT_CURRENT_SETPOINT, READOUT_CURRENT_USAGE, READOUT_VOLTAGE},
	        },
        },
    },
	
    .voltage_correction_ratio = DEFAULT_VOLTAGE_CORRECTION_RATIO,
};

void factory_reset() {
    EEPROM_Write((const uint8*)&default_settings, (const uint8*)settings, sizeof(settings_t));
}

#ifdef Bootloadable_START_BTLDR
const settings_t *settings = (settings_t*)0x00000B80;
#else
static const settings_t settings_data = {.settings_version = 0};
const settings_t *settings = &settings_data;
#endif

void prvHardwareSetup();

void main()
{
    CyGlobalIntEnable;

#if USE_WATCHDOG
    // Enable watchdog timer for every 2 seconds
    CySysWdtWriteMode(0, CY_SYS_WDT_MODE_RESET);
    CySysWdtWriteMatch(0, 0xFFFF);
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
#endif

    if(settings->settings_version < default_settings.settings_version)
        factory_reset();

    Backlight_Write(1);
	
	disp_reset_Write(0);
	CyDelayUs(10);
	disp_reset_Write(1);
	CyDelayUs(10);
	Display_Start();
	Display_SetContrast(settings->lcd_contrast);
	
	#ifdef USE_SPLASHSCREEN
	load_splashscreen();
	#endif
	

	IDAC_High_Start();
	IDAC_Low_Start();
    state.calibrating = 0;
    set_current(0);
	set_output_mode(OUTPUT_MODE_FEEDBACK);
		
	start_adc();

	setup();
	
	xTaskCreate(vTaskUI, (signed portCHAR *) "UI", 178, NULL, tskIDLE_PRIORITY + 2, &ui_task);
	xTaskCreate(vTaskComms, (signed portCHAR *) "UART", 160, NULL, tskIDLE_PRIORITY + 2, &comms_task);
	
	prvHardwareSetup();
	vTaskStartScheduler();
}

/* ---------------------------------------------------------------------------
 * FreeRTOS support and configuration functions
 * --------------------------------------------------------------------------- */

void prvHardwareSetup( void )
{
	/* Port layer functions that need to be copied into the vector table. */
	extern void xPortPendSVHandler( void );
	extern void xPortSysTickHandler( void );
	extern void vPortSVCHandler( void );
	extern cyisraddress CyRamVectors[];

	/* Install the OS Interrupt Handlers. */
	CyRamVectors[ 11 ] = ( cyisraddress ) vPortSVCHandler;
	CyRamVectors[ 14 ] = ( cyisraddress ) xPortPendSVHandler;
	CyRamVectors[ 15 ] = ( cyisraddress ) xPortSysTickHandler;
}

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	/* The stack space has been execeeded for a task, considering allocating more. */
	taskDISABLE_INTERRUPTS();
	for( ;; ) {
        Backlight_Write(0);
        CyDelay(500);
        Backlight_Write(1);
        CyDelay(500);
    }
}

void vApplicationMallocFailedHook( void )
{
	/* The heap space has been execeeded. */
	taskDISABLE_INTERRUPTS();
	for( ;; ){
        Backlight_Write(0);
        CyDelay(2000);
        Backlight_Write(1);
        CyDelay(2000);
    }
}

/* [] END OF FILE */
