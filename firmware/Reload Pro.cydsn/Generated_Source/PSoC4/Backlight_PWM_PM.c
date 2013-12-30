/*******************************************************************************
* File Name: Backlight_PWM_PM.c
* Version 1.0
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Backlight_PWM.h"

static Backlight_PWM_BACKUP_STRUCT Backlight_PWM_backup;


/*******************************************************************************
* Function Name: Backlight_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Backlight_PWM_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_Sleep(void)
{
    if(0u != (Backlight_PWM_BLOCK_CONTROL_REG & Backlight_PWM_MASK))
    {
        Backlight_PWM_backup.enableState = 1u;
    }
    else
    {
        Backlight_PWM_backup.enableState = 0u;
    }

    Backlight_PWM_Stop();
    Backlight_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: Backlight_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Backlight_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_Wakeup(void)
{
    Backlight_PWM_RestoreConfig();

    if(0u != Backlight_PWM_backup.enableState)
    {
        Backlight_PWM_Enable();
    }
}


/* [] END OF FILE */
