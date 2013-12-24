/*******************************************************************************
* File Name: disp_mosi.h  
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

#if !defined(CY_PINS_disp_mosi_H) /* Pins disp_mosi_H */
#define CY_PINS_disp_mosi_H

#include "cytypes.h"
#include "cyfitter.h"
#include "disp_mosi_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    disp_mosi_Write(uint8 value) ;
void    disp_mosi_SetDriveMode(uint8 mode) ;
uint8   disp_mosi_ReadDataReg(void) ;
uint8   disp_mosi_Read(void) ;
uint8   disp_mosi_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define disp_mosi_DRIVE_MODE_BITS        (3)
#define disp_mosi_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - disp_mosi_DRIVE_MODE_BITS))
#define disp_mosi_DRIVE_MODE_SHIFT       (0x00u)
#define disp_mosi_DRIVE_MODE_MASK        (0x07u << disp_mosi_DRIVE_MODE_SHIFT)

#define disp_mosi_DM_ALG_HIZ         (0x00u << disp_mosi_DRIVE_MODE_SHIFT)
#define disp_mosi_DM_DIG_HIZ         (0x01u << disp_mosi_DRIVE_MODE_SHIFT)
#define disp_mosi_DM_RES_UP          (0x02u << disp_mosi_DRIVE_MODE_SHIFT)
#define disp_mosi_DM_RES_DWN         (0x03u << disp_mosi_DRIVE_MODE_SHIFT)
#define disp_mosi_DM_OD_LO           (0x04u << disp_mosi_DRIVE_MODE_SHIFT)
#define disp_mosi_DM_OD_HI           (0x05u << disp_mosi_DRIVE_MODE_SHIFT)
#define disp_mosi_DM_STRONG          (0x06u << disp_mosi_DRIVE_MODE_SHIFT)
#define disp_mosi_DM_RES_UPDWN       (0x07u << disp_mosi_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define disp_mosi_MASK               disp_mosi__MASK
#define disp_mosi_SHIFT              disp_mosi__SHIFT
#define disp_mosi_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define disp_mosi_PS                     (* (reg32 *) disp_mosi__PS)
/* Port Configuration */
#define disp_mosi_PC                     (* (reg32 *) disp_mosi__PC)
/* Data Register */
#define disp_mosi_DR                     (* (reg32 *) disp_mosi__DR)
/* Input Buffer Disable Override */
#define disp_mosi_INP_DIS                (* (reg32 *) disp_mosi__PC2)


#if defined(disp_mosi__INTSTAT)  /* Interrupt Registers */

    #define disp_mosi_INTSTAT                (* (reg32 *) disp_mosi__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins disp_mosi_H */


/* [] END OF FILE */
