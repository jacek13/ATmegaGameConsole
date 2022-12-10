/*
 * gameLogic.c
 *
 * Created: 14.04.2022 19:54:12
 *  Author: Micha³ Jackowski
 */ 

#include "SnakeLogic.h"
#include "SnakeDisplay.h"
#include "SnakeBoardIO.h"

#define random() rand()

// Time base
volatile uint8_t numberOfTimer0Interupts;
volatile uint16_t numberOfMiliseconds;
volatile uint16_t numberOfSeconds;

inline const char * MapMenuSettingsValue(uint8_t val)
{
	return val ? menu_true : menu_false;
}

inline uint8_t MenuCheckForInteractiveButtons(MenuNavigation menuNavigation)
{
	return (MENU_NAVIGATE_LEFT <= menuNavigation) && (menuNavigation <= MENU_NAVIGATE_START);
}

uint8_t SnakeRun()
{
	int8_t menu_loop = TRUE;
	int8_t game_loop = TRUE;
	int8_t stop = FALSE;
	int8_t opposite_key = FALSE;
	int8_t x_previous, y_previous, collision_state, score;
	uint8_t displayMenu = TRUE;
	uint8_t startNextRound = FALSE;
	uint8_t timeBase = 0;
	int16_t speed;

	struct snake_element* head = NULL;
	struct snake_element* tail = NULL;
	struct food snake_food;
	struct SnakeBoard board;

	GAME_LOGIC previous_direction;
	GAME_LOGIC direction_copy;
	GAME_LOGIC opposite_direction;

	uint8_t elapsedTimeSum = 0;
	
	static char buffer[32] = {};
	//static char bufferForSettingsValuesFromProgmem[8] = {};
	//static char bufferForProgmem[32] = {};
	static Buttons buttons = {};
	//struct Menu* menu = MenuCreate(2);
	//SnakeDesignMenu(menu);

	//struct Menu* activeMenuHandler = menu;
	//struct MenuElement* localElement = NULL;
	
	// set Timer0
	TCNT0 = 0x00;
	TCCR0B = (1 << CS02) | (1 << CS00); // set 1024 prescaler
	
	// INIT
	score = 1;
	speed = 75;
	game_loop = TRUE;
	stop = FALSE;
	previous_direction = DIRECTION_UP;
	direction_copy = previous_direction;
	opposite_direction = DIRECTION_DOWN;
	board.borderX = 40;
	board.borderY = 28;
	board.blockHeight = 8;
	board.blockWidth = 8;
	board.isBorderEnabled = TRUE;
		
	snake_add_to_the_beginning(&head, &tail, board.borderX / 2, board.borderY / 2);
	generate_food(&board, &snake_food);
	
	Snake_clear_screen();
	if (board.isBorderEnabled) Snake_draw_borders(&board);
	
	while(menu_loop)
	{	
		if ((TIFR0 & 0x01) == 1) ++numberOfTimer0Interupts,  TIFR0 = 0x00;
		if (game_loop)
		{
			InputUpdateStates(&buttons);
			direction_copy = previous_direction;
			previous_direction = read_from_inputs(previous_direction, &buttons);
			if (previous_direction == opposite_direction) previous_direction = direction_copy;

			if (numberOfMiliseconds >= 1)
			{
				numberOfSeconds = numberOfMiliseconds = 0;

				head_buffer(tail, &x_previous, &y_previous);
				snake_update(&tail);
				controller(&previous_direction, &opposite_direction, direction_copy, &head, &game_loop, &menu_loop, &stop, &opposite_key, (int8_t*)&speed, &board);

				if (opposite_key)
				{
					opposite_key = FALSE;
					controller(&previous_direction, &opposite_direction, direction_copy, &head, &game_loop, &menu_loop, &stop, &opposite_key, (int8_t*)&speed, &board);
				}

				collision_state = check_collision(head, snake_food, &board, board.borderX, board.borderY);
				Snake_draw_scene(head, snake_food, &board, x_previous, y_previous);

				switch (collision_state)
				{
					case SNAKE_COLLISION_FOOD:
						Snake_draw_clear_food(&board, &snake_food);
						generate_food(&board, &snake_food);
						snake_add_at_the_end(&tail, x_previous, y_previous);
						score_update(&score);
						generate_sound(TRUE, FALSE);
						break;
					case SNAKE_COLLISION_WALL: game_loop = FALSE;
					case SNAKE_COLLISION_ITSELF: 
						displayMenu = game_loop = FALSE;
						Snake_draw_clear(&board);
						generate_sound(FALSE, TRUE);
						//menu->elements[0]->numeric.positiveValues = 0;
						break;
					default: break;
				}

				sprintf(buffer, "Score: %3d", score);
				Display_Draw_Text((DISPLAY_WIDTH / 2) - 16, DISPLAY_HEIGHT - 16, buffer, consolas_font, SNAKE_RGB565_FONT, 0x0000);
				handle_break_time(speed);
			}
		}
		else
		{
			InputUpdateStates(&buttons);
			
			if (!game_loop && menu_loop)
			{
				//Snake_draw_clear(&board);
				//generate_sound(FALSE, TRUE);
				Snake_draw_score(head, &board, score);
				if (buttons.ButtonStart.currentState == BUTTON_FALLING_EDGE) startNextRound = TRUE;
				if (buttons.ButtonSelect.currentState == BUTTON_FALLING_EDGE) displayMenu = TRUE;
			}

			if (!game_loop && !menu_loop)
			{
				Snake_clear_screen();
				snake_delete(&head);
				return 0;
			}

			// TODO MAKE INIT FUNCTION
			// INIT
			if (startNextRound)
			{
				startNextRound = FALSE;
				snake_delete(&head);

				score = 1;
				speed = 75;
				game_loop = TRUE;
				stop = FALSE;
				previous_direction = DIRECTION_UP;
				direction_copy = previous_direction;
				opposite_direction = DIRECTION_DOWN;

				snake_add_to_the_beginning(&head, &tail, board.borderX / 2, board.borderY / 2);
				generate_food(&board, &snake_food);

				Snake_draw_clear(&board);
				if (board.isBorderEnabled) Snake_draw_borders(&board);
			}
		}
		if (numberOfTimer0Interupts >= 12) ++numberOfMiliseconds, numberOfTimer0Interupts = 0;
		if (numberOfMiliseconds >= 5) ++numberOfSeconds, numberOfMiliseconds = 0;
		sprintf(buffer, "Time: %5d,%1d [s]", numberOfSeconds, numberOfMiliseconds << 1), Display_Draw_Text(0, 224, buffer, consolas_font, 0xD800, 0x0000);
	}
	return 0;
}

