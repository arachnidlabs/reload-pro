/*******************************************************************************
* File Name: QuadButtonISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_QuadButtonISR_H)
#define CY_ISR_QuadButtonISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void QuadButtonISR_Start(void);
void QuadButtonISR_StartEx(cyisraddress address);
void QuadButtonISR_Stop(void);

CY_ISR_PROTO(QuadButtonISR_Interrupt);

void QuadButtonISR_SetVector(cyisraddress address);
cyisraddress QuadButtonISR_GetVector(void);

void QuadButtonISR_SetPriority(uint8 priority);
uint8 QuadButtonISR_GetPriority(void);

void QuadButtonISR_Enable(void);
uint8 QuadButtonISR_GetState(void);
void QuadButtonISR_Disable(void);

void QuadButtonISR_SetPending(void);
void QuadButtonISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the QuadButtonISR ISR. */
#define QuadButtonISR_INTC_VECTOR            ((reg32 *) QuadButtonISR__INTC_VECT)

/* Address of the QuadButtonISR ISR priority. */
#define QuadButtonISR_INTC_PRIOR             ((reg32 *) QuadButtonISR__INTC_PRIOR_REG)

/* Priority of the QuadButtonISR interrupt. */
#define QuadButtonISR_INTC_PRIOR_NUMBER      QuadButtonISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable QuadButtonISR interrupt. */
#define QuadButtonISR_INTC_SET_EN            ((reg32 *) QuadButtonISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the QuadButtonISR interrupt. */
#define QuadButtonISR_INTC_CLR_EN            ((reg32 *) QuadButtonISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the QuadButtonISR interrupt state to pending. */
#define QuadButtonISR_INTC_SET_PD            ((reg32 *) QuadButtonISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the QuadButtonISR interrupt. */
#define QuadButtonISR_INTC_CLR_PD            ((reg32 *) QuadButtonISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_QuadButtonISR_H */


/* [] END OF FILE */
