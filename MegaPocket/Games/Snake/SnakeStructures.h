/*
 * structures.h
 *
 * Created: 14.04.2022 19:26:02
 *  Author: Micha³ Jackowski
 */ 

#ifndef SNAKE_STRUCTURES_H_
#define SNAKE_STRUCTURES_H_

#include <stdint.h>

#define TRUE 1
#define FALSE 0

/** Snake structure (bidirectional list) */
typedef struct snake_element
{
	int8_t x;
	int8_t y;
	struct snake_element * previous_element;
	struct snake_element * next_element;
}_snake_element;

typedef struct SnakeBoard
{
	uint8_t borderX;
	uint8_t borderY;
	uint8_t blockWidth;
	uint8_t blockHeight;
	uint8_t isBorderEnabled;
} SnakeBoard;

/** Food for the snake, snake likes to eat 2 bytes :D */
struct food
{
	int8_t x;
	int8_t y;
};

/** enumeration for program logic/events */
typedef enum
{
	DIRECTION_UP = 1,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	EVENT_EXIT,
	EVENT_RESET,
	EVENT_PAUSE,
	EVENT_SPEED_INCREASE,
	EVENT_SPEED_REDUCE
} GAME_LOGIC;

typedef enum
{
	SNAKE_COLLISION_NONE = 0,
	SNAKE_COLLISION_WALL,
	SNAKE_COLLISION_FOOD,
	SNAKE_COLLISION_ITSELF
} GAME_COLLISION_TYPE;

#endif /* SNAKE_STRUCTURES_H_ */