/*
 * display.h
 *
 * Created: 14.04.2022 19:36:08
 *  Author: Micha³ Jackowski
 */ 

#ifndef SNAKE_DISPLAY_H_
#define SNAKE_DISPLAY_H_

#include <avr/io.h>
#include <stdio.h>

#include "SnakeStructures.h"
#include "SnakeData.h"
#include "../../LcdDisplay/display.h"
#include "../../Data/fonts.h"

#define SNAKE_RGB565_HEAD 0x26C0
#define SNAKE_RGB565_BODY 0x1420
#define SNAKE_RGB565_FOOD 0xC800
#define SNAKE_RGB565_WALL 0x2932
#define SNAKE_RGB565_FONT 0xEFE0

void Snake_draw_borders(struct SnakeBoard * board);

void Snake_clear_screen();

void Snake_draw_clear(struct SnakeBoard* board);

void Snake_draw_clear_food(struct SnakeBoard* board, struct food * foodData);

void Snake_draw_scene(struct snake_element * pHead, struct food _food, struct SnakeBoard * board, int8_t prevoiusX, int8_t prevoiusY);

void Snake_draw_score(struct snake_element* pHead, struct SnakeBoard* board, int8_t score);

#endif /* SNAKE_DISPLAY_H_ */