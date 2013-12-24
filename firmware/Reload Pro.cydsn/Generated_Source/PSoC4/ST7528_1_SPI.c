/*******************************************************************************
* File Name: ST7528_1_SPI.c
* Version 2.40
*
* Description:
*  This file provides all API functionality of the SPI Master component.
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

#include "ST7528_1_SPI_PVT.h"

#if(ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED)
    volatile uint8 ST7528_1_SPI_txBuffer[ST7528_1_SPI_TX_BUFFER_SIZE] = {0u};
    volatile uint8 ST7528_1_SPI_txBufferFull;
    volatile uint8 ST7528_1_SPI_txBufferRead;
    volatile uint8 ST7528_1_SPI_txBufferWrite;
#endif /* (ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED) */

#if(ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED)
    volatile uint8 ST7528_1_SPI_rxBuffer[ST7528_1_SPI_RX_BUFFER_SIZE] = {0u};
    volatile uint8 ST7528_1_SPI_rxBufferFull;
    volatile uint8 ST7528_1_SPI_rxBufferRead;
    volatile uint8 ST7528_1_SPI_rxBufferWrite;
#endif /* (ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED) */

uint8 ST7528_1_SPI_initVar = 0u;

volatile uint8 ST7528_1_SPI_swStatusTx;
volatile uint8 ST7528_1_SPI_swStatusRx;


