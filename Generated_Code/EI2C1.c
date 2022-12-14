/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : EI2C1.c
**     Project     : Proyecto_SOTR
**     Processor   : MC9S08PT60VLH
**     Component   : SW_I2C
**     Version     : Component 01.121, Driver 03.31, CPU db: 3.00.007
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2022-05-20, 20:19, # CodeGen: 64
**     Abstract    :
**         This device "SW_I2C" implements an external I2C
**         communication interface. It uses two general-purpose
**         I/O pins.
**     Settings    :
**         Serial Clock (SCL) pin      :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       37            |  PTA7_FTM2FAULT2_ADP3_TSI1
**             ----------------------------------------------------
**
**         Serial Data (SDA) pin       :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       38            |  PTA6_FTM2FAULT1_ADP2_TSI0
**             ----------------------------------------------------
**
**
**         Mode                        : MASTER
**         Communication Speed         : FAST MODE
**         Output Buffer Size          : 0
**         Auto Stop Condition         : no
**         Acknowledge Polling Trials  : 2000
**
**         Speed modes
**
**             High Speed Mode         : Enabled
**             Low Speed Mode          : Disabled
**             Slow Speed Mode         : Disabled
**
**         Initialization
**
**             Slave address           : 8
**             Component function      : Enabled
**             Events                  : Enabled
**     Contents    :
**         SendChar    - byte EI2C1_SendChar(byte Chr);
**         RecvChar    - byte EI2C1_RecvChar(byte *Chr);
**         SendBlock   - byte EI2C1_SendBlock(void* Ptr, word Siz, word *Snt);
**         RecvBlock   - byte EI2C1_RecvBlock(void* Ptr, word Siz, word *Rcv);
**         SendStop    - byte EI2C1_SendStop(void);
**         SelectSlave - byte EI2C1_SelectSlave(byte Slv);
**         GetSelected - byte EI2C1_GetSelected(byte *Slv);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file EI2C1.c
** @version 03.31
** @brief
**         This device "SW_I2C" implements an external I2C
**         communication interface. It uses two general-purpose
**         I/O pins.
*/         
/*!
**  @addtogroup EI2C1_module EI2C1 module documentation
**  @{
*/         


/* MODULE EI2C1. */

#include "Events.h"
#include "PE_Error.h"
#include "EI2C1.h"
#include "ClockPin1.h"
#include "DataPin1.h"


#define ACK         0U
#define NOACK       1U
#define OUTPUT      1U
#define INPUT       0U
#define WRITE       0U
#define READ        1U
#define TRIALS      0x07D0U

static byte SlaveAddr;             /* destination slave address      */

/* Internal method prototypes */
static void Delay(void);
static void Write(byte Data);
static byte Read(void);
static bool GetAck(void);
static void SetAck(bool Ack);
static void InternalStop(void);

/*
** ===================================================================
**     Method      :  EI2C1_Delay (component SW_I2C)
**
**     Description :
**         The method waits in delay loop.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
static void Delay(void)
{
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
  asm {
    /* jsr/bsr                            (5 c) jump/branch to subroutine */
    /*
     * Delay
     *   - requested                  : 1250 ns @ 8MHz,
     *   - possible                   : 10 c, 1250 ns
     *   - without removable overhead : -1 c, -125 ns
     *     (negative value means that overhead time is greater than requested delay time)
     */
    nop                                /* (1 c: 125 ns) minimal delay */
    /* rts                                (6 c) return from subroutine */
  };
  /*lint -restore Enable MISRA rule (1.1) checking. */
}
/*lint -restore Enable MISRA rule (1.1) checking. */

/*
** ===================================================================
**     Method      :  EI2C1_Init (component SW_I2C)
**
**     Description :
**         Initializes the associated peripheral(s) and the components 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void EI2C1_Init(void)
{
  SlaveAddr = 0x10U;
}

/*
** ===================================================================
**     Method      :  EI2C1_Write (component SW_I2C)
**
**     Description :
**         The method sends one byte of data to the bus.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void Write(byte Data)
{
  byte Shift;
  byte I;
  word timeout;

  Shift = 0x80U;
  for (I = 0x08U; I != 0U; I--) {
    if (Data & Shift) {
      DataPin1_SetDir((bool)INPUT); /* SDA HIGH */
    }
    else {
      DataPin1_SetDir((bool)OUTPUT);
      DataPin1_ClrVal();           /* SDA LOW */
    }
    Shift = (byte)(Shift >> 1);
    ClockPin1_SetDir((bool)INPUT); /* CLOCK HIGH PULSE */
    Delay();
    timeout = 65535U;
    while((ClockPin1_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
      timeout--;
    }
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    Delay();
  }
}

