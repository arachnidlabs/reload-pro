/*******************************************************************************
* File Name: Idac_High.h  
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

#if !defined(CY_PINS_Idac_High_H) /* Pins Idac_High_H */
#define CY_PINS_Idac_High_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Idac_High_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Idac_High_Write(uint8 value) ;
void    Idac_High_SetDriveMode(uint8 mode) ;
uint8   Idac_High_ReadDataReg(void) ;
uint8   Idac_High_Read(void) ;
uint8   Idac_High_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Idac_High_DRIVE_MODE_BITS        (3)
#define Idac_High_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Idac_High_DRIVE_MODE_BITS))
#define Idac_High_DRIVE_MODE_SHIFT       (0x00u)
#define Idac_High_DRIVE_MODE_MASK        (0x07u << Idac_High_DRIVE_MODE_SHIFT)

#define Idac_High_DM_ALG_HIZ         (0x00u << Idac_High_DRIVE_MODE_SHIFT)
#define Idac_High_DM_DIG_HIZ         (0x01u << Idac_High_DRIVE_MODE_SHIFT)
#define Idac_High_DM_RES_UP          (0x02u << Idac_High_DRIVE_MODE_SHIFT)
#define Idac_High_DM_RES_DWN         (0x03u << Idac_High_DRIVE_MODE_SHIFT)
#define Idac_High_DM_OD_LO           (0x04u << Idac_High_DRIVE_MODE_SHIFT)
#define Idac_High_DM_OD_HI           (0x05u << Idac_High_DRIVE_MODE_SHIFT)
#define Idac_High_DM_STRONG          (0x06u << Idac_High_DRIVE_MODE_SHIFT)
#define Idac_High_DM_RES_UPDWN       (0x07u << Idac_High_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Idac_High_MASK               Idac_High__MASK
#define Idac_High_SHIFT              Idac_High__SHIFT
#define Idac_High_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Idac_High_PS                     (* (reg32 *) Idac_High__PS)
/* Port Configuration */
#define Idac_High_PC                     (* (reg32 *) Idac_High__PC)
/* Data Register */
#define Idac_High_DR                     (* (reg32 *) Idac_High__DR)
/* Input Buffer Disable Override */
#define Idac_High_INP_DIS                (* (reg32 *) Idac_High__PC2)


#if defined(Idac_High__INTSTAT)  /* Interrupt Registers */

    #define Idac_High_INTSTAT                (* (reg32 *) Idac_High__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Idac_High_H */


/* [] END OF FILE */
