/*******************************************************************************
* File Name: AMux_1.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_AMux_1_H)
#define CY_AMUX_AMux_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void AMux_1_Start(void) ;
#define AMux_1_Init() AMux_1_Start()
void AMux_1_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void AMux_1_Stop(void); */
/* void AMux_1_Select(uint8 channel); */
/* void AMux_1_Connect(uint8 channel); */
/* void AMux_1_Disconnect(uint8 channel); */
/* void AMux_1_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define AMux_1_CHANNELS  2u
#define AMux_1_MUXTYPE   1
#define AMux_1_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define AMux_1_NULL_CHANNEL 0xFFu
#define AMux_1_MUX_SINGLE   1
#define AMux_1_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if AMux_1_MUXTYPE == AMux_1_MUX_SINGLE
# if !AMux_1_ATMOSTONE
#  define AMux_1_Connect(channel) AMux_1_Set(channel)
# endif
# define AMux_1_Disconnect(channel) AMux_1_Unset(channel)
#else
# if !AMux_1_ATMOSTONE
void AMux_1_Connect(uint8 channel) ;
# endif
void AMux_1_Disconnect(uint8 channel) ;
#endif

#if AMux_1_ATMOSTONE
# define AMux_1_Stop() AMux_1_DisconnectAll()
# define AMux_1_Select(channel) AMux_1_FastSelect(channel)
void AMux_1_DisconnectAll(void) ;
#else
# define AMux_1_Stop() AMux_1_Start()
void AMux_1_Select(uint8 channel) ;
# define AMux_1_DisconnectAll() AMux_1_Start()
#endif

#endif /* CY_AMUX_AMux_1_H */


/* [] END OF FILE */
