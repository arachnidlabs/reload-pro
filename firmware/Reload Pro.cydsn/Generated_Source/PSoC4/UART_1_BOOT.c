/*******************************************************************************
* File Name: UART_1_BOOT.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_1.h"

#if(UART_1_SCB_MODE_I2C_INC)
    #include "UART_1_I2C.h"
#endif /* (UART_1_SCB_MODE_I2C_INC) */

#if(UART_1_SCB_MODE_EZI2C_INC)
    #include "UART_1_EZI2C.h"
#endif /* (UART_1_SCB_MODE_EZI2C_INC) */

#if(UART_1_SCB_MODE_SPI_INC || UART_1_SCB_MODE_UART_INC)
    #include "UART_1_SPI_UART.h"
#endif /* (UART_1_SCB_MODE_SPI_INC || UART_1_SCB_MODE_UART_INC) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_1) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/*******************************************************************************
* Function Name: UART_1_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls Start function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_1_CyBtldrCommStart(void)
{
    #if(UART_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(UART_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_1_I2CCyBtldrCommStart();
        }
        else if(UART_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_1_SpiCyBtldrCommStart();
        }
        else if(UART_1_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_1_UartCyBtldrCommStart();
        }
        else if(UART_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             UART_1_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(UART_1_SCB_MODE_I2C_CONST_CFG)
        UART_1_I2CCyBtldrCommStart();

    #elif(UART_1_SCB_MODE_SPI_CONST_CFG)
        UART_1_SpiCyBtldrCommStart();

    #elif(UART_1_SCB_MODE_UART_CONST_CFG)
        UART_1_UartCyBtldrCommStart();

    #elif(UART_1_SCB_MODE_EZI2C_CONST_CFG)
        UART_1_EzI2CCyBtldrCommStart();

    #else
        /* Do nothing */

    #endif /* (UART_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_1_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls Stop function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_1_CyBtldrCommStop(void)
{
    #if(UART_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(UART_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_1_I2CCyBtldrCommStop();
        }
        else if(UART_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_1_SpiCyBtldrCommStop();
        }
        else if(UART_1_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_1_UartCyBtldrCommStop();
        }
        else if(UART_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_1_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(UART_1_SCB_MODE_I2C_CONST_CFG)
        UART_1_I2CCyBtldrCommStop();

    #elif(UART_1_SCB_MODE_SPI_CONST_CFG)
        UART_1_SpiCyBtldrCommStop();

    #elif(UART_1_SCB_MODE_UART_CONST_CFG)
        UART_1_UartCyBtldrCommStop();

    #elif(UART_1_SCB_MODE_EZI2C_CONST_CFG)
        UART_1_EzI2CCyBtldrCommStop();

    #else
        /* Do nothing */

    #endif /* (UART_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_1_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls reset function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_1_CyBtldrCommReset(void)
{
    #if(UART_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(UART_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_1_I2CCyBtldrCommReset();
        }
        else if(UART_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_1_SpiCyBtldrCommReset();
        }
        else if(UART_1_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_1_UartCyBtldrCommReset();
        }
        else if(UART_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_1_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(UART_1_SCB_MODE_I2C_CONST_CFG)
        UART_1_I2CCyBtldrCommReset();

    #elif(UART_1_SCB_MODE_SPI_CONST_CFG)
        UART_1_SpiCyBtldrCommReset();

    #elif(UART_1_SCB_MODE_UART_CONST_CFG)
        UART_1_UartCyBtldrCommReset();

    #elif(UART_1_SCB_MODE_EZI2C_CONST_CFG)
        UART_1_EzI2CCyBtldrCommReset();

    #else
        /* Do nothing */

    #endif /* (UART_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_1_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls read fucntion of the bootloader communication component for selected
*  mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus UART_1_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(UART_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(UART_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = UART_1_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(UART_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = UART_1_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(UART_1_SCB_MODE_UART_RUNTM_CFG)
        {
            status = UART_1_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(UART_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = UART_1_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(UART_1_SCB_MODE_I2C_CONST_CFG)
        status = UART_1_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(UART_1_SCB_MODE_SPI_CONST_CFG)
        status = UART_1_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(UART_1_SCB_MODE_UART_CONST_CFG)
        status = UART_1_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(UART_1_SCB_MODE_EZI2C_CONST_CFG)
        status = UART_1_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (UART_1_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: UART_1_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls write fucntion of the bootloader communication component for selected
*  mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus UART_1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(UART_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(UART_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = UART_1_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(UART_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = UART_1_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(UART_1_SCB_MODE_UART_RUNTM_CFG)
        {
            status = UART_1_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(UART_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = UART_1_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }
    #elif(UART_1_SCB_MODE_I2C_CONST_CFG)
        status = UART_1_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(UART_1_SCB_MODE_SPI_CONST_CFG)
        status = UART_1_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(UART_1_SCB_MODE_UART_CONST_CFG)
        status = UART_1_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(UART_1_SCB_MODE_EZI2C_CONST_CFG)
        status = UART_1_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (UART_1_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_1) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


/* [] END OF FILE */
