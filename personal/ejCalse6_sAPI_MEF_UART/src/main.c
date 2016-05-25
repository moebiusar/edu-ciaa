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

#include "../../ejCalse6_sAPI_MEF_UART/inc/main.h"         /* <= own header */

#include "sAPI.h"         /* <= sAPI header */

/*==================[macros and definitions]=================================*/

/* ORIGINAL */
typedef enum{ ROJO, ROJO_AMARILLO, VERDE, AMARILLO } estadoMef;
/* FIN DEL ORIGINAL */

typedef enum{BUTTON_UP, BUTTON_FALLING, BUTTON_RISING, BUTTON_DOWN} estadoMEF2;

/* Definiciones de períodos */
#define T_DEBOUNCE 40	//Período de muestreo
#define T_1S	1000	//Base de tiempo del semaforo (implementación de Eric)

/* Macros */
#define toDec(X) ((X)-48)	//Macros útiles para interpretar y condicionar
#define toChar(X) ((X)+48)	//datos para la UART

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*== ORIGINAL de Eric ==*/
estadoMef estadoActual;
   
uint8_t tiempoTranscurrido = 0;
/* FIN DEL ORIGINAL */


/* Variable de estado Debounce*/
estadoMEF2 estadoActual2;

/* Variables que almacenan estado pasado y presente del botón */
bool_t buttonPressed = FALSE;
bool_t buttonPressedAnterior = FALSE;

/* Variable global para ser utilizada en el muestreo de debounce */
delay_t delayDebounce;

/* Variable de cambio para el semaforo */
bool_t cambio = FALSE;

/* Variables de períodos del semáforo */
uint16_t tiempoRojo = 2;
uint16_t tiempoRojoAmarillo = 1;
uint16_t tiempoAmarillo = 3;
uint16_t tiempoVerde = 2;


/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* Hice una modificación porque usaba el LEDG y no quedaba bien a la vista */
void ponerEnVerde( void ) {
   digitalWrite( LED1, OFF );
   digitalWrite( LED2, OFF );
   digitalWrite( LED3, ON );
}

void ponerEnAmarillo( void ) {
   digitalWrite( LED1, OFF );
   digitalWrite( LED2, ON );
   digitalWrite( LED3, OFF );
}

void ponerEnRojo( void ) {
   digitalWrite( LED1, ON );
   digitalWrite( LED2, OFF );
   digitalWrite( LED3, OFF );
}

void ponerEnRojoAmarillo( void ) {
   digitalWrite( LED1, ON );
   digitalWrite( LED2, ON );
   digitalWrite( LED3, OFF );
}

void MEF_Init( void ) {
   estadoActual = ROJO;
   estadoActual2 = BUTTON_UP; // Inicializa la MEF del debounce
   tiempoTranscurrido = 0;	  // Por precaución debido a las transiciones,
   	   	   	   	   	   	   	  // se resetea el contador de los períodos del
   	   	   	   	   	   	   	  // semaforo.
}

void MEF_Update( void ) {

	/* El update actualiza 2 maquinas de estado: la del semáforo y la
	 * del debounce. */

   switch(estadoActual){
      case ROJO:
         // Salida en el Estrado ROJO
         ponerEnRojo();
         // Chequear condiciones para cambiar de estado
         if( cambio && tiempoTranscurrido == tiempoRojo ){
            estadoActual = ROJO_AMARILLO;
            tiempoTranscurrido = 0;
            cambio = FALSE;
         }
      break;
      case ROJO_AMARILLO:
         // Salida en el Estrado ROJO_AMARILLO
         ponerEnRojoAmarillo();
         // Chequear condiciones para cambiar de estado
         if( cambio && tiempoTranscurrido == tiempoRojoAmarillo ){
            estadoActual = VERDE;
            tiempoTranscurrido = 0;
            cambio = FALSE;
         }
      break;
      case VERDE:
         // Salida en el Estrado VERDE
         ponerEnVerde();
         // Chequear condiciones para cambiar de estado
         if( cambio && tiempoTranscurrido == tiempoVerde ){
            estadoActual = AMARILLO;
            tiempoTranscurrido = 0;
            cambio = FALSE;
         }
      break;
      case AMARILLO:
         // Salida en el Estrado AMARILLO
         ponerEnAmarillo();
         // Chequear condiciones para cambiar de estado
         if( cambio && tiempoTranscurrido == tiempoAmarillo ){
            estadoActual = ROJO;
            tiempoTranscurrido = 0;
            cambio = FALSE;
         }
      break;
      default:
         MEF_Init();
      break;
   }


   switch(estadoActual2){
   case BUTTON_UP:
	   /* Acciones del estado */
	   buttonPressed = FALSE;

	   /* Verificación de condiciones de transición */
	   if( !digitalRead( TEC1 )){
		   /* Entra si el botón está presionado */
		   estadoActual2 = BUTTON_FALLING;

	   }
	   break;
   case BUTTON_FALLING:
	   /* Verificación de condiciones de transición */
	   if( delayRead( &delayDebounce ) ){
		   /* Pasado el Delay de muestreo */
		   if (!digitalRead( TEC1 ) ){
			   /* Entra si el botón está presionado */
			   estadoActual2 = BUTTON_DOWN;
			   buttonPressed = TRUE;
		   }
		   else{
			   /* Despues del delay el botón no está presionado
			    * vuelve al estado UP */
			   estadoActual2 = BUTTON_UP;
		   }
	   }
	   break;
   case BUTTON_DOWN:
	   /* Acciones del estado */
	   buttonPressed = TRUE;

	   /* Verificación de condiciones de transición */
	   if (digitalRead( TEC1 )){
		   /*Entra si el botón NO está presionado*/
		   estadoActual2 = BUTTON_RISING;
	   }
	   break;
   case BUTTON_RISING:
	   /* Verificación de condiciones de transición */
	   if( delayRead( &delayDebounce )){
		   /* Pasado el Delay de muestreo */
		   if ( digitalRead( TEC1 ) ){
			   /*Entra si el botón NO está presionado*/
			   estadoActual2 = BUTTON_UP;
			   buttonPressed = FALSE;
		   }
		   else{
			   /* Despues del delay el botón está presionado
			    * vuelve al estado DOWN */
			   estadoActual2 = BUTTON_DOWN;
		   }
	   }
	   break;
   default:
	   MEF_Init();
	   break;
   }

}

