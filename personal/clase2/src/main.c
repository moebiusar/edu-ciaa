/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
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

/** \brief Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "../../clase2/inc/main.h"       /* <= own header */
#include <stdint.h>
#include "chip.h"
/*
#define   __I     volatile const       //!< Defines 'read only' permissions
#define     __O     volatile             //!< Defines 'write only' permissions
#define     __IO    volatile             //!< Defines 'read / write' permissions
#define		STATIC	static
#define INLINE inline
#define __STATIC_INLINE  static __inline	*/
/*
#include <chip_lpc43xx.h>
#include <scu_18xx_43xx.h>
#include <gpio_18xx_43xx.h>	*/
/*
#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif							*/

#define OUTPUT 1
#define INPUT 0

/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
int main(void)
{
	/* perform the needed initialization here */
	uint8_t i;
	uint8_t valorDelPulsador1 = 0;
	uint8_t valorDelPulsador2 = 0;
	uint8_t valorDelPulsador3 = 0;
	uint8_t valorDelPulsador4 = 0;
	uint16_t modoTEC1 = SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
	uint16_t modoLED1 = SCU_MODE_INACT | SCU_MODE_ZIF_DIS;


	/*	LED 1	*/
	Chip_SCU_PinMux( 2 , 10 , modoLED1 , FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT , 0 , ( 1<<14 ) , OUTPUT);

	/*	LED 2 y 3	*/
	for (i = 11; i<=12; i++){
		Chip_SCU_PinMux( 2 , i , modoLED1 , FUNC0);
		Chip_GPIO_SetDir( LPC_GPIO_PORT , 1 , ( 1<<i ) , OUTPUT);
	}


	/*	TEC 1	*/
	Chip_SCU_PinMux( 1 , 0 , modoTEC1 , FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT , 0 , ( 1<<4 ) , INPUT);

	/*	TEC 2	*/
	Chip_SCU_PinMux( 1 , 1 , modoTEC1 , FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT , 0 , ( 1<<8 ) , INPUT);

	/*	TEC 3	*/
	Chip_SCU_PinMux( 1 , 2 , modoTEC1 , FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT , 0 , ( 1<<9 ) , INPUT);

	/*	TEC 4	*/
	Chip_SCU_PinMux( 1 , 6 , modoTEC1 , FUNC0);
	Chip_GPIO_SetDir( LPC_GPIO_PORT , 1 , ( 1<<9 ) , INPUT);

	while(1) {
		/* add your code here */
		valorDelPulsador1 = Chip_GPIO_GetPinState( LPC_GPIO_PORT , 0 , 4 );
		valorDelPulsador2 = Chip_GPIO_GetPinState( LPC_GPIO_PORT , 0 , 8 );
		valorDelPulsador3 = Chip_GPIO_GetPinState( LPC_GPIO_PORT , 0 , 9 );
		valorDelPulsador4 = Chip_GPIO_GetPinState( LPC_GPIO_PORT , 1 , 9 );

		Chip_GPIO_SetPinState( LPC_GPIO_PORT , 0 , 14 , valorDelPulsador2);
		Chip_GPIO_SetPinState( LPC_GPIO_PORT , 1 , 11 , valorDelPulsador3);
		Chip_GPIO_SetPinState( LPC_GPIO_PORT , 1 , 12 , valorDelPulsador4);
	}
	return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

