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

/** \brief This file implements the Midi main functionality
 **
 ** This file implements the main functionality of the Midi
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Midi CIAA Midi
 ** @{ */

/*==================[inclusions]=============================================*/
#include "midi.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
//int32_t Midi_Init_Uart(MidiUart_t uart){}

uint8_t Midi_Es_Status(uint8_t byte){

	return (byte & 128) >> 7;
}
uint8_t Midi_Es_Dato(uint8_t byte){

	return !Midi_Es_Status(byte);
}

uint8_t Midi_Es_Mensaje_De_Canal (uint8_t byte){

	uint8_t ret;
	if ((0x80 <= byte) && (0xF0 > byte)){
		ret = 1;
	}
	else
	{
		ret = 0;
	}
	return ret;
}

uint8_t Midi_Es_Mensaje_De_Sistema (uint8_t byte){

	uint8_t ret;
	if ((0xF0 <= byte) && (0xFF >= byte)){
		ret = 1;
	}
	else
	{
		ret = 0;
	}
	return ret;
}

void Midi_Init ( midiPortMode_t mode ){
	switch ( mode ){
	case MODE_USB:
		break;
	case MODE_UART_USB:
		Midi_UartConfig( UART_USB );
		//Midi_UsbConfig();
		break;
	default:
	case MODE_UART:
		Midi_UartConfig( UART_USB );
		break;
	}
}

void Midi_Send_Event (midiPort_t port, midi_Packet *packetPtr)
{
	switch(port){
	case USB_PORT:
		break;
	case UART_PORT:
	default:
		Midi_Uart_Send_Event(packetPtr);
		break;
	}

}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
