/*******************************************************************************
* File Name: Opamp_Mux.h
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

#if !defined(CY_AMUX_Opamp_Mux_H)
#define CY_AMUX_Opamp_Mux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void Opamp_Mux_Start(void) ;
#define Opamp_Mux_Init() Opamp_Mux_Start()
void Opamp_Mux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void Opamp_Mux_Stop(void); */
/* void Opamp_Mux_Select(uint8 channel); */
/* void Opamp_Mux_Connect(uint8 channel); */
/* void Opamp_Mux_Disconnect(uint8 channel); */
/* void Opamp_Mux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define Opamp_Mux_CHANNELS  2u
#define Opamp_Mux_MUXTYPE   1
#define Opamp_Mux_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define Opamp_Mux_NULL_CHANNEL 0xFFu
#define Opamp_Mux_MUX_SINGLE   1
#define Opamp_Mux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if Opamp_Mux_MUXTYPE == Opamp_Mux_MUX_SINGLE
# if !Opamp_Mux_ATMOSTONE
#  define Opamp_Mux_Connect(channel) Opamp_Mux_Set(channel)
# endif
# define Opamp_Mux_Disconnect(channel) Opamp_Mux_Unset(channel)
#else
# if !Opamp_Mux_ATMOSTONE
void Opamp_Mux_Connect(uint8 channel) ;
# endif
void Opamp_Mux_Disconnect(uint8 channel) ;
#endif

#if Opamp_Mux_ATMOSTONE
# define Opamp_Mux_Stop() Opamp_Mux_DisconnectAll()
# define Opamp_Mux_Select(channel) Opamp_Mux_FastSelect(channel)
void Opamp_Mux_DisconnectAll(void) ;
#else
# define Opamp_Mux_Stop() Opamp_Mux_Start()
void Opamp_Mux_Select(uint8 channel) ;
# define Opamp_Mux_DisconnectAll() Opamp_Mux_Start()
#endif

#endif /* CY_AMUX_Opamp_Mux_H */


/* [] END OF FILE */
