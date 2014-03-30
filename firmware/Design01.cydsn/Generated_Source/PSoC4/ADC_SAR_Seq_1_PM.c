/*******************************************************************************
* File Name: ADC_SAR_Seq_1_PM.c
* Version 1.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "ADC_SAR_Seq_1.h"


/***************************************
* Local data allocation
***************************************/

static ADC_SAR_Seq_1_BACKUP_STRUCT  ADC_SAR_Seq_1_backup =
{
    ADC_SAR_Seq_1_DISABLED
};


/*******************************************************************************
* Function Name: ADC_SAR_Seq_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_SAR_Seq_1_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_SAR_Seq_1_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_1_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_SAR_Seq_1_backup - modified.
*
*******************************************************************************/
void ADC_SAR_Seq_1_Sleep(void)
{
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    ADC_SAR_Seq_1_SAR_DFT_CTRL_REG |= ADC_SAR_Seq_1_ADFT_OVERRIDE;
    if((ADC_SAR_Seq_1_SAR_CTRL_REG  & ADC_SAR_Seq_1_ENABLE) != 0u)
    {
        if((ADC_SAR_Seq_1_SAR_SAMPLE_CTRL_REG & ADC_SAR_Seq_1_CONTINUOUS_EN) != 0u)
        {
            ADC_SAR_Seq_1_backup.enableState = ADC_SAR_Seq_1_ENABLED | ADC_SAR_Seq_1_STARTED;
        }
        else
        {
            ADC_SAR_Seq_1_backup.enableState = ADC_SAR_Seq_1_ENABLED;
        }
        ADC_SAR_Seq_1_StopConvert();
        ADC_SAR_Seq_1_Stop();
    }
    else
    {
        ADC_SAR_Seq_1_backup.enableState = ADC_SAR_Seq_1_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers.
*  This should be called just after awaking from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_SAR_Seq_1_backup - used.
*
*******************************************************************************/
void ADC_SAR_Seq_1_Wakeup(void)
{
    ADC_SAR_Seq_1_SAR_DFT_CTRL_REG &= (uint32)~ADC_SAR_Seq_1_ADFT_OVERRIDE;
    if(ADC_SAR_Seq_1_backup.enableState != ADC_SAR_Seq_1_DISABLED)
    {
        ADC_SAR_Seq_1_Start();
        if((ADC_SAR_Seq_1_backup.enableState & ADC_SAR_Seq_1_STARTED) != 0u)
        {
            ADC_SAR_Seq_1_StartConvert();
        }
    }
}
/* [] END OF FILE */
