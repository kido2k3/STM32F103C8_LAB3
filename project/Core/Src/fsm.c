/*
 * fsm.c
 *
 *  Created on: Oct 30, 2023
 *      Author: HP
 */

#include"fsm.h"

enum {
	release, pressed, long_pressed
} button_st[3];

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
} light_st = state1, light_pre_st = state1;
enum {
	RED_GREEN, RED_YELLOW, GREEN_RED, YELLOW_RED
} tl_st = RED_GREEN;
enum {
	ON, OFF
} led_st;
#define RED_TIME_INIT 	10
#define GREEN_TIME_INIT 8
#define YELLOW_TIME_INIT 2

uint8_t red_time = RED_TIME_INIT;
uint8_t green_time = GREEN_TIME_INIT;
uint8_t yellow_time = YELLOW_TIME_INIT;
uint8_t red_time_buffer = RED_TIME_INIT;
uint8_t green_time_buffer = GREEN_TIME_INIT;
uint8_t yellow_time_buffer = YELLOW_TIME_INIT;
uint8_t traffic_light_timer1 = RED_TIME_INIT;
uint8_t traffic_light_timer2 = GREEN_TIME_INIT;

bool button0_fsm(void);
bool button1_fsm(void);
bool button2_fsm(void);

void traffic_light_fsm(void) {
	update_led_buf(traffic_light_timer1, traffic_light_timer2);
	switch (tl_st) {
	case RED_GREEN:
		control_traffic_light(0, 1, 0, 0);
		control_traffic_light(1, 0, 0, 1);
		if (traffic_light_timer2 <= 0) {
			traffic_light_timer2 = yellow_time;
			tl_st = RED_YELLOW;
		}
		break;
	case RED_YELLOW:
		control_traffic_light(0, 1, 0, 0);
		control_traffic_light(1, 0, 1, 0);
		if (traffic_light_timer2 <= 0) {
			traffic_light_timer1 = green_time;
			traffic_light_timer2 = red_time;
			tl_st = GREEN_RED;
		}
		break;
	case GREEN_RED:
		control_traffic_light(0, 0, 0, 1);
		control_traffic_light(1, 1, 0, 0);
		if (traffic_light_timer1 <= 0) {
			traffic_light_timer1 = yellow_time;
			tl_st = YELLOW_RED;
		}
		break;
	case YELLOW_RED:
		control_traffic_light(0, 0, 1, 0);
		control_traffic_light(1, 1, 0, 0);
		if (traffic_light_timer1 <= 0) {
			traffic_light_timer1 = red_time;
			traffic_light_timer2 = green_time;
			tl_st = RED_GREEN;
		}
		break;

	default:
		break;
	}
}

