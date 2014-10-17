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

#include <project.h>

#ifndef CONFIG_H
#define CONFIG_H

typedef enum {
	ADC_CHAN_CURRENT_SENSE = 0,
	ADC_CHAN_VOLTAGE_SENSE = 1,
	ADC_CHAN_OPAMP_OUT = 2,
	ADC_CHAN_FET_IN = 3,
	ADC_CHAN_TEMP = 4,
	ADC_CHAN_CURRENT_SET = 5,
} adc_channel;

#define UI_TASK_FREQUENCY 2 // hz

#define USE_WATCHDOG 0

// How much does one encoder detent adjust the current?
#define CURRENT_STEP 10000 // 10mA
#define ENCODER_ACCEL_CONSTANT 400 // Defines the encoder acceleration speed; if steps are closer than 350ms, increase the rate of change

// Current induces voltage drop in the wires.
// This correction factor offsets that to get the correct voltage across the terminals.
// Expressed in 1024ths
#define VOLTAGE_CORRECTION_RATIO 40 // 51/1024 = ~0.05 ohms

// What's the maximum current?
#define CURRENT_MAX 6000000 // 6A
#define VOLTAGE_MAX 60000000 // 60 volts

#define DEFAULT_DAC_HIGH_GAIN		21157//23718	// 1.2uA over 996 ohms, 0.05 ohm shunt = 23.718 milliamps per count
#define DEFAULT_DAC_LOW_GAIN		186		// 1.2uA over 996 ohms, 0.05 ohm shunt = 0.186 milliamps per count
#define DEFAULT_OPAMP_OFFSET_TRIM	0x24
#define DEFAULT_DAC_OFFSET			0
#define DEFAULT_ADC_CURRENT_OFFSET	0
#define DEFAULT_ADC_CURRENT_GAIN 	599		// 1.024 volts / (1 microamp * 0.05 ohms) / 2048 / 16 = 625 microamps per count
#define DEFAULT_ADC_VOLTAGE_OFFSET	0		
#define DEFAULT_ADC_VOLTAGE_GAIN	2008	// 1.024 volts / (1 microvolt * (5.23 kiloohms / 205.23 kiloohms)) / 2048 / 16 = 1226 microvolts per count

#define ADC_MIX_RATIO 4 // 1 / 2^4 = 6.25%

#define DAC_EC_FEEDBACK
#define DAC_EC_MIX_RATIO 2
#define MAX_DAC_EC 100000

extern uint8 adc_mix_ratio;

#ifndef DEBUG
// No splashscreen in debug builds
#define USE_SPLASHSCREEN 1
#endif

typedef struct {
	int current_setpoint;
    int lower_voltage_limit;
    uint8_t calibrating;
} state_t;

extern state_t state;

typedef enum {
	READOUT_NONE = 0,
	READOUT_CURRENT_SETPOINT = 1,
	READOUT_CURRENT_USAGE = 2,
	READOUT_VOLTAGE = 3,
	READOUT_POWER = 4,
	READOUT_RESISTANCE = 5,
	READOUT_TOTAL_CURRENT = 6,
	READOUT_TOTAL_POWER = 7,
} readout_function;

// Configuration for one display readout
typedef struct {
		const readout_function readouts[3];
} display_config_t;

// Configuration for all displays
typedef union {
	struct {
        display_config_t cc;
    } named;
    display_config_t numbered[1];
} display_settings_t;

typedef struct {
    uint8_t settings_version;
    
	int dac_low_gain;		// Microamps per DAC count
	int dac_high_gain;		// Microamps per DAC count
	int dac_offset;			// Microamps
	int opamp_offset_trim;	// Offset trim value for opamp
	
	int adc_current_offset;	// ADC current reading offset in counts
	int adc_current_gain;	// Microamps per ADC count
	
	int adc_voltage_offset;	// ADC voltage reading offset in counts
	int adc_voltage_gain;	// Microvolts per ADC count
	
	int backlight_brightness; // 0-63
	int lcd_contrast; // 0-63
    
    display_settings_t display_settings;
} settings_t;

extern const settings_t *settings;

void set_current(int setpoint);
int get_current_setpoint();
int16 get_raw_current_usage();
int get_current_usage();
int16 get_raw_voltage();
int get_voltage();
int get_power();
int get_microamp_hours();
int get_microwatt_hours();
int get_dac_offset_correction();
void reset_running_totals();
void factory_reset();
uint8 get_minor_version();
uint8 get_major_version();

typedef enum {
	OUTPUT_MODE_OFF,
	OUTPUT_MODE_ON,
	OUTPUT_MODE_FEEDBACK,
} output_mode;

void set_output_mode(output_mode);
output_mode get_output_mode();

void setup();

#endif
/* [] END OF FILE */
