/* Copyright 2015, Mariano Cerdeiro
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

/** \brief This file implements the test of the Devices
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Midi CIAA Midi
 ** @{ */
/** \addtogroup UnitTests Unit Tests
 ** @{ */

/*==================[inclusions]=============================================*/
#include "unity.h"
#include "stdint.h"
#include "ciaaPOSIX_stdint.h"
#include "midi.h"
#include "mock_midi_uart.h"
//#include "../../../../../externals/drivers/cortexM4/lpc43xx/inc/ring_buffer.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief set Up function
 **
 ** This function is called before each test case is executed
 **
 **/
void setUp(void) {
}

void test_DiscrimaStatus (void){
	uint8_t resultado;

	resultado = Midi_Es_Status(0x91);
	TEST_ASSERT_EQUAL_UINT8(1, resultado);
	resultado = Midi_Es_Status(64);
	TEST_ASSERT_EQUAL_UINT8(0, resultado);
}
void test_DiscrimaDato (void){
	uint8_t resultado;

	resultado = Midi_Es_Dato(133);
	TEST_ASSERT_EQUAL_UINT8(0, resultado);
	resultado = Midi_Es_Dato(64);
	TEST_ASSERT_EQUAL_UINT8(1, resultado);
}

void test_EsMensajeDeCanal (void){

	uint8_t resultado;

	resultado = Midi_Es_Mensaje_De_Canal (0x7F);
	TEST_ASSERT_EQUAL_UINT8(0, resultado);
	resultado = Midi_Es_Mensaje_De_Canal (0x80);
	TEST_ASSERT_EQUAL_UINT8(1, resultado);
	resultado = Midi_Es_Mensaje_De_Canal (0xEF);
	TEST_ASSERT_EQUAL_UINT8(1, resultado);
	resultado = Midi_Es_Mensaje_De_Canal (0xF0);
	TEST_ASSERT_EQUAL_UINT8(0, resultado);
}

void test_EsMensajeDeSistema (void){

	uint8_t resultado;

	resultado = Midi_Es_Mensaje_De_Sistema (0xEF);
	TEST_ASSERT_EQUAL_UINT8(0, resultado);
	resultado = Midi_Es_Mensaje_De_Sistema (0xF0);
	TEST_ASSERT_EQUAL_UINT8(1, resultado);
	resultado = Midi_Es_Mensaje_De_Sistema (0xFF);
	TEST_ASSERT_EQUAL_UINT8(1, resultado);
}
void test_Inicializar_Midi_Solo_Uart (void){
	midiPortMode_t modo;

	modo = MODE_UART;
	Midi_UartConfig_Expect(UART_USB);
	Midi_Init(modo);

}
void test_Inicializar_Midi_Solo_Usb (void){
	/*midiPortMode_t modo;

	modo = MODE_USB;
	Midi_UartConfig_CMockExpect(UART_USB);
	Midi_Init(modo);
*/
	TEST_IGNORE_MESSAGE("Init USB no testeado");
}
void test_Inicializar_Midi_Uart_Usb (void){
	/*midiPortMode_t modo;

	modo = MODE_UART_USB;
	Midi_UartConfig_CMockExpect(UART_USB);
	Midi_Init(modo);
	*/
	TEST_IGNORE_MESSAGE("Init USB no testeado");
}

void test_Enviar_Evento (void){

	midi_Packet paquete;
	paquete.channel = 0x05;
	paquete.type = 0x80;
	paquete.msg0 = 0x85;
	paquete.msg1 = 64;
	paquete.msg2 = 64;
	Midi_Uart_Send_Event_Expect(&paquete);
	Midi_Send_Event (UART_PORT, &paquete);

}
/** \brief tear Down function
 **
 ** This function is called after each test case is executed
 **
 **/
void tearDown(void) {
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

