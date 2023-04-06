/*
 * Mutex.h
 *
 *  Created on: 
 *      Author: 
 */

#ifndef OS_SPEC_MUTEX_H_
#define OS_SPEC_MUTEX_H_

#include <stdint.h>

typedef struct
{
    // =================================================
	// .... private properties hidden ...........
} MUTEX_TYPE;

// To create and return a mutex object instance.
MUTEX_TYPE *Mutex_New();

// To construct a mutex object using the memory pointed to by obj.
// obj: pointer to the memory for the instance to be constructed.
void Mutex_Construct(MUTEX_TYPE *obj);

// To destroy the object (free the pointer in obj if necessary).
void Mutex_Destroy(MUTEX_TYPE *obj);

// To activate the mutex. Only need to be called by the owner once.
// obj: pointer to the instance
bool Mutex_Open(MUTEX_TYPE *obj);

// To leave a mutex, i.e. other users will come out of the blocking Mutex_Enter() call.
// obj: pointer to the instance
void Mutex_Leave(MUTEX_TYPE *obj);

// To enter a mutex, i.e. blocks until Mutex_Leave() being called.
// obj: pointer to the instance
void Mutex_Enter(MUTEX_TYPE *obj);

// To enter a mutex and wait for ms milliseconds, i.e. blocks until either Mutex_Leave() being called or timed out.
// obj: pointer to the instance
// ms: milliseconds to wait.
// Returns true if Mutex_Leave() has being called, false if timed out
bool Mutex_Enter_Timed(MUTEX_TYPE *obj,DWORD ms);

// To close this mutex instance.
// obj: pointer to the instance
void Mutex_Close(MUTEX_TYPE *obj);



#endif /* OS_SPEC_MUTEX_H_ */
