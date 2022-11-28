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

void HandleButtonInput(struct Button * button, uint8_t currentState)
{
	if (currentState)
	{
		if (button->prevoiusState == BUTTON_RELEASED && button->currentState == BUTTON_RELEASED)
		{
			button->currentState = BUTTON_FALLING_EDGE;
		}
		else if(button->prevoiusState == BUTTON_RELEASED && button->currentState == BUTTON_FALLING_EDGE)
		{
			button->prevoiusState = BUTTON_FALLING_EDGE;
			button->currentState = BUTTON_PRESSED;
		}
		else if(button->prevoiusState == BUTTON_FALLING_EDGE && button->currentState == BUTTON_PRESSED)
		{
			button->prevoiusState = BUTTON_PRESSED;
			button->currentState = BUTTON_PRESSED;
		}
	}
	else
	{
		if (button->prevoiusState == BUTTON_FALLING_EDGE && button->currentState == BUTTON_PRESSED)
		{
			button->prevoiusState = BUTTON_PRESSED;
			button->currentState = BUTTON_RISING_EDGE;
		}
		else if(button->prevoiusState == BUTTON_PRESSED && button->currentState == BUTTON_PRESSED)
		{
			button->prevoiusState = BUTTON_PRESSED;
			button->currentState = BUTTON_RISING_EDGE;
		}
		else if(button->prevoiusState == BUTTON_PRESSED && button->currentState == BUTTON_RISING_EDGE)
		{
			button->prevoiusState = BUTTON_RISING_EDGE;
			button->currentState = BUTTON_RELEASED;
		}
		else
		button->prevoiusState = button->currentState = BUTTON_RELEASED;
	}
}

void InputUpdateStates(struct Buttons * systemButtons)
{
	HandleButtonInput(&systemButtons->ButtonUp		, read_key(INPUT_BUTTON_UP,		PINC));
	HandleButtonInput(&systemButtons->ButtonDown	, read_key(INPUT_BUTTON_DOWN,	PINC));
	HandleButtonInput(&systemButtons->ButtonLeft	, read_key(INPUT_BUTTON_LEFT,	PINC));
	HandleButtonInput(&systemButtons->ButtonRight	, read_key(INPUT_BUTTON_RIGHT,	PINC));
	HandleButtonInput(&systemButtons->ButtonStart	, read_key(INPUT_BUTTON_START,	PINB));
	HandleButtonInput(&systemButtons->ButtonSelect	, read_key(INPUT_BUTTON_SELECT,	PINB));
}

uint8_t read_key(uint8_t key, uint8_t pinRegister)
{
	if(!(key & pinRegister))
	{
		if(!(key & pinRegister))
			return 1;
	}
	return 0;
}