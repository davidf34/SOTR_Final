/* ###################################################################
**     Filename    : Events.c
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
** @file Events.c
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

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
void ADC1_OnEnd(void)
{
  /* Write your code here ... */
}


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
void EI2C1_OnRxChar(void)
{
  /* Write your code here ... */
}

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
void EI2C1_OnTxChar(void)
{
  /* Write your code here ... */
}

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
void EI2C1_OnNACK(void)
{
  /* Write your code here ... */
}

/* END Events */

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
