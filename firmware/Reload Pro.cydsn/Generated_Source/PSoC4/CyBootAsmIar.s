;-------------------------------------------------------------------------------
; FILENAME: CyBootAsmIar.s
; Version 4.10
;
;  DESCRIPTION:
;    Assembly routines for IAR Embedded Workbench IDE.
;
;-------------------------------------------------------------------------------
; Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions,
; disclaimers, and limitations in the end user license agreement accompanying
; the software package with which this file was provided.
;-------------------------------------------------------------------------------

    SECTION .text:CODE:ROOT(4)
    PUBLIC CyDelayCycles
    PUBLIC CyEnterCriticalSection
    PUBLIC CyExitCriticalSection
    THUMB


;-------------------------------------------------------------------------------
; Function Name: CyDelayCycles
;-------------------------------------------------------------------------------
;
; Summary:
;  Delays for the specified number of cycles.
;
; Parameters:
;  uint32 cycles: number of cycles to delay.
;
; Return:
;  None
;
;-------------------------------------------------------------------------------
; void CyDelayCycles(uint32 cycles)

CyDelayCycles: 
    ADDS r0, r0, #2
    LSRS r0, r0, #2
    BEQ CyDelayCycles_done
    NOP
CyDelayCycles_loop:
    SUBS r0, r0, #1
    BNE CyDelayCycles_loop
    NOP
    NOP
CyDelayCycles_done:
    BX lr

;-------------------------------------------------------------------------------
; Function Name: CyEnterCriticalSection
;-------------------------------------------------------------------------------
;
; Summary:
;  CyEnterCriticalSection disables interrupts and returns a value indicating
;  whether interrupts were previously enabled.
;
;  Note Implementation of CyEnterCriticalSection manipulates the IRQ enable bit
;  with interrupts still enabled. The test and set of the interrupt bits is not
;  atomic. Therefore, to avoid corrupting processor state, it must be the policy 
;  that all interrupt routines restore the interrupt enable bits as they were 
;  found on entry.
;
; Parameters:
;  None
;
; Return:
;  uint8
;   Returns 0 if interrupts were previously enabled or 1 if interrupts
;   were previously disabled.
;
;-------------------------------------------------------------------------------
; uint8 CyEnterCriticalSection(void)

CyEnterCriticalSection:
    MRS r0, PRIMASK         ; Save and return interrupt state
    CPSID I                 ; Disable interrupts
    BX lr

;-------------------------------------------------------------------------------
; Function Name: CyExitCriticalSection
;-------------------------------------------------------------------------------
;
; Summary:
;  CyExitCriticalSection re-enables interrupts if they were enabled before
;  CyEnterCriticalSection was called. The argument should be the value returned
;  from CyEnterCriticalSection.
;
; Parameters:
;  uint8 savedIntrStatus:
;   Saved interrupt status returned by the CyEnterCriticalSection function.
;
; Return:
;  None
;
;-------------------------------------------------------------------------------
; void CyExitCriticalSection(uint8 savedIntrStatus)

CyExitCriticalSection:
    MSR PRIMASK, r0         ; Restore interrupt state
    BX lr

    END

