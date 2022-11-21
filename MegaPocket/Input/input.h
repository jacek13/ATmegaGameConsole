/*
 * input.h
 *
 * Created: 07.11.2022 19:32:04
 *  Author: Michal
 */ 


#ifndef INPUT_H_
#define INPUT_H_

#include <avr/io.h>

#define INPUT_BUTTON_UP		(1 << PC0)
#define INPUT_BUTTON_DOWN	(1 << PC1)
#define INPUT_BUTTON_LEFT	(1 << PC2)
#define INPUT_BUTTON_RIGHT	(1 << PC3)
#define INPUT_BUTTON_START	(1 << PB0)
#define INPUT_BUTTON_SELECT	(1 << PB2)

//void input_registers_init();

uint8_t read_key(uint8_t key, uint8_t pinRegister);

#endif /* INPUT_H_ */