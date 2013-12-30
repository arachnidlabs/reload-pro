/*******************************************************************************
* File Name: Backlight_PWM.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the Backlight_PWM
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

#include "Backlight_PWM.h"
#include "CyLib.h"

uint8 Backlight_PWM_initVar = 0u;


/*******************************************************************************
* Function Name: Backlight_PWM_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Backlight_PWM configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Backlight_PWM__QUAD == Backlight_PWM_CONFIG)
        Backlight_PWM_CONTROL_REG =
        (((uint32)(Backlight_PWM_QUAD_ENCODING_MODES     << Backlight_PWM_QUAD_MODE_SHIFT))       |
         ((uint32)(Backlight_PWM_CONFIG                  << Backlight_PWM_MODE_SHIFT)));
    #endif  /* (Backlight_PWM__QUAD == Backlight_PWM_CONFIG) */

    #if (Backlight_PWM__PWM_SEL == Backlight_PWM_CONFIG)
        Backlight_PWM_CONTROL_REG =
        (((uint32)(Backlight_PWM_PWM_STOP_EVENT          << Backlight_PWM_PWM_STOP_KILL_SHIFT))    |
         ((uint32)(Backlight_PWM_PWM_OUT_INVERT          << Backlight_PWM_INV_OUT_SHIFT))         |
         ((uint32)(Backlight_PWM_PWM_OUT_N_INVERT        << Backlight_PWM_INV_COMPL_OUT_SHIFT))     |
         ((uint32)(Backlight_PWM_PWM_MODE                << Backlight_PWM_MODE_SHIFT)));

        #if (Backlight_PWM__PWM_PR == Backlight_PWM_PWM_MODE)
            Backlight_PWM_CONTROL_REG |=
            ((uint32)(Backlight_PWM_PWM_RUN_MODE         << Backlight_PWM_ONESHOT_SHIFT));

            Backlight_PWM_WriteCounter(Backlight_PWM_PWM_PR_INIT_VALUE);
        #else
            Backlight_PWM_CONTROL_REG |=
            (((uint32)(Backlight_PWM_PWM_ALIGN           << Backlight_PWM_UPDOWN_SHIFT))          |
             ((uint32)(Backlight_PWM_PWM_KILL_EVENT      << Backlight_PWM_PWM_SYNC_KILL_SHIFT)));
        #endif  /* (Backlight_PWM__PWM_PR == Backlight_PWM_PWM_MODE) */

        #if (Backlight_PWM__PWM_DT == Backlight_PWM_PWM_MODE)
            Backlight_PWM_CONTROL_REG |=
            ((uint32)(Backlight_PWM_PWM_DEAD_TIME_CYCLE  << Backlight_PWM_PRESCALER_SHIFT));
        #endif  /* (Backlight_PWM__PWM_DT == Backlight_PWM_PWM_MODE) */

        #if (Backlight_PWM__PWM == Backlight_PWM_PWM_MODE)
            Backlight_PWM_CONTROL_REG |=
            ((uint32)Backlight_PWM_PWM_PRESCALER         << Backlight_PWM_PRESCALER_SHIFT);
        #endif  /* (Backlight_PWM__PWM == Backlight_PWM_PWM_MODE) */
    #endif  /* (Backlight_PWM__PWM_SEL == Backlight_PWM_CONFIG) */

    #if (Backlight_PWM__TIMER == Backlight_PWM_CONFIG)
        Backlight_PWM_CONTROL_REG =
        (((uint32)(Backlight_PWM_TC_PRESCALER            << Backlight_PWM_PRESCALER_SHIFT))   |
         ((uint32)(Backlight_PWM_TC_COUNTER_MODE         << Backlight_PWM_UPDOWN_SHIFT))      |
         ((uint32)(Backlight_PWM_TC_RUN_MODE             << Backlight_PWM_ONESHOT_SHIFT))     |
         ((uint32)(Backlight_PWM_TC_COMP_CAP_MODE        << Backlight_PWM_MODE_SHIFT)));
    #endif  /* (Backlight_PWM__TIMER == Backlight_PWM_CONFIG) */

    /* Set values from customizer to CTRL1 */
    #if (Backlight_PWM__QUAD == Backlight_PWM_CONFIG)
        Backlight_PWM_TRIG_CONTROL1_REG  =
        (((uint32)(Backlight_PWM_QUAD_PHIA_SIGNAL_MODE   << Backlight_PWM_COUNT_SHIFT))       |
         ((uint32)(Backlight_PWM_QUAD_INDEX_SIGNAL_MODE  << Backlight_PWM_RELOAD_SHIFT))      |
         ((uint32)(Backlight_PWM_QUAD_STOP_SIGNAL_MODE   << Backlight_PWM_STOP_SHIFT))        |
         ((uint32)(Backlight_PWM_QUAD_PHIB_SIGNAL_MODE   << Backlight_PWM_START_SHIFT)));
    #endif  /* (Backlight_PWM__QUAD == Backlight_PWM_CONFIG) */

    #if (Backlight_PWM__PWM_SEL == Backlight_PWM_CONFIG)
        Backlight_PWM_TRIG_CONTROL1_REG  =
        (((uint32)(Backlight_PWM_PWM_SWITCH_SIGNAL_MODE  << Backlight_PWM_CAPTURE_SHIFT))     |
         ((uint32)(Backlight_PWM_PWM_COUNT_SIGNAL_MODE   << Backlight_PWM_COUNT_SHIFT))       |
         ((uint32)(Backlight_PWM_PWM_RELOAD_SIGNAL_MODE  << Backlight_PWM_RELOAD_SHIFT))      |
         ((uint32)(Backlight_PWM_PWM_STOP_SIGNAL_MODE    << Backlight_PWM_STOP_SHIFT))        |
         ((uint32)(Backlight_PWM_PWM_START_SIGNAL_MODE   << Backlight_PWM_START_SHIFT)));
    #endif  /* (Backlight_PWM__PWM_SEL == Backlight_PWM_CONFIG) */

    #if (Backlight_PWM__TIMER == Backlight_PWM_CONFIG)
        Backlight_PWM_TRIG_CONTROL1_REG  =
        (((uint32)(Backlight_PWM_TC_CAPTURE_SIGNAL_MODE  << Backlight_PWM_CAPTURE_SHIFT))     |
         ((uint32)(Backlight_PWM_TC_COUNT_SIGNAL_MODE    << Backlight_PWM_COUNT_SHIFT))       |
         ((uint32)(Backlight_PWM_TC_RELOAD_SIGNAL_MODE   << Backlight_PWM_RELOAD_SHIFT))      |
         ((uint32)(Backlight_PWM_TC_STOP_SIGNAL_MODE     << Backlight_PWM_STOP_SHIFT))        |
         ((uint32)(Backlight_PWM_TC_START_SIGNAL_MODE    << Backlight_PWM_START_SHIFT)));
    #endif  /* (Backlight_PWM__TIMER == Backlight_PWM_CONFIG) */

    /* Set values from customizer to INTR */
    #if (Backlight_PWM__QUAD == Backlight_PWM_CONFIG)
        Backlight_PWM_SetInterruptMode(Backlight_PWM_QUAD_INTERRUPT_MASK);
    #endif  /* (Backlight_PWM__QUAD == Backlight_PWM_CONFIG) */

    #if (Backlight_PWM__PWM_SEL == Backlight_PWM_CONFIG)
        Backlight_PWM_SetInterruptMode(Backlight_PWM_PWM_INTERRUPT_MASK);
    #endif  /* (Backlight_PWM__PWM_SEL == Backlight_PWM_CONFIG) */

    #if (Backlight_PWM__TIMER == Backlight_PWM_CONFIG)
        Backlight_PWM_SetInterruptMode(Backlight_PWM_TC_INTERRUPT_MASK);
    #endif  /* (Backlight_PWM__TIMER == Backlight_PWM_CONFIG) */

    /* Set other values from customizer */
    #if (Backlight_PWM__TIMER == Backlight_PWM_CONFIG)
        Backlight_PWM_WritePeriod(Backlight_PWM_TC_PERIOD_VALUE );
        #if (Backlight_PWM__COMPARE == Backlight_PWM_TC_COMP_CAP_MODE)
            Backlight_PWM_WriteCompare(Backlight_PWM_TC_COMPARE_VALUE);

            #if (1u == Backlight_PWM_TC_COMPARE_SWAP)
                Backlight_PWM_SetCompareSwap(1u);
                Backlight_PWM_WriteCompareBuf(Backlight_PWM_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Backlight_PWM_TC_COMPARE_SWAP) */
        #endif  /* (Backlight_PWM__COMPARE == Backlight_PWM_TC_COMP_CAP_MODE) */
    #endif  /* (Backlight_PWM__TIMER == Backlight_PWM_CONFIG) */

    #if (Backlight_PWM__PWM_SEL == Backlight_PWM_CONFIG)
        Backlight_PWM_WritePeriod(Backlight_PWM_PWM_PERIOD_VALUE );
        Backlight_PWM_WriteCompare(Backlight_PWM_PWM_COMPARE_VALUE);

        #if (1u == Backlight_PWM_PWM_COMPARE_SWAP)
            Backlight_PWM_SetCompareSwap(1u);
            Backlight_PWM_WriteCompareBuf(Backlight_PWM_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Backlight_PWM_PWM_COMPARE_SWAP) */

        #if (1u == Backlight_PWM_PWM_PERIOD_SWAP)
            Backlight_PWM_SetPeriodSwap(1u);
            Backlight_PWM_WritePeriodBuf(Backlight_PWM_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Backlight_PWM_PWM_PERIOD_SWAP) */

        /* Set values from customizer to CTRL2 */
        #if (Backlight_PWM__PWM_PR == Backlight_PWM_PWM_MODE)
            Backlight_PWM_TRIG_CONTROL2_REG =
                    (Backlight_PWM_CC_MATCH_NO_CHANGE    |
                    Backlight_PWM_OVERLOW_NO_CHANGE      |
                    Backlight_PWM_UNDERFLOW_NO_CHANGE);
        #else
            #if (Backlight_PWM__LEFT == Backlight_PWM_PWM_ALIGN)
                Backlight_PWM_TRIG_CONTROL2_REG = Backlight_PWM_PWM_MODE_LEFT;
            #endif  /* ( Backlight_PWM_PWM_LEFT == Backlight_PWM_PWM_ALIGN) */

            #if (Backlight_PWM__RIGHT == Backlight_PWM_PWM_ALIGN)
                Backlight_PWM_TRIG_CONTROL2_REG = Backlight_PWM_PWM_MODE_RIGHT;
            #endif  /* ( Backlight_PWM_PWM_RIGHT == Backlight_PWM_PWM_ALIGN) */

            #if (Backlight_PWM__CENTER == Backlight_PWM_PWM_ALIGN)
                Backlight_PWM_TRIG_CONTROL2_REG = Backlight_PWM_PWM_MODE_CENTER;
            #endif  /* ( Backlight_PWM_PWM_CENTER == Backlight_PWM_PWM_ALIGN) */

            #if (Backlight_PWM__ASYMMETRIC == Backlight_PWM_PWM_ALIGN)
                Backlight_PWM_TRIG_CONTROL2_REG = Backlight_PWM_PWM_MODE_ASYM;
            #endif  /* (Backlight_PWM__ASYMMETRIC == Backlight_PWM_PWM_ALIGN) */
        #endif  /* (Backlight_PWM__PWM_PR == Backlight_PWM_PWM_MODE) */
    #endif  /* (Backlight_PWM__PWM_SEL == Backlight_PWM_CONFIG) */
}


