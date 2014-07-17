/*******************************************************************************
* File Name: QuadDec.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the QuadDec
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

#if !defined(CY_TCPWM_QuadDec_H)
#define CY_TCPWM_QuadDec_H

#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} QuadDec_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  QuadDec_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* TCPWM Configuration */
#define QuadDec_CONFIG                         (3lu)

/* Quad Mode */
/* Parameters */
#define QuadDec_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define QuadDec_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define QuadDec_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define QuadDec_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define QuadDec_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define QuadDec_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define QuadDec_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define QuadDec_QUAD_INTERRUPT_MASK            (0lu)

/* Timer/Counter Mode */
/* Parameters */
#define QuadDec_TC_RUN_MODE                    (0lu)
#define QuadDec_TC_COUNTER_MODE                (0lu)
#define QuadDec_TC_COMP_CAP_MODE               (2lu)
#define QuadDec_TC_PRESCALER                   (0lu)

/* Signal modes */
#define QuadDec_TC_RELOAD_SIGNAL_MODE          (0lu)
#define QuadDec_TC_COUNT_SIGNAL_MODE           (3lu)
#define QuadDec_TC_START_SIGNAL_MODE           (0lu)
#define QuadDec_TC_STOP_SIGNAL_MODE            (0lu)
#define QuadDec_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define QuadDec_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define QuadDec_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define QuadDec_TC_START_SIGNAL_PRESENT        (0lu)
#define QuadDec_TC_STOP_SIGNAL_PRESENT         (0lu)
#define QuadDec_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QuadDec_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define QuadDec_PWM_KILL_EVENT                 (0lu)
#define QuadDec_PWM_STOP_EVENT                 (0lu)
#define QuadDec_PWM_MODE                       (4lu)
#define QuadDec_PWM_OUT_N_INVERT               (0lu)
#define QuadDec_PWM_OUT_INVERT                 (0lu)
#define QuadDec_PWM_ALIGN                      (0lu)
#define QuadDec_PWM_RUN_MODE                   (0lu)
#define QuadDec_PWM_DEAD_TIME_CYCLE            (0lu)
#define QuadDec_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define QuadDec_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define QuadDec_PWM_COUNT_SIGNAL_MODE          (3lu)
#define QuadDec_PWM_START_SIGNAL_MODE          (0lu)
#define QuadDec_PWM_STOP_SIGNAL_MODE           (0lu)
#define QuadDec_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define QuadDec_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define QuadDec_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define QuadDec_PWM_START_SIGNAL_PRESENT       (0lu)
#define QuadDec_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define QuadDec_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QuadDec_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define QuadDec_TC_PERIOD_VALUE                (65535lu)
#define QuadDec_TC_COMPARE_VALUE               (65535lu)
#define QuadDec_TC_COMPARE_BUF_VALUE           (65535lu)
#define QuadDec_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define QuadDec_PWM_PERIOD_VALUE               (65535lu)
#define QuadDec_PWM_PERIOD_BUF_VALUE           (65535lu)
#define QuadDec_PWM_PERIOD_SWAP                (0lu)
#define QuadDec_PWM_COMPARE_VALUE              (65535lu)
#define QuadDec_PWM_COMPARE_BUF_VALUE          (65535lu)
#define QuadDec_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define QuadDec__LEFT 0
#define QuadDec__RIGHT 1
#define QuadDec__CENTER 2
#define QuadDec__ASYMMETRIC 3

#define QuadDec__X1 0
#define QuadDec__X2 1
#define QuadDec__X4 2

#define QuadDec__PWM 4
#define QuadDec__PWM_DT 5
#define QuadDec__PWM_PR 6

#define QuadDec__INVERSE 1
#define QuadDec__DIRECT 0

#define QuadDec__CAPTURE 2
#define QuadDec__COMPARE 0

#define QuadDec__TRIG_LEVEL 3
#define QuadDec__TRIG_RISING 0
#define QuadDec__TRIG_FALLING 1
#define QuadDec__TRIG_BOTH 2

