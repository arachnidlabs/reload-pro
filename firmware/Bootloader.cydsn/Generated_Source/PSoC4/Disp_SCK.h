/*******************************************************************************
* File Name: Disp_SCK.h  
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

#if !defined(CY_PINS_Disp_SCK_H) /* Pins Disp_SCK_H */
#define CY_PINS_Disp_SCK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Disp_SCK_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Disp_SCK_Write(uint8 value) ;
void    Disp_SCK_SetDriveMode(uint8 mode) ;
uint8   Disp_SCK_ReadDataReg(void) ;
uint8   Disp_SCK_Read(void) ;
uint8   Disp_SCK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Disp_SCK_DRIVE_MODE_BITS        (3)
#define Disp_SCK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Disp_SCK_DRIVE_MODE_BITS))
#define Disp_SCK_DRIVE_MODE_SHIFT       (0x00u)
#define Disp_SCK_DRIVE_MODE_MASK        (0x07u << Disp_SCK_DRIVE_MODE_SHIFT)

#define Disp_SCK_DM_ALG_HIZ         (0x00u << Disp_SCK_DRIVE_MODE_SHIFT)
#define Disp_SCK_DM_DIG_HIZ         (0x01u << Disp_SCK_DRIVE_MODE_SHIFT)
#define Disp_SCK_DM_RES_UP          (0x02u << Disp_SCK_DRIVE_MODE_SHIFT)
#define Disp_SCK_DM_RES_DWN         (0x03u << Disp_SCK_DRIVE_MODE_SHIFT)
#define Disp_SCK_DM_OD_LO           (0x04u << Disp_SCK_DRIVE_MODE_SHIFT)
#define Disp_SCK_DM_OD_HI           (0x05u << Disp_SCK_DRIVE_MODE_SHIFT)
#define Disp_SCK_DM_STRONG          (0x06u << Disp_SCK_DRIVE_MODE_SHIFT)
#define Disp_SCK_DM_RES_UPDWN       (0x07u << Disp_SCK_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Disp_SCK_MASK               Disp_SCK__MASK
#define Disp_SCK_SHIFT              Disp_SCK__SHIFT
#define Disp_SCK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Disp_SCK_PS                     (* (reg32 *) Disp_SCK__PS)
/* Port Configuration */
#define Disp_SCK_PC                     (* (reg32 *) Disp_SCK__PC)
/* Data Register */
#define Disp_SCK_DR                     (* (reg32 *) Disp_SCK__DR)
/* Input Buffer Disable Override */
#define Disp_SCK_INP_DIS                (* (reg32 *) Disp_SCK__PC2)


#if defined(Disp_SCK__INTSTAT)  /* Interrupt Registers */

    #define Disp_SCK_INTSTAT                (* (reg32 *) Disp_SCK__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Disp_SCK_H */


/* [] END OF FILE */
