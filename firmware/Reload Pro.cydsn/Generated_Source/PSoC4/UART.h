/*******************************************************************************
* File Name: UART.h
* Version 1.20
*
* Description:
*  This file provides constants and parameter values for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2013-2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_UART_H)
#define CY_SCB_UART_H

#include <cydevice_trm.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <CyLib.h>


/***************************************
*  Conditional Compilation Parameters
****************************************/

#define UART_CY_SCBIP_V0 (CYIPBLOCK_m0s8scb_VERSION == 0u)
#define UART_CY_SCBIP_V1 (CYIPBLOCK_m0s8scb_VERSION >= 1u)

#if(UART_CY_SCBIP_V1)
    #define UART_CY_SCBIP_V1_I2C_ONLY   (1u) /* SCB IP V1 supports only I2C */
#else
    #define UART_CY_SCBIP_V1_I2C_ONLY   (0u) /* SCB IP V0 supports I2C, SPI, UART */
#endif /* (UART_CY_SCBIP_V1) */

#define UART_SCB_MODE                     (4u)

/* SCB modes enum */
#define UART_SCB_MODE_I2C                 (0x01u)
#define UART_SCB_MODE_SPI                 (0x02u)
#define UART_SCB_MODE_UART                (0x04u)
#define UART_SCB_MODE_EZI2C               (0x08u)
#define UART_SCB_MODE_UNCONFIG            (0xFFu)

/* Condition compilation depends on operation mode: Unconfigured implies apply to all modes */
#define UART_SCB_MODE_I2C_CONST_CFG       (UART_SCB_MODE_I2C       == UART_SCB_MODE)
#define UART_SCB_MODE_SPI_CONST_CFG       (UART_SCB_MODE_SPI       == UART_SCB_MODE)
#define UART_SCB_MODE_UART_CONST_CFG      (UART_SCB_MODE_UART      == UART_SCB_MODE)
#define UART_SCB_MODE_EZI2C_CONST_CFG     (UART_SCB_MODE_EZI2C     == UART_SCB_MODE)
#define UART_SCB_MODE_UNCONFIG_CONST_CFG  (UART_SCB_MODE_UNCONFIG  == UART_SCB_MODE)

/* Condition compilation for includes */
#define UART_SCB_MODE_I2C_INC       (0u !=(UART_SCB_MODE_I2C       & UART_SCB_MODE))
#define UART_SCB_MODE_EZI2C_INC     (0u !=(UART_SCB_MODE_EZI2C     & UART_SCB_MODE))
#if(!UART_CY_SCBIP_V1_I2C_ONLY)
#define UART_SCB_MODE_SPI_INC       (0u !=(UART_SCB_MODE_SPI       & UART_SCB_MODE))
#define UART_SCB_MODE_UART_INC      (0u !=(UART_SCB_MODE_UART      & UART_SCB_MODE))
#else
#define UART_SCB_MODE_SPI_INC       (0u)
#define UART_SCB_MODE_UART_INC      (0u)
#endif /* ((!UART_CY_SCBIP_V1_I2C_ONLY) */

/* Interrupts remove options */
#define UART_REMOVE_SCB_IRQ             (1u)
#define UART_SCB_IRQ_INTERNAL           (0u == UART_REMOVE_SCB_IRQ)

#define UART_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define UART_UART_RX_WAKEUP_IRQ         (0u == UART_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define UART_SCB_INTR_MODE_NONE     (0u)
#define UART_SCB_INTR_MODE_INTERNAL (1u)
#define UART_SCB_INTR_MODE_EXTERNAL (2u)

/* Bootloader communication interface enable */
#define UART_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*       Includes
****************************************/

#include "UART_PINS.h"


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} UART_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* Start and Stop APIs */
void UART_Init(void);
void UART_Enable(void);
void UART_Start(void);
void UART_Stop(void);

/* Sleep and Wakeup APis */
void UART_Sleep(void);
void UART_Wakeup(void);

/* Custom interrupt handler */
void UART_SetCustomInterruptHandler(cyisraddress func);

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_BTLDR_COMM_ENABLED)
    /* Bootloader Physical layer functions */
    void UART_CyBtldrCommStart(void);
    void UART_CyBtldrCommStop (void);
    void UART_CyBtldrCommReset(void);
    cystatus UART_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    #if(CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART)
        #define CyBtldrCommStart    UART_CyBtldrCommStart
        #define CyBtldrCommStop     UART_CyBtldrCommStop
        #define CyBtldrCommReset    UART_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART) */

#endif /*defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */

/* Interface to internal interrupt component */
#if(UART_SCB_IRQ_INTERNAL)
    #define UART_EnableInt()        CyIntEnable      (UART_ISR_NUMBER)
    #define UART_DisableInt()       CyIntDisable     (UART_ISR_NUMBER)
    #define UART_ClearPendingInt()  CyIntClearPending(UART_ISR_NUMBER)
#endif /* (UART_SCB_IRQ_INTERNAL) */

#if(UART_UART_RX_WAKEUP_IRQ)
    #define UART_RxWakeEnableInt()        CyIntEnable      (UART_RX_WAKE_ISR_NUMBER)
    #define UART_RxWakeDisableInt()       CyIntDisable     (UART_RX_WAKE_ISR_NUMBER)
    #define UART_RxWakeClearPendingInt()  CyIntClearPending(UART_RX_WAKE_ISR_NUMBER)
#endif /* (UART_UART_RX_WAKEUP_IRQ) */

/* Get interrupt cause */
#define UART_GetInterruptCause()    (UART_INTR_CAUSE_REG)

/* APIs to service INTR_RX register */
#define UART_SetRxInterruptMode(interruptMask)     UART_WRITE_INTR_RX_MASK(interruptMask)
#define UART_ClearRxInterruptSource(interruptMask) UART_CLEAR_INTR_RX(interruptMask)
#define UART_SetRxInterrupt(interruptMask)         UART_SET_INTR_RX(interruptMask)
#define UART_GetRxInterruptSource()                (UART_INTR_RX_REG)
#define UART_GetRxInterruptMode()                  (UART_INTR_RX_MASK_REG)
#define UART_GetRxInterruptSourceMasked()          (UART_INTR_RX_MASKED_REG)

/* APIs to service INTR_TX register */
#define UART_SetTxInterruptMode(interruptMask)     UART_WRITE_INTR_TX_MASK(interruptMask)
#define UART_ClearTxInterruptSource(interruptMask) UART_CLEAR_INTR_TX(interruptMask)
#define UART_SetTxInterrupt(interruptMask)         UART_SET_INTR_TX(interruptMask)
#define UART_GetTxInterruptSource()                (UART_INTR_TX_REG)
#define UART_GetTxInterruptMode()                  (UART_INTR_TX_MASK_REG)
#define UART_GetTxInterruptSourceMasked()          (UART_INTR_TX_MASKED_REG)

/* APIs to service INTR_MASTER register */
#define UART_SetMasterInterruptMode(interruptMask)    UART_WRITE_INTR_MASTER_MASK(interruptMask)
#define UART_ClearMasterInterruptSource(interruptMask) UART_CLEAR_INTR_MASTER(interruptMask)
#define UART_SetMasterInterrupt(interruptMask)         UART_SET_INTR_MASTER(interruptMask)
#define UART_GetMasterInterruptSource()                (UART_INTR_MASTER_REG)
#define UART_GetMasterInterruptMode()                  (UART_INTR_MASTER_MASK_REG)
#define UART_GetMasterInterruptSourceMasked()          (UART_INTR_MASTER_MASKED_REG)

