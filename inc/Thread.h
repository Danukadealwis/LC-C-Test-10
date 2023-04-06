/*
 * Thread.h
 *
 *  Created on: 
 *      Author: 
 *
 * Last Modified:
 */

#ifndef OS_SPEC_THREAD_H_
#define OS_SPEC_THREAD_H_

#include <stdint.h>

typedef enum
{
    ENUM_PRIORITY_IDLE=1,
    ENUM_PRIORITY_LOW,
    ENUM_PRIORITY_BELOW_NORMAL,
    ENUM_PRIORITY_NORMAL,
    ENUM_PRIORITY_ABOVE_NORMAL,
    ENUM_PRIORITY_HIGH,
    ENUM_PRIORITY_REALTIME,
} ENUM_THREAD_PRIORITY_TYPE;

typedef struct
{
    char ThreadName[MAX_THREAD_NAME_SIZE];
    // =================================================
	// .... private properties hidden ...........
} THREAD_TYPE;

// To create and returns a thread object instance.
// name: The ASCII name for the thread.
// priority: thread priority (1 to 7 where 7 is the highest) 
// stackSize: Number of DWORDs reserved for as the stack for this thread.
// owner: the object instance needed to pass back to the exec below.
// exec: (think od it as the virtual function for this object) is the call back rouinte for the thread.
//       Returns from this routine will have the OS calls back in again.
//       The principle is not to stay in the exec forever and retuns from exec to allow thread health checks.
//       The owner object instance is passed as the single parameter when doing the call back.
THREAD_TYPE *Thread_New(const char *name,const ENUM_THREAD_PRIORITY_TYPE priority,int stackSize,
                            void *owner,void (*exec)(void const *));

// To construct a thread object using the memory pointed to by obj.
// obj: pointer to the memory for the instance to be constructed.
// name: The ASCII name for the thread.
// priority: thread priority (1 to 7 where 7 is the highest) 
// stackSize: Number of DWORDs reserved for as the stack for this thread.
// owner: the object instance needed to pass back to the exec below.
// exec: (think od it as the virtual function for this object) is the call back rouinte for the thread.
//       Returns from this routine will have the OS calls back in again.
//       The principle is not to stay in the exec forever and retuns from exec to allow thread health checks.
//       The owner object instance is passed as the single parameter when doing the call back.
void Thread_Construct(THREAD_TYPE *obj,const char *name,const ENUM_THREAD_PRIORITY_TYPE priority,int stackSize,
                            void *owner,void (*exec)(void const *));

// To destroy the object (free the pointer in obj if necessary).
void Thread_Destroy(THREAD_TYPE *obj);

// Start the thread, i.e. starts calling the exec callback.
// obj: pointer to the instance
bool Thread_Start(THREAD_TYPE *obj);

// suspend the thread, NOTE: stops calling exec after returned from exec.
// obj: pointer to the instance
void Thread_Suspend(THREAD_TYPE *obj);

// resume the thread, i.e. starts calling exec again.
// obj: pointer to the instance
void Thread_Resume(THREAD_TYPE *obj);

// Stop the thread, stops calling exec after returned from exec.
// Must call Thread_Stop() before calling Thread_WaitFinished()
// obj: pointer to the instance
bool Thread_Stop(THREAD_TYPE *obj);

// To be used in the exec to find out if Thread_Stop() has been called on this instance or not.
// obj: pointer to the instance
bool Thread_IsItTimeToExit(THREAD_TYPE *obj);

// To wait for exiting from exec so the Thread_Destroy() can be called to clean up.
// obj: pointer to the instance
// waitSec: 0 to wait forever, or how many seconeds to wait for exec to come back.
//          Kill the thread if not come back in time but can cause memory leaks if not careful. 
bool Thread_WaitFinished(THREAD_TYPE *obj,int waitSec);


// to be called by owner object instance to find out if the thread still healthy
bool Thread_HealthCheck(THREAD_TYPE *obj,int maxStallCount);

#endif /* OS_SPEC_THREAD_H_ */
