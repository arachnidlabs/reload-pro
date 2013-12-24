/*******************************************************************************
* File Name: Idac_Low.c  
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
#include "Idac_Low.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Idac_Low_PC =   (Idac_Low_PC & \
                                (uint32)(~(uint32)(Idac_Low_DRIVE_MODE_IND_MASK << (Idac_Low_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Idac_Low_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Idac_Low_Write
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
void Idac_Low_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Idac_Low_DR & (uint8)(~Idac_Low_MASK));
    drVal = (drVal | ((uint8)(value << Idac_Low_SHIFT) & Idac_Low_MASK));
    Idac_Low_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Idac_Low_SetDriveMode
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
void Idac_Low_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Idac_Low__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Idac_Low_Read
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
*  Macro Idac_Low_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Idac_Low_Read(void) 
{
    return (uint8)((Idac_Low_PS & Idac_Low_MASK) >> Idac_Low_SHIFT);
}


/*******************************************************************************
* Function Name: Idac_Low_ReadDataReg
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
uint8 Idac_Low_ReadDataReg(void) 
{
    return (uint8)((Idac_Low_DR & Idac_Low_MASK) >> Idac_Low_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Idac_Low_INTSTAT) 

    /*******************************************************************************
    * Function Name: Idac_Low_ClearInterrupt
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
    uint8 Idac_Low_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Idac_Low_INTSTAT & Idac_Low_MASK);
		Idac_Low_INTSTAT = maskedStatus;
        return maskedStatus >> Idac_Low_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
