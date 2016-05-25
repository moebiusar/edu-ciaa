/* Copyright 2016, Eric Pernia.
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

/** \brief Main example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Main example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * ENP          Eric Pernia
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 2016-04-26   v0.0.1   First version
 */

/*==================[inclusions]=============================================*/

#include "../../ej2_sAPI_LedDelayBlock/inc/main.h"         /* <= own header */

#include "sAPI.h"         /* <= sAPI header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

typedef struct{
	bool_t   change;
	bool_t   pressed;
	int8_t   tec;
	uint8_t   count;
} button;

/*==================[internal functions declaration]=========================*/

void debounce (button *);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
/**
 * La función debounce debe ser llamada periodicamente mediante una base de
 * tiempo. Su parametro es un struct que contiene:
 * 			*boton->change: tipo bool almacena si hubo cambio en la entrada
 * 			*boton->pressed: tipo bool, almacena si el TEC esta presionado
 * 			*boton->count: tipo int, almacena la cantidad de muestreos
 * 						   pendientes
 * 			*boton->tec: tipo int, almacena de qué TEC de hardware.
 *  *
 * */
void debounce (button *boton){

	bool_t valor;
	valor = !digitalRead( boton->tec );
	boton->change = FALSE;
	if ( boton->pressed == valor ){
		// No hubo cambio. Configuramos contadores.
		if ( boton->pressed == TRUE)
			boton->count = 10; // Muestrea el estado hasta pasadas 5 bases de tiempo
		else
			boton->count = 2; //
	}
	else{
		// Hubo cambio. Muestreamos a ver si es estable
		if ( --boton->count <= 0 ){
			boton->pressed = valor;
			boton->change = TRUE;
			// Reestablecemos contador para siguiente evento
			if ( boton->pressed == TRUE)
				boton->count = 10;
			else
				boton->count = 2;
		}
	}


}

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

 /* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void)
{
   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();


   tickConfig(1);

   /* Inicializar DigitalIO */
   digitalConfig( 0, INITIALIZE );

   /* Configuración de pines de entrada para
	   Teclas de la CIAA-NXP */
   digitalConfig( TEC1, INPUT );
   digitalConfig( TEC2, INPUT );
   digitalConfig( TEC3, INPUT );
   digitalConfig( TEC4, INPUT );

   /* Configuración de pines de salida para
	   Leds de la CIAA-NXP */
   digitalConfig( LEDR, OUTPUT );
   digitalConfig( LEDG, OUTPUT );
   digitalConfig( LEDB, OUTPUT );
   digitalConfig( LED1, OUTPUT );
   digitalConfig( LED2, OUTPUT );
   digitalConfig( LED3, OUTPUT );

   /* Variable para almacenar el valor de tecla leido */
   bool_t valor = 0;
   bool_t ledB = 0;
   bool_t led1 = 0;
   bool_t led2 = 0;
   bool_t led3 = 0;
   /* Variable para detectar boton presionado */
   button izquierda;
   button abajo;
   button arriba;
   button derecha;
   /* Variable para uso del delay no bloqueante */
   delay_t delay;
   /* Contador de bases de tiempo */
   uint16_t contador =50;
   /* Config de la función delay*/
   delayConfig( &delay, 10 );

   /* Inicialización de variables */
   izquierda.change = FALSE;	// No hay cambio
   izquierda.pressed = FALSE;	// Normal abierto
   izquierda.tec = TEC1;		//
   izquierda.count = 2;
   abajo.change = 0;
   abajo.pressed = 0;
   abajo.tec = TEC2;
   abajo.count = 2;
   arriba.change = 0;
   arriba.pressed = 0;
   arriba.tec = TEC3;
   arriba.count = 2;
   derecha.change = 0;
   derecha.pressed = 0;
   derecha.tec = TEC4;
   derecha.count = 2;
   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {

		if ( delayRead( &delay ) )
		if (--contador == 0)
		{
			contador = 50;
			valor = !valor;
			if(ledB) digitalWrite( LEDB, valor );
			if(led1) digitalWrite( LED1, valor );
			if(led2) digitalWrite( LED2, valor );
			if(led3) digitalWrite( LED3, valor );
		}

		debounce(&izquierda);
		debounce(&abajo);
		debounce(&arriba);
		debounce(&derecha);

		if (izquierda.change)
			if(izquierda.pressed)
				ledB = !ledB;
			else
				digitalWrite(LEDB,OFF);

		if (abajo.change)
			if(abajo.pressed)
				led1 = !led1;
			else
				digitalWrite(LED1,OFF);

		if (arriba.change)
			if(arriba.pressed)
				led2 = !led2;
			else
				digitalWrite(LED2,OFF);

		if (derecha.change)
			if(derecha.pressed)
				led3 = !led3;
			else
				digitalWrite(LED3,OFF);

		//if (abajo.pressed)		led1 = !led1;
		//if (arriba.pressed)		led2 = !led2;
		//if (derecha.pressed)		led3 = !led3;

	}

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este
	   programa no es llama-do por ningun S.O. */
	return 0 ;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
