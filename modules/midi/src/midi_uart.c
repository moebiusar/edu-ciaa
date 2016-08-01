/* Copyright 2016, Eric Pernia & Carlos I. Mancón <cimancon@gmail.com>
 * All rights reserved.
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

#include "chip.h"

#include "ring_buffer.h"

#include "midi_uart.h"

/*==================[macros and definitions]=================================*/

#define MIDI_BAUDRATE 31250

#define UART_485_LPC LPC_USART0  /* UART0 (RS485/Profibus) */
#define UART_USB_LPC LPC_USART2  /* UART2 (USB-UART) */
#define UART_232_LPC LPC_USART3  /* UART3 (RS232) */

/* Transmit and receive ring buffer sizes */
/* NOTE: if you are sending/receiving a lot of bytes in a short period of time,
 * you should increase the size of the buffers to avoid data loss */
#define SRB_SIZE 256   /* Send */
#define RRB_SIZE 256   /* Receive */

typedef unsigned char uint8_t;
//typedef unsigned int uint32_t;
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
static void Midi_Packet_to_String ( midi_Packet* Packet, uint8_t* string );
/*==================[internal data definition]===============================*/
static uint8_t midiString[3];
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
/* Transmit and receive ring buffers */
static RINGBUFF_T txring, rxring;
/*==================[external functions definition]==========================*/
void Midi_UartConfig( midiPort_t uart ){
   switch(uart){
   case UART_USB:
      Chip_UART_Init(UART_USB_LPC);
      Chip_UART_SetBaud(UART_USB_LPC, MIDI_BAUDRATE);  /* Set Baud rate */
      Chip_UART_SetupFIFOS(UART_USB_LPC, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0); /* Modify FCR (FIFO Control Register)*/
      Chip_UART_TXEnable(UART_USB_LPC); /* Enable UART Transmission */
      Chip_SCU_PinMux(7, 1, MD_PDN, FUNC6);              /* P7_1,FUNC6: UART2_TXD */
      Chip_SCU_PinMux(7, 2, MD_PLN|MD_EZI|MD_ZI, FUNC6); /* P7_2,FUNC6: UART2_RXD */

      //Enable UART Rx Interrupt
      //   Chip_UART_IntEnable(UART_USB_LPC,UART_IER_RBRINT );   //Receiver Buffer Register Interrupt
      // Enable UART line status interrupt
      //   Chip_UART_IntEnable(UART_USB_LPC,UART_IER_RLSINT ); //LPC43xx User manual page 1118
      //   NVIC_SetPriority(USART2_IRQn, 6);
      // Enable Interrupt for UART channel
      //   NVIC_EnableIRQ(USART2_IRQn);
   break;
   case UART_232:
      Chip_UART_Init(UART_232_LPC);
      Chip_UART_SetBaud(UART_232_LPC, MIDI_BAUDRATE);  /* Set Baud rate */
      Chip_UART_SetupFIFOS(UART_232_LPC, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0); /* Modify FCR (FIFO Control Register)*/
      Chip_UART_TXEnable(UART_232_LPC); /* Enable UART Transmission */
      Chip_SCU_PinMux(2, 3, MD_PDN, FUNC2);              /* P2_3,FUNC2: UART3_TXD */
      Chip_SCU_PinMux(2, 4, MD_PLN|MD_EZI|MD_ZI, FUNC2); /* P2_4,FUNC2: UART3_RXD */
   break;
   case UART_485:

   break;
   }
}

void Midi_Packet_to_String (midi_Packet* packetPtr, uint8_t* string){
	string[0] = packetPtr -> msg0;
	string[1] = packetPtr -> msg1;
	string[2] = packetPtr -> msg2;
}

void Midi_Uart_Send_Event(midi_Packet *packetPtr){
	Midi_Packet_to_String(packetPtr, midiString);
	uartWriteString( midiString, 3 );
}

/*
 * @brief   indicates if there data available in the reception buffer
 * @param   none
 * @return   1 if there is a byte in the reception buffer, 0 if not
 * @note   this function should be used before uartRead() to avoid receiving
 *   invalid bytes
 */
uint8_t uartCanRead (void)
{
   return (!RingBuffer_IsEmpty(&rxring));
}

/*
 * @brief   Data consumer in the Rx side of the communication
 * @param    none
 * @return   the oldest byte in the reception buffer. 0 if there is
 *   no new data.
 * @note   if there is no new data, the return will be zero
 */
uint8_t uartRead( void)
{
   uint8_t ch=0;
   RingBuffer_Pop(&rxring, &ch);
   return ch;
}

/*
 * @brief   Data producer in the Tx side of the communication
 * @param   byte:   data to be writen in the transmission buffer
 * @return   nothing
 */
void uartWrite( uint8_t byte )
{
   RingBuffer_Insert(&txring, &byte);
}

/*
 * @brief   write a string to the transmission buffer
 * @param   strPtr:   pointer to the string
 * @param   strLengt:   length of the string
 * @return   nothing
 * @note   Max string length = SRB_SIZE
 */
void uartWriteString(uint8_t *strPtr,uint8_t strLength)
{
   uint8_t i=0;
   for(i=0; i<strLength;i++)
   {
      uartWrite(strPtr[i]);
   }
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
