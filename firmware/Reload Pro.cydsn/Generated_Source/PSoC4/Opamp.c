/*******************************************************************************
* File Name: Opamp.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for OpAmp (Analog Buffer)
*  Component.
*
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Opamp.h"
#include <CyLib.h>

uint32 Opamp_initVar = 0u;


/*******************************************************************************
* Function Name: Opamp_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  Opamp_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Opamp_Init(void)
{
    /* Enable STB */
    Opamp_OA_CTRL |= ((uint32)1u << Opamp_OA_CTB_EN_SHIFT);
    Opamp_OA_RES_CTRL = 0u;
    Opamp_OA_COMP_TRIM_REG = Opamp_OA_COMP_TRIM_VALUE;
    #if(0u != Opamp_OUTPUT_CURRENT)
        /* 10 mA current */
        Opamp_OA_RES_CTRL |= Opamp_OA_DRIVE_STR_SEL_10X;
    #endif /* 0u != Opamp_OUTPUT_CURRENT */
}


/*******************************************************************************
* Function Name: Opamp_Enable
********************************************************************************
*
* Summary:
*  Enables the OpAmp block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Opamp_Enable(void)
{
    Opamp_OA_RES_CTRL &= (~(uint32)Opamp_OA_PWR_MODE_MASK);
    Opamp_OA_RES_CTRL |= Opamp_POWER | ((uint32)1u << Opamp_OA_PUMP_CTRL_SHIFT);
}


/*******************************************************************************
* Function Name:   Opamp_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Buffer with the default values and
*  sets the power to the given level. A power level of 0, is same as
*  executing the stop function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Opamp_initVar: Used to check the initial configuration, modified
*  when this function is called for the first time.
*
*******************************************************************************/
void Opamp_Start(void)
{
    if(Opamp_initVar == 0u)
    {
        Opamp_initVar = 1u;
        Opamp_Init();
    }
    Opamp_Enable();
}


/*******************************************************************************
* Function Name: Opamp_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Opamp_Stop(void)
{
    Opamp_OA_RES_CTRL &= (~(uint32)(Opamp_OA_PWR_MODE_MASK |
        ((uint32)1u << Opamp_OA_PUMP_CTRL_SHIFT)));
}


/*******************************************************************************
* Function Name: Opamp_SetPower
********************************************************************************
*
* Summary:
*  Sets power level of Analog buffer.
*
* Parameters:
*  power: Sets power level between low (1) and high power (3).
*
* Return:
*  None
*
**********************************************************************************/
void Opamp_SetPower(uint32 power)
{
    Opamp_OA_RES_CTRL &= (~(uint32)Opamp_OA_PWR_MODE_MASK);
    Opamp_OA_RES_CTRL |= (power & Opamp_OA_PWR_MODE_MASK);
}


/*******************************************************************************
* Function Name: Opamp_PumpControl
********************************************************************************
*
* Summary:
*  Turns the boost pump on or off.
*
* Parameters:
*  onOff: Opamp_PUMPON, Opamp_PUMPOFF.
*
* Return:
*  None
*
**********************************************************************************/
void Opamp_PumpControl(uint32 onOff)
{
    Opamp_OA_RES_CTRL &= (~(uint32)Opamp_OA_PUMP_EN_MASK);
    Opamp_OA_RES_CTRL |= ((onOff & Opamp_PUMP_PROTECT_MASK)
        << Opamp_OA_PUMP_CTRL_SHIFT);
}


/* [] END OF FILE */