/*******************************************************************************
* Function Name: ST7528_1_SPI_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default SPIM configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  When this function is called it initializes all of the necessary parameters
*  for execution. i.e. setting the initial interrupt mask, configuring the
*  interrupt service routine, configuring the bit-counter parameters and
*  clearing the FIFO and Status Register.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ST7528_1_SPI_Init(void) 
{
    /* Initialize the Bit counter */
    ST7528_1_SPI_COUNTER_PERIOD_REG = ST7528_1_SPI_BITCTR_INIT;

    /* Init TX ISR  */
    #if(0u != ST7528_1_SPI_INTERNAL_TX_INT_ENABLED)
        CyIntDisable         (ST7528_1_SPI_TX_ISR_NUMBER);
        CyIntSetPriority     (ST7528_1_SPI_TX_ISR_NUMBER,  ST7528_1_SPI_TX_ISR_PRIORITY);
        (void) CyIntSetVector(ST7528_1_SPI_TX_ISR_NUMBER, &ST7528_1_SPI_TX_ISR);
    #endif /* (0u != ST7528_1_SPI_INTERNAL_TX_INT_ENABLED) */

    /* Init RX ISR  */
    #if(0u != ST7528_1_SPI_INTERNAL_RX_INT_ENABLED)
        CyIntDisable         (ST7528_1_SPI_RX_ISR_NUMBER);
        CyIntSetPriority     (ST7528_1_SPI_RX_ISR_NUMBER,  ST7528_1_SPI_RX_ISR_PRIORITY);
        (void) CyIntSetVector(ST7528_1_SPI_RX_ISR_NUMBER, &ST7528_1_SPI_RX_ISR);
    #endif /* (0u != ST7528_1_SPI_INTERNAL_RX_INT_ENABLED) */

    /* Clear any stray data from the RX and TX FIFO */
    ST7528_1_SPI_ClearFIFO();

    #if(ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED)
        ST7528_1_SPI_rxBufferFull  = 0u;
        ST7528_1_SPI_rxBufferRead  = 0u;
        ST7528_1_SPI_rxBufferWrite = 0u;
    #endif /* (ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED) */

    #if(ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED)
        ST7528_1_SPI_txBufferFull  = 0u;
        ST7528_1_SPI_txBufferRead  = 0u;
        ST7528_1_SPI_txBufferWrite = 0u;
    #endif /* (ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED) */

    (void) ST7528_1_SPI_ReadTxStatus(); /* Clear Tx status and swStatusTx */
    (void) ST7528_1_SPI_ReadRxStatus(); /* Clear Rx status and swStatusRx */

    /* Configure TX and RX interrupt mask */
    ST7528_1_SPI_TX_STATUS_MASK_REG = ST7528_1_SPI_TX_INIT_INTERRUPTS_MASK;
    ST7528_1_SPI_RX_STATUS_MASK_REG = ST7528_1_SPI_RX_INIT_INTERRUPTS_MASK;
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_Enable
********************************************************************************
*
* Summary:
*  Enable SPIM component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ST7528_1_SPI_Enable(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    ST7528_1_SPI_COUNTER_CONTROL_REG |= ST7528_1_SPI_CNTR_ENABLE;
    ST7528_1_SPI_TX_STATUS_ACTL_REG  |= ST7528_1_SPI_INT_ENABLE;
    ST7528_1_SPI_RX_STATUS_ACTL_REG  |= ST7528_1_SPI_INT_ENABLE;
    CyExitCriticalSection(enableInterrupts);

    #if(0u != ST7528_1_SPI_INTERNAL_CLOCK)
        ST7528_1_SPI_IntClock_Enable();
    #endif /* (0u != ST7528_1_SPI_INTERNAL_CLOCK) */

    ST7528_1_SPI_EnableTxInt();
    ST7528_1_SPI_EnableRxInt();
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the SPI Master component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  ST7528_1_SPI_initVar - used to check initial configuration, modified on
*  first function call.
*
* Theory:
*  Enable the clock input to enable operation.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ST7528_1_SPI_Start(void) 
{
    if(0u == ST7528_1_SPI_initVar)
    {
        ST7528_1_SPI_Init();
        ST7528_1_SPI_initVar = 1u;
    }

    ST7528_1_SPI_Enable();
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_Stop
********************************************************************************
*
* Summary:
*  Disable the SPI Master component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the clock input to enable operation.
*
*******************************************************************************/
void ST7528_1_SPI_Stop(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    ST7528_1_SPI_TX_STATUS_ACTL_REG &= ((uint8) ~ST7528_1_SPI_INT_ENABLE);
    ST7528_1_SPI_RX_STATUS_ACTL_REG &= ((uint8) ~ST7528_1_SPI_INT_ENABLE);
    CyExitCriticalSection(enableInterrupts);

    #if(0u != ST7528_1_SPI_INTERNAL_CLOCK)
        ST7528_1_SPI_IntClock_Disable();
    #endif /* (0u != ST7528_1_SPI_INTERNAL_CLOCK) */

    ST7528_1_SPI_DisableTxInt();
    ST7528_1_SPI_DisableRxInt();
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_EnableTxInt
********************************************************************************
*
* Summary:
*  Enable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void ST7528_1_SPI_EnableTxInt(void) 
{
    #if(0u != ST7528_1_SPI_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(ST7528_1_SPI_TX_ISR_NUMBER);
    #endif /* (0u != ST7528_1_SPI_INTERNAL_TX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_EnableRxInt
********************************************************************************
*
* Summary:
*  Enable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void ST7528_1_SPI_EnableRxInt(void) 
{
    #if(0u != ST7528_1_SPI_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(ST7528_1_SPI_RX_ISR_NUMBER);
    #endif /* (0u != ST7528_1_SPI_INTERNAL_RX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_DisableTxInt
********************************************************************************
*
* Summary:
*  Disable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void ST7528_1_SPI_DisableTxInt(void) 
{
    #if(0u != ST7528_1_SPI_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(ST7528_1_SPI_TX_ISR_NUMBER);
    #endif /* (0u != ST7528_1_SPI_INTERNAL_TX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_DisableRxInt
********************************************************************************
*
* Summary:
*  Disable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void ST7528_1_SPI_DisableRxInt(void) 
{
    #if(0u != ST7528_1_SPI_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(ST7528_1_SPI_RX_ISR_NUMBER);
    #endif /* (0u != ST7528_1_SPI_INTERNAL_RX_INT_ENABLED) */
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_SetTxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void ST7528_1_SPI_SetTxInterruptMode(uint8 intSrc) 
{
    ST7528_1_SPI_TX_STATUS_MASK_REG = intSrc;
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_SetRxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void ST7528_1_SPI_SetRxInterruptMode(uint8 intSrc) 
{
    ST7528_1_SPI_RX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_ReadTxStatus
********************************************************************************
*
* Summary:
*  Read the Tx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Tx status register.
*
* Global variables:
*  ST7528_1_SPI_swStatusTx - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Tx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 ST7528_1_SPI_ReadTxStatus(void) 
{
    uint8 tmpStatus;

    #if(ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED)
        /* Disable TX interrupt to protect global veriables */
        ST7528_1_SPI_DisableTxInt();

        tmpStatus = ST7528_1_SPI_GET_STATUS_TX(ST7528_1_SPI_swStatusTx);
        ST7528_1_SPI_swStatusTx = 0u;

        ST7528_1_SPI_EnableTxInt();

    #else

        tmpStatus = ST7528_1_SPI_TX_STATUS_REG;

    #endif /* (ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_ReadRxStatus
********************************************************************************
*
* Summary:
*  Read the Rx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Rx status register.
*
* Global variables:
*  ST7528_1_SPI_swStatusRx - used to store in software Rx status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Rx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Rx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 ST7528_1_SPI_ReadRxStatus(void) 
{
    uint8 tmpStatus;

    #if(ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED)
        /* Disable RX interrupt to protect global veriables */
        ST7528_1_SPI_DisableRxInt();

        tmpStatus = ST7528_1_SPI_GET_STATUS_RX(ST7528_1_SPI_swStatusRx);
        ST7528_1_SPI_swStatusRx = 0u;

        ST7528_1_SPI_EnableRxInt();

    #else

        tmpStatus = ST7528_1_SPI_RX_STATUS_REG;

    #endif /* (ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_WriteTxData
********************************************************************************
*
* Summary:
*  Write a byte of data to be sent across the SPI.
*
* Parameters:
*  txDataByte: The data value to send across the SPI.
*
* Return:
*  None.
*
* Global variables:
*  ST7528_1_SPI_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call if TX Software Buffer is used.
*  ST7528_1_SPI_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*  ST7528_1_SPI_txBuffer[ST7528_1_SPI_TX_BUFFER_SIZE] - used to store
*  data to sending, modified every function call if TX Software Buffer is used.
*
* Theory:
*  Allows the user to transmit any byte of data in a single transfer.
*
* Side Effects:
*  If this function is called again before the previous byte is finished then
*  the next byte will be appended to the transfer with no time between
*  the byte transfers. Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ST7528_1_SPI_WriteTxData(uint8 txData) 
{
    #if(ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED)

        uint8 tempStatus;
        uint8 tmpTxBufferRead;

        /* Block if TX buffer is FULL: don't overwrite */
        do
        {
            tmpTxBufferRead = ST7528_1_SPI_txBufferRead;
            if(0u == tmpTxBufferRead)
            {
                tmpTxBufferRead = (ST7528_1_SPI_TX_BUFFER_SIZE - 1u);
            }
            else
            {
                tmpTxBufferRead--;
            }

        }while(tmpTxBufferRead == ST7528_1_SPI_txBufferWrite);

        /* Disable TX interrupt to protect global veriables */
        ST7528_1_SPI_DisableTxInt();

        tempStatus = ST7528_1_SPI_GET_STATUS_TX(ST7528_1_SPI_swStatusTx);
        ST7528_1_SPI_swStatusTx = tempStatus;


        if((ST7528_1_SPI_txBufferRead == ST7528_1_SPI_txBufferWrite) &&
           (0u != (ST7528_1_SPI_swStatusTx & ST7528_1_SPI_STS_TX_FIFO_NOT_FULL)))
        {
            /* Add directly to the TX FIFO */
            CY_SET_REG8(ST7528_1_SPI_TXDATA_PTR, txData);
        }
        else
        {
            /* Add to the TX software buffer */
            ST7528_1_SPI_txBufferWrite++;
            if(ST7528_1_SPI_txBufferWrite >= ST7528_1_SPI_TX_BUFFER_SIZE)
            {
                ST7528_1_SPI_txBufferWrite = 0u;
            }

            if(ST7528_1_SPI_txBufferWrite == ST7528_1_SPI_txBufferRead)
            {
                ST7528_1_SPI_txBufferRead++;
                if(ST7528_1_SPI_txBufferRead >= ST7528_1_SPI_TX_BUFFER_SIZE)
                {
                    ST7528_1_SPI_txBufferRead = 0u;
                }
                ST7528_1_SPI_txBufferFull = 1u;
            }

            ST7528_1_SPI_txBuffer[ST7528_1_SPI_txBufferWrite] = txData;

            ST7528_1_SPI_TX_STATUS_MASK_REG |= ST7528_1_SPI_STS_TX_FIFO_NOT_FULL;
        }

        ST7528_1_SPI_EnableTxInt();

    #else

        while(0u == (ST7528_1_SPI_TX_STATUS_REG & ST7528_1_SPI_STS_TX_FIFO_NOT_FULL))
        {
            ; /* Wait for room in FIFO */
        }

        /* Put byte in TX FIFO */
        CY_SET_REG8(ST7528_1_SPI_TXDATA_PTR, txData);

    #endif /* (ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED) */
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_ReadRxData
********************************************************************************
*
* Summary:
*  Read the next byte of data received across the SPI.
*
* Parameters:
*  None.
*
* Return:
*  The next byte of data read from the FIFO.
*
* Global variables:
*  ST7528_1_SPI_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  ST7528_1_SPI_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function
*  call if RX Software Buffer is used.
*  ST7528_1_SPI_rxBuffer[ST7528_1_SPI_RX_BUFFER_SIZE] - used to store
*  received data.
*
* Theory:
*  Allows the user to read a byte of data received.
*
* Side Effects:
*  Will return invalid data if the FIFO is empty. The user should Call
*  GetRxBufferSize() and if it returns a non-zero value then it is safe to call
*  ReadByte() function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 ST7528_1_SPI_ReadRxData(void) 
{
    uint8 rxData;

    #if(ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED)

        /* Disable RX interrupt to protect global veriables */
        ST7528_1_SPI_DisableRxInt();

        if(ST7528_1_SPI_rxBufferRead != ST7528_1_SPI_rxBufferWrite)
        {
            if(0u == ST7528_1_SPI_rxBufferFull)
            {
                ST7528_1_SPI_rxBufferRead++;
                if(ST7528_1_SPI_rxBufferRead >= ST7528_1_SPI_RX_BUFFER_SIZE)
                {
                    ST7528_1_SPI_rxBufferRead = 0u;
                }
            }
            else
            {
                ST7528_1_SPI_rxBufferFull = 0u;
            }
        }

        rxData = ST7528_1_SPI_rxBuffer[ST7528_1_SPI_rxBufferRead];

        ST7528_1_SPI_EnableRxInt();

    #else

        rxData = CY_GET_REG8(ST7528_1_SPI_RXDATA_PTR);

    #endif /* (ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED) */

    return(rxData);
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_GetRxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the RX buffer.
*  If RX Software Buffer not used then function return 0 if FIFO empty or 1 if
*  FIFO not empty. In another case function return size of RX Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the RX buffer.
*
* Global variables:
*  ST7528_1_SPI_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  ST7528_1_SPI_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
uint8 ST7528_1_SPI_GetRxBufferSize(void) 
{
    uint8 size;

    #if(ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED)

        /* Disable RX interrupt to protect global veriables */
        ST7528_1_SPI_DisableRxInt();

        if(ST7528_1_SPI_rxBufferRead == ST7528_1_SPI_rxBufferWrite)
        {
            size = 0u;
        }
        else if(ST7528_1_SPI_rxBufferRead < ST7528_1_SPI_rxBufferWrite)
        {
            size = (ST7528_1_SPI_rxBufferWrite - ST7528_1_SPI_rxBufferRead);
        }
        else
        {
            size = (ST7528_1_SPI_RX_BUFFER_SIZE - ST7528_1_SPI_rxBufferRead) + ST7528_1_SPI_rxBufferWrite;
        }

        ST7528_1_SPI_EnableRxInt();

    #else

        /* We can only know if there is data in the RX FIFO */
        size = (0u != (ST7528_1_SPI_RX_STATUS_REG & ST7528_1_SPI_STS_RX_FIFO_NOT_EMPTY)) ? 1u : 0u;

    #endif /* (ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED) */

    return(size);
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_GetTxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the TX buffer.
*  If TX Software Buffer not used then function return 0 - if FIFO empty, 1 - if
*  FIFO not full, 4 - if FIFO full. In another case function return size of TX
*  Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the TX buffer.
*
* Global variables:
*  ST7528_1_SPI_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  ST7528_1_SPI_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
uint8  ST7528_1_SPI_GetTxBufferSize(void) 
{
    uint8 size;

    #if(ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED)
        /* Disable TX interrupt to protect global veriables */
        ST7528_1_SPI_DisableTxInt();

        if(ST7528_1_SPI_txBufferRead == ST7528_1_SPI_txBufferWrite)
        {
            size = 0u;
        }
        else if(ST7528_1_SPI_txBufferRead < ST7528_1_SPI_txBufferWrite)
        {
            size = (ST7528_1_SPI_txBufferWrite - ST7528_1_SPI_txBufferRead);
        }
        else
        {
            size = (ST7528_1_SPI_TX_BUFFER_SIZE - ST7528_1_SPI_txBufferRead) + ST7528_1_SPI_txBufferWrite;
        }

        ST7528_1_SPI_EnableTxInt();

    #else

        size = ST7528_1_SPI_TX_STATUS_REG;

        if(0u != (size & ST7528_1_SPI_STS_TX_FIFO_EMPTY))
        {
            size = 0u;
        }
        else if(0u != (size & ST7528_1_SPI_STS_TX_FIFO_NOT_FULL))
        {
            size = 1u;
        }
        else
        {
            size = ST7528_1_SPI_FIFO_SIZE;
        }

    #endif /* (ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED) */

    return(size);
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_ClearRxBuffer
********************************************************************************
*
* Summary:
*  Clear the RX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  ST7528_1_SPI_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer, modified every function
*  call - resets to zero.
*  ST7528_1_SPI_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any received data not read from the RAM buffer will be lost when overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ST7528_1_SPI_ClearRxBuffer(void) 
{
    /* Clear Hardware RX FIFO */
    while(0u !=(ST7528_1_SPI_RX_STATUS_REG & ST7528_1_SPI_STS_RX_FIFO_NOT_EMPTY))
    {
        (void) CY_GET_REG8(ST7528_1_SPI_RXDATA_PTR);
    }

    #if(ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED)
        /* Disable RX interrupt to protect global veriables */
        ST7528_1_SPI_DisableRxInt();

        ST7528_1_SPI_rxBufferFull  = 0u;
        ST7528_1_SPI_rxBufferRead  = 0u;
        ST7528_1_SPI_rxBufferWrite = 0u;

        ST7528_1_SPI_EnableRxInt();
    #endif /* (ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED) */
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_ClearTxBuffer
********************************************************************************
*
* Summary:
*  Clear the TX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  ST7528_1_SPI_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call - resets to zero.
*  ST7528_1_SPI_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any data not yet transmitted from the RAM buffer will be lost when
*  overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ST7528_1_SPI_ClearTxBuffer(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    /* Clear TX FIFO */
    ST7528_1_SPI_AUX_CONTROL_DP0_REG |= ((uint8)  ST7528_1_SPI_TX_FIFO_CLR);
    ST7528_1_SPI_AUX_CONTROL_DP0_REG &= ((uint8) ~ST7528_1_SPI_TX_FIFO_CLR);

    #if(ST7528_1_SPI_USE_SECOND_DATAPATH)
        /* Clear TX FIFO for 2nd Datapath */
        ST7528_1_SPI_AUX_CONTROL_DP1_REG |= ((uint8)  ST7528_1_SPI_TX_FIFO_CLR);
        ST7528_1_SPI_AUX_CONTROL_DP1_REG &= ((uint8) ~ST7528_1_SPI_TX_FIFO_CLR);
    #endif /* (ST7528_1_SPI_USE_SECOND_DATAPATH) */
    CyExitCriticalSection(enableInterrupts);

    #if(ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED)
        /* Disable TX interrupt to protect global veriables */
        ST7528_1_SPI_DisableTxInt();

        ST7528_1_SPI_txBufferFull  = 0u;
        ST7528_1_SPI_txBufferRead  = 0u;
        ST7528_1_SPI_txBufferWrite = 0u;

        /* Buffer is EMPTY: disable TX FIFO NOT FULL interrupt */
        ST7528_1_SPI_TX_STATUS_MASK_REG &= ((uint8) ~ST7528_1_SPI_STS_TX_FIFO_NOT_FULL);

        ST7528_1_SPI_EnableTxInt();
    #endif /* (ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED) */
}


#if(0u != ST7528_1_SPI_BIDIRECTIONAL_MODE)
    /*******************************************************************************
    * Function Name: ST7528_1_SPI_TxEnable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI master is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to transmit.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void ST7528_1_SPI_TxEnable(void) 
    {
        ST7528_1_SPI_CONTROL_REG |= ST7528_1_SPI_CTRL_TX_SIGNAL_EN;
    }


    /*******************************************************************************
    * Function Name: ST7528_1_SPI_TxDisable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI master is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to receive.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void ST7528_1_SPI_TxDisable(void) 
    {
        ST7528_1_SPI_CONTROL_REG &= ((uint8) ~ST7528_1_SPI_CTRL_TX_SIGNAL_EN);
    }

#endif /* (0u != ST7528_1_SPI_BIDIRECTIONAL_MODE) */


/*******************************************************************************
* Function Name: ST7528_1_SPI_PutArray
********************************************************************************
*
* Summary:
*  Write available data from ROM/RAM to the TX buffer while space is available
*  in the TX buffer. Keep trying until all data is passed to the TX buffer.
*
* Parameters:
*  *buffer: Pointer to the location in RAM containing the data to send
*  byteCount: The number of bytes to move to the transmit buffer.
*
* Return:
*  None.
*
* Side Effects:
*  Will stay in this routine until all data has been sent.  May get locked in
*  this loop if data is not being initiated by the master if there is not
*  enough room in the TX FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ST7528_1_SPI_PutArray(const uint8 buffer[], uint8 byteCount)
                                                                          
{
    uint8 bufIndex;

    bufIndex = 0u;

    while(byteCount > 0u)
    {
        ST7528_1_SPI_WriteTxData(buffer[bufIndex]);
        bufIndex++;
        byteCount--;
    }
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_ClearFIFO
********************************************************************************
*
* Summary:
*  Clear the RX and TX FIFO's of all data for a fresh start.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
void ST7528_1_SPI_ClearFIFO(void) 
{
    uint8 enableInterrupts;

    /* Clear Hardware RX FIFO */
    while(0u !=(ST7528_1_SPI_RX_STATUS_REG & ST7528_1_SPI_STS_RX_FIFO_NOT_EMPTY))
    {
        (void) CY_GET_REG8(ST7528_1_SPI_RXDATA_PTR);
    }

    enableInterrupts = CyEnterCriticalSection();
    /* Clear TX FIFO */
    ST7528_1_SPI_AUX_CONTROL_DP0_REG |= ((uint8)  ST7528_1_SPI_TX_FIFO_CLR);
    ST7528_1_SPI_AUX_CONTROL_DP0_REG &= ((uint8) ~ST7528_1_SPI_TX_FIFO_CLR);

    #if(ST7528_1_SPI_USE_SECOND_DATAPATH)
        /* Clear TX FIFO for 2nd Datapath */
        ST7528_1_SPI_AUX_CONTROL_DP1_REG |= ((uint8)  ST7528_1_SPI_TX_FIFO_CLR);
        ST7528_1_SPI_AUX_CONTROL_DP1_REG &= ((uint8) ~ST7528_1_SPI_TX_FIFO_CLR);
    #endif /* (ST7528_1_SPI_USE_SECOND_DATAPATH) */
    CyExitCriticalSection(enableInterrupts);
}


/* Following functions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects.
*/


/*******************************************************************************
* Function Name: ST7528_1_SPI_EnableInt
********************************************************************************
*
* Summary:
*  Enable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void ST7528_1_SPI_EnableInt(void) 
{
    ST7528_1_SPI_EnableRxInt();
    ST7528_1_SPI_EnableTxInt();
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_DisableInt
********************************************************************************
*
* Summary:
*  Disable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void ST7528_1_SPI_DisableInt(void) 
{
    ST7528_1_SPI_DisableTxInt();
    ST7528_1_SPI_DisableRxInt();
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_SetInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void ST7528_1_SPI_SetInterruptMode(uint8 intSrc) 
{
    ST7528_1_SPI_TX_STATUS_MASK_REG  = (intSrc & ((uint8) ~ST7528_1_SPI_STS_SPI_IDLE));
    ST7528_1_SPI_RX_STATUS_MASK_REG  =  intSrc;
}


/*******************************************************************************
* Function Name: ST7528_1_SPI_ReadStatus
********************************************************************************
*
* Summary:
*  Read the status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the status register.
*
* Global variables:
*  ST7528_1_SPI_swStatus - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the status register for error detection
*  and flow control.
*
* Side Effects:
*  Clear status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 ST7528_1_SPI_ReadStatus(void) 
{
    uint8 tmpStatus;

    #if(ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED || ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED)

        ST7528_1_SPI_DisableInt();

        tmpStatus  = ST7528_1_SPI_GET_STATUS_RX(ST7528_1_SPI_swStatusRx);
        tmpStatus |= ST7528_1_SPI_GET_STATUS_TX(ST7528_1_SPI_swStatusTx);
        tmpStatus &= ((uint8) ~ST7528_1_SPI_STS_SPI_IDLE);

        ST7528_1_SPI_swStatusTx = 0u;
        ST7528_1_SPI_swStatusRx = 0u;

        ST7528_1_SPI_EnableInt();

    #else

        tmpStatus  = ST7528_1_SPI_RX_STATUS_REG;
        tmpStatus |= ST7528_1_SPI_TX_STATUS_REG;
        tmpStatus &= ((uint8) ~ST7528_1_SPI_STS_SPI_IDLE);

    #endif /* (ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED || ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/* [] END OF FILE */
