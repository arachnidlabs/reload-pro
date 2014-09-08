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

#if !defined(CY_SPIM_PVT_Display_SPI_H)
#define CY_SPIM_PVT_Display_SPI_H

#include "Display_SPI.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/

extern volatile uint8 Display_SPI_swStatusTx;
extern volatile uint8 Display_SPI_swStatusRx;

#if(Display_SPI_TX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 Display_SPI_txBuffer[Display_SPI_TX_BUFFER_SIZE];
    extern volatile uint8 Display_SPI_txBufferRead;
    extern volatile uint8 Display_SPI_txBufferWrite;
    extern volatile uint8 Display_SPI_txBufferFull;
#endif /* (Display_SPI_TX_SOFTWARE_BUF_ENABLED) */

#if(Display_SPI_RX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 Display_SPI_rxBuffer[Display_SPI_RX_BUFFER_SIZE];
    extern volatile uint8 Display_SPI_rxBufferRead;
    extern volatile uint8 Display_SPI_rxBufferWrite;
    extern volatile uint8 Display_SPI_rxBufferFull;
#endif /* (Display_SPI_RX_SOFTWARE_BUF_ENABLED) */

#endif /* CY_SPIM_PVT_Display_SPI_H */


/* [] END OF FILE */