/* APIs to service INTR_SLAVE register */
#define UART_SetSlaveInterruptMode(interruptMask)     UART_WRITE_INTR_SLAVE_MASK(interruptMask)
#define UART_ClearSlaveInterruptSource(interruptMask) UART_CLEAR_INTR_SLAVE(interruptMask)
#define UART_SetSlaveInterrupt(interruptMask)         UART_SET_INTR_SLAVE(interruptMask)
#define UART_GetSlaveInterruptSource()                (UART_INTR_SLAVE_REG)
#define UART_GetSlaveInterruptMode()                  (UART_INTR_SLAVE_MASK_REG)
#define UART_GetSlaveInterruptSourceMasked()          (UART_INTR_SLAVE_MASKED_REG)


/**********************************
*     Vars with External Linkage
**********************************/

extern uint8 UART_initVar;


/***************************************
*              Registers
***************************************/

#define UART_CTRL_REG               (*(reg32 *) UART_SCB__CTRL)
#define UART_CTRL_PTR               ( (reg32 *) UART_SCB__CTRL)

#define UART_STATUS_REG             (*(reg32 *) UART_SCB__STATUS)
#define UART_STATUS_PTR             ( (reg32 *) UART_SCB__STATUS)

#if(!UART_CY_SCBIP_V1_I2C_ONLY)
    #define UART_SPI_CTRL_REG           (*(reg32 *) UART_SCB__SPI_CTRL)
    #define UART_SPI_CTRL_PTR           ( (reg32 *) UART_SCB__SPI_CTRL)

    #define UART_SPI_STATUS_REG         (*(reg32 *) UART_SCB__SPI_STATUS)
    #define UART_SPI_STATUS_PTR         ( (reg32 *) UART_SCB__SPI_STATUS)

    #define UART_UART_CTRL_REG          (*(reg32 *) UART_SCB__UART_CTRL)
    #define UART_UART_CTRL_PTR          ( (reg32 *) UART_SCB__UART_CTRL)

    #define UART_UART_TX_CTRL_REG       (*(reg32 *) UART_SCB__UART_TX_CTRL)
    #define UART_UART_TX_CTRL_PTR       ( (reg32 *) UART_SCB__UART_RX_CTRL)

    #define UART_UART_RX_CTRL_REG       (*(reg32 *) UART_SCB__UART_RX_CTRL)
    #define UART_UART_RX_CTRL_PTR       ( (reg32 *) UART_SCB__UART_RX_CTRL)

    #define UART_UART_RX_STATUS_REG     (*(reg32 *) UART_SCB__UART_RX_STATUS)
    #define UART_UART_RX_STATUS_PTR     ( (reg32 *) UART_SCB__UART_RX_STATUS)
#endif /* (!UART_CY_SCBIP_V1_I2C_ONLY) */

#define UART_I2C_CTRL_REG           (*(reg32 *) UART_SCB__I2C_CTRL)
#define UART_I2C_CTRL_PTR           ( (reg32 *) UART_SCB__I2C_CTRL)

#define UART_I2C_STATUS_REG         (*(reg32 *) UART_SCB__I2C_STATUS)
#define UART_I2C_STATUS_PTR         ( (reg32 *) UART_SCB__I2C_STATUS)

#define UART_I2C_MASTER_CMD_REG     (*(reg32 *) UART_SCB__I2C_M_CMD)
#define UART_I2C_MASTER_CMD_PTR     ( (reg32 *) UART_SCB__I2C_M_CMD)

#define UART_I2C_SLAVE_CMD_REG      (*(reg32 *) UART_SCB__I2C_S_CMD)
#define UART_I2C_SLAVE_CMD_PTR      ( (reg32 *) UART_SCB__I2C_S_CMD)

#define UART_I2C_CFG_REG            (*(reg32 *) UART_SCB__I2C_CFG)
#define UART_I2C_CFG_PTR            ( (reg32 *) UART_SCB__I2C_CFG)

#define UART_TX_CTRL_REG            (*(reg32 *) UART_SCB__TX_CTRL)
#define UART_TX_CTRL_PTR            ( (reg32 *) UART_SCB__TX_CTRL)

#define UART_TX_FIFO_CTRL_REG       (*(reg32 *) UART_SCB__TX_FIFO_CTRL)
#define UART_TX_FIFO_CTRL_PTR       ( (reg32 *) UART_SCB__TX_FIFO_CTRL)

#define UART_TX_FIFO_STATUS_REG     (*(reg32 *) UART_SCB__TX_FIFO_STATUS)
#define UART_TX_FIFO_STATUS_PTR     ( (reg32 *) UART_SCB__TX_FIFO_STATUS)

#define UART_TX_FIFO_WR_REG         (*(reg32 *) UART_SCB__TX_FIFO_WR)
#define UART_TX_FIFO_WR_PTR         ( (reg32 *) UART_SCB__TX_FIFO_WR)

#define UART_RX_CTRL_REG            (*(reg32 *) UART_SCB__RX_CTRL)
#define UART_RX_CTRL_PTR            ( (reg32 *) UART_SCB__RX_CTRL)

#define UART_RX_FIFO_CTRL_REG       (*(reg32 *) UART_SCB__RX_FIFO_CTRL)
#define UART_RX_FIFO_CTRL_PTR       ( (reg32 *) UART_SCB__RX_FIFO_CTRL)

#define UART_RX_FIFO_STATUS_REG     (*(reg32 *) UART_SCB__RX_FIFO_STATUS)
#define UART_RX_FIFO_STATUS_PTR     ( (reg32 *) UART_SCB__RX_FIFO_STATUS)

#define UART_RX_MATCH_REG           (*(reg32 *) UART_SCB__RX_MATCH)
#define UART_RX_MATCH_PTR           ( (reg32 *) UART_SCB__RX_MATCH)

#define UART_RX_FIFO_RD_REG         (*(reg32 *) UART_SCB__RX_FIFO_RD)
#define UART_RX_FIFO_RD_PTR         ( (reg32 *) UART_SCB__RX_FIFO_RD)

#define UART_RX_FIFO_RD_SILENT_REG  (*(reg32 *) UART_SCB__RX_FIFO_RD_SILENT)
#define UART_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) UART_SCB__RX_FIFO_RD_SILENT)

#define UART_EZBUF_DATA00_REG       (*(reg32 *) UART_SCB__EZ_DATA00)
#define UART_EZBUF_DATA00_PTR       ( (reg32 *) UART_SCB__EZ_DATA00)

#define UART_INTR_CAUSE_REG         (*(reg32 *) UART_SCB__INTR_CAUSE)
#define UART_INTR_CAUSE_PTR         ( (reg32 *) UART_SCB__INTR_CAUSE)

#define UART_INTR_I2C_EC_REG        (*(reg32 *) UART_SCB__INTR_I2C_EC)
#define UART_INTR_I2C_EC_PTR        ( (reg32 *) UART_SCB__INTR_I2C_EC)

#define UART_INTR_I2C_EC_MASK_REG   (*(reg32 *) UART_SCB__INTR_I2C_EC_MASK)
#define UART_INTR_I2C_EC_MASK_PTR   ( (reg32 *) UART_SCB__INTR_I2C_EC_MASK)

