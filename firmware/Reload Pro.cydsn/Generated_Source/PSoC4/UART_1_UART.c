/*******************************************************************************
* File Name: UART_1_UART.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_1_PVT.h"
#include "UART_1_SPI_UART_PVT.h"


#if(UART_1_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Config Structure Initialization
    ***************************************/

    const UART_1_UART_INIT_STRUCT UART_1_configUart =
    {
        UART_1_UART_SUB_MODE,
        UART_1_UART_DIRECTION,
        UART_1_UART_DATA_BITS_NUM,
        UART_1_UART_PARITY_TYPE,
        UART_1_UART_STOP_BITS_NUM,
        UART_1_UART_OVS_FACTOR,
        UART_1_UART_IRDA_LOW_POWER,
        UART_1_UART_MEDIAN_FILTER_ENABLE,
        UART_1_UART_RETRY_ON_NACK,
        UART_1_UART_IRDA_POLARITY,
        UART_1_UART_DROP_ON_PARITY_ERR,
        UART_1_UART_DROP_ON_FRAME_ERR,
        UART_1_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        UART_1_UART_MP_MODE_ENABLE,
        UART_1_UART_MP_ACCEPT_ADDRESS,
        UART_1_UART_MP_RX_ADDRESS,
        UART_1_UART_MP_RX_ADDRESS_MASK,
        UART_1_SCB_IRQ_INTERNAL,
        UART_1_UART_INTR_RX_MASK,
        UART_1_UART_RX_TRIGGER_LEVEL,
        UART_1_UART_INTR_TX_MASK,
        UART_1_UART_TX_TRIGGER_LEVEL
    };


    /*******************************************************************************
    * Function Name: UART_1_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for SPI operation.
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
    void UART_1_UartInit(const UART_1_UART_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due bad fucntion parameter */
        }
        else
        {
            /* Configure pins */
            UART_1_SetPins(UART_1_SCB_MODE_UART, config->mode, config->direction);

            /* Store internal configuration */
            UART_1_scbMode       = (uint8) UART_1_SCB_MODE_UART;
            UART_1_scbEnableWake = (uint8) config->enableWake;
            UART_1_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            UART_1_rxBuffer      =         config->rxBuffer;
            UART_1_rxDataBits    = (uint8) config->dataBits;
            UART_1_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            UART_1_txBuffer      =         config->txBuffer;
            UART_1_txDataBits    = (uint8) config->dataBits;
            UART_1_txBufferSize  = (uint8) config->txBufferSize;


            /* Configure UART interface */
            if(UART_1_UART_MODE_IRDA == config->mode)
            {
                /* OVS settigns: IrDA */
                UART_1_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (UART_1_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (UART_1_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settigns: UART and SmartCard */
                UART_1_CTRL_REG  = UART_1_GET_CTRL_OVS(config->oversample);
            }

            UART_1_CTRL_REG     |= UART_1_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             UART_1_CTRL_UART;

            /* Confiuure submode: UART, SmartCard or IrDA */
            UART_1_UART_CTRL_REG = UART_1_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            UART_1_UART_RX_CTRL_REG = UART_1_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        UART_1_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        UART_1_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        UART_1_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        UART_1_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(UART_1_UART_PARITY_NONE != config->parity)
            {
               UART_1_UART_RX_CTRL_REG |= UART_1_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    UART_1_UART_RX_CTRL_PARITY_ENABLED;
            }

            UART_1_RX_CTRL_REG      = UART_1_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                UART_1_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                UART_1_GET_UART_RX_CTRL_ENABLED(config->direction);

            UART_1_RX_FIFO_CTRL_REG = UART_1_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            UART_1_RX_MATCH_REG     = UART_1_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                UART_1_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            UART_1_UART_TX_CTRL_REG = UART_1_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                UART_1_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(UART_1_UART_PARITY_NONE != config->parity)
            {
               UART_1_UART_TX_CTRL_REG |= UART_1_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    UART_1_UART_TX_CTRL_PARITY_ENABLED;
            }

            UART_1_TX_CTRL_REG      = UART_1_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                UART_1_GET_UART_TX_CTRL_ENABLED(config->direction);

            UART_1_TX_FIFO_CTRL_REG = UART_1_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);


            /* Configure WAKE interrupt */
            #if(UART_1_UART_RX_WAKEUP_IRQ)
                UART_1_RX_WAKEUP_IRQ_StartEx(&UART_1_UART_WAKEUP_ISR);
                UART_1_RX_WAKEUP_IRQ_Disable();
            #endif /* (UART_1_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt with UART handler */
            UART_1_SCB_IRQ_Disable();
            UART_1_SCB_IRQ_SetVector(&UART_1_SPI_UART_ISR);
            UART_1_SCB_IRQ_SetPriority((uint8)UART_1_SCB_IRQ_INTC_PRIOR_NUMBER);

            /* Configure interrupt sources */
            UART_1_INTR_I2C_EC_MASK_REG = UART_1_NO_INTR_SOURCES;
            UART_1_INTR_SPI_EC_MASK_REG = UART_1_NO_INTR_SOURCES;
            UART_1_INTR_SLAVE_MASK_REG  = UART_1_NO_INTR_SOURCES;
            UART_1_INTR_MASTER_MASK_REG = UART_1_NO_INTR_SOURCES;
            UART_1_INTR_RX_MASK_REG     = config->rxInterruptMask;
            UART_1_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            UART_1_rxBufferHead     = 0u;
            UART_1_rxBufferTail     = 0u;
            UART_1_rxBufferOverflow = 0u;

            /* Clrea TX buffer indexes */
            UART_1_txBufferHead = 0u;
            UART_1_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: UART_1_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for SPI operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_1_UartInit(void)
    {
        /* Configure UART interface */
        UART_1_CTRL_REG = UART_1_UART_DEFAULT_CTRL;

        /* Confiuure submode: UART, SmartCard or IrDA */
        UART_1_UART_CTRL_REG = UART_1_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        UART_1_UART_RX_CTRL_REG = UART_1_UART_DEFAULT_UART_RX_CTRL;
        UART_1_RX_CTRL_REG      = UART_1_UART_DEFAULT_RX_CTRL;
        UART_1_RX_FIFO_CTRL_REG = UART_1_UART_DEFAULT_RX_FIFO_CTRL;
        UART_1_RX_MATCH_REG     = UART_1_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        UART_1_UART_TX_CTRL_REG = UART_1_UART_DEFAULT_UART_TX_CTRL;
        UART_1_TX_CTRL_REG      = UART_1_UART_DEFAULT_TX_CTRL;
        UART_1_TX_FIFO_CTRL_REG = UART_1_UART_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with UART handler */
        #if(UART_1_SCB_IRQ_INTERNAL)
            UART_1_SCB_IRQ_Disable();
            UART_1_SCB_IRQ_SetVector(&UART_1_SPI_UART_ISR);
            UART_1_SCB_IRQ_SetPriority((uint8)UART_1_SCB_IRQ_INTC_PRIOR_NUMBER);
        #endif /* (UART_1_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
        #if(UART_1_UART_RX_WAKEUP_IRQ)
            UART_1_RX_WAKEUP_IRQ_StartEx(&UART_1_UART_WAKEUP_ISR);
            UART_1_RX_WAKEUP_IRQ_Disable();
        #endif /* (UART_1_UART_RX_WAKEUP_IRQ) */
        
        /* Configure interrupt sources */
        UART_1_INTR_I2C_EC_MASK_REG = UART_1_UART_DEFAULT_INTR_I2C_EC_MASK;
        UART_1_INTR_SPI_EC_MASK_REG = UART_1_UART_DEFAULT_INTR_SPI_EC_MASK;
        UART_1_INTR_SLAVE_MASK_REG  = UART_1_UART_DEFAULT_INTR_SLAVE_MASK;
        UART_1_INTR_MASTER_MASK_REG = UART_1_UART_DEFAULT_INTR_MASTER_MASK;
        UART_1_INTR_RX_MASK_REG     = UART_1_UART_DEFAULT_INTR_RX_MASK;
        UART_1_INTR_TX_MASK_REG     = UART_1_UART_DEFAULT_INTR_TX_MASK;

        #if(UART_1_INTERNAL_RX_SW_BUFFER_CONST)
            UART_1_rxBufferHead     = 0u;
            UART_1_rxBufferTail     = 0u;
            UART_1_rxBufferOverflow = 0u;
        #endif /* (UART_1_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(UART_1_INTERNAL_TX_SW_BUFFER_CONST)
            UART_1_txBufferHead = 0u;
            UART_1_txBufferTail = 0u;
        #endif /* (UART_1_INTERNAL_TX_SW_BUFFER_CONST) */
    }

#endif /* (UART_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: UART_1_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in Multiprocessor
*  mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void UART_1_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = UART_1_RX_MATCH_REG;

    matchReg &= ((uint32) ~UART_1_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & UART_1_RX_MATCH_ADDR_MASK)); /* Set address  */

    UART_1_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: UART_1_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in Multiprocessor mode.
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
void UART_1_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = UART_1_RX_MATCH_REG;

    matchReg &= ((uint32) ~UART_1_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << UART_1_RX_MATCH_MASK_POS));

    UART_1_RX_MATCH_REG = matchReg;
}


