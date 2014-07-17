/*******************************************************************************
* File Name: ST7528_1_SPI.h
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

#if !defined(CY_SPIM_ST7528_1_SPI_H)
#define CY_SPIM_ST7528_1_SPI_H

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

#define ST7528_1_SPI_INTERNAL_CLOCK             (0u)

#if(0u != ST7528_1_SPI_INTERNAL_CLOCK)
    #include "ST7528_1_SPI_IntClock.h"
#endif /* (0u != ST7528_1_SPI_INTERNAL_CLOCK) */

#define ST7528_1_SPI_MODE                       (1u)
#define ST7528_1_SPI_DATA_WIDTH                 (8u)
#define ST7528_1_SPI_MODE_USE_ZERO              (1u)
#define ST7528_1_SPI_BIDIRECTIONAL_MODE         (0u)

/* Internal interrupt handling */
#define ST7528_1_SPI_TX_BUFFER_SIZE             (4u)
#define ST7528_1_SPI_RX_BUFFER_SIZE             (4u)
#define ST7528_1_SPI_INTERNAL_TX_INT_ENABLED    (0u)
#define ST7528_1_SPI_INTERNAL_RX_INT_ENABLED    (0u)

#define ST7528_1_SPI_SINGLE_REG_SIZE            (8u)
#define ST7528_1_SPI_USE_SECOND_DATAPATH        (ST7528_1_SPI_DATA_WIDTH > ST7528_1_SPI_SINGLE_REG_SIZE)

#define ST7528_1_SPI_FIFO_SIZE                  (4u)
#define ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED    ((0u != ST7528_1_SPI_INTERNAL_TX_INT_ENABLED) && \
                                                     (ST7528_1_SPI_TX_BUFFER_SIZE > ST7528_1_SPI_FIFO_SIZE))

#define ST7528_1_SPI_RX_SOFTWARE_BUF_ENABLED    ((0u != ST7528_1_SPI_INTERNAL_RX_INT_ENABLED) && \
                                                     (ST7528_1_SPI_RX_BUFFER_SIZE > ST7528_1_SPI_FIFO_SIZE))


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

} ST7528_1_SPI_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  ST7528_1_SPI_Init(void)                           ;
void  ST7528_1_SPI_Enable(void)                         ;
void  ST7528_1_SPI_Start(void)                          ;
void  ST7528_1_SPI_Stop(void)                           ;

void  ST7528_1_SPI_EnableTxInt(void)                    ;
void  ST7528_1_SPI_EnableRxInt(void)                    ;
void  ST7528_1_SPI_DisableTxInt(void)                   ;
void  ST7528_1_SPI_DisableRxInt(void)                   ;

void  ST7528_1_SPI_Sleep(void)                          ;
void  ST7528_1_SPI_Wakeup(void)                         ;
void  ST7528_1_SPI_SaveConfig(void)                     ;
void  ST7528_1_SPI_RestoreConfig(void)                  ;

void  ST7528_1_SPI_SetTxInterruptMode(uint8 intSrc)     ;
void  ST7528_1_SPI_SetRxInterruptMode(uint8 intSrc)     ;
uint8 ST7528_1_SPI_ReadTxStatus(void)                   ;
uint8 ST7528_1_SPI_ReadRxStatus(void)                   ;
void  ST7528_1_SPI_WriteTxData(uint8 txData)  \
                                                            ;
uint8 ST7528_1_SPI_ReadRxData(void) \
                                                            ;
uint8 ST7528_1_SPI_GetRxBufferSize(void)                ;
uint8 ST7528_1_SPI_GetTxBufferSize(void)                ;
void  ST7528_1_SPI_ClearRxBuffer(void)                  ;
void  ST7528_1_SPI_ClearTxBuffer(void)                  ;
void  ST7528_1_SPI_ClearFIFO(void)                              ;
void  ST7528_1_SPI_PutArray(const uint8 buffer[], uint8 byteCount) \
                                                            ;

