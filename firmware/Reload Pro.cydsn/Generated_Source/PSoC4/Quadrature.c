/*******************************************************************************
* File Name: Quadrature.c  
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
#include "Quadrature.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Quadrature_PC =   (Quadrature_PC & \
                                (uint32)(~(uint32)(Quadrature_DRIVE_MODE_IND_MASK << (Quadrature_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Quadrature_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Quadrature_Write
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
void Quadrature_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Quadrature_DR & (uint8)(~Quadrature_MASK));
    drVal = (drVal | ((uint8)(value << Quadrature_SHIFT) & Quadrature_MASK));
    Quadrature_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Quadrature_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Quadrature_DM_STRONG     Strong Drive 
*  Quadrature_DM_OD_HI      Open Drain, Drives High 
*  Quadrature_DM_OD_LO      Open Drain, Drives Low 
*  Quadrature_DM_RES_UP     Resistive Pull Up 
*  Quadrature_DM_RES_DWN    Resistive Pull Down 
*  Quadrature_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Quadrature_DM_DIG_HIZ    High Impedance Digital 
*  Quadrature_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Quadrature_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Quadrature__0__SHIFT, mode);
	SetP4PinDriveMode(Quadrature__1__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Quadrature_Read
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
*  Macro Quadrature_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Quadrature_Read(void) 
{
    return (uint8)((Quadrature_PS & Quadrature_MASK) >> Quadrature_SHIFT);
}


/*******************************************************************************
* Function Name: Quadrature_ReadDataReg
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
uint8 Quadrature_ReadDataReg(void) 
{
    return (uint8)((Quadrature_DR & Quadrature_MASK) >> Quadrature_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Quadrature_INTSTAT) 

    /*******************************************************************************
    * Function Name: Quadrature_ClearInterrupt
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
    uint8 Quadrature_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Quadrature_INTSTAT & Quadrature_MASK);
		Quadrature_INTSTAT = maskedStatus;
        return maskedStatus >> Quadrature_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
