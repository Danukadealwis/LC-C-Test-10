/*
 * SerialInterface.h
 *
 *  Created on: 
 *      Author: 
  */

#ifndef NETWORK_SERIALINTERFACE_H_
#define NETWORK_SERIALINTERFACE_H_

#include "Thread.h"
#include "UartDev.h"
#include "Mutex.h"

typedef struct
{
	bool _opened;
	UART_DEV_TYPE _port;
	void *_owner;
	void (*_callback)(const void *owner,const BYTE *data, size_t len);
	//============ fill necessary variables needed ===============
} SERIAL_INTERFACE_TYPE;

void SerialInterface_Construct(SERIAL_INTERFACE_TYPE *obj,const char *name,const ENUM_THREAD_PRIORITY_TYPE priority,int stackSize,
											void *owner,void (*callback)(const void*,const BYTE *,size_t));
void SerialInterface_Destroy(SERIAL_INTERFACE_TYPE *obj);
bool SerialInterface_Open(SERIAL_INTERFACE_TYPE *obj);
bool SerialInterface_Close(SERIAL_INTERFACE_TYPE *obj);

bool SerialInterface_Write(SERIAL_INTERFACE_TYPE *obj,const BYTE *data, size_t len);

#endif /* NETWORK_SERIALINTERFACE_H_ */
