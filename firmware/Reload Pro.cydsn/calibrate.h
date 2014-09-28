#ifndef CALIBRATE_H
#define CALIBRATE_H
	
#include "config.h"

void calibrate_offsets(settings_t *settings);
void calibrate_voltage(settings_t *settings, int microvolts);
void calibrate_current(settings_t *settings, int microamps);
void calibrate_dacs(settings_t *settings, int microamps);
void set_opamp_offset_trim(settings_t *settings_t, int trim);

#endif
