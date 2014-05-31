#ifndef CALIBRATE_H
#define CALIBRATE_H
	
#include "config.h"

void calibrate_offsets(settings_t *settings);
void calibrate_voltage(settings_t *settings, int microvolts);
void calibrate_current(settings_t *settings, int microamps);
void calibrate_dacs(settings_t *settings, int microamps);

#endif
