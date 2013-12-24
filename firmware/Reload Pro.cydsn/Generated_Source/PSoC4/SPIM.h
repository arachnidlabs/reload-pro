/*******************************************************************************
* File Name: SPIM.h
* Version 2.40
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the SPI Master Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_SPIM_H)
#define CY_SPIM_SPIM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component SPI_Master_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define SPIM_INTERNAL_CLOCK             (1u)

#if(0u != SPIM_INTERNAL_CLOCK)
    #include "SPIM_IntClock.h"
#endif /* (0u != SPIM_INTERNAL_CLOCK) */

#define SPIM_MODE                       (1u)
#define SPIM_DATA_WIDTH                 (8u)
#define SPIM_MODE_USE_ZERO              (1u)
#define SPIM_BIDIRECTIONAL_MODE         (1u)

/* Internal interrupt handling */
#define SPIM_TX_BUFFER_SIZE             (4u)
#define SPIM_RX_BUFFER_SIZE             (4u)
#define SPIM_INTERNAL_TX_INT_ENABLED    (0u)
#define SPIM_INTERNAL_RX_INT_ENABLED    (0u)

#define SPIM_SINGLE_REG_SIZE            (8u)
#define SPIM_USE_SECOND_DATAPATH        (SPIM_DATA_WIDTH > SPIM_SINGLE_REG_SIZE)

#define SPIM_FIFO_SIZE                  (4u)
#define SPIM_TX_SOFTWARE_BUF_ENABLED    ((0u != SPIM_INTERNAL_TX_INT_ENABLED) && \
                                                     (SPIM_TX_BUFFER_SIZE > SPIM_FIFO_SIZE))

#define SPIM_RX_SOFTWARE_BUF_ENABLED    ((0u != SPIM_INTERNAL_RX_INT_ENABLED) && \
                                                     (SPIM_RX_BUFFER_SIZE > SPIM_FIFO_SIZE))


/***************************************
*        Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 cntrPeriod;
    #if(CY_UDB_V0)
        uint8 saveSrTxIntMask;
        uint8 saveSrRxIntMask;
    #endif /* (CY_UDB_V0) */

} SPIM_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  SPIM_Init(void)                           ;
void  SPIM_Enable(void)                         ;
void  SPIM_Start(void)                          ;
void  SPIM_Stop(void)                           ;

void  SPIM_EnableTxInt(void)                    ;
void  SPIM_EnableRxInt(void)                    ;
void  SPIM_DisableTxInt(void)                   ;
void  SPIM_DisableRxInt(void)                   ;

void  SPIM_Sleep(void)                          ;
void  SPIM_Wakeup(void)                         ;
void  SPIM_SaveConfig(void)                     ;
void  SPIM_RestoreConfig(void)                  ;

void  SPIM_SetTxInterruptMode(uint8 intSrc)     ;
void  SPIM_SetRxInterruptMode(uint8 intSrc)     ;
uint8 SPIM_ReadTxStatus(void)                   ;
uint8 SPIM_ReadRxStatus(void)                   ;
void  SPIM_WriteTxData(uint8 txData)  \
                                                            ;
uint8 SPIM_ReadRxData(void) \
                                                            ;
uint8 SPIM_GetRxBufferSize(void)                ;
uint8 SPIM_GetTxBufferSize(void)                ;
void  SPIM_ClearRxBuffer(void)                  ;
void  SPIM_ClearTxBuffer(void)                  ;
void  SPIM_ClearFIFO(void)                              ;
void  SPIM_PutArray(const uint8 buffer[], uint8 byteCount) \
                                                            ;

#if(0u != SPIM_BIDIRECTIONAL_MODE)
    void  SPIM_TxEnable(void)                   ;
    void  SPIM_TxDisable(void)                  ;
#endif /* (0u != SPIM_BIDIRECTIONAL_MODE) */

CY_ISR_PROTO(SPIM_TX_ISR);
CY_ISR_PROTO(SPIM_RX_ISR);


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 SPIM_initVar;


