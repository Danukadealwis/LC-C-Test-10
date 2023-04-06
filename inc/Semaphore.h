/*
 * Semaphore.h
 *
 *  Created on:
 *      Author:
 */

#ifndef OS_SPEC_SEMAPHORE_H_
#define OS_SPEC_SEMAPHORE_H_

#include <stdint.h>

typedef struct
{
    // =================================================
	// .... private properties hidden ...........
} SEMAPHORE_TYPE;

// To create and return a semaphore object instance.
SEMAPHORE_TYPE *Semaphore_New();

// To construct a semaphore object using the memory pointed to by obj.
// obj: pointer to the memory for the instance to be constructed.
void Semaphore_Construct(SEMAPHORE_TYPE *obj);

// To destroy the object (free the pointer in obj if necessary).
void Semaphore_Destroy(SEMAPHORE_TYPE *obj);

// To activate the semaphore. Only need to be called by the owner once.
// obj: pointer to the instance
bool Semaphore_Open(SEMAPHORE_TYPE *obj);

// To release a semaphore, i.e. other users will come out of the blocking Semaphore_Wait() call.
// obj: pointer to the instance
void Semaphore_Release(SEMAPHORE_TYPE *obj);

// To release a semaphore but only to be used in ISR routines, i.e. other users will come out of the blocking Semaphore_Wait() call.
// obj: pointer to the instance
bool Semaphore_ReleaseFromISR(SEMAPHORE_TYPE *obj);

// To wait for a semaphore, i.e. blocks until Semaphore_Release() being called.
// obj: pointer to the instance
void Semaphore_Wait(SEMAPHORE_TYPE *obj);

// To wait for a semaphore or wait for ms milliseconds, i.e. blocks until either Semaphore_Release() being called or timed out.
// obj: pointer to the instance
// ms: milliseconds to wait.
// Returns true if Semaphore_Release() has being called, false if timed out
bool Semaphore_Wait_Timed(SEMAPHORE_TYPE *obj,DWORD ms);

// To close this semaphore instance.
// obj: pointer to the instance
void Semaphore_Close(SEMAPHORE_TYPE *obj);


#endif /* OS_SPEC_SEMAPHORE_H_ */