#define UART_INTR_I2C_EC_MASKED_REG (*(reg32 *) UART_SCB__INTR_I2C_EC_MASKED)
#define UART_INTR_I2C_EC_MASKED_PTR ( (reg32 *) UART_SCB__INTR_I2C_EC_MASKED)

#if(!UART_CY_SCBIP_V1_I2C_ONLY)
    #define UART_INTR_SPI_EC_REG        (*(reg32 *) UART_SCB__INTR_SPI_EC)
    #define UART_INTR_SPI_EC_PTR        ( (reg32 *) UART_SCB__INTR_SPI_EC)

    #define UART_INTR_SPI_EC_MASK_REG   (*(reg32 *) UART_SCB__INTR_SPI_EC_MASK)
    #define UART_INTR_SPI_EC_MASK_PTR   ( (reg32 *) UART_SCB__INTR_SPI_EC_MASK)

    #define UART_INTR_SPI_EC_MASKED_REG (*(reg32 *) UART_SCB__INTR_SPI_EC_MASKED)
    #define UART_INTR_SPI_EC_MASKED_PTR ( (reg32 *) UART_SCB__INTR_SPI_EC_MASKED)
#endif /* (!UART_CY_SCBIP_V1_I2C_ONLY) */

#define UART_INTR_MASTER_REG        (*(reg32 *) UART_SCB__INTR_M)
#define UART_INTR_MASTER_PTR        ( (reg32 *) UART_SCB__INTR_M)

#define UART_INTR_MASTER_SET_REG    (*(reg32 *) UART_SCB__INTR_M_SET)
#define UART_INTR_MASTER_SET_PTR    ( (reg32 *) UART_SCB__INTR_M_SET)

#define UART_INTR_MASTER_MASK_REG   (*(reg32 *) UART_SCB__INTR_M_MASK)
#define UART_INTR_MASTER_MASK_PTR   ( (reg32 *) UART_SCB__INTR_M_MASK)

#define UART_INTR_MASTER_MASKED_REG (*(reg32 *) UART_SCB__INTR_M_MASKED)
#define UART_INTR_MASTER_MASKED_PTR ( (reg32 *) UART_SCB__INTR_M_MASKED)

#define UART_INTR_SLAVE_REG         (*(reg32 *) UART_SCB__INTR_S)
#define UART_INTR_SLAVE_PTR         ( (reg32 *) UART_SCB__INTR_S)

#define UART_INTR_SLAVE_SET_REG     (*(reg32 *) UART_SCB__INTR_S_SET)
#define UART_INTR_SLAVE_SET_PTR     ( (reg32 *) UART_SCB__INTR_S_SET)

#define UART_INTR_SLAVE_MASK_REG    (*(reg32 *) UART_SCB__INTR_S_MASK)
#define UART_INTR_SLAVE_MASK_PTR    ( (reg32 *) UART_SCB__INTR_S_MASK)

#define UART_INTR_SLAVE_MASKED_REG  (*(reg32 *) UART_SCB__INTR_S_MASKED)
#define UART_INTR_SLAVE_MASKED_PTR  ( (reg32 *) UART_SCB__INTR_S_MASKED)

#define UART_INTR_TX_REG            (*(reg32 *) UART_SCB__INTR_TX)
#define UART_INTR_TX_PTR            ( (reg32 *) UART_SCB__INTR_TX)

#define UART_INTR_TX_SET_REG        (*(reg32 *) UART_SCB__INTR_TX_SET)
#define UART_INTR_TX_SET_PTR        ( (reg32 *) UART_SCB__INTR_TX_SET)

#define UART_INTR_TX_MASK_REG       (*(reg32 *) UART_SCB__INTR_TX_MASK)
#define UART_INTR_TX_MASK_PTR       ( (reg32 *) UART_SCB__INTR_TX_MASK)

#define UART_INTR_TX_MASKED_REG     (*(reg32 *) UART_SCB__INTR_TX_MASKED)
#define UART_INTR_TX_MASKED_PTR     ( (reg32 *) UART_SCB__INTR_TX_MASKED)

#define UART_INTR_RX_REG            (*(reg32 *) UART_SCB__INTR_RX)
#define UART_INTR_RX_PTR            ( (reg32 *) UART_SCB__INTR_RX)

#define UART_INTR_RX_SET_REG        (*(reg32 *) UART_SCB__INTR_RX_SET)
#define UART_INTR_RX_SET_PTR        ( (reg32 *) UART_SCB__INTR_RX_SET)

#define UART_INTR_RX_MASK_REG       (*(reg32 *) UART_SCB__INTR_RX_MASK)
#define UART_INTR_RX_MASK_PTR       ( (reg32 *) UART_SCB__INTR_RX_MASK)

#define UART_INTR_RX_MASKED_REG     (*(reg32 *) UART_SCB__INTR_RX_MASKED)
#define UART_INTR_RX_MASKED_PTR     ( (reg32 *) UART_SCB__INTR_RX_MASKED)


/***************************************
*        Registers Constants
***************************************/

#if(UART_SCB_IRQ_INTERNAL)
    #define UART_ISR_NUMBER     ((uint8) UART_SCB_IRQ__INTC_NUMBER)
    #define UART_ISR_PRIORITY   ((uint8) UART_SCB_IRQ__INTC_PRIOR_NUM)
#endif /* (UART_SCB_IRQ_INTERNAL) */

#if(UART_UART_RX_WAKEUP_IRQ)
    #define UART_RX_WAKE_ISR_NUMBER     ((uint8) UART_RX_WAKEUP_IRQ__INTC_NUMBER)
    #define UART_RX_WAKE_ISR_PRIORITY   ((uint8) UART_RX_WAKEUP_IRQ__INTC_PRIOR_NUM)
#endif /* (UART_UART_RX_WAKEUP_IRQ) */

/* UART_CTRL_REG */
#define UART_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define UART_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define UART_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define UART_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#define UART_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO      */
#define UART_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve colide */
#define UART_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                      */
#define UART_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                    */
#define UART_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define UART_CTRL_EC_AM_MODE        ((uint32) 0x01u << UART_CTRL_EC_AM_MODE_POS)
#define UART_CTRL_EC_OP_MODE        ((uint32) 0x01u << UART_CTRL_EC_OP_MODE_POS)
#define UART_CTRL_EZBUF_MODE        ((uint32) 0x01u << UART_CTRL_EZBUF_MODE_POS)
#define UART_CTRL_ADDR_ACCEPT       ((uint32) 0x01u << UART_CTRL_ADDR_ACCEPT_POS)
#define UART_CTRL_BLOCK             ((uint32) 0x01u << UART_CTRL_BLOCK_POS)
#define UART_CTRL_MODE_MASK         ((uint32) 0x03u << UART_CTRL_MODE_POS)
#define UART_CTRL_MODE_I2C          ((uint32) 0x00u)
#define UART_CTRL_MODE_SPI          ((uint32) 0x01u << UART_CTRL_MODE_POS)
#define UART_CTRL_MODE_UART         ((uint32) 0x02u << UART_CTRL_MODE_POS)
#define UART_CTRL_ENABLED           ((uint32) 0x01u << UART_CTRL_ENABLED_POS)

/* UART_STATUS_REG */
#define UART_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externaly clocked loigc access to EZ memory */
#define UART_STATUS_EC_BUSY         ((uint32) 0x0Fu)

