#ifndef CALIBRATE_H
#define CALIBRATE_H
	
#include "config.h"

void calibrate_offsets(settings_t *newsettings);
void calibrate_voltage(settings_t *newsettings, int microvolts);
void calibrate_current(settings_t *newsettings, int microamps);
void calibrate_opamp_offset_trim(settings_t *newsettings, int microamps,void (*progress_callback)(int,int));
void calibrate_dacs(settings_t *newsettings, int microamps);
void set_opamp_offset_trim(settings_t *newsettings, int trim);

#define MAX_OA_OFFSET_STEPS 64

#endif