#if(0u != ST7528_1_SPI_BIDIRECTIONAL_MODE)
    void  ST7528_1_SPI_TxEnable(void)                   ;
    void  ST7528_1_SPI_TxDisable(void)                  ;
#endif /* (0u != ST7528_1_SPI_BIDIRECTIONAL_MODE) */

CY_ISR_PROTO(ST7528_1_SPI_TX_ISR);
CY_ISR_PROTO(ST7528_1_SPI_RX_ISR);


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 ST7528_1_SPI_initVar;


/***************************************
*           API Constants
***************************************/

#define ST7528_1_SPI_TX_ISR_NUMBER     ((uint8) (ST7528_1_SPI_TxInternalInterrupt__INTC_NUMBER))
#define ST7528_1_SPI_RX_ISR_NUMBER     ((uint8) (ST7528_1_SPI_RxInternalInterrupt__INTC_NUMBER))

#define ST7528_1_SPI_TX_ISR_PRIORITY   ((uint8) (ST7528_1_SPI_TxInternalInterrupt__INTC_PRIOR_NUM))
#define ST7528_1_SPI_RX_ISR_PRIORITY   ((uint8) (ST7528_1_SPI_RxInternalInterrupt__INTC_PRIOR_NUM))


/***************************************
*    Initial Parameter Constants
***************************************/

#define ST7528_1_SPI_INT_ON_SPI_DONE    ((uint8) (0u   << ST7528_1_SPI_STS_SPI_DONE_SHIFT))
#define ST7528_1_SPI_INT_ON_TX_EMPTY    ((uint8) (0u   << ST7528_1_SPI_STS_TX_FIFO_EMPTY_SHIFT))
#define ST7528_1_SPI_INT_ON_TX_NOT_FULL ((uint8) (0u << \
                                                                           ST7528_1_SPI_STS_TX_FIFO_NOT_FULL_SHIFT))
#define ST7528_1_SPI_INT_ON_BYTE_COMP   ((uint8) (0u  << ST7528_1_SPI_STS_BYTE_COMPLETE_SHIFT))
#define ST7528_1_SPI_INT_ON_SPI_IDLE    ((uint8) (0u   << ST7528_1_SPI_STS_SPI_IDLE_SHIFT))

/* Disable TX_NOT_FULL if software buffer is used */
#define ST7528_1_SPI_INT_ON_TX_NOT_FULL_DEF ((ST7528_1_SPI_TX_SOFTWARE_BUF_ENABLED) ? \
                                                                        (0u) : (ST7528_1_SPI_INT_ON_TX_NOT_FULL))

/* TX interrupt mask */
#define ST7528_1_SPI_TX_INIT_INTERRUPTS_MASK    (ST7528_1_SPI_INT_ON_SPI_DONE  | \
                                                     ST7528_1_SPI_INT_ON_TX_EMPTY  | \
                                                     ST7528_1_SPI_INT_ON_TX_NOT_FULL_DEF | \
                                                     ST7528_1_SPI_INT_ON_BYTE_COMP | \
                                                     ST7528_1_SPI_INT_ON_SPI_IDLE)

#define ST7528_1_SPI_INT_ON_RX_FULL         ((uint8) (0u << \
                                                                          ST7528_1_SPI_STS_RX_FIFO_FULL_SHIFT))
#define ST7528_1_SPI_INT_ON_RX_NOT_EMPTY    ((uint8) (0u << \
                                                                          ST7528_1_SPI_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define ST7528_1_SPI_INT_ON_RX_OVER         ((uint8) (0u << \
                                                                          ST7528_1_SPI_STS_RX_FIFO_OVERRUN_SHIFT))

/* RX interrupt mask */
#define ST7528_1_SPI_RX_INIT_INTERRUPTS_MASK    (ST7528_1_SPI_INT_ON_RX_FULL      | \
                                                     ST7528_1_SPI_INT_ON_RX_NOT_EMPTY | \
                                                     ST7528_1_SPI_INT_ON_RX_OVER)
