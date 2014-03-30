/*******************************************************************************
* File Name: IDAC_Low.c
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

#include "IDAC_Low.h"

uint32 IDAC_Low_initVar = 0u;


/*******************************************************************************
* Function Name: IDAC_Low_Init
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
void IDAC_Low_Init(void)
{
    uint8 enableInterrupts;

    /* Set initial configuration */
    enableInterrupts = CyEnterCriticalSection();

    /* clear previous values */
    IDAC_Low_IDAC_CONTROL_REG &= ((uint32)~((uint32)IDAC_Low_IDAC_VALUE_MASK <<
        IDAC_Low_IDAC_VALUE_POSITION)) | ((uint32)~((uint32)IDAC_Low_IDAC_MODE_MASK <<
        IDAC_Low_IDAC_MODE_POSITION))  | ((uint32)~((uint32)IDAC_Low_IDAC_RANGE_MASK  <<
        IDAC_Low_IDAC_RANGE_POSITION));

    IDAC_Low_IDAC_POLARITY_CONTROL_REG &= (~(uint32)((uint32)IDAC_Low_IDAC_POLARITY_MASK <<
        IDAC_Low_IDAC_POLARITY_POSITION));

    /* set new configuration */
    IDAC_Low_IDAC_CONTROL_REG |= (((uint32)IDAC_Low_IDAC_INIT_VALUE <<
        IDAC_Low_IDAC_VALUE_POSITION) | ((uint32)IDAC_Low_IDAC_RANGE <<
        IDAC_Low_IDAC_RANGE_POSITION));

    IDAC_Low_IDAC_POLARITY_CONTROL_REG |= ((uint32)IDAC_Low_IDAC_POLARITY <<
                                                           IDAC_Low_IDAC_POLARITY_POSITION);

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: IDAC_Low_Enable
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
void IDAC_Low_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Enable the IDAC */
    IDAC_Low_IDAC_CONTROL_REG |= ((uint32)IDAC_Low_IDAC_EN_MODE <<
                                                  IDAC_Low_IDAC_MODE_POSITION);
    IDAC_Low_IDAC_POLARITY_CONTROL_REG |= ((uint32)IDAC_Low_IDAC_CSD_EN <<
                                                           IDAC_Low_IDAC_CSD_EN_POSITION);
    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: IDAC_Low_Start
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
*  IDAC_Low_initVar
*
*******************************************************************************/
void IDAC_Low_Start(void)
{
    if(0u == IDAC_Low_initVar)
    {
        IDAC_Low_Init();
        IDAC_Low_initVar = 1u;
    }

    IDAC_Low_Enable();

}


/*******************************************************************************
* Function Name: IDAC_Low_Stop
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
void IDAC_Low_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Disable the IDAC */
    IDAC_Low_IDAC_CONTROL_REG &= ((uint32)~((uint32)IDAC_Low_IDAC_MODE_MASK <<
        IDAC_Low_IDAC_MODE_POSITION));
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: IDAC_Low_SetValue
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
void IDAC_Low_SetValue(uint32 value)
{
    uint8 enableInterrupts;
    uint32 newRegisterValue;

    enableInterrupts = CyEnterCriticalSection();

    #if(IDAC_Low_IDAC_VALUE_POSITION != 0u)
        newRegisterValue = ((IDAC_Low_IDAC_CONTROL_REG & (~(uint32)((uint32)IDAC_Low_IDAC_VALUE_MASK <<
        IDAC_Low_IDAC_VALUE_POSITION))) | (value << IDAC_Low_IDAC_VALUE_POSITION));
    #else
        newRegisterValue = ((IDAC_Low_IDAC_CONTROL_REG & (~(uint32)IDAC_Low_IDAC_VALUE_MASK)) | value);
    #endif /* IDAC_Low_IDAC_VALUE_POSITION != 0u */

    IDAC_Low_IDAC_CONTROL_REG = newRegisterValue;

    CyExitCriticalSection(enableInterrupts);
}

/* [] END OF FILE */