void head_buffer(struct snake_element * pTail, int8_t * X_previous, int8_t * Y_previous)
{
	*X_previous = pTail->x;
	*Y_previous = pTail->y;
}

void snake_add_to_the_beginning(struct snake_element ** pHead, struct snake_element ** pTail, int8_t X, int8_t Y)
{
	if(!*pHead)
	{
		*pTail = *pHead = (struct snake_element *) calloc(1, sizeof(struct snake_element));
		(*pHead)->x = X;
		(*pHead)->y = Y;
		(*pHead)->next_element = (*pHead)->previous_element = NULL;
	}
	else
	{
		struct snake_element * pNew = (struct snake_element *) calloc(1, sizeof(struct snake_element));
		pNew->previous_element = NULL;
		pNew->next_element = *pHead;
		pNew->next_element->previous_element = pNew;
		*pHead = pNew;
	}
}

void snake_delete(struct snake_element ** pHead)
{
	while(*pHead)
	{
		struct snake_element * pNew = *pHead;
		pNew = pNew->next_element;
		free(*pHead);
		*pHead = pNew;
	}
}

void snake_add_at_the_end(struct snake_element ** pTail, int8_t X, int8_t Y)
{
	struct snake_element * pNew = (struct snake_element *) calloc(1, sizeof(struct snake_element));
	pNew->next_element = NULL;
	pNew->previous_element = *pTail;
	pNew->x = X;
	pNew->y = Y;
	(*pTail)->next_element = pNew;
	*pTail = pNew;
}

void snake_update(struct snake_element ** pTail)
{
	struct snake_element * pNew = *pTail;
	struct snake_element * successor_from_back = *pTail;
	successor_from_back = successor_from_back->previous_element;
	while(successor_from_back)
	{
		pNew->x = successor_from_back->x;
		pNew->y = successor_from_back->y;
		pNew = pNew->previous_element;
		successor_from_back = successor_from_back->previous_element;
	}
}

void generate_food(struct SnakeBoard* board, struct food * _food)
{
	_food->x = board->isBorderEnabled ? (random() % (board->borderX - 2)) + 1 : random() % board->borderX;
	_food->y = board->isBorderEnabled ? (random() % (board->borderY - 2)) + 1 : random() % board->borderY;
}

int8_t check_collision(struct snake_element* pHead, struct food _food, struct SnakeBoard* board, int8_t board_max_x, int8_t board_max_y)
{
	if(pHead->x == _food.x && pHead->y == _food.y)
		return SNAKE_COLLISION_FOOD; // dodaj element do weza
	else if (board->isBorderEnabled && 
		(((pHead->x >= board->borderX - 1) || (pHead->x <= 0)) || 
		((pHead->y >= board->borderY - 1) || (pHead->y <= 0))))
	{
		return SNAKE_COLLISION_WALL;
	}
	else
	{
		struct snake_element * pNew = pHead;
		pNew = pNew->next_element;

		while(pNew)
		{
			if(pHead->x == pNew->x && pHead->y == pNew->y)
				return SNAKE_COLLISION_ITSELF;
			pNew = pNew->next_element;
		}
		return SNAKE_COLLISION_NONE;
	}
}

