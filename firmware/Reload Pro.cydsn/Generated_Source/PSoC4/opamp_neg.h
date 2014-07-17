/*******************************************************************************
* File Name: opamp_neg.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_opamp_neg_H) /* Pins opamp_neg_H */
#define CY_PINS_opamp_neg_H

#include "cytypes.h"
#include "cyfitter.h"
#include "opamp_neg_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    opamp_neg_Write(uint8 value) ;
void    opamp_neg_SetDriveMode(uint8 mode) ;
uint8   opamp_neg_ReadDataReg(void) ;
uint8   opamp_neg_Read(void) ;
uint8   opamp_neg_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define opamp_neg_DRIVE_MODE_BITS        (3)
#define opamp_neg_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - opamp_neg_DRIVE_MODE_BITS))
#define opamp_neg_DRIVE_MODE_SHIFT       (0x00u)
#define opamp_neg_DRIVE_MODE_MASK        (0x07u << opamp_neg_DRIVE_MODE_SHIFT)

#define opamp_neg_DM_ALG_HIZ         (0x00u << opamp_neg_DRIVE_MODE_SHIFT)
#define opamp_neg_DM_DIG_HIZ         (0x01u << opamp_neg_DRIVE_MODE_SHIFT)
#define opamp_neg_DM_RES_UP          (0x02u << opamp_neg_DRIVE_MODE_SHIFT)
#define opamp_neg_DM_RES_DWN         (0x03u << opamp_neg_DRIVE_MODE_SHIFT)
#define opamp_neg_DM_OD_LO           (0x04u << opamp_neg_DRIVE_MODE_SHIFT)
#define opamp_neg_DM_OD_HI           (0x05u << opamp_neg_DRIVE_MODE_SHIFT)
#define opamp_neg_DM_STRONG          (0x06u << opamp_neg_DRIVE_MODE_SHIFT)
#define opamp_neg_DM_RES_UPDWN       (0x07u << opamp_neg_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define opamp_neg_MASK               opamp_neg__MASK
#define opamp_neg_SHIFT              opamp_neg__SHIFT
#define opamp_neg_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define opamp_neg_PS                     (* (reg32 *) opamp_neg__PS)
/* Port Configuration */
#define opamp_neg_PC                     (* (reg32 *) opamp_neg__PC)
/* Data Register */
#define opamp_neg_DR                     (* (reg32 *) opamp_neg__DR)
/* Input Buffer Disable Override */
#define opamp_neg_INP_DIS                (* (reg32 *) opamp_neg__PC2)


#if defined(opamp_neg__INTSTAT)  /* Interrupt Registers */

    #define opamp_neg_INTSTAT                (* (reg32 *) opamp_neg__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins opamp_neg_H */


/* [] END OF FILE */
