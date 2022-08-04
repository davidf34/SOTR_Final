/*
 * RTOS.c
 *
 *  Created on: Mar 14, 2022
 *      Author: User
 */
#include "AppTypes.h"
#include "RTOS.h"
#include "scheduller.h"
#include "task.h"

/*
 * 
 * Definición de variables internas del modulo
 * 
 */
v RTOS_IdleTask(pv Param);
u16 RTOS_CreateIdleTask(v);


T_TCB	IdleTaskHandler;
u8		IdleTaskStack[RTOS_IDLE_TASK_STACK_SIZE];


v RTOS_IdleTask(pv Param){
	for(;;){
		
	}
}


u16 RTOS_Init(v)
{
	u16 Res;
	Res = Task_Init();
	if (Res == TASK_OK)
	{
		Res = Scheduller_Init();
		
	}
	return Res; //Linea que cambio en su totalidad
}
u16 RTOS_Start(v)
{
	u16	Res;
	u16	FirstTaskSP;
	Res = RTOS_CreateIdleTask();
	
	if(Res){
		
		return Res; //Creacion de la tarea inactiva del sistema
	}
	//IdleTaskHandler.TaskPriority = RTOS_IDLE_TASK_PRIORITY; //Tarea inactiva, se le asigna la prioridad de tarea inactiva
	FirstTaskSP = Scheduller_Coperative(0);//Busca el actual task en el Scheduller
	Portable_InitTickRTC();
	Portable_RestoreManualContext(FirstTaskSP);
	return Res;
	
}

u16 RTOS_CreateIdleTask(v){ //Creacion exclusiva para la tarea inactiva
	u16 Count;
	u16 Res = TASK_ERROR_NULL_PARAM; 
	if( (IdleTaskStack != NULL) && (RTOS_IDLE_TASK_STACK_SIZE >0))//Se crea la tarea, verifica parámetros
	{
		Res = TASK_ERROR_PARAM_OUT_OF_RANGE;
		if(RTOS_IDLE_TASK_STACK_SIZE >= RTOS_MIN_STACK_SIZE	){//Verifica el tamaño mínimo del stack
			
			Res = RTOS_OK;
			//revisar para aplicar cambios
			IdleTaskHandler.Id 					= RTOS_IDLE_TASK_ID;
			IdleTaskHandler.TaskName 			= RTOS_IDLE_TASK_NAME;
			IdleTaskHandler.TaskPriority		= RTOS_IDLE_TASK_PRIORITY; //Asignamos la prioridad numero 8 y asignamos a las tareas listas por ejecutarse
			IdleTaskHandler.TaskStackOverflow	= FALSE; //Nos hace falta TaskStackOverflow
			IdleTaskHandler.TaskParam			= NULL;
			IdleTaskHandler.TaskCallback		= RTOS_IdleTask;
			IdleTaskHandler.TaskStack  			= IdleTaskStack;
			IdleTaskHandler.TaskStackSize 		= RTOS_IDLE_TASK_STACK_SIZE; 
			IdleTaskHandler.TaskSleepTime 		= TIMEROFF16;
			IdleTaskHandler.TaskWaitEvents		= 0;
			for (Count = 0; Count < RTOS_IDLE_TASK_STACK_SIZE; Count++)
			{
				IdleTaskStack[Count] = RTOS_STACK_CHECK_BYTE;
			}
			IdleTaskHandler.TaskActualStack = (u16)Portable_InitTaskContext(&IdleTaskStack[RTOS_IDLE_TASK_STACK_SIZE],IdleTaskHandler.TaskCallback, IdleTaskHandler.TaskParam);
			Res = RTOS_OK;
			
		}
	}
	return Res;
}

