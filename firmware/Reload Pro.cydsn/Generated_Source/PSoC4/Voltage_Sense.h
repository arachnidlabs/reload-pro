/*******************************************************************************
* File Name: Voltage_Sense.h  
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

#if !defined(CY_PINS_Voltage_Sense_H) /* Pins Voltage_Sense_H */
#define CY_PINS_Voltage_Sense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Voltage_Sense_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Voltage_Sense_Write(uint8 value) ;
void    Voltage_Sense_SetDriveMode(uint8 mode) ;
uint8   Voltage_Sense_ReadDataReg(void) ;
uint8   Voltage_Sense_Read(void) ;
uint8   Voltage_Sense_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Voltage_Sense_DRIVE_MODE_BITS        (3)
#define Voltage_Sense_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Voltage_Sense_DRIVE_MODE_BITS))
#define Voltage_Sense_DRIVE_MODE_SHIFT       (0x00u)
#define Voltage_Sense_DRIVE_MODE_MASK        (0x07u << Voltage_Sense_DRIVE_MODE_SHIFT)

#define Voltage_Sense_DM_ALG_HIZ         (0x00u << Voltage_Sense_DRIVE_MODE_SHIFT)
#define Voltage_Sense_DM_DIG_HIZ         (0x01u << Voltage_Sense_DRIVE_MODE_SHIFT)
#define Voltage_Sense_DM_RES_UP          (0x02u << Voltage_Sense_DRIVE_MODE_SHIFT)
#define Voltage_Sense_DM_RES_DWN         (0x03u << Voltage_Sense_DRIVE_MODE_SHIFT)
#define Voltage_Sense_DM_OD_LO           (0x04u << Voltage_Sense_DRIVE_MODE_SHIFT)
#define Voltage_Sense_DM_OD_HI           (0x05u << Voltage_Sense_DRIVE_MODE_SHIFT)
#define Voltage_Sense_DM_STRONG          (0x06u << Voltage_Sense_DRIVE_MODE_SHIFT)
#define Voltage_Sense_DM_RES_UPDWN       (0x07u << Voltage_Sense_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Voltage_Sense_MASK               Voltage_Sense__MASK
#define Voltage_Sense_SHIFT              Voltage_Sense__SHIFT
#define Voltage_Sense_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Voltage_Sense_PS                     (* (reg32 *) Voltage_Sense__PS)
/* Port Configuration */
#define Voltage_Sense_PC                     (* (reg32 *) Voltage_Sense__PC)
/* Data Register */
#define Voltage_Sense_DR                     (* (reg32 *) Voltage_Sense__DR)
/* Input Buffer Disable Override */
#define Voltage_Sense_INP_DIS                (* (reg32 *) Voltage_Sense__PC2)


#if defined(Voltage_Sense__INTSTAT)  /* Interrupt Registers */

    #define Voltage_Sense_INTSTAT                (* (reg32 *) Voltage_Sense__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Voltage_Sense_H */


/* [] END OF FILE */
