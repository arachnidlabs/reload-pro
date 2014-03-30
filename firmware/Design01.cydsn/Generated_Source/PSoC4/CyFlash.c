/*******************************************************************************
* File Name: CyFlash.c
* Version 4.0
*
*  Description:
*   Provides an API for the FLASH.
*
*  Note:
*   This code is endian agnostic.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2010-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyFlash.h"


/*******************************************************************************
* Function Name: CySysFlashWriteRow
********************************************************************************
*
* Summary:
*  Writes a row of Flash.
*
* Parameters:
*  uint16 rowNum:
*   Row number. Each row is 128 bytes so a 32KB flash memory will have a valid
*   range of [0-255].
*
*  uint8* rowData:
*   Array of bytes to write.
*
* Return:
*  Status
*     Value             Description
*    CYRET_SUCCESS     Successful
*    CYRET_LOCKED      Flash writing already in use
*    CYRET_CANCELED    Command not accepted
*    CYRET_BAD_PARAM   One or more invalid parameters
*    Other non-zero    Failure
*
*******************************************************************************/
cystatus CySysFlashWriteRow(uint32 rowNum, const uint8 rowData[])
{
    volatile cystatus retValue = CYRET_SUCCESS;
    volatile uint32   *ptr;
    volatile uint32   cpuValue;
    volatile uint32   localData[(CY_FLASH_SIZEOF_ROW + CY_FLASH_SRAM_ROM_DATA)/4u];
    uint8  interruptState;

    #if(CY_PSOC4A)
        volatile uint32   imoConfigReg;
    #endif

    if ((rowNum < CY_FLASH_NUMBER_ROWS) && (rowData != 0u))
    {
        /* First load the data. Then invoke Write row command. */
        ptr = &localData[CY_FLASH_SRAM_ROM_KEY1];

        CY_FLASH_CPUSS_SYSARG_REG = (uint32)ptr;

        #if(CY_FLASH_NUMBER_ROWS > 255u)
            localData[CY_FLASH_SRAM_ROM_KEY1] = CY_FLASH_SROM_LOAD_CMD | (uint32)((rowNum & 0x100u) << 16u);
        #else
            localData[CY_FLASH_SRAM_ROM_KEY1] = CY_FLASH_SROM_LOAD_CMD;
        #endif /* (CY_FLASH_SIZEOF_ROW > 255) */

        localData[CY_FLASH_SRAM_ROM_PARAM2/4u] = ((uint32)(CYDEV_FLS_ROW_SIZE - 1u));

        /* Copy row data from 8bit to 32bit array with shift for CPUSS commands */
        (void)memcpy((void *)&localData[CY_FLASH_SRAM_ROM_DATA/4u], rowData, CYDEV_FLS_ROW_SIZE);

        /* Perform sysreq load data, opcode 0x80000004h */
        CY_FLASH_CPUSS_SYSREQ_REG = CY_FLASH_LOAD_BYTE_OPCODE | CY_FLASH_CPUSS_REQ_START;

        while((CY_FLASH_CPUSS_SYSREQ_REG & CY_FLASH_CPUSS_REQ_START) == CY_FLASH_CPUSS_REQ_START)
        {
            /* Wait till the CY_FLASH_CPUSS_REQ_START bit goes low */
        }

        /* Check if the value is written to the SRAM_BASE */
        cpuValue = CY_FLASH_CPUSS_SYSARG_REG;
        if (cpuValue == CY_FLASH_SROM_CMD_RETURN_SUCC)
        {
            retValue = CYRET_SUCCESS;
        }
        else if((cpuValue & CY_FLASH_SROM_CMD_RETURN_MASK) == CY_FLASH_SROM_CMD_RETURN_MASK)
        {
            /* Error value, cant proceed */
            retValue = CYRET_CANCELED;
        }
        else
        {
            while((CY_FLASH_CPUSS_SYSARG_REG & CY_FLASH_SROM_CMD_RETURN_MASK) != CY_FLASH_SROM_CMD_RETURN_SUCC)
            {
                /* Wait till the request is completed */
            }
        }

        if(retValue == CYRET_SUCCESS)
        {
            ptr = &localData[CY_FLASH_SRAM_ROM_KEY1/4u];
            CY_FLASH_CPUSS_SYSARG_REG = (uint32)ptr;

            /* Write row command to SROM */
            localData[CY_FLASH_SRAM_ROM_KEY1/4u] =  (uint32)(rowNum << 16u) |
                                                    (uint32)(CY_FLASH_SROM_KEY2_WRITE << 8u) |
                                                    CY_FLASH_SROM_KEY1;

            /* Mask all exceptions to guarantee that IMO configuration will be changed
            * in the atomic way. It will not affect syscall execution (flash row write)
            * since it is executed in the NMI context.
            */
            interruptState = CyEnterCriticalSection();

            #if(CY_PSOC4A)
                /* Preserve IMO configuration that could be changed
                * during syscall execution (Cypress ID #150448).
                */
                imoConfigReg = CY_SYS_CLK_IMO_CONFIG_REG;
            #endif

            /* Perform sysreq for Write row, opcode 0x80000005 */
            CY_FLASH_CPUSS_SYSREQ_REG = CY_FLASH_WRITE_ROW_OPCODE | CY_FLASH_CPUSS_REQ_START;

            while((CY_FLASH_CPUSS_SYSREQ_REG & CY_FLASH_CPUSS_REQ_START) == CY_FLASH_CPUSS_REQ_START)
            {
                /* Wait till the CY_FLASH_CPUSS_REQ_START bit goes low */
            }

            #if(CY_PSOC4A)
                /* Restore IMO configuration */
                CY_SYS_CLK_IMO_CONFIG_REG = imoConfigReg;
            #endif

            CyExitCriticalSection(interruptState);

            cpuValue = CY_FLASH_CPUSS_SYSARG_REG;
            if (cpuValue != CY_FLASH_SROM_CMD_RETURN_SUCC)
            {
                retValue = cpuValue;
            }
        }
    }
    else
    {
        retValue = CYRET_BAD_PARAM;
    }

    return (retValue);
}

#if(CY_PSOC4A)

    /*******************************************************************************
    * Function Name: CySysFlashSetWaitCycles
    ********************************************************************************
    *
    * Summary:
    *  Sets the number of clock cycles the cache will wait before it samples data
    *  coming back from Flash. This function must be called before increasing SYSCLK
    *  clock frequency. It can optionally be called after lowering SYSCLK clock
    *  frequency in order to improve CPU performance.
    *
    * Parameters:
    *  freq: Valid range [3-48].  Frequency for operation of the IMO.
    *  Note: Invalid frequency will be ignored.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysFlashSetWaitCycles(uint32 freq)
    {
        if ((freq >= CY_SYS_CLK_IMO_MIN_FREQ_MHZ) && (freq <= CY_SYS_CLK_IMO_MAX_FREQ_MHZ))
        {
            if ( freq <= CY_FLASH_SYSCLK_BOUNDARY_MHZ )
            {
                CY_SYS_CLK_SELECT_REG &= (uint32)(~CY_FLASH_WAIT_STATE_EN);
            }
            else
            {
                CY_SYS_CLK_SELECT_REG |= CY_FLASH_WAIT_STATE_EN;
            }
        }
        else
        {
            /* Halt CPU in debug mode if frequency is invalid */
            CYASSERT(0u != 0u);
        }
    }

#endif

/* [] END OF FILE */
