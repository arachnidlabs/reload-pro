/*******************************************************************************
* File Name: disp_sclk.h  
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

#if !defined(CY_PINS_disp_sclk_H) /* Pins disp_sclk_H */
#define CY_PINS_disp_sclk_H

#include "cytypes.h"
#include "cyfitter.h"
#include "disp_sclk_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    disp_sclk_Write(uint8 value) ;
void    disp_sclk_SetDriveMode(uint8 mode) ;
uint8   disp_sclk_ReadDataReg(void) ;
uint8   disp_sclk_Read(void) ;
uint8   disp_sclk_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define disp_sclk_DRIVE_MODE_BITS        (3)
#define disp_sclk_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - disp_sclk_DRIVE_MODE_BITS))
#define disp_sclk_DRIVE_MODE_SHIFT       (0x00u)
#define disp_sclk_DRIVE_MODE_MASK        (0x07u << disp_sclk_DRIVE_MODE_SHIFT)

#define disp_sclk_DM_ALG_HIZ         (0x00u << disp_sclk_DRIVE_MODE_SHIFT)
#define disp_sclk_DM_DIG_HIZ         (0x01u << disp_sclk_DRIVE_MODE_SHIFT)
#define disp_sclk_DM_RES_UP          (0x02u << disp_sclk_DRIVE_MODE_SHIFT)
#define disp_sclk_DM_RES_DWN         (0x03u << disp_sclk_DRIVE_MODE_SHIFT)
#define disp_sclk_DM_OD_LO           (0x04u << disp_sclk_DRIVE_MODE_SHIFT)
#define disp_sclk_DM_OD_HI           (0x05u << disp_sclk_DRIVE_MODE_SHIFT)
#define disp_sclk_DM_STRONG          (0x06u << disp_sclk_DRIVE_MODE_SHIFT)
#define disp_sclk_DM_RES_UPDWN       (0x07u << disp_sclk_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define disp_sclk_MASK               disp_sclk__MASK
#define disp_sclk_SHIFT              disp_sclk__SHIFT
#define disp_sclk_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define disp_sclk_PS                     (* (reg32 *) disp_sclk__PS)
/* Port Configuration */
#define disp_sclk_PC                     (* (reg32 *) disp_sclk__PC)
/* Data Register */
#define disp_sclk_DR                     (* (reg32 *) disp_sclk__DR)
/* Input Buffer Disable Override */
#define disp_sclk_INP_DIS                (* (reg32 *) disp_sclk__PC2)


#if defined(disp_sclk__INTSTAT)  /* Interrupt Registers */

    #define disp_sclk_INTSTAT                (* (reg32 *) disp_sclk__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins disp_sclk_H */


/* [] END OF FILE */
