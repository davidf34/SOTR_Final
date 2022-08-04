/*
 * task.h
 *
 *  Created on: Mar 13, 2022
 *      Author: User
 */

#ifndef TASK_H_
#define TASK_H_
#include "AppTypes.h"
#include "Queue.h"
#include "portable.h"
#include "Eventos.h"

#define TASK_OK			0
#define	TASK_ERROR_UNKNOW						TASK_BASE_ERROR | BASE_ERROR_UNKNOW
#define	TASK_ERROR_NULL_PARAM					TASK_BASE_ERROR | BASE_ERROR_NULL_PARAM
#define	TASK_ERROR_EMPTY						TASK_BASE_ERROR | BASE_ERROR_EMPTY
#define TASK_ERROR_PARAM_OUT_OF_RANGE			TASK_BASE_ERROR | BASE_ERROR_PARAM_OUT_OF_RANGE
#define TASK_ERROR_OVER_FLOW					TASK_BASE_ERROR | BASE_ERROR_OVER_FLOW


typedef enum{
	RUNNING = 0,
	READY,
	BLOCKED
}TaskStatus, * TaskStatus_PTR;


typedef struct{
	u16 Id;
	char *TaskName;
	TaskStatus	Status;
	u8 TaskPriority;
	u8 TaskStackOverflow;
	void *TaskParam;
	TaskFunction	TaskCallback;
	T_QUEUE_ELEMENT TaskQueueElement;
	pu8	TaskStack;
	u16	TaskStackSize;
	u16	TaskActualStack;
	u16	TaskSleepTime;
	T_EventReg TaskWaitEvents;
}T_TCB,* T_TCB_PTR;

/**
 * 
 * DEFINICION DE FUNCIONES DEL MODULO
 * 
 */

u16 Task_Init(v);
T_TCB_PTR Task_GetActualTask(void);
v Task_SetActualTask(T_TCB_PTR Task);
u16 Task_Create(T_TCB_PTR TaskHandler, u16 Id, char * Name, u8 Priority, pu8 Stack, u16 StackSize, TaskFunction Function, void * Param );
u16 Task_CheckStack(T_TCB_PTR TaskHandler);
u16 Task_Sleep(u16 SleepTicks);//Funcion que va a dormir en ticks del sistema

#endif /* TASK_H_ */



