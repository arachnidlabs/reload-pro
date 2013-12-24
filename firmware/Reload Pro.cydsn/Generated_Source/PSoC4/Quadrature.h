/*******************************************************************************
* File Name: Quadrature.h  
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

#if !defined(CY_PINS_Quadrature_H) /* Pins Quadrature_H */
#define CY_PINS_Quadrature_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Quadrature_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Quadrature_Write(uint8 value) ;
void    Quadrature_SetDriveMode(uint8 mode) ;
uint8   Quadrature_ReadDataReg(void) ;
uint8   Quadrature_Read(void) ;
uint8   Quadrature_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Quadrature_DRIVE_MODE_BITS        (3)
#define Quadrature_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Quadrature_DRIVE_MODE_BITS))
#define Quadrature_DRIVE_MODE_SHIFT       (0x00u)
#define Quadrature_DRIVE_MODE_MASK        (0x07u << Quadrature_DRIVE_MODE_SHIFT)

#define Quadrature_DM_ALG_HIZ         (0x00u << Quadrature_DRIVE_MODE_SHIFT)
#define Quadrature_DM_DIG_HIZ         (0x01u << Quadrature_DRIVE_MODE_SHIFT)
#define Quadrature_DM_RES_UP          (0x02u << Quadrature_DRIVE_MODE_SHIFT)
#define Quadrature_DM_RES_DWN         (0x03u << Quadrature_DRIVE_MODE_SHIFT)
#define Quadrature_DM_OD_LO           (0x04u << Quadrature_DRIVE_MODE_SHIFT)
#define Quadrature_DM_OD_HI           (0x05u << Quadrature_DRIVE_MODE_SHIFT)
#define Quadrature_DM_STRONG          (0x06u << Quadrature_DRIVE_MODE_SHIFT)
#define Quadrature_DM_RES_UPDWN       (0x07u << Quadrature_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Quadrature_MASK               Quadrature__MASK
#define Quadrature_SHIFT              Quadrature__SHIFT
#define Quadrature_WIDTH              2u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Quadrature_PS                     (* (reg32 *) Quadrature__PS)
/* Port Configuration */
#define Quadrature_PC                     (* (reg32 *) Quadrature__PC)
/* Data Register */
#define Quadrature_DR                     (* (reg32 *) Quadrature__DR)
/* Input Buffer Disable Override */
#define Quadrature_INP_DIS                (* (reg32 *) Quadrature__PC2)


#if defined(Quadrature__INTSTAT)  /* Interrupt Registers */

    #define Quadrature_INTSTAT                (* (reg32 *) Quadrature__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Quadrature_H */


/* [] END OF FILE */
