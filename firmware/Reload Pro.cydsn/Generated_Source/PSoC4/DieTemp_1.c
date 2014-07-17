/*******************************************************************************
* File Name: DieTemp_1.c
* Version 1.0
*
* Description:
*  This file provides the source code of APIs for the DieTemp_P4 component.
*
*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DieTemp_1.h"


/*******************************************************************************
* Function Name: DieTemp_1_CountsTo_Celsius
********************************************************************************
*
* Summary:
*  Converts the ADC output to degrees Celsius.
*
* Parameters:
*  int32 adcCounts:
*   Result from the ADC Conversion
*
* Return:
*  Temperature in degrees Celsius
*
* Global variables:
*  None
*
*******************************************************************************/
int32 DieTemp_1_CountsTo_Celsius(int32 adcCounts)
{
    int32 tempCelsius;
    int32 tInitial;
    int32 tAdjust;
    int32 offsetReg;
    int32 multReg;

    offsetReg = (int16)DieTemp_1_SAR_TEMP_OFFSET_REG;
    multReg   = (int16)DieTemp_1_SAR_TEMP_MULTIPLIER_REG;
    /* Calculate tInitial in Q16.16 */
    tInitial = (adcCounts * multReg) + (offsetReg * DieTemp_1_SAR_TEMP_OFFSET_MULT);

    if(tInitial >= DieTemp_1_DUAL_SLOPE_CORRECTION)
    {
        /* Shift (100 - tInitial) by 4 bits to prevent scale-adjustment from overflowing. */
        /* Then divide by the integer bits of (100 - cutoff) to end up with a Q16.16 tAdjust */
        tAdjust = (DieTemp_1_SCALE_ADJUSTMENT * (((int32)DieTemp_1_HIGH_TEMPERATURE - tInitial)
            / (int32)DieTemp_1_SCALE_ADJUSTMENT_DIVIDER)) /
            (((int32)DieTemp_1_HIGH_TEMPERATURE - (int32)DieTemp_1_DUAL_SLOPE_CORRECTION) /
            DieTemp_1_SAR_TEMP_DIVIDER);
    }
    else
    {
        /* Shift (40 + tInitial) by 4 bits to prevent scale-adjustment from overflowing. */
        /* Then divide by the integer bits of (40 + cutoff) to end up with a Q16.16 tAdjust */
        tAdjust = ((int32)DieTemp_1_SCALE_ADJUSTMENT * (((int32)DieTemp_1_LOW_TEMPERATURE + tInitial)
           / (int32)DieTemp_1_SCALE_ADJUSTMENT_DIVIDER)) /
            (((int32)DieTemp_1_LOW_TEMPERATURE + (int32)DieTemp_1_DUAL_SLOPE_CORRECTION) /
            (int32)DieTemp_1_SAR_TEMP_DIVIDER);
    }

    /* Add tInitial + tAdjust + 0.5 to round to nearest int. Shift off frac bits, and return. */
    tempCelsius = tInitial + tAdjust + DieTemp_1_HALF_OF_ONE;

    return (tempCelsius / DieTemp_1_SAR_TEMP_OFFSET_DIVIDER);
}


/* [] END OF FILE */
