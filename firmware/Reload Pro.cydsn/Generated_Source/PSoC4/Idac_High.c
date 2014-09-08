/*******************************************************************************
* File Name: IDAC_High.c
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

#include "IDAC_High.h"

uint32 IDAC_High_initVar = 0u;


/*******************************************************************************
* Function Name: IDAC_High_Init
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
void IDAC_High_Init(void)
{
    uint8 enableInterrupts;

    /* Set initial configuration */
    enableInterrupts = CyEnterCriticalSection();

    /* clear previous values */
    IDAC_High_IDAC_CONTROL_REG &= ((uint32)~((uint32)IDAC_High_IDAC_VALUE_MASK <<
        IDAC_High_IDAC_VALUE_POSITION)) | ((uint32)~((uint32)IDAC_High_IDAC_MODE_MASK <<
        IDAC_High_IDAC_MODE_POSITION))  | ((uint32)~((uint32)IDAC_High_IDAC_RANGE_MASK  <<
        IDAC_High_IDAC_RANGE_POSITION));

    IDAC_High_IDAC_POLARITY_CONTROL_REG &= (~(uint32)((uint32)IDAC_High_IDAC_POLARITY_MASK <<
        IDAC_High_IDAC_POLARITY_POSITION));

    /* set new configuration */
    IDAC_High_IDAC_CONTROL_REG |= (((uint32)IDAC_High_IDAC_INIT_VALUE <<
        IDAC_High_IDAC_VALUE_POSITION) | ((uint32)IDAC_High_IDAC_RANGE <<
        IDAC_High_IDAC_RANGE_POSITION));

    IDAC_High_IDAC_POLARITY_CONTROL_REG |= ((uint32)IDAC_High_IDAC_POLARITY <<
                                                           IDAC_High_IDAC_POLARITY_POSITION);

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: IDAC_High_Enable
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
void IDAC_High_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Enable the IDAC */
    IDAC_High_IDAC_CONTROL_REG |= ((uint32)IDAC_High_IDAC_EN_MODE <<
                                                  IDAC_High_IDAC_MODE_POSITION);
    IDAC_High_IDAC_POLARITY_CONTROL_REG |= ((uint32)IDAC_High_IDAC_CSD_EN <<
                                                           IDAC_High_IDAC_CSD_EN_POSITION);
    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: IDAC_High_Start
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
*  IDAC_High_initVar
*
*******************************************************************************/
void IDAC_High_Start(void)
{
    if(0u == IDAC_High_initVar)
    {
        IDAC_High_Init();
        IDAC_High_initVar = 1u;
    }

    IDAC_High_Enable();

}


/*******************************************************************************
* Function Name: IDAC_High_Stop
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
void IDAC_High_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Disable the IDAC */
    IDAC_High_IDAC_CONTROL_REG &= ((uint32)~((uint32)IDAC_High_IDAC_MODE_MASK <<
        IDAC_High_IDAC_MODE_POSITION));
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: IDAC_High_SetValue
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
void IDAC_High_SetValue(uint32 value)
{
    uint8 enableInterrupts;
    uint32 newRegisterValue;

    enableInterrupts = CyEnterCriticalSection();

    #if(IDAC_High_IDAC_VALUE_POSITION != 0u)
        newRegisterValue = ((IDAC_High_IDAC_CONTROL_REG & (~(uint32)((uint32)IDAC_High_IDAC_VALUE_MASK <<
        IDAC_High_IDAC_VALUE_POSITION))) | (value << IDAC_High_IDAC_VALUE_POSITION));
    #else
        newRegisterValue = ((IDAC_High_IDAC_CONTROL_REG & (~(uint32)IDAC_High_IDAC_VALUE_MASK)) | value);
    #endif /* IDAC_High_IDAC_VALUE_POSITION != 0u */

    IDAC_High_IDAC_CONTROL_REG = newRegisterValue;

    CyExitCriticalSection(enableInterrupts);
}

/* [] END OF FILE */
