/*******************************************************************************
* File Name: Bootloader.h
* Version 1.20
*
*  Description:
*   Provides an API for the Bootloader. The API includes functions for starting
*   boot loading operations, validating the application and jumping to the
*   application.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BOOTLOADER_Bootloader_H)
#define CY_BOOTLOADER_Bootloader_H

#include "cytypes.h"


/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Bootloader_v1_20 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5X) */


#define Bootloader_DUAL_APP_BOOTLOADER        (0u)
#define Bootloader_BOOTLOADER_APP_VERSION     (0u)
#define Bootloader_FAST_APP_VALIDATION        (0u)
#define Bootloader_PACKET_CHECKSUM_CRC        (0u)
#define Bootloader_WAIT_FOR_COMMAND           (0u)
#define Bootloader_WAIT_FOR_COMMAND_TIME      (0u)
#define Bootloader_BOOTLOADER_APP_VALIDATION  (1u)

#define Bootloader_CMD_GET_FLASH_SIZE_AVAIL   (1u)
#define Bootloader_CMD_ERASE_ROW_AVAIL        (1u)
#define Bootloader_CMD_VERIFY_ROW_AVAIL       (1u)
#define Bootloader_CMD_SYNC_BOOTLOADER_AVAIL  (1u)
#define Bootloader_CMD_SEND_DATA_AVAIL        (1u)
#define Bootloader_CMD_GET_METADATA           (0u)

#if(0u != Bootloader_DUAL_APP_BOOTLOADER)
    #define Bootloader_CMD_GET_APP_STATUS_AVAIL   (1u)
#endif  /* (0u != Bootloader_DUAL_APP_BOOTLOADER) */


/*******************************************************************************
* Bootloadable applications identification
*******************************************************************************/
#define Bootloader_MD_BTLDB_ACTIVE_0          (0x00u)
#if(0u != Bootloader_DUAL_APP_BOOTLOADER)
    #define Bootloader_MD_BTLDB_ACTIVE_1      (0x01u)
    #define Bootloader_MD_BTLDB_ACTIVE_NONE   (0x02u)
#endif  /* (0u != Bootloader_DUAL_APP_BOOTLOADER) */


/* Mask used to indicate starting application */
#define Bootloader_SCHEDULE_BTLDB             (0x80u)
#define Bootloader_SCHEDULE_BTLDR             (0x40u)
#define Bootloader_SCHEDULE_MASK              (0xC0u)


#if defined(__ARMCC_VERSION) || defined (__GNUC__)
    __attribute__((section (".bootloader")))
#elif defined (__ICCARM__)
    #pragma location=".bootloader"
#endif  /* defined(__ARMCC_VERSION) || defined (__GNUC__) */
extern const uint8  CYCODE Bootloader_Checksum;
extern const uint8  CYCODE  *Bootloader_ChecksumAccess;


#if defined(__ARMCC_VERSION) || defined (__GNUC__)
    __attribute__((section (".bootloader")))
#elif defined (__ICCARM__)
    #pragma location=".bootloader"
#endif  /* defined(__ARMCC_VERSION) || defined (__GNUC__) */
extern const uint32 CYCODE Bootloader_SizeBytes;
extern const uint32 CYCODE *Bootloader_SizeBytesAccess;


/*******************************************************************************
* This variable is used by Bootloader/Bootloadable components to schedule what
* application will be started after software reset.
*******************************************************************************/
#if (CY_PSOC4)
    #if defined(__ARMCC_VERSION)
        __attribute__ ((section(".bootloaderruntype"), zero_init))
    #elif defined (__GNUC__)
        __attribute__ ((section(".bootloaderruntype")))
   #elif defined (__ICCARM__)
        #pragma location=".bootloaderruntype"
    #endif  /* defined(__ARMCC_VERSION) */
    extern volatile uint32 cyBtldrRunType;
#endif  /* (CY_PSOC4) */


#if(0u != Bootloader_DUAL_APP_BOOTLOADER)
    extern uint8 Bootloader_activeApp;
#endif  /* (0u != Bootloader_DUAL_APP_BOOTLOADER) */


#if(CY_PSOC4)
    /* Reset Cause Observation Register */
    #define Bootloader_RES_CAUSE_REG           (* (reg32 *) CYREG_RES_CAUSE)
    #define Bootloader_RES_CAUSE_PTR           (  (reg32 *) CYREG_RES_CAUSE)
#else
    #define Bootloader_RESET_SR0_REG           (* (reg8 *) CYREG_RESET_SR0)
    #define Bootloader_RESET_SR0_PTR           (  (reg8 *) CYREG_RESET_SR0)
#endif /* (CY_PSOC4) */


