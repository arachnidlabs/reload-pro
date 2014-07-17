/*******************************************************************************
* File Name: opamp_pos_sense.c  
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
#include "opamp_pos_sense.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        opamp_pos_sense_PC =   (opamp_pos_sense_PC & \
                                (uint32)(~(uint32)(opamp_pos_sense_DRIVE_MODE_IND_MASK << (opamp_pos_sense_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (opamp_pos_sense_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: opamp_pos_sense_Write
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
void opamp_pos_sense_Write(uint8 value) 
{
    uint8 drVal = (uint8)(opamp_pos_sense_DR & (uint8)(~opamp_pos_sense_MASK));
    drVal = (drVal | ((uint8)(value << opamp_pos_sense_SHIFT) & opamp_pos_sense_MASK));
    opamp_pos_sense_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: opamp_pos_sense_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  opamp_pos_sense_DM_STRONG     Strong Drive 
*  opamp_pos_sense_DM_OD_HI      Open Drain, Drives High 
*  opamp_pos_sense_DM_OD_LO      Open Drain, Drives Low 
*  opamp_pos_sense_DM_RES_UP     Resistive Pull Up 
*  opamp_pos_sense_DM_RES_DWN    Resistive Pull Down 
*  opamp_pos_sense_DM_RES_UPDWN  Resistive Pull Up/Down 
*  opamp_pos_sense_DM_DIG_HIZ    High Impedance Digital 
*  opamp_pos_sense_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void opamp_pos_sense_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(opamp_pos_sense__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: opamp_pos_sense_Read
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
*  Macro opamp_pos_sense_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 opamp_pos_sense_Read(void) 
{
    return (uint8)((opamp_pos_sense_PS & opamp_pos_sense_MASK) >> opamp_pos_sense_SHIFT);
}


/*******************************************************************************
* Function Name: opamp_pos_sense_ReadDataReg
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
uint8 opamp_pos_sense_ReadDataReg(void) 
{
    return (uint8)((opamp_pos_sense_DR & opamp_pos_sense_MASK) >> opamp_pos_sense_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(opamp_pos_sense_INTSTAT) 

    /*******************************************************************************
    * Function Name: opamp_pos_sense_ClearInterrupt
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
    uint8 opamp_pos_sense_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(opamp_pos_sense_INTSTAT & opamp_pos_sense_MASK);
		opamp_pos_sense_INTSTAT = maskedStatus;
        return maskedStatus >> opamp_pos_sense_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
