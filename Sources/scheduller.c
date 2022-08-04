/*
 * 
 * Inclusi�n de librerias
 * 
 */
#include "AppTypes.h"
#include "scheduller.h"
#include "Queue.h"
#include "RTOS.h"
#include "task.h"

/*
 * 
 * DEFINICION DE VARIABLES GLOBALES INTERNAS EN EL MODULO
 * 
 */

extern T_TCB IdleTaskHandler;
T_QUEUE_HANDLER ReadyTaskList[RTOS_SYSTEM_PRIORITIES];


/*
 * Nombre		:Scheduller_Coperative
 * Descripci�n	:Funci�n encargada de buscar la siguiente tarea a ser 
 * 				ejecutada y guardar el SP de la tarea que se estaba 
 * 				ejecutando.
 * Par�metros	:ActualStackSP - SP de la tarea actual en ejecuci�n
 * Retonro		:u16 - El SP de la tarea que se va ejecutar
 * 
 */
u16 Scheduller_Init(void){
	u16 Res;
	u16 Count;
	for(Count = 0;Count < RTOS_SYSTEM_PRIORITIES; Count++){
		Res = Queue_Init(&ReadyTaskList[Count]);
		if(Res != SCHEDULLER_OK){
			break;
		}
	}
	return Res;
}

u16 Scheduller_Coperative(u16 ActualTaskSP){
    u16 Res;
    u16 Count;
    T_TCB_PTR Task =NULL;
    T_QUEUE_ELEMENT_PTR Element = NULL;
    Task = Task_GetActualTask();
    
    if(Task != NULL){
    	
    	if	(ActualTaskSP != 0){
    		Task ->TaskActualStack = ActualTaskSP;
    	}    		
    	
			if(Task != &IdleTaskHandler){
				if(Task_CheckStack(Task) == TASK_OK){
					if(Task->Status == RUNNING){ //si la tarea est� en running
						Res = Scheduller_SetTaskToReadyQueue(Task); //Se pone la tarea que ya esta lista para ejecutarse
						}
				}
			else{
				Task->Status = BLOCKED;
			}
				
    	}
		else{
			Task->Status = READY;//JMMM 
			}
    }
    Task = NULL;//se borra el apuntador de tarea

    for (Count = 0; Count < RTOS_SYSTEM_PRIORITIES; Count++)
    {// recorre para ver si hay tareas listas para ejecutar
    	
        if(Queue_GetCount(&ReadyTaskList[Count])>0){
            //se saca, se manda el handler de la cola donde se quiere desencolar
            Res = Queue_Dequeue(&ReadyTaskList[Count], &Element);
            if(Res == QUEUE_OK){
                if(Element != NULL){//SI LOGR� DESENCOLAR, EL APUNTADOR DE ELEMENTO SERA DIFERENTE A NULO 
                    Task = Element -> Data;//saca el TCB de la tarea y rompe el ciclo
                    break;
                	} 
            	}
        	}
    	}
    
if(Task == NULL){
    	Task = &IdleTaskHandler; 
    }
    Task -> Status = RUNNING; //pasa a estado de ejecuci�n
    Task_SetActualTask(Task);
    //se debe encontrar el stackpointer
    return Task->TaskActualStack;
    
}
u16 Scheduller_SetTaskToReadyQueue(T_TCB_PTR Task){
    u16 Res = SCHEDULLER_ERROR_NULL_PARAM; 
    if(Task != NULL){
        Task ->Status = READY;
        if(Task->TaskPriority < RTOS_SYSTEM_PRIORITIES){
            Task -> TaskQueueElement.Data = Task;
            Task -> TaskQueueElement.Next = NULL;
            Res  = Queue_Enqueue (&ReadyTaskList[Task->TaskPriority], &Task->TaskQueueElement);
        }
        else{
        	Res = SCHEDULLER_ERROR_PARAM_OUT_OF_RANGE;
        }
    }
    return Res;
    
}