/*******************************************************************************
* Get the reason of the device reset
*  Return cyBtldrRunType in case if software reset was reset reason and
*  set cyBtldrRunType to zero (bootloader application is scheduled - that is
*  initial clean state) and return zero.
*******************************************************************************/
#if(CY_PSOC4)
    #define Bootloader_GET_RUN_TYPE           (cyBtldrRunType)
#else
    #define Bootloader_GET_RUN_TYPE       (Bootloader_RESET_SR0_REG & Bootloader_SCHEDULE_MASK)
#endif  /* (CY_PSOC4) */


/*******************************************************************************
* Schedule Bootloader/Bootloadable to be run after software reset
*******************************************************************************/
#if(CY_PSOC4)
    #define Bootloader_SET_RUN_TYPE(x)                (cyBtldrRunType = (x))
#else
    #define Bootloader_SET_RUN_TYPE(x)                (Bootloader_RESET_SR0_REG = (x))
#endif  /* (CY_PSOC4) */


/* Returns the number of Flash arrays availalbe in the device */
#define Bootloader_NUM_OF_FLASH_ARRAYS    (CYDEV_FLASH_SIZE / CYDEV_FLS_SECTOR_SIZE)


/*******************************************************************************
* External References
*******************************************************************************/
void Bootloader_SetFlashByte(uint32 address, uint8 runType);
void CyBtldr_CheckLaunch(void)  CYSMALL ;
void Bootloader_Start(void) CYSMALL ;

#if(CY_PSOC3)
    /* Implementation for the PSoC 3 resides in a Bootloader_psoc3.a51 file.  */
    extern void     Bootloader_LaunchBootloadable(uint32 appAddr);
#endif  /* (CY_PSOC3) */

/* If using custom interface as the IO Component, user must provide these functions */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)

    extern void CyBtldrCommStart(void);
    extern void CyBtldrCommStop (void);
    extern void CyBtldrCommReset(void);
    extern cystatus CyBtldrCommWrite(uint8* buffer, uint16 size, uint16* count, uint8 timeOut);
    extern cystatus CyBtldrCommRead (uint8* buffer, uint16 size, uint16* count, uint8 timeOut);

#endif  /* defined(CYDEV_BOOTLOADER_IO_COMP) && (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface) */


/*******************************************************************************
* Kept for backward compatibility.
*******************************************************************************/
#if(0u != Bootloader_DUAL_APP_BOOTLOADER)
    #define Bootloader_ValidateApp(x)                 Bootloader_ValidateBootloadable((x))
    #define Bootloader_ValidateApplication            \
                            Bootloader_ValidateBootloadable(Bootloader_MD_BTLDB_ACTIVE_0)
#else
    #define Bootloader_ValidateApplication            \
                            Bootloader_ValidateBootloadable(Bootloader_MD_BTLDB_ACTIVE_0)
    #define Bootloader_ValidateApp(x)                 Bootloader_ValidateBootloadable((x))
#endif  /* (0u != Bootloader_DUAL_APP_BOOTLOADER) */


/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from version 1.10
*******************************************************************************/
#define Bootloader_BOOTLOADABLE_APP_VALID     (Bootloader_BOOTLOADER_APP_VALIDATION)
#define CyBtldr_Start                               Bootloader_Start


/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from version 1.20
*******************************************************************************/
#define Bootloader_META_BASE(x)                   (CYDEV_FLASH_BASE + \
                                                            (CYDEV_FLASH_SIZE - (( uint32 )(x) * CYDEV_FLS_ROW_SIZE) - \
                                                            Bootloader_META_DATA_SIZE))
#define Bootloader_META_ARRAY                     (Bootloader_NUM_OF_FLASH_ARRAYS - 1u)
#define Bootloader_META_APP_ENTRY_POINT_ADDR(x)   (Bootloader_META_BASE(x) + \
                                                            Bootloader_META_APP_ADDR_OFFSET)
#define Bootloader_META_APP_BYTE_LEN(x)           (Bootloader_META_BASE(x) + \
                                                            Bootloader_META_APP_BYTE_LEN_OFFSET)
#define Bootloader_META_APP_RUN_ADDR(x)           (Bootloader_META_BASE(x) + \
                                                            Bootloader_META_APP_RUN_TYPE_OFFSET)
#define Bootloader_META_APP_ACTIVE_ADDR(x)        (Bootloader_META_BASE(x) + \
                                                            Bootloader_META_APP_ACTIVE_OFFSET)
#define Bootloader_META_APP_VERIFIED_ADDR(x)      (Bootloader_META_BASE(x) + \
                                                            Bootloader_META_APP_VERIFIED_OFFSET)