/***************************************
*           API Constants
***************************************/

#define SPIM_TX_ISR_NUMBER     ((uint8) (SPIM_TxInternalInterrupt__INTC_NUMBER))
#define SPIM_RX_ISR_NUMBER     ((uint8) (SPIM_RxInternalInterrupt__INTC_NUMBER))

#define SPIM_TX_ISR_PRIORITY   ((uint8) (SPIM_TxInternalInterrupt__INTC_PRIOR_NUM))
#define SPIM_RX_ISR_PRIORITY   ((uint8) (SPIM_RxInternalInterrupt__INTC_PRIOR_NUM))


/***************************************
*    Initial Parameter Constants
***************************************/

#define SPIM_INT_ON_SPI_DONE    ((uint8) (0u   << SPIM_STS_SPI_DONE_SHIFT))
#define SPIM_INT_ON_TX_EMPTY    ((uint8) (0u   << SPIM_STS_TX_FIFO_EMPTY_SHIFT))
#define SPIM_INT_ON_TX_NOT_FULL ((uint8) (0u << \
                                                                           SPIM_STS_TX_FIFO_NOT_FULL_SHIFT))
#define SPIM_INT_ON_BYTE_COMP   ((uint8) (0u  << SPIM_STS_BYTE_COMPLETE_SHIFT))
#define SPIM_INT_ON_SPI_IDLE    ((uint8) (0u   << SPIM_STS_SPI_IDLE_SHIFT))

/* Disable TX_NOT_FULL if software buffer is used */
#define SPIM_INT_ON_TX_NOT_FULL_DEF ((SPIM_TX_SOFTWARE_BUF_ENABLED) ? \
                                                                        (0u) : (SPIM_INT_ON_TX_NOT_FULL))

/* TX interrupt mask */
#define SPIM_TX_INIT_INTERRUPTS_MASK    (SPIM_INT_ON_SPI_DONE  | \
                                                     SPIM_INT_ON_TX_EMPTY  | \
                                                     SPIM_INT_ON_TX_NOT_FULL_DEF | \
                                                     SPIM_INT_ON_BYTE_COMP | \
                                                     SPIM_INT_ON_SPI_IDLE)

#define SPIM_INT_ON_RX_FULL         ((uint8) (0u << \
                                                                          SPIM_STS_RX_FIFO_FULL_SHIFT))
#define SPIM_INT_ON_RX_NOT_EMPTY    ((uint8) (0u << \
                                                                          SPIM_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define SPIM_INT_ON_RX_OVER         ((uint8) (0u << \
                                                                          SPIM_STS_RX_FIFO_OVERRUN_SHIFT))

/* RX interrupt mask */
#define SPIM_RX_INIT_INTERRUPTS_MASK    (SPIM_INT_ON_RX_FULL      | \
                                                     SPIM_INT_ON_RX_NOT_EMPTY | \
                                                     SPIM_INT_ON_RX_OVER)
/* Nubmer of bits to receive/transmit */
#define SPIM_BITCTR_INIT            (((uint8) (SPIM_DATA_WIDTH << 1u)) - 1u)


/***************************************
*             Registers
***************************************/

#if(CY_PSOC3 || CY_PSOC5)
    #define SPIM_TXDATA_REG (* (reg8 *) \
                                                SPIM_BSPIM_sR8_Dp_u0__F0_REG)
    #define SPIM_TXDATA_PTR (  (reg8 *) \
                                                SPIM_BSPIM_sR8_Dp_u0__F0_REG)
    #define SPIM_RXDATA_REG (* (reg8 *) \
                                                SPIM_BSPIM_sR8_Dp_u0__F1_REG)
    #define SPIM_RXDATA_PTR (  (reg8 *) \
                                                SPIM_BSPIM_sR8_Dp_u0__F1_REG)
