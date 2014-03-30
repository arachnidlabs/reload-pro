/*******************************************************************************
* File Name: ADC_SAR_Seq_1_intClock.h
* Version 2.0
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_ADC_SAR_Seq_1_intClock_H)
#define CY_CLOCK_ADC_SAR_Seq_1_intClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void ADC_SAR_Seq_1_intClock_Start(void);
void ADC_SAR_Seq_1_intClock_Stop(void);

void ADC_SAR_Seq_1_intClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ADC_SAR_Seq_1_intClock_GetDividerRegister(void);
uint8  ADC_SAR_Seq_1_intClock_GetFractionalDividerRegister(void);

#define ADC_SAR_Seq_1_intClock_Enable()                         ADC_SAR_Seq_1_intClock_Start()
#define ADC_SAR_Seq_1_intClock_Disable()                        ADC_SAR_Seq_1_intClock_Stop()
#define ADC_SAR_Seq_1_intClock_SetDividerRegister(clkDivider, reset)  \
                        ADC_SAR_Seq_1_intClock_SetFractionalDividerRegister((clkDivider), 0)
#define ADC_SAR_Seq_1_intClock_SetDivider(clkDivider)           ADC_SAR_Seq_1_intClock_SetDividerRegister((clkDivider), 1)
#define ADC_SAR_Seq_1_intClock_SetDividerValue(clkDivider)      ADC_SAR_Seq_1_intClock_SetDividerRegister((clkDivider) - 1, 1)


/***************************************
*             Registers
***************************************/

#define ADC_SAR_Seq_1_intClock_DIV_REG    (*(reg32 *)ADC_SAR_Seq_1_intClock__REGISTER)
#define ADC_SAR_Seq_1_intClock_ENABLE_REG ADC_SAR_Seq_1_intClock_DIV_REG

#endif /* !defined(CY_CLOCK_ADC_SAR_Seq_1_intClock_H) */

/* [] END OF FILE */
