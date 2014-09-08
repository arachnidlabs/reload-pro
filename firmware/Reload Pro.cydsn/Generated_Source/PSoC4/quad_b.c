/*******************************************************************************
* File Name: quad_b.c  
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
#include "quad_b.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        quad_b_PC =   (quad_b_PC & \
                                (uint32)(~(uint32)(quad_b_DRIVE_MODE_IND_MASK << (quad_b_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (quad_b_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: quad_b_Write
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
void quad_b_Write(uint8 value) 
{
    uint8 drVal = (uint8)(quad_b_DR & (uint8)(~quad_b_MASK));
    drVal = (drVal | ((uint8)(value << quad_b_SHIFT) & quad_b_MASK));
    quad_b_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: quad_b_SetDriveMode
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
void quad_b_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(quad_b__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: quad_b_Read
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
*  Macro quad_b_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 quad_b_Read(void) 
{
    return (uint8)((quad_b_PS & quad_b_MASK) >> quad_b_SHIFT);
}


/*******************************************************************************
* Function Name: quad_b_ReadDataReg
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
uint8 quad_b_ReadDataReg(void) 
{
    return (uint8)((quad_b_DR & quad_b_MASK) >> quad_b_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(quad_b_INTSTAT) 

    /*******************************************************************************
    * Function Name: quad_b_ClearInterrupt
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
    uint8 quad_b_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(quad_b_INTSTAT & quad_b_MASK);
		quad_b_INTSTAT = maskedStatus;
        return maskedStatus >> quad_b_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
