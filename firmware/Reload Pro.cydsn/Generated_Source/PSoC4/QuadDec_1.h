/*******************************************************************************
* File Name: QuadDec_1.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the QuadDec_1
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

#if !defined(CY_TCPWM_QuadDec_1_H)
#define CY_TCPWM_QuadDec_1_H

#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} QuadDec_1_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  QuadDec_1_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* TCPWM Configuration */
#define QuadDec_1_CONFIG                         (3lu)

/* Quad Mode */
/* Parameters */
#define QuadDec_1_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define QuadDec_1_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define QuadDec_1_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define QuadDec_1_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define QuadDec_1_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define QuadDec_1_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define QuadDec_1_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define QuadDec_1_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define QuadDec_1_TC_RUN_MODE                    (0lu)
#define QuadDec_1_TC_COUNTER_MODE                (0lu)
#define QuadDec_1_TC_COMP_CAP_MODE               (2lu)
#define QuadDec_1_TC_PRESCALER                   (0lu)

/* Signal modes */
#define QuadDec_1_TC_RELOAD_SIGNAL_MODE          (0lu)
#define QuadDec_1_TC_COUNT_SIGNAL_MODE           (3lu)
#define QuadDec_1_TC_START_SIGNAL_MODE           (0lu)
#define QuadDec_1_TC_STOP_SIGNAL_MODE            (0lu)
#define QuadDec_1_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define QuadDec_1_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define QuadDec_1_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define QuadDec_1_TC_START_SIGNAL_PRESENT        (0lu)
#define QuadDec_1_TC_STOP_SIGNAL_PRESENT         (0lu)
#define QuadDec_1_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QuadDec_1_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define QuadDec_1_PWM_KILL_EVENT                 (0lu)
#define QuadDec_1_PWM_STOP_EVENT                 (0lu)
#define QuadDec_1_PWM_MODE                       (4lu)
#define QuadDec_1_PWM_OUT_N_INVERT               (0lu)
#define QuadDec_1_PWM_OUT_INVERT                 (0lu)
#define QuadDec_1_PWM_ALIGN                      (0lu)
#define QuadDec_1_PWM_RUN_MODE                   (0lu)
#define QuadDec_1_PWM_DEAD_TIME_CYCLE            (0lu)
#define QuadDec_1_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define QuadDec_1_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define QuadDec_1_PWM_COUNT_SIGNAL_MODE          (3lu)
#define QuadDec_1_PWM_START_SIGNAL_MODE          (0lu)
#define QuadDec_1_PWM_STOP_SIGNAL_MODE           (0lu)
#define QuadDec_1_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define QuadDec_1_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define QuadDec_1_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define QuadDec_1_PWM_START_SIGNAL_PRESENT       (0lu)
#define QuadDec_1_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define QuadDec_1_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QuadDec_1_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define QuadDec_1_TC_PERIOD_VALUE                (65535lu)
#define QuadDec_1_TC_COMPARE_VALUE               (65535lu)
#define QuadDec_1_TC_COMPARE_BUF_VALUE           (65535lu)
#define QuadDec_1_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define QuadDec_1_PWM_PERIOD_VALUE               (65535lu)
#define QuadDec_1_PWM_PERIOD_BUF_VALUE           (65535lu)
#define QuadDec_1_PWM_PERIOD_SWAP                (0lu)
#define QuadDec_1_PWM_COMPARE_VALUE              (65535lu)
#define QuadDec_1_PWM_COMPARE_BUF_VALUE          (65535lu)
#define QuadDec_1_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define QuadDec_1__LEFT 0
#define QuadDec_1__RIGHT 1
#define QuadDec_1__CENTER 2
#define QuadDec_1__ASYMMETRIC 3

#define QuadDec_1__X1 0
#define QuadDec_1__X2 1
#define QuadDec_1__X4 2

#define QuadDec_1__PWM 4
#define QuadDec_1__PWM_DT 5
#define QuadDec_1__PWM_PR 6

#define QuadDec_1__INVERSE 1
#define QuadDec_1__DIRECT 0

#define QuadDec_1__CAPTURE 2
#define QuadDec_1__COMPARE 0

#define QuadDec_1__TRIG_LEVEL 3
#define QuadDec_1__TRIG_RISING 0
#define QuadDec_1__TRIG_FALLING 1
#define QuadDec_1__TRIG_BOTH 2

