/*******************************************************************************
* File Name: Opamp_1.h
* Version 1.0
*
* Description:
*  This file contains the function prototypes and constants used in
*  the OpAmp (Analog Buffer) Component.
*
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_Opamp_1_H)
#define CY_OPAMP_Opamp_1_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Data Struct Definition
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Opamp_1_BACKUP_STRUCT;

/* Component init state */
extern uint32 Opamp_1_initVar;


/**************************************
*        Function Prototypes
**************************************/
void Opamp_1_Init(void);
void Opamp_1_Enable(void);
void Opamp_1_Start(void);
void Opamp_1_Stop(void);
void Opamp_1_SetPower(uint32 power);
void Opamp_1_PumpControl(uint32 onOff);
void Opamp_1_Sleep(void);
void Opamp_1_Wakeup(void);
void Opamp_1_SaveConfig(void);
void Opamp_1_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/
#define Opamp_1_LOWPOWER                   (1u)
#define Opamp_1_MEDPOWER                   (2u)
#define Opamp_1_HIGHPOWER                  (3u)

#define Opamp_1_OUTPUT_CURRENT             (1u)
#define Opamp_1_POWER                      (3u)
#define Opamp_1_MODE                       (0u)
#define Opamp_1_OA_COMP_TRIM_VALUE         (3u)


/**************************************
*             Registers
**************************************/
#define Opamp_1_OA_CTRL                    (*(reg32 *)Opamp_1_cy_psoc4_abuf__CTBM_CTB_CTRL)
#define Opamp_1_OA_RES_CTRL                (*(reg32 *)Opamp_1_cy_psoc4_abuf__OA_RES_CTRL)
#define Opamp_1_OA_COMP_TRIM_REG           (*(reg32 *)Opamp_1_cy_psoc4_abuf__OA_COMP_TRIM)

/* Bit Field  OA_CTRL */
#define Opamp_1_OA_CTB_EN_SHIFT            (31u)

/* PUMP ON/OFF defines */
#define Opamp_1_PUMPON                     (1u)
#define Opamp_1_PUMPOFF                    (0u)

#define Opamp_1_PUMP_PROTECT_MASK          (1u)

/* Bit Field  OA_CTRL */
#define Opamp_1_OA_PWR_MODE_MASK           (0x3u)
#define Opamp_1_OA_DRIVE_STR_SEL_MASK      (0x4u)
#define Opamp_1_OA_DRIVE_STR_SEL_10X       (0x4u)
#define Opamp_1_OA_PUMP_EN_MASK            (0x800u)
#define Opamp_1_OA_PUMP_CTRL_SHIFT         (11u)

#endif    /* CY_OPAMP_Opamp_1_H */


/* [] END OF FILE */
