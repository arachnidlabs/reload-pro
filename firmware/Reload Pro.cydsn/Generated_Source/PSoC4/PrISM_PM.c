/*******************************************************************************
* File Name: PrISM_PM.c
* Version 2.20
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality of the PrISM component
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PrISM.h"


/***************************************
* Local data allocation
***************************************/
static PrISM_BACKUP_STRUCT  PrISM_backup = 
{
    /* enableState */
    0u,
    /* cr */
    #if(!PrISM_PULSE_TYPE_HARDCODED)
       (((PrISM_GREATERTHAN_OR_EQUAL == PrISM_COMPARE0) ? \
                                                PrISM_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL : 0u) |
        ((PrISM_GREATERTHAN_OR_EQUAL == PrISM_COMPARE1) ? \
                                                PrISM_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL : 0u)),
    #endif /* End PrISM_PULSE_TYPE_HARDCODED */
    /* seed */    
    PrISM_SEED,
    /* seed_copy */    
    PrISM_SEED,
    /* polynom */
    PrISM_POLYNOM,
    #if(CY_UDB_V0)
        /* density0 */
        PrISM_DENSITY0,
        /* density1 */
        PrISM_DENSITY1,
    #endif /*End CY_UDB_V0*/
};


/*******************************************************************************
* Function Name: PrISM_SaveConfig
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
* Global Variables:
*  PrISM_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PrISM_SaveConfig(void) 
{
    #if (CY_UDB_V0)
        #if(!PrISM_PULSE_TYPE_HARDCODED)
            PrISM_backup.cr = PrISM_CONTROL_REG;
        #endif /* End PrISM_PULSE_TYPE_HARDCODED */
        PrISM_backup.seed = PrISM_ReadSeed();
        PrISM_backup.seed_copy = CY_GET_REG8(PrISM_SEED_COPY_PTR);
        PrISM_backup.polynom = PrISM_ReadPolynomial();
        PrISM_backup.density0 = PrISM_ReadPulse0();
        PrISM_backup.density1 = PrISM_ReadPulse1();
    #else /* CY_UDB_V1 */
        #if(!PrISM_PULSE_TYPE_HARDCODED)
            PrISM_backup.cr = PrISM_CONTROL_REG;
        #endif /* End PrISM_PULSE_TYPE_HARDCODED */
        PrISM_backup.seed = PrISM_ReadSeed();
        PrISM_backup.seed_copy = CY_GET_REG8(PrISM_SEED_COPY_PTR);
        PrISM_backup.polynom = PrISM_ReadPolynomial();
    #endif  /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: PrISM_RestoreConfig
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
* Global Variables:
*  PrISM_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void PrISM_RestoreConfig(void) 
{
    #if (CY_UDB_V0)
    
        uint8 enableInterrupts;
        
        #if(!PrISM_PULSE_TYPE_HARDCODED)
            PrISM_CONTROL_REG = PrISM_backup.cr;
        #endif /* End PrISM_PULSE_TYPE_HARDCODED */

        CY_SET_REG8(PrISM_SEED_COPY_PTR, PrISM_backup.seed_copy);
        CY_SET_REG8(PrISM_SEED_PTR, PrISM_backup.seed);
        PrISM_WritePolynomial(PrISM_backup.polynom);
        PrISM_WritePulse0(PrISM_backup.density0);
        PrISM_WritePulse1(PrISM_backup.density1);
        
        enableInterrupts = CyEnterCriticalSection();
        /* Set FIFO0_CLR bit to use FIFO0 as a simple one-byte buffer*/
        CY_SET_REG8(PrISM_AUX_CONTROL_PTR, 
                        CY_GET_REG8(PrISM_AUX_CONTROL_PTR) | PrISM_FIFO0_CLR);
        CyExitCriticalSection(enableInterrupts);

    #else   /* CY_UDB_V1 */

        #if(!PrISM_PULSE_TYPE_HARDCODED)
            PrISM_CONTROL_REG = PrISM_backup.cr;
        #endif /* End PrISM_PULSE_TYPE_HARDCODED */

        CY_SET_REG8(PrISM_SEED_COPY_PTR, PrISM_backup.seed_copy);
        CY_SET_REG8(PrISM_SEED_PTR, PrISM_backup.seed);
        PrISM_WritePolynomial(PrISM_backup.polynom);
    
    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: PrISM_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  PrISM_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PrISM_Sleep(void) 
{
    #if(!PrISM_PULSE_TYPE_HARDCODED)
        if((PrISM_CONTROL_REG & PrISM_CTRL_ENABLE) != 0u) 
        {
            PrISM_backup.enableState = 1u;
        }
        else
        {
            PrISM_backup.enableState = 0u;
        }
    #endif /* End PrISM_PULSE_TYPE_HARDCODED */
    PrISM_Stop();
    PrISM_SaveConfig();
}


/*******************************************************************************
* Function Name: PrISM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  PrISM_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void PrISM_Wakeup(void) 
{
    PrISM_RestoreConfig();
    if(PrISM_backup.enableState != 0u)
    {
        PrISM_Enable();
    } 
}


/* [] END OF FILE */
