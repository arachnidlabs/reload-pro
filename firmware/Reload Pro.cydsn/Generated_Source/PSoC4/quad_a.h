/*******************************************************************************
* File Name: quad_a.h  
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

#if !defined(CY_PINS_quad_a_H) /* Pins quad_a_H */
#define CY_PINS_quad_a_H

#include "cytypes.h"
#include "cyfitter.h"
#include "quad_a_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    quad_a_Write(uint8 value) ;
void    quad_a_SetDriveMode(uint8 mode) ;
uint8   quad_a_ReadDataReg(void) ;
uint8   quad_a_Read(void) ;
uint8   quad_a_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define quad_a_DRIVE_MODE_BITS        (3)
#define quad_a_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - quad_a_DRIVE_MODE_BITS))
#define quad_a_DRIVE_MODE_SHIFT       (0x00u)
#define quad_a_DRIVE_MODE_MASK        (0x07u << quad_a_DRIVE_MODE_SHIFT)

#define quad_a_DM_ALG_HIZ         (0x00u << quad_a_DRIVE_MODE_SHIFT)
#define quad_a_DM_DIG_HIZ         (0x01u << quad_a_DRIVE_MODE_SHIFT)
#define quad_a_DM_RES_UP          (0x02u << quad_a_DRIVE_MODE_SHIFT)
#define quad_a_DM_RES_DWN         (0x03u << quad_a_DRIVE_MODE_SHIFT)
#define quad_a_DM_OD_LO           (0x04u << quad_a_DRIVE_MODE_SHIFT)
#define quad_a_DM_OD_HI           (0x05u << quad_a_DRIVE_MODE_SHIFT)
#define quad_a_DM_STRONG          (0x06u << quad_a_DRIVE_MODE_SHIFT)
#define quad_a_DM_RES_UPDWN       (0x07u << quad_a_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define quad_a_MASK               quad_a__MASK
#define quad_a_SHIFT              quad_a__SHIFT
#define quad_a_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define quad_a_PS                     (* (reg32 *) quad_a__PS)
/* Port Configuration */
#define quad_a_PC                     (* (reg32 *) quad_a__PC)
/* Data Register */
#define quad_a_DR                     (* (reg32 *) quad_a__DR)
/* Input Buffer Disable Override */
#define quad_a_INP_DIS                (* (reg32 *) quad_a__PC2)


#if defined(quad_a__INTSTAT)  /* Interrupt Registers */

    #define quad_a_INTSTAT                (* (reg32 *) quad_a__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins quad_a_H */


/* [] END OF FILE */
