/*
 * software_timer.h
 *
 *  Created on: Oct 30, 2023
 *      Author: HP
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include<stdint.h>
#include"port.h"

#define FREQUENCY_OF_TIM	1000 //Hz
#define READ_BUTTON_TIME	10 //10ms

#define TEST_TIME 1000

void set_timer(unsigned i, unsigned int time);
void run_timer(void);
bool is_timer_on(unsigned i);
#endif /* INC_SOFTWARE_TIMER_H_ */
