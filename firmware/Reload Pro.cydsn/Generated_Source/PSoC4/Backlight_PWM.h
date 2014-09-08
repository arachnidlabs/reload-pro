/*******************************************************************************
* File Name: Backlight_PWM.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the Backlight_PWM
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_Backlight_PWM_H)
#define CY_TCPWM_Backlight_PWM_H

#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Backlight_PWM_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Backlight_PWM_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* TCPWM Configuration */
#define Backlight_PWM_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define Backlight_PWM_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define Backlight_PWM_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Backlight_PWM_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Backlight_PWM_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Backlight_PWM_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Backlight_PWM_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Backlight_PWM_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Backlight_PWM_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Backlight_PWM_TC_RUN_MODE                    (0lu)
#define Backlight_PWM_TC_COUNTER_MODE                (0lu)
#define Backlight_PWM_TC_COMP_CAP_MODE               (2lu)
#define Backlight_PWM_TC_PRESCALER                   (0lu)

/* Signal modes */
#define Backlight_PWM_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Backlight_PWM_TC_COUNT_SIGNAL_MODE           (3lu)
#define Backlight_PWM_TC_START_SIGNAL_MODE           (0lu)
#define Backlight_PWM_TC_STOP_SIGNAL_MODE            (0lu)
#define Backlight_PWM_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Backlight_PWM_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Backlight_PWM_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Backlight_PWM_TC_START_SIGNAL_PRESENT        (0lu)
#define Backlight_PWM_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Backlight_PWM_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Backlight_PWM_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define Backlight_PWM_PWM_KILL_EVENT                 (0lu)
#define Backlight_PWM_PWM_STOP_EVENT                 (0lu)
#define Backlight_PWM_PWM_MODE                       (4lu)
#define Backlight_PWM_PWM_OUT_N_INVERT               (0lu)
#define Backlight_PWM_PWM_OUT_INVERT                 (0lu)
#define Backlight_PWM_PWM_ALIGN                      (0lu)
#define Backlight_PWM_PWM_RUN_MODE                   (0lu)
#define Backlight_PWM_PWM_DEAD_TIME_CYCLE            (0lu)
#define Backlight_PWM_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Backlight_PWM_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Backlight_PWM_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Backlight_PWM_PWM_START_SIGNAL_MODE          (0lu)
#define Backlight_PWM_PWM_STOP_SIGNAL_MODE           (0lu)
#define Backlight_PWM_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Backlight_PWM_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Backlight_PWM_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Backlight_PWM_PWM_START_SIGNAL_PRESENT       (0lu)
#define Backlight_PWM_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Backlight_PWM_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Backlight_PWM_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Backlight_PWM_TC_PERIOD_VALUE                (65535lu)
#define Backlight_PWM_TC_COMPARE_VALUE               (65535lu)
#define Backlight_PWM_TC_COMPARE_BUF_VALUE           (65535lu)
#define Backlight_PWM_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Backlight_PWM_PWM_PERIOD_VALUE               (63lu)
#define Backlight_PWM_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Backlight_PWM_PWM_PERIOD_SWAP                (0lu)
#define Backlight_PWM_PWM_COMPARE_VALUE              (32lu)
#define Backlight_PWM_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Backlight_PWM_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Backlight_PWM__LEFT 0
#define Backlight_PWM__RIGHT 1
#define Backlight_PWM__CENTER 2
#define Backlight_PWM__ASYMMETRIC 3

#define Backlight_PWM__X1 0
#define Backlight_PWM__X2 1
#define Backlight_PWM__X4 2

#define Backlight_PWM__PWM 4
#define Backlight_PWM__PWM_DT 5
#define Backlight_PWM__PWM_PR 6

#define Backlight_PWM__INVERSE 1
#define Backlight_PWM__DIRECT 0

#define Backlight_PWM__CAPTURE 2
#define Backlight_PWM__COMPARE 0

#define Backlight_PWM__TRIG_LEVEL 3
#define Backlight_PWM__TRIG_RISING 0
#define Backlight_PWM__TRIG_FALLING 1
#define Backlight_PWM__TRIG_BOTH 2

#define Backlight_PWM__INTR_MASK_TC 1
#define Backlight_PWM__INTR_MASK_CC_MATCH 2
#define Backlight_PWM__INTR_MASK_NONE 0
#define Backlight_PWM__INTR_MASK_TC_CC 3

