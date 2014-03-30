/*******************************************************************************
* File Name: IDAC_Low.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the IDAC_P4
*  component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_IDAC_IDAC_Low_H)
#define CY_IDAC_IDAC_Low_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Internal Type defines
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} IDAC_Low_BACKUP_STRUCT;


extern uint32 IDAC_Low_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define IDAC_Low_IDAC_RESOLUTION    (7u)
#define IDAC_Low_IDAC_RANGE         (0u)
#define IDAC_Low_IDAC_POLARITY      (0u)


/***************************************
*    Initial Parameter Constants
***************************************/
#define IDAC_Low_IDAC_INIT_VALUE    (120u)




/***************************************
*        Function Prototypes
***************************************/

void IDAC_Low_Init(void);
void IDAC_Low_Enable(void);
void IDAC_Low_Start(void);
void IDAC_Low_Stop(void);
void IDAC_Low_SetValue(uint32  value);
void IDAC_Low_SaveConfig(void);
void IDAC_Low_Sleep(void);
void IDAC_Low_RestoreConfig(void);
void IDAC_Low_Wakeup(void);


/***************************************
*            API Constants
***************************************/

#define IDAC_Low_IDAC_EN_MODE              (3u)
#define IDAC_Low_IDAC_CSD_EN               (1u)
#define IDAC_Low_IDAC_CSD_EN_POSITION      (31u)
#define IDAC_Low_IDAC_VALUE_POSITION       (IDAC_Low_cy_psoc4_idac__CSD_IDAC_SHIFT)
#define IDAC_Low_IDAC_MODE_SHIFT           (8u)
#define IDAC_Low_IDAC_POLARITY_POSITION    (IDAC_Low_cy_psoc4_idac__POLARITY_SHIFT)
#define IDAC_Low_IDAC_MODE_POSITION        ((uint32)IDAC_Low_cy_psoc4_idac__CSD_IDAC_SHIFT + \
                                                        (uint32)IDAC_Low_IDAC_MODE_SHIFT)
#define IDAC_Low_IDAC_RANGE_SHIFT          (10u)
#define IDAC_Low_IDAC_RANGE_POSITION       ((uint32)IDAC_Low_cy_psoc4_idac__CSD_IDAC_SHIFT + \
                                                        (uint32)IDAC_Low_IDAC_RANGE_SHIFT)

#define IDAC_Low_IDAC_CDS_EN_MASK      (0x80000000u)

#if(IDAC_Low_IDAC_RESOLUTION == 8u)
  #define IDAC_Low_IDAC_VALUE_MASK     (0xFFu)
#else
  #define IDAC_Low_IDAC_VALUE_MASK     (0x7Fu)
#endif /* (IDAC_Low_IDAC_RESOLUTION == 8u) */

#define IDAC_Low_IDAC_MODE_MASK        (3u)
#define IDAC_Low_IDAC_RANGE_MASK       (1u)
#define IDAC_Low_IDAC_POLARITY_MASK    (1u)


/***************************************
*        Registers
***************************************/

#define IDAC_Low_IDAC_CONTROL_REG    (*(reg32 *) (uint32)CYREG_CSD_IDAC)
#define IDAC_Low_IDAC_CONTROL_PTR    ( (reg32 *) CYREG_CSD_IDAC)

#define IDAC_Low_IDAC_POLARITY_CONTROL_REG    (*(reg32 *) CYREG_CSD_CONFIG)
#define IDAC_Low_IDAC_POLARITY_CONTROL_PTR    ( (reg32 *) CYREG_CSD_CONFIG)

#endif /* CY_IDAC_IDAC_Low_H */

/* [] END OF FILE */
