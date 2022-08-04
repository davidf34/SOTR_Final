/* ###################################################################
**     Filename    : Events.h
**     Project     : Proyecto_SOTR
**     Processor   : MC9S08PT60VLH
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2022-03-30, 16:16, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Led1.h"
#include "Led_button.h"
#include "Button.h"
#include "ADC1.h"
#include "PWM.h"
#include "Led2.h"
#include "Button_1.h"
#include "Led_ejemplo.h"
#include "DataPin1.h"
#include "ClockPin1.h"
#include "LCD1.h"
#include "MCUC1.h"
#include "WAIT1.h"
#include "GI2C1.h"
#include "EI2C1.h"



void ADC1_OnEnd(void);
/*
** ===================================================================
**     Event       :  ADC1_OnEnd (module Events)
**
**     Component   :  ADC1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void EI2C1_OnRxChar(void);
/*
** ===================================================================
**     Event       :  EI2C1_OnRxChar (module Events)
**
**     Component   :  EI2C1 [SW_I2C]
**     Description :
**         Called when a correct character is received. In the SLAVE
**         mode, this event is not called if the component receives the
**         first byte with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void EI2C1_OnTxChar(void);
/*
** ===================================================================
**     Event       :  EI2C1_OnTxChar (module Events)
**
**     Component   :  EI2C1 [SW_I2C]
**     Description :
**         Called when a correct character is sent. In MASTER mode,
**         this event is not called if the component sends the first
**         byte with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void EI2C1_OnNACK(void);
/*
** ===================================================================
**     Event       :  EI2C1_OnNACK (module Events)
**
**     Component   :  EI2C1 [SW_I2C]
**     Description :
**         In the MASTER mode, this event is called when an invalid
**         slaves acknowledgement occurs during communication transfer.
**         If the acknowledge polling is provided (MASTER mode only), i.
**         e., the <Acknowledge polling trials> property value is
**         higher than one, this event is called only when no trial is
**         successful. In the SLAVE mode, this event is called when a
**         master sends an acknowledgement instead of no
**         acknowledgement at the end of the last byte transfer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

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
