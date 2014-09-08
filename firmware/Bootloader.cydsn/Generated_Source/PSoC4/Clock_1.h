/*******************************************************************************
* File Name: Clock_1.h
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

#if !defined(CY_CLOCK_Clock_1_H)
#define CY_CLOCK_Clock_1_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void Clock_1_Start(void);
void Clock_1_Stop(void);

void Clock_1_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock_1_GetDividerRegister(void);
uint8  Clock_1_GetFractionalDividerRegister(void);

#define Clock_1_Enable()                         Clock_1_Start()
#define Clock_1_Disable()                        Clock_1_Stop()
#define Clock_1_SetDividerRegister(clkDivider, reset)  \
                        Clock_1_SetFractionalDividerRegister((clkDivider), 0u)
#define Clock_1_SetDivider(clkDivider)           Clock_1_SetDividerRegister((clkDivider), 1u)
#define Clock_1_SetDividerValue(clkDivider)      Clock_1_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/

#define Clock_1_DIV_REG    (*(reg32 *)Clock_1__REGISTER)
#define Clock_1_ENABLE_REG Clock_1_DIV_REG

#endif /* !defined(CY_CLOCK_Clock_1_H) */

/* [] END OF FILE */
