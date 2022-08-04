/*
 * Eventos.h
 *
 *  Created on: May 13, 2022
 *      Author: User
 */

#ifndef EVENTOS_H_
#define EVENTOS_H_


#include "AppTypes.h"
#include "Queue.h"


#define EVENT_WAIT_TYPE_BIT		0x80
#define EVENT_WAIT_TYPE_MASK	~EVENT_WAIT_TYPE_BIT


#define	EVENT_WAIT_ANY			0
#define	EVENT_WAIT_ALL			EVENT_WAIT_TYPE_BIT



#define EVENT_OK 							0
#define EVENT_ERROR_UNKNOW					EVENT_BASE_ERROR | BASE_ERROR_UNKNOW
#define EVENT_ERROR_NULL_PARAM 				EVENT_BASE_ERROR | BASE_ERROR_NULL_PARAM
#define EVENT_ERROR_EMPTY 					EVENT_BASE_ERROR | BASE_ERROR_UNKNOW
#define EVENT_ERROR_PARAM_OUT_OF_RANGE 		EVENT_BASE_ERROR | BASE_ERROR_PARAM_OUT_OF_RANGE



typedef u8 T_EventReg;

typedef struct{
	T_EventReg EventBits;
	T_QUEUE_HANDLER EventQueue;
}T_EVENT_HANDLER, * T_EVENT_HANDLER_PTR;


u16 Event_Init(T_EVENT_HANDLER_PTR Event, T_EventReg InitEvents);
u16 Event_Set (T_EVENT_HANDLER_PTR Event, T_EventReg SetBits);
u16 Event_Clear(T_EVENT_HANDLER_PTR Event, T_EventReg ClearBits);
u16 Event_WaitAny(T_EVENT_HANDLER_PTR Event, T_EventReg EventBits);
u16 Event_WaitAll(T_EVENT_HANDLER_PTR Event, T_EventReg EventBits);
T_EventReg Event_GetEvents(T_EVENT_HANDLER_PTR Event);



#endif /* EVENTOS_H_ */