/*******************************************************************************
* Function Name: Backlight_PWM_Enable
********************************************************************************
*
* Summary:
*  Enables the Backlight_PWM.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Backlight_PWM_BLOCK_CONTROL_REG |= Backlight_PWM_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Statr Timer or PWM if start input is absent */
    #if (Backlight_PWM__PWM_SEL == Backlight_PWM_CONFIG)
        #if (0u == Backlight_PWM_PWM_START_SIGNAL_PRESENT)
            Backlight_PWM_TriggerCommand(Backlight_PWM_MASK, Backlight_PWM_CMD_START);
        #endif /* (0u == Backlight_PWM_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Backlight_PWM__PWM_SEL == Backlight_PWM_CONFIG) */

    #if (Backlight_PWM__TIMER == Backlight_PWM_CONFIG)
        #if (0u == Backlight_PWM_TC_START_SIGNAL_PRESENT)
            Backlight_PWM_TriggerCommand(Backlight_PWM_MASK, Backlight_PWM_CMD_START);
        #endif /* (0u == Backlight_PWM_TC_START_SIGNAL_PRESENT) */
    #endif /* (Backlight_PWM__TIMER == Backlight_PWM_CONFIG) */
}


/*******************************************************************************
* Function Name: Backlight_PWM_Start
********************************************************************************
*
* Summary:
*  Initialize the Backlight_PWM with default customizer
*  values when called the first time and enables the Backlight_PWM.
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
*  Backlight_PWM_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Backlight_PWM_Start() is called. This allows
*  enable/disable component without re-initialization in all subsequent calls
*  to the Backlight_PWM_Start() routine.
*
*******************************************************************************/
void Backlight_PWM_Start(void)
{
    if (0u == Backlight_PWM_initVar)
    {
        Backlight_PWM_Init();
        Backlight_PWM_initVar = 1u;
    }

    Backlight_PWM_Enable();
}