/* UART_SPI_CTRL_REG  */
#define UART_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define UART_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define UART_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define UART_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define UART_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#define UART_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loopback control enabled             */
#define UART_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define UART_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define UART_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define UART_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define UART_SPI_CTRL_SELECT_PRECEDE        ((uint32) 0x01u << UART_SPI_CTRL_SELECT_PRECEDE_POS)
#define UART_SPI_CTRL_SCLK_MODE_MASK        ((uint32) 0x03u << UART_SPI_CTRL_CPHA_POS)
#define UART_SPI_CTRL_CPHA                  ((uint32) 0x01u << UART_SPI_CTRL_CPHA_POS)
#define UART_SPI_CTRL_CPOL                  ((uint32) 0x01u << UART_SPI_CTRL_CPOL_POS)
#define UART_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) 0x01u << \
                                                                    UART_SPI_CTRL_LATE_MISO_SAMPLE_POS)
#define UART_SPI_CTRL_LOOPBACK              ((uint32) 0x01u << UART_SPI_CTRL_LOOPBACK_POS)
#define UART_SPI_CTRL_MODE_MASK             ((uint32) 0x03u << UART_SPI_CTRL_MODE_POS)
#define UART_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define UART_SPI_CTRL_MODE_TI               ((uint32) 0x01u << UART_CTRL_MODE_POS)
#define UART_SPI_CTRL_MODE_NS               ((uint32) 0x02u << UART_CTRL_MODE_POS)
#define UART_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) 0x03u << UART_SPI_CTRL_SLAVE_SELECT_POS)
#define UART_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define UART_SPI_CTRL_SLAVE_SELECT1         ((uint32) 0x01u << UART_SPI_CTRL_SLAVE_SELECT_POS)
#define UART_SPI_CTRL_SLAVE_SELECT2         ((uint32) 0x02u << UART_SPI_CTRL_SLAVE_SELECT_POS)
#define UART_SPI_CTRL_SLAVE_SELECT3         ((uint32) 0x03u << UART_SPI_CTRL_SLAVE_SELECT_POS)
#define UART_SPI_CTRL_MASTER                ((uint32) 0x01u << UART_SPI_CTRL_MASTER_MODE_POS)
#define UART_SPI_CTRL_SLAVE                 ((uint32) 0x00u)

/* UART_SPI_STATUS_REG  */
#define UART_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define UART_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define UART_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define UART_SPI_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << UART_I2C_STATUS_EZBUF_ADDR_POS)

/* UART_UART_CTRL */
#define UART_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loopback     */
#define UART_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define UART_UART_CTRL_LOOPBACK             ((uint32) 0x01u << UART_UART_CTRL_LOOPBACK_POS)
#define UART_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define UART_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) 0x01u << UART_UART_CTRL_MODE_POS)
#define UART_UART_CTRL_MODE_UART_IRDA       ((uint32) 0x02u << UART_UART_CTRL_MODE_POS)
#define UART_UART_CTRL_MODE_MASK            ((uint32) 0x03u << UART_UART_CTRL_MODE_POS)

/* UART_UART_TX_CTRL */
#define UART_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define UART_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define UART_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define UART_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define UART_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define UART_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define UART_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define UART_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define UART_UART_TX_CTRL_PARITY                ((uint32) 0x01u << \
                                                                    UART_UART_TX_CTRL_PARITY_POS)
#define UART_UART_TX_CTRL_PARITY_ENABLED        ((uint32) 0x01u << \
                                                                    UART_UART_TX_CTRL_PARITY_ENABLED_POS)
#define UART_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) 0x01u << \
                                                                    UART_UART_TX_CTRL_RETRY_ON_NACK_POS)

/* UART_UART_RX_CTRL */
#define UART_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 prd   */
#define UART_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define UART_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define UART_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define UART_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define UART_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define UART_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define UART_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standart */
#define UART_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standart */
#define UART_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define UART_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define UART_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define UART_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define UART_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define UART_UART_RX_CTRL_PARITY                    ((uint32) 0x01u << \
                                                                    UART_UART_RX_CTRL_PARITY_POS)
#define UART_UART_RX_CTRL_PARITY_ENABLED            ((uint32) 0x01u << \
                                                                    UART_UART_RX_CTRL_PARITY_ENABLED_POS)
#define UART_UART_RX_CTRL_POLARITY                  ((uint32) 0x01u << \
                                                                    UART_UART_RX_CTRL_POLARITY_POS)
#define UART_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) 0x01u << \
                                                                   UART_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS)
#define UART_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) 0x01u << \
                                                                    UART_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS)
#define UART_UART_RX_CTRL_MP_MODE                   ((uint32) 0x01u << \
                                                                    UART_UART_RX_CTRL_MP_MODE_POS)
#define UART_UART_RX_CTRL_LIN_MODE                  ((uint32) 0x01u << \
                                                                    UART_UART_RX_CTRL_LIN_MODE_POS)
#define UART_UART_RX_CTRL_SKIP_START                ((uint32) 0x01u << \
                                                                    UART_UART_RX_CTRL_SKIP_START_POS)
#define UART_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) 0x0Fu << \
                                                                    UART_UART_RX_CTRL_BREAK_WIDTH_POS)
/* UART_UART_RX_STATUS_REG */
#define UART_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baute Rate counter */
#define UART_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)

/* UART_I2C_CTRL */
#define UART_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: masrer only */
#define UART_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  masrer only */
#define UART_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data wgile RX FIFO != FULL*/
#define UART_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define UART_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define UART_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define UART_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define UART_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define UART_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define UART_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loopback                              */
#define UART_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define UART_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define UART_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define UART_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) 0x0Fu << \
                                                                UART_I2C_CTRL_LOW_PHASE_OVS_POS)
#define UART_I2C_CTRL_M_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                UART_I2C_CTRL_M_READY_DATA_ACK_POS)
#define UART_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                UART_I2C_CTRL_M_NOT_READY_DATA_NACK_POS)
#define UART_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) 0x01u << \
                                                                UART_I2C_CTRL_S_GENERAL_IGNORE_POS)
#define UART_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) 0x01u << \
                                                                UART_I2C_CTRL_S_READY_ADDR_ACK_POS)
#define UART_I2C_CTRL_S_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                UART_I2C_CTRL_S_READY_DATA_ACK_POS)
#define UART_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) 0x01u << \
                                                                UART_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS)
#define UART_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                UART_I2C_CTRL_S_NOT_READY_DATA_NACK_POS)
#define UART_I2C_CTRL_LOOPBACK              ((uint32) 0x01u << \
                                                                UART_I2C_CTRL_LOOPBACK_POS)
#define UART_I2C_CTRL_SLAVE_MODE            ((uint32) 0x01u << \
                                                                UART_I2C_CTRL_SLAVE_MODE_POS)
#define UART_I2C_CTRL_MASTER_MODE           ((uint32) 0x01u << \
                                                                UART_I2C_CTRL_MASTER_MODE_POS)
#define UART_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) 0x03u << \
                                                                UART_I2C_CTRL_SLAVE_MODE_POS)

/* UART_I2C_STATUS_REG  */
#define UART_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define UART_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define UART_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define UART_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define UART_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define UART_I2C_STATUS_S_READ          ((uint32) 0x01u << UART_I2C_STATUS_S_READ_POS)
#define UART_I2C_STATUS_M_READ          ((uint32) 0x01u << UART_I2C_STATUS_M_READ_POS)
#define UART_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << UART_I2C_STATUS_EZBUF_ADDR_POS)

