
#include "AppTypes.h"
#include "Queue.h"
#include "string.h"
#include "portable.h"
#include "scheduller.h"
#include "Message.h"

u16 Message_Init(T_MSG_HANDLER_PTR Handler, u16 MsgNumber, u16 MsgSize, pu8 MsgPollMemory ){
	u16 Res = MESSAGE_ERROR_NULL_PARAM;
	u16 i;
	
	if((Handler) && (MsgPollMemory)){
		
		if((MsgNumber) && (MsgSize)){
			Handler->MsgNumber = MsgNumber;
			Handler->MsgSize = MsgSize;
			Handler->MsgElementsPollPtr = (T_QUEUE_ELEMENT_PTR)MsgPollMemory;
			Handler->MsgDataPollPtr = MsgPollMemory + (sizeof(T_QUEUE_ELEMENT) * MsgNumber);
			Res = Queue_Init(&Handler->MsgFree);
			if(Res != QUEUE_OK){
				return Res;
			}
			Res = Queue_Init(&Handler->MsgUsed);
			if(Res != QUEUE_OK){
				return Res;
			}
			Res = Queue_Init(&Handler-> MsgTaskWaitToReceive);
			if(Res != QUEUE_OK){
				return Res;
			}
			Res = Queue_Init(&Handler-> MsgTaskWaitToSend);
			if(Res != QUEUE_OK){
				return Res;
			}
			for (i=0;i<MsgNumber;i++){
				Handler->MsgElementsPollPtr[i].Next = NULL;
				Handler->MsgElementsPollPtr[i].Data = (pv)(Handler->MsgDataPollPtr + (MsgSize * i));
				Res = Queue_Enqueue(&Handler->MsgFree, &Handler->MsgElementsPollPtr[i]);
				if(Res != QUEUE_OK){
					break;
				}
			}
		}
		else{
			Res = MESSAGE_ERROR_PARAM_OUT_OF_RANGE;
		}
	}
	
	return Res;
}


u16 Message_GetMsgFreeCount(T_MSG_HANDLER_PTR Handler){
	u16 Res = 0;
	//ver minuto 33 clase 7 de mayo
	if(Handler ){
		Portable_DisableInterrupts();
		Res = Queue_GetCount(&Handler->MsgFree);
	    Portable_EnableInterrupts();
	}
	return Res;
}



u16 Message_GetMsgUsedCount(T_MSG_HANDLER_PTR Handler){
	u16 Res = 0;
	if(Handler){
		Portable_DisableInterrupts();
		Res = Queue_GetCount(&Handler->MsgUsed);
		Portable_EnableInterrupts();
	}
	return Res;
}


u16 Message_Send(T_MSG_HANDLER_PTR Handler,pv Data){
	u16 Res = MESSAGE_ERROR_NULL_PARAM;
	T_QUEUE_ELEMENT_PTR Element;
	u8 CallScheduller = FALSE;
	T_TCB_PTR Task;
	if((Handler) && (Data)){
		Portable_DisableInterrupts();
		Task = Task_GetActualTask();
		if(Task){
			while(Queue_Dequeue(&Handler->MsgFree, &Element)!= QUEUE_OK){
				Task -> Status = BLOCKED;
				Task->TaskQueueElement.Data = Task;
				Task->TaskQueueElement.Next = NULL;
				Res = Queue_Enqueue((&Handler->MsgTaskWaitToSend), &Task->TaskQueueElement);
				if(Res == QUEUE_OK){
					Task->Status = BLOCKED;
					Portable_EnableInterrupts();
					Portable_SoftwareInterrupt();
					Portable_DisableInterrupts();
				}
			}
			memcpy(Element->Data, Data, Handler->MsgSize);
			Res = Queue_Enqueue(&Handler->MsgUsed, Element);
			if(Res == QUEUE_OK){
				if(Queue_GetCount(&Handler->MsgTaskWaitToReceive)>0){
					Res = Queue_Dequeue(&Handler->MsgTaskWaitToReceive, &Element);
					if(Res == QUEUE_OK){
						Res = Scheduller_SetTaskToReadyQueue((T_TCB_PTR) Element-> Data);
						if(Res == SCHEDULLER_OK){
							if(((T_TCB_PTR) Element-> Data)->TaskPriority < Task->TaskPriority){
								CallScheduller = TRUE;
							}
						}
					}
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


u16 Message_Receive(T_MSG_HANDLER_PTR Handler, pv Data){
	u16 Res = MESSAGE_ERROR_NULL_PARAM;
	T_QUEUE_ELEMENT_PTR Element;
	u8 CallScheduller = FALSE;
	T_TCB_PTR Task;
	if((Handler) && (Data)){
		Portable_DisableInterrupts();
		Task = Task_GetActualTask();
		if(Task){
			while(Queue_Dequeue(&Handler->MsgUsed, &Element)!= QUEUE_OK){
				Task -> Status = BLOCKED;
				Task->TaskQueueElement.Data = Task;
				Task->TaskQueueElement.Next = NULL;
				Res = Queue_Enqueue((&Handler->MsgTaskWaitToReceive), &Task->TaskQueueElement);
				if(Res == QUEUE_OK){
					Task->Status = BLOCKED;
					Portable_EnableInterrupts();
					Portable_SoftwareInterrupt();
					Portable_DisableInterrupts();
				}
			}
			(v)memcpy(Data, Element->Data, Handler->MsgSize);
			Res = Queue_Enqueue(&Handler->MsgFree, Element);
			if(Res == QUEUE_OK){
				if(Queue_GetCount(&Handler->MsgTaskWaitToSend)>0){
					Res = Queue_Dequeue(&Handler->MsgTaskWaitToSend, &Element);
					if(Res == QUEUE_OK){
						Res = Scheduller_SetTaskToReadyQueue((T_TCB_PTR) Element-> Data);
						if(Res == SCHEDULLER_OK){
							if(((T_TCB_PTR) Element-> Data)->TaskPriority < Task->TaskPriority){
								CallScheduller = TRUE;
							}
						}
					}
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
