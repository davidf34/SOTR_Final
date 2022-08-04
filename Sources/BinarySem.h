/*
 * BinarySem.h
 *
 *  Created on: Apr 25, 2022
 *      Author: User
 */

#ifndef BINARYSEM_H_
#define BINARYSEM_H_

#include "AppTypes.h"
#include "Semaforo.h"

//el semaforo cuenta para sdaber si tiene que restringir o no el acceso

#define BINARY_SEM_OK 							0
#define BINARY_SEM_ERROR_UNKNOW					BINARY_SEM_BASE_ERROR | BASE_ERROR_UNKNOW
#define BINARY_SEM_ERROR_NULL_PARAM 			BINARY_SEM_BASE_ERROR | BASE_ERROR_NULL_PARAM
#define BINARY_SEM_ERROR_EMPTY 					BINARY_SEM_BASE_ERROR | BASE_ERROR_UNKNOW
#define BINARY_SEM_ERROR_PARAM_OUT_OF_RANGE 	BINARY_SEM_BASE_ERROR | BASE_ERROR_PARAM_OUT_OF_RANGE


typedef T_SEMAPHORE T_BINARY_SEM;
typedef T_SEMAPHORE_PTR T_BINARY_SEM_PTR;

u16 BinarySem_Init (T_BINARY_SEM_PTR Sem, u8 InitStatus);
u8 BinarySem_GetStatus (T_BINARY_SEM_PTR Sem);
u16 BinarySem_Take(T_BINARY_SEM_PTR Sem);
u16 BinarySem_Give (T_BINARY_SEM_PTR Sem);

#endif /* BINARYSEM_H_ */