#define QuadDec__INTR_MASK_TC 1
#define QuadDec__INTR_MASK_CC_MATCH 2
#define QuadDec__INTR_MASK_NONE 0
#define QuadDec__INTR_MASK_TC_CC 3

#define QuadDec__UNCONFIG 8
#define QuadDec__TIMER 1
#define QuadDec__QUAD 3
#define QuadDec__PWM_SEL 7

#define QuadDec__COUNT_UP 0
#define QuadDec__COUNT_DOWN 1
#define QuadDec__COUNT_UPDOWN0 2
#define QuadDec__COUNT_UPDOWN1 3


/* Prescaler */
#define QuadDec_PRESCALE_DIVBY1                ((uint32)(0u << QuadDec_PRESCALER_SHIFT))
#define QuadDec_PRESCALE_DIVBY2                ((uint32)(1u << QuadDec_PRESCALER_SHIFT))
#define QuadDec_PRESCALE_DIVBY4                ((uint32)(2u << QuadDec_PRESCALER_SHIFT))
#define QuadDec_PRESCALE_DIVBY8                ((uint32)(3u << QuadDec_PRESCALER_SHIFT))
#define QuadDec_PRESCALE_DIVBY16               ((uint32)(4u << QuadDec_PRESCALER_SHIFT))
#define QuadDec_PRESCALE_DIVBY32               ((uint32)(5u << QuadDec_PRESCALER_SHIFT))
#define QuadDec_PRESCALE_DIVBY64               ((uint32)(6u << QuadDec_PRESCALER_SHIFT))
#define QuadDec_PRESCALE_DIVBY128              ((uint32)(7u << QuadDec_PRESCALER_SHIFT))

/* TCPWM set modes */
#define QuadDec_MODE_TIMER_COMPARE             ((uint32)(QuadDec__COMPARE         <<  \
                                                                  QuadDec_MODE_SHIFT))
#define QuadDec_MODE_TIMER_CAPTURE             ((uint32)(QuadDec__CAPTURE         <<  \
                                                                  QuadDec_MODE_SHIFT))
#define QuadDec_MODE_QUAD                      ((uint32)(QuadDec__QUAD            <<  \
                                                                  QuadDec_MODE_SHIFT))
#define QuadDec_MODE_PWM                       ((uint32)(QuadDec__PWM             <<  \
                                                                  QuadDec_MODE_SHIFT))
#define QuadDec_MODE_PWM_DT                    ((uint32)(QuadDec__PWM_DT          <<  \
                                                                  QuadDec_MODE_SHIFT))
#define QuadDec_MODE_PWM_PR                    ((uint32)(QuadDec__PWM_PR          <<  \
                                                                  QuadDec_MODE_SHIFT))

/* Quad Modes */
#define QuadDec_MODE_X1                        ((uint32)(QuadDec__X1              <<  \
                                                                  QuadDec_QUAD_MODE_SHIFT))
#define QuadDec_MODE_X2                        ((uint32)(QuadDec__X2              <<  \
                                                                  QuadDec_QUAD_MODE_SHIFT))
#define QuadDec_MODE_X4                        ((uint32)(QuadDec__X4              <<  \
                                                                  QuadDec_QUAD_MODE_SHIFT))

/* Counter modes */
#define QuadDec_COUNT_UP                       ((uint32)(QuadDec__COUNT_UP        <<  \
                                                                  QuadDec_UPDOWN_SHIFT))
#define QuadDec_COUNT_DOWN                     ((uint32)(QuadDec__COUNT_DOWN      <<  \
                                                                  QuadDec_UPDOWN_SHIFT))
#define QuadDec_COUNT_UPDOWN0                  ((uint32)(QuadDec__COUNT_UPDOWN0   <<  \
                                                                  QuadDec_UPDOWN_SHIFT))
#define QuadDec_COUNT_UPDOWN1                  ((uint32)(QuadDec__COUNT_UPDOWN1   <<  \
                                                                  QuadDec_UPDOWN_SHIFT))

/* PWM output invert */
#define QuadDec_INVERT_LINE                    ((uint32)(QuadDec__INVERSE         <<  \
                                                                  QuadDec_INV_OUT_SHIFT))
