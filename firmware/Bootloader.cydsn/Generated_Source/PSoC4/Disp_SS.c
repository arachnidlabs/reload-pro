/*******************************************************************************
* File Name: Disp_SS.c  
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
#include "Disp_SS.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Disp_SS_PC =   (Disp_SS_PC & \
                                (uint32)(~(uint32)(Disp_SS_DRIVE_MODE_IND_MASK << (Disp_SS_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Disp_SS_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Disp_SS_Write
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
void Disp_SS_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Disp_SS_DR & (uint8)(~Disp_SS_MASK));
    drVal = (drVal | ((uint8)(value << Disp_SS_SHIFT) & Disp_SS_MASK));
    Disp_SS_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Disp_SS_SetDriveMode
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
void Disp_SS_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Disp_SS__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Disp_SS_Read
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
*  Macro Disp_SS_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Disp_SS_Read(void) 
{
    return (uint8)((Disp_SS_PS & Disp_SS_MASK) >> Disp_SS_SHIFT);
}


/*******************************************************************************
* Function Name: Disp_SS_ReadDataReg
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
uint8 Disp_SS_ReadDataReg(void) 
{
    return (uint8)((Disp_SS_DR & Disp_SS_MASK) >> Disp_SS_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Disp_SS_INTSTAT) 

    /*******************************************************************************
    * Function Name: Disp_SS_ClearInterrupt
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
    uint8 Disp_SS_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Disp_SS_INTSTAT & Disp_SS_MASK);
		Disp_SS_INTSTAT = maskedStatus;
        return maskedStatus >> Disp_SS_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
