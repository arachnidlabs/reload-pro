/*******************************************************************************
* File Name: IDAC_2.c
* Version 1.0
*
* Description:
*  This file provides the source code of APIs for the IDAC_P4 component.
*
*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "IDAC_2.h"

uint32 IDAC_2_initVar = 0u;


/*******************************************************************************
* Function Name: IDAC_2_Init
********************************************************************************
*
* Summary:
*  Initializes IDAC registers with initial values provided from customizer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void IDAC_2_Init(void)
{
    uint8 enableInterrupts;

    /* Set initial configuration */
    enableInterrupts = CyEnterCriticalSection();

    /* clear previous values */
    IDAC_2_IDAC_CONTROL_REG &= ((uint32)~((uint32)IDAC_2_IDAC_VALUE_MASK <<
        IDAC_2_IDAC_VALUE_POSITION)) | ((uint32)~((uint32)IDAC_2_IDAC_MODE_MASK <<
        IDAC_2_IDAC_MODE_POSITION))  | ((uint32)~((uint32)IDAC_2_IDAC_RANGE_MASK  <<
        IDAC_2_IDAC_RANGE_POSITION));

    IDAC_2_IDAC_POLARITY_CONTROL_REG &= (~(uint32)((uint32)IDAC_2_IDAC_POLARITY_MASK <<
        IDAC_2_IDAC_POLARITY_POSITION));

    /* set new configuration */
    IDAC_2_IDAC_CONTROL_REG |= (((uint32)IDAC_2_IDAC_INIT_VALUE <<
        IDAC_2_IDAC_VALUE_POSITION) | ((uint32)IDAC_2_IDAC_RANGE <<
        IDAC_2_IDAC_RANGE_POSITION));

    IDAC_2_IDAC_POLARITY_CONTROL_REG |= ((uint32)IDAC_2_IDAC_POLARITY <<
                                                           IDAC_2_IDAC_POLARITY_POSITION);

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: IDAC_2_Enable
********************************************************************************
*
* Summary:
*  Enables IDAC operations.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void IDAC_2_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Enable the IDAC */
    IDAC_2_IDAC_CONTROL_REG |= ((uint32)IDAC_2_IDAC_EN_MODE <<
                                                  IDAC_2_IDAC_MODE_POSITION);
    IDAC_2_IDAC_POLARITY_CONTROL_REG |= ((uint32)IDAC_2_IDAC_CSD_EN <<
                                                           IDAC_2_IDAC_CSD_EN_POSITION);
    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: IDAC_2_Start
********************************************************************************
*
* Summary:
*  Starts the IDAC hardware.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  IDAC_2_initVar
*
*******************************************************************************/
void IDAC_2_Start(void)
{
    if(0u == IDAC_2_initVar)
    {
        IDAC_2_Init();
        IDAC_2_initVar = 1u;
    }

    IDAC_2_Enable();

}


/*******************************************************************************
* Function Name: IDAC_2_Stop
********************************************************************************
*
* Summary:
*  Stops the IDAC hardware.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void IDAC_2_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Disable the IDAC */
    IDAC_2_IDAC_CONTROL_REG &= ((uint32)~((uint32)IDAC_2_IDAC_MODE_MASK <<
        IDAC_2_IDAC_MODE_POSITION));
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: IDAC_2_SetValue
********************************************************************************
*
* Summary:
*  Sets the IDAC value.
*
* Parameters:
*  uint32 value
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void IDAC_2_SetValue(uint32 value)
{
    uint8 enableInterrupts;
    uint32 newRegisterValue;

    enableInterrupts = CyEnterCriticalSection();

    #if(IDAC_2_IDAC_VALUE_POSITION != 0u)
        newRegisterValue = ((IDAC_2_IDAC_CONTROL_REG & (~(uint32)((uint32)IDAC_2_IDAC_VALUE_MASK <<
        IDAC_2_IDAC_VALUE_POSITION))) | (value << IDAC_2_IDAC_VALUE_POSITION));
    #else
        newRegisterValue = ((IDAC_2_IDAC_CONTROL_REG & (~(uint32)IDAC_2_IDAC_VALUE_MASK)) | value);
    #endif /* IDAC_2_IDAC_VALUE_POSITION != 0u */

    IDAC_2_IDAC_CONTROL_REG = newRegisterValue;

    CyExitCriticalSection(enableInterrupts);
}

/* [] END OF FILE */
