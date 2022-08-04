/*
 * Semafoto.h
 *
 *  Created on: Apr 23, 2022
 *      Author: User
 */

#ifndef SEMAFOTO_H_
#define SEMAFOTO_H_

#include "AppTypes.h"
#include "Queue.h"

//el semaforo cuenta para sdaber si tiene que restringir o no el acceso

#define SEMAPHORE_OK 							0
#define SEMAPHORE_ERROR_UNKNOW					SEMAPHORE_BASE_ERROR | BASE_ERROR_UNKNOW
#define SEMAPHORE_ERROR_NULL_PARAM 				SEMAPHORE_BASE_ERROR | BASE_ERROR_NULL_PARAM
#define SEMAPHORE_ERROR_EMPTY 					SEMAPHORE_BASE_ERROR | BASE_ERROR_UNKNOW
#define SEMAPHORE_ERROR_PARAM_OUT_OF_RANGE 		SEMAPHORE_BASE_ERROR | BASE_ERROR_PARAM_OUT_OF_RANGE


typedef struct{
	u16 Count;
	u16 Limit;
	T_QUEUE_HANDLER SemQueue;
	
}T_SEMAPHORE,* T_SEMAPHORE_PTR;


u16 Semaforo_Init (T_SEMAPHORE_PTR Sem, u16 CountLimit, u16 InitCount);
u16 Semaforo_GetCount (T_SEMAPHORE_PTR Sem);
u16 Semaforo_GetLimit (T_SEMAPHORE_PTR Sem);
u16 Semaforo_Take(T_SEMAPHORE_PTR Sem);
u16 Semaforo_Give (T_SEMAPHORE_PTR Sem);

#endif /* SEMAFOTO_H_ */
