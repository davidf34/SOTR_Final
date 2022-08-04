#include "Queue.h"
#include "AppTypes.h"

u16 Queue_Init(T_QUEUE_HANDLER_PTR Queue){
    u16 Res=QUEUE_ERROR_NULL_PARAM; // Inicia en error para que cuando entre al if, quede ok.
    if(Queue){// Si Queue esta apuntado a nulo no entra al if. 
        Queue->Count=0;
        Queue->Head=NULL;
        Queue->Tail=NULL;
        Res=QUEUE_OK;
    }
    return Res;
}

u16 Queue_GetCount(T_QUEUE_HANDLER_PTR Queue){
    if(Queue){
    	return Queue->Count;
    }
    return 0;
}
u16 Queue_Enqueue(T_QUEUE_HANDLER_PTR Queue, T_QUEUE_ELEMENT_PTR Element){
    u16 Res=QUEUE_ERROR_NULL_PARAM;
	Portable_DisableInterrupts();
    if ((Queue) && (Element)){
        Queue->Count++;
        Element->Next=NULL;
        if(Queue->Tail){
            Queue->Tail->Next = Element;
        }
        else{
            Queue->Head=Element;
            Queue->Count=1;
        }
        Queue->Tail=Element;
        Res=QUEUE_OK;
    }
    //Portable_EnableInterrupts();
    return Res;
}
u16 Queue_Dequeue(T_QUEUE_HANDLER_PTR Queue, T_QUEUE_ELEMENT_PTR * Element){
    u16 Res=QUEUE_ERROR_NULL_PARAM;
    if ((Queue) && (Element)){ //Verifica que los apuntadores no sean nulos
        if (Queue->Head){
            *Element = Queue->Head;
            Queue->Count--;
            if(Queue->Head==Queue->Tail){
                Queue->Head=NULL;
                Queue->Tail=NULL;
                Queue->Count=0; 
            }else{
                Queue->Head=Queue->Head->Next;
            }
            Res=QUEUE_OK;
        }
    }
    return Res;
}
u16 Queue_Copy(T_QUEUE_HANDLER_PTR Source, T_QUEUE_HANDLER_PTR Destination)
{
	u16 Res = QUEUE_ERROR_NULL_PARAM;
	if((Source != NULL) && (Destination != NULL))
	{
		Portable_DisableInterrupts();
		Destination->Count = Source->Count;
		Destination->Head = Source->Head;
		Destination->Tail = Source->Tail;
		Res = QUEUE_OK;
		Portable_EnableInterrupts();
	}
return Res;
}

//siempre hay que verificar si el apuntador no es nulo, si se trabaja con apuntadores
