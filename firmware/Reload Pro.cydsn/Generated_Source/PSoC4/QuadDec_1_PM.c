/*******************************************************************************
* File Name: QuadDec_1_PM.c
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

#include "QuadDec_1.h"

static QuadDec_1_BACKUP_STRUCT QuadDec_1_backup;


/*******************************************************************************
* Function Name: QuadDec_1_SaveConfig
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
void QuadDec_1_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: QuadDec_1_Sleep
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
void QuadDec_1_Sleep(void)
{
    if(0u != (QuadDec_1_BLOCK_CONTROL_REG & QuadDec_1_MASK))
    {
        QuadDec_1_backup.enableState = 1u;
    }
    else
    {
        QuadDec_1_backup.enableState = 0u;
    }

    QuadDec_1_Stop();
    QuadDec_1_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec_1_RestoreConfig
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
void QuadDec_1_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: QuadDec_1_Wakeup
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
void QuadDec_1_Wakeup(void)
{
    QuadDec_1_RestoreConfig();

    if(0u != QuadDec_1_backup.enableState)
    {
        QuadDec_1_Enable();
    }
}


/* [] END OF FILE */
