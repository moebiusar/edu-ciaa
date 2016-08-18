/*
 * board.h
 *
 *  Created on: 9/5/2016
 *      Author: jorge
 */

#ifndef PROYECTOS_CLASE2_INC_BOARD_H_
#define PROYECTOS_CLASE2_INC_BOARD_H_



#define TEC1_P    1
#define TEC1_P_   0
#define TEC1_GPIO 0
#define TEC1_PIN  4

#define TEC2_P    1
#define TEC2_P_   1
#define TEC2_GPIO 0
#define TEC2_PIN  8

#define TEC3_P    1
#define TEC3_P_   2
#define TEC3_GPIO 0
#define TEC3_PIN  9

#define TEC4_P    1
#define TEC4_P_   6
#define TEC4_GPIO 1
#define TEC4_PIN  9

#define LEDR_P    2
#define LEDR_P_   0
#define LEDR_GPIO 5
#define LEDR_PIN  0

#define LEDG_P    2
#define LEDG_P_   1
#define LEDG_GPIO 5
#define LEDG_PIN  1

#define LEDB_P    2
#define LEDB_P_   2
#define LEDB_GPIO 5
#define LEDB_PIN  2

#define LED1_P    2
#define LED1_P_  10
#define LED1_GPIO 0
#define LED1_PIN 14

#define LED2_P    2
#define LED2_P_  11
#define LED2_GPIO 1
#define LED2_PIN 11

#define LED3_P    2
#define LED3_P_  12
#define LED3_GPIO 1
#define LED3_PIN 12

#define _INPUT 0
#define _OUTPUT 1

#define ON        1
#define OFF       0

void board_init(void);



#endif /* PROYECTOS_CLASE2_INC_BOARD_H_ */
