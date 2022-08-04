/* ###################################################################
**     Filename    : main.c
**     Project     : Proyecto_SOTR
**     Processor   : MC9S08PT60VLH
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2022-03-30, 16:16, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */

//REVISAR 11:21 AM
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Led1.h"
#include "Led_button.h"
#include "Button.h"
#include "ADC1.h"
#include "PWM.h"
#include "Led2.h"
#include "Button_1.h"
#include "Led_ejemplo.h"
#include "MCUC1.h"
#include "WAIT1.h"
#include "GI2C1.h"
#include "EI2C1.h"
#include "DataPin1.h"
#include "ClockPin1.h"
#include "LCD1.h"
#include "Semaforo.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h" 
#include "AppTypes.h"
#include "RTOS.h"
#include "Eventos.h"
#include "Message.h"


int dx=-1;
int dy=-1;
int i;
int j;
int ball_x;
int ball_y;
char a;
int H = 128,V = 64;
int flag_x=0, flag_y=0;
int count_1 = 0, count_2 = 0;

int LeftRaqX = 6, LeftRaqY, RightRaqX = 117, RightRaqY = 40;
int jugador1,jugador2, acumulador1, acumulador2;
char punt1, punt2;
//char ADC1;
uint16_t Pot_player1, Pot_player2,Pot_player1_old=0,Pot_player2_old=0;
int flag_delete=0;
int value_p1,value_p2; 

void FuncionTarea1();
void FuncionADC();
void ball();
char IntToChar1(int N);
char IntToChar2(int N);
void puntaje();
/* User includes (#include below this line is not maintained by Processor Expert) */
char IntToChar1(int N1){
	return N1+'0';
}
char IntToChar2(int N2){
	return N2+'0';
}


#define EVENT_LED1 0x01
#define EVENT_LED2 0x02
#define EVENT_LED3 0x04
#define EVENT_LED4 0x08


void FuncionTarea1(void * Param);
void FuncionTarea2(void * Param);
void FuncionTarea3(void * Param);
void FuncionTarea4(void * Param);
void FuncionTareaEvento(void * Param);
void FuncionTareaSemaforo(void *Param);
void FuncionTareaPong(void *Param);
void FuncionTareaButton(void *Param);
void FuncionTareaLed(void *Param);
/* User includes (#include below this line is not maintained by Processor Expert) */
T_TCB Tarea1;
T_TCB Tarea2;
T_TCB Tarea3;
T_TCB Tarea4;
T_TCB Tarea5;
T_TCB Tarea6;
T_TCB Tarea7;

u8		ADC1;
u8		Tarea1Stack[RTOS_MIN_STACK_SIZE];
u8		Tarea2Stack[RTOS_MIN_STACK_SIZE];
u8		Tarea3Stack[RTOS_MIN_STACK_SIZE];
u8		Tarea4Stack[RTOS_MIN_STACK_SIZE];
u8		Tarea5Stack[RTOS_MIN_STACK_SIZE *2];
u8		Tarea6Stack[RTOS_MIN_STACK_SIZE];
u8		Tarea7Stack[RTOS_MIN_STACK_SIZE];
u8		Tarea8Stack[RTOS_MIN_STACK_SIZE];

T_SEMAPHORE SemTest;
T_MUTEX MutexTest;
T_EVENT_HANDLER EventTest;
T_MSG_HANDLER Message;

u8 MsgPoll[MESSAGE_POLL_SIZE(10, sizeof(unsigned long))];



