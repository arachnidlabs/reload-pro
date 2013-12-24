/*******************************************************************************
* File Name: UART_Clock.h
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

#if !defined(CY_CLOCK_UART_Clock_H)
#define CY_CLOCK_UART_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void UART_Clock_Start(void);
void UART_Clock_Stop(void);

void UART_Clock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 UART_Clock_GetDividerRegister(void);
uint8  UART_Clock_GetFractionalDividerRegister(void);

#define UART_Clock_Enable()                         UART_Clock_Start()
#define UART_Clock_Disable()                        UART_Clock_Stop()
#define UART_Clock_SetDividerRegister(clkDivider, reset)  \
                        UART_Clock_SetFractionalDividerRegister((clkDivider), 0u)
#define UART_Clock_SetDivider(clkDivider)           UART_Clock_SetDividerRegister((clkDivider), 1u)
#define UART_Clock_SetDividerValue(clkDivider)      UART_Clock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/

#define UART_Clock_DIV_REG    (*(reg32 *)UART_Clock__REGISTER)
#define UART_Clock_ENABLE_REG UART_Clock_DIV_REG

#endif /* !defined(CY_CLOCK_UART_Clock_H) */

/* [] END OF FILE */
