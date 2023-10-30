/*
 * fsm.c
 *
 *  Created on: Oct 30, 2023
 *      Author: HP
 */

#include"fsm.h"

#define TOGGLE_TIME 250

enum {
	release, pressed, long_pressed
} button_st;

bool button_fsm(void) {
	switch (button_st) {
	case release:
		if (is_button_pressed(0) == 1) {
			// to do
			HAL_GPIO_TogglePin(LED1_PORT, LED1);
			button_st = pressed;
		} else if (is_button_pressed(0) == ERROR)
			return 0;
		break;
	case pressed:
		if (!is_button_pressed(0)) {
			button_st = release;
		} else if (is_button_long_pressed(0) == 1) {
			set_timer(1, TOGGLE_TIME);
			button_st = long_pressed;
		} else {
			return 0;
		}
		break;
	case long_pressed:
		// to do
		if(!is_timer_on(1)){
			HAL_GPIO_TogglePin(LED1_PORT, LED1);
			set_timer(1, TOGGLE_TIME);
		}
		if (!is_button_pressed(0)) {
			button_st = release;
		}
		break;
	default:
		return 0;
		break;
	}
	return 1;
}
