/*******************************************************************************
* File Name: QuadButton.c  
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
#include "QuadButton.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        QuadButton_PC =   (QuadButton_PC & \
                                (uint32)(~(uint32)(QuadButton_DRIVE_MODE_IND_MASK << (QuadButton_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (QuadButton_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: QuadButton_Write
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
void QuadButton_Write(uint8 value) 
{
    uint8 drVal = (uint8)(QuadButton_DR & (uint8)(~QuadButton_MASK));
    drVal = (drVal | ((uint8)(value << QuadButton_SHIFT) & QuadButton_MASK));
    QuadButton_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: QuadButton_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  QuadButton_DM_STRONG     Strong Drive 
*  QuadButton_DM_OD_HI      Open Drain, Drives High 
*  QuadButton_DM_OD_LO      Open Drain, Drives Low 
*  QuadButton_DM_RES_UP     Resistive Pull Up 
*  QuadButton_DM_RES_DWN    Resistive Pull Down 
*  QuadButton_DM_RES_UPDWN  Resistive Pull Up/Down 
*  QuadButton_DM_DIG_HIZ    High Impedance Digital 
*  QuadButton_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void QuadButton_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(QuadButton__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: QuadButton_Read
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
*  Macro QuadButton_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 QuadButton_Read(void) 
{
    return (uint8)((QuadButton_PS & QuadButton_MASK) >> QuadButton_SHIFT);
}


/*******************************************************************************
* Function Name: QuadButton_ReadDataReg
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
uint8 QuadButton_ReadDataReg(void) 
{
    return (uint8)((QuadButton_DR & QuadButton_MASK) >> QuadButton_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(QuadButton_INTSTAT) 

    /*******************************************************************************
    * Function Name: QuadButton_ClearInterrupt
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
    uint8 QuadButton_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(QuadButton_INTSTAT & QuadButton_MASK);
		QuadButton_INTSTAT = maskedStatus;
        return maskedStatus >> QuadButton_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
