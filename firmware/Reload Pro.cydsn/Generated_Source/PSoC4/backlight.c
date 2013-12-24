/*******************************************************************************
* File Name: backlight.c  
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
#include "backlight.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        backlight_PC =   (backlight_PC & \
                                (uint32)(~(uint32)(backlight_DRIVE_MODE_IND_MASK << (backlight_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (backlight_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: backlight_Write
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
void backlight_Write(uint8 value) 
{
    uint8 drVal = (uint8)(backlight_DR & (uint8)(~backlight_MASK));
    drVal = (drVal | ((uint8)(value << backlight_SHIFT) & backlight_MASK));
    backlight_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: backlight_SetDriveMode
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
void backlight_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(backlight__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: backlight_Read
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
*  Macro backlight_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 backlight_Read(void) 
{
    return (uint8)((backlight_PS & backlight_MASK) >> backlight_SHIFT);
}


/*******************************************************************************
* Function Name: backlight_ReadDataReg
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
uint8 backlight_ReadDataReg(void) 
{
    return (uint8)((backlight_DR & backlight_MASK) >> backlight_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(backlight_INTSTAT) 

    /*******************************************************************************
    * Function Name: backlight_ClearInterrupt
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
    uint8 backlight_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(backlight_INTSTAT & backlight_MASK);
		backlight_INTSTAT = maskedStatus;
        return maskedStatus >> backlight_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
