/*******************************************************************************
* File Name: cyPm.c
* Version 4.0
*
*  Description:
*   Provides an API for the power management.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2011-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cyPm.h"
#include "CyLib.h"


/*******************************************************************************
* Function Name: CySysPmSleep
********************************************************************************
*
* Summary:
*  Puts the part into the Sleep state. This is a CPU-centric power mode.
*  It means that the CPU has indicated that it is in sleep mode and
*  its main clock can be removed. It is identical to Active from a peripheral
*  point of view. Any enabled interrupts can cause wakeup from a Sleep mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysPmSleep(void)
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();

    /* CM0 enters Sleep mode upon execution of WFI */
    CY_PM_CM0_SCR_REG &= (uint32) (~CY_PM_CM0_SCR_SLEEPDEEP);

    /* Sleep and wait for interrupt */
    CY_PM_WFI;

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: CySysPmDeepSleep
********************************************************************************
*
* Summary:
*  Puts the part into the Deep Sleep state. If firmware attempts to enter this
*  mode before the system is ready (that is, when PWR_CONTROL.LPM_READY = 0),
*  then the device will go into Sleep mode instead and automatically enter
*  the originally intended mode when the holdoff expires.
*
*  The wakeup occurs when an interrupt is received from a DeepSleep or
*  Hibernate peripheral. For more details, see corresponding
*  peripheral's datasheet.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysPmDeepSleep(void)
{
    uint8 interruptState;
    #if(CY_PSOC4A)
        volatile uint32 clkSelectReg;
    #endif /* (CY_PSOC4A) */

    interruptState = CyEnterCriticalSection();

    #if(CY_PSOC4A)
        /* Device enters DeepSleep mode when CPU asserts SLEEPDEEP signal */
        CY_PM_PWR_CONTROL_REG &= (uint32) (~CY_PM_PWR_CONTROL_HIBERNATE);
    #endif /* (CY_PSOC4A) */

    /* Adjust delay to wait for references to settle on wakeup from deepsleep */
    CY_PM_PWR_KEY_DELAY_REG = CY_SFLASH_DPSLP_KEY_DELAY_REG;

    /* CM0 enters DeepSleep/Hibernate mode upon execution of WFI */
    CY_PM_CM0_SCR_REG |= CY_PM_CM0_SCR_SLEEPDEEP;
    
    #if(CY_PSOC4A)
        /* Preserve system clock configuration and 
        * reduce sysclk to <=24 MHz (Cypress ID #158710).
        */
        clkSelectReg = CY_SYS_CLK_SELECT_REG;
        CySysClkWriteSysclkDiv(CY_SYS_CLK_SYSCLK_DIV2);
    #endif /* (CY_PSOC4A) */

    /* Sleep and wait for interrupt */
    CY_PM_WFI;

    #if(CY_PSOC4A)
        /* Restore system clock configuration */
        CY_SYS_CLK_SELECT_REG = clkSelectReg;
    #endif /* (CY_PSOC4A) */

    CyExitCriticalSection(interruptState);
}


