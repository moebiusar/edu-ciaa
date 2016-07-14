/* Copyright 2014, ACSE & CADIEEL
 *    ACSE   : http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *    CADIEEL: http://www.cadieel.org.ar
 * All rights reserved.
 *
 *    or
 *
 * Copyright 2014, Carlos I. Mancón <cimancon@gmail.com>
 * All rights reserved.
 *
 *    or
 *
 * Copyright 2014, ACSE & CADIEEL & Carlos I. Mancón <cimancon@gmail.com>
 *    ACSE   : http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *    CADIEEL: http://www.cadieel.org.ar
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

#ifndef MIDI_UART_H
#define MIDI_UART_H
/** \brief Midi Header File
 **
 ** This files shall be included by modules using the interfaces provided by
 ** the Midi
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Midi CIAA Midi
 ** @{ */

/*==================[inclusions]=============================================*/
#include "midi.h"
/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/


/*==================[typedef]================================================*/

typedef enum{
   UART_USB, UART_232, UART_485, USB
} MidiUart_t;

/*==================[external data declaration]==============================*/
//extern midi_Packet;
/*==================[external functions declaration]=========================*/
void Midi_UartConfig( MidiUart_t uart );
void Midi_Uart_Send_Event(midi_Packet *packetPtr);
/*
 * @brief   Data consumer in the Rx side of the communication
 * @param    none
 * @return   the oldest byte in the reception buffer. 0 if there is
 *   no new data.
 * @note   if there is no new data, the return will be zero
 */
uint8_t uartCanRead (void);

/*
 * @brief   indicates if there data available in the reception buffer
 * @param   none
 * @return   1 if there is a byte in the reception buffer, 0 if not
 * @note   this function should be used before uartRead() to avoid receiving
 *   invalid bytes
 */
uint8_t uartRead( void );

/*
 * @brief   Data producer in the Tx side of the communication
 * @param   byte:   data to be writen in the transmission buffer
 * @return   nothing
 */
void uartWrite( uint8_t byte);

/*
 * @brief   write a string to the transmission buffer
 * @param   strPtr:   pointer to the string
 * @param   strLengt:   length of the string (sizeof)
 * @return   nothing
 * @note   Max string length = SRB_SIZE
 */
void uartWriteString( uint8_t *strPtr,uint8_t strLength);
/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef MIDI_UART_H */