#else   /* PSOC4 */
    #if(SPIM_USE_SECOND_DATAPATH)
        #define SPIM_TXDATA_REG (* (reg16 *) \
                                          SPIM_BSPIM_sR8_Dp_u0__16BIT_F0_REG)
        #define SPIM_TXDATA_PTR (  (reg16 *) \
                                          SPIM_BSPIM_sR8_Dp_u0__16BIT_F0_REG)
        #define SPIM_RXDATA_REG (* (reg16 *) \
                                          SPIM_BSPIM_sR8_Dp_u0__16BIT_F1_REG)
        #define SPIM_RXDATA_PTR         (  (reg16 *) \
                                          SPIM_BSPIM_sR8_Dp_u0__16BIT_F1_REG)
    #else
        #define SPIM_TXDATA_REG (* (reg8 *) \
                                                SPIM_BSPIM_sR8_Dp_u0__F0_REG)
        #define SPIM_TXDATA_PTR (  (reg8 *) \
                                                SPIM_BSPIM_sR8_Dp_u0__F0_REG)
        #define SPIM_RXDATA_REG (* (reg8 *) \
                                                SPIM_BSPIM_sR8_Dp_u0__F1_REG)
        #define SPIM_RXDATA_PTR (  (reg8 *) \
                                                SPIM_BSPIM_sR8_Dp_u0__F1_REG)
    #endif /* (SPIM_USE_SECOND_DATAPATH) */
#endif     /* (CY_PSOC3 || CY_PSOC5) */

#define SPIM_AUX_CONTROL_DP0_REG (* (reg8 *) \
                                        SPIM_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG)
#define SPIM_AUX_CONTROL_DP0_PTR (  (reg8 *) \
                                        SPIM_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG)

#if(SPIM_USE_SECOND_DATAPATH)
    #define SPIM_AUX_CONTROL_DP1_REG  (* (reg8 *) \
                                        SPIM_BSPIM_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define SPIM_AUX_CONTROL_DP1_PTR  (  (reg8 *) \
                                        SPIM_BSPIM_sR8_Dp_u1__DP_AUX_CTL_REG)
#endif /* (SPIM_USE_SECOND_DATAPATH) */

#define SPIM_COUNTER_PERIOD_REG     (* (reg8 *) SPIM_BSPIM_BitCounter__PERIOD_REG)
#define SPIM_COUNTER_PERIOD_PTR     (  (reg8 *) SPIM_BSPIM_BitCounter__PERIOD_REG)
#define SPIM_COUNTER_CONTROL_REG    (* (reg8 *) SPIM_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)
#define SPIM_COUNTER_CONTROL_PTR    (  (reg8 *) SPIM_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)

#define SPIM_TX_STATUS_REG          (* (reg8 *) SPIM_BSPIM_TxStsReg__STATUS_REG)
#define SPIM_TX_STATUS_PTR          (  (reg8 *) SPIM_BSPIM_TxStsReg__STATUS_REG)
#define SPIM_RX_STATUS_REG          (* (reg8 *) SPIM_BSPIM_RxStsReg__STATUS_REG)
#define SPIM_RX_STATUS_PTR          (  (reg8 *) SPIM_BSPIM_RxStsReg__STATUS_REG)

#define SPIM_CONTROL_REG            (* (reg8 *) \
                                      SPIM_BSPIM_BidirMode_SyncCtl_CtrlReg__CONTROL_REG)
#define SPIM_CONTROL_PTR            (  (reg8 *) \
                                      SPIM_BSPIM_BidirMode_SyncCtl_CtrlReg__CONTROL_REG)

#define SPIM_TX_STATUS_MASK_REG     (* (reg8 *) SPIM_BSPIM_TxStsReg__MASK_REG)
#define SPIM_TX_STATUS_MASK_PTR     (  (reg8 *) SPIM_BSPIM_TxStsReg__MASK_REG)
#define SPIM_RX_STATUS_MASK_REG     (* (reg8 *) SPIM_BSPIM_RxStsReg__MASK_REG)
#define SPIM_RX_STATUS_MASK_PTR     (  (reg8 *) SPIM_BSPIM_RxStsReg__MASK_REG)