#define QuadDec_INVERT_LINE_N                  ((uint32)(QuadDec__INVERSE         <<  \
                                                                  QuadDec_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define QuadDec_TRIG_RISING                    (QuadDec__TRIG_RISING)
#define QuadDec_TRIG_FALLING                   (QuadDec__TRIG_FALLING)
#define QuadDec_TRIG_BOTH                      (QuadDec__TRIG_BOTH)
#define QuadDec_TRIG_LEVEL                     (QuadDec__TRIG_LEVEL)

/* Interrupt mask */
#define QuadDec_INTR_MASK_TC                   (QuadDec__INTR_MASK_TC)
#define QuadDec_INTR_MASK_CC_MATCH             (QuadDec__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define QuadDec_CC_MATCH_SET                   (0x00u)
#define QuadDec_CC_MATCH_CLEAR                 (0x01u)
#define QuadDec_CC_MATCH_INVERT                (0x02u)
#define QuadDec_CC_MATCH_NO_CHANGE             (0x03u)
#define QuadDec_OVERLOW_SET                    (0x00u)
#define QuadDec_OVERLOW_CLEAR                  (0x04u)
#define QuadDec_OVERLOW_INVERT                 (0x08u)
#define QuadDec_OVERLOW_NO_CHANGE              (0x0Cu)
#define QuadDec_UNDERFLOW_SET                  (0x00u)
#define QuadDec_UNDERFLOW_CLEAR                (0x10u)
#define QuadDec_UNDERFLOW_INVERT               (0x20u)
#define QuadDec_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define QuadDec_PWM_MODE_LEFT                  (QuadDec_CC_MATCH_CLEAR        |   \
                                                         QuadDec_OVERLOW_SET           |   \
                                                         QuadDec_UNDERFLOW_NO_CHANGE)
#define QuadDec_PWM_MODE_RIGHT                 (QuadDec_CC_MATCH_SET          |   \
                                                         QuadDec_OVERLOW_NO_CHANGE     |   \
                                                         QuadDec_UNDERFLOW_CLEAR)
#define QuadDec_PWM_MODE_CENTER                (QuadDec_CC_MATCH_INVERT       |   \
                                                         QuadDec_OVERLOW_NO_CHANGE     |   \
                                                         QuadDec_UNDERFLOW_CLEAR)
#define QuadDec_PWM_MODE_ASYM                  (QuadDec_CC_MATCH_NO_CHANGE    |   \
                                                         QuadDec_OVERLOW_SET           |   \
                                                         QuadDec_UNDERFLOW_CLEAR )

/* Command operations without condition */
#define QuadDec_CMD_CAPTURE                    (0u)
#define QuadDec_CMD_RELOAD                     (8u)
#define QuadDec_CMD_STOP                       (16u)
#define QuadDec_CMD_START                      (24u)

/* Status */
#define QuadDec_STATUS_DOWN                    (1u)
#define QuadDec_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   QuadDec_Init(void);
void   QuadDec_Enable(void);
void   QuadDec_Start(void);
void   QuadDec_Stop(void);

void   QuadDec_SetMode(uint32 mode);
void   QuadDec_SetCounterMode(uint32 counterMode);
void   QuadDec_SetPWMMode(uint32 modeMask);
void   QuadDec_SetQDMode(uint32 qdMode);

void   QuadDec_SetPrescaler(uint32 prescaler);
void   QuadDec_TriggerCommand(uint32 mask, uint32 command);
void   QuadDec_SetOneShot(uint32 oneShotEnable);
uint32 QuadDec_ReadStatus(void);

void   QuadDec_SetPWMSyncKill(uint32 syncKillEnable);
void   QuadDec_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   QuadDec_SetPWMDeadTime(uint32 deadTime);
void   QuadDec_SetPWMInvert(uint32 mask);

void   QuadDec_SetInterruptMode(uint32 interruptMask);
uint32 QuadDec_GetInterruptSourceMasked(void);
uint32 QuadDec_GetInterruptSource(void);
void   QuadDec_ClearInterrupt(uint32 interruptMask);
void   QuadDec_SetInterrupt(uint32 interruptMask);

