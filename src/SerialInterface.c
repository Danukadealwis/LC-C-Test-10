/*
 * SerialInterface.c
 *
 *  Created on:
 *      Author:
 * Last Modified:
  */

#include "../inc/SerialInterface.h"


void SerialInterface_Construct(SERIAL_INTERFACE_TYPE *obj,const char *name,const ENUM_THREAD_PRIORITY_TYPE priority,int stackSize,
                                void *owner,void (*callback)(const void*,const BYTE *,size_t))
{
//    if(obj == NULL)return;
    memset(obj,0,sizeof(*obj));
    obj->name = name;
    obj->_opened = false; // necessary?
    obj->_owner = owner;
    obj->_callback = callback; // callback is used to send to application where it will print through standard printf
    pUartDev[0] = UartDev_New();
    pUartDev[1] = UartDev_New();
    UartDev_Construct(pUartDev[0], UART_FLAG_RX_NOT_READY);
    UartDev_Construct(pUartDev[1], UART_FLAG_TX_NOT_READY);
    UartDev_Open(pUartDev[0], UART_BAUD_RATE, UART_ODD_PARITY, UART_DATA_BITS_SIZE, UART_STOP_BITS);
    UartDev_Open(pUartDev[1], UART_BAUD_RATE, UART_ODD_PARITY, UART_DATA_BITS_SIZE, UART_STOP_BITS);
    obj->_interfaceThread = Thread_New("Serial_Interface_Thread", priority, stackSize, owner,  SerialInterfaceRead(obj,&obj->_read_data));
}

void SerialInterface_Destroy(SERIAL_INTERFACE_TYPE *obj)
{
    if(obj == NULL)return;
	free(obj);
}

bool SerialInterface_Open(SERIAL_INTERFACE_TYPE *obj)
{
    if (obj == NULL)return (false);
	obj->_opened = true;
    return Thread_Start(obj->_interfaceThread);
}

bool SerialInterface_Close(SERIAL_INTERFACE_TYPE *obj)
{
    if(obj == NULL)return(false);
	obj->_opened = false;
    return Thread_Stop(obj->_interfaceThread);
}

void * SerialInterfaceRead(SERIAL_INTERFACE_TYPE * obj, BYTE *data){
    if(obj != NULL) {
        if (obj->_opened && pUartDev[0]->opened) {
            if(UartDev_Get(pUartDev[0], data)){
                obj->_byteCount++;
                return (void *) true;
            }
        }
    }
    return false;
}

bool SerialInterface_Write(SERIAL_INTERFACE_TYPE *obj,const BYTE *data, size_t len)
{
	if(obj != NULL) {
        if (obj->_opened && pUartDev[1]->opened) {
            for(int i = 0; i < len ;i++){
                    UartDev_Put(pUartDev[1],data[i]);
            }
            return true;
        }
    }
    return false;
}

int SerialInterface_Stats(SERIAL_INTERFACE_TYPE *obj){ // do these stats need to be sent out to the uartdev.c?
    int byteCount = obj->_byteCount;
    obj->_byteCount = 0;
    return byteCount;
}


