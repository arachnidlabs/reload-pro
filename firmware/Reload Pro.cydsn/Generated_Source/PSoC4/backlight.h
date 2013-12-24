/*******************************************************************************
* File Name: backlight.h  
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

#if !defined(CY_PINS_backlight_H) /* Pins backlight_H */
#define CY_PINS_backlight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "backlight_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    backlight_Write(uint8 value) ;
void    backlight_SetDriveMode(uint8 mode) ;
uint8   backlight_ReadDataReg(void) ;
uint8   backlight_Read(void) ;
uint8   backlight_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define backlight_DRIVE_MODE_BITS        (3)
#define backlight_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - backlight_DRIVE_MODE_BITS))
#define backlight_DRIVE_MODE_SHIFT       (0x00u)
#define backlight_DRIVE_MODE_MASK        (0x07u << backlight_DRIVE_MODE_SHIFT)

#define backlight_DM_ALG_HIZ         (0x00u << backlight_DRIVE_MODE_SHIFT)
#define backlight_DM_DIG_HIZ         (0x01u << backlight_DRIVE_MODE_SHIFT)
#define backlight_DM_RES_UP          (0x02u << backlight_DRIVE_MODE_SHIFT)
#define backlight_DM_RES_DWN         (0x03u << backlight_DRIVE_MODE_SHIFT)
#define backlight_DM_OD_LO           (0x04u << backlight_DRIVE_MODE_SHIFT)
#define backlight_DM_OD_HI           (0x05u << backlight_DRIVE_MODE_SHIFT)
#define backlight_DM_STRONG          (0x06u << backlight_DRIVE_MODE_SHIFT)
#define backlight_DM_RES_UPDWN       (0x07u << backlight_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define backlight_MASK               backlight__MASK
#define backlight_SHIFT              backlight__SHIFT
#define backlight_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define backlight_PS                     (* (reg32 *) backlight__PS)
/* Port Configuration */
#define backlight_PC                     (* (reg32 *) backlight__PC)
/* Data Register */
#define backlight_DR                     (* (reg32 *) backlight__DR)
/* Input Buffer Disable Override */
#define backlight_INP_DIS                (* (reg32 *) backlight__PC2)


#if defined(backlight__INTSTAT)  /* Interrupt Registers */

    #define backlight_INTSTAT                (* (reg32 *) backlight__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins backlight_H */


/* [] END OF FILE */
