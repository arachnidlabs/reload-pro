/*******************************************************************************
* File Name: Idac_Low.h  
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

#if !defined(CY_PINS_Idac_Low_H) /* Pins Idac_Low_H */
#define CY_PINS_Idac_Low_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Idac_Low_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Idac_Low_Write(uint8 value) ;
void    Idac_Low_SetDriveMode(uint8 mode) ;
uint8   Idac_Low_ReadDataReg(void) ;
uint8   Idac_Low_Read(void) ;
uint8   Idac_Low_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Idac_Low_DRIVE_MODE_BITS        (3)
#define Idac_Low_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Idac_Low_DRIVE_MODE_BITS))
#define Idac_Low_DRIVE_MODE_SHIFT       (0x00u)
#define Idac_Low_DRIVE_MODE_MASK        (0x07u << Idac_Low_DRIVE_MODE_SHIFT)

#define Idac_Low_DM_ALG_HIZ         (0x00u << Idac_Low_DRIVE_MODE_SHIFT)
#define Idac_Low_DM_DIG_HIZ         (0x01u << Idac_Low_DRIVE_MODE_SHIFT)
#define Idac_Low_DM_RES_UP          (0x02u << Idac_Low_DRIVE_MODE_SHIFT)
#define Idac_Low_DM_RES_DWN         (0x03u << Idac_Low_DRIVE_MODE_SHIFT)
#define Idac_Low_DM_OD_LO           (0x04u << Idac_Low_DRIVE_MODE_SHIFT)
#define Idac_Low_DM_OD_HI           (0x05u << Idac_Low_DRIVE_MODE_SHIFT)
#define Idac_Low_DM_STRONG          (0x06u << Idac_Low_DRIVE_MODE_SHIFT)
#define Idac_Low_DM_RES_UPDWN       (0x07u << Idac_Low_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Idac_Low_MASK               Idac_Low__MASK
#define Idac_Low_SHIFT              Idac_Low__SHIFT
#define Idac_Low_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Idac_Low_PS                     (* (reg32 *) Idac_Low__PS)
/* Port Configuration */
#define Idac_Low_PC                     (* (reg32 *) Idac_Low__PC)
/* Data Register */
#define Idac_Low_DR                     (* (reg32 *) Idac_Low__DR)
/* Input Buffer Disable Override */
#define Idac_Low_INP_DIS                (* (reg32 *) Idac_Low__PC2)


#if defined(Idac_Low__INTSTAT)  /* Interrupt Registers */

    #define Idac_Low_INTSTAT                (* (reg32 *) Idac_Low__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Idac_Low_H */


/* [] END OF FILE */