#define QuadDec_1__INTR_MASK_TC 1
#define QuadDec_1__INTR_MASK_CC_MATCH 2
#define QuadDec_1__INTR_MASK_NONE 0
#define QuadDec_1__INTR_MASK_TC_CC 3

#define QuadDec_1__UNCONFIG 8
#define QuadDec_1__TIMER 1
#define QuadDec_1__QUAD 3
#define QuadDec_1__PWM_SEL 7

#define QuadDec_1__COUNT_UP 0
#define QuadDec_1__COUNT_DOWN 1
#define QuadDec_1__COUNT_UPDOWN0 2
#define QuadDec_1__COUNT_UPDOWN1 3


/* Prescaler */
#define QuadDec_1_PRESCALE_DIVBY1                ((uint32)(0u << QuadDec_1_PRESCALER_SHIFT))
#define QuadDec_1_PRESCALE_DIVBY2                ((uint32)(1u << QuadDec_1_PRESCALER_SHIFT))
#define QuadDec_1_PRESCALE_DIVBY4                ((uint32)(2u << QuadDec_1_PRESCALER_SHIFT))
#define QuadDec_1_PRESCALE_DIVBY8                ((uint32)(3u << QuadDec_1_PRESCALER_SHIFT))
#define QuadDec_1_PRESCALE_DIVBY16               ((uint32)(4u << QuadDec_1_PRESCALER_SHIFT))
#define QuadDec_1_PRESCALE_DIVBY32               ((uint32)(5u << QuadDec_1_PRESCALER_SHIFT))
#define QuadDec_1_PRESCALE_DIVBY64               ((uint32)(6u << QuadDec_1_PRESCALER_SHIFT))
#define QuadDec_1_PRESCALE_DIVBY128              ((uint32)(7u << QuadDec_1_PRESCALER_SHIFT))

/* TCPWM set modes */
#define QuadDec_1_MODE_TIMER_COMPARE             ((uint32)(QuadDec_1__COMPARE         <<  \
                                                                  QuadDec_1_MODE_SHIFT))
#define QuadDec_1_MODE_TIMER_CAPTURE             ((uint32)(QuadDec_1__CAPTURE         <<  \
                                                                  QuadDec_1_MODE_SHIFT))
#define QuadDec_1_MODE_QUAD                      ((uint32)(QuadDec_1__QUAD            <<  \
                                                                  QuadDec_1_MODE_SHIFT))
#define QuadDec_1_MODE_PWM                       ((uint32)(QuadDec_1__PWM             <<  \
                                                                  QuadDec_1_MODE_SHIFT))
#define QuadDec_1_MODE_PWM_DT                    ((uint32)(QuadDec_1__PWM_DT          <<  \
                                                                  QuadDec_1_MODE_SHIFT))
#define QuadDec_1_MODE_PWM_PR                    ((uint32)(QuadDec_1__PWM_PR          <<  \
                                                                  QuadDec_1_MODE_SHIFT))

/* Quad Modes */
#define QuadDec_1_MODE_X1                        ((uint32)(QuadDec_1__X1              <<  \
                                                                  QuadDec_1_QUAD_MODE_SHIFT))
#define QuadDec_1_MODE_X2                        ((uint32)(QuadDec_1__X2              <<  \
                                                                  QuadDec_1_QUAD_MODE_SHIFT))
#define QuadDec_1_MODE_X4                        ((uint32)(QuadDec_1__X4              <<  \
                                                                  QuadDec_1_QUAD_MODE_SHIFT))

/* Counter modes */
#define QuadDec_1_COUNT_UP                       ((uint32)(QuadDec_1__COUNT_UP        <<  \
                                                                  QuadDec_1_UPDOWN_SHIFT))
#define QuadDec_1_COUNT_DOWN                     ((uint32)(QuadDec_1__COUNT_DOWN      <<  \
                                                                  QuadDec_1_UPDOWN_SHIFT))
#define QuadDec_1_COUNT_UPDOWN0                  ((uint32)(QuadDec_1__COUNT_UPDOWN0   <<  \
                                                                  QuadDec_1_UPDOWN_SHIFT))
#define QuadDec_1_COUNT_UPDOWN1                  ((uint32)(QuadDec_1__COUNT_UPDOWN1   <<  \
                                                                  QuadDec_1_UPDOWN_SHIFT))

/* PWM output invert */
#define QuadDec_1_INVERT_LINE                    ((uint32)(QuadDec_1__INVERSE         <<  \
                                                                  QuadDec_1_INV_OUT_SHIFT))