/* UART_I2C_MASTER_CMD_REG */
#define UART_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define UART_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define UART_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define UART_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define UART_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define UART_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define UART_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) 0x01u << \
                                                                   UART_I2C_MASTER_CMD_M_START_ON_IDLE_POS)
#define UART_I2C_MASTER_CMD_M_ACK           ((uint32) 0x01u << \
                                                                   UART_I2C_MASTER_CMD_M_ACK_POS)
#define UART_I2C_MASTER_CMD_M_NACK          ((uint32) 0x01u << \
                                                                    UART_I2C_MASTER_CMD_M_NACK_POS)
#define UART_I2C_MASTER_CMD_M_STOP          ((uint32) 0x01u << \
                                                                    UART_I2C_MASTER_CMD_M_STOP_POS)

/* UART_I2C_SLAVE_CMD_REG  */
#define UART_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define UART_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define UART_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define UART_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << UART_I2C_SLAVE_CMD_S_NACK_POS)

#define UART_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define UART_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define UART_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define UART_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << UART_I2C_SLAVE_CMD_S_NACK_POS)
/* UART_I2C_CFG  */
#define UART_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define UART_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define UART_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define UART_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define UART_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define UART_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define UART_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define UART_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define UART_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define UART_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define UART_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50ns filter, '1': 10 ns filter      */
#define UART_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define UART_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x00u)
#define UART_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                UART_I2C_CFG_SDA_FILT_TRIM_POS)
#define UART_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) 0x03u << \
                                                                UART_I2C_CFG_SCL_FILT_HYS_POS)
#define UART_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                UART_I2C_CFG_SCL_FILT_TRIM_POS)
#define UART_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) 0x03u << \
                                                                UART_I2C_CFG_SDA_FILT_OUT_HYS_POS)
#define UART_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) 0x03u << \
                                                                UART_I2C_CFG_SDA_FILT_OUT_TRIM_POS)
#define UART_I2C_CFG_SDA_FILT_HS                ((uint32) 0x01u << \
                                                                UART_I2C_CFG_SDA_FILT_HS_POS)
#define UART_I2C_CFG_SDA_FILT_ENABLED           ((uint32) 0x01u << \
                                                                UART_I2C_CFG_SDA_FILT_ENABLED_POS)
#define UART_I2C_CFG_SCL_FILT_HS                ((uint32) 0x01u << \
                                                                UART_I2C_CFG_SCL_FILT_HS_POS)
#define UART_I2C_CFG_SCL_FILT_ENABLED           ((uint32) 0x01u << \
                                                                UART_I2C_CFG_SCL_FILT_ENABLED_POS)
#define UART_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) 0x01u << \
                                                                UART_I2C_CFG_SDA_FILT_OUT_HS_POS)
#define UART_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) 0x01u << \
                                                                UART_I2C_CFG_SDA_FILT_OUT_ENABLED_POS)

/* UART_TX_CTRL_REG */
#define UART_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Dataframe width: (Data width - 1) */
#define UART_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define UART_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define UART_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define UART_TX_CTRL_MSB_FIRST          ((uint32) 0x01u << UART_TX_CTRL_MSB_FIRST_POS)
#define UART_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define UART_TX_CTRL_ENABLED            ((uint32) 0x01u << UART_TX_CTRL_ENABLED_POS)

/* UART_TX_CTRL_FIFO_REG */
#define UART_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define UART_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: claared after set           */
#define UART_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define UART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) 0x07u)
#define UART_TX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << UART_TX_FIFO_CTRL_CLEAR_POS)
#define UART_TX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << UART_TX_FIFO_CTRL_FREEZE_POS)

/* UART_TX_FIFO_STATUS_REG */
#define UART_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define UART_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define UART_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define UART_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define UART_TX_FIFO_STATUS_USED_MASK   ((uint32) 0x0Fu)
#define UART_TX_FIFO_SR_VALID           ((uint32) 0x01u << UART_TX_FIFO_SR_VALID_POS)
#define UART_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) 0x07u << UART_TX_FIFO_STATUS_RD_PTR_POS)
#define UART_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) 0x07u << UART_TX_FIFO_STATUS_WR_PTR_POS)

/* UART_TX_FIFO_WR_REG */
#define UART_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define UART_TX_FIFO_WR_MASK   ((uint32) 0xFFu)

/* UART_RX_CTRL_REG */
#define UART_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Dataframe width: (Data width - 1) */
#define UART_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define UART_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define UART_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define UART_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define UART_RX_CTRL_MSB_FIRST          ((uint32) 0x01u << UART_RX_CTRL_MSB_FIRST_POS)
#define UART_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define UART_RX_CTRL_MEDIAN             ((uint32) 0x01u << UART_RX_CTRL_MEDIAN_POS)
#define UART_RX_CTRL_ENABLED            ((uint32) 0x01u << UART_RX_CTRL_ENABLED_POS)


/* UART_RX_FIFO_CTRL_REG */
#define UART_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define UART_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: claar after set           */
#define UART_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define UART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) 0x07u)
#define UART_RX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << UART_RX_FIFO_CTRL_CLEAR_POS)
#define UART_RX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << UART_RX_FIFO_CTRL_FREEZE_POS)

/* UART_RX_FIFO_STATUS_REG */
#define UART_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define UART_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define UART_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define UART_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define UART_RX_FIFO_STATUS_USED_MASK   ((uint32) 0x0Fu)
#define UART_RX_FIFO_SR_VALID           ((uint32) 0x01u << UART_RX_FIFO_SR_VALID_POS)
#define UART_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) 0x07u << UART_RX_FIFO_STATUS_RD_PTR_POS)
#define UART_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) 0x07u << UART_RX_FIFO_STATUS_WR_PTR_POS)

/* UART_RX_MATCH_REG */
#define UART_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define UART_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define UART_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define UART_RX_MATCH_MASK_MASK    ((uint32) 0xFFu << UART_RX_MATCH_MASK_POS)

/* UART_RX_FIFO_WR_REG */
#define UART_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define UART_RX_FIFO_RD_MASK   ((uint32) 0xFFu)

/* UART_RX_FIFO_RD_SILENT_REG */
#define UART_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define UART_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* UART_RX_FIFO_RD_SILENT_REG */
#define UART_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define UART_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* UART_EZBUF_DATA_REG */
#define UART_EZBUF_DATA_POS   (0u)  /* [7:0] Data from Ez Memory */
#define UART_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  UART_INTR_CAUSE_REG */
#define UART_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define UART_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define UART_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define UART_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define UART_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define UART_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define UART_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define UART_INTR_CAUSE_SLAVE       ((uint32) 0x01u << UART_INTR_CAUSE_SLAVE_POS)
#define UART_INTR_CAUSE_TX          ((uint32) 0x01u << UART_INTR_CAUSE_TX_POS)
#define UART_INTR_CAUSE_RX          ((uint32) 0x01u << UART_INTR_CAUSE_RX_POS)
#define UART_INTR_CAUSE_I2C_EC      ((uint32) 0x01u << UART_INTR_CAUSE_I2C_EC_POS)
#define UART_INTR_CAUSE_SPI_EC      ((uint32) 0x01u << UART_INTR_CAUSE_SPI_EC_POS)

