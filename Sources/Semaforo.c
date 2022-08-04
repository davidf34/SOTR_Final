/*
 * Semaforo.c
 *
 *  Created on: Apr 23, 2022
 *      Author: User
 */

#include "AppTypes.h"
#include "Semaforo.h"
#include "portable.h"
#include "Queue.h"
#include "task.h"
#include "RTOS.h"
#include "scheduller.h"


u16 Semaforo_Init (T_SEMAPHORE_PTR Sem, u16 CountLimit, u16 InitCount){
	
	u16 Res = SEMAPHORE_ERROR_NULL_PARAM;
	if (Sem != NULL){
		
		Res = SEMAPHORE_ERROR_PARAM_OUT_OF_RANGE;
		if(CountLimit > 0){
			if(InitCount > CountLimit){
				InitCount = CountLimit;
			}
			Sem -> Limit = CountLimit;
			Sem -> Count = InitCount;
			Res = Queue_Init(&Sem->SemQueue);
		}
	}
	return Res;
}

u16 Semaforo_GetCount (T_SEMAPHORE_PTR Sem){
	if(Sem != NULL){
		return Sem -> Count;
		
	}
	return 0;
}
u16 Semaforo_GetLimit (T_SEMAPHORE_PTR Sem){
	if (Sem != NULL){
		return Sem ->Limit;
	}
	return 0;
}
//11:03 am revisar

u16 Semaforo_Take(T_SEMAPHORE_PTR Sem){
	u16 Res= SEMAPHORE_ERROR_NULL_PARAM;
	T_TCB_PTR Task;
	u8 CallScheduller = FALSE;
	if(Sem != NULL){
		Portable_DisableInterrupts();
		if(Sem->Count < Sem->Limit){
			Sem->Count++;
			Res = SEMAPHORE_OK;
		}
		else{
			Task = Task_GetActualTask();
			if(Task != NULL){
				Task->TaskQueueElement.Data = Task;
				Task->TaskQueueElement.Next = NULL;
				Res = Queue_Enqueue(&Sem->SemQueue, &Task->TaskQueueElement);
				if(Res == QUEUE_OK){
					Task->Status = BLOCKED;
					CallScheduller = TRUE;
				}
			}
			
		}
		Portable_EnableInterrupts();
		if(CallScheduller){
			Portable_SoftwareInterrupt();
		}
	}
	return Res;
}

u16 Semaforo_Give (T_SEMAPHORE_PTR Sem){
	
	u16 Res = SEMAPHORE_ERROR_NULL_PARAM;
    T_TCB_PTR Task;
    u8 ActualTaskPriority = RTOS_SYSTEM_PRIORITIES;
    T_QUEUE_ELEMENT_PTR Element = NULL;
    u8 CallScheduller = FALSE;
    if(Sem != NULL){
    	Portable_DisableInterrupts();
    	if(Queue_GetCount(&Sem->SemQueue) > 0){
    		Task = Task_GetActualTask();
    		if(Task){
    			ActualTaskPriority = Task->TaskPriority;
    		}
    		Res = Queue_Dequeue(&Sem ->SemQueue, &Element);
    		if(Res == QUEUE_OK){
    			
    			Task = Element->Data;
    			if(Task !=NULL){
    				Res = Scheduller_SetTaskToReadyQueue(Task);
    				if (Res == SCHEDULLER_OK){
						if(Task->TaskPriority < ActualTaskPriority){
							CallScheduller = TRUE;
						}
    				}
    			}
    		}
    	}
    	else{
    		if(Sem->Count >0){
    		Sem-> Count --;
    		}
    		Res = SEMAPHORE_OK;
    	}
    	Portable_EnableInterrupts();
    	//acá falta algo :(
    	if(CallScheduller){
    		Portable_SoftwareInterrupt();
    	}
    }
    return Res;
}
