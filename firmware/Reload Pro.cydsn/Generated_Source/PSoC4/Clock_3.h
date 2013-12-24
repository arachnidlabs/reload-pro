/*******************************************************************************
* File Name: Clock_3.h
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

#if !defined(CY_CLOCK_Clock_3_H)
#define CY_CLOCK_Clock_3_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void Clock_3_Start(void);
void Clock_3_Stop(void);

void Clock_3_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock_3_GetDividerRegister(void);
uint8  Clock_3_GetFractionalDividerRegister(void);

#define Clock_3_Enable()                         Clock_3_Start()
#define Clock_3_Disable()                        Clock_3_Stop()
#define Clock_3_SetDividerRegister(clkDivider, reset)  \
                        Clock_3_SetFractionalDividerRegister((clkDivider), 0u)
#define Clock_3_SetDivider(clkDivider)           Clock_3_SetDividerRegister((clkDivider), 1u)
#define Clock_3_SetDividerValue(clkDivider)      Clock_3_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/

#define Clock_3_DIV_REG    (*(reg32 *)Clock_3__REGISTER)
#define Clock_3_ENABLE_REG Clock_3_DIV_REG

#endif /* !defined(CY_CLOCK_Clock_3_H) */

/* [] END OF FILE */