void fsm_led(void) {
	switch (led_st) {
	case ON:
		switch (light_st) {
		case state2:
			control_traffic_light(0, 1, 0, 0);
			control_traffic_light(1, 1, 0, 0);
			break;
		case state3:
			control_traffic_light(0, 0, 1, 0);
			control_traffic_light(1, 0, 1, 0);
			break;
		case state4:
			control_traffic_light(0, 0, 0, 1);
			control_traffic_light(1, 0, 0, 1);
			break;
		default:
			break;
		}
		if (!is_timer_on(3)) {
			led_st = OFF;
			set_timer(3, TOGGLE_TIME);
		}
		break;
	case OFF:
		control_traffic_light(0, 0, 0, 0);
		control_traffic_light(1, 0, 0, 0);
		if (!is_timer_on(3)) {
			led_st = ON;
			set_timer(3, TOGGLE_TIME);
		}
	}
}
void fsm(void) {

	if (!is_timer_on(1)) {
		if (traffic_light_timer1 > 0)
			traffic_light_timer1--;
		if (traffic_light_timer2 > 0)
			traffic_light_timer2--;
		set_timer(1, ONE_SECOND);
	}
	if (!is_timer_on(0)) {
		if (light_st != state1 || red_time == green_time + yellow_time) {
			scan7SEG();
		} else {
			off_all7led();
		}
		set_timer(0, SCAN_7SEGLED_TIME);
	}
	switch (light_st) {
	case state1:
		if (red_time != green_time + yellow_time) {
			control_traffic_light(0, 0, 0, 0);
			control_traffic_light(1, 0, 0, 0);
		} else {
			traffic_light_fsm();
		}
		button0_fsm();

		break;
	case state2:
		if (light_pre_st != state6 && light_pre_st != state5) {
			red_time_buffer = red_time;
		}
		update_led_buf(red_time_buffer, 2);
		fsm_led();
		button0_fsm();
		button1_fsm();
		button2_fsm();

		break;
	case state3:
		if (light_pre_st != state6 && light_pre_st != state5)
			yellow_time_buffer = yellow_time;
		update_led_buf(yellow_time_buffer, 3);
		fsm_led();
		button0_fsm();
		button1_fsm();
		button2_fsm();

		break;
	case state4:
		if (light_pre_st != state6 && light_pre_st != state5)
			green_time_buffer = green_time;
		update_led_buf(green_time_buffer, 4);
		fsm_led();
		button0_fsm();
		button1_fsm();
		button2_fsm();

		break;
	case state5:
		if (light_pre_st == state2) {
			red_time = red_time_buffer;
		} else if (light_pre_st == state3) {
			yellow_time = yellow_time_buffer;
		} else if (light_pre_st == state4) {
			green_time = green_time_buffer;
		}
		light_st = light_pre_st;
		light_pre_st = state5;
		break;
	case state6:
		if (light_pre_st == state2) {
			red_time_buffer++;
		} else if (light_pre_st == state3) {
			yellow_time_buffer++;
		} else if (light_pre_st == state4) {
			green_time_buffer++;
		}
		light_st = light_pre_st;
		light_pre_st = state6;
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

	default:
		break;
	}
}
bool button0_fsm(void) {
	switch (button_st[0]) {
	case release:
		if (is_button_pressed(0) == 1) {
			// to do
			light_pre_st = light_st;
			switch (light_st) {
			case state1:
				light_st = state2;
				break;
			case state2:
				light_st = state3;
				break;
			case state3:
				light_st = state4;
				break;
			case state4:
				light_st = state1;
				break;
			default:
				break;
			}
			button_st[0] = pressed;
		} else if (is_button_pressed(0) == ERROR)
			return 0;
		break;
	case pressed:
		if (!is_button_pressed(0)) {
			button_st[0] = release;
		} else {
			return 0;
		}
		break;
	default:
		return 0;
		break;
	}
	return 1;
}
bool button2_fsm(void) {
	switch (button_st[2]) {
	case release:
		if (is_button_pressed(2) == 1) {
			// to do
			light_pre_st = light_st;
			light_st = state5;
			button_st[2] = pressed;
		} else if (is_button_pressed(2) == ERROR)
			return 0;
		break;
	case pressed:
		if (!is_button_pressed(2)) {
			button_st[2] = release;
		} else {
			return 0;
		}
		break;
	default:
		return 0;
		break;
	}
	return 1;
}
bool button1_fsm(void) {
	switch (button_st[1]) {
	case release:
		if (is_button_pressed(1) == 1) {
			// to do
			light_pre_st = light_st;
			light_st = state6;
			button_st[1] = pressed;
		} else if (is_button_pressed(1) == ERROR)
			return 0;
		break;
	case pressed:
		if (!is_button_pressed(1)) {
			button_st[1] = release;
		} else if (is_button_long_pressed(1) == 1) {
			button_st[1] = long_pressed;
		} else {
			return 0;
		}
		break;
	case long_pressed:
		// to do
		light_pre_st = light_st;
		light_st = state7;
		if (!is_button_pressed(1)) {
			button_st[1] = release;
		}
		break;
	default:
		return 0;
		break;
	}
	return 1;
}