#define Bootloader_META_APP_BLDBL_VER_ADDR(x)     (Bootloader_META_BASE(x) + \
                                                            Bootloader_META_APP_BL_BUILD_VER_OFFSET)
#define Bootloader_META_APP_VER_ADDR(x)           (Bootloader_META_BASE(x) + \
                                                            Bootloader_META_APP_VER_OFFSET)
#define Bootloader_META_APP_ID_ADDR(x)            (Bootloader_META_BASE(x) + \
                                                            Bootloader_META_APP_ID_OFFSET)
#define Bootloader_META_APP_CUST_ID_ADDR(x)       (Bootloader_META_BASE(x) + \
                                                            Bootloader_META_APP_CUST_ID_OFFSET)
#define Bootloader_META_LAST_BLDR_ROW_ADDR(x)     (Bootloader_META_BASE(x) + \
                                                            Bootloader_META_APP_BL_LAST_ROW_OFFSET)
#define Bootloader_META_CHECKSUM_ADDR(x)          (Bootloader_META_BASE(x) + \
                                                            Bootloader_META_APP_CHECKSUM_OFFSET)
#if(0u == Bootloader_DUAL_APP_BOOTLOADER)
    #define Bootloader_MD_BASE                    Bootloader_META_BASE(0u)
    #define Bootloader_MD_ROW                     ((CY_FLASH_NUMBER_ROWS / Bootloader_NUM_OF_FLASH_ARRAYS) \
                                                           - 1u)
    #define Bootloader_MD_CHECKSUM_ADDR           Bootloader_META_CHECKSUM_ADDR(0u)
    #define Bootloader_MD_LAST_BLDR_ROW_ADDR      Bootloader_META_LAST_BLDR_ROW_ADDR(0u)
    #define Bootloader_MD_APP_BYTE_LEN            Bootloader_META_APP_BYTE_LEN(0u)
    #define Bootloader_MD_APP_VERIFIED_ADDR       Bootloader_META_APP_VERIFIED_ADDR(0u)
    #define Bootloader_MD_APP_ENTRY_POINT_ADDR    Bootloader_META_APP_ENTRY_POINT_ADDR(0u)
    #define Bootloader_MD_APP_RUN_ADDR            Bootloader_META_APP_RUN_ADDR(0u)
#else
    #define Bootloader_MD_ROW(x)                  ((CY_FLASH_NUMBER_ROWS / Bootloader_NUM_OF_FLASH_ARRAYS) \
                                                            - 1u - ( uint32 )(x))
    #define Bootloader_MD_CHECKSUM_ADDR           Bootloader_META_CHECKSUM_ADDR(appId)
    #define Bootloader_MD_LAST_BLDR_ROW_ADDR      Bootloader_META_LAST_BLDR_ROW_ADDR(appId)
    #define Bootloader_MD_APP_BYTE_LEN            Bootloader_META_APP_BYTE_LEN(appId)
    #define Bootloader_MD_APP_VERIFIED_ADDR       Bootloader_META_APP_VERIFIED_ADDR(appId)
    #define Bootloader_MD_APP_ENTRY_POINT_ADDR    \
                                                Bootloader_META_APP_ENTRY_POINT_ADDR(Bootloader_activeApp)
    #define Bootloader_MD_APP_RUN_ADDR            Bootloader_META_APP_RUN_ADDR(Bootloader_activeApp)
#endif  /* (0u == Bootloader_DUAL_APP_BOOTLOADER) */

#define Bootloader_P_APP_ACTIVE(x)                ((uint8 CYCODE *) Bootloader_META_APP_ACTIVE_ADDR(x))
#define Bootloader_MD_PTR_CHECKSUM                ((uint8  CYCODE *) Bootloader_MD_CHECKSUM_ADDR)
#define Bootloader_MD_PTR_APP_ENTRY_POINT         ((Bootloader_APP_ADDRESS CYCODE *) \
                                                                Bootloader_MD_APP_ENTRY_POINT_ADDR)
#define Bootloader_MD_PTR_LAST_BLDR_ROW            ((uint16 CYCODE *) Bootloader_MD_LAST_BLDR_ROW_ADDR)
#define Bootloader_MD_PTR_APP_BYTE_LEN             ((Bootloader_APP_ADDRESS CYCODE *) \
                                                                Bootloader_MD_APP_BYTE_LEN)
