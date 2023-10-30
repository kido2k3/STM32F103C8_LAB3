/*
 * port.h
 *
 *  Created on: Oct 24, 2023
 *      Author: HP
 */

#ifndef INC_PORT_H_
#define INC_PORT_H_

#include "stm32f1xx_hal.h"

#define BUTTON_1_PORT	GPIOA
#define BUTTON_1		GPIO_PIN_5

#define LED1_PORT		GPIOA
#define LED1			GPIO_PIN_6

#define ERROR			0xff

typedef uint8_t bool;
#endif /* INC_PORT_H_ */
