/*******************************************************************************
* File Name: AMux_2.h
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

#if !defined(CY_AMUX_AMux_2_H)
#define CY_AMUX_AMux_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void AMux_2_Start(void) ;
#define AMux_2_Init() AMux_2_Start()
void AMux_2_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void AMux_2_Stop(void); */
/* void AMux_2_Select(uint8 channel); */
/* void AMux_2_Connect(uint8 channel); */
/* void AMux_2_Disconnect(uint8 channel); */
/* void AMux_2_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define AMux_2_CHANNELS  2u
#define AMux_2_MUXTYPE   1
#define AMux_2_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define AMux_2_NULL_CHANNEL 0xFFu
#define AMux_2_MUX_SINGLE   1
#define AMux_2_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if AMux_2_MUXTYPE == AMux_2_MUX_SINGLE
# if !AMux_2_ATMOSTONE
#  define AMux_2_Connect(channel) AMux_2_Set(channel)
# endif
# define AMux_2_Disconnect(channel) AMux_2_Unset(channel)
#else
# if !AMux_2_ATMOSTONE
void AMux_2_Connect(uint8 channel) ;
# endif
void AMux_2_Disconnect(uint8 channel) ;
#endif

#if AMux_2_ATMOSTONE
# define AMux_2_Stop() AMux_2_DisconnectAll()
# define AMux_2_Select(channel) AMux_2_FastSelect(channel)
void AMux_2_DisconnectAll(void) ;
#else
# define AMux_2_Stop() AMux_2_Start()
void AMux_2_Select(uint8 channel) ;
# define AMux_2_DisconnectAll() AMux_2_Start()
#endif

#endif /* CY_AMUX_AMux_2_H */


/* [] END OF FILE */