void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  (v)RTOS_Init(); //Funci�n de inicializaci�n del RTOS, llama a la inicializaci�n de Scheduller
  	
  	(v)Task_Create(&Tarea1, 1, "Tarea 1", 1, Tarea1Stack, RTOS_MIN_STACK_SIZE, FuncionTarea1,(void *) 1);
  	(v)Task_Create(&Tarea2, 2, "Tarea 2", 2, Tarea2Stack, RTOS_MIN_STACK_SIZE, FuncionTarea2,(void *) 2);
  	(v)Task_Create(&Tarea3, 3, "Tarea 3", 4, Tarea3Stack, RTOS_MIN_STACK_SIZE, FuncionTarea3,(void *) 3);
  	(v)Task_Create(&Tarea4, 4, "Tarea 4", 5, Tarea4Stack, RTOS_MIN_STACK_SIZE, FuncionTarea4,(void *) 4);
  	(v)Task_Create(&Tarea5, 5, "Tarea 5", 3, Tarea5Stack, RTOS_MIN_STACK_SIZE *2, FuncionTareaEvento,NULL);
  	(v)Task_Create(&Tarea6, 6, "Tarea 6", 3, Tarea6Stack, RTOS_MIN_STACK_SIZE *2, FuncionTareaSemaforo,3000);
  	(v)Task_Create(&Tarea7, 7, "Tarea 7", 2, Tarea7Stack, RTOS_MIN_STACK_SIZE *2, FuncionTareaPong,NULL);
  	//(v)Task_Create(&Tarea6, 5, "Tarea Button", 5, Tarea6Stack, RTOS_MIN_STACK_SIZE, FuncionTareaButton, NULL);
  	//(v)Task_Create(&Tarea7, 5, "Tarea Led", 4, Tarea7Stack, RTOS_MIN_STACK_SIZE, FuncionTareaLed, NULL);
  	(v)Semaforo_Init(&SemTest,9,0); //Count limit y Inicializacion del contador
  	(v)Mutex_Init(&MutexTest, FALSE);
  	(v)Event_Init(&EventTest, 0);
  	(v)Message_Init(&Message, 10, sizeof(unsigned long), MsgPoll);
  	
  	(v)RTOS_Start();
  	
  /* For example: for(;;) { } */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

void FuncionTarea1(void * Param){
	u16 Time = (u16)Param;
	unsigned long Val = Time;
	T_EventReg Evento;
		for(;;){
			(v)Task_Sleep(Time * 10);
			switch(Time){
			case 1:
				(v)Event_Set(&EventTest, EVENT_LED1);
				break;
			case 2:
				(v)Event_Set(&EventTest, EVENT_LED2);
				break;
			case 3:
				(v)Event_Set(&EventTest, EVENT_LED3);
				break;
				
			default:
				(v)Event_Set(&EventTest, EVENT_LED4);
				break;
			}
			(v)Message_Send(&Message, Val);
			//if(Semaforo_Take(&SemTest)== SEMAPHORE_OK){
			
				/*for(Count = Time; Count > 0; Count --) //EN EL VIDEO EL PROFE DICE QUE ES UN ERROR TENER Count ++, ahi se cambia por Count --
				{}*/
				
				//Led1_NegVal();
			//}
		}
}
void FuncionTarea2(void * Param){
	u16 Time = (u16)Param;
	u16 Count;
		for(;;){
			(v)Task_Sleep(Time);
			/*for(Count = Time; Count > 0; Count --) //EN EL VIDEO EL PROFE DICE QUE ES UN ERROR TENER Count ++, ahi se cambia por Count --
			{}*/
				
			Led2_NegVal();
		}
}
void FuncionTarea3(void * Param){
	u16 Time = (u16)Param;
	for(;;){
		(v)Task_Sleep(Time);
		if(Button_GetVal()){
			Led_button_SetVal();
		}
		else{
			Led_button_ClrVal();
		}
		
	}
}

