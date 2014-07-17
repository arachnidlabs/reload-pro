/*******************************************************************************
* File Name: QuadDec_PM.c
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

#include "QuadDec.h"

static QuadDec_BACKUP_STRUCT QuadDec_backup;


/*******************************************************************************
* Function Name: QuadDec_SaveConfig
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
void QuadDec_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: QuadDec_Sleep
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
void QuadDec_Sleep(void)
{
    if(0u != (QuadDec_BLOCK_CONTROL_REG & QuadDec_MASK))
    {
        QuadDec_backup.enableState = 1u;
    }
    else
    {
        QuadDec_backup.enableState = 0u;
    }

    QuadDec_Stop();
    QuadDec_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec_RestoreConfig
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
void QuadDec_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: QuadDec_Wakeup
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
void QuadDec_Wakeup(void)
{
    QuadDec_RestoreConfig();

    if(0u != QuadDec_backup.enableState)
    {
        QuadDec_Enable();
    }
}


/* [] END OF FILE */
