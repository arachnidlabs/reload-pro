/*******************************************************************************
* File Name: Pin_3.c  
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
#include "Pin_3.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Pin_3_PC =   (Pin_3_PC & \
                                (uint32)(~(uint32)(Pin_3_DRIVE_MODE_IND_MASK << (Pin_3_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Pin_3_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Pin_3_Write
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
void Pin_3_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Pin_3_DR & (uint8)(~Pin_3_MASK));
    drVal = (drVal | ((uint8)(value << Pin_3_SHIFT) & Pin_3_MASK));
    Pin_3_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Pin_3_SetDriveMode
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
void Pin_3_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Pin_3__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Pin_3_Read
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
*  Macro Pin_3_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin_3_Read(void) 
{
    return (uint8)((Pin_3_PS & Pin_3_MASK) >> Pin_3_SHIFT);
}


/*******************************************************************************
* Function Name: Pin_3_ReadDataReg
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
uint8 Pin_3_ReadDataReg(void) 
{
    return (uint8)((Pin_3_DR & Pin_3_MASK) >> Pin_3_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin_3_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin_3_ClearInterrupt
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
    uint8 Pin_3_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Pin_3_INTSTAT & Pin_3_MASK);
		Pin_3_INTSTAT = maskedStatus;
        return maskedStatus >> Pin_3_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
