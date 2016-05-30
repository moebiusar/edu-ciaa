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

#include "../../Examen_ej2/inc/main.h"         /* <= own header */

#include "sAPI.h"         /* <= sAPI header */

#include <stdlib.h>

/*==================[macros and definitions]=================================*/

typedef enum{MENU, ESPERA_ENTRADA, ESPERA_1S, ESPERA_2S, E_LEDR, E_LEDG, E_LEDB,
			E_LED1, E_LED2, E_LED3, E_TEC1, E_TEC2, E_TEC3, E_TEC4, ALLOFF} estadoMEF;

#define T_MUESTRA1 1000
#define T_MUESTRA2 2000

typedef struct{
	bool_t   change;
	bool_t   pressed;
	int8_t   tec;
	uint8_t   count;
} button;


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

void debounce (button *);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/* Variable de estado */
estadoMEF estadoActual;

/* Variables que almacenan estado pasado y presente del botón */
bool_t buttonPressed = FALSE;
bool_t buttonPressedAnterior = FALSE;

/* Flags */
bool_t cambioLed;
bool_t cambioContador;

uint8_t entrada;

button tec1;
button tec2;
button tec3;
button tec4;

delay_t delayMuestra1;
delay_t delayMuestra2;

/*==================[internal functions definition]==========================*/

/**
 * La función debounce debe ser llamada periodicamente para muestrear el
 * estado del botón. Su parametro de entreada es un struct que contiene:
 * 			*boton->change: tipo bool almacena si hubo cambio en la entrada
 * 			*boton->pressed: tipo bool, almacena si el TEC esta presionado
 * 			*boton->count: tipo int, almacena la cantidad de muestreos
 * 						   pendientes
 * 			*boton->tec: tipo int, almacena de qué TEC de hardware.
 *
 * La cantidad de muestreos es asimetrico segun el estado del botón. Cuando
 * el estado cambia de Abierto a Cerrado, se espera que el rebote sea menor
 * que cuando pasa de Cerrado a Abieto.
 *  *
 * */
void debounce (button *boton){

	#define MUESTREO_A_C   2
	#define MUESTREO_C_A   10
	bool_t valor;				// Variable para leer el TEC
	boton->change = FALSE;		// Reinicializa variable de cambio

	valor = !digitalRead( boton->tec );
	if ( boton->pressed == valor ){
		// No hubo cambio. Configuramos contadores.
		if ( boton->pressed == TRUE)
			/* Si el botón se encuentra cerrado */
			boton->count = MUESTREO_C_A;
		else
			/* Si el botón se encuentra abierto */
			boton->count = MUESTREO_A_C;
	}
	else{
		// Hubo cambio. Muestreamos a ver si es estable
		if ( --boton->count <= 0 ){
			/* Después de la cantidad de muestreos correspondiente
			 * en el mismo estado, se formaliza el cambio */
			boton->pressed = valor;
			boton->change = TRUE;
			// Reestablecemos contador para siguiente evento
			if ( boton->pressed == TRUE)
				boton->count = MUESTREO_C_A;
			else
				boton->count = MUESTREO_A_C;
		}
	}
}

/*==================[external functions definition]==========================*/

void ImprimirMenu (void){

	uartWriteString(UART_USB, (uint8_t*)"==============================================\r\n");
	uartWriteString(UART_USB, (uint8_t*)"=             Menú de selección              =\r\n");
	uartWriteString(UART_USB, (uint8_t*)"==============================================\r\n");
	uartWriteString(UART_USB, (uint8_t*)"\r\n");
	uartWriteString(UART_USB, (uint8_t*)"r -> Enciende el Led R.\r\n");
	uartWriteString(UART_USB, (uint8_t*)"g -> Enciende el Led G.\r\n");
	uartWriteString(UART_USB, (uint8_t*)"b -> Enciende el Led B.\r\n");
	uartWriteString(UART_USB, (uint8_t*)"1 -> Enciende el Led 1.\r\n");
	uartWriteString(UART_USB, (uint8_t*)"2 -> Enciende el Led 2.\r\n");
	uartWriteString(UART_USB, (uint8_t*)"3 -> Enciende el Led 3.\r\n");
	uartWriteString(UART_USB, (uint8_t*)"0 -> Apaga todos los Leds.\r\n");
	uartWriteString(UART_USB, (uint8_t*)"O bien, presione una tecla de la placa.\r\n");
	uartWriteString(UART_USB, (uint8_t*)"\r\n");
	uartWriteString(UART_USB, (uint8_t*)"Opción: ");
}

/**
 *
 */

   void MEF_Init ( void ){
	   estadoActual = MENU;
   }

