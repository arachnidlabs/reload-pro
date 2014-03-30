/*******************************************************************************
* File Name: IDAC_Low_PM.c
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

#include "IDAC_Low.h"


static IDAC_Low_BACKUP_STRUCT IDAC_Low_backup;


/*******************************************************************************
* Function Name: IDAC_Low_SaveConfig
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
void IDAC_Low_SaveConfig(void)
{
    /* All registers are retention - nothing to save */
}


/*******************************************************************************
* Function Name: IDAC_Low_Sleep
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
void IDAC_Low_Sleep(void)
{
        if(0u != (IDAC_Low_IDAC_CONTROL_REG & ((uint32)IDAC_Low_IDAC_MODE_MASK <<
        IDAC_Low_IDAC_MODE_POSITION)))
        {
            IDAC_Low_backup.enableState = 1u;
        }
        else
        {
            IDAC_Low_backup.enableState = 0u;
        }

    IDAC_Low_Stop();
    IDAC_Low_SaveConfig();
}


/*******************************************************************************
* Function Name: IDAC_Low_RestoreConfig
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
void IDAC_Low_RestoreConfig(void)
{
    /* All registers are retention - nothing to save */
}


/*******************************************************************************
* Function Name: IDAC_Low_Wakeup
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
void IDAC_Low_Wakeup(void)
{
    /* Restore IDAC register settings */
    IDAC_Low_RestoreConfig();
    if(IDAC_Low_backup.enableState == 1u)
    {
        /* Enable operation */
        IDAC_Low_Enable();
    } /* Do nothing if the component was disabled before */

}


/* [] END OF FILE */
