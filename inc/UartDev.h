/*
 * UartDev.h
 *
 *  Created on: 
 *      Author: 
 */

#ifndef UARTDev_H_
#define UARTDev_H_
#define UART_ODD_PARITY 1
#define UART_EVEN_PARITY 0
#define UART_STOP_BITS 2
#define UART_BAUD_RATE 115200
#define UART_DATA_BITS_SIZE 8

#include "Semaphore.h"
#include "StandardInc.h"
#include "CircularBuffer.h"
#include "Utils.h"
typedef enum{
    UART_FLAG_RX_READY,
    UART_FLAG_RX_NOT_READY,
    UART_FLAG_TX_READY,
    UART_FLAG_TX_NOT_READY,
} UART_FLAG;
typedef struct
{
	uint32_t _flag;
    cbuf_handle_t _circular_buffer_handle;
    bool opened;
    int baud_rate;
    char parity;
    int bits;
    int stopbits;
    bool processingSecondByte;
    BYTE data_frame;
    BYTE DR;
    uint16_t packet;
	//====== please implement necessary variables if need be ===================
} UART_DEV_TYPE;

extern UART_DEV_TYPE *pUartDev[];

UART_DEV_TYPE* UartDev_New();
void UartDev_Construct(UART_DEV_TYPE *obj, UART_FLAG flag);
bool UartDev_Open(UART_DEV_TYPE *obj, int baud, char parity, int bits, int stopbits);
bool UartDev_Close(UART_DEV_TYPE *obj);
void UartDev_Destroy(UART_DEV_TYPE *obj);
#ifdef UNIT_TESTING
int _UartDev_IRQHandler(UART_DEV_TYPE *p);
#endif
// This routine has to be a timed blocking call until
// either data received (return true) or 1000ms time(return false).
bool UartDev_Get(UART_DEV_TYPE *obj,  BYTE *ch);

int UartDev_Put(UART_DEV_TYPE *obj, BYTE data);

#endif /* UARTDev_H_ */
