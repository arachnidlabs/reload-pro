/*******************************************************************************
* File Name: ST7528_1_SS_Reg.h  
* Version 1.70
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_ST7528_1_SS_Reg_H) /* CY_CONTROL_REG_ST7528_1_SS_Reg_H */
#define CY_CONTROL_REG_ST7528_1_SS_Reg_H

#include "cytypes.h"


/***************************************
*         Function Prototypes 
***************************************/

void    ST7528_1_SS_Reg_Write(uint8 control) ;
uint8   ST7528_1_SS_Reg_Read(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define ST7528_1_SS_Reg_Control        (* (reg8 *) ST7528_1_SS_Reg_Sync_ctrl_reg__CONTROL_REG )
#define ST7528_1_SS_Reg_Control_PTR    (  (reg8 *) ST7528_1_SS_Reg_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_ST7528_1_SS_Reg_H */


/* [] END OF FILE */
