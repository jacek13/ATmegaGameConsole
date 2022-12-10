/*
 * boardIO.c
 *
 * Created: 14.04.2022 20:01:04
 *  Author: Micha³ Jackowski
 */

#include <stdlib.h>

#include "SnakeBoardIO.h"
#include "SnakeStructures.h"

GAME_LOGIC read_from_inputs(GAME_LOGIC previous_direction, Buttons * buttons)
{
	int8_t reset = (buttons->ButtonSelect.currentState == BUTTON_FALLING_EDGE);
	int8_t exit  = (buttons->ButtonStart.currentState == BUTTON_FALLING_EDGE);
	int8_t up	 = (buttons->ButtonUp.currentState == BUTTON_FALLING_EDGE);
	int8_t down	 = (buttons->ButtonDown.currentState == BUTTON_FALLING_EDGE);
	int8_t left	 = (buttons->ButtonLeft.currentState == BUTTON_FALLING_EDGE);
	int8_t right = (buttons->ButtonRight.currentState == BUTTON_FALLING_EDGE);

	if (exit) return EVENT_EXIT;
	if (reset && up) return EVENT_SPEED_INCREASE;
	if (reset && down) return EVENT_SPEED_REDUCE;
	if (reset) return EVENT_RESET;
	if (right) return DIRECTION_RIGHT;
	if (left) return DIRECTION_LEFT;
	if (down) return DIRECTION_DOWN;
	if (up) return DIRECTION_UP;
	return previous_direction;
}

void generate_sound(int8_t _scored, int8_t _game_over)
{
	// TODO Use system sound generation
}