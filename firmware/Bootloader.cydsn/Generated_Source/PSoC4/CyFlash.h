/*******************************************************************************
* File Name: CyFlash.h
* Version 4.0
*
*  Description:
*   Provides the function definitions for the FLASH.
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

#if !defined(CY_BOOT_CYFLASH_H)
#define CY_BOOT_CYFLASH_H

#include "CyLib.h"


/*******************************************************************************
*     Function Prototypes
*******************************************************************************/
cystatus CySysFlashWriteRow             (uint32 rowNum, const uint8 rowData[]);
void     CySysFlashSetWaitCycles        (uint32 freq);


/*******************************************************************************
*     Flash defines
*******************************************************************************/
#define CY_FLASH_SRAM_ROM_KEY1          (( uint32 )0x00u)                  /* SROM Key1 address                       */
#define CY_FLASH_SRAM_ROM_PARAM2        (CY_FLASH_SRAM_ROM_KEY1 + 0x04u)   /* SROM parameter 2 address                */
#define CY_FLASH_SRAM_ROM_DATA          (CY_FLASH_SRAM_ROM_KEY1 + 0x08u)   /* SROM data address                       */

#define CY_FLASH_SROM_CMD_RETURN_MASK   (0xF0000000u)                      /* SROM command return value mask          */
#define CY_FLASH_SROM_CMD_RETURN_SUCC   (0xA0000000u)                      /* SROM command success                    */
#define CY_FLASH_SROM_KEY1              (( uint32 )0xB6u)                  /* SROM key for FLASH command              */
#define CY_FLASH_SROM_KEY2_LOAD         (( uint32 )0xD7u)                  /* SROM key for FLASH load command         */
#define CY_FLASH_SROM_KEY2_WRITE        (( uint32 )0xD8u)                  /* SROM key for FLASH write command        */
#define CY_FLASH_SROM_LOAD_CMD          ((CY_FLASH_SROM_KEY2_LOAD << 8u) | CY_FLASH_SROM_KEY1)
                                                                           /* SROM key for FLASH commands             */
#define CY_FLASH_LOAD_BYTE_OPCODE       (( uint32 )0x04u)                  /* Load byte SROM opcode                   */
#define CY_FLASH_WRITE_ROW_OPCODE       (( uint32 )0x05u)                  /* Row write SROM opcode                   */
#define CY_FLASH_CPUSS_REQ_START        (( uint32 )(( uint32 )0x1u << 31u))/* Request CPU to execute the special code */

#define CY_FLASH_NUMBER_ROWS            (CYDEV_FLASH_SIZE / CYDEV_FLS_ROW_SIZE)
#define CY_FLASH_BASE                   (CYDEV_FLASH_BASE)
#define CY_FLASH_SIZE                   (CYDEV_FLASH_SIZE)
#define CY_FLASH_SIZEOF_ARRAY           (CYDEV_FLS_SECTOR_SIZE)
#define CY_FLASH_SIZEOF_ROW             (CYDEV_FLS_ROW_SIZE)
#define CY_FLASH_NUMBER_ROWS            (CYDEV_FLASH_SIZE / CYDEV_FLS_ROW_SIZE)
#define CY_FLASH_NUMBER_ARRAYS          (CYDEV_FLASH_SIZE / CYDEV_FLS_SECTOR_SIZE)

#define CY_FLASH_CPUSS_SYSARG_REG       (*(reg32 *) CYREG_CPUSS_SYSARG)
#define CY_FLASH_CPUSS_SYSARG_PTR       ( (reg32 *) CYREG_CPUSS_SYSARG)

#define CY_FLASH_CPUSS_SYSREQ_REG       (*(reg32 *) CYREG_CPUSS_SYSREQ)
#define CY_FLASH_CPUSS_SYSREQ_PTR       ( (reg32 *) CYREG_CPUSS_SYSREQ)


/* CySysFlashSetWaitCycles() - implementation definitions */
#define CY_FLASH_WAIT_STATE_EN          (( uint32 )(( uint32 )0x01u << 18u))
#define CY_FLASH_SYSCLK_BOUNDARY_MHZ    (24u)

#endif  /* (CY_BOOT_CYFLASH_H) */


/* [] END OF FILE */