void ImprimirMenu (void){

	uartWriteString(UART_USB, (uint8_t*)"==============================================\r\n");
	uartWriteString(UART_USB, (uint8_t*)"=     Menú de configuración del Semaforo     =\r\n");
	uartWriteString(UART_USB, (uint8_t*)"==============================================\r\n");
	uartWriteString(UART_USB, (uint8_t*)"\r\n");
	uartWriteString(UART_USB, (uint8_t*)"1 -> Modificar tiempo de estado ROJO\r\n");
	uartWriteString(UART_USB, (uint8_t*)"2 -> Modificar tiempo de estado AMARILLO\r\n");
	uartWriteString(UART_USB, (uint8_t*)"3 -> Modificar tiempo de estado VERDE\r\n");
	uartWriteString(UART_USB, (uint8_t*)"4 -> Modificar tiempo de estado ROJO/AMARILLO\r\n");
	uartWriteString(UART_USB, (uint8_t*)"\r\n");
	uartWriteString(UART_USB, (uint8_t*)"Opción: ");
}

uint8_t ObtenerRespuesta (void){

	/* Copy-Paste del bloque de Pablo */
	uint8_t ret = 0;
	uint8_t option;

	option = uartReadByte(UART_USB);
	while (option!=13){
		if (option)
			ret=option;
		option = uartReadByte(UART_USB);
		uartWriteByte(UART_USB, option);
	}

	return ret;
}
uint16_t ObtenerDecimal (void){

	/* Variación sobre el bloque de Pablo. Implementa la recepción de valores decimales de más de un
	 * char desde la UART. Es una implementación riesgosa porque no considera valores inválidos.*/
	uint16_t ret = 0;
	uint8_t lectura;

	lectura = uartReadByte(UART_USB);

	/* Conversión "Serie-Paralelo" de los digitos ingresados */
	while (lectura!=13){
		if (lectura){
			ret *= 10;				//Multiplicamos para esperar la siguiente unidad
			ret += toDec(lectura);	//Sumamos nueva unidad
		}
		lectura = uartReadByte(UART_USB);
		uartWriteByte(UART_USB, lectura);
	}

	return ret;
}

void AtenderRequerimiento (uint8_t opcion){

	switch(opcion){
	case 1:
		uartWriteString(UART_USB, (uint8_t*) "\r\n");
		uartWriteString(UART_USB, (uint8_t*) "Introduzca el tiempo del estado ROJO [seg]:");
		tiempoRojo = ObtenerDecimal();
		MEF_Init();
		uartWriteString(UART_USB, (uint8_t*) "\r\n");
		break;
	case 2:
		uartWriteString(UART_USB, (uint8_t*) "\r\n");
		uartWriteString(UART_USB, (uint8_t*) "Introduzca el tiempo del estado AMARILLO [seg]:");
		tiempoAmarillo = ObtenerDecimal();
		MEF_Init();
		uartWriteString(UART_USB, (uint8_t*) "\r\n");
		break;
	case 3:
		uartWriteString(UART_USB, (uint8_t*) "\r\n");
		uartWriteString(UART_USB, (uint8_t*) "Introduzca el tiempo del estado VERDE [seg]:");
		tiempoVerde = ObtenerDecimal();
		MEF_Init();
		uartWriteString(UART_USB, (uint8_t*) "\r\n");
		break;
	case 4:
		uartWriteString(UART_USB, (uint8_t*) "\r\n");
		uartWriteString(UART_USB, (uint8_t*) "Introduzca el tiempo del estado ROJO/AMARILLO [seg]:");
		tiempoRojoAmarillo = ObtenerDecimal();
		MEF_Init();
		uartWriteString(UART_USB, (uint8_t*) "\r\n");
		break;
	default:
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

   /* Inicializar UART */
   uartConfig(UART_USB,9600);

   /* Inicializar el conteo de Ticks con resolución de 1ms */
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

	/*
	Tiempo de rojo 2s
	Tiempo de rojo_amarillo 1s
	Tiempo de amarillo 3s
	Tiempo de verde 1s
	*/
   
   /* Variable para uso del delay no bloqueante */
   delay_t delay;

   /* Config de la función delay para el Blinkeo */
   delayConfig( &delay, T_1S );
   /* Config de la función delay para el Debounce */
   delayConfig( &delayDebounce, T_DEBOUNCE);

   uint8_t dato;

   MEF_Init();
   uartWriteString(UART_USB, (uint8_t*) "Inicializando\r\n");
	
   /* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		MEF_Update();
		if (delayRead(&delay)){
			cambio = TRUE;
			tiempoTranscurrido++;
		}
		/* Buscamos un cambio: Abierto -> Cerrado o viceversa */
		if (buttonPressedAnterior != buttonPressed)
		{
			/* Alamcenamos el nuevo estado del botón */
			buttonPressedAnterior = buttonPressed;
			/* Efectuamos el cambio al liberar el botón */
			if (!buttonPressed){
				ImprimirMenu();
				dato = toDec(ObtenerRespuesta());
				AtenderRequerimiento(dato);
			}
		}
	}

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este
	   programa no es llamado por ningun S.O. */
	return 0 ;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
