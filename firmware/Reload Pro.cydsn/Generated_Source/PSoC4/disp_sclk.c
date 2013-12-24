/*******************************************************************************
* File Name: disp_sclk.c  
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
#include "disp_sclk.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        disp_sclk_PC =   (disp_sclk_PC & \
                                (uint32)(~(uint32)(disp_sclk_DRIVE_MODE_IND_MASK << (disp_sclk_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (disp_sclk_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: disp_sclk_Write
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
void disp_sclk_Write(uint8 value) 
{
    uint8 drVal = (uint8)(disp_sclk_DR & (uint8)(~disp_sclk_MASK));
    drVal = (drVal | ((uint8)(value << disp_sclk_SHIFT) & disp_sclk_MASK));
    disp_sclk_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: disp_sclk_SetDriveMode
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
void disp_sclk_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(disp_sclk__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: disp_sclk_Read
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
*  Macro disp_sclk_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 disp_sclk_Read(void) 
{
    return (uint8)((disp_sclk_PS & disp_sclk_MASK) >> disp_sclk_SHIFT);
}


/*******************************************************************************
* Function Name: disp_sclk_ReadDataReg
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
uint8 disp_sclk_ReadDataReg(void) 
{
    return (uint8)((disp_sclk_DR & disp_sclk_MASK) >> disp_sclk_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(disp_sclk_INTSTAT) 

    /*******************************************************************************
    * Function Name: disp_sclk_ClearInterrupt
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
    uint8 disp_sclk_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(disp_sclk_INTSTAT & disp_sclk_MASK);
		disp_sclk_INTSTAT = maskedStatus;
        return maskedStatus >> disp_sclk_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