#define SPIM_TX_STATUS_ACTL_REG     (* (reg8 *) SPIM_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define SPIM_TX_STATUS_ACTL_PTR     (  (reg8 *) SPIM_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define SPIM_RX_STATUS_ACTL_REG     (* (reg8 *) SPIM_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)
#define SPIM_RX_STATUS_ACTL_PTR     (  (reg8 *) SPIM_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)

#if(SPIM_USE_SECOND_DATAPATH)
    #define SPIM_AUX_CONTROLDP1     (SPIM_AUX_CONTROL_DP1_REG)
#endif /* (SPIM_USE_SECOND_DATAPATH) */


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define SPIM_STS_SPI_DONE_SHIFT             (0x00u)
#define SPIM_STS_TX_FIFO_EMPTY_SHIFT        (0x01u)
#define SPIM_STS_TX_FIFO_NOT_FULL_SHIFT     (0x02u)
#define SPIM_STS_BYTE_COMPLETE_SHIFT        (0x03u)
#define SPIM_STS_SPI_IDLE_SHIFT             (0x04u)
#define SPIM_STS_RX_FIFO_FULL_SHIFT         (0x04u)
#define SPIM_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x05u)
#define SPIM_STS_RX_FIFO_OVERRUN_SHIFT      (0x06u)

#define SPIM_STS_SPI_DONE           ((uint8) (0x01u << SPIM_STS_SPI_DONE_SHIFT))
#define SPIM_STS_TX_FIFO_EMPTY      ((uint8) (0x01u << SPIM_STS_TX_FIFO_EMPTY_SHIFT))
#define SPIM_STS_TX_FIFO_NOT_FULL   ((uint8) (0x01u << SPIM_STS_TX_FIFO_NOT_FULL_SHIFT))
#define SPIM_STS_BYTE_COMPLETE      ((uint8) (0x01u << SPIM_STS_BYTE_COMPLETE_SHIFT))
#define SPIM_STS_SPI_IDLE           ((uint8) (0x01u << SPIM_STS_SPI_IDLE_SHIFT))
#define SPIM_STS_RX_FIFO_FULL       ((uint8) (0x01u << SPIM_STS_RX_FIFO_FULL_SHIFT))
#define SPIM_STS_RX_FIFO_NOT_EMPTY  ((uint8) (0x01u << SPIM_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define SPIM_STS_RX_FIFO_OVERRUN    ((uint8) (0x01u << SPIM_STS_RX_FIFO_OVERRUN_SHIFT))

/* TX and RX masks for clear on read bits */
#define SPIM_TX_STS_CLR_ON_RD_BYTES_MASK    (0x09u)
#define SPIM_RX_STS_CLR_ON_RD_BYTES_MASK    (0x40u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define SPIM_INT_ENABLE     (0x10u) /* Enable interrupt from statusi */
#define SPIM_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define SPIM_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define SPIM_FIFO_CLR       (SPIM_TX_FIFO_CLR | SPIM_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define SPIM_CNTR_ENABLE    (0x20u) /* Enable CNT7 */

/* Bi-Directional mode control bit */
#define SPIM_CTRL_TX_SIGNAL_EN  (0x01u)

/* Datapath Auxillary Control Register definitions */
#define SPIM_AUX_CTRL_FIFO0_CLR         (0x01u)
#define SPIM_AUX_CTRL_FIFO1_CLR         (0x02u)
#define SPIM_AUX_CTRL_FIFO0_LVL         (0x04u)
#define SPIM_AUX_CTRL_FIFO1_LVL         (0x08u)
#define SPIM_STATUS_ACTL_INT_EN_MASK    (0x10u)

/* Component disabled */
#define SPIM_DISABLED   (0u)


/***************************************
*       Macros
***************************************/

/* Returns true if componentn enabled */
#define SPIM_IS_ENABLED (0u != (SPIM_TX_STATUS_ACTL_REG & SPIM_INT_ENABLE))

/* Retuns TX status register */
#define SPIM_GET_STATUS_TX(swTxSts) ( (uint8)(SPIM_TX_STATUS_REG | \
                                                          ((swTxSts) & SPIM_TX_STS_CLR_ON_RD_BYTES_MASK)) )
