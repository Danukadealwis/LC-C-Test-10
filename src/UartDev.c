/*
 * UartDev.h
 *
 *  Created on:
 *      Author:
 * 
 * Last Modified:
 */

#include "UartDev.h"

static void _UartDev_IRQHandler(UART_DEV_TYPE *p)
{
    if (p == NULL)return (0);
    if (p->_flag == UART_FLAG_RX_READY)
    {
		// === please implement =================
    }
    if (p->_flag == UART_FLAG_TX_READY)
    {
		// ==== please implement ================
    }
}

// This routine has to be a timed blocking call until
// either data received (return true) or 1000ms time(return false).
bool UartDev_Get(UART_DEV_TYPE *obj, BYTE *ch)
{
    if (obj == NULL)return (false);
	//======== please implement =================
    return(ret);
}

// returns number of bytes sent to tx buf.
bool UartDev_Put(UART_DEV_TYPE *obj, BYTE data)
{
    if (obj == NULL)return (false);
    bool ret = false;
	//============ please implement ====================
    return(ret);
}

