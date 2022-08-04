#include "AppTypes.h"
#include "Semaforo.h"
#include "portable.h"
#include "Queue.h"
#include "task.h"
#include "RTOS.h"
#include "Eventos.h"
#include "scheduller.h"


u16 Event_Init(T_EVENT_HANDLER_PTR Event, T_EventReg InitEvents){
	u16 Res = EVENT_ERROR_NULL_PARAM;
	if(Event){
		Event->EventBits = InitEvents;
		Event->EventBits &= EVENT_WAIT_TYPE_MASK;
		Res = Queue_Init(&Event->EventQueue);
	}
	return Res;
}


u16 Event_Clear(T_EVENT_HANDLER_PTR Event, T_EventReg ClearBits){
	u16 Res = EVENT_ERROR_NULL_PARAM;
	if(Event){
		Portable_DisableInterrupts();
		ClearBits = ~ClearBits;
		Event->EventBits &= ClearBits;
		Event->EventBits &= EVENT_WAIT_TYPE_MASK;
		Res = EVENT_OK;
		Portable_EnableInterrupts();
	}
	return Res;
}


u16 Event_Set (T_EVENT_HANDLER_PTR Event, T_EventReg SetBits){
	u16 Res = EVENT_ERROR_NULL_PARAM;
	u8 ActualTaskPriority = RTOS_SYSTEM_PRIORITIES; //acá quedé :(
	u8 CallScheduller = FALSE;
	T_TCB_PTR	Task;
	T_EventReg Evt;
	T_QUEUE_HANDLER TempQueue;
	T_QUEUE_ELEMENT_PTR Element;
	if(Event){
		SetBits &= EVENT_WAIT_TYPE_MASK;
		if(SetBits){
			Portable_DisableInterrupts();
			Event -> EventBits |= SetBits;
			Task = Task_GetActualTask();
			if(Task){
				ActualTaskPriority = Task ->TaskPriority;
			}
			Res = Queue_Init(&TempQueue);
			if(Res == QUEUE_OK){
				while(Queue_GetCount(&Event->EventQueue)){
					Res = Queue_Dequeue(&Event->EventQueue, &Element);
					if(Res == QUEUE_OK){
						Task = (T_TCB_PTR)Element->Data;
						if(Task){
							if((Task->TaskWaitEvents & EVENT_WAIT_TYPE_BIT) == EVENT_WAIT_ALL){
								//Caso wait ALL
								Evt = Task->TaskWaitEvents & EVENT_WAIT_TYPE_MASK;
								if((Evt & Event ->EventBits) == Evt){
									Res = Scheduller_SetTaskToReadyQueue(Task);
									if(Res == SCHEDULLER_OK){
										
										if(Task->TaskPriority < ActualTaskPriority){
											CallScheduller = TRUE;
										}
									}
								}
								else{
									Res = Queue_Enqueue(&TempQueue, Element);
								}
							}
							else{
								//Caso wait any
								Evt = Task->TaskWaitEvents & EVENT_WAIT_TYPE_MASK;
								if((Evt & Event ->EventBits) != 0){
									
									Res = Scheduller_SetTaskToReadyQueue(Task);
									if(Res == SCHEDULLER_OK){
										if(Task->TaskPriority < ActualTaskPriority){
											CallScheduller = TRUE;
										}
									}
								}
								else{
									Res = Queue_Enqueue(&TempQueue, Element);
								}
								
							}
						}
					}
				}
				Res = Queue_Copy(&TempQueue, &Event->EventQueue);
			}
			Portable_EnableInterrupts();
			if (CallScheduller){
				Portable_SoftwareInterrupt();
				
			}
		}
		else{
			Res = EVENT_OK;
		}
	}
	return Res;
}

u16 Event_WaitAny(T_EVENT_HANDLER_PTR Event, T_EventReg EventBits){
	u16 Res = EVENT_ERROR_NULL_PARAM;
	u8 CallScheduller = FALSE;
	T_TCB_PTR Task;
	if(Event){
		EventBits &= EVENT_WAIT_TYPE_MASK;
		if (EventBits){
			
			Portable_DisableInterrupts();
			if((EventBits & Event->EventBits) == 0){//Sigue derecho si el evento uya ocurrió
				Task = Task_GetActualTask();
				if(Task){
					Task->TaskWaitEvents = EventBits;
					Task->TaskQueueElement.Data = Task;
					Task->TaskQueueElement.Next = NULL;
					Res = Queue_Enqueue(&Event -> EventQueue, &Task->TaskQueueElement);
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
		else{
			Res = TRUE;
		}
	}
	return Res;
}


u16 Event_WaitAll(T_EVENT_HANDLER_PTR Event, T_EventReg EventBits){
	u16 Res = EVENT_ERROR_NULL_PARAM;
		u8 CallScheduller = FALSE;
		T_TCB_PTR Task;
		if(Event){
			EventBits &= EVENT_WAIT_TYPE_MASK;
			if (EventBits){
				
				Portable_DisableInterrupts();
				if((EventBits & Event->EventBits) != EventBits){//Sigue derecho si el evento uya ocurrió
					Task = Task_GetActualTask();
					if(Task){
						Task->TaskWaitEvents = EventBits | EVENT_WAIT_ALL;
						Task->TaskQueueElement.Data = Task;
						Task->TaskQueueElement.Next = NULL;
						Res = Queue_Enqueue(&Event -> EventQueue, &Task->TaskQueueElement);
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
			else{
				Res = TRUE;
			}
		}
		return Res;
}


T_EventReg Event_GetEvents(T_EVENT_HANDLER_PTR Event){
	T_EventReg Res =0;
	if(Event){
		Res = Event -> EventBits;
		Res &= EVENT_WAIT_TYPE_MASK;
	}
	return Res;
}

