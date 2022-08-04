#ifndef __PORTABLE_H
#define __PORTABLE_H
/*
 * 
 * Inclusi�n de librerias
 * 
 */

#include "AppTypes.h"
//#include "scheduller.h"
//#include "task.h"
/*
 * 
 * DEFINICI�N DE CONSTANTES DEL M�DULO
 * 
 * 
 */

#define Portable_SoftwareInterrupt()	asm(SWI)

/**
 * 
 * 
 * DEFINICI�N DE CONSTANTES INTERNAS DEL M�DULO
 * 
 * 
 */


#define Portable_SaveContext()			asm(TSX):\
										asm(STHX CurrentStackPtr)
#define Portable_RestoreContext()		asm(LDHX CurrentStackPtr):\
										asm(TXS)

#define Portable_SoftwareInterrupt()	asm(SWI)

/*
 * 
 * DEFINICI�N DE TIPOS DE DATOS DEL M�DULO
 * 
 */

typedef	void (*TaskFunction)(void * Param);

/*
 * 
 * DEFINICI�N DE FUNCIONES DEL M�DULO
 * 
 */

pu8 Portable_InitTaskContext(pu8 Stack, TaskFunction Function, void * Param);
v Portable_RestoreManualContext(u16 Stack);
v Portable_InitTickRTC(v);
v Portable_DisableInterrupts(v);
v Portable_EnableInterrupts(v);
__interrupt void ISR_SoftwareInterrupt(void);
__interrupt void ISR_TimerInterrupt(void);

u16	Scheduller_Coperative(u16 ActualTaskSP);

#endif