#define Backlight_PWM__UNCONFIG 8
#define Backlight_PWM__TIMER 1
#define Backlight_PWM__QUAD 3
#define Backlight_PWM__PWM_SEL 7

#define Backlight_PWM__COUNT_UP 0
#define Backlight_PWM__COUNT_DOWN 1
#define Backlight_PWM__COUNT_UPDOWN0 2
#define Backlight_PWM__COUNT_UPDOWN1 3


/* Prescaler */
#define Backlight_PWM_PRESCALE_DIVBY1                ((uint32)(0u << Backlight_PWM_PRESCALER_SHIFT))
#define Backlight_PWM_PRESCALE_DIVBY2                ((uint32)(1u << Backlight_PWM_PRESCALER_SHIFT))
#define Backlight_PWM_PRESCALE_DIVBY4                ((uint32)(2u << Backlight_PWM_PRESCALER_SHIFT))
#define Backlight_PWM_PRESCALE_DIVBY8                ((uint32)(3u << Backlight_PWM_PRESCALER_SHIFT))
#define Backlight_PWM_PRESCALE_DIVBY16               ((uint32)(4u << Backlight_PWM_PRESCALER_SHIFT))
#define Backlight_PWM_PRESCALE_DIVBY32               ((uint32)(5u << Backlight_PWM_PRESCALER_SHIFT))
#define Backlight_PWM_PRESCALE_DIVBY64               ((uint32)(6u << Backlight_PWM_PRESCALER_SHIFT))
#define Backlight_PWM_PRESCALE_DIVBY128              ((uint32)(7u << Backlight_PWM_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Backlight_PWM_MODE_TIMER_COMPARE             ((uint32)(Backlight_PWM__COMPARE         <<  \
                                                                  Backlight_PWM_MODE_SHIFT))
#define Backlight_PWM_MODE_TIMER_CAPTURE             ((uint32)(Backlight_PWM__CAPTURE         <<  \
                                                                  Backlight_PWM_MODE_SHIFT))
#define Backlight_PWM_MODE_QUAD                      ((uint32)(Backlight_PWM__QUAD            <<  \
                                                                  Backlight_PWM_MODE_SHIFT))
#define Backlight_PWM_MODE_PWM                       ((uint32)(Backlight_PWM__PWM             <<  \
                                                                  Backlight_PWM_MODE_SHIFT))
#define Backlight_PWM_MODE_PWM_DT                    ((uint32)(Backlight_PWM__PWM_DT          <<  \
                                                                  Backlight_PWM_MODE_SHIFT))
#define Backlight_PWM_MODE_PWM_PR                    ((uint32)(Backlight_PWM__PWM_PR          <<  \
                                                                  Backlight_PWM_MODE_SHIFT))

/* Quad Modes */
#define Backlight_PWM_MODE_X1                        ((uint32)(Backlight_PWM__X1              <<  \
                                                                  Backlight_PWM_QUAD_MODE_SHIFT))
#define Backlight_PWM_MODE_X2                        ((uint32)(Backlight_PWM__X2              <<  \
                                                                  Backlight_PWM_QUAD_MODE_SHIFT))
#define Backlight_PWM_MODE_X4                        ((uint32)(Backlight_PWM__X4              <<  \
                                                                  Backlight_PWM_QUAD_MODE_SHIFT))

/* Counter modes */
#define Backlight_PWM_COUNT_UP                       ((uint32)(Backlight_PWM__COUNT_UP        <<  \
                                                                  Backlight_PWM_UPDOWN_SHIFT))
#define Backlight_PWM_COUNT_DOWN                     ((uint32)(Backlight_PWM__COUNT_DOWN      <<  \
                                                                  Backlight_PWM_UPDOWN_SHIFT))
#define Backlight_PWM_COUNT_UPDOWN0                  ((uint32)(Backlight_PWM__COUNT_UPDOWN0   <<  \
                                                                  Backlight_PWM_UPDOWN_SHIFT))
#define Backlight_PWM_COUNT_UPDOWN1                  ((uint32)(Backlight_PWM__COUNT_UPDOWN1   <<  \
                                                                  Backlight_PWM_UPDOWN_SHIFT))

/* PWM output invert */
#define Backlight_PWM_INVERT_LINE                    ((uint32)(Backlight_PWM__INVERSE         <<  \
                                                                  Backlight_PWM_INV_OUT_SHIFT))
#define Backlight_PWM_INVERT_LINE_N                  ((uint32)(Backlight_PWM__INVERSE         <<  \
                                                                  Backlight_PWM_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Backlight_PWM_TRIG_RISING                    (Backlight_PWM__TRIG_RISING)
