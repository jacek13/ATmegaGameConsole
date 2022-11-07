/*
 * input.c
 *
 * Created: 07.11.2022 19:40:28
 *  Author: Michal
 */ 

//#include <avr/delay.h>

#include "input.h"

void initRegisters()
{
	//DDRB |= BUTTON_UP;
	//DDRB |= BUTTON_DOWN;
	//DDRB |= BUTTON_LEFT;
	//DDRB |= BUTTON_RIGHT;
	//DDRC |= BUTTON_START;
	//DDRC |= BUTTON_SELECT;
}

uint8_t read_key(uint8_t key, uint8_t pinRegister)
{
	if(!(key & pinRegister))
	{
		//_delay_ms(20); // drgania na stykach
		if(!(key & pinRegister))
			return 1;
	}
	return 0;
}