#if(UART_1_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: UART_1_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 is valid characters and 0 indicates an error occurred or
    *  no data is present.
    *  RX software buffer disabled: returns data element retrieved from RX FIFO.
    *  Undefined data will be returned if the RX FIFO is empty.
    *  RX software buffer enabled: Returns data element from the software receive
    *  buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    *******************************************************************************/
    uint32 UART_1_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Read data only if there is data to read */
        if(0u != UART_1_SpiUartGetRxBufferSize())
        {
            rxData = UART_1_SpiUartReadRxData();
        }

        if(UART_1_CHECK_INTR_RX(UART_1_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occured: return zero */
            UART_1_ClearRxInterruptSource(UART_1_INTR_RX_ERR);
        }

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: UART_1_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves next data element from the receive buffer, returns received byte
    *  and error condition.
    *  RX software buffer disabled: Returns data element retrieved from RX FIFO.
    *  Undefined data will be returned if the RX FIFO is empty.
    *  RX software buffer enabled: Returns data element from the software receive
    *  buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 15-8 contains status and bits 7-0 contains the next data element from
    *  receive buffer. If the bits 15-8 are nonzero, an error has occurred.
    *
    *******************************************************************************/
    uint32 UART_1_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;
        uint32 intSourceMask;

        intSourceMask = UART_1_SpiUartDisableIntRx();

        if(0u != UART_1_SpiUartGetRxBufferSize())
        {
             /*
             * Enable interrupt to receive more bytes: at least one byte is in
             * buffer.
             */
            UART_1_SpiUartEnableIntRx(intSourceMask);

            /* Get received byte */
            rxData = UART_1_SpiUartReadRxData();
        }
        else
        {
            /*
            * Read byte directly from RX FIFO: the underflow is raised in case
            * of empty. In other case the first received byte will be read.
            */
            rxData = UART_1_RX_FIFO_RD_REG;

            /*
            * Enable interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by interrupt routine in case
            * byte was received and read above.
            */
            UART_1_SpiUartEnableIntRx(intSourceMask);
        }

        /* Get and clear RX error mask */
        tmpStatus = (UART_1_GetRxInterruptSource() & UART_1_INTR_RX_ERR);
        UART_1_ClearRxInterruptSource(UART_1_INTR_RX_ERR);

        /*
        * Put together data and error status:
        * MP mode and accept address: the 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return(rxData);
    }

#endif /* (UART_1_UART_RX_DIRECTION) */


#if(UART_1_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: UART_1_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_1_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data will be sent */
        while(string[bufIndex] != ((char8) 0))
        {
            UART_1_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: UART_1_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places byte of data followed by a carriage return (0x0D) and line feed (0x0A)
    *  to the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_1_UartPutCRLF(uint32 txDataByte)
    {
        UART_1_UartPutChar(txDataByte);  /* Blocks the control flow until all data will be sent */
        UART_1_UartPutChar(0x0Du);       /* Blocks the control flow until all data will be sent */
        UART_1_UartPutChar(0x0Au);       /* Blocks the control flow until all data will be sent */
    }
#endif /* (UART_1_UART_TX_DIRECTION) */


#if(UART_1_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: UART_1_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Wakeup disabled: does nothing.
    *  Wakeup enabled: clears SCB_backup.enableStateto keep component enabled while
    *  DeepSleep. Clears and enables interrupt on falling edge of rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in active mode
    *  therefore requires to be cleared by this API. It makes uart wakeup single
    *  triggered event.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_1_UartSaveConfig(void)
    {
        /* Clear interrupt activy:
        *  - set skip start and disable RX. On GPIO wakeup the RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers while normal operations.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        UART_1_UART_RX_CTRL_REG |= UART_1_UART_RX_CTRL_SKIP_START;

        #if(UART_1_SCB_MODE_UNCONFIG_CONST_CFG)
            #if(UART_1_MOSI_SCL_RX_WAKE_PIN)
                (void) UART_1_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
            #endif /* (UART_1_MOSI_SCL_RX_WAKE_PIN) */
        #else
            #if(UART_1_UART_RX_WAKE_PIN)
                (void) UART_1_rx_wake_ClearInterrupt();
            #endif /* (UART_1_UART_RX_WAKE_PIN) */
        #endif /* (UART_1_SCB_MODE_UNCONFIG_CONST_CFG) */

        #if(UART_1_UART_RX_WAKEUP_IRQ)
            UART_1_RX_WAKEUP_IRQ_ClearPending();
            UART_1_RX_WAKEUP_IRQ_Enable();
        #endif /* (UART_1_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: UART_1_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Does nothing.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void UART_1_UartRestoreConfig(void)
    {
        /* Disable RX GPIO interrupt: no more triggers in active mode */
        #if(UART_1_UART_RX_WAKEUP_IRQ)
            UART_1_RX_WAKEUP_IRQ_Disable();
        #endif /* (UART_1_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (UART_1_UART_WAKE_ENABLE_CONST) */


#if(UART_1_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: UART_1_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles Interrupt Service Routine for SCB UART mode GPIO wakeup event.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(UART_1_UART_WAKEUP_ISR)
    {
        /* Clear interrupt source: the event becomes multi triggerred and only disabled
        * by UART_1_UartRestoreConfig() call.
        */
        #if(UART_1_SCB_MODE_UNCONFIG_CONST_CFG)
            #if(UART_1_MOSI_SCL_RX_WAKE_PIN)
                (void) UART_1_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
            #endif /* (UART_1_MOSI_SCL_RX_WAKE_PIN) */
        #else
            #if(UART_1_UART_RX_WAKE_PIN)
                (void) UART_1_rx_wake_ClearInterrupt();
            #endif /* (UART_1_UART_RX_WAKE_PIN) */
        #endif /* (UART_1_SCB_MODE_UNCONFIG_CONST_CFG) */
    }
#endif /* (UART_1_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
