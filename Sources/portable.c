
#include "AppTypes.h"
#include "portable.h"
#include "IO_Map.h"
#include "RTOS.h"
#include "scheduller.h"


/*
 * 
 * Definicion de variables globales internas del m�dulo
 * 
 */
extern  v Task_DecrementTimers(v);
extern 	u16 Scheduller_Coperative(u16 ActualTaskSP);

u8 *ActualStack;
u16 CurrentStackPtr;// asi se almacena HX
u8  CriticalNesting = 0;


pu8 Portable_InitTaskContext (pu8 Stack, TaskFunction Function, void * Param) 
{
	if((!Stack)||(!Function))
	{
		return NULL;
	}
	Stack--;
	*Stack = (u8)((u16)Function & 0x00FF);		//Asignacion PC Low
	Stack--;
	*Stack = (u8)(((u16)Function >> 8)& 0x00FF);//Asignacion PC High
	Stack--;
	*Stack=	 (u8)((u16)Param & 0x00FF);;	//Asignacion X
	Stack--;
	*Stack=0;	//Asignacion del A(acumulador)
	Stack--;
	*Stack=0;	//Asignacion de CCR (codigo de condicion)
	Stack--;
	*Stack=  (u8)(((u16)Param >> 8)& 0x00FF);	//Asignacion de H
	Stack--;
	*Stack=1;	//Asignacion del Critical Nesting, modificacion a 1 nueva linea, para que el primer decremento llegue a cero
	return Stack;
}

 

v Portable_RestoreManualContext(u16 Stack){
	
	CurrentStackPtr = Stack;
	asm{
		LDHX	CurrentStackPtr
		TXS	
		PULA
		STA		CriticalNesting
		PULH
		RTI	//retorno de interrupcion
	}
}

v Portable_InitTickRTC(v){
	
	RTC_SC2 = 0x07; //timer rtc del micro
	RTC_MODL = 0x1B;
	RTC_MODH = 0x03;
	//RTC_MOD = 0x9F;	//inicializa
	//RTC_MOD = RTC_MOD;
	RTC_SC2 = 0xC6;
	RTC_SC1 |= 0xC0; 
}

v Portable_DisableInterrupts(v){
	asm(SEI);
	CriticalNesting++;
}

v Portable_EnableInterrupts(v){
	
	if(CriticalNesting){
		CriticalNesting--;
		
		if(!CriticalNesting){
			asm(CLI); 
		}
	}
}

__interrupt void ISR_SoftwareInterrupt(void){
	
	CriticalNesting ++;
	asm{
		LDA		CriticalNesting
		PSHA
		TSX
		STHX	CurrentStackPtr
	}
	
	CurrentStackPtr = Scheduller_Coperative(CurrentStackPtr);
	asm{
		LDHX	CurrentStackPtr
		TXS
		PULA
		STA		CriticalNesting
	}
	CriticalNesting --; //Nueva linea
	
}
//entra a la interupcion de software 
__interrupt void ISR_TimerInterrupt(void)
{ //inicializar un timer
//LED_2_SetVal();
RTC_SC1 |= 0x80U;

CriticalNesting++;
asm{
	LDA 	CriticalNesting
	PSHA //Enviando al stack criticalnesting
	TSX
	STHX 	CurrentStackPtr
}
Task_DecrementTimers();
CurrentStackPtr = Scheduller_Coperative(CurrentStackPtr); //Retorna el Stack pointer de la tarea a ejecutar
asm{
	LDHX CurrentStackPtr
	TXS
	PULA
	STA CriticalNesting
	}
CriticalNesting--;
IPC_SC_PULIPM = 1U;
//salida del Timer
}




