void FuncionTarea4(void * Param){
	int count = 0;
	T_SEMAPHORE_PTR FuncionTareaPong; //El semaforo debera controlar la tarea que ejecuta el juego
	for(;;){
	//La funcion semaforo, se encargará de llevar un conteo, llegar a un limite y detener tareas para
	//que no se ejecuten. 
	//Cada vez que se ejecuten los 9 puntos, el juego se detendra hasta que se de inicio nuevamente, por
	//lo tanto, en la parte de los punto anadir y probar:
	 
		if(ball_y == 2 || ball_y == V-6)
					{
						dy *= -1;
					}
						
					if(ball_x == 2 )
					{
						count_1++;
						dx *= -1;
						jugador1++;
						if(jugador1 <10){
							punt1 = IntToChar1(jugador1);
						}
						else{
							jugador1 = 0;
						}
						
						LCD1_PrintString(1,80,&punt1);
						LCD1_PutPixel(flag_x,flag_y,FALSE);
						LCD1_PutPixel(flag_x,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x,flag_y+2,FALSE);
						LCD1_PutPixel(flag_x,flag_y,FALSE);
						LCD1_PutPixel(flag_x+1,flag_y,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y,FALSE);
						
						LCD1_PutPixel(flag_x+1,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x+1,flag_y+2,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y+2,FALSE);
						LCD1_UpdateRegion(flag_x,flag_y,4,4);
						ball_x = 64;
						ball_y = 32;
						
						
					}else if(ball_x == H-6)
					{
						count_2++;
						dx *= -1;
						jugador2++;
						if(jugador2 <10){
							punt2 = IntToChar1(jugador2);
						}
						else{
							jugador2 = 0;
						}
						
						LCD1_PrintString(1,45,&punt2);
						LCD1_PutPixel(flag_x,flag_y,FALSE);
						LCD1_PutPixel(flag_x,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x,flag_y+2,FALSE);
						LCD1_PutPixel(flag_x,flag_y,FALSE);
						LCD1_PutPixel(flag_x+1,flag_y,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y,FALSE);
						
						LCD1_PutPixel(flag_x+1,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x+1,flag_y+2,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y+2,FALSE);
						LCD1_UpdateRegion(flag_x,flag_y,4,4);
						ball_x = 64;
						ball_y = 32;
						
					}





		/*(v)ADC1_Measure(FALSE);
		(v)Task_Sleep(Time);
		(v)ADC1_GetValue8(&ADC1);
		(v)PWM_SetRatio8(ADC1);*/
	}
}

