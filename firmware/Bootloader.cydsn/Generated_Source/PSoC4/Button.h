/*******************************************************************************
* File Name: Button.h  
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

#if !defined(CY_PINS_Button_H) /* Pins Button_H */
#define CY_PINS_Button_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Button_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Button_Write(uint8 value) ;
void    Button_SetDriveMode(uint8 mode) ;
uint8   Button_ReadDataReg(void) ;
uint8   Button_Read(void) ;
uint8   Button_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Button_DRIVE_MODE_BITS        (3)
#define Button_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Button_DRIVE_MODE_BITS))
#define Button_DRIVE_MODE_SHIFT       (0x00u)
#define Button_DRIVE_MODE_MASK        (0x07u << Button_DRIVE_MODE_SHIFT)

#define Button_DM_ALG_HIZ         (0x00u << Button_DRIVE_MODE_SHIFT)
#define Button_DM_DIG_HIZ         (0x01u << Button_DRIVE_MODE_SHIFT)
#define Button_DM_RES_UP          (0x02u << Button_DRIVE_MODE_SHIFT)
#define Button_DM_RES_DWN         (0x03u << Button_DRIVE_MODE_SHIFT)
#define Button_DM_OD_LO           (0x04u << Button_DRIVE_MODE_SHIFT)
#define Button_DM_OD_HI           (0x05u << Button_DRIVE_MODE_SHIFT)
#define Button_DM_STRONG          (0x06u << Button_DRIVE_MODE_SHIFT)
#define Button_DM_RES_UPDWN       (0x07u << Button_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Button_MASK               Button__MASK
#define Button_SHIFT              Button__SHIFT
#define Button_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button_PS                     (* (reg32 *) Button__PS)
/* Port Configuration */
#define Button_PC                     (* (reg32 *) Button__PC)
/* Data Register */
#define Button_DR                     (* (reg32 *) Button__DR)
/* Input Buffer Disable Override */
#define Button_INP_DIS                (* (reg32 *) Button__PC2)


#if defined(Button__INTSTAT)  /* Interrupt Registers */

    #define Button_INTSTAT                (* (reg32 *) Button__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Button_H */


/* [] END OF FILE */
