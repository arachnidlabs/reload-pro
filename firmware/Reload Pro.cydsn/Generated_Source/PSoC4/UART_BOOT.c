/*******************************************************************************
* File Name: UART_BOOT.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART.h"

#if(UART_SCB_MODE_I2C_INC)
    #include "UART_I2C.h"
#endif /* (UART_SCB_MODE_I2C_INC) */

#if(UART_SCB_MODE_EZI2C_INC)
    #include "UART_EZI2C.h"
#endif /* (UART_SCB_MODE_EZI2C_INC) */

#if(UART_SCB_MODE_SPI_INC || UART_SCB_MODE_UART_INC)
    #include "UART_SPI_UART.h"
#endif /* (UART_SCB_MODE_SPI_INC || UART_SCB_MODE_UART_INC) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/*******************************************************************************
* Function Name: UART_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_CyBtldrCommStart(void)
{
    #if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_I2CCyBtldrCommStart();
        }
        else if(UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_SpiCyBtldrCommStart();
        }
        else if(UART_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_UartCyBtldrCommStart();
        }
        else if(UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             UART_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(UART_SCB_MODE_I2C_CONST_CFG)
        UART_I2CCyBtldrCommStart();

    #elif(UART_SCB_MODE_SPI_CONST_CFG)
        UART_SpiCyBtldrCommStart();

    #elif(UART_SCB_MODE_UART_CONST_CFG)
        UART_UartCyBtldrCommStart();

    #elif(UART_SCB_MODE_EZI2C_CONST_CFG)
        UART_EzI2CCyBtldrCommStart();

    #else
        /* Do nothing */

    #endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls CyBtldrCommStop function function of the bootloader communication
*  component for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_CyBtldrCommStop(void)
{
    #if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_I2CCyBtldrCommStop();
        }
        else if(UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_SpiCyBtldrCommStop();
        }
        else if(UART_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_UartCyBtldrCommStop();
        }
        else if(UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(UART_SCB_MODE_I2C_CONST_CFG)
        UART_I2CCyBtldrCommStop();

    #elif(UART_SCB_MODE_SPI_CONST_CFG)
        UART_SpiCyBtldrCommStop();

    #elif(UART_SCB_MODE_UART_CONST_CFG)
        UART_UartCyBtldrCommStop();

    #elif(UART_SCB_MODE_EZI2C_CONST_CFG)
        UART_EzI2CCyBtldrCommStop();

    #else
        /* Do nothing */

    #endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_CyBtldrCommReset(void)
{
    #if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_I2CCyBtldrCommReset();
        }
        else if(UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_SpiCyBtldrCommReset();
        }
        else if(UART_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_UartCyBtldrCommReset();
        }
        else if(UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(UART_SCB_MODE_I2C_CONST_CFG)
        UART_I2CCyBtldrCommReset();

    #elif(UART_SCB_MODE_SPI_CONST_CFG)
        UART_SpiCyBtldrCommReset();

    #elif(UART_SCB_MODE_UART_CONST_CFG)
        UART_UartCyBtldrCommReset();

    #elif(UART_SCB_MODE_EZI2C_CONST_CFG)
        UART_EzI2CCyBtldrCommReset();

    #else
        /* Do nothing */

    #endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
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
cystatus UART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = UART_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = UART_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(UART_SCB_MODE_UART_RUNTM_CFG)
        {
            status = UART_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = UART_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(UART_SCB_MODE_I2C_CONST_CFG)
        status = UART_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(UART_SCB_MODE_SPI_CONST_CFG)
        status = UART_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(UART_SCB_MODE_UART_CONST_CFG)
        status = UART_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(UART_SCB_MODE_EZI2C_CONST_CFG)
        status = UART_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: UART_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
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
cystatus UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = UART_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = UART_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(UART_SCB_MODE_UART_RUNTM_CFG)
        {
            status = UART_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = UART_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode */
        }
    #elif(UART_SCB_MODE_I2C_CONST_CFG)
        status = UART_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(UART_SCB_MODE_SPI_CONST_CFG)
        status = UART_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(UART_SCB_MODE_UART_CONST_CFG)
        status = UART_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(UART_SCB_MODE_EZI2C_CONST_CFG)
        status = UART_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode */

    #endif /* (UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


/* [] END OF FILE */
