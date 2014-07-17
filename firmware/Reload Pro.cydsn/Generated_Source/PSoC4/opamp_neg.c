/*******************************************************************************
* File Name: opamp_neg.c  
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
#include "opamp_neg.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        opamp_neg_PC =   (opamp_neg_PC & \
                                (uint32)(~(uint32)(opamp_neg_DRIVE_MODE_IND_MASK << (opamp_neg_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (opamp_neg_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: opamp_neg_Write
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
void opamp_neg_Write(uint8 value) 
{
    uint8 drVal = (uint8)(opamp_neg_DR & (uint8)(~opamp_neg_MASK));
    drVal = (drVal | ((uint8)(value << opamp_neg_SHIFT) & opamp_neg_MASK));
    opamp_neg_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: opamp_neg_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  opamp_neg_DM_STRONG     Strong Drive 
*  opamp_neg_DM_OD_HI      Open Drain, Drives High 
*  opamp_neg_DM_OD_LO      Open Drain, Drives Low 
*  opamp_neg_DM_RES_UP     Resistive Pull Up 
*  opamp_neg_DM_RES_DWN    Resistive Pull Down 
*  opamp_neg_DM_RES_UPDWN  Resistive Pull Up/Down 
*  opamp_neg_DM_DIG_HIZ    High Impedance Digital 
*  opamp_neg_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void opamp_neg_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(opamp_neg__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: opamp_neg_Read
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
*  Macro opamp_neg_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 opamp_neg_Read(void) 
{
    return (uint8)((opamp_neg_PS & opamp_neg_MASK) >> opamp_neg_SHIFT);
}


/*******************************************************************************
* Function Name: opamp_neg_ReadDataReg
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
uint8 opamp_neg_ReadDataReg(void) 
{
    return (uint8)((opamp_neg_DR & opamp_neg_MASK) >> opamp_neg_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(opamp_neg_INTSTAT) 

    /*******************************************************************************
    * Function Name: opamp_neg_ClearInterrupt
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
    uint8 opamp_neg_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(opamp_neg_INTSTAT & opamp_neg_MASK);
		opamp_neg_INTSTAT = maskedStatus;
        return maskedStatus >> opamp_neg_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
