/*******************************************************************************
* File Name: Opamp_Pos_Low.h  
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

#if !defined(CY_PINS_Opamp_Pos_Low_H) /* Pins Opamp_Pos_Low_H */
#define CY_PINS_Opamp_Pos_Low_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Opamp_Pos_Low_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Opamp_Pos_Low_Write(uint8 value) ;
void    Opamp_Pos_Low_SetDriveMode(uint8 mode) ;
uint8   Opamp_Pos_Low_ReadDataReg(void) ;
uint8   Opamp_Pos_Low_Read(void) ;
uint8   Opamp_Pos_Low_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Opamp_Pos_Low_DRIVE_MODE_BITS        (3)
#define Opamp_Pos_Low_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Opamp_Pos_Low_DRIVE_MODE_BITS))
#define Opamp_Pos_Low_DRIVE_MODE_SHIFT       (0x00u)
#define Opamp_Pos_Low_DRIVE_MODE_MASK        (0x07u << Opamp_Pos_Low_DRIVE_MODE_SHIFT)

#define Opamp_Pos_Low_DM_ALG_HIZ         (0x00u << Opamp_Pos_Low_DRIVE_MODE_SHIFT)
#define Opamp_Pos_Low_DM_DIG_HIZ         (0x01u << Opamp_Pos_Low_DRIVE_MODE_SHIFT)
#define Opamp_Pos_Low_DM_RES_UP          (0x02u << Opamp_Pos_Low_DRIVE_MODE_SHIFT)
#define Opamp_Pos_Low_DM_RES_DWN         (0x03u << Opamp_Pos_Low_DRIVE_MODE_SHIFT)
#define Opamp_Pos_Low_DM_OD_LO           (0x04u << Opamp_Pos_Low_DRIVE_MODE_SHIFT)
#define Opamp_Pos_Low_DM_OD_HI           (0x05u << Opamp_Pos_Low_DRIVE_MODE_SHIFT)
#define Opamp_Pos_Low_DM_STRONG          (0x06u << Opamp_Pos_Low_DRIVE_MODE_SHIFT)
#define Opamp_Pos_Low_DM_RES_UPDWN       (0x07u << Opamp_Pos_Low_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Opamp_Pos_Low_MASK               Opamp_Pos_Low__MASK
#define Opamp_Pos_Low_SHIFT              Opamp_Pos_Low__SHIFT
#define Opamp_Pos_Low_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Opamp_Pos_Low_PS                     (* (reg32 *) Opamp_Pos_Low__PS)
/* Port Configuration */
#define Opamp_Pos_Low_PC                     (* (reg32 *) Opamp_Pos_Low__PC)
/* Data Register */
#define Opamp_Pos_Low_DR                     (* (reg32 *) Opamp_Pos_Low__DR)
/* Input Buffer Disable Override */
#define Opamp_Pos_Low_INP_DIS                (* (reg32 *) Opamp_Pos_Low__PC2)


#if defined(Opamp_Pos_Low__INTSTAT)  /* Interrupt Registers */

    #define Opamp_Pos_Low_INTSTAT                (* (reg32 *) Opamp_Pos_Low__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Opamp_Pos_Low_H */


/* [] END OF FILE */
