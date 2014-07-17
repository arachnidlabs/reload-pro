/*******************************************************************************
* File Name: Backlight.c  
* Version 2.0
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
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
*  mode:  Change the pins to one of the following drive modes.
*
*  Backlight_DM_STRONG     Strong Drive 
*  Backlight_DM_OD_HI      Open Drain, Drives High 
*  Backlight_DM_OD_LO      Open Drain, Drives Low 
*  Backlight_DM_RES_UP     Resistive Pull Up 
*  Backlight_DM_RES_DWN    Resistive Pull Down 
*  Backlight_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Backlight_DM_DIG_HIZ    High Impedance Digital 
*  Backlight_DM_ALG_HIZ    High Impedance Analog 
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