void score_update(int8_t * counter)
{
	(*counter)++;
}

int16_t change_speed(int16_t current_speed, int8_t increase)
{
	int16_t r = current_speed;
	if(current_speed >= 100 && current_speed <= 650)
	{
		if(increase) r -= 25;
		else r += 25;
	}
	else r = 75;
	return r;
}

void controller(GAME_LOGIC * direction, GAME_LOGIC * opposite_direction, GAME_LOGIC previous_direction, struct snake_element ** pHead, int8_t * game_loop, int8_t * menu_loop, int8_t * pause, int8_t * key_control, int8_t * speed, struct SnakeBoard* board)
{
	if(*direction == *opposite_direction)
	{
		*direction = previous_direction;
		*key_control = TRUE;
	}
	else
	{
		switch (*direction)
		{
			case DIRECTION_UP:
				(*pHead)->y--;
				*opposite_direction = DIRECTION_DOWN;
				if (!board->isBorderEnabled)
				{
					if ((*pHead)->y == -1)
						(*pHead)->y = board->borderY;
				}
				break;
			case DIRECTION_DOWN:
				(*pHead)->y++;
				*opposite_direction = DIRECTION_UP;
				if (!board->isBorderEnabled)
				{
					if ((*pHead)->y == board->borderY)
						(*pHead)->y = 0;
				}
				break;
			case DIRECTION_LEFT:
				(*pHead)->x--;
				*opposite_direction = DIRECTION_RIGHT;
				if (!board->isBorderEnabled)
				{
					if ((*pHead)->x == -1)
						(*pHead)->x = board->borderX;
				}
				break;
			case DIRECTION_RIGHT:
				(*pHead)->x++;
				*opposite_direction = DIRECTION_LEFT;
				if (!board->isBorderEnabled)
				{
					if ((*pHead)->x == board->borderX)
						(*pHead)->x = 0;
				}
				break;
			case EVENT_RESET:
				*game_loop = FALSE;
				//*pause = TRUE;
				break;
			case EVENT_EXIT:
				*game_loop = FALSE;
				*menu_loop = FALSE;
				break;
			case EVENT_SPEED_INCREASE:
				*direction = previous_direction;
				*key_control = TRUE;
				*speed = change_speed(*speed, TRUE);
				break;
			case EVENT_SPEED_REDUCE:
				*direction = previous_direction;
				*key_control = TRUE;
				*speed = change_speed(*speed, FALSE);
			default:
				break;
		}
	}
}

void handle_break_time(int16_t _speed)
{
	while(_speed > 0)
	{
		_speed -= 25;
		//_delay_ms(25);
	}
}

// Not used in current version
void SnakeDesignMenu(struct Menu* menu)
{
	MenuStatusCode status = MENU_UNKNOWN;

	// Main Menu
	status = MenuAVRSpecificAddElementAt(menu, 0, MENU_BOOL_SELECTION, &snake_menu_play);
	status = MenuAVRSpecificAddElementAt(menu, 1, MENU_SUBMENU, &snake_menu_settings);
	status = MenuSetElementNumericalInitialValueAt(menu, 0, 0);

	// Submenu Settings
	status = MenuAddSubMenuAt(menu, 1, 5);
	status = MenuAVRSpecificAddElementAt(menu->elements[1]->subMenu, 0, MENU_BOOL_SELECTION, &snake_settings_sound);
	status = MenuAVRSpecificAddElementAt(menu->elements[1]->subMenu, 1, MENU_BOOL_SELECTION, &snake_settings_borders);
	status = MenuAVRSpecificAddElementAt(menu->elements[1]->subMenu, 2, MENU_INCREASE_DECREASE_VALUE, &snake_settings_map_limit_x);
	status = MenuAVRSpecificAddElementAt(menu->elements[1]->subMenu, 3, MENU_INCREASE_DECREASE_VALUE, &snake_settings_map_limit_y);
	status = MenuAVRSpecificAddElementAt(menu->elements[1]->subMenu, 4, MENU_EXIT, &snake_settings_return);
	status = MenuSetElementNumericalInitialValueAt(menu->elements[1]->subMenu, 0, 0);
	status = MenuSetElementNumericalInitialValueAt(menu->elements[1]->subMenu, 1, 1);
	status = MenuUpdateElementRangesAt(menu->elements[1]->subMenu, 2, 10, 40, 40);
	status = MenuUpdateElementRangesAt(menu->elements[1]->subMenu, 3, 10, 30, 30);
}