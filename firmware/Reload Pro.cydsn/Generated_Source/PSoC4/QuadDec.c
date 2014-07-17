/*******************************************************************************
* File Name: QuadDec.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the QuadDec
*  component
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

#include "QuadDec.h"
#include "CyLib.h"

uint8 QuadDec_initVar = 0u;


/*******************************************************************************
* Function Name: QuadDec_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default QuadDec configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (QuadDec__QUAD == QuadDec_CONFIG)
        QuadDec_CONTROL_REG =
        (((uint32)(QuadDec_QUAD_ENCODING_MODES     << QuadDec_QUAD_MODE_SHIFT))       |
         ((uint32)(QuadDec_CONFIG                  << QuadDec_MODE_SHIFT)));
    #endif  /* (QuadDec__QUAD == QuadDec_CONFIG) */

    #if (QuadDec__PWM_SEL == QuadDec_CONFIG)
        QuadDec_CONTROL_REG =
        (((uint32)(QuadDec_PWM_STOP_EVENT          << QuadDec_PWM_STOP_KILL_SHIFT))    |
         ((uint32)(QuadDec_PWM_OUT_INVERT          << QuadDec_INV_OUT_SHIFT))         |
         ((uint32)(QuadDec_PWM_OUT_N_INVERT        << QuadDec_INV_COMPL_OUT_SHIFT))     |
         ((uint32)(QuadDec_PWM_MODE                << QuadDec_MODE_SHIFT)));

        #if (QuadDec__PWM_PR == QuadDec_PWM_MODE)
            QuadDec_CONTROL_REG |=
            ((uint32)(QuadDec_PWM_RUN_MODE         << QuadDec_ONESHOT_SHIFT));

            QuadDec_WriteCounter(QuadDec_PWM_PR_INIT_VALUE);
        #else
            QuadDec_CONTROL_REG |=
            (((uint32)(QuadDec_PWM_ALIGN           << QuadDec_UPDOWN_SHIFT))          |
             ((uint32)(QuadDec_PWM_KILL_EVENT      << QuadDec_PWM_SYNC_KILL_SHIFT)));
        #endif  /* (QuadDec__PWM_PR == QuadDec_PWM_MODE) */

        #if (QuadDec__PWM_DT == QuadDec_PWM_MODE)
            QuadDec_CONTROL_REG |=
            ((uint32)(QuadDec_PWM_DEAD_TIME_CYCLE  << QuadDec_PRESCALER_SHIFT));
        #endif  /* (QuadDec__PWM_DT == QuadDec_PWM_MODE) */

        #if (QuadDec__PWM == QuadDec_PWM_MODE)
            QuadDec_CONTROL_REG |=
            ((uint32)QuadDec_PWM_PRESCALER         << QuadDec_PRESCALER_SHIFT);
        #endif  /* (QuadDec__PWM == QuadDec_PWM_MODE) */
    #endif  /* (QuadDec__PWM_SEL == QuadDec_CONFIG) */

    #if (QuadDec__TIMER == QuadDec_CONFIG)
        QuadDec_CONTROL_REG =
        (((uint32)(QuadDec_TC_PRESCALER            << QuadDec_PRESCALER_SHIFT))   |
         ((uint32)(QuadDec_TC_COUNTER_MODE         << QuadDec_UPDOWN_SHIFT))      |
         ((uint32)(QuadDec_TC_RUN_MODE             << QuadDec_ONESHOT_SHIFT))     |
         ((uint32)(QuadDec_TC_COMP_CAP_MODE        << QuadDec_MODE_SHIFT)));
    #endif  /* (QuadDec__TIMER == QuadDec_CONFIG) */

    /* Set values from customizer to CTRL1 */
    #if (QuadDec__QUAD == QuadDec_CONFIG)
        QuadDec_TRIG_CONTROL1_REG  =
        (((uint32)(QuadDec_QUAD_PHIA_SIGNAL_MODE   << QuadDec_COUNT_SHIFT))       |
         ((uint32)(QuadDec_QUAD_INDEX_SIGNAL_MODE  << QuadDec_RELOAD_SHIFT))      |
         ((uint32)(QuadDec_QUAD_STOP_SIGNAL_MODE   << QuadDec_STOP_SHIFT))        |
         ((uint32)(QuadDec_QUAD_PHIB_SIGNAL_MODE   << QuadDec_START_SHIFT)));
    #endif  /* (QuadDec__QUAD == QuadDec_CONFIG) */

    #if (QuadDec__PWM_SEL == QuadDec_CONFIG)
        QuadDec_TRIG_CONTROL1_REG  =
        (((uint32)(QuadDec_PWM_SWITCH_SIGNAL_MODE  << QuadDec_CAPTURE_SHIFT))     |
         ((uint32)(QuadDec_PWM_COUNT_SIGNAL_MODE   << QuadDec_COUNT_SHIFT))       |
         ((uint32)(QuadDec_PWM_RELOAD_SIGNAL_MODE  << QuadDec_RELOAD_SHIFT))      |
         ((uint32)(QuadDec_PWM_STOP_SIGNAL_MODE    << QuadDec_STOP_SHIFT))        |
         ((uint32)(QuadDec_PWM_START_SIGNAL_MODE   << QuadDec_START_SHIFT)));
    #endif  /* (QuadDec__PWM_SEL == QuadDec_CONFIG) */

    #if (QuadDec__TIMER == QuadDec_CONFIG)
        QuadDec_TRIG_CONTROL1_REG  =
        (((uint32)(QuadDec_TC_CAPTURE_SIGNAL_MODE  << QuadDec_CAPTURE_SHIFT))     |
         ((uint32)(QuadDec_TC_COUNT_SIGNAL_MODE    << QuadDec_COUNT_SHIFT))       |
         ((uint32)(QuadDec_TC_RELOAD_SIGNAL_MODE   << QuadDec_RELOAD_SHIFT))      |
         ((uint32)(QuadDec_TC_STOP_SIGNAL_MODE     << QuadDec_STOP_SHIFT))        |
         ((uint32)(QuadDec_TC_START_SIGNAL_MODE    << QuadDec_START_SHIFT)));
    #endif  /* (QuadDec__TIMER == QuadDec_CONFIG) */

    /* Set values from customizer to INTR */
    #if (QuadDec__QUAD == QuadDec_CONFIG)
        QuadDec_SetInterruptMode(QuadDec_QUAD_INTERRUPT_MASK);
    #endif  /* (QuadDec__QUAD == QuadDec_CONFIG) */

    #if (QuadDec__PWM_SEL == QuadDec_CONFIG)
        QuadDec_SetInterruptMode(QuadDec_PWM_INTERRUPT_MASK);
    #endif  /* (QuadDec__PWM_SEL == QuadDec_CONFIG) */

    #if (QuadDec__TIMER == QuadDec_CONFIG)
        QuadDec_SetInterruptMode(QuadDec_TC_INTERRUPT_MASK);
    #endif  /* (QuadDec__TIMER == QuadDec_CONFIG) */

    /* Set other values from customizer */
    #if (QuadDec__TIMER == QuadDec_CONFIG)
        QuadDec_WritePeriod(QuadDec_TC_PERIOD_VALUE );
        #if (QuadDec__COMPARE == QuadDec_TC_COMP_CAP_MODE)
            QuadDec_WriteCompare(QuadDec_TC_COMPARE_VALUE);

            #if (1u == QuadDec_TC_COMPARE_SWAP)
                QuadDec_SetCompareSwap(1u);
                QuadDec_WriteCompareBuf(QuadDec_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == QuadDec_TC_COMPARE_SWAP) */
        #endif  /* (QuadDec__COMPARE == QuadDec_TC_COMP_CAP_MODE) */
    #endif  /* (QuadDec__TIMER == QuadDec_CONFIG) */

    #if (QuadDec__PWM_SEL == QuadDec_CONFIG)
        QuadDec_WritePeriod(QuadDec_PWM_PERIOD_VALUE );
        QuadDec_WriteCompare(QuadDec_PWM_COMPARE_VALUE);

        #if (1u == QuadDec_PWM_COMPARE_SWAP)
            QuadDec_SetCompareSwap(1u);
            QuadDec_WriteCompareBuf(QuadDec_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == QuadDec_PWM_COMPARE_SWAP) */

        #if (1u == QuadDec_PWM_PERIOD_SWAP)
            QuadDec_SetPeriodSwap(1u);
            QuadDec_WritePeriodBuf(QuadDec_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == QuadDec_PWM_PERIOD_SWAP) */

        /* Set values from customizer to CTRL2 */
        #if (QuadDec__PWM_PR == QuadDec_PWM_MODE)
            QuadDec_TRIG_CONTROL2_REG =
                    (QuadDec_CC_MATCH_NO_CHANGE    |
                    QuadDec_OVERLOW_NO_CHANGE      |
                    QuadDec_UNDERFLOW_NO_CHANGE);
        #else
            #if (QuadDec__LEFT == QuadDec_PWM_ALIGN)
                QuadDec_TRIG_CONTROL2_REG = QuadDec_PWM_MODE_LEFT;
            #endif  /* ( QuadDec_PWM_LEFT == QuadDec_PWM_ALIGN) */

            #if (QuadDec__RIGHT == QuadDec_PWM_ALIGN)
                QuadDec_TRIG_CONTROL2_REG = QuadDec_PWM_MODE_RIGHT;
            #endif  /* ( QuadDec_PWM_RIGHT == QuadDec_PWM_ALIGN) */

            #if (QuadDec__CENTER == QuadDec_PWM_ALIGN)
                QuadDec_TRIG_CONTROL2_REG = QuadDec_PWM_MODE_CENTER;
            #endif  /* ( QuadDec_PWM_CENTER == QuadDec_PWM_ALIGN) */

            #if (QuadDec__ASYMMETRIC == QuadDec_PWM_ALIGN)
                QuadDec_TRIG_CONTROL2_REG = QuadDec_PWM_MODE_ASYM;
            #endif  /* (QuadDec__ASYMMETRIC == QuadDec_PWM_ALIGN) */
        #endif  /* (QuadDec__PWM_PR == QuadDec_PWM_MODE) */
    #endif  /* (QuadDec__PWM_SEL == QuadDec_CONFIG) */
}


