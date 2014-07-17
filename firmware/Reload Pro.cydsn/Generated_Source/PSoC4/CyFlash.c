/*******************************************************************************
* File Name: CyFlash.c
* Version 4.10
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
* Copyright 2010-2014, Cypress Semiconductor Corporation.  All rights reserved.
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
    #else
        uint32 clkSelectReg;
        uint32 clkImoEna;
        uint32 clkImoFreq;
    #endif

    #if(!CY_PSOC4A)
        clkSelectReg = CY_SYS_CLK_SELECT_REG;
        clkImoEna    = CY_SYS_CLK_IMO_CONFIG_REG & CY_SYS_CLK_IMO_CONFIG_ENABLE;
        clkImoFreq   = CY_SYS_CLK_IMO_MIN_FREQ_MHZ + (CY_SYS_CLK_IMO_SELECT_REG << 2);
    #endif

    if ((rowNum < CY_FLASH_NUMBER_ROWS) && (rowData != 0u))
    {
        /* First load data. Then invoke Write row command. */
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
            /* Wait till CY_FLASH_CPUSS_REQ_START bit goes low */
        }

        /* Check if value is written to SRAM_BASE */
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
                /* Wait till request is completed */
            }
        }

        if(retValue == CYRET_SUCCESS)
        {
            #if(!CY_PSOC4A)
                /* Mask all exceptions to guarantee that IMO configuration will be changed
                * in the atomic way. It will not affect the syscall execution (flash row write)
                * since it is executed in the NMI context.
                */
                interruptState = CyEnterCriticalSection();

                /* The FM-Lite IP (s8fmlt) uses the IMO at 48MHz for the pump clock and SPC timer clock.
                 * The PUMP_SEL and HF clock must be set to IMO before calling Flash write or erase operation.
                 */
                if ((clkImoFreq != 48u) ||
                    ((clkSelectReg & CY_SYS_CLK_SELECT_DIRECT_SEL_MASK) != CY_SYS_CLK_HFCLK_IMO) ||
                    (((clkSelectReg >> CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT) & CY_SYS_CLK_SELECT_PUMP_SEL_MASK) !=
					    CY_SYS_CLK_SELECT_PUMP_SEL_IMO))
                {
                    CySysClkWriteHfclkDiv(CY_SYS_CLK_HFCLK_DIV_4);
                    if (clkImoFreq != 48u)
                    {
                        CySysClkWriteImoFreq(48u);
                    }
                    CySysClkImoStart();
                    CySysClkWriteHfclkDirect(CY_SYS_CLK_HFCLK_IMO);
                    /* Set IMO output as clock source for charge pump clock */
                    CY_SYS_CLK_SELECT_REG &= ((uint32)~(uint32)(CY_SYS_CLK_SELECT_PUMP_SEL_MASK << CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT));
                    CY_SYS_CLK_SELECT_REG |= (uint32)((uint32)1u << CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT);
                }
            #endif

            ptr = &localData[CY_FLASH_SRAM_ROM_KEY1/4u];
            CY_FLASH_CPUSS_SYSARG_REG = (uint32)ptr;

            /* Write row command to SROM */
            localData[CY_FLASH_SRAM_ROM_KEY1/4u] =  (uint32)(rowNum << 16u) |
                                                    (uint32)(CY_FLASH_SROM_KEY2_WRITE << 8u) |
                                                    CY_FLASH_SROM_KEY1;

            #if(CY_PSOC4A)
                /* Mask all the exceptions to guarantee that IMO configuration will be changed
                * in the atomic way. It will not affect the syscall execution (flash row write)
                * since it is executed in the NMI context.
                */
                interruptState = CyEnterCriticalSection();

                /* Preserve IMO configuration that could be changed
                * during syscall execution (Cypress ID #150448).
                */
                imoConfigReg = CY_SYS_CLK_IMO_CONFIG_REG;
            #endif

            /* Perform sysreq for Write row, opcode 0x80000005 */
            CY_FLASH_CPUSS_SYSREQ_REG = CY_FLASH_WRITE_ROW_OPCODE | CY_FLASH_CPUSS_REQ_START;

            while((CY_FLASH_CPUSS_SYSREQ_REG & CY_FLASH_CPUSS_REQ_START) == CY_FLASH_CPUSS_REQ_START)
            {
                /* Wait till CY_FLASH_CPUSS_REQ_START bit goes low */
            }

            #if(CY_PSOC4A)
                /* Restore IMO configuration */
                CY_SYS_CLK_IMO_CONFIG_REG = imoConfigReg;

                CyExitCriticalSection(interruptState);
            #else
                /* Restore clock settings */
                if ((clkImoFreq != 48u) ||
                    ((clkSelectReg & CY_SYS_CLK_SELECT_DIRECT_SEL_MASK) != CY_SYS_CLK_HFCLK_IMO) ||
                    (((clkSelectReg >> CY_SYS_CLK_SELECT_PUMP_SEL_SHIFT) & CY_SYS_CLK_SELECT_PUMP_SEL_MASK) !=
                        CY_SYS_CLK_SELECT_PUMP_SEL_IMO))
                {
                    if (clkImoFreq != 48u)
                    {
                        CySysClkWriteImoFreq(clkImoFreq);
                    }
                    CySysClkWriteHfclkDiv(CY_SYS_CLK_HFCLK_DIV_8);
                    CySysClkWriteHfclkDirect(clkSelectReg & CY_SYS_CLK_SELECT_DIRECT_SEL_MASK);
                    CY_SYS_CLK_SELECT_REG = clkSelectReg;
                    if (0u == clkImoEna)
                    {
                        CySysClkImoStop();
                    }
                }
                CyExitCriticalSection(interruptState);
            #endif

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
    *  coming back from Flash. This function must be called before increasing the
    *  SYSCLK clock frequency. It can optionally be called after lowering SYSCLK
    *  clock frequency in order to improve the CPU performance.
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
