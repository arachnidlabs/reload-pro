/*******************************************************************************
* File Name: IDAC_Mux.h
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

#if !defined(CY_AMUX_IDAC_Mux_H)
#define CY_AMUX_IDAC_Mux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void IDAC_Mux_Start(void) ;
#define IDAC_Mux_Init() IDAC_Mux_Start()
void IDAC_Mux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void IDAC_Mux_Stop(void); */
/* void IDAC_Mux_Select(uint8 channel); */
/* void IDAC_Mux_Connect(uint8 channel); */
/* void IDAC_Mux_Disconnect(uint8 channel); */
/* void IDAC_Mux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define IDAC_Mux_CHANNELS  2u
#define IDAC_Mux_MUXTYPE   1
#define IDAC_Mux_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define IDAC_Mux_NULL_CHANNEL 0xFFu
#define IDAC_Mux_MUX_SINGLE   1
#define IDAC_Mux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if IDAC_Mux_MUXTYPE == IDAC_Mux_MUX_SINGLE
# if !IDAC_Mux_ATMOSTONE
#  define IDAC_Mux_Connect(channel) IDAC_Mux_Set(channel)
# endif
# define IDAC_Mux_Disconnect(channel) IDAC_Mux_Unset(channel)
#else
# if !IDAC_Mux_ATMOSTONE
void IDAC_Mux_Connect(uint8 channel) ;
# endif
void IDAC_Mux_Disconnect(uint8 channel) ;
#endif

#if IDAC_Mux_ATMOSTONE
# define IDAC_Mux_Stop() IDAC_Mux_DisconnectAll()
# define IDAC_Mux_Select(channel) IDAC_Mux_FastSelect(channel)
void IDAC_Mux_DisconnectAll(void) ;
#else
# define IDAC_Mux_Stop() IDAC_Mux_Start()
void IDAC_Mux_Select(uint8 channel) ;
# define IDAC_Mux_DisconnectAll() IDAC_Mux_Start()
#endif

#endif /* CY_AMUX_IDAC_Mux_H */


/* [] END OF FILE */
