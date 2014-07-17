/*******************************************************************************
* File Name: QuadratureISR.h
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
#if !defined(CY_ISR_QuadratureISR_H)
#define CY_ISR_QuadratureISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void QuadratureISR_Start(void);
void QuadratureISR_StartEx(cyisraddress address);
void QuadratureISR_Stop(void);

CY_ISR_PROTO(QuadratureISR_Interrupt);

void QuadratureISR_SetVector(cyisraddress address);
cyisraddress QuadratureISR_GetVector(void);

void QuadratureISR_SetPriority(uint8 priority);
uint8 QuadratureISR_GetPriority(void);

void QuadratureISR_Enable(void);
uint8 QuadratureISR_GetState(void);
void QuadratureISR_Disable(void);

void QuadratureISR_SetPending(void);
void QuadratureISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the QuadratureISR ISR. */
#define QuadratureISR_INTC_VECTOR            ((reg32 *) QuadratureISR__INTC_VECT)

/* Address of the QuadratureISR ISR priority. */
#define QuadratureISR_INTC_PRIOR             ((reg32 *) QuadratureISR__INTC_PRIOR_REG)

/* Priority of the QuadratureISR interrupt. */
#define QuadratureISR_INTC_PRIOR_NUMBER      QuadratureISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable QuadratureISR interrupt. */
#define QuadratureISR_INTC_SET_EN            ((reg32 *) QuadratureISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the QuadratureISR interrupt. */
#define QuadratureISR_INTC_CLR_EN            ((reg32 *) QuadratureISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the QuadratureISR interrupt state to pending. */
#define QuadratureISR_INTC_SET_PD            ((reg32 *) QuadratureISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the QuadratureISR interrupt. */
#define QuadratureISR_INTC_CLR_PD            ((reg32 *) QuadratureISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_QuadratureISR_H */


/* [] END OF FILE */