/*******************************************************************************
* Function Name: QuadDec_Enable
********************************************************************************
*
* Summary:
*  Enables the QuadDec.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    QuadDec_BLOCK_CONTROL_REG |= QuadDec_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Statr Timer or PWM if start input is absent */
    #if (QuadDec__PWM_SEL == QuadDec_CONFIG)
        #if (0u == QuadDec_PWM_START_SIGNAL_PRESENT)
            QuadDec_TriggerCommand(QuadDec_MASK, QuadDec_CMD_START);
        #endif /* (0u == QuadDec_PWM_START_SIGNAL_PRESENT) */
    #endif /* (QuadDec__PWM_SEL == QuadDec_CONFIG) */

    #if (QuadDec__TIMER == QuadDec_CONFIG)
        #if (0u == QuadDec_TC_START_SIGNAL_PRESENT)
            QuadDec_TriggerCommand(QuadDec_MASK, QuadDec_CMD_START);
        #endif /* (0u == QuadDec_TC_START_SIGNAL_PRESENT) */
    #endif /* (QuadDec__TIMER == QuadDec_CONFIG) */
}


/*******************************************************************************
* Function Name: QuadDec_Start
********************************************************************************
*
* Summary:
*  Initialize the QuadDec with default customizer
*  values when called the first time and enables the QuadDec.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  QuadDec_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time QuadDec_Start() is called. This allows
*  enable/disable component without re-initialization in all subsequent calls
*  to the QuadDec_Start() routine.
*
*******************************************************************************/
void QuadDec_Start(void)
{
    if (0u == QuadDec_initVar)
    {
        QuadDec_Init();
        QuadDec_initVar = 1u;
    }

    QuadDec_Enable();
}