/* Nubmer of bits to receive/transmit */
#define ST7528_1_SPI_BITCTR_INIT            (((uint8) (ST7528_1_SPI_DATA_WIDTH << 1u)) - 1u)


/***************************************
*             Registers
***************************************/

#if(CY_PSOC3 || CY_PSOC5)
    #define ST7528_1_SPI_TXDATA_REG (* (reg8 *) \
                                                ST7528_1_SPI_BSPIM_sR8_Dp_u0__F0_REG)
    #define ST7528_1_SPI_TXDATA_PTR (  (reg8 *) \
                                                ST7528_1_SPI_BSPIM_sR8_Dp_u0__F0_REG)
    #define ST7528_1_SPI_RXDATA_REG (* (reg8 *) \
                                                ST7528_1_SPI_BSPIM_sR8_Dp_u0__F1_REG)
    #define ST7528_1_SPI_RXDATA_PTR (  (reg8 *) \
                                                ST7528_1_SPI_BSPIM_sR8_Dp_u0__F1_REG)
#else   /* PSOC4 */
    #if(ST7528_1_SPI_USE_SECOND_DATAPATH)
        #define ST7528_1_SPI_TXDATA_REG (* (reg16 *) \
                                          ST7528_1_SPI_BSPIM_sR8_Dp_u0__16BIT_F0_REG)
        #define ST7528_1_SPI_TXDATA_PTR (  (reg16 *) \
                                          ST7528_1_SPI_BSPIM_sR8_Dp_u0__16BIT_F0_REG)
        #define ST7528_1_SPI_RXDATA_REG (* (reg16 *) \
                                          ST7528_1_SPI_BSPIM_sR8_Dp_u0__16BIT_F1_REG)
        #define ST7528_1_SPI_RXDATA_PTR         (  (reg16 *) \
                                          ST7528_1_SPI_BSPIM_sR8_Dp_u0__16BIT_F1_REG)
    #else
        #define ST7528_1_SPI_TXDATA_REG (* (reg8 *) \
                                                ST7528_1_SPI_BSPIM_sR8_Dp_u0__F0_REG)
        #define ST7528_1_SPI_TXDATA_PTR (  (reg8 *) \
                                                ST7528_1_SPI_BSPIM_sR8_Dp_u0__F0_REG)
        #define ST7528_1_SPI_RXDATA_REG (* (reg8 *) \
                                                ST7528_1_SPI_BSPIM_sR8_Dp_u0__F1_REG)
        #define ST7528_1_SPI_RXDATA_PTR (  (reg8 *) \
                                                ST7528_1_SPI_BSPIM_sR8_Dp_u0__F1_REG)
    #endif /* (ST7528_1_SPI_USE_SECOND_DATAPATH) */
#endif     /* (CY_PSOC3 || CY_PSOC5) */

#define ST7528_1_SPI_AUX_CONTROL_DP0_REG (* (reg8 *) \
                                        ST7528_1_SPI_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG)
#define ST7528_1_SPI_AUX_CONTROL_DP0_PTR (  (reg8 *) \
                                        ST7528_1_SPI_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG)

#if(ST7528_1_SPI_USE_SECOND_DATAPATH)
    #define ST7528_1_SPI_AUX_CONTROL_DP1_REG  (* (reg8 *) \
                                        ST7528_1_SPI_BSPIM_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define ST7528_1_SPI_AUX_CONTROL_DP1_PTR  (  (reg8 *) \
                                        ST7528_1_SPI_BSPIM_sR8_Dp_u1__DP_AUX_CTL_REG)
#endif /* (ST7528_1_SPI_USE_SECOND_DATAPATH) */

#define ST7528_1_SPI_COUNTER_PERIOD_REG     (* (reg8 *) ST7528_1_SPI_BSPIM_BitCounter__PERIOD_REG)
#define ST7528_1_SPI_COUNTER_PERIOD_PTR     (  (reg8 *) ST7528_1_SPI_BSPIM_BitCounter__PERIOD_REG)
#define ST7528_1_SPI_COUNTER_CONTROL_REG    (* (reg8 *) ST7528_1_SPI_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)
#define ST7528_1_SPI_COUNTER_CONTROL_PTR    (  (reg8 *) ST7528_1_SPI_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)

