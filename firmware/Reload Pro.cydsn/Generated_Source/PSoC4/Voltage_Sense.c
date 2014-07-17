/*******************************************************************************
* File Name: Voltage_Sense.c  
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
#include "Voltage_Sense.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Voltage_Sense_PC =   (Voltage_Sense_PC & \
                                (uint32)(~(uint32)(Voltage_Sense_DRIVE_MODE_IND_MASK << (Voltage_Sense_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Voltage_Sense_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Voltage_Sense_Write
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
void Voltage_Sense_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Voltage_Sense_DR & (uint8)(~Voltage_Sense_MASK));
    drVal = (drVal | ((uint8)(value << Voltage_Sense_SHIFT) & Voltage_Sense_MASK));
    Voltage_Sense_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Voltage_Sense_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Voltage_Sense_DM_STRONG     Strong Drive 
*  Voltage_Sense_DM_OD_HI      Open Drain, Drives High 
*  Voltage_Sense_DM_OD_LO      Open Drain, Drives Low 
*  Voltage_Sense_DM_RES_UP     Resistive Pull Up 
*  Voltage_Sense_DM_RES_DWN    Resistive Pull Down 
*  Voltage_Sense_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Voltage_Sense_DM_DIG_HIZ    High Impedance Digital 
*  Voltage_Sense_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Voltage_Sense_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Voltage_Sense__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Voltage_Sense_Read
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
*  Macro Voltage_Sense_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Voltage_Sense_Read(void) 
{
    return (uint8)((Voltage_Sense_PS & Voltage_Sense_MASK) >> Voltage_Sense_SHIFT);
}


/*******************************************************************************
* Function Name: Voltage_Sense_ReadDataReg
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
uint8 Voltage_Sense_ReadDataReg(void) 
{
    return (uint8)((Voltage_Sense_DR & Voltage_Sense_MASK) >> Voltage_Sense_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Voltage_Sense_INTSTAT) 

    /*******************************************************************************
    * Function Name: Voltage_Sense_ClearInterrupt
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
    uint8 Voltage_Sense_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Voltage_Sense_INTSTAT & Voltage_Sense_MASK);
		Voltage_Sense_INTSTAT = maskedStatus;
        return maskedStatus >> Voltage_Sense_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
