/*******************************************************************************
* File Name: IDAC.c
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

#include "IDAC.h"

uint32 IDAC_initVar = 0u;


/*******************************************************************************
* Function Name: IDAC_Init
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
void IDAC_Init(void)
{
    uint8 enableInterrupts;

    /* Set initial configuration */
    enableInterrupts = CyEnterCriticalSection();

    /* clear previous values */
    IDAC_IDAC_CONTROL_REG &= ((uint32)~((uint32)IDAC_IDAC_VALUE_MASK <<
        IDAC_IDAC_VALUE_POSITION)) | ((uint32)~((uint32)IDAC_IDAC_MODE_MASK <<
        IDAC_IDAC_MODE_POSITION))  | ((uint32)~((uint32)IDAC_IDAC_RANGE_MASK  <<
        IDAC_IDAC_RANGE_POSITION));

    IDAC_IDAC_POLARITY_CONTROL_REG &= (~(uint32)((uint32)IDAC_IDAC_POLARITY_MASK <<
        IDAC_IDAC_POLARITY_POSITION));

    /* set new configuration */
    IDAC_IDAC_CONTROL_REG |= (((uint32)IDAC_IDAC_INIT_VALUE <<
        IDAC_IDAC_VALUE_POSITION) | ((uint32)IDAC_IDAC_RANGE <<
        IDAC_IDAC_RANGE_POSITION));

    IDAC_IDAC_POLARITY_CONTROL_REG |= ((uint32)IDAC_IDAC_POLARITY <<
                                                           IDAC_IDAC_POLARITY_POSITION);

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: IDAC_Enable
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
void IDAC_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Enable the IDAC */
    IDAC_IDAC_CONTROL_REG |= ((uint32)IDAC_IDAC_EN_MODE <<
                                                  IDAC_IDAC_MODE_POSITION);
    IDAC_IDAC_POLARITY_CONTROL_REG |= ((uint32)IDAC_IDAC_CSD_EN <<
                                                           IDAC_IDAC_CSD_EN_POSITION);
    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: IDAC_Start
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
*  IDAC_initVar
*
*******************************************************************************/
void IDAC_Start(void)
{
    if(0u == IDAC_initVar)
    {
        IDAC_Init();
        IDAC_initVar = 1u;
    }

    IDAC_Enable();

}


/*******************************************************************************
* Function Name: IDAC_Stop
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
void IDAC_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Disable the IDAC */
    IDAC_IDAC_CONTROL_REG &= ((uint32)~((uint32)IDAC_IDAC_MODE_MASK <<
        IDAC_IDAC_MODE_POSITION));
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: IDAC_SetValue
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
void IDAC_SetValue(uint32 value)
{
    uint8 enableInterrupts;
    uint32 newRegisterValue;

    enableInterrupts = CyEnterCriticalSection();

    #if(IDAC_IDAC_VALUE_POSITION != 0u)
        newRegisterValue = ((IDAC_IDAC_CONTROL_REG & (~(uint32)((uint32)IDAC_IDAC_VALUE_MASK <<
        IDAC_IDAC_VALUE_POSITION))) | (value << IDAC_IDAC_VALUE_POSITION));
    #else
        newRegisterValue = ((IDAC_IDAC_CONTROL_REG & (~(uint32)IDAC_IDAC_VALUE_MASK)) | value);
    #endif /* IDAC_IDAC_VALUE_POSITION != 0u */

    IDAC_IDAC_CONTROL_REG = newRegisterValue;

    CyExitCriticalSection(enableInterrupts);
}

/* [] END OF FILE */
