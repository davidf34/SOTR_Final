/*
 * Mutex.c
 *
 *  Created on: Apr 25, 2022
 *      Author: User
 */


#include "AppTypes.h"
#include "Mutex.h"
#include "portable.h"
#include "Queue.h"
#include "task.h"
#include "RTOS.h"
#include "scheduller.h"


u16 Mutex_Init (T_MUTEX_PTR Mutex, u8 InitStatus){
	
	u16 Res = MUTEX_ERROR_NULL_PARAM;
	if (Mutex != NULL){
		
		if(InitStatus){
			Mutex ->Status = TRUE;
			
		}
		else{
			Mutex->Status = FALSE;
		}
		Res = Queue_Init(&Mutex->MutexQueue);
		
	}
	return Res;
}

u8 Mutex_GetStatus (T_MUTEX_PTR Mutex){
	if(Mutex != NULL){
		return Mutex -> Status;
		
	}
	return 0;
}

u16 Mutex_Take(T_MUTEX_PTR Mutex){
	u16 Res= MUTEX_ERROR_NULL_PARAM;
	T_TCB_PTR Task;
	u8 CallScheduller = FALSE;
	if(Mutex != NULL){
		Portable_DisableInterrupts();
		if(!Mutex->Status){
			
			Mutex->Status=TRUE;
			Res = MUTEX_OK;
		}
		else{
			Task = Task_GetActualTask();
			if(Task != NULL){
				Task->TaskQueueElement.Data = Task;
				Task->TaskQueueElement.Next = NULL;
				Res = Queue_Enqueue(&Mutex->MutexQueue, &Task->TaskQueueElement);
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

u16 Mutex_Give (T_MUTEX_PTR Mutex){
	
	u16 Res = MUTEX_ERROR_NULL_PARAM;
    T_TCB_PTR Task;
    u8 ActualTaskPriority = RTOS_SYSTEM_PRIORITIES;
    T_QUEUE_ELEMENT_PTR Element = NULL;
    u8 CallScheduller = FALSE;
    if(Mutex != NULL){
    	Portable_DisableInterrupts();
    	if(Queue_GetCount(&Mutex->MutexQueue) > 0){
    		Task = Task_GetActualTask();
    		if(Task){
    			ActualTaskPriority = Task->TaskPriority;
    		}
    		Res = Queue_Dequeue(&Mutex ->MutexQueue, &Element);
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
    		Mutex->Status=FALSE;
    		Res = MUTEX_OK;
    	}
    	Portable_EnableInterrupts();
    	
    	if(CallScheduller){
    		Portable_SoftwareInterrupt();
    	}
    }
    return Res;
}
