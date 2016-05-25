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

#include "../../ejClase5_sAPI/inc/main.h"         /* <= own header */

#include "sAPI.h"         /* <= sAPI header */

/*==================[macros and definitions]=================================*/

typedef enum{BUTTON_UP, BUTTON_FALLING, BUTTON_RISING, BUTTON_DOWN} estadoMEF;

#define T_DEBOUNCE 40
#define T_BLINK	500

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/* Variable de estado */
estadoMEF estadoActual;

/* Variables que almacenan estado pasado y presente del botón */
bool_t buttonPressed = FALSE;
bool_t buttonPressedAnterior = FALSE;

/* Variable global para ser utilizada en el muestreo de debounce */
delay_t delayDebounce;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/**
 *
 */

   void MEF_Init ( void ){
	   estadoActual = BUTTON_UP;
   }

/**
 *
 */

   void MEF_Update ( void ){

	   switch(estadoActual){
	   case BUTTON_UP:
		   /* Acciones del estado */
		   buttonPressed = FALSE;

		   /* Verificación de condiciones de transición */
		   if( !digitalRead( TEC1 )){
			   /* Entra si el botón está presionado */
			   estadoActual = BUTTON_FALLING;
		   }
		   break;


	   case BUTTON_FALLING:
		   /* Verificación de condiciones de transición */
		   if( delayRead( &delayDebounce ) ){
			   /* Pasado el Delay de muestreo */
			   if (!digitalRead( TEC1 ) ){
				   /* Entra si el botón está presionado */
				   estadoActual = BUTTON_DOWN;
				   buttonPressed = TRUE;
			   }
			   else
				   /* Despues del delay el botón no está presionado
				    * vuelve al estado UP */
				   estadoActual = BUTTON_UP;
		   }
		   break;


	   case BUTTON_DOWN:
		   /* Acciones del estado */
		   buttonPressed = TRUE;

		   /* Verificación de condiciones de transición */
		   if (digitalRead( TEC1 )){
			   /*Entra si el botón NO está presionado*/
			   estadoActual = BUTTON_RISING;
		   }
		   break;


	   case BUTTON_RISING:
		   /* Verificación de condiciones de transición */
		   if( delayRead( &delayDebounce )){
			   /* Pasado el Delay de muestreo */
			   if ( digitalRead( TEC1 ) ){
				   /*Entra si el botón NO está presionado*/
				   estadoActual = BUTTON_UP;
				   buttonPressed = FALSE;
			   }
			   else
				   /* Despues del delay el botón está presionado
				    * vuelve al estado DOWN */
				   estadoActual = BUTTON_DOWN;
		   }
		   break;


	   default:
		   MEF_Init();
		   break;
	   }
   }

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

   /* Variable para uso del delay no bloqueante */
   delay_t delay;

   /* Config de la función delay para el Blinkeo */
   delayConfig( &delay, T_BLINK );
   /* Config de la función delay para el Debounce */
   delayConfig( &delayDebounce, T_DEBOUNCE);

   uint8_t estado_led = OFF;
   int i=0;

   /* Inicialización de MEF */
   MEF_Init();

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

	   MEF_Update();

	   /* Buscamos un cambio: Abierto -> Cerrado o viceversa */
	   if (buttonPressedAnterior != buttonPressed)
	   {
		   /* Alamcenamos el nuevo estado del botón */
		   buttonPressedAnterior = buttonPressed;
		   /* Efectuamos el cambio al liberar el botón */
		   if (!buttonPressed)
			   i += 2;
	   }
	   /* Fragmento del programa ejemplo sin debounce */
	   if ( delayRead( &delay ) && i>0 ){

		   if( !estado_led )
			   estado_led = ON;
		   else
			   estado_led = OFF;

		   digitalWrite( LEDB, estado_led );
		   i--;
	   }
   }

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este
	   programa no es llama-do por ningun S.O. */
	return 0 ;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
