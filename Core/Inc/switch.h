/*
 * switch.h
 *
 *  Created on: Feb 24, 2021
 *      Author: Bartłomiej Burda
 */
// Debounce of switch without Delay function

#ifndef INC_SWITCH_H_
#define INC_SWITCH_H_

#include "stm32f3xx_hal.h"

enum State{ Reset, Start, Go, Wait, Trigger, Lock};

struct Switch{
	uint32_t Debounce_Time;
	GPIO_TypeDef* Port;
	uint16_t Pin;
	uint32_t Start_Time;
	enum State State_Machine;
};

void init_button(struct Switch* switch_handler, GPIO_TypeDef* switch_port, uint16_t switch_pin, uint32_t debounce_time);
int update_switch(struct Switch* switch_handler);

#endif /* INC_SWITCH_H_ */
