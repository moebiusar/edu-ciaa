#include "pAPI.h"
#include "../../sapi_bm/inc/sAPI.h"


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