#if(CY_PSOC4A)

    /*******************************************************************************
    * Function Name: CySysPmHibernate
    ********************************************************************************
    *
    * Summary:
    *  Puts the part into the Hibernate state. Only SRAM and UDBs are retained;
    *  most internal supplies are off. Wakeup is possible from a pin or a hibernate
    *  comparator only.
    *
    *  It is expected that the firmware has already frozen the IO-Cells using
    *  CySysPmFreezeIo() function before the call to this function. If this is
    *  omitted the IO-cells will be frozen in the same way as they are
    *  in the Active to Deep Sleep transition, but will lose their state on wake up
    *  (because of the reset occurring at that time).
    *
    *  Because all CPU state is lost, the CPU will start up at the reset vector.
    *  To save firmware state through Hibernate low power mode, corresponding
    *  variable should be defined with CY_NOINIT attribute. It prevents data
    *  from being initialized to zero on startup. The interrupt cause of
    *  the hibernate peripheral is retained, such that it can be either read by
    *  the firmware or cause an interrupt after the firmware has booted and
    *  enabled the corresponding interrupt. To distinguish the wakeup from
    *  the Hibernate mode and the general Reset event, the CySysPmGetResetReason()
    *  function could be used.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysPmHibernate(void)
    {
        uint8 interruptState;

        interruptState = CyEnterCriticalSection();

        /* Device enters Hibernate mode when CPU asserts SLEEPDEEP signal */
        CY_PM_PWR_CONTROL_REG |= CY_PM_PWR_CONTROL_HIBERNATE;

        /* Adjust delay to wait for references to settle on wakeup from hibernate */
        CY_PM_PWR_KEY_DELAY_REG = CY_SFLASH_HIB_KEY_DELAY_REG;

        /* CM0 enters DeepSleep/Hibernate mode upon execution of WFI */
        CY_PM_CM0_SCR_REG |= CY_PM_CM0_SCR_SLEEPDEEP;

        /* Save token that will retain through a STOP/WAKEUP sequence
         * thus could be used by CySysPmGetResetReason() to differentiate
         * WAKEUP from a general RESET event.
         */
        CY_PM_PWR_STOP_REG = (CY_PM_PWR_STOP_REG & (uint32)(~CY_PM_PWR_STOP_TOKEN_MASK)) | CY_PM_PWR_STOP_TOKEN_HIB;

        /* Sleep and wait for interrupt. Wakeup from Hibernate is performed 
         * through RESET state, causing a normal Boot procedure to occur.
         * The WFI instruction doesn't put the core to sleep if its wake condition 
         * is true when the instruction is executed.
         */
        CY_PM_WFI;

        CyExitCriticalSection(interruptState);
    }


    /*******************************************************************************
    * Function Name: CySysPmStop
    ********************************************************************************
    *
    * Summary:
    *  Puts the part into the Stop state. All internal supplies are off;
    *  no state is retained.
    *
    *  Wakeup from Stop is performed by toggling the wakeup pin (P0.7), causing
    *  a normal Boot procedure to occur. To configure the wakeup pin,
    *  the Digital Input Pin component should be placed on the schematic,
    *  assigned to the P0.7, and resistively pulled up or down to the inverse state
    *  of the wakeup polarity. To distinguish the wakeup from the Stop mode and
    *  the general Reset event, CySysPmGetResetReason() function could be used.
    *  The wakeup pin is active low by default. The wakeup pin polarity
    *  could be changed with the CySysPmSetWakeupPolarity() function.
    *
    *  This function freezes IO cells implicitly. It is not possible to enter
    *  STOP mode before freezing the IO cells. The IO cells remain frozen after
    *  awake from the Stop mode until the firmware unfreezes them after booting
    *  explicitly with CySysPmUnfreezeIo() function call.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysPmStop(void)
    {
        (void)CyEnterCriticalSection();

        /* Freeze IO-Cells to save IO-Cell state */
        CySysPmFreezeIo();

        /* Initiates transition to the Stop state */
        CY_PM_PWR_STOP_REG = (CY_PM_PWR_STOP_REG & (uint32)(~CY_PM_PWR_STOP_TOKEN_MASK)) |
                            CY_PM_PWR_STOP_TOKEN_STOP | CY_PM_PWR_STOP_STOP;

        /* Depending on the clock frequency and internal timing delays,
         * the final AHB transaction may or may not complete. To guard against
         * accidentally executing an unintended instruction, it is recommended
         * to add 2 NOP cycles after the final write to the STOP register.
         */
        CY_NOP;
        CY_NOP;
        
        /* Should never get to this WFI instruction */
        CY_PM_WFI;

        /* Wakeup from Stop is performed by toggling of Wakeup pin,
         * causing a normal Boot procedure to occur. No need to exit
         * from the critical section.
         */
    }


    /*******************************************************************************
    * Function Name: CySysPmSetWakeupPolarity
    ********************************************************************************
    *
    * Summary:
    *  Wake up from stop mode is performed by toggling the wakeup pin (P0.7),
    *  causing a normal boot procedure to occur. This function assigns
    *  the wakeup pin active level. Setting the wakeup pin to this level will cause
    *  the wakeup from stop mode. The wakeup pin is active low by default.
    *
    * Parameters:
    *  polarity: Wakeup pin active level:
    *   Value    Define                          Level
    *    0        CY_PM_STOP_WAKEUP_ACTIVE_LOW    Logical zero will wakeup the chip
    *    1        CY_PM_STOP_WAKEUP_ACTIVE_HIGH   Logical one will wakeup the chip
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysPmSetWakeupPolarity(uint32 polarity)
    {
        uint8 interruptState;

        interruptState = CyEnterCriticalSection();

        CY_PM_PWR_STOP_REG = (CY_PM_STOP_WAKEUP_ACTIVE_LOW != polarity) ?
                            (CY_PM_PWR_STOP_REG | CY_PM_PWR_STOP_POLARITY) :
                            (CY_PM_PWR_STOP_REG & (uint32) (~CY_PM_PWR_STOP_POLARITY));

        CyExitCriticalSection(interruptState);
    }


    /*******************************************************************************
    * Function Name: CySysPmGetResetReason
    ********************************************************************************
    *
    * Summary:
    *  Retrieves last reset reason - transition from OFF/XRES/STOP/HIBERNATE to
    *  RESET state. Note that waking up from STOP using XRES will be perceived as
    *  general RESET.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Reset reason.
    *  CY_PM_RESET_REASON_UNKN        - unknown
    *  CY_PM_RESET_REASON_XRES        - transition from OFF/XRES to RESET
    *  CY_PM_RESET_REASON_WAKEUP_HIB  - transition/wakeup from HIBERNATE to RESET
    *  CY_PM_RESET_REASON_WAKEUP_STOP - transition/wakeup from STOP to RESET
    *
    *******************************************************************************/
    uint32 CySysPmGetResetReason(void)
    {
        uint32 reason = CY_PM_RESET_REASON_UNKN;

        switch(CY_PM_PWR_STOP_REG & CY_PM_PWR_STOP_TOKEN_MASK)
        {
        /* Power up, XRES */
        case CY_PM_PWR_STOP_TOKEN_XRES:
            reason = CY_PM_RESET_REASON_XRES;
            break;

        /* Wakeup from Hibernate */
        case CY_PM_PWR_STOP_TOKEN_HIB:
            reason = CY_PM_RESET_REASON_WAKEUP_HIB;
            break;

        /* Wakeup from Stop (through WAKEUP pin assert) */
        case CY_PM_PWR_STOP_TOKEN_STOP:
            reason = CY_PM_RESET_REASON_WAKEUP_STOP;
            break;

        /* Unknown reason */
        default:
            break;
        }

        return (reason);
    }


    /*******************************************************************************
    * Function Name: CySysPmFreezeIo
    ********************************************************************************
    *
    * Summary:
    *  Freezes IO-Cells directly to save IO-Cell state on wake up from Hibernate or
    *  Stop state. It is not required to call this function before entering
    *  Stop mode, since CySysPmStop() function freezes IO-Cells implicitly.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysPmFreezeIo(void)
    {
        uint8 interruptState;

        interruptState = CyEnterCriticalSection();

        /* Check FREEZE state to avoid recurrent IO-Cells freeze attempt,
         * since the second call to this function will cause accidental switch
         * to the STOP mode (the system will enter STOP mode immediately after
         * writing to STOP bit since both UNLOCK and FREEZE have been set correctly
         * in a previous call to this function).
         */
        if (0u == (CY_PM_PWR_STOP_REG & CY_PM_PWR_STOP_FREEZE))
        {
            /* Preserve last reset reason and disable overrides the next freeze command by peripherals */
            CY_PM_PWR_STOP_REG = CY_PM_PWR_STOP_STOP | CY_PM_PWR_STOP_FREEZE | CY_PM_PWR_STOP_UNLOCK |
                                (CY_PM_PWR_STOP_REG & (CY_PM_PWR_STOP_TOKEN_MASK | CY_PM_PWR_STOP_POLARITY));

            /* PWR_STOP read after write must be delayed for 6 clock cycles to let internal nodes to settle */
            CyDelayCycles(6u);

            /* The second write causes the freeze of IO-Cells to save IO-Cell state */
            CY_PM_PWR_STOP_REG &= ~CY_PM_PWR_STOP_STOP;
        }

        CyExitCriticalSection(interruptState);
    }


    /*******************************************************************************
    * Function Name: CySysPmUnfreezeIo
    ********************************************************************************
    *
    * Summary:
    *  The IO-Cells remain frozen after awake from Hibernate or Stop mode until
    *  the firmware unfreezes them after booting. The call of this function
    *  unfreezes IO-Cells explicitly.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysPmUnfreezeIo(void)
    {
        uint8 interruptState;

        interruptState = CyEnterCriticalSection();

        /* Preserve last reset reason and wakeup polarity. Then, unfreeze I/O:
         * write PWR_STOP.FREEZE=0, .UNLOCK=0x3A, .STOP=0, .TOKEN
         */
        CY_PM_PWR_STOP_REG = CY_PM_PWR_STOP_UNLOCK |
                            (CY_PM_PWR_STOP_REG & (CY_PM_PWR_STOP_TOKEN_MASK | CY_PM_PWR_STOP_POLARITY));

        /* PWR_STOP read after write must be delayed for 6 clock cycles to let internal nodes to settle */
        CyDelayCycles(6u);

        /* Lock STOP mode: write PWR_STOP.FREEZE=0, UNLOCK=0x00, STOP=0, .TOKEN */
        CY_PM_PWR_STOP_REG &= (CY_PM_PWR_STOP_TOKEN_MASK | CY_PM_PWR_STOP_POLARITY);

        CyExitCriticalSection(interruptState);
    }

#endif /* (CY_PSOC4A) */


/* [] END OF FILE */
