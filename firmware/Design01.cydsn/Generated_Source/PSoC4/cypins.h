/*******************************************************************************
* File Name: cypins.h
* Version 4.0
*
*  Description:
*   This file contains the function prototypes and constants used for port/pin
*   in access and control.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BOOT_CYPINS_H)
#define CY_BOOT_CYPINS_H

#include "cytypes.h"


/**************************************
*       Register Constants
**************************************/


#define CY_SYS_PINS_PC_DATAOUT                 ((uint32) 0x01u)
#define CY_SYS_PINS_PC_DRIVE_MODE_BITS         ((uint32) 0x03u)
#define CY_SYS_PINS_PC_DRIVE_MODE_MASK         ((uint32) 0x07u)


/**************************************
*        API Parameter Constants
**************************************/

/*  SetPinDriveMode */
#define CY_SYS_PINS_DM_ALG_HIZ                ((uint32) 0x00u)
#define CY_SYS_PINS_DM_DIG_HIZ                ((uint32) 0x01u)
#define CY_SYS_PINS_DM_RES_UP                 ((uint32) 0x02u)
#define CY_SYS_PINS_DM_RES_DWN                ((uint32) 0x03u)
#define CY_SYS_PINS_DM_OD_LO                  ((uint32) 0x04u)
#define CY_SYS_PINS_DM_OD_HI                  ((uint32) 0x05u)
#define CY_SYS_PINS_DM_STRONG                 ((uint32) 0x06u)
#define CY_SYS_PINS_DM_RES_UPDWN              ((uint32) 0x07u)


/**************************************
*       Pin API Macros
**************************************/


/*******************************************************************************
* Macro Name: CY_SYS_PINS_READ_PIN
********************************************************************************
* Summary:
*  Reads the current value on the pin (pin state, PS).
*
* Parameters:
*   portPS: Address of port pin status register (uint32). Definitions for the
*   each port are provided in the cydevice_trm.h file in the form:
*   CYREG_PRTx_PS, where x is a port number 0 - 4.
*
*   pin: pin number 0 - 7
*
* Return:
*   Pin state:
*    0: Logic low value
*    Non-0: Logic high value
*
*******************************************************************************/
#define CY_SYS_PINS_READ_PIN(portPS, pin)    \
            (( *(reg32 *)(portPS) & (CY_SYS_PINS_PC_DATAOUT << (pin)) ) >> (pin))


/*******************************************************************************
* Macro Name: CY_SYS_PINS_SET_PIN
********************************************************************************
* Summary:
*  Set the output value for the pin (data register, DR) to a logic high.
*  Note that this only has an effect for pins configured as software pins that
*  are not driven by hardware.
*
* Parameters:
*   portDR: Address of port output pin data register (uint32). Definitions for
*   the each port are provided in the cydevice_trm.h file in the form:
*   CYREG_PRTx_DR, where x is a port number 0 - 4.
*
*   pin: pin number 0 - 7.
*
* Return:
*   None
*
*******************************************************************************/
#define CY_SYS_PINS_SET_PIN(portDR, pin)     \
            ( *(reg32 *)(portDR) |= (CY_SYS_PINS_PC_DATAOUT << (pin)) )


/*******************************************************************************
* Macro Name: CY_SYS_PINS_CLEAR_PIN
********************************************************************************
* Summary:
*  This macro sets the state of the specified pin to zero.
*
* Parameters:
*   portDR: Address of port output pin data register (uint32). Definitions for
*   the each port are provided in the cydevice_trm.h file in the form:
*   CYREG_PRTx_DR, where x is a port number 0 - 4.
*
*   where x is a port number 0 - 4
*
*   pin: pin number 0 - 7
*
* Return:
*   None
*
*******************************************************************************/
#define CY_SYS_PINS_CLEAR_PIN(portDR, pin)   \
            ( *(reg32 *)(portDR) &= ~(CY_SYS_PINS_PC_DATAOUT << (pin)) )


/*******************************************************************************
* Macro Name: CY_SYS_PINS_SET_DRIVE_MODE
********************************************************************************
* Summary:
*  Sets the drive mode for the pin (DM).
*
* Parameters:
*   portPC: Address of port configuration register (uint32). Definitions for the
*   each port are provided in the cydevice_trm.h file in the form:
*   CYREG_PRTx_PC, where x is a port number 0 - 4.
*
*   pin: pin number 0 - 7
*
*   mode: Desired drive mode
*
*        Define                        Source
*   CY_SYS_PINS_DM_ALG_HIZ        Analog HiZ
*   CY_SYS_PINS_DM_DIG_HIZ        Digital HiZ
*   CY_SYS_PINS_DM_RES_UP         Resistive pull up
*   CY_SYS_PINS_DM_RES_DWN        Resistive pull down
*   CY_SYS_PINS_DM_OD_LO          Open drain - drive low
*   CY_SYS_PINS_DM_OD_HI          Open drain - drive high
*   CY_SYS_PINS_DM_STRONG         Strong CMOS Output
*   CY_SYS_PINS_DM_RES_UPDWN      Resistive pull up/down
*
* Return:
*   None
*
*******************************************************************************/
#define CY_SYS_PINS_SET_DRIVE_MODE(portPC, pin, mode)    \
            ( *(reg32 *)(portPC) = (*(reg32 *)(portPC) & \
            ~(CY_SYS_PINS_PC_DRIVE_MODE_MASK << ((pin) * CY_SYS_PINS_PC_DRIVE_MODE_BITS))) | \
            ((mode) << ((pin) * CY_SYS_PINS_PC_DRIVE_MODE_BITS)))


/*******************************************************************************
* Macro Name: CY_SYS_PINS_READ_DRIVE_MODE
********************************************************************************
* Summary:
*  Reads the drive mode for the pin (DM).
*
* Parameters:
*   portPC: Address of port configuration register (uint32). Definitions for the
*   each port are provided in the cydevice_trm.h file in the form:
*   CYREG_PRTx_PC, where x is a port number 0 - 4.
*
*   pin: pin number 0 - 7.
*
*
* Return:
*   mode:  Current drive mode for the pin
*
*     Define                          Source
*   CY_SYS_PINS_DM_ALG_HIZ        Analog HiZ
*   CY_SYS_PINS_DM_DIG_HIZ        Digital HiZ
*   CY_SYS_PINS_DM_RES_UP         Resistive pull up
*   CY_SYS_PINS_DM_RES_DWN        Resistive pull down
*   CY_SYS_PINS_DM_OD_LO          Open drain - drive low
*   CY_SYS_PINS_DM_OD_HI          Open drain - drive high
*   CY_SYS_PINS_DM_STRONG         Strong CMOS Output
*   CY_SYS_PINS_DM_RES_UPDWN      Resistive pull up/down
*
*******************************************************************************/
#define CY_SYS_PINS_READ_DRIVE_MODE(portPC, pin)     \
        (( *(reg32 *)(portPC) & \
        (CY_SYS_PINS_PC_DRIVE_MODE_MASK << ((pin) * CY_SYS_PINS_PC_DRIVE_MODE_BITS)) ) >> \
        (pin) * CY_SYS_PINS_PC_DRIVE_MODE_BITS)


#endif /* (CY_BOOT_CYPINS_H) */


/* [] END OF FILE */
