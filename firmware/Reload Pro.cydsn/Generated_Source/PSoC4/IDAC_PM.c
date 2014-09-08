/*******************************************************************************
* File Name: IDAC_PM.c
* Version 1.0
*
* Description:
*  This file provides Low power mode APIs for IDAC_P4 component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "IDAC.h"


static IDAC_BACKUP_STRUCT IDAC_backup;


/*******************************************************************************
* Function Name: IDAC_SaveConfig
********************************************************************************
*
* Summary:
*  Saves component state before sleep
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
*******************************************************************************/
void IDAC_SaveConfig(void)
{
    /* All registers are retention - nothing to save */
}


/*******************************************************************************
* Function Name: IDAC_Sleep
********************************************************************************
*
* Summary:
*  Calls _SaveConfig() function
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void IDAC_Sleep(void)
{
        if(0u != (IDAC_IDAC_CONTROL_REG & ((uint32)IDAC_IDAC_MODE_MASK <<
        IDAC_IDAC_MODE_POSITION)))
        {
            IDAC_backup.enableState = 1u;
        }
        else
        {
            IDAC_backup.enableState = 0u;
        }

    IDAC_Stop();
    IDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: IDAC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores component state after wakeup
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
*******************************************************************************/
void IDAC_RestoreConfig(void)
{
    /* All registers are retention - nothing to save */
}


/*******************************************************************************
* Function Name: IDAC_Wakeup
********************************************************************************
*
* Summary:
*  Calls _RestoreConfig() function
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void IDAC_Wakeup(void)
{
    /* Restore IDAC register settings */
    IDAC_RestoreConfig();
    if(IDAC_backup.enableState == 1u)
    {
        /* Enable operation */
        IDAC_Enable();
    } /* Do nothing if the component was disabled before */

}


/* [] END OF FILE */