void FuncionTareaPong(void *Param){
	
	u16 Time = (u16)Param;
	u16 count; 
	//El sem�foro deber� controlar la tarea que ejecuta el juego
	//La funci�n sem�foro, se encargar� de llevar un conteo, llegar a un l�mite y detener tareas para
	//que no se ejecuten. 
	//Cada vez que se ejecuten los 9 puntos, el juego se detendr� hasta que se de inicio nuevamente, por
	//lo tanto, en la parte de los punto a�adir y probar:
	for(;;){
		(v)Task_Sleep(Time);
		if(Semaforo_Take(&SemTest)==SEMAPHORE_OK)
		{
			//AQU� VA LA TAREA DEL PONG COMPLETICA
			/*Dentro de la tarea del PONG completa, insertar en la parte del cambio de lado,
			 * es decir, cuando la pelota va a de un jugador a otro se deber�a liberar con el 
			 * Mutex, es decir, Jugador 1 lanza, Mutex retiene a Jugador 2, cuando la pelota 
			 * est� en juego y va a recibir Jugador 1, se bloquea Jugador 1 y permite movimiento y 
			 * recepci�n de jugador 2*/
			
	
	
	
				LCD1_Clear();
				(void)LCD1_DisplayOn(TRUE);
				
				ball_x = 64;
				ball_y = 32;
				
				
				//Ball
				
				for(i = ball_x; i < ball_x+3; i++){
					for(j= ball_y; j < ball_y+3; j++){
					LCD1_PutPixel(i,j,TRUE); 
					}
				}
				
				// Zone
				for (i = 0;i<H;i++){
					for(j = 0 ; j < V; j++){
						if( i == 1 || i == H - 3 || j == 1 || j == V-3){
						LCD1_PutPixel(i,j,TRUE);
						}
					}
				}
				////////////////////////////////////////////////////////////////////
				//LeftRaq
				/*if(flag_delete == 1){
					for (i = LeftRaqX ; i < LeftRaqX + 3; i++)
					{
						for(j = LeftRaqY; j < LeftRaqY + 15; j++)
						{			
							LCD1_PutPixel(i,j,TRUE);	
						}
					}
				}
				else if(flag_delete ==0){
					
					for(i = 0 ;i<3;i++){
						//para borrar la raqueta inicial y que se mueva con el potenciometro
						for(j =0 ;j<15;j++){
							LCD1_PutPixel(LeftRaqX+i,LeftRaqY+j,FALSE);
							LCD1_UpdateRegion(LeftRaqX+i,LeftRaqY+j,3,15);
						}
					}
					flag_delete = 2;
				}*/
				//RightRaq
				for (i = RightRaqX ; i < RightRaqX + 3; i++)
				{
					for(j = RightRaqY; j < RightRaqY +15; j++)
					{			
						LCD1_PutPixel(i,j,TRUE);
					}
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
				}
				LCD1_UpdateFull();
				
				
				while(1){
					
					/*if(Pot_player1 > Pot_player1_old)
						Pot_player1_old =Pot_player1 ;		
					
					else if(Pot_player1 < Pot_player1_old)
						Pot_player1_old =Pot_player1 ;	
					
					else if(Pot_player2 > Pot_player2_old)
						Pot_player2_old =Pot_player2 ;
					
					else if(Pot_player2 < Pot_player2_old)
						Pot_player2_old =Pot_player2 ;
					*/
					
					
					
					
					//if(flag_delete == 1){
					
						
						//flag_delete = 0;
					//}
					/*else if(flag_delete == 0){
						
					}*/
						
							
				
					/*if(flag_delete == 0){
						for (i = LeftRaqX ; i < LeftRaqX + 3; i++)
								{
									for(j = LeftRaqY; j < LeftRaqY + 15; j++)
									{			
										LCD1_PutPixel(i,j,TRUE);
									}
								}
					}
					else if(flag_delete ==1){
								for(i = 0 ;i<3;i++){
									//para borrar la raqueta inicial y que se mueva con el potenciometro
									for(j =0 ;j<15;j++){
										LCD1_PutPixel(LeftRaqX+i,LeftRaqY+j,FALSE);
										LCD1_UpdateRegion(LeftRaqX+i,LeftRaqY+j,3,15);
									}
								}
							flag_delete = 2;
						}*/
					
								
						
					
					
					
					
					
				/*	punt2=0;
					punt1=0;
					flag_x = ball_x;
					flag_y = ball_y;
					
				
								
					
					
					//Verificación
						//Lower side & Upper side
					if(ball_y == 2 || ball_y == V-6)
					{
						dy *= -1;
					}
						
					if(ball_x == 2 )
					{
						count_1++;
						dx *= -1;
						jugador1++;
						if(jugador1 <10){
							punt1 = IntToChar1(jugador1);
						}
						else{
							jugador1 = 0;
						}
						
						LCD1_PrintString(1,80,&punt1);
						LCD1_PutPixel(flag_x,flag_y,FALSE);
						LCD1_PutPixel(flag_x,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x,flag_y+2,FALSE);
						LCD1_PutPixel(flag_x,flag_y,FALSE);
						LCD1_PutPixel(flag_x+1,flag_y,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y,FALSE);
						
						LCD1_PutPixel(flag_x+1,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x+1,flag_y+2,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y+2,FALSE);
						LCD1_UpdateRegion(flag_x,flag_y,4,4);
						ball_x = 64;
						ball_y = 32;
						
						
					}else if(ball_x == H-6)
					{
						count_2++;
						dx *= -1;
						jugador2++;
						if(jugador2 <10){
							punt2 = IntToChar1(jugador2);
						}
						else{
							jugador2 = 0;
						}
						
						LCD1_PrintString(1,45,&punt2);
						LCD1_PutPixel(flag_x,flag_y,FALSE);
						LCD1_PutPixel(flag_x,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x,flag_y+2,FALSE);
						LCD1_PutPixel(flag_x,flag_y,FALSE);
						LCD1_PutPixel(flag_x+1,flag_y,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y,FALSE);
						
						LCD1_PutPixel(flag_x+1,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y+1,FALSE);
						LCD1_PutPixel(flag_x+1,flag_y+2,FALSE);
						LCD1_PutPixel(flag_x+2,flag_y+2,FALSE);
						LCD1_UpdateRegion(flag_x,flag_y,4,4);
						ball_x = 64;
						ball_y = 32;
						
					}*/
						/*//LeftRaq
					if(ball_x == LeftRaqX + 3)
					{
						if((ball_y + 1) >= LeftRaqY && (ball_y+1) < (LeftRaqY + 8))
						{
							dx = 1;
							dy = -1;
						}else if((ball_y+1) == (LeftRaqY + 8))
						{
							dx = 1;
							dy = 0;
						}
						else if((ball_y+1) >= (LeftRaqY + 9) && (ball_y+1) < LeftRaqY + 15)
						{
							dx = 1;
							dy = 1;
						}
					}
					
						//RightRaq
					if(RightRaqX == (ball_x+3))
					{
						if((ball_y+1) >= RightRaqY && (ball_y+1) < (RightRaqY + 8))
						{
							dx = -1;
							dy = -1;
						}else if((ball_y+1) == (RightRaqY + 8))
						{
							dx = -1;
							dy = 0;
						}else if((ball_y+1) >= (RightRaqY + 9) && (ball_y+1) < RightRaqY + 15)
						{
							dx = -1;
							dy = 1;
						}
					}*/		
					
					//Modificación
					ball_x += (dx);
					ball_y += (dy);
					
					//Draw ball by (x,y)
					if(dx == -1 && dy == -1)
					{
						for(i = ball_x; i<=(flag_x+2); i++)
						{
							for(j= ball_y; j<=(flag_y+2); j++){
								if(i <= ball_x + 2 &&  j <= ball_y + 2)
								{
										LCD1_PutPixel(i,j,TRUE);
								}
								else {
									LCD1_PutPixel(i,j,FALSE);
								}
							}
							
						}
						LCD1_UpdateRegion(ball_x,ball_y,4,4);
					}else if(dx == -1 && dy == 1)
					{
						for(i = ball_x; i<=(flag_x+2); i++)
						{
							for(j= flag_y; j<=(ball_y+2); j++){
								if(i <= ball_x + 2  && j <= ball_y + 2 && j >= ball_y)
								{
									LCD1_PutPixel(i,j,TRUE);	
								}
								else {
									LCD1_PutPixel(i,j,FALSE);
								}
							}
						}
						LCD1_UpdateRegion(ball_x,flag_y,4,4);
					}else if(dx == 1 && dy == 1)
					{
						for(i = flag_x; i<=(ball_x+2); i++)
						{
							for(j= flag_y; j<=(ball_y+2); j++){
								if(i >= ball_x && j >= ball_y)
								{
									LCD1_PutPixel(i,j,TRUE);	
								}
								else {
									LCD1_PutPixel(i,j,FALSE);
								}
							}
						}
						LCD1_UpdateRegion(flag_x,flag_y,4,4);
					}else if(dx == 1 && dy == -1 )
					{
						for(i = flag_x; i<=(ball_x+2); i++)
						{
							for(j= ball_y; j<=(flag_y+2); j++)
							{
								if(i >= ball_x && j >= ball_y && j <= ball_y+2)
								{
									LCD1_PutPixel(i,j,TRUE);	
								}
								else {
									LCD1_PutPixel(i,j,FALSE);
								}
							}
						}
						LCD1_UpdateRegion(flag_x,ball_y,4,4);
					}else if(dx == 1 && dy == 0)
					{
						for(i = flag_x; i<=(ball_x+2); i++)
						{
							for(j= ball_y; j<=(flag_y+2); j++)
							{
								if(i >= ball_x && i<=ball_x+2 && j <= ball_y+2)
								{
									LCD1_PutPixel(i,j,TRUE);	
								}
								else {
									LCD1_PutPixel(i,j,FALSE);
								}
							}
						}
						LCD1_UpdateRegion(flag_x,ball_y,4,4);
					}else if(dx == -1 && dy == 0)
					{
						for(i = ball_x; i<=(flag_x+2); i++)
						{
							for(j= ball_y; j<=(flag_y+2); j++)
							{
								if(i >= ball_x && i<=ball_x+2 && j <= ball_y+2)
								{
									LCD1_PutPixel(i,j,TRUE);	
								}
								else {
									LCD1_PutPixel(i,j,FALSE);
								}
							}
						}
						LCD1_UpdateRegion(ball_x,ball_y,4,4);
					
					}
					for(i=1 ; i < 63; i++){
							LCD1_PutPixel(64,i,TRUE); 
							
						}
					
					LCD1_UpdateRegion(64,30,1,1);	
					//////////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					ADC1_Measure(TRUE);
					value_p1 = ADC1_GetChanValue8(0,&Pot_player1 );
					value_p2 = ADC1_GetChanValue8(1,&Pot_player2 );
					
					
					Pot_player1 = Pot_player1/1024;
					Pot_player2 = Pot_player2/1024;
					
					LeftRaqY = Pot_player1;
					RightRaqY = Pot_player2;
					/*LCD1_PutPixel(LeftRaqX,Pot_player1,TRUE);
					LCD1_UpdateRegion(LeftRaqX,Pot_player1,3,15);*/
					
				
					//hay que hacer otro if para que lo haga solo cuando se mueva 
					
					
					//hay que definir cuando se decrementa y cuando incrementa con el valor de old y actual
					
					//incremento
					if(Pot_player1>32 && Pot_player1<64 ){
									
									for (i = LeftRaqX ; i <= LeftRaqX+3; i++)
									{
										for(j = 32; j <= Pot_player1; j++){
												LCD1_PutPixel(i,j,TRUE);
												LCD1_PutPixel(i+2,j,TRUE);
												LCD1_PutPixel(i+3,j,TRUE);
											}
											
										
										
											/*for(j=32; j<=LeftRaqY ;j++){
												LCD1_PutPixel(i-1,j,FALSE);
												LCD1_PutPixel(i-2,j,FALSE);
												LCD1_PutPixel(i-3,j,FALSE);
												LCD1_PutPixel(i-4,j,FALSE);
												LCD1_PutPixel(i,j,TRUE);
												LCD1_PutPixel(i+2,j,TRUE);
												LCD1_PutPixel(i+3,j,TRUE);
												LCD1_PutPixel(i+4,j,TRUE);
												
											}*/
											
										/*	LCD1_PutPixel(i-1,j-1,FALSE);
											LCD1_PutPixel(i-2,j-1,FALSE);
											LCD1_PutPixel(i-3,j-1,FALSE);*/
											//LCD1_PutPixel(i,j,TRUE);
											/*LCD1_PutPixel(i+2,j,TRUE);
											LCD1_PutPixel(i+3,j,TRUE);
											LCD1_PutPixel(i+4,j,TRUE);*/
								
										
									LCD1_PutPixel(i,j,FALSE);
									
										
								}
								LCD1_UpdateRegion(i,j,3,15);
				}
									/*LCD1_UpdateRegion(i-2,j,3,15);
									LCD1_UpdateRegion(i-3,j,3,15);
									LCD1_UpdateRegion(i-4,j,3,15);
									LCD1_UpdateRegion(i,j,3,15);
									LCD1_UpdateRegion(i+2,j,3,15);
									LCD1_UpdateRegion(i+3,j,3,15);
									LCD1_UpdateRegion(i+4,j,3,15);*/
					
				
					
					else if(Pot_player2>0 && Pot_player2<32 ){
						if(flag_delete == 0)
							flag_delete = 1;
						if(LeftRaqY > 0 && LeftRaqY < 32){
							
							for(j = 1; j<=Pot_player2 ;j++){	
								
								RightRaqY = j;
								/*LCD1_PutPixel(RightRaqX+1,j,TRUE);
								
								LCD1_PutPixel(RightRaqX+2,j,TRUE);
								LCD1_PutPixel(RightRaqX+3,j,TRUE);
								LCD1_PutPixel(RightRaqX,j+1,FALSE);*/
								///LCD1_UpdateRegion(RightRaqX,RightRaqY,3,15);
								//LCD1_UpdateFull();
								//LCD1_UpdateRegion(RightRaqX,RightRaqY-j,3,15);
							}
											
						}
					}
					
					
					//decremento
					else if(Pot_player1<32 && Pot_player1>0){
						if(flag_delete == 0)
							flag_delete = 1;
					
						if(LeftRaqY <32 && LeftRaqY > 0){
								
							for(j = 32; j<=Pot_player1 ;j++){
								LeftRaqY = j;
								
								/*LCD1_PutPixel(LeftRaqX-1,j,TRUE);
								LCD1_PutPixel(LeftRaqX-2,j,TRUE);
								LCD1_PutPixel(LeftRaqX-3,j,TRUE);
								LCD1_PutPixel(LeftRaqX+1,j+1,FALSE);*/
								//LCD1_UpdateRegion(LeftRaqX,LeftRaqY,3,15);
								//LCD1_UpdateFull();
								//LCD1_UpdateRegion(LeftRaqX,LeftRaqY-j,3,15);
							}
						}
					}
					
					
					else if (Pot_player2<64 && Pot_player2>32){
					if(flag_delete == 0)
						flag_delete = 1;
					
						if(LeftRaqY < 64 && LeftRaqY > 32){
							
						
							for(j = 1; j<=Pot_player2 ;j++){	
								RightRaqY = j;
							/*	LCD1_PutPixel(RightRaqX-1,j,TRUE);
								LCD1_PutPixel(RightRaqX-2,j,TRUE);
								LCD1_PutPixel(RightRaqX-3,j,TRUE);
								LCD1_PutPixel(RightRaqX,j+1,FALSE);*/
								//LCD1_UpdateRegion(RightRaqX,RightRaqY,3,15);
								//LCD1_UpdateFull();
								//LCD1_UpdateRegion(LeftRaqX,LeftRaqY-j,3,15);
							}
											
						}
					}
				}
			}





			  (v)Task_Sleep(10);
				if(Mutex_Take(&MutexTest)==MUTEX_OK){
				do{
					//Aqui va la funcion de lanzar de cada jugador;
					//LeftRaq
					if(ball_x == LeftRaqX + 3)
					{
						if((ball_y + 1) >= LeftRaqY && (ball_y+1) < (LeftRaqY + 8))
						{
							dx = 1;
							dy = -1;
						}else if((ball_y+1) == (LeftRaqY + 8))
						{
							dx = 1;
							dy = 0;
						}
						else if((ball_y+1) >= (LeftRaqY + 9) && (ball_y+1) < LeftRaqY + 15)
						{
							dx = 1;
							dy = 1;
						}
					}
					
						//RightRaq
					if(RightRaqX == (ball_x+3))
					{
						if((ball_y+1) >= RightRaqY && (ball_y+1) < (RightRaqY + 8))
						{
							dx = -1;
							dy = -1;
						}else if((ball_y+1) == (RightRaqY + 8))
						{
							dx = -1;
							dy = 0;
						}else if((ball_y+1) >= (RightRaqY + 9) && (ball_y+1) < RightRaqY + 15)
						{
							dx = -1;
							dy = 1;
						}
					}		


					(v)Task_Sleep(10);
				}while(!Button_1_GetVal());
				(v)Mutex_Give(&MutexTest);
			 
			  
			 
			  
			 
	
		}
	}
	
}


