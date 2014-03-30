/*******************************************************************************
* File Name: Pin_7.h  
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

#if !defined(CY_PINS_Pin_7_H) /* Pins Pin_7_H */
#define CY_PINS_Pin_7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin_7_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_7_Write(uint8 value) ;
void    Pin_7_SetDriveMode(uint8 mode) ;
uint8   Pin_7_ReadDataReg(void) ;
uint8   Pin_7_Read(void) ;
uint8   Pin_7_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_7_DRIVE_MODE_BITS        (3)
#define Pin_7_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin_7_DRIVE_MODE_BITS))
#define Pin_7_DRIVE_MODE_SHIFT       (0x00u)
#define Pin_7_DRIVE_MODE_MASK        (0x07u << Pin_7_DRIVE_MODE_SHIFT)

#define Pin_7_DM_ALG_HIZ         (0x00u << Pin_7_DRIVE_MODE_SHIFT)
#define Pin_7_DM_DIG_HIZ         (0x01u << Pin_7_DRIVE_MODE_SHIFT)
#define Pin_7_DM_RES_UP          (0x02u << Pin_7_DRIVE_MODE_SHIFT)
#define Pin_7_DM_RES_DWN         (0x03u << Pin_7_DRIVE_MODE_SHIFT)
#define Pin_7_DM_OD_LO           (0x04u << Pin_7_DRIVE_MODE_SHIFT)
#define Pin_7_DM_OD_HI           (0x05u << Pin_7_DRIVE_MODE_SHIFT)
#define Pin_7_DM_STRONG          (0x06u << Pin_7_DRIVE_MODE_SHIFT)
#define Pin_7_DM_RES_UPDWN       (0x07u << Pin_7_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Pin_7_MASK               Pin_7__MASK
#define Pin_7_SHIFT              Pin_7__SHIFT
#define Pin_7_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_7_PS                     (* (reg32 *) Pin_7__PS)
/* Port Configuration */
#define Pin_7_PC                     (* (reg32 *) Pin_7__PC)
/* Data Register */
#define Pin_7_DR                     (* (reg32 *) Pin_7__DR)
/* Input Buffer Disable Override */
#define Pin_7_INP_DIS                (* (reg32 *) Pin_7__PC2)


#if defined(Pin_7__INTSTAT)  /* Interrupt Registers */

    #define Pin_7_INTSTAT                (* (reg32 *) Pin_7__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_7_H */


/* [] END OF FILE */
