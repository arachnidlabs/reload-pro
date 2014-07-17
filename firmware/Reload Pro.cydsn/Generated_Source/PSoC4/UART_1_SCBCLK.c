/*******************************************************************************
* File Name: UART_1_SCBCLK.c
* Version 2.0
*
*  Description:
*   Provides system API for the clocking, interrupts and watchdog timer.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <cydevice_trm.h>
#include "UART_1_SCBCLK.h"


/*******************************************************************************
* Function Name: UART_1_SCBCLK_Start
********************************************************************************
*
* Summary:
*  Starts the clock.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/
void UART_1_SCBCLK_Start(void)
{
    /* Set the bit to enable the clock. */
    UART_1_SCBCLK_ENABLE_REG |= UART_1_SCBCLK__ENABLE_MASK;
}


/*******************************************************************************
* Function Name: UART_1_SCBCLK_Stop
********************************************************************************
*
* Summary:
*  Stops the clock and returns immediately. This API does not require the
*  source clock to be running but may return before the hardware is actually
*  disabled.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/
void UART_1_SCBCLK_Stop(void)
{
    /* Clear the bit to disable the clock. */
    UART_1_SCBCLK_ENABLE_REG &= (uint32)(~UART_1_SCBCLK__ENABLE_MASK);
}


/*******************************************************************************
* Function Name: UART_1_SCBCLK_SetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Modifies the clock divider and the fractional divider.
*
* Parameters:
*  clkDivider:  Divider register value (0-65535). This value is NOT the
*    divider; the clock hardware divides by clkDivider plus one. For example,
*    to divide the clock by 2, this parameter should be set to 1.
*  fracDivider:  Fractional Divider register value (0-31).
* Returns:
*  None
*
*******************************************************************************/
void UART_1_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional)
{
#if defined (UART_1_SCBCLK__FRAC_MASK)
	/* get all but divider bits */
    uint32 maskVal = UART_1_SCBCLK_DIV_REG & 
                    (uint32)(~(UART_1_SCBCLK__DIVIDER_MASK | UART_1_SCBCLK__FRAC_MASK)); 
	/* combine mask and new divider val into 32-bit value */
    uint32 regVal = clkDivider | (((uint32)clkFractional << 16) & UART_1_SCBCLK__FRAC_MASK) | maskVal;
#else
    /* get all but integer divider bits */
    uint32 maskVal = UART_1_SCBCLK_DIV_REG & (uint32)(~(uint32)UART_1_SCBCLK__DIVIDER_MASK);
    /* combine mask and new divider val into 32-bit value */
    uint32 regVal = clkDivider | maskVal;
#endif /* UART_1_SCBCLK__FRAC_MASK */

	UART_1_SCBCLK_DIV_REG = regVal;
}


/*******************************************************************************
* Function Name: UART_1_SCBCLK_GetDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Divide value of the clock minus 1. For example, if the clock is set to
*  divide by 2, the return value will be 1.
*
*******************************************************************************/
uint16 UART_1_SCBCLK_GetDividerRegister(void)
{
    return (uint16)UART_1_SCBCLK_DIV_REG;
}


/*******************************************************************************
* Function Name: UART_1_SCBCLK_GetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock fractional divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Fractional Divide value of the clock
*  0 if the fractional divider is not in use.
*
*******************************************************************************/
uint8 UART_1_SCBCLK_GetFractionalDividerRegister(void)
{
#if defined (UART_1_SCBCLK__FRAC_MASK)
    /* get fractional divider bits */
    uint32 maskVal = UART_1_SCBCLK_DIV_REG & UART_1_SCBCLK__FRAC_MASK;
    return (maskVal >> 16);
#else
    return 0u;
#endif /* UART_1_SCBCLK__FRAC_MASK */
}


/* [] END OF FILE */
