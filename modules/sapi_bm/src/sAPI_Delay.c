/* Copyright 2015, Eric Pernia.
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** @brief Brief for this file.
 **
 **/

/** \addtogroup groupName Group Name
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * ENP          Eric Pernia
 *
 *  */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20150923   v0.0.1   First version
 */

/*==================[inclusions]=============================================*/

#include "sAPI_DataTypes.h"
#include "sAPI_Tick.h"

#include "sAPI_Delay.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

extern volatile tick_t tickRateMS;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* ---- Inaccurate Blocking Delay ---- */

void delayInaccurate(tick_t delay_ms) {
   volatile tick_t i;
   volatile tick_t delay;

   delay = INACCURATE_TO_MS * delay_ms;

   for( i=delay; i>0; i-- );
}

/* ---- Blocking Delay ---- */

void delay (tick_t time){
    tick_t curTicks = tickRead();
    while ( (tickRead() - curTicks) < time/tickRateMS );
 }


/* ---- Non Blocking Delay ---- */

void delayConfig( delay_t * delay, tick_t duration ){
   delay->duration = duration/tickRateMS;
   delay->running = 0;
}

bool_t delayRead( delay_t * delay ){

   bool_t timeArrived = 0;

   if( !delay->running ){
      delay->startTime = tickRead();
      delay->running = 1;
   }
   else{
      if ( (tickRead() - delay->startTime) >= delay->duration ){
         timeArrived = 1;
         delay->running = 0;
      }
   }

   return timeArrived;
}

void delayWrite( delay_t * delay, tick_t duration ){
   delay->duration = duration/tickRateMS;
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/