#define ST7528_1_SPI_TX_STATUS_REG          (* (reg8 *) ST7528_1_SPI_BSPIM_TxStsReg__STATUS_REG)
#define ST7528_1_SPI_TX_STATUS_PTR          (  (reg8 *) ST7528_1_SPI_BSPIM_TxStsReg__STATUS_REG)
#define ST7528_1_SPI_RX_STATUS_REG          (* (reg8 *) ST7528_1_SPI_BSPIM_RxStsReg__STATUS_REG)
#define ST7528_1_SPI_RX_STATUS_PTR          (  (reg8 *) ST7528_1_SPI_BSPIM_RxStsReg__STATUS_REG)

#define ST7528_1_SPI_CONTROL_REG            (* (reg8 *) \
                                      ST7528_1_SPI_BSPIM_BidirMode_SyncCtl_CtrlReg__CONTROL_REG)
#define ST7528_1_SPI_CONTROL_PTR            (  (reg8 *) \
                                      ST7528_1_SPI_BSPIM_BidirMode_SyncCtl_CtrlReg__CONTROL_REG)

#define ST7528_1_SPI_TX_STATUS_MASK_REG     (* (reg8 *) ST7528_1_SPI_BSPIM_TxStsReg__MASK_REG)
#define ST7528_1_SPI_TX_STATUS_MASK_PTR     (  (reg8 *) ST7528_1_SPI_BSPIM_TxStsReg__MASK_REG)
#define ST7528_1_SPI_RX_STATUS_MASK_REG     (* (reg8 *) ST7528_1_SPI_BSPIM_RxStsReg__MASK_REG)
#define ST7528_1_SPI_RX_STATUS_MASK_PTR     (  (reg8 *) ST7528_1_SPI_BSPIM_RxStsReg__MASK_REG)

#define ST7528_1_SPI_TX_STATUS_ACTL_REG     (* (reg8 *) ST7528_1_SPI_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define ST7528_1_SPI_TX_STATUS_ACTL_PTR     (  (reg8 *) ST7528_1_SPI_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define ST7528_1_SPI_RX_STATUS_ACTL_REG     (* (reg8 *) ST7528_1_SPI_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)
#define ST7528_1_SPI_RX_STATUS_ACTL_PTR     (  (reg8 *) ST7528_1_SPI_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)

#if(ST7528_1_SPI_USE_SECOND_DATAPATH)
    #define ST7528_1_SPI_AUX_CONTROLDP1     (ST7528_1_SPI_AUX_CONTROL_DP1_REG)
#endif /* (ST7528_1_SPI_USE_SECOND_DATAPATH) */


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define ST7528_1_SPI_STS_SPI_DONE_SHIFT             (0x00u)
#define ST7528_1_SPI_STS_TX_FIFO_EMPTY_SHIFT        (0x01u)
#define ST7528_1_SPI_STS_TX_FIFO_NOT_FULL_SHIFT     (0x02u)
#define ST7528_1_SPI_STS_BYTE_COMPLETE_SHIFT        (0x03u)
#define ST7528_1_SPI_STS_SPI_IDLE_SHIFT             (0x04u)
#define ST7528_1_SPI_STS_RX_FIFO_FULL_SHIFT         (0x04u)
#define ST7528_1_SPI_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x05u)
#define ST7528_1_SPI_STS_RX_FIFO_OVERRUN_SHIFT      (0x06u)

