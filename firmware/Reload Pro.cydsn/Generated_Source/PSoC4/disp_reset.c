/*******************************************************************************
* File Name: disp_reset.c  
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
#include "disp_reset.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        disp_reset_PC =   (disp_reset_PC & \
                                (uint32)(~(uint32)(disp_reset_DRIVE_MODE_IND_MASK << (disp_reset_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (disp_reset_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: disp_reset_Write
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
void disp_reset_Write(uint8 value) 
{
    uint8 drVal = (uint8)(disp_reset_DR & (uint8)(~disp_reset_MASK));
    drVal = (drVal | ((uint8)(value << disp_reset_SHIFT) & disp_reset_MASK));
    disp_reset_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: disp_reset_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  disp_reset_DM_STRONG     Strong Drive 
*  disp_reset_DM_OD_HI      Open Drain, Drives High 
*  disp_reset_DM_OD_LO      Open Drain, Drives Low 
*  disp_reset_DM_RES_UP     Resistive Pull Up 
*  disp_reset_DM_RES_DWN    Resistive Pull Down 
*  disp_reset_DM_RES_UPDWN  Resistive Pull Up/Down 
*  disp_reset_DM_DIG_HIZ    High Impedance Digital 
*  disp_reset_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void disp_reset_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(disp_reset__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: disp_reset_Read
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
*  Macro disp_reset_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 disp_reset_Read(void) 
{
    return (uint8)((disp_reset_PS & disp_reset_MASK) >> disp_reset_SHIFT);
}


/*******************************************************************************
* Function Name: disp_reset_ReadDataReg
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
uint8 disp_reset_ReadDataReg(void) 
{
    return (uint8)((disp_reset_DR & disp_reset_MASK) >> disp_reset_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(disp_reset_INTSTAT) 

    /*******************************************************************************
    * Function Name: disp_reset_ClearInterrupt
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
    uint8 disp_reset_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(disp_reset_INTSTAT & disp_reset_MASK);
		disp_reset_INTSTAT = maskedStatus;
        return maskedStatus >> disp_reset_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