/*
** ===================================================================
**     Method      :  EI2C1_Read (component SW_I2C)
**
**     Description :
**         The method reads one byte of data from the bus.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static byte Read(void)
{
  byte Shift;
  byte I;
  word timeout;

  Shift = 0U;
  DataPin1_SetDir((bool)INPUT);    /* SDA INPUT MODE */
  for (I = 0x08U; I != 0U; I--) {
    ClockPin1_SetDir((bool)INPUT); /* CLOCK HIGH PULSE */
    Delay();
    timeout = 65535U;
    while((ClockPin1_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
      timeout--;
    }
    Shift = (byte)(Shift << 1);
    if (DataPin1_GetVal()) {
      Shift++;
    }
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    Delay();
  }
  return Shift;
}

/*
** ===================================================================
**     Method      :  EI2C1_GetAck (component SW_I2C)
**
**     Description :
**         The method reads ACK from the bus.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static bool GetAck(void)
{
  word timeout;

  DataPin1_SetDir((bool)INPUT);    /* SDA HIGH */
  ClockPin1_SetDir((bool)INPUT);   /* CLOCK HIGH PULSE */
  Delay();
  timeout = 65535U;
  while((ClockPin1_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
    timeout--;
  }
  return((bool)DataPin1_GetVal()); /* ACKNOWLEDGE VALUE */
}

/*
** ===================================================================
**     Method      :  EI2C1_SetAck (component SW_I2C)
**
**     Description :
**         The method sends ACK to the bus.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SetAck(bool Ack)
{
  word timeout;

  if (Ack) {
    DataPin1_SetDir((bool)INPUT);  /* MASTER NOACKNOWLEDGE - SDA HIGH */
  }
  else {
    DataPin1_SetDir((bool)OUTPUT);
    DataPin1_ClrVal();             /* MASTER ACKNOWLEDGE - SDA LOW */
  }
  ClockPin1_SetDir((bool)INPUT);   /* HIGH CLOCK PULSE */
  Delay();
  timeout = 65535U;
  while((ClockPin1_GetVal()==0U)&&(timeout!=0U)) { /* WAIT FOR CLOCK HIGH PULSE */
    timeout--;
  }
  ClockPin1_SetDir((bool)OUTPUT);
  ClockPin1_ClrVal();              /* LOW CLOCK PULSE */
  Delay();
  DataPin1_SetDir((bool)INPUT);    /* ACKNOWLEDGE END - SDA HIGH  */
}

/*
** ===================================================================
**     Method      :  EI2C1_InternalStop (component SW_I2C)
**
**     Description :
**         The method generates the Stop condition on the bus.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void InternalStop(void)
{
  DataPin1_SetDir((bool)OUTPUT);
  DataPin1_ClrVal();               /* STOP SETUP */
  ClockPin1_SetDir((bool)INPUT);   /* CLOCK HIGH PULSE + STOP SETUP TIME */
  Delay();
  DataPin1_SetDir((bool)INPUT);    /* STOP CONDITION */
}

