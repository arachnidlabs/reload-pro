/*******************************************************************************
* File Name: quad_button.h  
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

#if !defined(CY_PINS_quad_button_H) /* Pins quad_button_H */
#define CY_PINS_quad_button_H

#include "cytypes.h"
#include "cyfitter.h"
#include "quad_button_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    quad_button_Write(uint8 value) ;
void    quad_button_SetDriveMode(uint8 mode) ;
uint8   quad_button_ReadDataReg(void) ;
uint8   quad_button_Read(void) ;
uint8   quad_button_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define quad_button_DRIVE_MODE_BITS        (3)
#define quad_button_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - quad_button_DRIVE_MODE_BITS))
#define quad_button_DRIVE_MODE_SHIFT       (0x00u)
#define quad_button_DRIVE_MODE_MASK        (0x07u << quad_button_DRIVE_MODE_SHIFT)

#define quad_button_DM_ALG_HIZ         (0x00u << quad_button_DRIVE_MODE_SHIFT)
#define quad_button_DM_DIG_HIZ         (0x01u << quad_button_DRIVE_MODE_SHIFT)
#define quad_button_DM_RES_UP          (0x02u << quad_button_DRIVE_MODE_SHIFT)
#define quad_button_DM_RES_DWN         (0x03u << quad_button_DRIVE_MODE_SHIFT)
#define quad_button_DM_OD_LO           (0x04u << quad_button_DRIVE_MODE_SHIFT)
#define quad_button_DM_OD_HI           (0x05u << quad_button_DRIVE_MODE_SHIFT)
#define quad_button_DM_STRONG          (0x06u << quad_button_DRIVE_MODE_SHIFT)
#define quad_button_DM_RES_UPDWN       (0x07u << quad_button_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define quad_button_MASK               quad_button__MASK
#define quad_button_SHIFT              quad_button__SHIFT
#define quad_button_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define quad_button_PS                     (* (reg32 *) quad_button__PS)
/* Port Configuration */
#define quad_button_PC                     (* (reg32 *) quad_button__PC)
/* Data Register */
#define quad_button_DR                     (* (reg32 *) quad_button__DR)
/* Input Buffer Disable Override */
#define quad_button_INP_DIS                (* (reg32 *) quad_button__PC2)


#if defined(quad_button__INTSTAT)  /* Interrupt Registers */

    #define quad_button_INTSTAT                (* (reg32 *) quad_button__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins quad_button_H */


/* [] END OF FILE */