void   QuadDec_WriteCounter(uint32 count);
uint32 QuadDec_ReadCounter(void);

uint32 QuadDec_ReadCapture(void);
uint32 QuadDec_ReadCaptureBuf(void);

void   QuadDec_WritePeriod(uint32 period);
uint32 QuadDec_ReadPeriod(void);
void   QuadDec_WritePeriodBuf(uint32 periodBuf);
uint32 QuadDec_ReadPeriodBuf(void);

void   QuadDec_WriteCompare(uint32 compare);
uint32 QuadDec_ReadCompare(void);
void   QuadDec_WriteCompareBuf(uint32 compareBuf);
uint32 QuadDec_ReadCompareBuf(void);

void   QuadDec_SetPeriodSwap(uint32 swapEnable);
void   QuadDec_SetCompareSwap(uint32 swapEnable);

void   QuadDec_SetCaptureMode(uint32 triggerMode);
void   QuadDec_SetReloadMode(uint32 triggerMode);
void   QuadDec_SetStartMode(uint32 triggerMode);
void   QuadDec_SetStopMode(uint32 triggerMode);
void   QuadDec_SetCountMode(uint32 triggerMode);

void   QuadDec_SaveConfig(void);
void   QuadDec_RestoreConfig(void);
void   QuadDec_Sleep(void);
void   QuadDec_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define QuadDec_BLOCK_CONTROL_REG              (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QuadDec_BLOCK_CONTROL_PTR              ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QuadDec_COMMAND_REG                    (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QuadDec_COMMAND_PTR                    ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QuadDec_INTRRUPT_CAUSE_REG             (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QuadDec_INTRRUPT_CAUSE_PTR             ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QuadDec_CONTROL_REG                    (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__CTRL )
#define QuadDec_CONTROL_PTR                    ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__CTRL )
#define QuadDec_STATUS_REG                     (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__STATUS )
#define QuadDec_STATUS_PTR                     ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__STATUS )
#define QuadDec_COUNTER_REG                    (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__COUNTER )
#define QuadDec_COUNTER_PTR                    ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__COUNTER )
#define QuadDec_COMP_CAP_REG                   (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__CC )
#define QuadDec_COMP_CAP_PTR                   ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__CC )
#define QuadDec_COMP_CAP_BUF_REG               (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__CC_BUFF )
#define QuadDec_COMP_CAP_BUF_PTR               ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__CC_BUFF )
#define QuadDec_PERIOD_REG                     (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__PERIOD )
#define QuadDec_PERIOD_PTR                     ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__PERIOD )
#define QuadDec_PERIOD_BUF_REG                 (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QuadDec_PERIOD_BUF_PTR                 ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QuadDec_TRIG_CONTROL0_REG              (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QuadDec_TRIG_CONTROL0_PTR              ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QuadDec_TRIG_CONTROL1_REG              (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QuadDec_TRIG_CONTROL1_PTR              ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QuadDec_TRIG_CONTROL2_REG              (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QuadDec_TRIG_CONTROL2_PTR              ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QuadDec_INTERRUPT_REQ_REG              (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__INTR )
#define QuadDec_INTERRUPT_REQ_PTR              ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__INTR )
#define QuadDec_INTERRUPT_SET_REG              (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__INTR_SET )
#define QuadDec_INTERRUPT_SET_PTR              ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__INTR_SET )
#define QuadDec_INTERRUPT_MASK_REG             (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__INTR_MASK )
#define QuadDec_INTERRUPT_MASK_PTR             ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__INTR_MASK )
#define QuadDec_INTERRUPT_MASKED_REG           (*(reg32 *) QuadDec_cy_m0s8_tcpwm_1__INTR_MASKED )
#define QuadDec_INTERRUPT_MASKED_PTR           ( (reg32 *) QuadDec_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define QuadDec_MASK                           ((uint32)QuadDec_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define QuadDec_RELOAD_CC_SHIFT                (0u)
#define QuadDec_RELOAD_PERIOD_SHIFT            (1u)
#define QuadDec_PWM_SYNC_KILL_SHIFT            (2u)
#define QuadDec_PWM_STOP_KILL_SHIFT            (3u)
#define QuadDec_PRESCALER_SHIFT                (8u)
#define QuadDec_UPDOWN_SHIFT                   (16u)
#define QuadDec_ONESHOT_SHIFT                  (18u)
#define QuadDec_QUAD_MODE_SHIFT                (20u)
#define QuadDec_INV_OUT_SHIFT                  (20u)
#define QuadDec_INV_COMPL_OUT_SHIFT            (21u)
#define QuadDec_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define QuadDec_RELOAD_CC_MASK                 ((uint32)(QuadDec_1BIT_MASK        <<  \
                                                                            QuadDec_RELOAD_CC_SHIFT))
#define QuadDec_RELOAD_PERIOD_MASK             ((uint32)(QuadDec_1BIT_MASK        <<  \
                                                                            QuadDec_RELOAD_PERIOD_SHIFT))
