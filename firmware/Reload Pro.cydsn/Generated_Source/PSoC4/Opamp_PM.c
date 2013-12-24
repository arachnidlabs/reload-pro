/*******************************************************************************
* File Name: Opamp_PM.c
* Version 1.0
*
* Description:
*  This file provides the power management source code to the API for the
*  OpAmp (Analog Buffer) component.
*
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Opamp.h"

static Opamp_BACKUP_STRUCT  Opamp_backup;


/*******************************************************************************
* Function Name: Opamp_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Opamp_SaveConfig(void)
{
}


/*******************************************************************************
* Function Name: Opamp_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Opamp_RestoreConfig(void)
{
}


/*******************************************************************************
* Function Name: Opamp_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Opamp_backup: The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Opamp_Sleep(void)
{
    /* Save OpAmp enable state */
    if((Opamp_OA_RES_CTRL & Opamp_OA_PWR_MODE_MASK) != 0u)
    {
        /* Component is enabled */
        Opamp_backup.enableState = 1u;
        /* Stops the component */
        Opamp_Stop();
    }
    else
    {
        /* Component is disabled */
        Opamp_backup.enableState = 0u;
    }
    /* Saves the configuration */
    Opamp_SaveConfig();
}


/*******************************************************************************
* Function Name: Opamp_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Opamp_backup: The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Opamp_Wakeup(void)
{
    /* Restore the user configuration */
    Opamp_RestoreConfig();

    /* Enables the component operation */
    if(Opamp_backup.enableState == 1u)
    {
        Opamp_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
