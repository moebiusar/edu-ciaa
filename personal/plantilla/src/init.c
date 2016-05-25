/*
 * init.c
 *
 *  Created on: Apr 23, 2016
 *      Author: moebiusar
 */

/*==================[inclusions]=============================================*/
#include "init.h"       /* <= own header */

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void boardButtonsInit(void) {

   /* Config EDU-CIAA-NXP Button Pins as GPIOs */
   Chip_SCU_PinMux(TEC1_P, TEC1_P_, MD_PUP|MD_EZI|MD_ZI, FUNC0); /* P1_0,  GPIO0[4], TEC1 */
   Chip_SCU_PinMux(TEC2_P, TEC2_P_, MD_PUP|MD_EZI|MD_ZI, FUNC0); /* P1_1,  GPIO0[8], TEC2 */
   Chip_SCU_PinMux(TEC3_P, TEC3_P_, MD_PUP|MD_EZI|MD_ZI, FUNC0); /* P1_2,  GPIO0[9], TEC3 */
	Chip_SCU_PinMux(TEC4_P, TEC4_P_, MD_PUP|MD_EZI|MD_ZI, FUNC0); /* P1_6,  GPIO1[9], TEC4 */

   /* Config EDU-CIAA-NXP Button Pins as INPUT_PINs */
   Chip_GPIO_SetDir(LPC_GPIO_PORT, TEC1_GPIO, (1<<TEC1_PIN), INPUT_PIN);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, TEC2_GPIO, (1<<TEC3_PIN), INPUT_PIN);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, TEC2_GPIO, (1<<TEC2_PIN), INPUT_PIN);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, TEC4_GPIO, (1<<TEC4_PIN), INPUT_PIN);

}

static void boardLedsInit(void) {

   /* Config EDU-CIAA-NXP Led Pins as GPIOs */
   Chip_SCU_PinMux(LEDR_P, LEDR_P_, MD_PUP, FUNC4); /* P2_0,  GPIO5[0],  LEDR */
   Chip_SCU_PinMux(LEDG_P, LEDG_P_, MD_PUP, FUNC4); /* P2_1,  GPIO5[1],  LEDG */
   Chip_SCU_PinMux(LEDB_P, LEDB_P_, MD_PUP, FUNC4); /* P2_2,  GPIO5[2],  LEDB */
   Chip_SCU_PinMux(LED1_P, LED1_P_, MD_PUP, FUNC0); /* P2_10, GPIO0[14], LED1 */
   Chip_SCU_PinMux(LED2_P, LED2_P_, MD_PUP, FUNC0); /* P2_11, GPIO1[11], LED2 */
   Chip_SCU_PinMux(LED3_P, LED3_P_, MD_PUP, FUNC0); /* P2_12, GPIO1[12], LED3 */

   /* Config EDU-CIAA-NXP Led Pins as OUTPUT_PINs */
   Chip_GPIO_SetDir(LPC_GPIO_PORT, LEDR_GPIO, (1<<LEDR_PIN), OUTPUT_PIN);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, LEDG_GPIO, (1<<LEDG_PIN), OUTPUT_PIN);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, LEDB_GPIO, (1<<LEDB_PIN), OUTPUT_PIN);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, LED1_GPIO, (1<<LED1_PIN), OUTPUT_PIN);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, LED2_GPIO, (1<<LED2_PIN), OUTPUT_PIN);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, LED3_GPIO, (1<<LED3_PIN), OUTPUT_PIN);

   /* Init EDU-CIAA-NXP Led Pins OFF */
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, LEDR_GPIO, (1<<LEDR_PIN));
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, LEDG_GPIO, (1<<LEDG_PIN));
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, LEDB_GPIO, (1<<LEDB_PIN));
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED1_GPIO, (1<<LED1_PIN));
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED2_GPIO, (1<<LED2_PIN));
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED3_GPIO, (1<<LED3_PIN));

}

static void coreInit(void) {

   /* Read clock settings and update SystemCoreClock variable */
   SystemCoreClockUpdate();

}
