/*******************************************************************************
* File Name: Opamp_Mux.c
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

#include "Opamp_Mux.h"

static uint8 Opamp_Mux_lastChannel = Opamp_Mux_NULL_CHANNEL;


/*******************************************************************************
* Function Name: Opamp_Mux_Start
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
void Opamp_Mux_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < Opamp_Mux_CHANNELS ; chan++)
    {
#if (Opamp_Mux_MUXTYPE == Opamp_Mux_MUX_SINGLE)
        Opamp_Mux_Unset(chan);
#else
        Opamp_Mux_CYAMUXSIDE_A_Unset(chan);
        Opamp_Mux_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    Opamp_Mux_lastChannel = Opamp_Mux_NULL_CHANNEL;
}


#if (!Opamp_Mux_ATMOSTONE)
/*******************************************************************************
* Function Name: Opamp_Mux_Select
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
void Opamp_Mux_Select(uint8 channel) 
{
    Opamp_Mux_DisconnectAll();        /* Disconnect all previous connections */
    Opamp_Mux_Connect(channel);       /* Make the given selection */
    Opamp_Mux_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: Opamp_Mux_FastSelect
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
void Opamp_Mux_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( Opamp_Mux_lastChannel != Opamp_Mux_NULL_CHANNEL)
    {
        Opamp_Mux_Disconnect(Opamp_Mux_lastChannel);
    }

    /* Make the new channel connection */
#if (Opamp_Mux_MUXTYPE == Opamp_Mux_MUX_SINGLE)
    Opamp_Mux_Set(channel);
#else
    Opamp_Mux_CYAMUXSIDE_A_Set(channel);
    Opamp_Mux_CYAMUXSIDE_B_Set(channel);
#endif


    Opamp_Mux_lastChannel = channel;   /* Update last channel */
}


#if (Opamp_Mux_MUXTYPE == Opamp_Mux_MUX_DIFF)
#if (!Opamp_Mux_ATMOSTONE)
/*******************************************************************************
* Function Name: Opamp_Mux_Connect
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
void Opamp_Mux_Connect(uint8 channel) 
{
    Opamp_Mux_CYAMUXSIDE_A_Set(channel);
    Opamp_Mux_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: Opamp_Mux_Disconnect
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
void Opamp_Mux_Disconnect(uint8 channel) 
{
    Opamp_Mux_CYAMUXSIDE_A_Unset(channel);
    Opamp_Mux_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (Opamp_Mux_ATMOSTONE)
/*******************************************************************************
* Function Name: Opamp_Mux_DisconnectAll
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
void Opamp_Mux_DisconnectAll(void) 
{
    if(Opamp_Mux_lastChannel != Opamp_Mux_NULL_CHANNEL) 
    {
        Opamp_Mux_Disconnect(Opamp_Mux_lastChannel);
        Opamp_Mux_lastChannel = Opamp_Mux_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
