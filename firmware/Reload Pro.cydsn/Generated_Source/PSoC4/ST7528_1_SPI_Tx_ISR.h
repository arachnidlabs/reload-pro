/*******************************************************************************
* File Name: ST7528_1_SPI_Tx_ISR.h
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
#if !defined(CY_ISR_ST7528_1_SPI_Tx_ISR_H)
#define CY_ISR_ST7528_1_SPI_Tx_ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ST7528_1_SPI_Tx_ISR_Start(void);
void ST7528_1_SPI_Tx_ISR_StartEx(cyisraddress address);
void ST7528_1_SPI_Tx_ISR_Stop(void);

CY_ISR_PROTO(ST7528_1_SPI_Tx_ISR_Interrupt);

void ST7528_1_SPI_Tx_ISR_SetVector(cyisraddress address);
cyisraddress ST7528_1_SPI_Tx_ISR_GetVector(void);

void ST7528_1_SPI_Tx_ISR_SetPriority(uint8 priority);
uint8 ST7528_1_SPI_Tx_ISR_GetPriority(void);

void ST7528_1_SPI_Tx_ISR_Enable(void);
uint8 ST7528_1_SPI_Tx_ISR_GetState(void);
void ST7528_1_SPI_Tx_ISR_Disable(void);

void ST7528_1_SPI_Tx_ISR_SetPending(void);
void ST7528_1_SPI_Tx_ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ST7528_1_SPI_Tx_ISR ISR. */
#define ST7528_1_SPI_Tx_ISR_INTC_VECTOR            ((reg32 *) ST7528_1_SPI_Tx_ISR__INTC_VECT)

/* Address of the ST7528_1_SPI_Tx_ISR ISR priority. */
#define ST7528_1_SPI_Tx_ISR_INTC_PRIOR             ((reg32 *) ST7528_1_SPI_Tx_ISR__INTC_PRIOR_REG)

/* Priority of the ST7528_1_SPI_Tx_ISR interrupt. */
#define ST7528_1_SPI_Tx_ISR_INTC_PRIOR_NUMBER      ST7528_1_SPI_Tx_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ST7528_1_SPI_Tx_ISR interrupt. */
#define ST7528_1_SPI_Tx_ISR_INTC_SET_EN            ((reg32 *) ST7528_1_SPI_Tx_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ST7528_1_SPI_Tx_ISR interrupt. */
#define ST7528_1_SPI_Tx_ISR_INTC_CLR_EN            ((reg32 *) ST7528_1_SPI_Tx_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ST7528_1_SPI_Tx_ISR interrupt state to pending. */
#define ST7528_1_SPI_Tx_ISR_INTC_SET_PD            ((reg32 *) ST7528_1_SPI_Tx_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ST7528_1_SPI_Tx_ISR interrupt. */
#define ST7528_1_SPI_Tx_ISR_INTC_CLR_PD            ((reg32 *) ST7528_1_SPI_Tx_ISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_ST7528_1_SPI_Tx_ISR_H */


/* [] END OF FILE */
