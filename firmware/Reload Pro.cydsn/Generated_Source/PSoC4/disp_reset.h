/*******************************************************************************
* File Name: disp_reset.h  
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

#if !defined(CY_PINS_disp_reset_H) /* Pins disp_reset_H */
#define CY_PINS_disp_reset_H

#include "cytypes.h"
#include "cyfitter.h"
#include "disp_reset_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    disp_reset_Write(uint8 value) ;
void    disp_reset_SetDriveMode(uint8 mode) ;
uint8   disp_reset_ReadDataReg(void) ;
uint8   disp_reset_Read(void) ;
uint8   disp_reset_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define disp_reset_DRIVE_MODE_BITS        (3)
#define disp_reset_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - disp_reset_DRIVE_MODE_BITS))
#define disp_reset_DRIVE_MODE_SHIFT       (0x00u)
#define disp_reset_DRIVE_MODE_MASK        (0x07u << disp_reset_DRIVE_MODE_SHIFT)

#define disp_reset_DM_ALG_HIZ         (0x00u << disp_reset_DRIVE_MODE_SHIFT)
#define disp_reset_DM_DIG_HIZ         (0x01u << disp_reset_DRIVE_MODE_SHIFT)
#define disp_reset_DM_RES_UP          (0x02u << disp_reset_DRIVE_MODE_SHIFT)
#define disp_reset_DM_RES_DWN         (0x03u << disp_reset_DRIVE_MODE_SHIFT)
#define disp_reset_DM_OD_LO           (0x04u << disp_reset_DRIVE_MODE_SHIFT)
#define disp_reset_DM_OD_HI           (0x05u << disp_reset_DRIVE_MODE_SHIFT)
#define disp_reset_DM_STRONG          (0x06u << disp_reset_DRIVE_MODE_SHIFT)
#define disp_reset_DM_RES_UPDWN       (0x07u << disp_reset_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define disp_reset_MASK               disp_reset__MASK
#define disp_reset_SHIFT              disp_reset__SHIFT
#define disp_reset_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define disp_reset_PS                     (* (reg32 *) disp_reset__PS)
/* Port Configuration */
#define disp_reset_PC                     (* (reg32 *) disp_reset__PC)
/* Data Register */
#define disp_reset_DR                     (* (reg32 *) disp_reset__DR)
/* Input Buffer Disable Override */
#define disp_reset_INP_DIS                (* (reg32 *) disp_reset__PC2)


#if defined(disp_reset__INTSTAT)  /* Interrupt Registers */

    #define disp_reset_INTSTAT                (* (reg32 *) disp_reset__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins disp_reset_H */


/* [] END OF FILE */
