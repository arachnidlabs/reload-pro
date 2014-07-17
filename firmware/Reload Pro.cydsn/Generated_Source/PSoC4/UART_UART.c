/*******************************************************************************
* File Name: UART_UART.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_PVT.h"
#include "UART_SPI_UART_PVT.h"


#if(UART_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Config Structure Initialization
    ***************************************/

    const UART_UART_INIT_STRUCT UART_configUart =
    {
        UART_UART_SUB_MODE,
        UART_UART_DIRECTION,
        UART_UART_DATA_BITS_NUM,
        UART_UART_PARITY_TYPE,
        UART_UART_STOP_BITS_NUM,
        UART_UART_OVS_FACTOR,
        UART_UART_IRDA_LOW_POWER,
        UART_UART_MEDIAN_FILTER_ENABLE,
        UART_UART_RETRY_ON_NACK,
        UART_UART_IRDA_POLARITY,
        UART_UART_DROP_ON_PARITY_ERR,
        UART_UART_DROP_ON_FRAME_ERR,
        UART_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        UART_UART_MP_MODE_ENABLE,
        UART_UART_MP_ACCEPT_ADDRESS,
        UART_UART_MP_RX_ADDRESS,
        UART_UART_MP_RX_ADDRESS_MASK,
        (uint32) UART_SCB_IRQ_INTERNAL,
        UART_UART_INTR_RX_MASK,
        UART_UART_RX_TRIGGER_LEVEL,
        UART_UART_INTR_TX_MASK,
        UART_UART_TX_TRIGGER_LEVEL
    };


    /*******************************************************************************
    * Function Name: UART_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_UartInit(const UART_UART_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due bad function parameter */
        }
        else
        {
            /* Configure pins */
            UART_SetPins(UART_SCB_MODE_UART, config->mode, config->direction);

            /* Store internal configuration */
            UART_scbMode       = (uint8) UART_SCB_MODE_UART;
            UART_scbEnableWake = (uint8) config->enableWake;
            UART_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            UART_rxBuffer      =         config->rxBuffer;
            UART_rxDataBits    = (uint8) config->dataBits;
            UART_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            UART_txBuffer      =         config->txBuffer;
            UART_txDataBits    = (uint8) config->dataBits;
            UART_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(UART_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                UART_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (UART_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (UART_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                UART_CTRL_REG  = UART_GET_CTRL_OVS(config->oversample);
            }

            UART_CTRL_REG     |= UART_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             UART_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            UART_UART_CTRL_REG = UART_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            UART_UART_RX_CTRL_REG = UART_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        UART_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        UART_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        UART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        UART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(UART_UART_PARITY_NONE != config->parity)
            {
               UART_UART_RX_CTRL_REG |= UART_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    UART_UART_RX_CTRL_PARITY_ENABLED;
            }

            UART_RX_CTRL_REG      = UART_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                UART_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                UART_GET_UART_RX_CTRL_ENABLED(config->direction);

            UART_RX_FIFO_CTRL_REG = UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            UART_RX_MATCH_REG     = UART_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                UART_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            UART_UART_TX_CTRL_REG = UART_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                UART_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(UART_UART_PARITY_NONE != config->parity)
            {
               UART_UART_TX_CTRL_REG |= UART_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    UART_UART_TX_CTRL_PARITY_ENABLED;
            }

            UART_TX_CTRL_REG      = UART_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                UART_GET_UART_TX_CTRL_ENABLED(config->direction);

            UART_TX_FIFO_CTRL_REG = UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);



            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (UART_ISR_NUMBER);
            CyIntSetPriority(UART_ISR_NUMBER, UART_ISR_PRIORITY);
            (void) CyIntSetVector(UART_ISR_NUMBER, &UART_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(UART_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (UART_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(UART_RX_WAKE_ISR_NUMBER, UART_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(UART_RX_WAKE_ISR_NUMBER, &UART_UART_WAKEUP_ISR);
        #endif /* (UART_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            UART_INTR_I2C_EC_MASK_REG = UART_NO_INTR_SOURCES;
            UART_INTR_SPI_EC_MASK_REG = UART_NO_INTR_SOURCES;
            UART_INTR_SLAVE_MASK_REG  = UART_NO_INTR_SOURCES;
            UART_INTR_MASTER_MASK_REG = UART_NO_INTR_SOURCES;
            UART_INTR_RX_MASK_REG     = config->rxInterruptMask;
            UART_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            UART_rxBufferHead     = 0u;
            UART_rxBufferTail     = 0u;
            UART_rxBufferOverflow = 0u;

            /* Clrea TX buffer indexes */
            UART_txBufferHead = 0u;
            UART_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: UART_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_UartInit(void)
    {
        /* Configure UART interface */
        UART_CTRL_REG = UART_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        UART_UART_CTRL_REG = UART_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        UART_UART_RX_CTRL_REG = UART_UART_DEFAULT_UART_RX_CTRL;
        UART_RX_CTRL_REG      = UART_UART_DEFAULT_RX_CTRL;
        UART_RX_FIFO_CTRL_REG = UART_UART_DEFAULT_RX_FIFO_CTRL;
        UART_RX_MATCH_REG     = UART_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        UART_UART_TX_CTRL_REG = UART_UART_DEFAULT_UART_TX_CTRL;
        UART_TX_CTRL_REG      = UART_UART_DEFAULT_TX_CTRL;
        UART_TX_FIFO_CTRL_REG = UART_UART_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with UART handler but do not enable it */
    #if(UART_SCB_IRQ_INTERNAL)
        CyIntDisable    (UART_ISR_NUMBER);
        CyIntSetPriority(UART_ISR_NUMBER, UART_ISR_PRIORITY);
        (void) CyIntSetVector(UART_ISR_NUMBER, &UART_SPI_UART_ISR);
    #endif /* (UART_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(UART_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (UART_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(UART_RX_WAKE_ISR_NUMBER, UART_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(UART_RX_WAKE_ISR_NUMBER, &UART_UART_WAKEUP_ISR);
    #endif /* (UART_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        UART_INTR_I2C_EC_MASK_REG = UART_UART_DEFAULT_INTR_I2C_EC_MASK;
        UART_INTR_SPI_EC_MASK_REG = UART_UART_DEFAULT_INTR_SPI_EC_MASK;
        UART_INTR_SLAVE_MASK_REG  = UART_UART_DEFAULT_INTR_SLAVE_MASK;
        UART_INTR_MASTER_MASK_REG = UART_UART_DEFAULT_INTR_MASTER_MASK;
        UART_INTR_RX_MASK_REG     = UART_UART_DEFAULT_INTR_RX_MASK;
        UART_INTR_TX_MASK_REG     = UART_UART_DEFAULT_INTR_TX_MASK;

    #if(UART_INTERNAL_RX_SW_BUFFER_CONST)
        UART_rxBufferHead     = 0u;
        UART_rxBufferTail     = 0u;
        UART_rxBufferOverflow = 0u;
    #endif /* (UART_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(UART_INTERNAL_TX_SW_BUFFER_CONST)
        UART_txBufferHead = 0u;
        UART_txBufferTail = 0u;
    #endif /* (UART_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: UART_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the Multiprocessor
*  mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void UART_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = UART_RX_MATCH_REG;

    matchReg &= ((uint32) ~UART_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & UART_RX_MATCH_ADDR_MASK)); /* Set address  */

    UART_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: UART_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void UART_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = UART_RX_MATCH_REG;

    matchReg &= ((uint32) ~UART_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << UART_RX_MATCH_MASK_POS));

    UART_RX_MATCH_REG = matchReg;
}


#if(UART_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: UART_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from the software receive
    *    buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    *******************************************************************************/
    uint32 UART_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Read data only if there is data to read */
        if(0u != UART_SpiUartGetRxBufferSize())
        {
            rxData = UART_SpiUartReadRxData();
        }

        if(UART_CHECK_INTR_RX(UART_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: return zero */
            UART_ClearRxInterruptSource(UART_INTR_RX_ERR);
        }

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: UART_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the received byte
    *  and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved from the RX FIFO.
    *     Undefined data will be returned if the RX FIFO is empty.
    *   - The RX software buffer is enabled: returns data element from the software receive
    *     buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 15-8 contains status and bits 7-0 contains the next data element from
    *  receive buffer. If the bits 15-8 are non-zero, an error has occurred.
    *
    *******************************************************************************/
    uint32 UART_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;
        uint32 intSourceMask;

        intSourceMask = UART_SpiUartDisableIntRx();

        if(0u != UART_SpiUartGetRxBufferSize())
        {
             /*
             * Enable interrupt to receive more bytes: at least one byte is in
             * buffer.
             */
            UART_SpiUartEnableIntRx(intSourceMask);

            /* Get received byte */
            rxData = UART_SpiUartReadRxData();
        }
        else
        {
            /*
            * Read byte directly from RX FIFO: the underflow is raised in case
            * of empty. In other case the first received byte will be read.
            */
            rxData = UART_RX_FIFO_RD_REG;

            /*
            * Enable interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine in case
            * the byte was received and read above.
            */
            UART_SpiUartEnableIntRx(intSourceMask);
        }

        /* Get and clear RX error mask */
        tmpStatus = (UART_GetRxInterruptSource() & UART_INTR_RX_ERR);
        UART_ClearRxInterruptSource(UART_INTR_RX_ERR);

        /*
        * Put together data and error status:
        * MP mode and accept address: the 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return(rxData);
    }

#endif /* (UART_UART_RX_DIRECTION) */


#if(UART_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: UART_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Block the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            UART_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: UART_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and line feed (0x0A)
    *  into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_UartPutCRLF(uint32 txDataByte)
    {
        UART_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        UART_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        UART_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }
#endif /* (UART_UART_TX_DIRECTION) */


#if(UART_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: UART_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the active
    *  mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. On GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        UART_UART_RX_CTRL_REG |= UART_UART_RX_CTRL_SKIP_START;

    #if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(UART_MOSI_SCL_RX_WAKE_PIN)
            (void) UART_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (UART_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(UART_UART_RX_WAKE_PIN)
            (void) UART_rx_wake_ClearInterrupt();
        #endif /* (UART_UART_RX_WAKE_PIN) */
    #endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(UART_UART_RX_WAKEUP_IRQ)
        UART_RxWakeClearPendingInt();
        UART_RxWakeEnableInt();
    #endif /* (UART_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: UART_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt remains
    *  active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(UART_UART_RX_WAKEUP_IRQ)
        UART_RxWakeDisableInt();
    #endif /* (UART_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (UART_UART_WAKE_ENABLE_CONST) */


#if(UART_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: UART_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup event. This
    *  event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(UART_UART_WAKEUP_ISR)
    {
        /* Clear interrupt source: the event becomes multi triggered and is only disabled
        * by UART_UartRestoreConfig() call.
        */
    #if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(UART_MOSI_SCL_RX_WAKE_PIN)
            (void) UART_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (UART_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(UART_UART_RX_WAKE_PIN)
            (void) UART_rx_wake_ClearInterrupt();
        #endif /* (UART_UART_RX_WAKE_PIN) */
    #endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */
    }
#endif /* (UART_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
