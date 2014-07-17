/*******************************************************************************
* File Name: disp_ss.c  
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
#include "disp_ss.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        disp_ss_PC =   (disp_ss_PC & \
                                (uint32)(~(uint32)(disp_ss_DRIVE_MODE_IND_MASK << (disp_ss_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (disp_ss_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: disp_ss_Write
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
void disp_ss_Write(uint8 value) 
{
    uint8 drVal = (uint8)(disp_ss_DR & (uint8)(~disp_ss_MASK));
    drVal = (drVal | ((uint8)(value << disp_ss_SHIFT) & disp_ss_MASK));
    disp_ss_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: disp_ss_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  disp_ss_DM_STRONG     Strong Drive 
*  disp_ss_DM_OD_HI      Open Drain, Drives High 
*  disp_ss_DM_OD_LO      Open Drain, Drives Low 
*  disp_ss_DM_RES_UP     Resistive Pull Up 
*  disp_ss_DM_RES_DWN    Resistive Pull Down 
*  disp_ss_DM_RES_UPDWN  Resistive Pull Up/Down 
*  disp_ss_DM_DIG_HIZ    High Impedance Digital 
*  disp_ss_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void disp_ss_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(disp_ss__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: disp_ss_Read
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
*  Macro disp_ss_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 disp_ss_Read(void) 
{
    return (uint8)((disp_ss_PS & disp_ss_MASK) >> disp_ss_SHIFT);
}


/*******************************************************************************
* Function Name: disp_ss_ReadDataReg
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
uint8 disp_ss_ReadDataReg(void) 
{
    return (uint8)((disp_ss_DR & disp_ss_MASK) >> disp_ss_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(disp_ss_INTSTAT) 

    /*******************************************************************************
    * Function Name: disp_ss_ClearInterrupt
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
    uint8 disp_ss_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(disp_ss_INTSTAT & disp_ss_MASK);
		disp_ss_INTSTAT = maskedStatus;
        return maskedStatus >> disp_ss_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
