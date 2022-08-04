/*
 * scheduller.h
 *
 *  Created on: Mar 13, 2022
 *      Author: User
 */

#ifndef SCHEDULLER_H_
#define SCHEDULLER_H_

#include "AppTypes.h"
#include "task.h"

#define SCHEDULLER_OK								0
#define	SCHEDULLER_ERROR_UNKNOW						SCHEDULLER_BASE_ERROR | BASE_ERROR_UNKNOW
#define	SCHEDULLER_ERROR_NULL_PARAM					SCHEDULLER_BASE_ERROR | BASE_ERROR_NULL_PARAM
#define	SCHEDULLER_ERROR_EMPTY						SCHEDULLER_BASE_ERROR | BASE_ERROR_EMPTY
#define SCHEDULLER_ERROR_PARAM_OUT_OF_RANGE			SCHEDULLER_BASE_ERROR | BASE_ERROR_PARAM_OUT_OF_RANGE

u16	Scheduller_Init(void);
u16 Sheduller_Coperative(u16 ActualTaskSP);
u16 Scheduller_SetTaskToReadyQueue(T_TCB_PTR Task);


#endif /* SCHEDULLER_H_ */
