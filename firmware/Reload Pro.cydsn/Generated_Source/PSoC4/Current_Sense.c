/*******************************************************************************
* File Name: Current_Sense.c  
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
#include "Current_Sense.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Current_Sense_PC =   (Current_Sense_PC & \
                                (uint32)(~(uint32)(Current_Sense_DRIVE_MODE_IND_MASK << (Current_Sense_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Current_Sense_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Current_Sense_Write
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
void Current_Sense_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Current_Sense_DR & (uint8)(~Current_Sense_MASK));
    drVal = (drVal | ((uint8)(value << Current_Sense_SHIFT) & Current_Sense_MASK));
    Current_Sense_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Current_Sense_SetDriveMode
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
void Current_Sense_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Current_Sense__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Current_Sense_Read
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
*  Macro Current_Sense_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Current_Sense_Read(void) 
{
    return (uint8)((Current_Sense_PS & Current_Sense_MASK) >> Current_Sense_SHIFT);
}


/*******************************************************************************
* Function Name: Current_Sense_ReadDataReg
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
uint8 Current_Sense_ReadDataReg(void) 
{
    return (uint8)((Current_Sense_DR & Current_Sense_MASK) >> Current_Sense_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Current_Sense_INTSTAT) 

    /*******************************************************************************
    * Function Name: Current_Sense_ClearInterrupt
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
    uint8 Current_Sense_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Current_Sense_INTSTAT & Current_Sense_MASK);
		Current_Sense_INTSTAT = maskedStatus;
        return maskedStatus >> Current_Sense_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
