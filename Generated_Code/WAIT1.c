/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : WAIT1.c
**     Project     : Proyecto_SOTR
**     Processor   : MC9S08PT60VLH
**     Component   : Wait
**     Version     : Component 01.091, Driver 01.00, CPU db: 3.00.007
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2022-05-20, 20:10, # CodeGen: 61
**     Abstract    :
**          Implements busy waiting routines.
**     Settings    :
**          Component name                                 : WAIT1
**          Manual Clock Values                            : Disabled
**          Delay100usFunction                             : Delay100US
**          RTOS                                           : Disabled
**          Watchdog                                       : Disabled
**     Contents    :
**         Wait10Cycles   - void WAIT1_Wait10Cycles(void);
**         Wait100Cycles  - void WAIT1_Wait100Cycles(void);
**         WaitCycles     - void WAIT1_WaitCycles(uint32_t cycles);
**         WaitLongCycles - void WAIT1_WaitLongCycles(uint32_t cycles);
**         Waitms         - void WAIT1_Waitms(uint32_t ms);
**         Waitus         - void WAIT1_Waitus(uint32_t us);
**         Waitns         - void WAIT1_Waitns(uint32_t ns);
**         WaitOSms       - void WAIT1_WaitOSms(void);
**         Init           - void WAIT1_Init(void);
**         Deinit         - void WAIT1_Deinit(void);
**
**     * Copyright (c) 2013-2021, Erich Styger
**      * Web:         https://mcuoneclipse.com
**      * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**      * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**      * All rights reserved.
**      *
**      * Redistribution and use in source and binary forms, with or without modification,
**      * are permitted provided that the following conditions are met:
**      *
**      * - Redistributions of source code must retain the above copyright notice, this list
**      *   of conditions and the following disclaimer.
**      *
**      * - Redistributions in binary form must reproduce the above copyright notice, this
**      *   list of conditions and the following disclaimer in the documentation and/or
**      *   other materials provided with the distribution.
**      *
**      * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**      * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**      * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**      * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**      * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**      * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**      * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**      * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**      * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**      * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file WAIT1.c
** @version 01.00
** @brief
**          Implements busy waiting routines.
*/         
/*!
**  @addtogroup WAIT1_module WAIT1 module documentation
**  @{
*/         

/* MODULE WAIT1. */

#include "WAIT1.h"


/*
** ===================================================================
**     Method      :  WAIT1_Wait10Cycles (component Wait)
**     Description :
**         Wait for 10 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#ifdef __GNUC__
#if MCUC1_CONFIG_CPU_IS_RISC_V || MCUC1_CONFIG_CPU_IS_ESP32 /* naked is ignored for RISC-V or ESP32 gcc */
  #ifdef __cplusplus  /* gcc 4.7.3 in C++ mode does not like no_instrument_function: error: can't set 'no_instrument_function' attribute after definition */
  #else
    __attribute__((no_instrument_function))
  #endif
#else
  #ifdef __cplusplus  /* gcc 4.7.3 in C++ mode does not like no_instrument_function: error: can't set 'no_instrument_function' attribute after definition */
    __attribute__((naked))
  #else
    __attribute__((naked, no_instrument_function))
  #endif
#endif
#endif
void WAIT1_Wait10Cycles(void)
{
  /* This function will wait 10 CPU cycles (including call overhead). */
  /*lint -save -e522 function lacks side effect. */
  __asm {
      ; BSR to here  ;  [5]
      ; RTS would be    [6]
  }
  /*lint -restore */
}

/*
** ===================================================================
**     Method      :  WAIT1_Wait100Cycles (component Wait)
**     Description :
**         Wait for 100 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if MCUC1_CONFIG_COMPILER==MCUC1_CONFIG_COMPILER_IAR
  /* Implemented in assembly file, as IAR does not support labels in HLI */