#define Backlight_PWM_TRIG_FALLING                   (Backlight_PWM__TRIG_FALLING)
#define Backlight_PWM_TRIG_BOTH                      (Backlight_PWM__TRIG_BOTH)
#define Backlight_PWM_TRIG_LEVEL                     (Backlight_PWM__TRIG_LEVEL)

/* Interrupt mask */
#define Backlight_PWM_INTR_MASK_TC                   (Backlight_PWM__INTR_MASK_TC)
#define Backlight_PWM_INTR_MASK_CC_MATCH             (Backlight_PWM__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Backlight_PWM_CC_MATCH_SET                   (0x00u)
#define Backlight_PWM_CC_MATCH_CLEAR                 (0x01u)
#define Backlight_PWM_CC_MATCH_INVERT                (0x02u)
#define Backlight_PWM_CC_MATCH_NO_CHANGE             (0x03u)
#define Backlight_PWM_OVERLOW_SET                    (0x00u)
#define Backlight_PWM_OVERLOW_CLEAR                  (0x04u)
#define Backlight_PWM_OVERLOW_INVERT                 (0x08u)
#define Backlight_PWM_OVERLOW_NO_CHANGE              (0x0Cu)
#define Backlight_PWM_UNDERFLOW_SET                  (0x00u)
#define Backlight_PWM_UNDERFLOW_CLEAR                (0x10u)
#define Backlight_PWM_UNDERFLOW_INVERT               (0x20u)
#define Backlight_PWM_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Backlight_PWM_PWM_MODE_LEFT                  (Backlight_PWM_CC_MATCH_CLEAR        |   \
                                                         Backlight_PWM_OVERLOW_SET           |   \
                                                         Backlight_PWM_UNDERFLOW_NO_CHANGE)
#define Backlight_PWM_PWM_MODE_RIGHT                 (Backlight_PWM_CC_MATCH_SET          |   \
                                                         Backlight_PWM_OVERLOW_NO_CHANGE     |   \
                                                         Backlight_PWM_UNDERFLOW_CLEAR)
#define Backlight_PWM_PWM_MODE_CENTER                (Backlight_PWM_CC_MATCH_INVERT       |   \
                                                         Backlight_PWM_OVERLOW_NO_CHANGE     |   \
                                                         Backlight_PWM_UNDERFLOW_CLEAR)
#define Backlight_PWM_PWM_MODE_ASYM                  (Backlight_PWM_CC_MATCH_NO_CHANGE    |   \
                                                         Backlight_PWM_OVERLOW_SET           |   \
                                                         Backlight_PWM_UNDERFLOW_CLEAR )

/* Command operations without condition */
#define Backlight_PWM_CMD_CAPTURE                    (0u)
#define Backlight_PWM_CMD_RELOAD                     (8u)
#define Backlight_PWM_CMD_STOP                       (16u)
#define Backlight_PWM_CMD_START                      (24u)

/* Status */
#define Backlight_PWM_STATUS_DOWN                    (1u)
#define Backlight_PWM_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Backlight_PWM_Init(void);
void   Backlight_PWM_Enable(void);
void   Backlight_PWM_Start(void);
void   Backlight_PWM_Stop(void);

void   Backlight_PWM_SetMode(uint32 mode);
void   Backlight_PWM_SetCounterMode(uint32 counterMode);
void   Backlight_PWM_SetPWMMode(uint32 modeMask);
void   Backlight_PWM_SetQDMode(uint32 qdMode);

void   Backlight_PWM_SetPrescaler(uint32 prescaler);
void   Backlight_PWM_TriggerCommand(uint32 mask, uint32 command);
void   Backlight_PWM_SetOneShot(uint32 oneShotEnable);
uint32 Backlight_PWM_ReadStatus(void);

void   Backlight_PWM_SetPWMSyncKill(uint32 syncKillEnable);
void   Backlight_PWM_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Backlight_PWM_SetPWMDeadTime(uint32 deadTime);
void   Backlight_PWM_SetPWMInvert(uint32 mask);

void   Backlight_PWM_SetInterruptMode(uint32 interruptMask);
uint32 Backlight_PWM_GetInterruptSourceMasked(void);
uint32 Backlight_PWM_GetInterruptSource(void);
void   Backlight_PWM_ClearInterrupt(uint32 interruptMask);
void   Backlight_PWM_SetInterrupt(uint32 interruptMask);

