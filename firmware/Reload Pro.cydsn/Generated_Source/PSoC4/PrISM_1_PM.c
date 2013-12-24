/*******************************************************************************
* File Name: PrISM_1_PM.c
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

#include "PrISM_1.h"


/***************************************
* Local data allocation
***************************************/
static PrISM_1_BACKUP_STRUCT  PrISM_1_backup = 
{
    /* enableState */
    0u,
    /* cr */
    #if(!PrISM_1_PULSE_TYPE_HARDCODED)
       (((PrISM_1_GREATERTHAN_OR_EQUAL == PrISM_1_COMPARE0) ? \
                                                PrISM_1_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL : 0u) |
        ((PrISM_1_GREATERTHAN_OR_EQUAL == PrISM_1_COMPARE1) ? \
                                                PrISM_1_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL : 0u)),
    #endif /* End PrISM_1_PULSE_TYPE_HARDCODED */
    /* seed */    
    PrISM_1_SEED,
    /* seed_copy */    
    PrISM_1_SEED,
    /* polynom */
    PrISM_1_POLYNOM,
    #if(CY_UDB_V0)
        /* density0 */
        PrISM_1_DENSITY0,
        /* density1 */
        PrISM_1_DENSITY1,
    #endif /*End CY_UDB_V0*/
};


/*******************************************************************************
* Function Name: PrISM_1_SaveConfig
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
*  PrISM_1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PrISM_1_SaveConfig(void) 
{
    #if (CY_UDB_V0)
        #if(!PrISM_1_PULSE_TYPE_HARDCODED)
            PrISM_1_backup.cr = PrISM_1_CONTROL_REG;
        #endif /* End PrISM_1_PULSE_TYPE_HARDCODED */
        PrISM_1_backup.seed = PrISM_1_ReadSeed();
        PrISM_1_backup.seed_copy = CY_GET_REG8(PrISM_1_SEED_COPY_PTR);
        PrISM_1_backup.polynom = PrISM_1_ReadPolynomial();
        PrISM_1_backup.density0 = PrISM_1_ReadPulse0();
        PrISM_1_backup.density1 = PrISM_1_ReadPulse1();
    #else /* CY_UDB_V1 */
        #if(!PrISM_1_PULSE_TYPE_HARDCODED)
            PrISM_1_backup.cr = PrISM_1_CONTROL_REG;
        #endif /* End PrISM_1_PULSE_TYPE_HARDCODED */
        PrISM_1_backup.seed = PrISM_1_ReadSeed();
        PrISM_1_backup.seed_copy = CY_GET_REG8(PrISM_1_SEED_COPY_PTR);
        PrISM_1_backup.polynom = PrISM_1_ReadPolynomial();
    #endif  /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: PrISM_1_RestoreConfig
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
*  PrISM_1_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void PrISM_1_RestoreConfig(void) 
{
    #if (CY_UDB_V0)
    
        uint8 enableInterrupts;
        
        #if(!PrISM_1_PULSE_TYPE_HARDCODED)
            PrISM_1_CONTROL_REG = PrISM_1_backup.cr;
        #endif /* End PrISM_1_PULSE_TYPE_HARDCODED */

        CY_SET_REG8(PrISM_1_SEED_COPY_PTR, PrISM_1_backup.seed_copy);
        CY_SET_REG8(PrISM_1_SEED_PTR, PrISM_1_backup.seed);
        PrISM_1_WritePolynomial(PrISM_1_backup.polynom);
        PrISM_1_WritePulse0(PrISM_1_backup.density0);
        PrISM_1_WritePulse1(PrISM_1_backup.density1);
        
        enableInterrupts = CyEnterCriticalSection();
        /* Set FIFO0_CLR bit to use FIFO0 as a simple one-byte buffer*/
        CY_SET_REG8(PrISM_1_AUX_CONTROL_PTR, 
                        CY_GET_REG8(PrISM_1_AUX_CONTROL_PTR) | PrISM_1_FIFO0_CLR);
        CyExitCriticalSection(enableInterrupts);

    #else   /* CY_UDB_V1 */

        #if(!PrISM_1_PULSE_TYPE_HARDCODED)
            PrISM_1_CONTROL_REG = PrISM_1_backup.cr;
        #endif /* End PrISM_1_PULSE_TYPE_HARDCODED */

        CY_SET_REG8(PrISM_1_SEED_COPY_PTR, PrISM_1_backup.seed_copy);
        CY_SET_REG8(PrISM_1_SEED_PTR, PrISM_1_backup.seed);
        PrISM_1_WritePolynomial(PrISM_1_backup.polynom);
    
    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: PrISM_1_Sleep
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
*  PrISM_1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PrISM_1_Sleep(void) 
{
    #if(!PrISM_1_PULSE_TYPE_HARDCODED)
        if((PrISM_1_CONTROL_REG & PrISM_1_CTRL_ENABLE) != 0u) 
        {
            PrISM_1_backup.enableState = 1u;
        }
        else
        {
            PrISM_1_backup.enableState = 0u;
        }
    #endif /* End PrISM_1_PULSE_TYPE_HARDCODED */
    PrISM_1_Stop();
    PrISM_1_SaveConfig();
}


/*******************************************************************************
* Function Name: PrISM_1_Wakeup
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
*  PrISM_1_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void PrISM_1_Wakeup(void) 
{
    PrISM_1_RestoreConfig();
    if(PrISM_1_backup.enableState != 0u)
    {
        PrISM_1_Enable();
    } 
}


/* [] END OF FILE */
