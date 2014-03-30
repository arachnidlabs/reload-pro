/*******************************************************************************
* File Name: IDAC_1_PM.c
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

#include "IDAC_1.h"


static IDAC_1_BACKUP_STRUCT IDAC_1_backup;


/*******************************************************************************
* Function Name: IDAC_1_SaveConfig
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
void IDAC_1_SaveConfig(void)
{
    /* All registers are retention - nothing to save */
}


/*******************************************************************************
* Function Name: IDAC_1_Sleep
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
void IDAC_1_Sleep(void)
{
        if(0u != (IDAC_1_IDAC_CONTROL_REG & ((uint32)IDAC_1_IDAC_MODE_MASK <<
        IDAC_1_IDAC_MODE_POSITION)))
        {
            IDAC_1_backup.enableState = 1u;
        }
        else
        {
            IDAC_1_backup.enableState = 0u;
        }

    IDAC_1_Stop();
    IDAC_1_SaveConfig();
}


/*******************************************************************************
* Function Name: IDAC_1_RestoreConfig
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
void IDAC_1_RestoreConfig(void)
{
    /* All registers are retention - nothing to save */
}


/*******************************************************************************
* Function Name: IDAC_1_Wakeup
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
void IDAC_1_Wakeup(void)
{
    /* Restore IDAC register settings */
    IDAC_1_RestoreConfig();
    if(IDAC_1_backup.enableState == 1u)
    {
        /* Enable operation */
        IDAC_1_Enable();
    } /* Do nothing if the component was disabled before */

}


/* [] END OF FILE */
