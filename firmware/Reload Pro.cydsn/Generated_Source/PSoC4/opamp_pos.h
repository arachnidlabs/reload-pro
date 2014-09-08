/*******************************************************************************
* File Name: opamp_pos.h  
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

#if !defined(CY_PINS_opamp_pos_H) /* Pins opamp_pos_H */
#define CY_PINS_opamp_pos_H

#include "cytypes.h"
#include "cyfitter.h"
#include "opamp_pos_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    opamp_pos_Write(uint8 value) ;
void    opamp_pos_SetDriveMode(uint8 mode) ;
uint8   opamp_pos_ReadDataReg(void) ;
uint8   opamp_pos_Read(void) ;
uint8   opamp_pos_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define opamp_pos_DRIVE_MODE_BITS        (3)
#define opamp_pos_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - opamp_pos_DRIVE_MODE_BITS))
#define opamp_pos_DRIVE_MODE_SHIFT       (0x00u)
#define opamp_pos_DRIVE_MODE_MASK        (0x07u << opamp_pos_DRIVE_MODE_SHIFT)

#define opamp_pos_DM_ALG_HIZ         (0x00u << opamp_pos_DRIVE_MODE_SHIFT)
#define opamp_pos_DM_DIG_HIZ         (0x01u << opamp_pos_DRIVE_MODE_SHIFT)
#define opamp_pos_DM_RES_UP          (0x02u << opamp_pos_DRIVE_MODE_SHIFT)
#define opamp_pos_DM_RES_DWN         (0x03u << opamp_pos_DRIVE_MODE_SHIFT)
#define opamp_pos_DM_OD_LO           (0x04u << opamp_pos_DRIVE_MODE_SHIFT)
#define opamp_pos_DM_OD_HI           (0x05u << opamp_pos_DRIVE_MODE_SHIFT)
#define opamp_pos_DM_STRONG          (0x06u << opamp_pos_DRIVE_MODE_SHIFT)
#define opamp_pos_DM_RES_UPDWN       (0x07u << opamp_pos_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define opamp_pos_MASK               opamp_pos__MASK
#define opamp_pos_SHIFT              opamp_pos__SHIFT
#define opamp_pos_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define opamp_pos_PS                     (* (reg32 *) opamp_pos__PS)
/* Port Configuration */
#define opamp_pos_PC                     (* (reg32 *) opamp_pos__PC)
/* Data Register */
#define opamp_pos_DR                     (* (reg32 *) opamp_pos__DR)
/* Input Buffer Disable Override */
#define opamp_pos_INP_DIS                (* (reg32 *) opamp_pos__PC2)


#if defined(opamp_pos__INTSTAT)  /* Interrupt Registers */

    #define opamp_pos_INTSTAT                (* (reg32 *) opamp_pos__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins opamp_pos_H */


/* [] END OF FILE */
