/*******************************************************************************
* File Name: quad_b.h  
* Version 1.90
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

#if !defined(CY_PINS_quad_b_H) /* Pins quad_b_H */
#define CY_PINS_quad_b_H

#include "cytypes.h"
#include "cyfitter.h"
#include "quad_b_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    quad_b_Write(uint8 value) ;
void    quad_b_SetDriveMode(uint8 mode) ;
uint8   quad_b_ReadDataReg(void) ;
uint8   quad_b_Read(void) ;
uint8   quad_b_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define quad_b_DRIVE_MODE_BITS        (3)
#define quad_b_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - quad_b_DRIVE_MODE_BITS))
#define quad_b_DRIVE_MODE_SHIFT       (0x00u)
#define quad_b_DRIVE_MODE_MASK        (0x07u << quad_b_DRIVE_MODE_SHIFT)

#define quad_b_DM_ALG_HIZ         (0x00u << quad_b_DRIVE_MODE_SHIFT)
#define quad_b_DM_DIG_HIZ         (0x01u << quad_b_DRIVE_MODE_SHIFT)
#define quad_b_DM_RES_UP          (0x02u << quad_b_DRIVE_MODE_SHIFT)
#define quad_b_DM_RES_DWN         (0x03u << quad_b_DRIVE_MODE_SHIFT)
#define quad_b_DM_OD_LO           (0x04u << quad_b_DRIVE_MODE_SHIFT)
#define quad_b_DM_OD_HI           (0x05u << quad_b_DRIVE_MODE_SHIFT)
#define quad_b_DM_STRONG          (0x06u << quad_b_DRIVE_MODE_SHIFT)
#define quad_b_DM_RES_UPDWN       (0x07u << quad_b_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define quad_b_MASK               quad_b__MASK
#define quad_b_SHIFT              quad_b__SHIFT
#define quad_b_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define quad_b_PS                     (* (reg32 *) quad_b__PS)
/* Port Configuration */
#define quad_b_PC                     (* (reg32 *) quad_b__PC)
/* Data Register */
#define quad_b_DR                     (* (reg32 *) quad_b__DR)
/* Input Buffer Disable Override */
#define quad_b_INP_DIS                (* (reg32 *) quad_b__PC2)


#if defined(quad_b__INTSTAT)  /* Interrupt Registers */

    #define quad_b_INTSTAT                (* (reg32 *) quad_b__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins quad_b_H */


/* [] END OF FILE */
