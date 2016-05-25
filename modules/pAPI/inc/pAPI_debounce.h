#ifndef _DEBOUNCE_H_
#define _DEBOUNCE_H_

#include "../../sapi_bm/inc/sAPI.h"

typedef struct{
	bool_t   change;
	bool_t   pressed;
	int8_t   tec;
	uint8_t   count;
} button;

/*==================[internal functions declaration]=========================*/

void debounce (button *);

#endif
