#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "AppTypes.h"
#include "Queue.h"

#define MESSAGE_POLL_SIZE(MsgNumber, MsgSize)((sizeof(T_QUEUE_ELEMENT)* MsgNumber) + MsgSize)*MsgNumber

#define MESSAGE_OK 							0
#define MESSAGE_ERROR_UNKNOW					MESSAGE_BASE_ERROR | BASE_ERROR_UNKNOW
#define MESSAGE_ERROR_NULL_PARAM 				MESSAGE_BASE_ERROR | BASE_ERROR_NULL_PARAM
#define MESSAGE_ERROR_EMPTY 					MESSAGE_BASE_ERROR | BASE_ERROR_UNKNOW
#define MESSAGE_ERROR_PARAM_OUT_OF_RANGE 		MESSAGE_BASE_ERROR | BASE_ERROR_PARAM_OUT_OF_RANGE



typedef struct{
	u16 MsgNumber;
	u16 MsgSize;
	pu8 MsgDataPollPtr;
	T_QUEUE_ELEMENT_PTR MsgElementsPollPtr;
	T_QUEUE_HANDLER MsgFree;
	T_QUEUE_HANDLER MsgUsed;
	T_QUEUE_HANDLER	MsgTaskWaitToSend;
	T_QUEUE_HANDLER MsgTaskWaitToReceive;
}T_MSG_HANDLER, * T_MSG_HANDLER_PTR;


u16 Message_Init(T_MSG_HANDLER_PTR Handler, u16 MsgNumber, u16 MsgSize, pu8 MsgPollMemory ); 
u16 Message_GetMsgFreeCount(T_MSG_HANDLER_PTR Handler);
u16 Message_GetMsgUsedCount(T_MSG_HANDLER_PTR Handler);
u16 Message_Send(T_MSG_HANDLER_PTR Handler,pv Data);
u16 Message_Receive(T_MSG_HANDLER_PTR Handler, pv Data);


#endif