void   Backlight_PWM_WriteCounter(uint32 count);
uint32 Backlight_PWM_ReadCounter(void);

uint32 Backlight_PWM_ReadCapture(void);
uint32 Backlight_PWM_ReadCaptureBuf(void);

void   Backlight_PWM_WritePeriod(uint32 period);
uint32 Backlight_PWM_ReadPeriod(void);
void   Backlight_PWM_WritePeriodBuf(uint32 periodBuf);
uint32 Backlight_PWM_ReadPeriodBuf(void);

void   Backlight_PWM_WriteCompare(uint32 compare);
uint32 Backlight_PWM_ReadCompare(void);
void   Backlight_PWM_WriteCompareBuf(uint32 compareBuf);
uint32 Backlight_PWM_ReadCompareBuf(void);

void   Backlight_PWM_SetPeriodSwap(uint32 swapEnable);
void   Backlight_PWM_SetCompareSwap(uint32 swapEnable);

void   Backlight_PWM_SetCaptureMode(uint32 triggerMode);
void   Backlight_PWM_SetReloadMode(uint32 triggerMode);
void   Backlight_PWM_SetStartMode(uint32 triggerMode);
void   Backlight_PWM_SetStopMode(uint32 triggerMode);
void   Backlight_PWM_SetCountMode(uint32 triggerMode);

void   Backlight_PWM_SaveConfig(void);
void   Backlight_PWM_RestoreConfig(void);
void   Backlight_PWM_Sleep(void);
void   Backlight_PWM_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Backlight_PWM_BLOCK_CONTROL_REG              (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Backlight_PWM_BLOCK_CONTROL_PTR              ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Backlight_PWM_COMMAND_REG                    (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Backlight_PWM_COMMAND_PTR                    ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Backlight_PWM_INTRRUPT_CAUSE_REG             (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Backlight_PWM_INTRRUPT_CAUSE_PTR             ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Backlight_PWM_CONTROL_REG                    (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__CTRL )
#define Backlight_PWM_CONTROL_PTR                    ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__CTRL )
#define Backlight_PWM_STATUS_REG                     (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__STATUS )
#define Backlight_PWM_STATUS_PTR                     ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__STATUS )
#define Backlight_PWM_COUNTER_REG                    (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__COUNTER )
#define Backlight_PWM_COUNTER_PTR                    ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__COUNTER )
#define Backlight_PWM_COMP_CAP_REG                   (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__CC )
#define Backlight_PWM_COMP_CAP_PTR                   ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__CC )
#define Backlight_PWM_COMP_CAP_BUF_REG               (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define Backlight_PWM_COMP_CAP_BUF_PTR               ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define Backlight_PWM_PERIOD_REG                     (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__PERIOD )
#define Backlight_PWM_PERIOD_PTR                     ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__PERIOD )
#define Backlight_PWM_PERIOD_BUF_REG                 (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Backlight_PWM_PERIOD_BUF_PTR                 ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Backlight_PWM_TRIG_CONTROL0_REG              (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Backlight_PWM_TRIG_CONTROL0_PTR              ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Backlight_PWM_TRIG_CONTROL1_REG              (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Backlight_PWM_TRIG_CONTROL1_PTR              ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Backlight_PWM_TRIG_CONTROL2_REG              (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Backlight_PWM_TRIG_CONTROL2_PTR              ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Backlight_PWM_INTERRUPT_REQ_REG              (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__INTR )
#define Backlight_PWM_INTERRUPT_REQ_PTR              ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__INTR )
#define Backlight_PWM_INTERRUPT_SET_REG              (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__INTR_SET )
#define Backlight_PWM_INTERRUPT_SET_PTR              ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__INTR_SET )
#define Backlight_PWM_INTERRUPT_MASK_REG             (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define Backlight_PWM_INTERRUPT_MASK_PTR             ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define Backlight_PWM_INTERRUPT_MASKED_REG           (*(reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Backlight_PWM_INTERRUPT_MASKED_PTR           ( (reg32 *) Backlight_PWM_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Backlight_PWM_MASK                           ((uint32)Backlight_PWM_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Backlight_PWM_RELOAD_CC_SHIFT                (0u)
#define Backlight_PWM_RELOAD_PERIOD_SHIFT            (1u)
#define Backlight_PWM_PWM_SYNC_KILL_SHIFT            (2u)
#define Backlight_PWM_PWM_STOP_KILL_SHIFT            (3u)
#define Backlight_PWM_PRESCALER_SHIFT                (8u)
#define Backlight_PWM_UPDOWN_SHIFT                   (16u)
#define Backlight_PWM_ONESHOT_SHIFT                  (18u)
#define Backlight_PWM_QUAD_MODE_SHIFT                (20u)
#define Backlight_PWM_INV_OUT_SHIFT                  (20u)
#define Backlight_PWM_INV_COMPL_OUT_SHIFT            (21u)
#define Backlight_PWM_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Backlight_PWM_RELOAD_CC_MASK                 ((uint32)(Backlight_PWM_1BIT_MASK        <<  \
                                                                            Backlight_PWM_RELOAD_CC_SHIFT))
#define Backlight_PWM_RELOAD_PERIOD_MASK             ((uint32)(Backlight_PWM_1BIT_MASK        <<  \
                                                                            Backlight_PWM_RELOAD_PERIOD_SHIFT))
