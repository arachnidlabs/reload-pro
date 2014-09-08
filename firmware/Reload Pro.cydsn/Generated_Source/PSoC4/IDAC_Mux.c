/*******************************************************************************
* File Name: IDAC_Mux.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "IDAC_Mux.h"

static uint8 IDAC_Mux_lastChannel = IDAC_Mux_NULL_CHANNEL;


/*******************************************************************************
* Function Name: IDAC_Mux_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void IDAC_Mux_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < IDAC_Mux_CHANNELS ; chan++)
    {
#if (IDAC_Mux_MUXTYPE == IDAC_Mux_MUX_SINGLE)
        IDAC_Mux_Unset(chan);
#else
        IDAC_Mux_CYAMUXSIDE_A_Unset(chan);
        IDAC_Mux_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    IDAC_Mux_lastChannel = IDAC_Mux_NULL_CHANNEL;
}


#if (!IDAC_Mux_ATMOSTONE)
/*******************************************************************************
* Function Name: IDAC_Mux_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void IDAC_Mux_Select(uint8 channel) 
{
    IDAC_Mux_DisconnectAll();        /* Disconnect all previous connections */
    IDAC_Mux_Connect(channel);       /* Make the given selection */
    IDAC_Mux_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: IDAC_Mux_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void IDAC_Mux_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( IDAC_Mux_lastChannel != IDAC_Mux_NULL_CHANNEL)
    {
        IDAC_Mux_Disconnect(IDAC_Mux_lastChannel);
    }

    /* Make the new channel connection */
#if (IDAC_Mux_MUXTYPE == IDAC_Mux_MUX_SINGLE)
    IDAC_Mux_Set(channel);
#else
    IDAC_Mux_CYAMUXSIDE_A_Set(channel);
    IDAC_Mux_CYAMUXSIDE_B_Set(channel);
#endif


    IDAC_Mux_lastChannel = channel;   /* Update last channel */
}


#if (IDAC_Mux_MUXTYPE == IDAC_Mux_MUX_DIFF)
#if (!IDAC_Mux_ATMOSTONE)
/*******************************************************************************
* Function Name: IDAC_Mux_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void IDAC_Mux_Connect(uint8 channel) 
{
    IDAC_Mux_CYAMUXSIDE_A_Set(channel);
    IDAC_Mux_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: IDAC_Mux_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void IDAC_Mux_Disconnect(uint8 channel) 
{
    IDAC_Mux_CYAMUXSIDE_A_Unset(channel);
    IDAC_Mux_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (IDAC_Mux_ATMOSTONE)
/*******************************************************************************
* Function Name: IDAC_Mux_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void IDAC_Mux_DisconnectAll(void) 
{
    if(IDAC_Mux_lastChannel != IDAC_Mux_NULL_CHANNEL) 
    {
        IDAC_Mux_Disconnect(IDAC_Mux_lastChannel);
        IDAC_Mux_lastChannel = IDAC_Mux_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
