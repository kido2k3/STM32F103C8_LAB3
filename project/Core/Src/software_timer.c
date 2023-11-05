/*
 * software_timer.c
 *
 *  Created on: Oct 30, 2023
 *      Author: HP
 */

#include"software_timer.h"

#define NUMBER_OF_TIMER	5
/*
 * bief: state --> timer is on or off
 * */
struct {
	bool state;
	unsigned int count;
} timer[NUMBER_OF_TIMER];
/* timer[0]: to scan 4 7-seg leds
 * timer[1]: to display traffic led
 * timer[2]: to read button
 * timer[3]: to toggle led
 * timer[4]: to increase value by 1 over time
 * */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	run_timer();
}
//time unit is ms
void set_timer(unsigned i, unsigned int time) {
	timer[i].count = time * FREQUENCY_OF_TIM / 1000.0;
	timer[i].state = 1;
}
void run_timer(void) {
	for (unsigned i = 0; i < NUMBER_OF_TIMER; i++) {
		if (timer[i].state) {
			timer[i].count--;
			if (timer[i].count <= 0) {
				timer[i].state = 0;
			}
		}
	}
}
bool is_timer_on(unsigned i) {
	return (timer[i].state == 1);
}

