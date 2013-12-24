/*******************************************************************************
* File Name: Clock_2.h
* Version 2.10
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

#if !defined(CY_CLOCK_Clock_2_H)
#define CY_CLOCK_Clock_2_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void Clock_2_Start(void);
void Clock_2_Stop(void);

void Clock_2_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock_2_GetDividerRegister(void);
uint8  Clock_2_GetFractionalDividerRegister(void);

#define Clock_2_Enable()                         Clock_2_Start()
#define Clock_2_Disable()                        Clock_2_Stop()
#define Clock_2_SetDividerRegister(clkDivider, reset)  \
                        Clock_2_SetFractionalDividerRegister((clkDivider), 0u)
#define Clock_2_SetDivider(clkDivider)           Clock_2_SetDividerRegister((clkDivider), 1u)
#define Clock_2_SetDividerValue(clkDivider)      Clock_2_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/

#define Clock_2_DIV_REG    (*(reg32 *)Clock_2__REGISTER)
#define Clock_2_ENABLE_REG Clock_2_DIV_REG

#endif /* !defined(CY_CLOCK_Clock_2_H) */

/* [] END OF FILE */