#define QuadDec_1_INVERT_LINE_N                  ((uint32)(QuadDec_1__INVERSE         <<  \
                                                                  QuadDec_1_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define QuadDec_1_TRIG_RISING                    (QuadDec_1__TRIG_RISING)
#define QuadDec_1_TRIG_FALLING                   (QuadDec_1__TRIG_FALLING)
#define QuadDec_1_TRIG_BOTH                      (QuadDec_1__TRIG_BOTH)
#define QuadDec_1_TRIG_LEVEL                     (QuadDec_1__TRIG_LEVEL)

/* Interrupt mask */
#define QuadDec_1_INTR_MASK_TC                   (QuadDec_1__INTR_MASK_TC)
#define QuadDec_1_INTR_MASK_CC_MATCH             (QuadDec_1__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define QuadDec_1_CC_MATCH_SET                   (0x00u)
#define QuadDec_1_CC_MATCH_CLEAR                 (0x01u)
#define QuadDec_1_CC_MATCH_INVERT                (0x02u)
#define QuadDec_1_CC_MATCH_NO_CHANGE             (0x03u)
#define QuadDec_1_OVERLOW_SET                    (0x00u)
#define QuadDec_1_OVERLOW_CLEAR                  (0x04u)
#define QuadDec_1_OVERLOW_INVERT                 (0x08u)
#define QuadDec_1_OVERLOW_NO_CHANGE              (0x0Cu)
#define QuadDec_1_UNDERFLOW_SET                  (0x00u)
#define QuadDec_1_UNDERFLOW_CLEAR                (0x10u)
#define QuadDec_1_UNDERFLOW_INVERT               (0x20u)
#define QuadDec_1_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define QuadDec_1_PWM_MODE_LEFT                  (QuadDec_1_CC_MATCH_CLEAR        |   \
                                                         QuadDec_1_OVERLOW_SET           |   \
                                                         QuadDec_1_UNDERFLOW_NO_CHANGE)
#define QuadDec_1_PWM_MODE_RIGHT                 (QuadDec_1_CC_MATCH_SET          |   \
                                                         QuadDec_1_OVERLOW_NO_CHANGE     |   \
                                                         QuadDec_1_UNDERFLOW_CLEAR)
#define QuadDec_1_PWM_MODE_CENTER                (QuadDec_1_CC_MATCH_INVERT       |   \
                                                         QuadDec_1_OVERLOW_NO_CHANGE     |   \
                                                         QuadDec_1_UNDERFLOW_CLEAR)
#define QuadDec_1_PWM_MODE_ASYM                  (QuadDec_1_CC_MATCH_NO_CHANGE    |   \
                                                         QuadDec_1_OVERLOW_SET           |   \
                                                         QuadDec_1_UNDERFLOW_CLEAR )

/* Command operations without condition */
#define QuadDec_1_CMD_CAPTURE                    (0u)
#define QuadDec_1_CMD_RELOAD                     (8u)
#define QuadDec_1_CMD_STOP                       (16u)
#define QuadDec_1_CMD_START                      (24u)

/* Status */
#define QuadDec_1_STATUS_DOWN                    (1u)
#define QuadDec_1_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   QuadDec_1_Init(void);
void   QuadDec_1_Enable(void);
void   QuadDec_1_Start(void);
void   QuadDec_1_Stop(void);

void   QuadDec_1_SetMode(uint32 mode);
void   QuadDec_1_SetCounterMode(uint32 counterMode);
void   QuadDec_1_SetPWMMode(uint32 modeMask);
void   QuadDec_1_SetQDMode(uint32 qdMode);

void   QuadDec_1_SetPrescaler(uint32 prescaler);
void   QuadDec_1_TriggerCommand(uint32 mask, uint32 command);
void   QuadDec_1_SetOneShot(uint32 oneShotEnable);
uint32 QuadDec_1_ReadStatus(void);

void   QuadDec_1_SetPWMSyncKill(uint32 syncKillEnable);
void   QuadDec_1_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   QuadDec_1_SetPWMDeadTime(uint32 deadTime);
void   QuadDec_1_SetPWMInvert(uint32 mask);

void   QuadDec_1_SetInterruptMode(uint32 interruptMask);
uint32 QuadDec_1_GetInterruptSourceMasked(void);
uint32 QuadDec_1_GetInterruptSource(void);
void   QuadDec_1_ClearInterrupt(uint32 interruptMask);
void   QuadDec_1_SetInterrupt(uint32 interruptMask);

