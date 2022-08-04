
#include "AppTypes.h"
#include "task.h"
#include "RTOS.h"
#include "portable.h"
#include "Queue.h"


//#define TIMEROFF16 500
/**
 * 
 * DEFINICION DE FUNCIONES DEL MODULO
 * 
 */
v Task_DecrementTimers(v);


T_TCB_PTR ActualTask = NULL; 
T_QUEUE_HANDLER TimeBlockedTaskQueue; //acá se hizo un cambio


T_TCB_PTR Task_GetActualTask(void){
	return ActualTask;
}

u16 Task_Init(v)
{
	return Queue_Init(&TimeBlockedTaskQueue);
	
}

v Task_SetActualTask(T_TCB_PTR Task){
		
		ActualTask = Task;
	
}


u16 Task_Create(T_TCB_PTR TaskHandler,u16 Id, char * Name, u8 Priority, pu8 Stack, u16 StackSize, TaskFunction Function, void * Param ){
	u16 Count;
	u16 Res = TASK_ERROR_NULL_PARAM; 
	if((TaskHandler != NULL) && (Function != NULL) && (Stack != NULL ) && (StackSize > 0))//Se crea la tarea, verifica parámetros
	{
		Res = TASK_ERROR_PARAM_OUT_OF_RANGE;
		if(StackSize >= RTOS_MIN_STACK_SIZE	){//Verifica el tamaño mínimo del stack
			
			Res = TASK_OK;
			if(Priority > RTOS_MIN_PRIORITY){
				
				Priority = RTOS_MIN_PRIORITY;  
			}
			//revisar para aplicar cambios
			TaskHandler -> Id = Id;
			TaskHandler -> TaskName = Name;
			TaskHandler -> TaskPriority = Priority;
			TaskHandler -> TaskStackOverflow = FALSE;
			TaskHandler -> TaskParam = Param;
			TaskHandler -> TaskCallback = Function;
			TaskHandler -> TaskStack = Stack;
			TaskHandler -> TaskStackSize = StackSize; 
			TaskHandler -> TaskSleepTime = TIMEROFF16;
			TaskHandler -> TaskWaitEvents = 0;
			for (Count = 0; Count < StackSize; Count++)
			{
				Stack[Count] = RTOS_STACK_CHECK_BYTE;
			}
			TaskHandler -> TaskActualStack = (u16)Portable_InitTaskContext(&Stack[StackSize],Function, Param);
			Res = Scheduller_SetTaskToReadyQueue(TaskHandler);
			
		}
	}
	return Res;
}
u16 Task_CheckStack(T_TCB_PTR TaskHandler){
	u16 Count;
	u16 Res = TASK_ERROR_NULL_PARAM; 
	if(TaskHandler != NULL){
		Res = TASK_OK;
		for(Count = 0; Count <RTOS_STACK_CHECK_COUNT; Count++){
			if(TaskHandler->TaskStack[Count] != RTOS_STACK_CHECK_BYTE){
				TaskHandler ->TaskStackOverflow = TRUE;
				Res = TASK_ERROR_OVER_FLOW;
				//break; //ver si hay que ponerlo
			}
		} 
	}
	return Res;
}


u16 Task_Sleep (u16 SleepTicks)
{
	u8 CallScheduller = FALSE; 
	u16 Res = TASK_OK;	
	T_TCB_PTR Task;
	if (SleepTicks)
	{
		Portable_DisableInterrupts();
		if (SleepTicks == TIMEROFF16)
		{
			SleepTicks--; //El objetivo es dormir una tarea, por eso se desahabilitan las interrupciones 
		}
		Task = Task_GetActualTask();
		if (Task != NULL)
		{
			Task->TaskSleepTime = SleepTicks; //Con el TCB de la tarea, la pongo a dormir y la pongo en estado de bloqueo
			Task->Status = BLOCKED;
			Task->TaskQueueElement.Data = Task;
			Task->TaskQueueElement.Next = NULL;
			Res = Queue_Enqueue(&TimeBlockedTaskQueue, &Task -> TaskQueueElement);
			if (Res == QUEUE_OK)
			{
				CallScheduller = TRUE;
			}
			
		}
		Portable_EnableInterrupts();
		if (CallScheduller)
		{
			Portable_SoftwareInterrupt();//Scheduller busca una nueva tarea para ejecutarse
		}
	}
	return Res;
}
v Task_DecrementTimers(v)
{
	T_TCB_PTR Task;
	T_QUEUE_ELEMENT_PTR Element;
	T_QUEUE_HANDLER TempQueue;
	if(Queue_Init(&TempQueue)==QUEUE_OK)
	{
		while (Queue_Dequeue(&TimeBlockedTaskQueue, &Element)== QUEUE_OK)
		{
			if(Element != NULL)
			{
				if(Element -> Data != NULL)
				{
					Task = (T_TCB_PTR)Element -> Data;
					if (Task -> TaskSleepTime != TIMEROFF16)
					{
						Task -> TaskSleepTime--;
						if(Task->TaskSleepTime==0)
						{
							Task->TaskSleepTime = TIMEROFF16;
							Scheduller_SetTaskToReadyQueue(Task);
							
						}
						else
						{
							Queue_Enqueue(&TempQueue, Element);
						}
					}
					else
					{
						Scheduller_SetTaskToReadyQueue(Task);
					}
				}
			}
		}
		Queue_Copy(&TempQueue, &TimeBlockedTaskQueue);
	}
}