#else
void WAIT1_Wait100Cycles(void)
{
  /* This function will spend 100 CPU cycles (including call overhead). */
  /*lint -save -e522 function lacks side effect. */
  __asm {
      ; BSR to here  ;  [5]
      PSHH            ; [2], reserve space on stack
      LDA #13         ; [2], n
      TSX             ; [2]
      STA 0,X         ; [2]
    Label:
      DBNZ X,Label    ; 13*[6] =[78]
      PULH            ; [3]
      ; RTS would be    [6]
  }
  /*lint -restore */
}
#endif  /* MCUC1_CONFIG_COMPILER==MCUC1_CONFIG_COMPILER_IAR */

/*
** ===================================================================
**     Method      :  WAIT1_WaitCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles.
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/
void WAIT1_WaitCycles(uint32_t cycles)
{
  /*lint -save -e522 function lacks side effect. */
#if WAIT1_CONFIG_USE_CYCLE_COUNTER
  uint32_t counter = cycles;

  counter += McuArmTools_GetCycleCounter();
  while(McuArmTools_GetCycleCounter()<counter) {
    /* wait */
  }
#else
  while(cycles >= 100u) {
    WAIT1_Wait100Cycles();
    cycles -= 100u;
  }
  while(cycles >= 10u) {
    WAIT1_Wait10Cycles();
    cycles -= 10u;
  }
#endif
  /*lint -restore */
}

/*
** ===================================================================
**     Method      :  WAIT1_WaitLongCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles (32bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/
void WAIT1_WaitLongCycles(uint32_t cycles)
{
#if WAIT1_CONFIG_USE_CYCLE_COUNTER
  uint32_t counter = cycles;

  counter += McuArmTools_GetCycleCounter();
  while(McuArmTools_GetCycleCounter()<counter) {
    /* wait */
  }
#else
  /*lint -save -e522 function lacks side effect. */
  while(cycles>60000) {
    WAIT1_WaitCycles(60000);
    cycles -= 60000;
  }
  WAIT1_WaitCycles(cycles);
  /*lint -restore */
#endif
}

/*
** ===================================================================
**     Method      :  WAIT1_Waitms (component Wait)
**     Description :
**         Wait for a specified time in milliseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ms              - How many milliseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/
#pragma MESSAGE DISABLE C5905 /* multiplication with one */
void WAIT1_Waitms(uint32_t ms)
{
  /*lint -save -e522 function lacks side effect. */
  uint32_t msCycles; /* cycles for 1 ms */

  /* static clock/speed configuration */
  msCycles = WAIT1_NofCyclesMs(1, WAIT1_INSTR_CLOCK_HZ);
  while(ms>0) {
    WAIT1_WaitLongCycles(msCycles);
    ms--;
  }
  /*lint -restore */
}
#pragma MESSAGE DEFAULT C5905 /* multiplication with one */
/*
** ===================================================================
**     Method      :  WAIT1_Waitus (component Wait)
**     Description :
**         Wait for a specified time in microseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us              - How many microseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/
/* implemented as macro version. See header file. */
/*
** ===================================================================
**     Method      :  WAIT1_Waitns (component Wait)
**     Description :
**         Wait for a specified time in nano seconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ns              - How many ns the function has to wait
**     Returns     : Nothing
** ===================================================================
*/
/* implemented as macro version. See header file. */
/*
** ===================================================================
**     Method      :  WAIT1_WaitOSms (component Wait)
**     Description :
**         If an RTOS is enabled, this routine will use a non-blocking
**         wait method. Otherwise it will do a busy/blocking wait.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void WAIT1_WaitOSms(void)
{
  Method is implemented as macro in the header file
}
*/

/*
** ===================================================================
**     Method      :  WAIT1_Init (component Wait)
**     Description :
**         Driver initialization routine.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void WAIT1_Init(void)
{
#if WAIT1_CONFIG_USE_CYCLE_COUNTER
  /* init cycle counter */
  McuArmTools_InitCycleCounter();
  McuArmTools_ResetCycleCounter();
  McuArmTools_EnableCycleCounter();
#endif
}

/*
** ===================================================================
**     Method      :  WAIT1_Deinit (component Wait)
**     Description :
**         Driver de-initialization routine
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void WAIT1_Deinit(void)
{
#if WAIT1_CONFIG_USE_CYCLE_COUNTER
  /* disable hardware cycle counter */
  McuArmTools_DisableCycleCounter();
#endif
}

/* END WAIT1. */

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
