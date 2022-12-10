/*
 * boardIO.h
 *
 * Created: 14.04.2022 20:01:20
 *  Author: Micha³ Jackowski
 */ 

#ifndef BOARDIO_H_
#define BOARDIO_H_

#include "../../Input/input.h"
#include "SnakeStructures.h"

GAME_LOGIC read_from_inputs(GAME_LOGIC previous_direction, Buttons * buttons);

void generate_sound(int8_t _scored, int8_t _game_over);

#endif /* BOARDIO_H_ */