/*******************************************************************************
* Function Name: Backlight_PWM_Stop
********************************************************************************
*
* Summary:
*  Disables the Backlight_PWM.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_BLOCK_CONTROL_REG &= (uint32)~Backlight_PWM_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Backlight_PWM. This function is used when
*  configured as a generic Backlight_PWM and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Backlight_PWM to operate in
*   Values:
*   - Backlight_PWM_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Backlight_PWM_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Backlight_PWM_MODE_QUAD - Quadrature decoder
*         - Backlight_PWM_MODE_PWM - PWM
*         - Backlight_PWM_MODE_PWM_DT - PWM with dead time
*         - Backlight_PWM_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_CONTROL_REG &= (uint32)~Backlight_PWM_MODE_MASK;
    Backlight_PWM_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of 3 supported modes.
*  Is functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Backlight_PWM_MODE_X1 - Counts on phi 1 rising
*         - Backlight_PWM_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Backlight_PWM_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_CONTROL_REG &= (uint32)~Backlight_PWM_QUAD_MODE_MASK;
    Backlight_PWM_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to PWM with dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Backlight_PWM_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Backlight_PWM_PRESCALE_DIVBY2    - Divide by 2
*         - Backlight_PWM_PRESCALE_DIVBY4    - Divide by 4
*         - Backlight_PWM_PRESCALE_DIVBY8    - Divide by 8
*         - Backlight_PWM_PRESCALE_DIVBY16   - Divide by 16
*         - Backlight_PWM_PRESCALE_DIVBY32   - Divide by 32
*         - Backlight_PWM_PRESCALE_DIVBY64   - Divide by 64
*         - Backlight_PWM_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_CONTROL_REG &= (uint32)~Backlight_PWM_PRESCALER_MASK;
    Backlight_PWM_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Backlight_PWM runs
*  continuously or stops when terminal count is reached.  By default the
*  Backlight_PWM operates in continuous mode.
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
void Backlight_PWM_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_CONTROL_REG &= (uint32)~Backlight_PWM_ONESHOT_MASK;
    Backlight_PWM_CONTROL_REG |= ((uint32)((oneShotEnable & Backlight_PWM_1BIT_MASK) <<
                                                               Backlight_PWM_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetPWMMode
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
void Backlight_PWM_SetPWMMode(uint32 modeMask)
{
    Backlight_PWM_TRIG_CONTROL2_REG = (modeMask & Backlight_PWM_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Backlight_PWM_SetPWMSyncKill
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
void Backlight_PWM_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_CONTROL_REG &= (uint32)~Backlight_PWM_PWM_SYNC_KILL_MASK;
    Backlight_PWM_CONTROL_REG |= ((uint32)((syncKillEnable & Backlight_PWM_1BIT_MASK)  <<
                                               Backlight_PWM_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetPWMStopOnKill
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
void Backlight_PWM_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_CONTROL_REG &= (uint32)~Backlight_PWM_PWM_STOP_KILL_MASK;
    Backlight_PWM_CONTROL_REG |= ((uint32)((stopOnKillEnable & Backlight_PWM_1BIT_MASK)  <<
                                                         Backlight_PWM_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetPWMDeadTime
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
void Backlight_PWM_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_CONTROL_REG &= (uint32)~Backlight_PWM_PRESCALER_MASK;
    Backlight_PWM_CONTROL_REG |= ((uint32)((deadTime & Backlight_PWM_8BIT_MASK) <<
                                                          Backlight_PWM_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetPWMInvert
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
*         - Backlight_PWM_INVERT_LINE   - Inverts the line output
*         - Backlight_PWM_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_CONTROL_REG &= (uint32)~Backlight_PWM_INV_OUT_MASK;
    Backlight_PWM_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Backlight_PWM_WriteCounter
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
void Backlight_PWM_WriteCounter(uint32 count)
{
    Backlight_PWM_COUNTER_REG = (count & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_ReadCounter
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
uint32 Backlight_PWM_ReadCounter(void)
{
    return (Backlight_PWM_COUNTER_REG & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and PWM with pseudo random output.
*
* Parameters:
*  counterMode: Enumerated couner type values
*   Values:
*     - Backlight_PWM_COUNT_UP       - Counts up
*     - Backlight_PWM_COUNT_DOWN     - Counts down
*     - Backlight_PWM_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Backlight_PWM_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_CONTROL_REG &= (uint32)~Backlight_PWM_UPDOWN_MASK;
    Backlight_PWM_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_WritePeriod
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
void Backlight_PWM_WritePeriod(uint32 period)
{
    Backlight_PWM_PERIOD_REG = (period & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_ReadPeriod
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
uint32 Backlight_PWM_ReadPeriod(void)
{
    return (Backlight_PWM_PERIOD_REG & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetCompareSwap
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
void Backlight_PWM_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_CONTROL_REG &= (uint32)~Backlight_PWM_RELOAD_CC_MASK;
    Backlight_PWM_CONTROL_REG |= (swapEnable & Backlight_PWM_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_WritePeriodBuf
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
void Backlight_PWM_WritePeriodBuf(uint32 periodBuf)
{
    Backlight_PWM_PERIOD_BUF_REG = (periodBuf & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_ReadPeriodBuf
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
uint32 Backlight_PWM_ReadPeriodBuf(void)
{
    return (Backlight_PWM_PERIOD_BUF_REG & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetPeriodSwap
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
void Backlight_PWM_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_CONTROL_REG &= (uint32)~Backlight_PWM_RELOAD_PERIOD_MASK;
    Backlight_PWM_CONTROL_REG |= ((uint32)((swapEnable & Backlight_PWM_1BIT_MASK) <<
                                                            Backlight_PWM_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_WriteCompare
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
void Backlight_PWM_WriteCompare(uint32 compare)
{
    Backlight_PWM_COMP_CAP_REG = (compare & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_ReadCompare
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
uint32 Backlight_PWM_ReadCompare(void)
{
    return (Backlight_PWM_COMP_CAP_REG & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_WriteCompareBuf
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
void Backlight_PWM_WriteCompareBuf(uint32 compareBuf)
{
   Backlight_PWM_COMP_CAP_BUF_REG = (compareBuf & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_ReadCompareBuf
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
uint32 Backlight_PWM_ReadCompareBuf(void)
{
    return (Backlight_PWM_COMP_CAP_BUF_REG & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_ReadCapture
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
uint32 Backlight_PWM_ReadCapture(void)
{
    return (Backlight_PWM_COMP_CAP_REG & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_ReadCaptureBuf
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
uint32 Backlight_PWM_ReadCaptureBuf(void)
{
    return (Backlight_PWM_COMP_CAP_BUF_REG & Backlight_PWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetCaptureMode
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
*     - Backlight_PWM_TRIG_LEVEL     - Level
*     - Backlight_PWM_TRIG_RISING    - Rising edge
*     - Backlight_PWM_TRIG_FALLING   - Falling edge
*     - Backlight_PWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_TRIG_CONTROL1_REG &= (uint32)~Backlight_PWM_CAPTURE_MASK;
    Backlight_PWM_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Backlight_PWM_TRIG_LEVEL     - Level
*     - Backlight_PWM_TRIG_RISING    - Rising edge
*     - Backlight_PWM_TRIG_FALLING   - Falling edge
*     - Backlight_PWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_TRIG_CONTROL1_REG &= (uint32)~Backlight_PWM_RELOAD_MASK;
    Backlight_PWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Backlight_PWM_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Backlight_PWM_TRIG_LEVEL     - Level
*     - Backlight_PWM_TRIG_RISING    - Rising edge
*     - Backlight_PWM_TRIG_FALLING   - Falling edge
*     - Backlight_PWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_TRIG_CONTROL1_REG &= (uint32)~Backlight_PWM_START_MASK;
    Backlight_PWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Backlight_PWM_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Backlight_PWM_TRIG_LEVEL     - Level
*     - Backlight_PWM_TRIG_RISING    - Rising edge
*     - Backlight_PWM_TRIG_FALLING   - Falling edge
*     - Backlight_PWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_TRIG_CONTROL1_REG &= (uint32)~Backlight_PWM_STOP_MASK;
    Backlight_PWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Backlight_PWM_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Backlight_PWM_TRIG_LEVEL     - Level
*     - Backlight_PWM_TRIG_RISING    - Rising edge
*     - Backlight_PWM_TRIG_FALLING   - Falling edge
*     - Backlight_PWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_TRIG_CONTROL1_REG &= (uint32)~Backlight_PWM_COUNT_MASK;
    Backlight_PWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Backlight_PWM_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_TriggerCommand
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
*     - Backlight_PWM_CMD_CAPTURE    - Trigger Capture command
*     - Backlight_PWM_CMD_RELOAD     - Trigger Reload command
*     - Backlight_PWM_CMD_STOP       - Trigger Stop command
*     - Backlight_PWM_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Backlight_PWM_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Backlight_PWM_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Backlight_PWM.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Backlight_PWM_STATUS_DOWN    - Set if counting down
*     - Backlight_PWM_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Backlight_PWM_ReadStatus(void)
{
    return ((Backlight_PWM_STATUS_REG >> Backlight_PWM_RUNNING_STATUS_SHIFT) |
            (Backlight_PWM_STATUS_REG & Backlight_PWM_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Backlight_PWM_INTR_MASK_TC       - Terminal count mask
*     - Backlight_PWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetInterruptMode(uint32 interruptMask)
{
    Backlight_PWM_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Backlight_PWM_GetInterruptSourceMasked
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
*     - Backlight_PWM_INTR_MASK_TC       - Terminal count mask
*     - Backlight_PWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Backlight_PWM_GetInterruptSourceMasked(void)
{
    return (Backlight_PWM_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Backlight_PWM_GetInterruptSource
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
*     - Backlight_PWM_INTR_MASK_TC       - Terminal count mask
*     - Backlight_PWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Backlight_PWM_GetInterruptSource(void)
{
    return (Backlight_PWM_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Backlight_PWM_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Backlight_PWM_INTR_MASK_TC       - Terminal count mask
*     - Backlight_PWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_ClearInterrupt(uint32 interruptMask)
{
    Backlight_PWM_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Backlight_PWM_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Backlight_PWM_INTR_MASK_TC       - Terminal count mask
*     - Backlight_PWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Backlight_PWM_SetInterrupt(uint32 interruptMask)
{
    Backlight_PWM_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
