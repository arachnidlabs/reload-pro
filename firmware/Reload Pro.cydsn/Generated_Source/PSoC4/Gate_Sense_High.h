/*******************************************************************************
* File Name: Gate_Sense_High.h  
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

#if !defined(CY_PINS_Gate_Sense_High_H) /* Pins Gate_Sense_High_H */
#define CY_PINS_Gate_Sense_High_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Gate_Sense_High_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Gate_Sense_High_Write(uint8 value) ;
void    Gate_Sense_High_SetDriveMode(uint8 mode) ;
uint8   Gate_Sense_High_ReadDataReg(void) ;
uint8   Gate_Sense_High_Read(void) ;
uint8   Gate_Sense_High_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Gate_Sense_High_DRIVE_MODE_BITS        (3)
#define Gate_Sense_High_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Gate_Sense_High_DRIVE_MODE_BITS))
#define Gate_Sense_High_DRIVE_MODE_SHIFT       (0x00u)
#define Gate_Sense_High_DRIVE_MODE_MASK        (0x07u << Gate_Sense_High_DRIVE_MODE_SHIFT)

#define Gate_Sense_High_DM_ALG_HIZ         (0x00u << Gate_Sense_High_DRIVE_MODE_SHIFT)
#define Gate_Sense_High_DM_DIG_HIZ         (0x01u << Gate_Sense_High_DRIVE_MODE_SHIFT)
#define Gate_Sense_High_DM_RES_UP          (0x02u << Gate_Sense_High_DRIVE_MODE_SHIFT)
#define Gate_Sense_High_DM_RES_DWN         (0x03u << Gate_Sense_High_DRIVE_MODE_SHIFT)
#define Gate_Sense_High_DM_OD_LO           (0x04u << Gate_Sense_High_DRIVE_MODE_SHIFT)
#define Gate_Sense_High_DM_OD_HI           (0x05u << Gate_Sense_High_DRIVE_MODE_SHIFT)
#define Gate_Sense_High_DM_STRONG          (0x06u << Gate_Sense_High_DRIVE_MODE_SHIFT)
#define Gate_Sense_High_DM_RES_UPDWN       (0x07u << Gate_Sense_High_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Gate_Sense_High_MASK               Gate_Sense_High__MASK
#define Gate_Sense_High_SHIFT              Gate_Sense_High__SHIFT
#define Gate_Sense_High_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Gate_Sense_High_PS                     (* (reg32 *) Gate_Sense_High__PS)
/* Port Configuration */
#define Gate_Sense_High_PC                     (* (reg32 *) Gate_Sense_High__PC)
/* Data Register */
#define Gate_Sense_High_DR                     (* (reg32 *) Gate_Sense_High__DR)
/* Input Buffer Disable Override */
#define Gate_Sense_High_INP_DIS                (* (reg32 *) Gate_Sense_High__PC2)


#if defined(Gate_Sense_High__INTSTAT)  /* Interrupt Registers */

    #define Gate_Sense_High_INTSTAT                (* (reg32 *) Gate_Sense_High__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Gate_Sense_High_H */


/* [] END OF FILE */
