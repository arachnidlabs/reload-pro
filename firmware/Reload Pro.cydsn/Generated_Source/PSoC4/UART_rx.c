/*******************************************************************************
* File Name: UART_rx.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "UART_rx.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        UART_rx_PC =   (UART_rx_PC & \
                                (uint32)(~(uint32)(UART_rx_DRIVE_MODE_IND_MASK << (UART_rx_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (UART_rx_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: UART_rx_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void UART_rx_Write(uint8 value) 
{
    uint8 drVal = (uint8)(UART_rx_DR & (uint8)(~UART_rx_MASK));
    drVal = (drVal | ((uint8)(value << UART_rx_SHIFT) & UART_rx_MASK));
    UART_rx_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: UART_rx_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void UART_rx_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(UART_rx__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: UART_rx_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro UART_rx_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 UART_rx_Read(void) 
{
    return (uint8)((UART_rx_PS & UART_rx_MASK) >> UART_rx_SHIFT);
}


/*******************************************************************************
* Function Name: UART_rx_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 UART_rx_ReadDataReg(void) 
{
    return (uint8)((UART_rx_DR & UART_rx_MASK) >> UART_rx_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(UART_rx_INTSTAT) 

    /*******************************************************************************
    * Function Name: UART_rx_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 UART_rx_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(UART_rx_INTSTAT & UART_rx_MASK);
		UART_rx_INTSTAT = maskedStatus;
        return maskedStatus >> UART_rx_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