/* Retuns RX status register */
#define SPIM_GET_STATUS_RX(swRxSts) ( (uint8)(SPIM_RX_STATUS_REG | \
                                                          ((swRxSts) & SPIM_RX_STS_CLR_ON_RD_BYTES_MASK)) )


/***************************************
*       Obsolete definitions
***************************************/

/* Following definitions are for version compatibility.
*  They are obsolete in SPIM v2_30.
*  Please do not use it in new projects
*/

#define SPIM_WriteByte   SPIM_WriteTxData
#define SPIM_ReadByte    SPIM_ReadRxData
void  SPIM_SetInterruptMode(uint8 intSrc)       ;
uint8 SPIM_ReadStatus(void)                     ;
void  SPIM_EnableInt(void)                      ;
void  SPIM_DisableInt(void)                     ;

/* Obsolete register names. Not to be used in new designs */
#define SPIM_TXDATA                 (SPIM_TXDATA_REG)
#define SPIM_RXDATA                 (SPIM_RXDATA_REG)
#define SPIM_AUX_CONTROLDP0         (SPIM_AUX_CONTROL_DP0_REG)
#define SPIM_TXBUFFERREAD           (SPIM_txBufferRead)
#define SPIM_TXBUFFERWRITE          (SPIM_txBufferWrite)
#define SPIM_RXBUFFERREAD           (SPIM_rxBufferRead)
#define SPIM_RXBUFFERWRITE          (SPIM_rxBufferWrite)

#define SPIM_COUNTER_PERIOD         (SPIM_COUNTER_PERIOD_REG)
#define SPIM_COUNTER_CONTROL        (SPIM_COUNTER_CONTROL_REG)
#define SPIM_STATUS                 (SPIM_TX_STATUS_REG)
#define SPIM_CONTROL                (SPIM_CONTROL_REG)
#define SPIM_STATUS_MASK            (SPIM_TX_STATUS_MASK_REG)
#define SPIM_STATUS_ACTL            (SPIM_TX_STATUS_ACTL_REG)

#define SPIM_INIT_INTERRUPTS_MASK  (SPIM_INT_ON_SPI_DONE     | \
                                                SPIM_INT_ON_TX_EMPTY     | \
                                                SPIM_INT_ON_TX_NOT_FULL_DEF  | \
                                                SPIM_INT_ON_RX_FULL      | \
                                                SPIM_INT_ON_RX_NOT_EMPTY | \
                                                SPIM_INT_ON_RX_OVER      | \
                                                SPIM_INT_ON_BYTE_COMP)
                                                
/* Following definitions are for version Compatibility.
*  They are obsolete in SPIM v2_40.
*  Please do not use it in new projects
*/

#define SPIM_DataWidth                  (SPIM_DATA_WIDTH)
#define SPIM_InternalClockUsed          (SPIM_INTERNAL_CLOCK)
#define SPIM_InternalTxInterruptEnabled (SPIM_INTERNAL_TX_INT_ENABLED)
#define SPIM_InternalRxInterruptEnabled (SPIM_INTERNAL_RX_INT_ENABLED)
#define SPIM_ModeUseZero                (SPIM_MODE_USE_ZERO)
#define SPIM_BidirectionalMode          (SPIM_BIDIRECTIONAL_MODE)
#define SPIM_Mode                       (SPIM_MODE)
#define SPIM_DATAWIDHT                  (SPIM_DATA_WIDTH)
#define SPIM_InternalInterruptEnabled   (0u)

#define SPIM_TXBUFFERSIZE   (SPIM_TX_BUFFER_SIZE)
#define SPIM_RXBUFFERSIZE   (SPIM_RX_BUFFER_SIZE)

#define SPIM_TXBUFFER       SPIM_txBuffer
#define SPIM_RXBUFFER       SPIM_rxBuffer

#endif /* (CY_SPIM_SPIM_H) */


/* [] END OF FILE */
