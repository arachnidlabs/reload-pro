/*******************************************************************************
* File Name: QuadButton.h  
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

#if !defined(CY_PINS_QuadButton_H) /* Pins QuadButton_H */
#define CY_PINS_QuadButton_H

#include "cytypes.h"
#include "cyfitter.h"
#include "QuadButton_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    QuadButton_Write(uint8 value) ;
void    QuadButton_SetDriveMode(uint8 mode) ;
uint8   QuadButton_ReadDataReg(void) ;
uint8   QuadButton_Read(void) ;
uint8   QuadButton_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define QuadButton_DRIVE_MODE_BITS        (3)
#define QuadButton_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - QuadButton_DRIVE_MODE_BITS))
#define QuadButton_DRIVE_MODE_SHIFT       (0x00u)
#define QuadButton_DRIVE_MODE_MASK        (0x07u << QuadButton_DRIVE_MODE_SHIFT)

#define QuadButton_DM_ALG_HIZ         (0x00u << QuadButton_DRIVE_MODE_SHIFT)
#define QuadButton_DM_DIG_HIZ         (0x01u << QuadButton_DRIVE_MODE_SHIFT)
#define QuadButton_DM_RES_UP          (0x02u << QuadButton_DRIVE_MODE_SHIFT)
#define QuadButton_DM_RES_DWN         (0x03u << QuadButton_DRIVE_MODE_SHIFT)
#define QuadButton_DM_OD_LO           (0x04u << QuadButton_DRIVE_MODE_SHIFT)
#define QuadButton_DM_OD_HI           (0x05u << QuadButton_DRIVE_MODE_SHIFT)
#define QuadButton_DM_STRONG          (0x06u << QuadButton_DRIVE_MODE_SHIFT)
#define QuadButton_DM_RES_UPDWN       (0x07u << QuadButton_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define QuadButton_MASK               QuadButton__MASK
#define QuadButton_SHIFT              QuadButton__SHIFT
#define QuadButton_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define QuadButton_PS                     (* (reg32 *) QuadButton__PS)
/* Port Configuration */
#define QuadButton_PC                     (* (reg32 *) QuadButton__PC)
/* Data Register */
#define QuadButton_DR                     (* (reg32 *) QuadButton__DR)
/* Input Buffer Disable Override */
#define QuadButton_INP_DIS                (* (reg32 *) QuadButton__PC2)


#if defined(QuadButton__INTSTAT)  /* Interrupt Registers */

    #define QuadButton_INTSTAT                (* (reg32 *) QuadButton__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins QuadButton_H */


/* [] END OF FILE */