/*
** ===================================================================
**     Method      :  EI2C1_SendChar (component SW_I2C)
**     Description :
**         When working as a MASTER, this method writes 7 bits of slave
**         address plus R/W bit = 0 to the I2C bus and then writes one
**         character (byte) to the bus. The slave address must be
**         specified before by the "SelectSlave" method or in the
**         component initialization section of <Slave address init>
**         property. When working as the SLAVE, this method writes one
**         character (byte) to the bus. If the ERR_NOTAVAIL error code
**         returned, the char is successfully sent to master but the
**         master device responds by an acknowledgement instead of no
**         acknowledgement at the end of transfer. <OnError> event is
**         called in this case.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledgement
**                           (MASTER mode only)
**                           ERR_NOTAVAIL - The master device sends
**                           acknowledgement instead of no
**                           acknowledgement after the last byte
**                           transfer (SLAVE mode only)
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSOFF - Clock timeout elapsed (SLAVE
**                           mode only)
** ===================================================================
*/
byte EI2C1_SendChar(byte Chr)
{
  word Trial;
  bool Acknowledge;

  Trial = TRIALS;
  do {
    DataPin1_SetDir((bool)INPUT);  /* SDA HIGH - START SETUP*/
    ClockPin1_SetDir((bool)INPUT); /* CLOCK HIGH PULSE */
    Delay();                       /* CLOCK HIGH PULSE & BUS FREE TIME */
    DataPin1_SetDir((bool)OUTPUT);
    DataPin1_ClrVal();             /* START CONDITION */
    Delay();                       /* START HOLD TIME */
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    Delay();
    Write((byte)(SlaveAddr + WRITE));
    Acknowledge = GetAck();
    --Trial;
  } while ((Trial != 0U) && Acknowledge);
  if (Acknowledge) {               /* WRONG ACKNOWLEDGE */
    EI2C1_OnNACK();
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    InternalStop();
    return ERR_BUSY;
  }
  else {
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    Delay();
  }
  Write(Chr);
  if (GetAck()) {                  /* WRONG ACKNOWLEDGE */
    EI2C1_OnNACK();
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    InternalStop();
    return ERR_BUSY;
  }
  else {
    EI2C1_OnTxChar();
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    Delay();
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  EI2C1_RecvChar (component SW_I2C)
**     Description :
**         When working as a MASTER, this method writes 7 bits of slave
**         address plus R/W bit = 1 to the I2C bus and then reads one
**         character (byte) from the bus. The slave address must be
**         specified before by the "SelectSlave" method or in the
**         component initialization section of <Slave address init>
**         property. When working as a SLAVE, this method reads one
**         character (byte) from the bus.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledgement
**                           (MASTER mode only)
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSOFF - Clock timeout elapsed (SLAVE
**                           mode only)
** ===================================================================
*/
byte EI2C1_RecvChar(byte *Chr)
{
  word Trial;
  bool Acknowledge;

  Trial = TRIALS;
  do {
    DataPin1_SetDir((bool)INPUT);  /* SDA HIGH - START SETUP */
    ClockPin1_SetDir((bool)INPUT); /* CLOCK HIGH PULSE */
    Delay();                       /* CLOCK HIGH PULSE & BUS FREE TIME */
    DataPin1_SetDir((bool)OUTPUT);
    DataPin1_ClrVal();             /* START CONDITION */
    Delay();                       /* START HOLD TIME */
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    Delay();
    Write((byte)(SlaveAddr + READ));
    Acknowledge = GetAck();
    --Trial;
  } while ((Trial != 0U) && Acknowledge);
  if (Acknowledge) {
    EI2C1_OnNACK();
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    InternalStop();
    return ERR_BUSY;
  }
  else {
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    Delay();
  }
  *Chr = Read();
  EI2C1_OnRxChar();
  SetAck((bool)NOACK);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  EI2C1_SendBlock (component SW_I2C)
**     Description :
**         When working as a MASTER, this method writes 7 bits of slave
**         address plus R/W bit = 0 to the I2C bus and then writes the
**         block of characters to the bus. If the component is disabled
**         (by the "Disable" method or initialization), the block is
**         moved to the output buffer if the <Output buffer size>
**         property is different from zero. The content of the output
**         buffer is sent immediately with the stop condition at the
**         end when the component is enabled by the "Enable" method.
**         After the output buffer transmission, the whole output
**         buffer is cleared. The slave address must be specified
**         before by the "SelectSlave" method or in component
**         initialization section of <Slave address init> property.
**         When working as a SLAVE, this method writes block of
**         characters to the bus. If the ERR_NOTAVAIL error code is
**         returned, the whole block is successfully sent to a master
**         but the master device responds by an acknowledgement instead
**         of no acknowledgment sent at the end of the last block byte
**         transfer. <OnError> event is called in this case.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - A pointer to the block of data to send
**         Siz             - The size of the block
**       * Snt             - A pointer to the number of data that are
**                           sent (copied to buffer)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledgement
**                           (MASTER mode only)
**                           ERR_TXFULL - Output buffer is full (MASTER
**                           mode only)
**                           ERR_NOTAVAIL - The master device sends
**                           acknowledgement instead of no
**                           acknowledgement after the last byte
**                           transfer (SLAVE mode only)
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSOFF - Clock timeout elapsed (SLAVE
**                           mode only)
** ===================================================================
*/
byte EI2C1_SendBlock(const void * Ptr,word Siz,word *Snt)
{
  register word I = 0x00U;
  bool Acknowledge;
  word Trial;

  *Snt = 0U;
  Trial = TRIALS;
  do {
    DataPin1_SetDir((bool)INPUT);  /* SDA HIGH  - START SETUP */
    ClockPin1_SetDir((bool)INPUT); /* CLOCK HIGH PULSE */
    Delay();                       /* CLOCK HIGH PULSE + BUS FREE TIME */
    DataPin1_SetDir((bool)OUTPUT);
    DataPin1_ClrVal();             /* START CONDITION */
    Delay();                       /* START HOLD TIME */
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    Delay();
    Write((byte)(SlaveAddr + WRITE));
    Acknowledge = GetAck();
    --Trial;
  } while ((Trial != 0U) && Acknowledge);
  if (Acknowledge) {
    EI2C1_OnNACK();
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    InternalStop();
    return ERR_BUSY;
  }
  else {
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    Delay();
  }
  for (I = 0U; I < Siz; I++) {
    Write ( *((const byte *) Ptr + I) );
    if (GetAck()) {
      EI2C1_OnNACK();
      ClockPin1_SetDir((bool)OUTPUT);
      ClockPin1_ClrVal();          /* CLOCK LOW PULSE */
      InternalStop();
      return ERR_BUSY;
    }
    else {
      EI2C1_OnTxChar();
      ClockPin1_SetDir((bool)OUTPUT);
      ClockPin1_ClrVal();          /* CLOCK LOW PULSE */
      Delay();
    }
    ++(*Snt);
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  EI2C1_RecvBlock (component SW_I2C)
**     Description :
**         When working as a MASTER, this method writes 7 bits of slave
**         address plus R/W bit = 1 to the I2C bus and then reads the
**         block of characters from the bus. The slave address must be
**         specified before by the "SelectSlave" method or in component
**         initialization section of <Slave address init> property.
**         When working as a SLAVE, this method reads the block of
**         characters from the bus.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - A pointer to the block space for received
**                           data
**         Siz             - The size of the block
**       * Rcv             - A pointer to the number of actually
**                           received data
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledgement
**                           (MASTER mode only)
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSOFF - Clock timeout elapsed (SLAVE
**                           mode only)
** ===================================================================
*/
byte EI2C1_RecvBlock(void* Ptr,word Siz,word *Rcv)
{
  register word I;
  bool Acknowledge;
  word Trial;

  *Rcv = 0U;
  Trial = TRIALS;
  do {
    DataPin1_SetDir((bool)INPUT);  /* SDA HIGH - START SETUP */
    ClockPin1_SetDir((bool)INPUT); /* CLOCK HIGH PULSE */
    Delay();                       /* CLOCK HIGH PULSE + BUS FREE TIME */
    DataPin1_SetDir((bool)OUTPUT);
    DataPin1_ClrVal();             /* START CONDITION */
    Delay();                       /* START HOLD TIME */
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    Delay();
    Write((byte)(SlaveAddr + READ));
    Acknowledge = GetAck();
    --Trial;
  } while ((Trial != 0U) && Acknowledge);
  if (Acknowledge) {
    EI2C1_OnNACK();
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    InternalStop();
    return ERR_BUSY;
  }
  else {
    ClockPin1_SetDir((bool)OUTPUT);
    ClockPin1_ClrVal();            /* CLOCK LOW PULSE */
    Delay();
  }
  for (I = 0U; I < Siz; I++) {
    *((byte *) Ptr + I) = Read();
    EI2C1_OnRxChar();
    if (I == (Siz - 1U)) {
      SetAck((bool)NOACK);
    }
    else {
      SetAck((bool)ACK);
    }
    ++(*Rcv);
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  EI2C1_SendStop (component SW_I2C)
**     Description :
**         When working as a MASTER, if the <Automatic stop condition>
**         property value is 'no', this method sends a valid stop
**         condition to the serial data line of the I2C bus to
**         terminate the communication on the bus after using send
**         methods. This method is enabled only if the component is in
**         MASTER mode and <Automatic stop condition> property value is
**         'no'
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
** ===================================================================
*/
byte EI2C1_SendStop(void)
{
  DataPin1_SetDir((bool)OUTPUT);
  DataPin1_ClrVal();               /* STOP SETUP */
  ClockPin1_SetDir((bool)INPUT);   /* HIGH CLOCK PULSE + STOP SETUP TIME */
  Delay();
  DataPin1_SetDir((bool)INPUT);    /* STOP CONDITION */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  EI2C1_SelectSlave (component SW_I2C)
**     Description :
**         When working as a MASTER, this method selects a new slave
**         for communication by its slave address value. Any send or
**         receive method are directed to or from the selected device,
**         until a new slave device is selected by this method. If the
**         selected slave uses 10-bit slave addressing, as the
**         parameter 7 bits must be passed, which involves 10-bit
**         addressing (11110XX), including two MSBs of slave address
**         (XX). The second byte of the 10-bit slave address must be
**         sent to the slave as a general character of send methods.
**         This method is available only if the component is in MASTER
**         mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Slv             - Slave address value
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
** ===================================================================
*/
byte EI2C1_SelectSlave(byte Slv)
{
  SlaveAddr = (byte)(Slv << 1);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  EI2C1_GetSelected (component SW_I2C)
**     Description :
**         When working as a MASTER, this method returns the
**         identification address value of the slave, which is
**         currently selected for communication with the master. If the
**         current slave uses 10-bit slave addressing, the method
**         returns the first 7 bits only, which involves 10-bit
**         addressing (11110XX), including two MSBs of the slave
**         address (XX). This method is not able to return the rest
**         value of 10-bit slave address. This method is available only
**         if the component is in MASTER mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Slv             - A pointer to the current selected slave
**                           address value
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte EI2C1_GetSelected(byte *Slv)
{
  *Slv = (byte)(SlaveAddr >> 1);
  return ERR_OK;
}



/* END EI2C1. */

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
