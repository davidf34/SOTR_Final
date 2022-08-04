#ifndef __PORTABLE_H
#define __PORTABLE_H
/*
 * 
 * Inclusión de librerias
 * 
 */

#include "AppTypes.h"
//#include "scheduller.h"
//#include "task.h"
/*
 * 
 * DEFINICIÓN DE CONSTANTES DEL MÓDULO
 * 
 * 
 */

#define Portable_SoftwareInterrupt()	asm(SWI)

/**
 * 
 * 
 * DEFINICIÓN DE CONSTANTES INTERNAS DEL MÓDULO
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
 * DEFINICIÓN DE TIPOS DE DATOS DEL MÓDULO
 * 
 */

typedef	void (*TaskFunction)(void * Param);

/*
 * 
 * DEFINICIÓN DE FUNCIONES DEL MÓDULO
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