#define QuadDec_PWM_SYNC_KILL_MASK             ((uint32)(QuadDec_1BIT_MASK        <<  \
                                                                            QuadDec_PWM_SYNC_KILL_SHIFT))
#define QuadDec_PWM_STOP_KILL_MASK             ((uint32)(QuadDec_1BIT_MASK        <<  \
                                                                            QuadDec_PWM_STOP_KILL_SHIFT))
#define QuadDec_PRESCALER_MASK                 ((uint32)(QuadDec_8BIT_MASK        <<  \
                                                                            QuadDec_PRESCALER_SHIFT))
#define QuadDec_UPDOWN_MASK                    ((uint32)(QuadDec_2BIT_MASK        <<  \
                                                                            QuadDec_UPDOWN_SHIFT))
#define QuadDec_ONESHOT_MASK                   ((uint32)(QuadDec_1BIT_MASK        <<  \
                                                                            QuadDec_ONESHOT_SHIFT))
#define QuadDec_QUAD_MODE_MASK                 ((uint32)(QuadDec_3BIT_MASK        <<  \
                                                                            QuadDec_QUAD_MODE_SHIFT))
#define QuadDec_INV_OUT_MASK                   ((uint32)(QuadDec_2BIT_MASK        <<  \
                                                                            QuadDec_INV_OUT_SHIFT))
#define QuadDec_MODE_MASK                      ((uint32)(QuadDec_3BIT_MASK        <<  \
                                                                            QuadDec_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define QuadDec_CAPTURE_SHIFT                  (0u)
#define QuadDec_COUNT_SHIFT                    (2u)
#define QuadDec_RELOAD_SHIFT                   (4u)
#define QuadDec_STOP_SHIFT                     (6u)
#define QuadDec_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define QuadDec_CAPTURE_MASK                   ((uint32)(QuadDec_2BIT_MASK        <<  \
                                                                  QuadDec_CAPTURE_SHIFT))
#define QuadDec_COUNT_MASK                     ((uint32)(QuadDec_2BIT_MASK        <<  \
                                                                  QuadDec_COUNT_SHIFT))
#define QuadDec_RELOAD_MASK                    ((uint32)(QuadDec_2BIT_MASK        <<  \
                                                                  QuadDec_RELOAD_SHIFT))
#define QuadDec_STOP_MASK                      ((uint32)(QuadDec_2BIT_MASK        <<  \
                                                                  QuadDec_STOP_SHIFT))
#define QuadDec_START_MASK                     ((uint32)(QuadDec_2BIT_MASK        <<  \
                                                                  QuadDec_START_SHIFT))

/* MASK */
#define QuadDec_1BIT_MASK                      ((uint32)0x01u)
#define QuadDec_2BIT_MASK                      ((uint32)0x03u)
#define QuadDec_3BIT_MASK                      ((uint32)0x07u)
#define QuadDec_6BIT_MASK                      ((uint32)0x3Fu)
#define QuadDec_8BIT_MASK                      ((uint32)0xFFu)
#define QuadDec_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define QuadDec_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define QuadDec_PWM_PR_INIT_VALUE              (1u)

#endif /* End CY_TCPWM_QuadDec_H */

/* [] END OF FILE */
