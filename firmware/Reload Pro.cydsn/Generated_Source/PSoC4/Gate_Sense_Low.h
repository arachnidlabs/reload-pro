/*******************************************************************************
* File Name: Gate_Sense_Low.h  
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

#if !defined(CY_PINS_Gate_Sense_Low_H) /* Pins Gate_Sense_Low_H */
#define CY_PINS_Gate_Sense_Low_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Gate_Sense_Low_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Gate_Sense_Low_Write(uint8 value) ;
void    Gate_Sense_Low_SetDriveMode(uint8 mode) ;
uint8   Gate_Sense_Low_ReadDataReg(void) ;
uint8   Gate_Sense_Low_Read(void) ;
uint8   Gate_Sense_Low_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Gate_Sense_Low_DRIVE_MODE_BITS        (3)
#define Gate_Sense_Low_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Gate_Sense_Low_DRIVE_MODE_BITS))
#define Gate_Sense_Low_DRIVE_MODE_SHIFT       (0x00u)
#define Gate_Sense_Low_DRIVE_MODE_MASK        (0x07u << Gate_Sense_Low_DRIVE_MODE_SHIFT)

#define Gate_Sense_Low_DM_ALG_HIZ         (0x00u << Gate_Sense_Low_DRIVE_MODE_SHIFT)
#define Gate_Sense_Low_DM_DIG_HIZ         (0x01u << Gate_Sense_Low_DRIVE_MODE_SHIFT)
#define Gate_Sense_Low_DM_RES_UP          (0x02u << Gate_Sense_Low_DRIVE_MODE_SHIFT)
#define Gate_Sense_Low_DM_RES_DWN         (0x03u << Gate_Sense_Low_DRIVE_MODE_SHIFT)
#define Gate_Sense_Low_DM_OD_LO           (0x04u << Gate_Sense_Low_DRIVE_MODE_SHIFT)
#define Gate_Sense_Low_DM_OD_HI           (0x05u << Gate_Sense_Low_DRIVE_MODE_SHIFT)
#define Gate_Sense_Low_DM_STRONG          (0x06u << Gate_Sense_Low_DRIVE_MODE_SHIFT)
#define Gate_Sense_Low_DM_RES_UPDWN       (0x07u << Gate_Sense_Low_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Gate_Sense_Low_MASK               Gate_Sense_Low__MASK
#define Gate_Sense_Low_SHIFT              Gate_Sense_Low__SHIFT
#define Gate_Sense_Low_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Gate_Sense_Low_PS                     (* (reg32 *) Gate_Sense_Low__PS)
/* Port Configuration */
#define Gate_Sense_Low_PC                     (* (reg32 *) Gate_Sense_Low__PC)
/* Data Register */
#define Gate_Sense_Low_DR                     (* (reg32 *) Gate_Sense_Low__DR)
/* Input Buffer Disable Override */
#define Gate_Sense_Low_INP_DIS                (* (reg32 *) Gate_Sense_Low__PC2)


#if defined(Gate_Sense_Low__INTSTAT)  /* Interrupt Registers */

    #define Gate_Sense_Low_INTSTAT                (* (reg32 *) Gate_Sense_Low__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Gate_Sense_Low_H */


/* [] END OF FILE */