/* UART_INTR_SPI_EC_REG, UART_INTR_SPI_EC_MASK_REG, UART_INTR_SPI_EC_MASKED_REG */
#define UART_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define UART_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define UART_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define UART_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define UART_INTR_SPI_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    UART_INTR_SPI_EC_EZBUF_STOP_POS)
#define UART_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    UART_INTR_SPI_EC_EZBUF_WRITE_STOP_POS)

/* UART_INTR_I2C_EC, UART_INTR_I2C_EC_MASK, UART_INTR_I2C_EC_MASKED */
#define UART_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define UART_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define UART_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define UART_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define UART_INTR_I2C_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    UART_INTR_I2C_EC_EZBUF_STOP_POS)
#define UART_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    UART_INTR_I2C_EC_EZBUF_WRITE_STOP_POS)

/* UART_INTR_MASTER, UART_INTR_MASTER_SET,
   UART_INTR_MASTER_MASK, UART_INTR_MASTER_MASKED */
#define UART_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define UART_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define UART_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define UART_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define UART_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define UART_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete trasfer: Only for SPI            */
#define UART_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define UART_INTR_MASTER_I2C_NACK           ((uint32) 0x01u << UART_INTR_MASTER_I2C_NACK_POS)
#define UART_INTR_MASTER_I2C_ACK            ((uint32) 0x01u << UART_INTR_MASTER_I2C_ACK_POS)
#define UART_INTR_MASTER_I2C_STOP           ((uint32) 0x01u << UART_INTR_MASTER_I2C_STOP_POS)
#define UART_INTR_MASTER_I2C_BUS_ERROR      ((uint32) 0x01u << \
                                                                    UART_INTR_MASTER_I2C_BUS_ERROR_POS)
#define UART_INTR_MASTER_SPI_DONE           ((uint32) 0x01u << UART_INTR_MASTER_SPI_DONE_POS)

/*
* UART_INTR_SLAVE, UART_INTR_SLAVE_SET,
* UART_INTR_SLAVE_MASK, UART_INTR_SLAVE_MASKED
*/
#define UART_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define UART_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define UART_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define UART_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define UART_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intened */
#define UART_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define UART_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define UART_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define UART_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define UART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define UART_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaciton: Only for SPI   */
#define UART_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define UART_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define UART_INTR_SLAVE_I2C_NACK                 ((uint32) 0x01u << \
                                                                    UART_INTR_SLAVE_I2C_NACK_POS)
#define UART_INTR_SLAVE_I2C_ACK                  ((uint32) 0x01u << \
                                                                    UART_INTR_SLAVE_I2C_ACK_POS)
#define UART_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) 0x01u << \
                                                                    UART_INTR_SLAVE_I2C_WRITE_STOP_POS)
#define UART_INTR_SLAVE_I2C_STOP                 ((uint32) 0x01u << \
                                                                    UART_INTR_SLAVE_I2C_STOP_POS)
#define UART_INTR_SLAVE_I2C_START                ((uint32) 0x01u << \
                                                                    UART_INTR_SLAVE_I2C_START_POS)
#define UART_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) 0x01u << \
                                                                    UART_INTR_SLAVE_I2C_ADDR_MATCH_POS)
#define UART_INTR_SLAVE_I2C_GENERAL              ((uint32) 0x01u << \
                                                                    UART_INTR_SLAVE_I2C_GENERAL_POS)
#define UART_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) 0x01u << \
                                                                    UART_INTR_SLAVE_I2C_BUS_ERROR_POS)
#define UART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                   UART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS)
#define UART_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    UART_INTR_SLAVE_SPI_EZBUF_STOP_POS)
#define UART_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) 0x01u << \
                                                                    UART_INTR_SLAVE_SPI_BUS_ERROR_POS)

/*
* UART_INTR_TX, UART_INTR_TX_SET,
* UART_INTR_TX_MASK, UART_INTR_TX_MASKED
*/
#define UART_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define UART_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define UART_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define UART_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define UART_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define UART_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define UART_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define UART_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define UART_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define UART_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define UART_INTR_TX_NOT_FULL           ((uint32) 0x01u << UART_INTR_TX_NOT_FULL_POS)
#define UART_INTR_TX_EMPTY              ((uint32) 0x01u << UART_INTR_TX_EMPTY_POS)
#define UART_INTR_TX_OVERFLOW           ((uint32) 0x01u << UART_INTR_TX_OVERFLOW_POS)
#define UART_INTR_TX_UNDERFLOW          ((uint32) 0x01u << UART_INTR_TX_UNDERFLOW_POS)
#define UART_INTR_TX_BLOCKED            ((uint32) 0x01u << UART_INTR_TX_BLOCKED_POS)
#define UART_INTR_TX_UART_NACK          ((uint32) 0x01u << UART_INTR_TX_UART_NACK_POS)
#define UART_INTR_TX_UART_DONE          ((uint32) 0x01u << UART_INTR_TX_UART_DONE_POS)
#define UART_INTR_TX_UART_ARB_LOST      ((uint32) 0x01u << UART_INTR_TX_UART_ARB_LOST_POS)

/*
* UART_INTR_RX, UART_INTR_RX_SET,
* UART_INTR_RX_MASK, UART_INTR_RX_MASKED
*/
#define UART_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define UART_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define UART_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define UART_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define UART_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define UART_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define UART_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define UART_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define UART_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baudrate detection is completed   */
#define UART_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define UART_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define UART_INTR_RX_NOT_EMPTY          ((uint32) 0x01u << UART_INTR_RX_NOT_EMPTY_POS)
#define UART_INTR_RX_FULL               ((uint32) 0x01u << UART_INTR_RX_FULL_POS)
#define UART_INTR_RX_OVERFLOW           ((uint32) 0x01u << UART_INTR_RX_OVERFLOW_POS)
#define UART_INTR_RX_UNDERFLOW          ((uint32) 0x01u << UART_INTR_RX_UNDERFLOW_POS)
#define UART_INTR_RX_BLOCKED            ((uint32) 0x01u << UART_INTR_RX_BLOCKED_POS)
#define UART_INTR_RX_FRAME_ERROR        ((uint32) 0x01u << UART_INTR_RX_FRAME_ERROR_POS)
#define UART_INTR_RX_PARITY_ERROR       ((uint32) 0x01u << UART_INTR_RX_PARITY_ERROR_POS)
#define UART_INTR_RX_BAUD_DETECT        ((uint32) 0x01u << UART_INTR_RX_BAUD_DETECT_POS)
#define UART_INTR_RX_BREAK_DETECT       ((uint32) 0x01u << UART_INTR_RX_BREAK_DETECT_POS)

