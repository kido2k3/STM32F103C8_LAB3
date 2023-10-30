/*
 * fsm.c
 *
 *  Created on: Oct 30, 2023
 *      Author: HP
 */

#include"fsm.h"

#define TOGGLE_TIME 100 // 100ms

enum {
	release, pressed, long_pressed
} button_st = release;

enum {
	state1, //normal state
	state2,
	state3,
	state4,
	state5,
	state6,
	state7,
	state8,
	state9,
	state10,
	state11,
	state12,
	state13
} light_st = state1;

void fsm(void) {
	switch (light_st) {
	case state1:

		break;
	case state2:

		break;
	case state3:

		break;
	case state4:

		break;
	case state5:

		break;
	case state6:

		break;
	case state7:

		break;
	case state8:

		break;
	case state9:

		break;
	case state10:

		break;
	case state11:

		break;
	case state12:

		break;
	case state13:

		break;

	default:
		break;
	}
}
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
		if (!is_timer_on(1)) {
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
