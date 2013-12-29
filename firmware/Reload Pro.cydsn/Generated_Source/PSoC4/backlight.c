/*******************************************************************************
* File Name: Backlight.c  
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
#include "Backlight.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Backlight_PC =   (Backlight_PC & \
                                (uint32)(~(uint32)(Backlight_DRIVE_MODE_IND_MASK << (Backlight_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Backlight_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Backlight_Write
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
void Backlight_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Backlight_DR & (uint8)(~Backlight_MASK));
    drVal = (drVal | ((uint8)(value << Backlight_SHIFT) & Backlight_MASK));
    Backlight_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Backlight_SetDriveMode
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
void Backlight_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Backlight__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Backlight_Read
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
*  Macro Backlight_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Backlight_Read(void) 
{
    return (uint8)((Backlight_PS & Backlight_MASK) >> Backlight_SHIFT);
}


/*******************************************************************************
* Function Name: Backlight_ReadDataReg
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
uint8 Backlight_ReadDataReg(void) 
{
    return (uint8)((Backlight_DR & Backlight_MASK) >> Backlight_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Backlight_INTSTAT) 

    /*******************************************************************************
    * Function Name: Backlight_ClearInterrupt
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
    uint8 Backlight_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Backlight_INTSTAT & Backlight_MASK);
		Backlight_INTSTAT = maskedStatus;
        return maskedStatus >> Backlight_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