#define Bootloader_MD_PTR_APP_RUN_ADDR             ((uint8  CYCODE *) Bootloader_MD_APP_RUN_ADDR)
#define Bootloader_MD_PTR_APP_VERIFIED             ((uint8  CYCODE *) Bootloader_MD_APP_VERIFIED_ADDR)
#define Bootloader_MD_PTR_APP_BLD_BL_VER           ((uint16 CYCODE *) Bootloader_MD_APP_BLDBL_VER_ADDR)
#define Bootloader_MD_PTR_APP_VER                  ((uint16 CYCODE *) Bootloader_MD_APP_VER_ADDR)
#define Bootloader_MD_PTR_APP_ID                   ((uint16 CYCODE *) Bootloader_MD_APP_ID_ADDR)
#define Bootloader_MD_PTR_APP_CUST_ID              ((uint32 CYCODE *) Bootloader_MD_APP_CUST_ID_ADDR)
#if(CY_PSOC3)
    #define Bootloader_APP_ADDRESS                    uint16
    #define Bootloader_GET_CODE_DATA(idx)             (*((uint8  CYCODE *) (idx)))
    #define Bootloader_GET_CODE_WORD(idx)             (*((uint32 CYCODE *) (idx)))
    #define Bootloader_META_APP_ADDR_OFFSET           (3u)
    #define Bootloader_META_APP_BL_LAST_ROW_OFFSET    (7u)
    #define Bootloader_META_APP_BYTE_LEN_OFFSET       (11u)
    #define Bootloader_META_APP_RUN_TYPE_OFFSET       (15u)
#else
    #define Bootloader_APP_ADDRESS                    uint32
    #define Bootloader_GET_CODE_DATA(idx)             (*((uint8  *)(CYDEV_FLASH_BASE + (idx))))
    #define Bootloader_GET_CODE_WORD(idx)             (*((uint32 *)(CYDEV_FLASH_BASE + (idx))))
    #define Bootloader_META_APP_ADDR_OFFSET           (1u)
    #define Bootloader_META_APP_BL_LAST_ROW_OFFSET    (5u)
    #define Bootloader_META_APP_BYTE_LEN_OFFSET       (9u)
    #define Bootloader_META_APP_RUN_TYPE_OFFSET       (13u)
#endif /* (CY_PSOC3) */
#define Bootloader_META_APP_ACTIVE_OFFSET             (16u)
#define Bootloader_META_APP_VERIFIED_OFFSET           (17u)
#define Bootloader_META_APP_BL_BUILD_VER_OFFSET       (18u)
#define Bootloader_META_APP_ID_OFFSET                 (20u)
#define Bootloader_META_APP_VER_OFFSET                (22u)
#define Bootloader_META_APP_CUST_ID_OFFSET            (24u)
#if (CY_PSOC4)
    #define Bootloader_GET_REG16(x)   ((uint16)(                                                          \
                                                (( uint16 )(( uint16 )CY_GET_XTND_REG8((x)     )       ))   |   \
                                                (( uint16 )(( uint16 )CY_GET_XTND_REG8((x) + 1u) <<  8u))       \
                                            ))

    #define Bootloader_GET_REG32(x)   (                                                                    \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x)     )       ))   |   \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x) + 1u) <<  8u))   |   \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x) + 2u) << 16u))   |   \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x) + 3u) << 24u))       \
                                            )
#endif  /* (CY_PSOC4) */
#define Bootloader_META_APP_CHECKSUM_OFFSET           (0u)
#define Bootloader_META_DATA_SIZE                     (64u)
#if(CY_PSOC4)
    extern uint8 appRunType;
#endif  /* (CY_PSOC4) */

#if(CY_PSOC4)
    #define Bootloader_SOFTWARE_RESET                 CY_SET_REG32(CYREG_CM0_AIRCR, 0x05FA0004u)
#else
    #define Bootloader_SOFTWARE_RESET                 CY_SET_REG8(CYREG_RESET_CR2, 0x01u)
#endif  /* (CY_PSOC4) */

#define Bootloader_SetFlashRunType(runType)        Bootloader_SetFlashByte( \
                                                            Bootloader_MD_APP_RUN_ADDR(0), (runType))

#define Bootloader_START_APP                  (Bootloader_SCHEDULE_BTLDB)
#define Bootloader_START_BTLDR                (Bootloader_SCHEDULE_BTLDR)

/* Some PSoC Creator versions used to generate only one name types */
#if !defined (CYDEV_FLASH_BASE)
    #define CYDEV_FLASH_BASE                                (CYDEV_FLS_BASE)
#endif /* !defined (CYDEV_FLASH_BASE) */

#if !defined (CYDEV_FLASH_SIZE)
    #define CYDEV_FLASH_SIZE                                (CYDEV_FLS_SIZE)
#endif /* CYDEV_FLASH_SIZE */


#endif /* CY_BOOTLOADER_Bootloader_H */


/* [] END OF FILE */
