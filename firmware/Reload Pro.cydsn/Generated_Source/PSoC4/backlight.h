/*******************************************************************************
* File Name: Backlight.h  
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

#if !defined(CY_PINS_Backlight_H) /* Pins Backlight_H */
#define CY_PINS_Backlight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Backlight_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Backlight_Write(uint8 value) ;
void    Backlight_SetDriveMode(uint8 mode) ;
uint8   Backlight_ReadDataReg(void) ;
uint8   Backlight_Read(void) ;
uint8   Backlight_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Backlight_DRIVE_MODE_BITS        (3)
#define Backlight_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Backlight_DRIVE_MODE_BITS))
#define Backlight_DRIVE_MODE_SHIFT       (0x00u)
#define Backlight_DRIVE_MODE_MASK        (0x07u << Backlight_DRIVE_MODE_SHIFT)

#define Backlight_DM_ALG_HIZ         (0x00u << Backlight_DRIVE_MODE_SHIFT)
#define Backlight_DM_DIG_HIZ         (0x01u << Backlight_DRIVE_MODE_SHIFT)
#define Backlight_DM_RES_UP          (0x02u << Backlight_DRIVE_MODE_SHIFT)
#define Backlight_DM_RES_DWN         (0x03u << Backlight_DRIVE_MODE_SHIFT)
#define Backlight_DM_OD_LO           (0x04u << Backlight_DRIVE_MODE_SHIFT)
#define Backlight_DM_OD_HI           (0x05u << Backlight_DRIVE_MODE_SHIFT)
#define Backlight_DM_STRONG          (0x06u << Backlight_DRIVE_MODE_SHIFT)
#define Backlight_DM_RES_UPDWN       (0x07u << Backlight_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Backlight_MASK               Backlight__MASK
#define Backlight_SHIFT              Backlight__SHIFT
#define Backlight_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Backlight_PS                     (* (reg32 *) Backlight__PS)
/* Port Configuration */
#define Backlight_PC                     (* (reg32 *) Backlight__PC)
/* Data Register */
#define Backlight_DR                     (* (reg32 *) Backlight__DR)
/* Input Buffer Disable Override */
#define Backlight_INP_DIS                (* (reg32 *) Backlight__PC2)


#if defined(Backlight__INTSTAT)  /* Interrupt Registers */

    #define Backlight_INTSTAT                (* (reg32 *) Backlight__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Backlight_H */


/* [] END OF FILE */
