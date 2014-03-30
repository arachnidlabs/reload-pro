/*******************************************************************************
* File Name: idac_low_out.c  
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
#include "idac_low_out.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        idac_low_out_PC =   (idac_low_out_PC & \
                                (uint32)(~(uint32)(idac_low_out_DRIVE_MODE_IND_MASK << (idac_low_out_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (idac_low_out_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: idac_low_out_Write
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
void idac_low_out_Write(uint8 value) 
{
    uint8 drVal = (uint8)(idac_low_out_DR & (uint8)(~idac_low_out_MASK));
    drVal = (drVal | ((uint8)(value << idac_low_out_SHIFT) & idac_low_out_MASK));
    idac_low_out_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: idac_low_out_SetDriveMode
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
void idac_low_out_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(idac_low_out__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: idac_low_out_Read
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
*  Macro idac_low_out_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 idac_low_out_Read(void) 
{
    return (uint8)((idac_low_out_PS & idac_low_out_MASK) >> idac_low_out_SHIFT);
}


/*******************************************************************************
* Function Name: idac_low_out_ReadDataReg
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
uint8 idac_low_out_ReadDataReg(void) 
{
    return (uint8)((idac_low_out_DR & idac_low_out_MASK) >> idac_low_out_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(idac_low_out_INTSTAT) 

    /*******************************************************************************
    * Function Name: idac_low_out_ClearInterrupt
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
    uint8 idac_low_out_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(idac_low_out_INTSTAT & idac_low_out_MASK);
		idac_low_out_INTSTAT = maskedStatus;
        return maskedStatus >> idac_low_out_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
