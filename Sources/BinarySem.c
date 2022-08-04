/*
 * BinarySem.c
 *
 *  Created on: Apr 25, 2022
 *      Author: User
 */


#include "AppTypes.h"
#include "Semaforo.h"
#include "BinarySem.h"
#include "portable.h"
#include "Queue.h"
#include "task.h"
#include "RTOS.h"
#include "scheduller.h"


u16 BinarySem_Init (T_BINARY_SEM_PTR Sem, u8 InitStatus){
	
	return Semaforo_Init(Sem, 1, InitStatus ? 1:0 );
}

u8 BinarySem_GetStatus (T_BINARY_SEM_PTR Sem){
	
	return Semaforo_GetCount(Sem) > 0 ? TRUE : FALSE;
}


u16 BinarySem_Take(T_BINARY_SEM_PTR Sem){
	
	return Semaforo_Take(Sem);
}

u16 BinarySem_Give (T_BINARY_SEM_PTR Sem){
	
	
    return Semaforo_Give(Sem);
}