#define ST7528_1_SPI_STS_SPI_DONE           ((uint8) (0x01u << ST7528_1_SPI_STS_SPI_DONE_SHIFT))
#define ST7528_1_SPI_STS_TX_FIFO_EMPTY      ((uint8) (0x01u << ST7528_1_SPI_STS_TX_FIFO_EMPTY_SHIFT))
#define ST7528_1_SPI_STS_TX_FIFO_NOT_FULL   ((uint8) (0x01u << ST7528_1_SPI_STS_TX_FIFO_NOT_FULL_SHIFT))
#define ST7528_1_SPI_STS_BYTE_COMPLETE      ((uint8) (0x01u << ST7528_1_SPI_STS_BYTE_COMPLETE_SHIFT))
#define ST7528_1_SPI_STS_SPI_IDLE           ((uint8) (0x01u << ST7528_1_SPI_STS_SPI_IDLE_SHIFT))
#define ST7528_1_SPI_STS_RX_FIFO_FULL       ((uint8) (0x01u << ST7528_1_SPI_STS_RX_FIFO_FULL_SHIFT))
#define ST7528_1_SPI_STS_RX_FIFO_NOT_EMPTY  ((uint8) (0x01u << ST7528_1_SPI_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define ST7528_1_SPI_STS_RX_FIFO_OVERRUN    ((uint8) (0x01u << ST7528_1_SPI_STS_RX_FIFO_OVERRUN_SHIFT))

/* TX and RX masks for clear on read bits */
#define ST7528_1_SPI_TX_STS_CLR_ON_RD_BYTES_MASK    (0x09u)
#define ST7528_1_SPI_RX_STS_CLR_ON_RD_BYTES_MASK    (0x40u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define ST7528_1_SPI_INT_ENABLE     (0x10u) /* Enable interrupt from statusi */
#define ST7528_1_SPI_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define ST7528_1_SPI_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define ST7528_1_SPI_FIFO_CLR       (ST7528_1_SPI_TX_FIFO_CLR | ST7528_1_SPI_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define ST7528_1_SPI_CNTR_ENABLE    (0x20u) /* Enable CNT7 */

/* Bi-Directional mode control bit */
#define ST7528_1_SPI_CTRL_TX_SIGNAL_EN  (0x01u)

/* Datapath Auxillary Control Register definitions */
#define ST7528_1_SPI_AUX_CTRL_FIFO0_CLR         (0x01u)
#define ST7528_1_SPI_AUX_CTRL_FIFO1_CLR         (0x02u)
#define ST7528_1_SPI_AUX_CTRL_FIFO0_LVL         (0x04u)
#define ST7528_1_SPI_AUX_CTRL_FIFO1_LVL         (0x08u)
#define ST7528_1_SPI_STATUS_ACTL_INT_EN_MASK    (0x10u)

/* Component disabled */
#define ST7528_1_SPI_DISABLED   (0u)


/***************************************
*       Macros
***************************************/

/* Returns true if componentn enabled */
#define ST7528_1_SPI_IS_ENABLED (0u != (ST7528_1_SPI_TX_STATUS_ACTL_REG & ST7528_1_SPI_INT_ENABLE))

/* Retuns TX status register */
#define ST7528_1_SPI_GET_STATUS_TX(swTxSts) ( (uint8)(ST7528_1_SPI_TX_STATUS_REG | \
                                                          ((swTxSts) & ST7528_1_SPI_TX_STS_CLR_ON_RD_BYTES_MASK)) )
/* Retuns RX status register */
#define ST7528_1_SPI_GET_STATUS_RX(swRxSts) ( (uint8)(ST7528_1_SPI_RX_STATUS_REG | \
                                                          ((swRxSts) & ST7528_1_SPI_RX_STS_CLR_ON_RD_BYTES_MASK)) )


/***************************************
*       Obsolete definitions
***************************************/

/* Following definitions are for version compatibility.
*  They are obsolete in SPIM v2_30.
*  Please do not use it in new projects
*/

#define ST7528_1_SPI_WriteByte   ST7528_1_SPI_WriteTxData
#define ST7528_1_SPI_ReadByte    ST7528_1_SPI_ReadRxData
void  ST7528_1_SPI_SetInterruptMode(uint8 intSrc)       ;
uint8 ST7528_1_SPI_ReadStatus(void)                     ;
void  ST7528_1_SPI_EnableInt(void)                      ;
void  ST7528_1_SPI_DisableInt(void)                     ;