void FuncionTareaSemaforo(void *Param){
	
	u16 Time = (u16)Param;
	for(;;){
		(v)Task_Sleep(Time);
		(v)Semaforo_Give(&SemTest);
	}
	
}

/*
void FuncionTareaButton(void *Param){
	
	for(;;){
		(v)Task_Sleep(10);
		if(!Button_1_GetVal()){
			
			if(Mutex_Take(&MutexTest)==MUTEX_OK){
				
			
				do{
					Led1_SetVal();
					(v)Task_Sleep(10);
				}while(!Button_1_GetVal());
				(v)Mutex_Give(&MutexTest);
			}
		}
	}
}

void FuncionTareaLed(void *Param){
	for(;;){
			(v)Task_Sleep(10);
			if(Mutex_Take(&MutexTest)==MUTEX_OK){
				Led_ejemplo_ClrVal();
				(v)Mutex_Give(&MutexTest);
			}	
	}
}*/

//revisar esta funcion en la grabaci�n
void FuncionTareaEvento(void * Param){
	unsigned long Val;
	unsigned long i;
	for(;;){
		
		while(Message_GetMsgUsedCount(&Message)>0){

			if(Message_Receive(&Message, &Val) == MESSAGE_OK){
				for (i=0; i<Val; i++){
					
					Led1_NegVal();
				}
				
				
			}
		}
		Task_Sleep(200);
		/*if(Event_WaitAny(&EventTest, (EVENT_LED1 | EVENT_LED2 | EVENT_LED3 | EVENT_LED4))){
			(v)Event_Clear(&EventTest, (EVENT_LED1 | EVENT_LED2 | EVENT_LED3 | EVENT_LED4));
			Led1_NegVal();
		}*/
	}
}
/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
