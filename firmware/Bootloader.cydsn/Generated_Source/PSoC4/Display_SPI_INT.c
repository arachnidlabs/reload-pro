/*******************************************************************************
* File Name: Display_SPI_INT.c
* Version 2.40
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Master
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Display_SPI_PVT.h"

/* User code required at start of ISR */
/* `#START Display_SPI_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: Display_SPI_TX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Display_SPI_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  Display_SPI_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  Display_SPI_txBuffer[Display_SPI_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(Display_SPI_TX_ISR)
{
    #if(Display_SPI_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (Display_SPI_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START Display_SPI_TX_ISR_START` */

    /* `#END` */

    #if(Display_SPI_TX_SOFTWARE_BUF_ENABLED)
        /* Check if TX data buffer is not empty and there is space in TX FIFO */
        while(Display_SPI_txBufferRead != Display_SPI_txBufferWrite)
        {
            tmpStatus = Display_SPI_GET_STATUS_TX(Display_SPI_swStatusTx);
            Display_SPI_swStatusTx = tmpStatus;

            if(0u != (Display_SPI_swStatusTx & Display_SPI_STS_TX_FIFO_NOT_FULL))
            {
                if(0u == Display_SPI_txBufferFull)
                {
                   Display_SPI_txBufferRead++;

                    if(Display_SPI_txBufferRead >= Display_SPI_TX_BUFFER_SIZE)
                    {
                        Display_SPI_txBufferRead = 0u;
                    }
                }
                else
                {
                    Display_SPI_txBufferFull = 0u;
                }

                /* Move data from the Buffer to the FIFO */
                CY_SET_REG8(Display_SPI_TXDATA_PTR,
                    Display_SPI_txBuffer[Display_SPI_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        if(Display_SPI_txBufferRead == Display_SPI_txBufferWrite)
        {
            /* TX Buffer is EMPTY: disable interrupt on TX NOT FULL */
            Display_SPI_TX_STATUS_MASK_REG &= ((uint8) ~Display_SPI_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* (Display_SPI_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START Display_SPI_TX_ISR_END` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: Display_SPI_RX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Display_SPI_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  Display_SPI_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  Display_SPI_rxBuffer[Display_SPI_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(Display_SPI_RX_ISR)
{
    #if(Display_SPI_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint8 rxData;
    #endif /* (Display_SPI_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START Display_SPI_RX_ISR_START` */

    /* `#END` */

    #if(Display_SPI_RX_SOFTWARE_BUF_ENABLED)

        tmpStatus = Display_SPI_GET_STATUS_RX(Display_SPI_swStatusRx);
        Display_SPI_swStatusRx = tmpStatus;

        /* Check if RX data FIFO has some data to be moved into the RX Buffer */
        while(0u != (Display_SPI_swStatusRx & Display_SPI_STS_RX_FIFO_NOT_EMPTY))
        {
            rxData = CY_GET_REG8(Display_SPI_RXDATA_PTR);

            /* Set next pointer. */
            Display_SPI_rxBufferWrite++;
            if(Display_SPI_rxBufferWrite >= Display_SPI_RX_BUFFER_SIZE)
            {
                Display_SPI_rxBufferWrite = 0u;
            }

            if(Display_SPI_rxBufferWrite == Display_SPI_rxBufferRead)
            {
                Display_SPI_rxBufferRead++;
                if(Display_SPI_rxBufferRead >= Display_SPI_RX_BUFFER_SIZE)
                {
                    Display_SPI_rxBufferRead = 0u;
                }

                Display_SPI_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            Display_SPI_rxBuffer[Display_SPI_rxBufferWrite] = rxData;

            tmpStatus = Display_SPI_GET_STATUS_RX(Display_SPI_swStatusRx);
            Display_SPI_swStatusRx = tmpStatus;
        }

    #endif /* (Display_SPI_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START Display_SPI_RX_ISR_END` */

    /* `#END` */
}

/* [] END OF FILE */
