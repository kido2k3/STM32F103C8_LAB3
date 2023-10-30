/*
 * software_timer.c
 *
 *  Created on: Oct 30, 2023
 *      Author: HP
 */

#include"software_timer.h"
/*
 * bief: state --> timer is on or off
 * */
struct {
	bool state;
	unsigned int count;
} timer[2];
/* timer[0]: to read button
 * timer[1]: to toggle led when being long pressed
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
	for (unsigned i = 0; i < 2; i++) {
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

