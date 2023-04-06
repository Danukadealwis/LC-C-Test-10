/*
 * SerialInterface.c
 *
 *  Created on:
 *      Author:
 * Last Modified:
  */

#include "SerialInterface.h"

void SerialInterface_Construct(SERIAL_INTERFACE_TYPE *obj,const char *name,const ENUM_THREAD_PRIORITY_TYPE priority,int stackSize,
                                void *owner,void (*callback)(const void*,const BYTE *,size_t))
{
    if(obj == NULL)return;
    memset(obj,0,sizeof(*obj));
	//======== please implement =======================
}

void SerialInterface_Destroy(SERIAL_INTERFACE_TYPE *obj)
{
    if(obj == NULL)return;
	//======== please implement =======================
}

bool SerialInterface_Open(SERIAL_INTERFACE_TYPE *obj)
{
    if (obj == NULL)return (false);
	//======== please implement =======================
    return (ret);
}

bool SerialInterface_Close(SERIAL_INTERFACE_TYPE *obj)
{
    if(obj == NULL)return(false);
	// ============ please implement ==================
    return(true);
}

bool SerialInterface_Write(SERIAL_INTERFACE_TYPE *obj,const BYTE *data, size_t len)
{
	// ==== please implement ===================
    return(ok);
}