#define Backlight_PWM_PWM_SYNC_KILL_MASK             ((uint32)(Backlight_PWM_1BIT_MASK        <<  \
                                                                            Backlight_PWM_PWM_SYNC_KILL_SHIFT))
#define Backlight_PWM_PWM_STOP_KILL_MASK             ((uint32)(Backlight_PWM_1BIT_MASK        <<  \
                                                                            Backlight_PWM_PWM_STOP_KILL_SHIFT))
#define Backlight_PWM_PRESCALER_MASK                 ((uint32)(Backlight_PWM_8BIT_MASK        <<  \
                                                                            Backlight_PWM_PRESCALER_SHIFT))
#define Backlight_PWM_UPDOWN_MASK                    ((uint32)(Backlight_PWM_2BIT_MASK        <<  \
                                                                            Backlight_PWM_UPDOWN_SHIFT))
#define Backlight_PWM_ONESHOT_MASK                   ((uint32)(Backlight_PWM_1BIT_MASK        <<  \
                                                                            Backlight_PWM_ONESHOT_SHIFT))
#define Backlight_PWM_QUAD_MODE_MASK                 ((uint32)(Backlight_PWM_3BIT_MASK        <<  \
                                                                            Backlight_PWM_QUAD_MODE_SHIFT))
#define Backlight_PWM_INV_OUT_MASK                   ((uint32)(Backlight_PWM_2BIT_MASK        <<  \
                                                                            Backlight_PWM_INV_OUT_SHIFT))
#define Backlight_PWM_MODE_MASK                      ((uint32)(Backlight_PWM_3BIT_MASK        <<  \
                                                                            Backlight_PWM_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Backlight_PWM_CAPTURE_SHIFT                  (0u)
#define Backlight_PWM_COUNT_SHIFT                    (2u)
#define Backlight_PWM_RELOAD_SHIFT                   (4u)
#define Backlight_PWM_STOP_SHIFT                     (6u)
#define Backlight_PWM_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Backlight_PWM_CAPTURE_MASK                   ((uint32)(Backlight_PWM_2BIT_MASK        <<  \
                                                                  Backlight_PWM_CAPTURE_SHIFT))
#define Backlight_PWM_COUNT_MASK                     ((uint32)(Backlight_PWM_2BIT_MASK        <<  \
                                                                  Backlight_PWM_COUNT_SHIFT))
#define Backlight_PWM_RELOAD_MASK                    ((uint32)(Backlight_PWM_2BIT_MASK        <<  \
                                                                  Backlight_PWM_RELOAD_SHIFT))
#define Backlight_PWM_STOP_MASK                      ((uint32)(Backlight_PWM_2BIT_MASK        <<  \
                                                                  Backlight_PWM_STOP_SHIFT))
#define Backlight_PWM_START_MASK                     ((uint32)(Backlight_PWM_2BIT_MASK        <<  \
                                                                  Backlight_PWM_START_SHIFT))

/* MASK */
#define Backlight_PWM_1BIT_MASK                      ((uint32)0x01u)
#define Backlight_PWM_2BIT_MASK                      ((uint32)0x03u)
#define Backlight_PWM_3BIT_MASK                      ((uint32)0x07u)
#define Backlight_PWM_6BIT_MASK                      ((uint32)0x3Fu)
#define Backlight_PWM_8BIT_MASK                      ((uint32)0xFFu)
#define Backlight_PWM_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Backlight_PWM_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Backlight_PWM_PWM_PR_INIT_VALUE              (1u)

#endif /* End CY_TCPWM_Backlight_PWM_H */

/* [] END OF FILE */
