/*
 * display.c
 *
 * Created: 14.04.2022 19:37:36
 *  Author: Micha³ Jackowski
 */ 

#include "SnakeDisplay.h"

void Snake_draw_borders(struct SnakeBoard* board)
{
	if (board->isBorderEnabled)
	{
		for (uint8_t x = 0; x < board->borderX; x++)
		{
			Display_Draw_Fill_Rect((x * board->blockWidth), 0, board->blockWidth, board->blockHeight, SNAKE_RGB565_WALL);
			Display_Draw_Fill_Rect((x * board->blockWidth), (board->borderY - 1) * board->blockHeight, board->blockWidth, board->blockHeight, SNAKE_RGB565_WALL);
		}

		for (uint8_t y = 0; y < board->borderY; y++)
		{
			Display_Draw_Fill_Rect(0, (y * board->blockHeight), board->blockWidth, board->blockHeight, SNAKE_RGB565_WALL);
			Display_Draw_Fill_Rect(((board->borderX - 1) * board->blockWidth), y * board->blockHeight, board->blockWidth, board->blockHeight, SNAKE_RGB565_WALL);
		}
	}
}

void Snake_clear_screen()
{
	Display_Clear_Screen(0x0000);
}

void Snake_draw_clear(struct SnakeBoard* board)
{
	for (uint8_t y = 0; y < board->borderY; y++)
	{
		for (uint8_t x = 0; x < board->borderX; x++)
			Display_Draw_Fill_Rect((x * board->blockWidth), (y * board->blockHeight), board->blockWidth, board->blockHeight, 0x0000);
	}
}

// Potrzebne poniewa¿ kompilator ma b³¹d i Ÿle rozdziela rejestry przy dostawaniu siê do pamiêci planszy
// Treœæ b³êdu kompilatora: unable to find a register to spill in class 'SIMPLE_LD_REGS'
// Najprawdopodobniej kompilator nie potrafi rozdzieliæ odpowiednio rejestrów dla operacji mno¿enia wskaŸników do wartoœci uint16_t i uint8_t
static uint16_t Local_Mul(uint16_t a, uint8_t b) 
{
	return a * b;
}

void Snake_draw_clear_food(struct SnakeBoard* board, struct food* foodData)
{
	Display_Draw_Fill_Rect(Local_Mul(foodData->x, board->blockWidth), (foodData->y * board->blockHeight), board->blockWidth, board->blockHeight, SNAKE_RGB565_HEAD);
}

void Snake_draw_scene(struct snake_element * pHead, struct food _food, struct SnakeBoard* board, int8_t prevoiusX, int8_t prevoiusY/*olc::PixelGameEngine* engine*/)
{
	struct snake_element * pNew = pHead;

	while(pNew)
	{
		if (pHead->x == pNew->x && pHead->y == pNew->y) Display_Draw_Fill_Rect(Local_Mul(pHead->x, board->blockWidth), pHead->y * board->blockHeight, board->blockWidth, board->blockHeight, SNAKE_RGB565_HEAD);
		else Display_Draw_Fill_Rect(Local_Mul(pNew->x, board->blockWidth), pNew->y * board->blockHeight, board->blockWidth, board->blockHeight, SNAKE_RGB565_BODY);
		pNew = pNew->next_element;
	}

	Display_Draw_Fill_Rect(Local_Mul(_food.x, board->blockWidth), _food.y * board->blockHeight, board->blockWidth, board->blockHeight, SNAKE_RGB565_FOOD);
	Display_Draw_Fill_Rect(Local_Mul(prevoiusX, board->blockWidth), prevoiusY * board->blockHeight, board->blockWidth, board->blockHeight, 0x0000);
}
//
void Snake_draw_score(struct snake_element* pHead, struct SnakeBoard* board, int8_t score/*olc::PixelGameEngine* engine*/)
{
	static char buffer[32] = {};

	sprintf(buffer, "Score: %4d", score), Display_Draw_Text(0, 0, buffer, consolas_font, SNAKE_RGB565_FONT, 0x0000);
	Display_Draw_Text_From_Progmem(0, 16, PSTR("Final pattern:"), consolas_font, SNAKE_RGB565_FONT, 0x0000);

	struct snake_element* pNew = pHead;
	uint8_t scale = 1;

	while (pNew)
	{
		if (pHead->x == pNew->x && pHead->y == pNew->y) Display_Draw_Fill_Rect(Local_Mul(pHead->x, board->blockWidth >> scale), (pNew->y + 8) * (board->blockHeight >> scale), board->blockWidth >> scale, board->blockHeight >> scale, SNAKE_RGB565_HEAD);
		else Display_Draw_Fill_Rect(Local_Mul(pNew->x, (board->blockWidth >> scale)), (pNew->y + 8) * (board->blockHeight >> scale), board->blockWidth >> scale, board->blockHeight >> scale, SNAKE_RGB565_BODY);
		pNew = pNew->next_element;
	}
}