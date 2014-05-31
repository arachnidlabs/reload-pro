/*******************************************************************************
* File Name: UART_Clock.h
* Version 2.20
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
#if defined CYREG_PERI_DIV_CMD

void UART_Clock_StartEx(uint32 alignClkDiv);
#define UART_Clock_Start() \
    UART_Clock_StartEx(UART_Clock__PA_DIV_ID)

#else

void UART_Clock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

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
#if defined CYREG_PERI_DIV_CMD

#define UART_Clock_DIV_ID     UART_Clock__DIV_ID

#define UART_Clock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define UART_Clock_CTRL_REG   (*(reg32 *)UART_Clock__CTRL_REGISTER)
#define UART_Clock_DIV_REG    (*(reg32 *)UART_Clock__DIV_REGISTER)

#define UART_Clock_CMD_DIV_SHIFT          (0u)
#define UART_Clock_CMD_PA_DIV_SHIFT       (8u)
#define UART_Clock_CMD_DISABLE_SHIFT      (30u)
#define UART_Clock_CMD_ENABLE_SHIFT       (31u)

#define UART_Clock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << UART_Clock_CMD_DISABLE_SHIFT))
#define UART_Clock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << UART_Clock_CMD_ENABLE_SHIFT))

#define UART_Clock_DIV_FRAC_MASK  (0x000000F8u)
#define UART_Clock_DIV_FRAC_SHIFT (3u)
#define UART_Clock_DIV_INT_MASK   (0xFFFFFF00u)
#define UART_Clock_DIV_INT_SHIFT  (8u)

#else 

#define UART_Clock_DIV_REG        (*(reg32 *)UART_Clock__REGISTER)
#define UART_Clock_ENABLE_REG     UART_Clock_DIV_REG
#define UART_Clock_DIV_FRAC_MASK  UART_Clock__FRAC_MASK
#define UART_Clock_DIV_FRAC_SHIFT (16u)
#define UART_Clock_DIV_INT_MASK   UART_Clock__DIVIDER_MASK
#define UART_Clock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_UART_Clock_H) */

/* [] END OF FILE */
