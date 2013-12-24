/*******************************************************************************
* File Name: QuadratureISR.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <QuadratureISR.h>

#if !defined(QuadratureISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START QuadratureISR_intc` */

/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: QuadratureISR_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void QuadratureISR_Start(void)
{
    /* For all we know the interrupt is active. */
    QuadratureISR_Disable();

    /* Set the ISR to point to the QuadratureISR Interrupt. */
    QuadratureISR_SetVector(&QuadratureISR_Interrupt);

    /* Set the priority. */
    QuadratureISR_SetPriority((uint8)QuadratureISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    QuadratureISR_Enable();
}


/*******************************************************************************
* Function Name: QuadratureISR_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void QuadratureISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    QuadratureISR_Disable();

    /* Set the ISR to point to the QuadratureISR Interrupt. */
    QuadratureISR_SetVector(address);

    /* Set the priority. */
    QuadratureISR_SetPriority((uint8)QuadratureISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    QuadratureISR_Enable();
}


/*******************************************************************************
* Function Name: QuadratureISR_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void QuadratureISR_Stop(void)
{
    /* Disable this interrupt. */
    QuadratureISR_Disable();

    /* Set the ISR to point to the passive one. */
    QuadratureISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: QuadratureISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for QuadratureISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(QuadratureISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START QuadratureISR_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: QuadratureISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling QuadratureISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use QuadratureISR_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void QuadratureISR_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + QuadratureISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: QuadratureISR_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress QuadratureISR_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + QuadratureISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: QuadratureISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling QuadratureISR_Start
*   or QuadratureISR_StartEx will override any effect this method would 
*   have had. This method should only be called after QuadratureISR_Start or 
*   QuadratureISR_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void QuadratureISR_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((QuadratureISR__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *QuadratureISR_INTC_PRIOR = (*QuadratureISR_INTC_PRIOR & (uint32)(~QuadratureISR__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: QuadratureISR_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 3, 0 being the highest.
*
*******************************************************************************/
uint8 QuadratureISR_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((QuadratureISR__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*QuadratureISR_INTC_PRIOR & QuadratureISR__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: QuadratureISR_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void QuadratureISR_Enable(void)
{
    /* Enable the general interrupt. */
    *QuadratureISR_INTC_SET_EN = QuadratureISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: QuadratureISR_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 QuadratureISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*QuadratureISR_INTC_SET_EN & (uint32)QuadratureISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: QuadratureISR_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void QuadratureISR_Disable(void)
{
    /* Disable the general interrupt. */
    *QuadratureISR_INTC_CLR_EN = QuadratureISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: QuadratureISR_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void QuadratureISR_SetPending(void)
{
    *QuadratureISR_INTC_SET_PD = QuadratureISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: QuadratureISR_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void QuadratureISR_ClearPending(void)
{
    *QuadratureISR_INTC_CLR_PD = QuadratureISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
