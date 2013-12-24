/*******************************************************************************
* File Name: Current_Sense.h  
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

#if !defined(CY_PINS_Current_Sense_H) /* Pins Current_Sense_H */
#define CY_PINS_Current_Sense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Current_Sense_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Current_Sense_Write(uint8 value) ;
void    Current_Sense_SetDriveMode(uint8 mode) ;
uint8   Current_Sense_ReadDataReg(void) ;
uint8   Current_Sense_Read(void) ;
uint8   Current_Sense_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Current_Sense_DRIVE_MODE_BITS        (3)
#define Current_Sense_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Current_Sense_DRIVE_MODE_BITS))
#define Current_Sense_DRIVE_MODE_SHIFT       (0x00u)
#define Current_Sense_DRIVE_MODE_MASK        (0x07u << Current_Sense_DRIVE_MODE_SHIFT)

#define Current_Sense_DM_ALG_HIZ         (0x00u << Current_Sense_DRIVE_MODE_SHIFT)
#define Current_Sense_DM_DIG_HIZ         (0x01u << Current_Sense_DRIVE_MODE_SHIFT)
#define Current_Sense_DM_RES_UP          (0x02u << Current_Sense_DRIVE_MODE_SHIFT)
#define Current_Sense_DM_RES_DWN         (0x03u << Current_Sense_DRIVE_MODE_SHIFT)
#define Current_Sense_DM_OD_LO           (0x04u << Current_Sense_DRIVE_MODE_SHIFT)
#define Current_Sense_DM_OD_HI           (0x05u << Current_Sense_DRIVE_MODE_SHIFT)
#define Current_Sense_DM_STRONG          (0x06u << Current_Sense_DRIVE_MODE_SHIFT)
#define Current_Sense_DM_RES_UPDWN       (0x07u << Current_Sense_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Current_Sense_MASK               Current_Sense__MASK
#define Current_Sense_SHIFT              Current_Sense__SHIFT
#define Current_Sense_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Current_Sense_PS                     (* (reg32 *) Current_Sense__PS)
/* Port Configuration */
#define Current_Sense_PC                     (* (reg32 *) Current_Sense__PC)
/* Data Register */
#define Current_Sense_DR                     (* (reg32 *) Current_Sense__DR)
/* Input Buffer Disable Override */
#define Current_Sense_INP_DIS                (* (reg32 *) Current_Sense__PC2)


#if defined(Current_Sense__INTSTAT)  /* Interrupt Registers */

    #define Current_Sense_INTSTAT                (* (reg32 *) Current_Sense__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Current_Sense_H */


/* [] END OF FILE */
