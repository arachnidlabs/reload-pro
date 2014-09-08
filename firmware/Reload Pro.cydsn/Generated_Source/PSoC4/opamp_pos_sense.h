/*******************************************************************************
* File Name: opamp_pos_sense.h  
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

#if !defined(CY_PINS_opamp_pos_sense_H) /* Pins opamp_pos_sense_H */
#define CY_PINS_opamp_pos_sense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "opamp_pos_sense_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    opamp_pos_sense_Write(uint8 value) ;
void    opamp_pos_sense_SetDriveMode(uint8 mode) ;
uint8   opamp_pos_sense_ReadDataReg(void) ;
uint8   opamp_pos_sense_Read(void) ;
uint8   opamp_pos_sense_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define opamp_pos_sense_DRIVE_MODE_BITS        (3)
#define opamp_pos_sense_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - opamp_pos_sense_DRIVE_MODE_BITS))
#define opamp_pos_sense_DRIVE_MODE_SHIFT       (0x00u)
#define opamp_pos_sense_DRIVE_MODE_MASK        (0x07u << opamp_pos_sense_DRIVE_MODE_SHIFT)

#define opamp_pos_sense_DM_ALG_HIZ         (0x00u << opamp_pos_sense_DRIVE_MODE_SHIFT)
#define opamp_pos_sense_DM_DIG_HIZ         (0x01u << opamp_pos_sense_DRIVE_MODE_SHIFT)
#define opamp_pos_sense_DM_RES_UP          (0x02u << opamp_pos_sense_DRIVE_MODE_SHIFT)
#define opamp_pos_sense_DM_RES_DWN         (0x03u << opamp_pos_sense_DRIVE_MODE_SHIFT)
#define opamp_pos_sense_DM_OD_LO           (0x04u << opamp_pos_sense_DRIVE_MODE_SHIFT)
#define opamp_pos_sense_DM_OD_HI           (0x05u << opamp_pos_sense_DRIVE_MODE_SHIFT)
#define opamp_pos_sense_DM_STRONG          (0x06u << opamp_pos_sense_DRIVE_MODE_SHIFT)
#define opamp_pos_sense_DM_RES_UPDWN       (0x07u << opamp_pos_sense_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define opamp_pos_sense_MASK               opamp_pos_sense__MASK
#define opamp_pos_sense_SHIFT              opamp_pos_sense__SHIFT
#define opamp_pos_sense_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define opamp_pos_sense_PS                     (* (reg32 *) opamp_pos_sense__PS)
/* Port Configuration */
#define opamp_pos_sense_PC                     (* (reg32 *) opamp_pos_sense__PC)
/* Data Register */
#define opamp_pos_sense_DR                     (* (reg32 *) opamp_pos_sense__DR)
/* Input Buffer Disable Override */
#define opamp_pos_sense_INP_DIS                (* (reg32 *) opamp_pos_sense__PC2)


#if defined(opamp_pos_sense__INTSTAT)  /* Interrupt Registers */

    #define opamp_pos_sense_INTSTAT                (* (reg32 *) opamp_pos_sense__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins opamp_pos_sense_H */


/* [] END OF FILE */
