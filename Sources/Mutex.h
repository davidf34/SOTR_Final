/*
 * Mutex.h
 *
 *  Created on: Apr 25, 2022
 *      Author: User
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include "AppTypes.h"
#include "Queue.h"


#define MUTEX_OK 							0
#define MUTEX_ERROR_UNKNOW					MUTEX_BASE_ERROR | BASE_ERROR_UNKNOW
#define MUTEX_ERROR_NULL_PARAM 				MUTEX_BASE_ERROR | BASE_ERROR_NULL_PARAM
#define MUTEX_ERROR_EMPTY 					MUTEX_BASE_ERROR | BASE_ERROR_UNKNOW
#define MUTEX_ERROR_PARAM_OUT_OF_RANGE 		MUTEX_BASE_ERROR | BASE_ERROR_PARAM_OUT_OF_RANGE


typedef struct{
	u8 Status;
	T_QUEUE_HANDLER MutexQueue;
	
}T_MUTEX,* T_MUTEX_PTR;


u16 Mutex_Init (T_MUTEX_PTR Mutex, u8 InitStatus);
u8  Mutex_GetStatus (T_MUTEX_PTR Mutex);
u16 Mutex_Take(T_MUTEX_PTR Mutex);
u16 Mutex_Give (T_MUTEX_PTR Mutex);

#endif /* MUTEX_H_ */
