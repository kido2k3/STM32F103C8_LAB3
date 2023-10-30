/*
 * button.c
 *
 *  Created on: Oct 30, 2023
 *      Author: HP
 */

#include"button.h"

#define NUMBER_OF_BUTTON 	1
#define RELEASE				1
#define PRESSED				0
#define LONG_PRESSED_TIME	300 // 3s


struct {
	bool reg[3];
	bool is_pressed;
	bool is_long_pressed;
	unsigned int timer;

	GPIO_TypeDef *port;
	uint16_t pin;
} button[NUMBER_OF_BUTTON];



void button_init(void) {
	for (int i = 0; i < NUMBER_OF_BUTTON; i++) {
		button[i].reg[0] = button[i].reg[1] = button[i].reg[2] = RELEASE;
		button[i].is_long_pressed = 0;
		button[i].is_pressed = 0;
		button[i].timer = LONG_PRESSED_TIME;
	}
	// port and pin were matched by hand
	button[0].port = BUTTON1_PORT;
	button[0].pin = BUTTON1;
}
void button_read(void) {
	for (unsigned i = 0; i < NUMBER_OF_BUTTON; i++) {
		button[i].reg[0] = button[i].reg[1];
		button[i].reg[1] = button[i].reg[2];
		button[i].reg[2] = HAL_GPIO_ReadPin(button[0].port, button[0].pin);
		if (button[i].reg[0] == button[i].reg[1]
				&& button[i].reg[1] == button[i].reg[2]) {
			if (button[i].reg[2] == PRESSED) {
				button[i].is_pressed = 1;
				if (button[i].timer > 0) {
					button[i].timer--;
				} else {
					button[i].is_long_pressed = 1;
				}
			} else {
				button[i].is_long_pressed = button[i].is_pressed = 0;
				button[i].timer = LONG_PRESSED_TIME;
			}
		}
	}
}

bool is_button_pressed(unsigned i) {
	if (i >= NUMBER_OF_BUTTON)
		return ERROR;
	return button[i].is_pressed;
}

bool is_button_long_pressed(unsigned i) {
	if (i >= NUMBER_OF_BUTTON)
		return ERROR;
	return button[i].is_long_pressed;
}
