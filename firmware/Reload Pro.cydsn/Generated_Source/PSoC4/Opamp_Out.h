/*******************************************************************************
* File Name: Opamp_Out.h  
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

#if !defined(CY_PINS_Opamp_Out_H) /* Pins Opamp_Out_H */
#define CY_PINS_Opamp_Out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Opamp_Out_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Opamp_Out_Write(uint8 value) ;
void    Opamp_Out_SetDriveMode(uint8 mode) ;
uint8   Opamp_Out_ReadDataReg(void) ;
uint8   Opamp_Out_Read(void) ;
uint8   Opamp_Out_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Opamp_Out_DRIVE_MODE_BITS        (3)
#define Opamp_Out_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Opamp_Out_DRIVE_MODE_BITS))
#define Opamp_Out_DRIVE_MODE_SHIFT       (0x00u)
#define Opamp_Out_DRIVE_MODE_MASK        (0x07u << Opamp_Out_DRIVE_MODE_SHIFT)

#define Opamp_Out_DM_ALG_HIZ         (0x00u << Opamp_Out_DRIVE_MODE_SHIFT)
#define Opamp_Out_DM_DIG_HIZ         (0x01u << Opamp_Out_DRIVE_MODE_SHIFT)
#define Opamp_Out_DM_RES_UP          (0x02u << Opamp_Out_DRIVE_MODE_SHIFT)
#define Opamp_Out_DM_RES_DWN         (0x03u << Opamp_Out_DRIVE_MODE_SHIFT)
#define Opamp_Out_DM_OD_LO           (0x04u << Opamp_Out_DRIVE_MODE_SHIFT)
#define Opamp_Out_DM_OD_HI           (0x05u << Opamp_Out_DRIVE_MODE_SHIFT)
#define Opamp_Out_DM_STRONG          (0x06u << Opamp_Out_DRIVE_MODE_SHIFT)
#define Opamp_Out_DM_RES_UPDWN       (0x07u << Opamp_Out_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Opamp_Out_MASK               Opamp_Out__MASK
#define Opamp_Out_SHIFT              Opamp_Out__SHIFT
#define Opamp_Out_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Opamp_Out_PS                     (* (reg32 *) Opamp_Out__PS)
/* Port Configuration */
#define Opamp_Out_PC                     (* (reg32 *) Opamp_Out__PC)
/* Data Register */
#define Opamp_Out_DR                     (* (reg32 *) Opamp_Out__DR)
/* Input Buffer Disable Override */
#define Opamp_Out_INP_DIS                (* (reg32 *) Opamp_Out__PC2)


#if defined(Opamp_Out__INTSTAT)  /* Interrupt Registers */

    #define Opamp_Out_INTSTAT                (* (reg32 *) Opamp_Out__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Opamp_Out_H */


/* [] END OF FILE */
