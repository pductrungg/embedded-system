/*
 * software_timer.h
 *
 *  Created on: Sep 20, 2024
 *      Author: macbook
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "tim.h"
#include "software_timer.h"

extern uint16_t flag_timer2;

void timer_init();
void setTimer2(uint16_t duration);


#endif /* INC_SOFTWARE_TIMER_H_ */