void   QuadDec_1_WriteCounter(uint32 count);
uint32 QuadDec_1_ReadCounter(void);

uint32 QuadDec_1_ReadCapture(void);
uint32 QuadDec_1_ReadCaptureBuf(void);

void   QuadDec_1_WritePeriod(uint32 period);
uint32 QuadDec_1_ReadPeriod(void);
void   QuadDec_1_WritePeriodBuf(uint32 periodBuf);
uint32 QuadDec_1_ReadPeriodBuf(void);

void   QuadDec_1_WriteCompare(uint32 compare);
uint32 QuadDec_1_ReadCompare(void);
void   QuadDec_1_WriteCompareBuf(uint32 compareBuf);
uint32 QuadDec_1_ReadCompareBuf(void);

void   QuadDec_1_SetPeriodSwap(uint32 swapEnable);
void   QuadDec_1_SetCompareSwap(uint32 swapEnable);

void   QuadDec_1_SetCaptureMode(uint32 triggerMode);
void   QuadDec_1_SetReloadMode(uint32 triggerMode);
void   QuadDec_1_SetStartMode(uint32 triggerMode);
void   QuadDec_1_SetStopMode(uint32 triggerMode);
void   QuadDec_1_SetCountMode(uint32 triggerMode);

void   QuadDec_1_SaveConfig(void);
void   QuadDec_1_RestoreConfig(void);
void   QuadDec_1_Sleep(void);
void   QuadDec_1_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define QuadDec_1_BLOCK_CONTROL_REG              (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QuadDec_1_BLOCK_CONTROL_PTR              ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QuadDec_1_COMMAND_REG                    (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QuadDec_1_COMMAND_PTR                    ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QuadDec_1_INTRRUPT_CAUSE_REG             (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QuadDec_1_INTRRUPT_CAUSE_PTR             ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QuadDec_1_CONTROL_REG                    (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__CTRL )
#define QuadDec_1_CONTROL_PTR                    ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__CTRL )
#define QuadDec_1_STATUS_REG                     (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__STATUS )
#define QuadDec_1_STATUS_PTR                     ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__STATUS )
#define QuadDec_1_COUNTER_REG                    (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__COUNTER )
#define QuadDec_1_COUNTER_PTR                    ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__COUNTER )
#define QuadDec_1_COMP_CAP_REG                   (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__CC )
#define QuadDec_1_COMP_CAP_PTR                   ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__CC )
#define QuadDec_1_COMP_CAP_BUF_REG               (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__CC_BUFF )
#define QuadDec_1_COMP_CAP_BUF_PTR               ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__CC_BUFF )
#define QuadDec_1_PERIOD_REG                     (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__PERIOD )
#define QuadDec_1_PERIOD_PTR                     ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__PERIOD )
#define QuadDec_1_PERIOD_BUF_REG                 (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QuadDec_1_PERIOD_BUF_PTR                 ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QuadDec_1_TRIG_CONTROL0_REG              (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QuadDec_1_TRIG_CONTROL0_PTR              ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QuadDec_1_TRIG_CONTROL1_REG              (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QuadDec_1_TRIG_CONTROL1_PTR              ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QuadDec_1_TRIG_CONTROL2_REG              (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QuadDec_1_TRIG_CONTROL2_PTR              ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QuadDec_1_INTERRUPT_REQ_REG              (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__INTR )
#define QuadDec_1_INTERRUPT_REQ_PTR              ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__INTR )
#define QuadDec_1_INTERRUPT_SET_REG              (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__INTR_SET )
#define QuadDec_1_INTERRUPT_SET_PTR              ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__INTR_SET )
#define QuadDec_1_INTERRUPT_MASK_REG             (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__INTR_MASK )
#define QuadDec_1_INTERRUPT_MASK_PTR             ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__INTR_MASK )
#define QuadDec_1_INTERRUPT_MASKED_REG           (*(reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__INTR_MASKED )
#define QuadDec_1_INTERRUPT_MASKED_PTR           ( (reg32 *) QuadDec_1_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define QuadDec_1_MASK                           ((uint32)QuadDec_1_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define QuadDec_1_RELOAD_CC_SHIFT                (0u)
#define QuadDec_1_RELOAD_PERIOD_SHIFT            (1u)
#define QuadDec_1_PWM_SYNC_KILL_SHIFT            (2u)
#define QuadDec_1_PWM_STOP_KILL_SHIFT            (3u)
#define QuadDec_1_PRESCALER_SHIFT                (8u)
#define QuadDec_1_UPDOWN_SHIFT                   (16u)
#define QuadDec_1_ONESHOT_SHIFT                  (18u)
#define QuadDec_1_QUAD_MODE_SHIFT                (20u)
#define QuadDec_1_INV_OUT_SHIFT                  (20u)
#define QuadDec_1_INV_COMPL_OUT_SHIFT            (21u)
#define QuadDec_1_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define QuadDec_1_RELOAD_CC_MASK                 ((uint32)(QuadDec_1_1BIT_MASK        <<  \
                                                                            QuadDec_1_RELOAD_CC_SHIFT))
#define QuadDec_1_RELOAD_PERIOD_MASK             ((uint32)(QuadDec_1_1BIT_MASK        <<  \
                                                                            QuadDec_1_RELOAD_PERIOD_SHIFT))