/* Define all interupt soureces */
#define UART_INTR_I2C_EC_ALL    (UART_INTR_I2C_EC_WAKE_UP    | \
                                             UART_INTR_I2C_EC_EZBUF_STOP | \
                                             UART_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define UART_INTR_SPI_EC_ALL    (UART_INTR_SPI_EC_WAKE_UP    | \
                                             UART_INTR_SPI_EC_EZBUF_STOP | \
                                             UART_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define UART_INTR_MASTER_ALL    (UART_INTR_MASTER_I2C_ARB_LOST  | \
                                             UART_INTR_MASTER_I2C_NACK      | \
                                             UART_INTR_MASTER_I2C_ACK       | \
                                             UART_INTR_MASTER_I2C_STOP      | \
                                             UART_INTR_MASTER_I2C_BUS_ERROR | \
                                             UART_INTR_MASTER_SPI_DONE )

#define UART_INTR_SLAVE_ALL     (UART_INTR_SLAVE_I2C_ARB_LOST      | \
                                             UART_INTR_SLAVE_I2C_NACK          | \
                                             UART_INTR_SLAVE_I2C_ACK           | \
                                             UART_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             UART_INTR_SLAVE_I2C_STOP          | \
                                             UART_INTR_SLAVE_I2C_START         | \
                                             UART_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             UART_INTR_SLAVE_I2C_GENERAL       | \
                                             UART_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             UART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             UART_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             UART_INTR_SLAVE_SPI_BUS_ERROR)

#define UART_INTR_TX_ALL        (UART_INTR_TX_TRIGGER   | \
                                             UART_INTR_TX_NOT_FULL  | \
                                             UART_INTR_TX_EMPTY     | \
                                             UART_INTR_TX_OVERFLOW  | \
                                             UART_INTR_TX_UNDERFLOW | \
                                             UART_INTR_TX_BLOCKED   | \
                                             UART_INTR_TX_UART_NACK | \
                                             UART_INTR_TX_UART_DONE | \
                                             UART_INTR_TX_UART_ARB_LOST)

#define UART_INTR_RX_ALL        (UART_INTR_RX_TRIGGER      | \
                                             UART_INTR_RX_NOT_EMPTY    | \
                                             UART_INTR_RX_FULL         | \
                                             UART_INTR_RX_OVERFLOW     | \
                                             UART_INTR_RX_UNDERFLOW    | \
                                             UART_INTR_RX_BLOCKED      | \
                                             UART_INTR_RX_FRAME_ERROR  | \
                                             UART_INTR_RX_PARITY_ERROR | \
                                             UART_INTR_RX_BAUD_DETECT  | \
                                             UART_INTR_RX_BREAK_DETECT)

/* General usage HW definitions */
#define UART_ONE_BYTE_WIDTH (8u)   /* Number of bits in one byte           */
#define UART_FIFO_SIZE      (8u)   /* Size of TX or RX FIFO: defined by HW */
#define UART_EZBUFFER_SIZE  (32u)  /* EZ Buffer size: defined by HW        */

/* I2C and EZI2C slave address defines */
#define UART_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define UART_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define UART_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define UART_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define UART_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define UART_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define UART_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define UART_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define UART_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define UART_CTRL_OVS_IRDA_OVS16        (UART_UART_IRDA_LP_OVS16)


/***************************************
*    SCB Common Macro Definitions
***************************************/

/* Re-enables the SCB IP. The clear enable bit has a different effect on the scb IP depending on the version.* CY_SCBIP_V0: resets state, status, TX and RX FIFOs.
* CY_SCBIP_V1 or later: resets state, status, TX and RX FIFOs and interrupt sources.
*/
#define UART_SCB_SW_RESET \
                        do{           \
                            UART_CTRL_REG &= ((uint32) ~UART_CTRL_ENABLED); \
                            UART_CTRL_REG |= ((uint32)  UART_CTRL_ENABLED); \
                        }while(0)

