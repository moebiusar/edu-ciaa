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

#ifndef MIDI_DEFINITIONS_H
#define MIDI_DEFINITIONS_H
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

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef unsigned char uint8_t;

typedef struct{
	uint8_t type;
	uint8_t channel;
	uint8_t msg0;
	uint8_t msg1;
	uint8_t msg2;
} midi_Packet;
/*==================[external data declaration]==============================*/

enum MIDI_channel{
		CHN1,	CHN2,	CHN3,	CHN4,
		CHN5,	CHN6,	CHN7,	CHN8,
		CHN9,	CHN10,	CHN11,	CHN12,
		CHN13,	CHN14,	CHN15,	CHN16	};

enum MIDI_voice_message{
		NOTE_OFF = 0x80,
		NOTE_ON = 0x90,
		POLY_KEY_PRESSURE = 0xA0,
		CONTROL_CHANGE = 0xB0,
		PROGRAM_CHANGE = 0xC0,
		CHANNEL_PRESSURE = 0xD0,
		PITCH_BEND = 0xE0		};

enum MIDI_sys_common_message{
		TIME_CODE_QTR_FRAME = 0xF1,
		SONG_POSITION_POINTER = 0xF2,
		SONG_SELECT = 0xF3,
		TUNE_REQUEST = 0xF6,
		EOX = 0xF7					//End Of Exclusive
};

enum MIDI_sys_real_time_message{
		TIMMING_CLOCK = 0xF8,
		START = 0xFA,
		CONTINUE = 0xFB,
		STOP = 0xFC,
		ACTIVE_SENSING = 0xFE,
		SYSTEM_RESET = 0xFF
};

#define SYSTEM_EXCLUSIVE 0xF0

/*==================[external functions declaration]=========================*/

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef MIDI_DEFINITIONS_H */