#define QuadDec_1_PWM_SYNC_KILL_MASK             ((uint32)(QuadDec_1_1BIT_MASK        <<  \
                                                                            QuadDec_1_PWM_SYNC_KILL_SHIFT))
#define QuadDec_1_PWM_STOP_KILL_MASK             ((uint32)(QuadDec_1_1BIT_MASK        <<  \
                                                                            QuadDec_1_PWM_STOP_KILL_SHIFT))
#define QuadDec_1_PRESCALER_MASK                 ((uint32)(QuadDec_1_8BIT_MASK        <<  \
                                                                            QuadDec_1_PRESCALER_SHIFT))
#define QuadDec_1_UPDOWN_MASK                    ((uint32)(QuadDec_1_2BIT_MASK        <<  \
                                                                            QuadDec_1_UPDOWN_SHIFT))
#define QuadDec_1_ONESHOT_MASK                   ((uint32)(QuadDec_1_1BIT_MASK        <<  \
                                                                            QuadDec_1_ONESHOT_SHIFT))
#define QuadDec_1_QUAD_MODE_MASK                 ((uint32)(QuadDec_1_3BIT_MASK        <<  \
                                                                            QuadDec_1_QUAD_MODE_SHIFT))
#define QuadDec_1_INV_OUT_MASK                   ((uint32)(QuadDec_1_2BIT_MASK        <<  \
                                                                            QuadDec_1_INV_OUT_SHIFT))
#define QuadDec_1_MODE_MASK                      ((uint32)(QuadDec_1_3BIT_MASK        <<  \
                                                                            QuadDec_1_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define QuadDec_1_CAPTURE_SHIFT                  (0u)
#define QuadDec_1_COUNT_SHIFT                    (2u)
#define QuadDec_1_RELOAD_SHIFT                   (4u)
#define QuadDec_1_STOP_SHIFT                     (6u)
#define QuadDec_1_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define QuadDec_1_CAPTURE_MASK                   ((uint32)(QuadDec_1_2BIT_MASK        <<  \
                                                                  QuadDec_1_CAPTURE_SHIFT))
#define QuadDec_1_COUNT_MASK                     ((uint32)(QuadDec_1_2BIT_MASK        <<  \
                                                                  QuadDec_1_COUNT_SHIFT))
#define QuadDec_1_RELOAD_MASK                    ((uint32)(QuadDec_1_2BIT_MASK        <<  \
                                                                  QuadDec_1_RELOAD_SHIFT))
#define QuadDec_1_STOP_MASK                      ((uint32)(QuadDec_1_2BIT_MASK        <<  \
                                                                  QuadDec_1_STOP_SHIFT))
#define QuadDec_1_START_MASK                     ((uint32)(QuadDec_1_2BIT_MASK        <<  \
                                                                  QuadDec_1_START_SHIFT))

/* MASK */
#define QuadDec_1_1BIT_MASK                      ((uint32)0x01u)
#define QuadDec_1_2BIT_MASK                      ((uint32)0x03u)
#define QuadDec_1_3BIT_MASK                      ((uint32)0x07u)
#define QuadDec_1_6BIT_MASK                      ((uint32)0x3Fu)
#define QuadDec_1_8BIT_MASK                      ((uint32)0xFFu)
#define QuadDec_1_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define QuadDec_1_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define QuadDec_1_PWM_PR_INIT_VALUE              (1u)

#endif /* End CY_TCPWM_QuadDec_1_H */

/* [] END OF FILE */