/* TX FIFO macro */
#define UART_CLEAR_TX_FIFO \
                            do{        \
                                UART_TX_FIFO_CTRL_REG |= ((uint32)  UART_TX_FIFO_CTRL_CLEAR); \
                                UART_TX_FIFO_CTRL_REG &= ((uint32) ~UART_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define UART_GET_TX_FIFO_ENTRIES    (UART_TX_FIFO_STATUS_REG & \
                                                 UART_TX_FIFO_STATUS_USED_MASK)

#define UART_GET_TX_FIFO_SR_VALID   ((0u != (UART_TX_FIFO_STATUS_REG & \
                                                         UART_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define UART_CLEAR_RX_FIFO \
                            do{        \
                                UART_RX_FIFO_CTRL_REG |= ((uint32)  UART_RX_FIFO_CTRL_CLEAR); \
                                UART_RX_FIFO_CTRL_REG &= ((uint32) ~UART_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define UART_GET_RX_FIFO_ENTRIES    (UART_RX_FIFO_STATUS_REG & \
                                                    UART_RX_FIFO_STATUS_USED_MASK)

#define UART_GET_RX_FIFO_SR_VALID   ((0u != (UART_RX_FIFO_STATUS_REG & \
                                                         UART_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Write interrupt source: set sourceMask bits in UART_INTR_X_MASK_REG */
#define UART_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    UART_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define UART_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    UART_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define UART_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    UART_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define UART_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    UART_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define UART_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    UART_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define UART_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    UART_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enable interrupt source: set sourceMask bits in UART_INTR_X_MASK_REG */
#define UART_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    UART_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define UART_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    UART_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define UART_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    UART_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define UART_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    UART_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define UART_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    UART_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define UART_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    UART_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disable interrupt source: clear sourceMask bits in UART_INTR_X_MASK_REG */
#define UART_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    UART_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define UART_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    UART_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define UART_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                UART_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define UART_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    UART_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define UART_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    UART_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define UART_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    UART_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Set interrupt sources: write sourceMask bits in UART_INTR_X_SET_REG */
#define UART_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    UART_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define UART_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    UART_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define UART_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    UART_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define UART_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    UART_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clear interrupt sources: write sourceMask bits in UART_INTR_X_REG */
#define UART_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    UART_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#define UART_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    UART_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#define UART_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    UART_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define UART_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    UART_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define UART_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    UART_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define UART_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    UART_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in UART_INTR_CAUSE_REG */
#define UART_CHECK_CAUSE_INTR(sourceMask)    (0u != (UART_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in INTR_X_MASKED_REG */
#define UART_CHECK_INTR_I2C_EC(sourceMask)  (0u != (UART_INTR_I2C_EC_REG & (sourceMask)))
#define UART_CHECK_INTR_SPI_EC(sourceMask)  (0u != (UART_INTR_SPI_EC_REG & (sourceMask)))
#define UART_CHECK_INTR_MASTER(sourceMask)  (0u != (UART_INTR_MASTER_REG & (sourceMask)))
#define UART_CHECK_INTR_SLAVE(sourceMask)   (0u != (UART_INTR_SLAVE_REG  & (sourceMask)))
#define UART_CHECK_INTR_TX(sourceMask)      (0u != (UART_INTR_TX_REG     & (sourceMask)))
#define UART_CHECK_INTR_RX(sourceMask)      (0u != (UART_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in UART_INTR_X_MASKED_REG */
#define UART_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (UART_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#define UART_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (UART_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#define UART_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (UART_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define UART_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (UART_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define UART_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (UART_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define UART_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (UART_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in UART_CTRL_REG: generaly is used to check enable bit */
#define UART_GET_CTRL_ENABLED    (0u != (UART_CTRL_REG & UART_CTRL_ENABLED))

#define UART_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (UART_I2C_CTRL_REG & \
                                                                UART_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define UART_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                UART_I2C_CTRL_REG |= UART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define UART_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                UART_I2C_CTRL_REG |= UART_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define UART_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                UART_I2C_CTRL_REG |= UART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define UART_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                UART_I2C_CTRL_REG |= UART_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define UART_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                UART_I2C_CTRL_REG |= UART_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define UART_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                UART_I2C_CTRL_REG &= ~UART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define UART_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                UART_I2C_CTRL_REG &= ~UART_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define UART_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                UART_I2C_CTRL_REG &= ~UART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define UART_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                UART_I2C_CTRL_REG &= ~UART_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define UART_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                UART_I2C_CTRL_REG &= ~UART_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define UART_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                UART_I2C_CTRL_REG |= (UART_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  UART_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define UART_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                UART_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(UART_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    UART_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define UART_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                UART_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(UART_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    UART_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Master commands */
#define UART_I2C_MASTER_GENERATE_START \
                            do{                    \
                                UART_I2C_MASTER_CMD_REG = UART_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define UART_I2C_MASTER_CLEAR_START \
                            do{                 \
                                UART_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define UART_I2C_MASTER_GENERATE_RESTART UART_I2CReStartGeneration()

#define UART_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                UART_I2C_MASTER_CMD_REG =                                            \
                                    (UART_I2C_MASTER_CMD_M_STOP |                                    \
                                        (UART_CHECK_I2C_STATUS(UART_I2C_STATUS_M_READ) ? \
                                            (UART_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define UART_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                UART_I2C_MASTER_CMD_REG = UART_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define UART_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                UART_I2C_MASTER_CMD_REG = UART_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave commands */
#define UART_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                UART_I2C_SLAVE_CMD_REG = UART_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#define UART_I2C_SLAVE_GENERATE_NACK \
                            do{                  \
                                UART_I2C_SLAVE_CMD_REG = UART_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)

#define UART_I2C_SLAVE_CLEAR_NACK \
                            do{               \
                                UART_I2C_SLAVE_CMD_REG = 0u; \
                            }while(0)

/* Return 8-bit address. The input address should be 7-bits */
#define UART_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    UART_I2C_SLAVE_ADDR_POS)) & \
                                                                        UART_I2C_SLAVE_ADDR_MASK)

#define UART_GET_I2C_7BIT_ADDRESS(addr) ((uint32) (addr) >> UART_I2C_SLAVE_ADDR_POS)

/* Adjust SDA filter Trim settings */
#define UART_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define UART_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#define UART_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            UART_I2C_CFG_REG =                  \
                            ((UART_I2C_CFG_REG & (uint32) ~UART_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<UART_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)

/* Return slave select number from SPI_CTRL register */
#define UART_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    UART_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        UART_SPI_CTRL_SLAVE_SELECT_MASK)

/* Return true if bit is set in UART_I2C_STATUS_REG */
#define UART_CHECK_I2C_STATUS(sourceMask)   (0u != (UART_I2C_STATUS_REG & (sourceMask)))

/* Return true if bit is set in UART_SPI_STATUS_REG */
#define UART_CHECK_SPI_STATUS(sourceMask)   (0u != (UART_SPI_STATUS_REG & (sourceMask)))


/***************************************
*       SCB Init Macros Definitions
***************************************/

/* UART_CTRL */
#define UART_GET_CTRL_OVS(oversample)   ((((uint32) (oversample)) - 1u) & UART_CTRL_OVS_MASK)

#define UART_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (UART_CTRL_EC_OP_MODE)  : (0u))

#define UART_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (UART_CTRL_EC_AM_MODE)  : (0u))

#define UART_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (UART_CTRL_BLOCK)       : (0u))

#define UART_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (UART_CTRL_ADDR_ACCEPT) : (0u))

/* UART_I2C_CTRL */
#define UART_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        UART_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define UART_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)   (((uint32) (((uint32) (oversampleLow) - 1u) << \
                                                                    UART_I2C_CTRL_LOW_PHASE_OVS_POS)) &  \
                                                                    UART_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define UART_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (UART_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define UART_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32) ((uint32)(mode) << \
                                                                    UART_I2C_CTRL_SLAVE_MODE_POS))

/* UART_SPI_CTRL */
#define UART_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (UART_SPI_CTRL_CONTINUOUS) : (0u))

#define UART_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (UART_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define UART_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) ((uint32) (mode) << \
                                                                        UART_SPI_CTRL_CPHA_POS)) & \
                                                                        UART_SPI_CTRL_SCLK_MODE_MASK)

#define UART_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (UART_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#define UART_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (((uint32) (mode)) << \
                                                                        UART_SPI_CTRL_MODE_POS)) & \
                                                                        UART_SPI_CTRL_MODE_MASK)

#define UART_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) ((uint32) (select) << \
                                                                      UART_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                      UART_SPI_CTRL_SLAVE_SELECT_MASK)

#define UART_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (UART_SPI_CTRL_MASTER) : (0u))

/* UART_UART_CTRL */
#define UART_GET_UART_CTRL_MODE(mode)           (((uint32) ((uint32) (mode) << \
                                                                            UART_UART_CTRL_MODE_POS)) & \
                                                                                UART_UART_CTRL_MODE_MASK)

/* UART_UART_RX_CTRL */
#define UART_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        UART_UART_RX_CTRL_STOP_BITS_MASK)

#define UART_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (UART_UART_RX_CTRL_PARITY) : (0u))

#define UART_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (UART_UART_RX_CTRL_POLARITY) : (0u))

#define UART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (UART_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define UART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (UART_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define UART_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (UART_UART_RX_CTRL_MP_MODE) : (0u))

/* UART_UART_TX_CTRL */
#define UART_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                UART_UART_RX_CTRL_STOP_BITS_MASK)

#define UART_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (UART_UART_TX_CTRL_PARITY) : (0u))

#define UART_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (UART_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* UART_RX_CTRL */
#define UART_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                UART_RX_CTRL_DATA_WIDTH_MASK)

#define UART_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (UART_RX_CTRL_MSB_FIRST) : (0u))

#define UART_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (UART_RX_CTRL_MEDIAN) : (0u))

/* UART_RX_MATCH */
#define UART_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & UART_RX_MATCH_ADDR_MASK)
#define UART_GET_RX_MATCH_MASK(mask)    (((uint32) ((uint32) (mask) << \
                                                            UART_RX_MATCH_MASK_POS)) & \
                                                            UART_RX_MATCH_MASK_MASK)

/* UART_RX_FIFO_CTRL */
#define UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    UART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* UART_TX_CTRL */
#define UART_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                UART_RX_CTRL_DATA_WIDTH_MASK)

#define UART_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (UART_TX_CTRL_MSB_FIRST) : (0u))

/* UART_TX_FIFO_CTRL */
#define UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    UART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* Clears register: configuration and interrupt mask */
#define UART_CLEAR_REG          ((uint32) (0u))
#define UART_NO_INTR_SOURCES    ((uint32) (0u))
#define UART_DUMMY_PARAM        ((uint32) (0u))
#define UART_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case I2C read error */
#define UART_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define UART_CHECK_VALID_BYTE   ((uint32) 0x80000000u)


/***************************************
*       Obsolete definitions
***************************************/

/* The following definitions are for version compatibility.
* They are obsolete in SCB v1_20. Please do not use them in new projects
*/
#define UART_CHECK_INTR_EC_I2C(sourceMask)  UART_CHECK_INTR_I2C_EC(sourceMask)
#define UART_CHECK_INTR_EC_SPI(sourceMask)  UART_CHECK_INTR_SPI_EC(sourceMask)

#endif /* (CY_SCB_UART_H) */


/* [] END OF FILE */
