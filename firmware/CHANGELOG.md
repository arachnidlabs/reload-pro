# Release Notes

## v1.8
 - Expanded opamp offset calibration range to 0-63
 - Output current setpoint over serial in response to UI actions (#19)
 - Add range checking for 'set' command (#38)
 - Progress bar for final calibration step

## v1.7
 - Fixed bug in calibration routine that caused crashes
 - Added 'cal t' command

## v1.6
 - Rewrote opamp offset calibration routine to use measured output values
 - Added 'cal O' command

## v1.5
 - Substantially improved calibration routine
 - Software feedback loop so set vs actual current tracks better

## v1.4
 - Improved display layout
 - Fixed display initialisation issues in some units
 - Undervoltage cutoff for discharging batteries

## v1.3
 - Minor bugfixes identified during production run

## v1.0
 - First production release

## v0.13
 - Fixed some calibration issues.
 - Fixed an issue with some units drawing max current after being set to 0 post-calibration.
 - Implemented overtemperature shutdown detection and reset.
 - Implemented watchdog timer to automatically reset firmware if the UI task locks up.
 - Implemented factory reset
 - Fixed watt hour readout

## v0.12
 - Fixed boot issues in v0.1.1

## v0.11
 - Fixed bug causing the Re:load Pro to stop at the bootloader after display settings have been changed
 - Added version number to bootup splashscreen
 - Improved button debounce