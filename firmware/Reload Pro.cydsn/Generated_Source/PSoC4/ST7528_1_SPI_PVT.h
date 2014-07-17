/*******************************************************************************
* File Name: .h
* Version 2.40
*
* Description:
*  This private header file contains internal definitions for the SPIM
*  component. Do not use these definitions directly in your application.
*
* Note:
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_PVT_ST7528_1_SPI_H)
#define CY_SPIM_PVT_ST7528_1_SPI_H

#include "ST7528_1_SPI.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/

extern volatile uint8 ST7528_1_SPI_swStatusTx;
extern volatile uint8 ST7528_1_SPI_swStatusRx;

#if(ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 ST7528_1_SPI_txBuffer[ST7528_1_SPI_TX_BUFFER_SIZE];
    extern volatile uint8 ST7528_1_SPI_txBufferRead;
    extern volatile uint8 ST7528_1_SPI_txBufferWrite;
    extern volatile uint8 ST7528_1_SPI_txBufferFull;
#endif /* (ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED) */

#if(ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 ST7528_1_SPI_rxBuffer[ST7528_1_SPI_RX_BUFFER_SIZE];
    extern volatile uint8 ST7528_1_SPI_rxBufferRead;
    extern volatile uint8 ST7528_1_SPI_rxBufferWrite;
    extern volatile uint8 ST7528_1_SPI_rxBufferFull;
#endif /* (ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED) */

#endif /* CY_SPIM_PVT_ST7528_1_SPI_H */


/* [] END OF FILE */