/*******************************************************************************
* Function Name: QuadDec_Stop
********************************************************************************
*
* Summary:
*  Disables the QuadDec.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_BLOCK_CONTROL_REG &= (uint32)~QuadDec_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the QuadDec. This function is used when
*  configured as a generic QuadDec and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the QuadDec to operate in
*   Values:
*   - QuadDec_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - QuadDec_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - QuadDec_MODE_QUAD - Quadrature decoder
*         - QuadDec_MODE_PWM - PWM
*         - QuadDec_MODE_PWM_DT - PWM with dead time
*         - QuadDec_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_CONTROL_REG &= (uint32)~QuadDec_MODE_MASK;
    QuadDec_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of 3 supported modes.
*  Is functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - QuadDec_MODE_X1 - Counts on phi 1 rising
*         - QuadDec_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - QuadDec_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_CONTROL_REG &= (uint32)~QuadDec_QUAD_MODE_MASK;
    QuadDec_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to PWM with dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - QuadDec_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - QuadDec_PRESCALE_DIVBY2    - Divide by 2
*         - QuadDec_PRESCALE_DIVBY4    - Divide by 4
*         - QuadDec_PRESCALE_DIVBY8    - Divide by 8
*         - QuadDec_PRESCALE_DIVBY16   - Divide by 16
*         - QuadDec_PRESCALE_DIVBY32   - Divide by 32
*         - QuadDec_PRESCALE_DIVBY64   - Divide by 64
*         - QuadDec_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_CONTROL_REG &= (uint32)~QuadDec_PRESCALER_MASK;
    QuadDec_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the QuadDec runs
*  continuously or stops when terminal count is reached.  By default the
*  QuadDec operates in continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_CONTROL_REG &= (uint32)~QuadDec_ONESHOT_MASK;
    QuadDec_CONTROL_REG |= ((uint32)((oneShotEnable & QuadDec_1BIT_MASK) <<
                                                               QuadDec_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the 3 must be ORed together to form the
*  mode.
*
* Parameters:
*  modeMask: Combination of the 3 mode settings.  Mask must include a value for
*  each of the 3 or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be 
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetPWMMode(uint32 modeMask)
{
    QuadDec_TRIG_CONTROL2_REG = (modeMask & QuadDec_6BIT_MASK);
}



/*******************************************************************************
* Function Name: QuadDec_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes an asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to PWM and
*  PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_CONTROL_REG &= (uint32)~QuadDec_PWM_SYNC_KILL_MASK;
    QuadDec_CONTROL_REG |= ((uint32)((syncKillEnable & QuadDec_1BIT_MASK)  <<
                                               QuadDec_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_CONTROL_REG &= (uint32)~QuadDec_PWM_STOP_KILL_MASK;
    QuadDec_CONTROL_REG |= ((uint32)((stopOnKillEnable & QuadDec_1BIT_MASK)  <<
                                                         QuadDec_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_CONTROL_REG &= (uint32)~QuadDec_PRESCALER_MASK;
    QuadDec_CONTROL_REG |= ((uint32)((deadTime & QuadDec_8BIT_MASK) <<
                                                          QuadDec_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - QuadDec_INVERT_LINE   - Inverts the line output
*         - QuadDec_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_CONTROL_REG &= (uint32)~QuadDec_INV_OUT_MASK;
    QuadDec_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: QuadDec_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_WriteCounter(uint32 count)
{
    QuadDec_COUNTER_REG = (count & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 QuadDec_ReadCounter(void)
{
    return (QuadDec_COUNTER_REG & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and PWM with pseudo random output.
*
* Parameters:
*  counterMode: Enumerated couner type values
*   Values:
*     - QuadDec_COUNT_UP       - Counts up
*     - QuadDec_COUNT_DOWN     - Counts down
*     - QuadDec_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - QuadDec_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_CONTROL_REG &= (uint32)~QuadDec_UPDOWN_MASK;
    QuadDec_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_WritePeriod(uint32 period)
{
    QuadDec_PERIOD_REG = (period & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 QuadDec_ReadPeriod(void)
{
    return (QuadDec_PERIOD_REG & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in Timer/Counter mode(without capture) the swap occurs
*  at a TC event. In PWM mode the swap occurs at the next TC event following
*  a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_CONTROL_REG &= (uint32)~QuadDec_RELOAD_CC_MASK;
    QuadDec_CONTROL_REG |= (swapEnable & QuadDec_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_WritePeriodBuf(uint32 periodBuf)
{
    QuadDec_PERIOD_BUF_REG = (periodBuf & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 QuadDec_ReadPeriodBuf(void)
{
    return (QuadDec_PERIOD_BUF_REG & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In PWM mode the swap occurs at the next TC event following a hardware switch
*  event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_CONTROL_REG &= (uint32)~QuadDec_RELOAD_PERIOD_MASK;
    QuadDec_CONTROL_REG |= ((uint32)((swapEnable & QuadDec_1BIT_MASK) <<
                                                            QuadDec_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_WriteCompare(uint32 compare)
{
    QuadDec_COMP_CAP_REG = (compare & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
*******************************************************************************/
uint32 QuadDec_ReadCompare(void)
{
    return (QuadDec_COMP_CAP_REG & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_WriteCompareBuf(uint32 compareBuf)
{
   QuadDec_COMP_CAP_BUF_REG = (compareBuf & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
*******************************************************************************/
uint32 QuadDec_ReadCompareBuf(void)
{
    return (QuadDec_COMP_CAP_BUF_REG & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 QuadDec_ReadCapture(void)
{
    return (QuadDec_COMP_CAP_REG & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 QuadDec_ReadCaptureBuf(void)
{
    return (QuadDec_COMP_CAP_BUF_REG & QuadDec_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QuadDec_TRIG_LEVEL     - Level
*     - QuadDec_TRIG_RISING    - Rising edge
*     - QuadDec_TRIG_FALLING   - Falling edge
*     - QuadDec_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_TRIG_CONTROL1_REG &= (uint32)~QuadDec_CAPTURE_MASK;
    QuadDec_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QuadDec_TRIG_LEVEL     - Level
*     - QuadDec_TRIG_RISING    - Rising edge
*     - QuadDec_TRIG_FALLING   - Falling edge
*     - QuadDec_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_TRIG_CONTROL1_REG &= (uint32)~QuadDec_RELOAD_MASK;
    QuadDec_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QuadDec_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QuadDec_TRIG_LEVEL     - Level
*     - QuadDec_TRIG_RISING    - Rising edge
*     - QuadDec_TRIG_FALLING   - Falling edge
*     - QuadDec_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_TRIG_CONTROL1_REG &= (uint32)~QuadDec_START_MASK;
    QuadDec_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QuadDec_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QuadDec_TRIG_LEVEL     - Level
*     - QuadDec_TRIG_RISING    - Rising edge
*     - QuadDec_TRIG_FALLING   - Falling edge
*     - QuadDec_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_TRIG_CONTROL1_REG &= (uint32)~QuadDec_STOP_MASK;
    QuadDec_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QuadDec_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QuadDec_TRIG_LEVEL     - Level
*     - QuadDec_TRIG_RISING    - Rising edge
*     - QuadDec_TRIG_FALLING   - Falling edge
*     - QuadDec_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_TRIG_CONTROL1_REG &= (uint32)~QuadDec_COUNT_MASK;
    QuadDec_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QuadDec_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: Combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - QuadDec_CMD_CAPTURE    - Trigger Capture command
*     - QuadDec_CMD_RELOAD     - Trigger Reload command
*     - QuadDec_CMD_STOP       - Trigger Stop command
*     - QuadDec_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QuadDec_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QuadDec_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the QuadDec.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - QuadDec_STATUS_DOWN    - Set if counting down
*     - QuadDec_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 QuadDec_ReadStatus(void)
{
    return ((QuadDec_STATUS_REG >> QuadDec_RUNNING_STATUS_SHIFT) |
            (QuadDec_STATUS_REG & QuadDec_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: QuadDec_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - QuadDec_INTR_MASK_TC       - Terminal count mask
*     - QuadDec_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetInterruptMode(uint32 interruptMask)
{
    QuadDec_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: QuadDec_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - QuadDec_INTR_MASK_TC       - Terminal count mask
*     - QuadDec_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 QuadDec_GetInterruptSourceMasked(void)
{
    return (QuadDec_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: QuadDec_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - QuadDec_INTR_MASK_TC       - Terminal count mask
*     - QuadDec_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 QuadDec_GetInterruptSource(void)
{
    return (QuadDec_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: QuadDec_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - QuadDec_INTR_MASK_TC       - Terminal count mask
*     - QuadDec_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_ClearInterrupt(uint32 interruptMask)
{
    QuadDec_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: QuadDec_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - QuadDec_INTR_MASK_TC       - Terminal count mask
*     - QuadDec_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void QuadDec_SetInterrupt(uint32 interruptMask)
{
    QuadDec_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