/**
 *
 */
   void MEF_Update ( void ){

	   switch (estadoActual) {
	   case MENU:
		   ImprimirMenu();
		   estadoActual = ESPERA_ENTRADA;
			break;
	   case ESPERA_ENTRADA:
		   debounce(&tec1);
		   debounce(&tec2);
		   debounce(&tec3);
		   debounce(&tec4);
		   entrada = uartReadByte(UART_USB);
		   switch (entrada) {
		   case 'r':
		   case 'R':
			   estadoActual = E_LEDR;
			   break;
		   case 'g':
		   case 'G':
			   estadoActual = E_LEDG;
			   break;
		   case 'b':
		   case 'B':
			   estadoActual = E_LEDB;
			   break;
		   case '1':
			   estadoActual = E_LED1;
			   break;
		   case '2':
			   estadoActual = E_LED2;
			   break;
		   case '3':
			   estadoActual = E_LED3;
			   break;
		   case '0':
			   estadoActual = ALLOFF;
			   break;
		   default:
			   break;
		   }
		   if (tec1.change)
			   if(tec1.pressed)
				   estadoActual = E_TEC1;
		   if (tec2.change)
			   if(tec2.pressed)
				   estadoActual = E_TEC2;
		   if (tec3.change)
			   if(tec3.pressed)
				   estadoActual = E_TEC3;
		   if (tec4.change)
			   if(tec4.pressed)
				   estadoActual = E_TEC4;
		   break;
	   case E_LEDB:
		   uartWriteString(UART_USB, (uint8_t*)"Led B encendido.\r\n");
		   uartWriteString(UART_USB, (uint8_t*)"\r\n");
		   digitalWrite( LEDB, ON );
		   estadoActual = ESPERA_2S;
		   break;
	   case E_LEDG:
		   uartWriteString(UART_USB, (uint8_t*)"Led G encendido.\r\n");
		   uartWriteString(UART_USB, (uint8_t*)"\r\n");
		   digitalWrite( LEDG, ON );
		   estadoActual = ESPERA_2S;
		   break;
	   case E_LEDR:
		   uartWriteString(UART_USB, (uint8_t*)"Led R encendido.\r\n");
		   uartWriteString(UART_USB, (uint8_t*)"\r\n");
		   digitalWrite( LEDR, ON );
		   estadoActual = ESPERA_2S;
		   break;
	   case E_LED1:
		   uartWriteString(UART_USB, (uint8_t*)"Led 1 encendido.\r\n");
		   uartWriteString(UART_USB, (uint8_t*)"\r\n");
		   digitalWrite( LED1, ON );
		   estadoActual = ESPERA_2S;
		   break;
	   case E_LED2:
		   uartWriteString(UART_USB, (uint8_t*)"Led 2 encendido.\r\n");
		   uartWriteString(UART_USB, (uint8_t*)"\r\n");
		   digitalWrite( LED2, ON );
		   estadoActual = ESPERA_2S;
		   break;
	   case E_LED3:
		   uartWriteString(UART_USB, (uint8_t*)"Led 3 encendido.\r\n");
		   uartWriteString(UART_USB, (uint8_t*)"\r\n");
		   digitalWrite( LED3, ON );
		   estadoActual = ESPERA_2S;
		   break;
	   case E_TEC1:
		   uartWriteString(UART_USB, (uint8_t*)"Tecla 1 presionada.\r\n");
		   uartWriteString(UART_USB, (uint8_t*)"\r\n");
		   estadoActual = ESPERA_1S;
		   break;
	   case E_TEC2:
		   uartWriteString(UART_USB, (uint8_t*) "Tecla 2 presionada.\r\n");
		   uartWriteString(UART_USB, (uint8_t*)"\r\n");
		   estadoActual = ESPERA_1S;
		   break;
	   case E_TEC3:
		   uartWriteString(UART_USB, (uint8_t*)"Tecla 3 presionada.\r\n");
		   uartWriteString(UART_USB, (uint8_t*)"\r\n");
		   estadoActual = ESPERA_1S;
		   break;
	   case E_TEC4:
		   uartWriteString(UART_USB, (uint8_t*)"Tecla 4 presionada.\r\n");
		   uartWriteString(UART_USB, (uint8_t*)"\r\n");
		   estadoActual = ESPERA_1S;
		   break;
	   case ALLOFF:
		   digitalWrite( LEDR, OFF );
		   digitalWrite( LEDG, OFF );
		   digitalWrite( LEDB, OFF );
		   digitalWrite( LED1, OFF );
		   digitalWrite( LED2, OFF );
		   digitalWrite( LED3, OFF );
		   uartWriteString(UART_USB, (uint8_t*)"Todos los Leds apagados.\r\n");
		   uartWriteString(UART_USB, (uint8_t*)"\r\n");
		   estadoActual = ESPERA_2S;
		   break;
	   case ESPERA_1S:
		   delay(T_MUESTRA1);
		   //if ( delayRead(&delayMuestra1) )
		   estadoActual = MENU;
		   break;
	   case ESPERA_2S:
		   delay(T_MUESTRA2);
		   //if ( delayRead(&delayMuestra2) )
		   estadoActual = MENU;
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

   uartConfig(UART_USB,9600);

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

   /* Inicialización de variables */
   tec1.change = FALSE;	// No hay cambio
   tec1.pressed = FALSE;	// Normal abierto
   tec1.tec = TEC1;		// Qué botón de Hardware
   tec1.count = 2;			// Se espera cambio Abierto -> Cerrado

   tec2.change = FALSE;
   tec2.pressed = FALSE;
   tec2.tec = TEC2;
   tec2.count = 2;

   tec3.change = FALSE;
   tec3.pressed = FALSE;
   tec3.tec = TEC3;
   tec3.count = 2;

   tec4.change = FALSE;
   tec4.pressed = FALSE;
   tec4.tec = TEC4;
   tec4.count = 2;

   delayConfig( &delayMuestra1, T_MUESTRA1 );
   delayConfig( &delayMuestra2, T_MUESTRA2 );

   /* Inicialización de MEF */
   MEF_Init();

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

	   MEF_Update();

   }

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este
	   programa no es llamado por ningun S.O. */
	return 0 ;
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
