/*
 * UartDev.h
 *
 *  Created on: 
 *      Author: 
 */

#ifndef UARTDev_H_
#define UARTDev_H_

#include "Semaphore.h"

typedef struct
{
	uint32_t _flag;
	//====== please implement necessary variables if need be ===================
} UART_DEV_TYPE;

extern UART_DEV_TYPE *pUartDev[];

UART_DEV_TYPE* UartDev_New();
void UartDev_Construct(UART_DEV_TYPE *obj);
bool UartDev_Open(UART_DEV_TYPE *obj, int baud, char parity, int bits, int stopbits);
bool UartDev_Close(UART_DEV_TYPE *obj);
void UartDev_Destroy(UART_DEV_TYPE *obj);

// This routine has to be a timed blocking call until
// either data received (return true) or 1000ms time(return false).
bool UartDev_Get(UART_DEV_TYPE *obj, BYTE *ch);

bool UartDev_Put(UART_DEV_TYPE *obj, BYTE data);

#endif /* UARTDev_H_ */
