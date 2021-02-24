/*
 * switch.c
 *
 *  Created on: Feb 24, 2021
 *      Author: Bartłomiej Burda
 */
#include "switch.h"

void init_button(struct Switch* switch_handler, GPIO_TypeDef* switch_port, uint16_t switch_pin, uint32_t debounce_time){
	switch_handler-> Port = switch_port;
	switch_handler-> Pin = switch_pin;
	switch_handler-> Debounce_Time = debounce_time;
	switch_handler-> Start_Time = 0;
	switch_handler-> State_Machine = Reset;
}


// function return 1 when switch is activated and 0 when not
int update_switch (struct Switch* switch_handler){

	GPIO_TypeDef* switch_port = switch_handler-> Port;
	uint16_t switch_pin = switch_handler-> Pin;
	uint32_t debounce_time = switch_handler-> Debounce_Time;
	uint32_t start_time = switch_handler-> Start_Time;
	enum State state_machine = switch_handler-> State_Machine;

	int result = 0;
	uint32_t current_time = 0;

	switch(state_machine)
	{
	case Reset:
		state_machine = Start;

		break;
	case Start:
		if(HAL_GPIO_ReadPin(switch_port, switch_pin) == 0){
			state_machine = Go;
		}
		break;
	case Go:
		start_time = HAL_GetTick();
		state_machine= Wait;
		break;
	case Wait:
		current_time = HAL_GetTick();
		if(HAL_GPIO_ReadPin(switch_port, switch_pin) == 1){
			state_machine = Reset;
		}
		if(current_time - start_time > debounce_time){
			state_machine = Lock;
		}
		break;
	case Lock:
		if(HAL_GPIO_ReadPin(switch_port, switch_pin) == 1)
			state_machine = Trigger;
		break;
	case Trigger:
		result = 1;
		state_machine = Reset;
		break;
	}
	switch_handler-> State_Machine = state_machine;
	switch_handler-> Start_Time = start_time;

	return result;
}

