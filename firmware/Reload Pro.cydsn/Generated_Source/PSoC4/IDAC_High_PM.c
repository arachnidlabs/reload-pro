/*******************************************************************************
* File Name: IDAC_High_PM.c
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

#include "IDAC_High.h"


static IDAC_High_BACKUP_STRUCT IDAC_High_backup;


/*******************************************************************************
* Function Name: IDAC_High_SaveConfig
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
void IDAC_High_SaveConfig(void)
{
    /* All registers are retention - nothing to save */
}


/*******************************************************************************
* Function Name: IDAC_High_Sleep
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
void IDAC_High_Sleep(void)
{
        if(0u != (IDAC_High_IDAC_CONTROL_REG & ((uint32)IDAC_High_IDAC_MODE_MASK <<
        IDAC_High_IDAC_MODE_POSITION)))
        {
            IDAC_High_backup.enableState = 1u;
        }
        else
        {
            IDAC_High_backup.enableState = 0u;
        }

    IDAC_High_Stop();
    IDAC_High_SaveConfig();
}


/*******************************************************************************
* Function Name: IDAC_High_RestoreConfig
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
void IDAC_High_RestoreConfig(void)
{
    /* All registers are retention - nothing to save */
}


/*******************************************************************************
* Function Name: IDAC_High_Wakeup
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
void IDAC_High_Wakeup(void)
{
    /* Restore IDAC register settings */
    IDAC_High_RestoreConfig();
    if(IDAC_High_backup.enableState == 1u)
    {
        /* Enable operation */
        IDAC_High_Enable();
    } /* Do nothing if the component was disabled before */

}


/* [] END OF FILE */