/* Obsolete register names. Not to be used in new designs */
#define ST7528_1_SPI_TXDATA                 (ST7528_1_SPI_TXDATA_REG)
#define ST7528_1_SPI_RXDATA                 (ST7528_1_SPI_RXDATA_REG)
#define ST7528_1_SPI_AUX_CONTROLDP0         (ST7528_1_SPI_AUX_CONTROL_DP0_REG)
#define ST7528_1_SPI_TXBUFFERREAD           (ST7528_1_SPI_txBufferRead)
#define ST7528_1_SPI_TXBUFFERWRITE          (ST7528_1_SPI_txBufferWrite)
#define ST7528_1_SPI_RXBUFFERREAD           (ST7528_1_SPI_rxBufferRead)
#define ST7528_1_SPI_RXBUFFERWRITE          (ST7528_1_SPI_rxBufferWrite)

#define ST7528_1_SPI_COUNTER_PERIOD         (ST7528_1_SPI_COUNTER_PERIOD_REG)
#define ST7528_1_SPI_COUNTER_CONTROL        (ST7528_1_SPI_COUNTER_CONTROL_REG)
#define ST7528_1_SPI_STATUS                 (ST7528_1_SPI_TX_STATUS_REG)
#define ST7528_1_SPI_CONTROL                (ST7528_1_SPI_CONTROL_REG)
#define ST7528_1_SPI_STATUS_MASK            (ST7528_1_SPI_TX_STATUS_MASK_REG)
#define ST7528_1_SPI_STATUS_ACTL            (ST7528_1_SPI_TX_STATUS_ACTL_REG)

#define ST7528_1_SPI_INIT_INTERRUPTS_MASK  (ST7528_1_SPI_INT_ON_SPI_DONE     | \
                                                ST7528_1_SPI_INT_ON_TX_EMPTY     | \
                                                ST7528_1_SPI_INT_ON_TX_NOT_FULL_DEF  | \
                                                ST7528_1_SPI_INT_ON_RX_FULL      | \
                                                ST7528_1_SPI_INT_ON_RX_NOT_EMPTY | \
                                                ST7528_1_SPI_INT_ON_RX_OVER      | \
                                                ST7528_1_SPI_INT_ON_BYTE_COMP)
                                                
/* Following definitions are for version Compatibility.
*  They are obsolete in SPIM v2_40.
*  Please do not use it in new projects
*/

#define ST7528_1_SPI_DataWidth                  (ST7528_1_SPI_DATA_WIDTH)
#define ST7528_1_SPI_InternalClockUsed          (ST7528_1_SPI_INTERNAL_CLOCK)
#define ST7528_1_SPI_InternalTxInterruptEnabled (ST7528_1_SPI_INTERNAL_TX_INT_ENABLED)
#define ST7528_1_SPI_InternalRxInterruptEnabled (ST7528_1_SPI_INTERNAL_RX_INT_ENABLED)
#define ST7528_1_SPI_ModeUseZero                (ST7528_1_SPI_MODE_USE_ZERO)
#define ST7528_1_SPI_BidirectionalMode          (ST7528_1_SPI_BIDIRECTIONAL_MODE)
#define ST7528_1_SPI_Mode                       (ST7528_1_SPI_MODE)
#define ST7528_1_SPI_DATAWIDHT                  (ST7528_1_SPI_DATA_WIDTH)
#define ST7528_1_SPI_InternalInterruptEnabled   (0u)

#define ST7528_1_SPI_TXBUFFERSIZE   (ST7528_1_SPI_TX_BUFFER_SIZE)
#define ST7528_1_SPI_RXBUFFERSIZE   (ST7528_1_SPI_RX_BUFFER_SIZE)

#define ST7528_1_SPI_TXBUFFER       ST7528_1_SPI_txBuffer
#define ST7528_1_SPI_RXBUFFER       ST7528_1_SPI_rxBuffer

#endif /* (CY_SPIM_ST7528_1_SPI_H) */


/* [] END OF FILE */
