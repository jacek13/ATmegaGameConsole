#include <stdio.h>
#include <stdlib.h>

#include "Tetris.h"
#include "TetrisData.h"

//#define random() rand()

// Time base
volatile uint8_t numberOfTimer0Interupts;
volatile uint8_t tetrisGameLoop;
volatile uint16_t numberOfMiliseconds;
volatile uint16_t numberOfSeconds;

// Input
volatile uint8_t ButtonUp;
volatile uint8_t ButtonDown;
volatile uint8_t ButtonLeft;
volatile uint8_t ButtonRight;
volatile uint8_t ButtonStart;
volatile uint8_t ButtonSelect;

inline Tetromino generateTile() { return (Tetromino)(random() % NumberOfTetrominos); }

inline int isTetrominoType(char type)
{
	unsigned int i = 0;
	while (TetrominosTypes[i] != '\0') if (type == TetrominosTypes[i++]) return 1;
	return 0;
}

void TetrisRun()
{
	tetrisGameLoop = 1;
	struct Board board;
	struct Tile currentTetromino;
	struct Tile currentTetrominoCopy;
	//float elapsedTimeSum = 0.0f;
	TetrisInit(&board, &currentTetromino);
	TetrisDrawMap(/*engine,*/ &board);
	TetrisDrawScore(board.score);
	
	static char buffer[32] = {};
		
	// set Timer0
	TCNT0 = 0x00;
	TCCR0B = (1 << CS02) | (1 << CS00); // set 1024 prescaler
	
	while(tetrisGameLoop) 
	{
		if ((TIFR0 & 0x01) == 1) ++numberOfTimer0Interupts,  TIFR0 = 0x00;
		TetrisLoop(&board, &currentTetromino, &currentTetrominoCopy, &numberOfMiliseconds);
		if (numberOfTimer0Interupts >= 12) ++numberOfMiliseconds, numberOfTimer0Interupts = 0;
		if (numberOfMiliseconds >= 5) ++numberOfSeconds, numberOfMiliseconds = 0;
		sprintf(buffer, "Time: %5d,%1d [s]", numberOfSeconds, numberOfMiliseconds << 1), Display_Draw_Text(0, 224, buffer, consolas_font, 0xD800, 0x0000);
	}
}

void TetrisLoop(/*olc::PixelGameEngine* engine, */ struct Board* board, struct Tile* tetromino, struct Tile* bufferTetromino, uint8_t * elapsedTimeSum)
{
	uint16_t bufferScore = board->score;
	collisionType collision = COLLISION_NONE;
	ButtonType input = BUTTON_NONE;
	bufferTetromino->x = tetromino->x;
	bufferTetromino->y = tetromino->y;
	bufferTetromino->colision = tetromino->colision;
	bufferTetromino->Type = tetromino->Type;

	if ((input = TetrisHandleInput(/*engine,*/ tetromino, board->rows, board->columns)) == BUTTON_ROTATE)
	{
		tetromino->Type = TetrisRotateTetromino(tetromino->Type);
		if (TetrisCheckForCollision(board, tetromino)) tetromino->Type = bufferTetromino->Type;
	}
	if (input == BUTTON_RESET) TetrisHandleGameOver(board, tetromino);
	collision = TetrisHandleCollision(board, tetromino, input);
	TetrisUpdateGameLogic(board, tetromino, elapsedTimeSum);

	if (collision = TetrisHandleCollision(board, tetromino, BUTTON_DOWN))
	{
		TetrisMapCurrentTileToArea(board, tetromino);
		TetrisMakeNewTile(tetromino);
		if (TetrisCheckForCollision(board, tetromino)) TetrisHandleGameOver(board, tetromino);
		TetrisUpdateGameLogic(board, tetromino, elapsedTimeSum);
	}

	//TetrisDrawMap(/*engine,*/ board);
	//sprintf_s(buffer, "Elapsed: %1.3f\tCurrent tetromino: %d\tFull row: %d\n", elapsedTimeSum += GetElapsedTime(), tetromino->Type, TetrisFindIndexOfFilledRow(&board));
	//printf(buffer);
	if ((tetromino->x != bufferTetromino->x) || (tetromino->y != bufferTetromino->y) || (tetromino->Type != bufferTetromino->Type)) TetrisDrawCurrentTile(/*engine,*/ tetromino, bufferTetromino, collision);
	
	if (board->score != bufferScore) TetrisDrawScore(board->score);
	//bufferString.clear();
	//bufferString += "Score: ";
	//bufferString += std::to_string(board.score);
	//DrawString(0, 226, bufferString);

}

void TetrisInit(struct Board* board, struct Tile* tetromino)
{
	TetrisMakeNewBoard(board);
	TetrisCleanBoard(board);
	TetrisMakeNewTile(tetromino);
}

void TetrisMakeNewBoard(struct Board* board)
{
	board->columns = 10;
	board->rows = 20;
	board->area = (char**)malloc((board->rows + 1) * sizeof(char*));
	board->score = 0;

	for (int i = 0; i <= (board->rows + 1); i++)
		board->area[i] = (char*)malloc((board->columns + 3) * sizeof(char));
}

void TetrisCleanBoard(struct Board* board)
{
	for (unsigned int i = 0; i < board->rows + 1; i++)
		for (unsigned int j = 0; j <= (board->columns + 1); j++)
			board->area[i][j] = map[i][j];
	board->score = 0;
}

void TetrisMakeNewTile(struct Tile* tetromino)
{
	tetromino->Type = generateTile();
	tetromino->x = 1;
	tetromino->y = 1;
}

void TetrisFreeMemory(struct Board* board)
{
	for (int i = 0; i <= (board->rows + 1); i++)
		free(board->area[i]);
	free(board->area);
}

ButtonType TetrisHandleInput(/*olc::PixelGameEngine* engine,*/ struct Tile * tetromino, unsigned int maxRows, unsigned int maxColumns)
{
	ButtonType input = BUTTON_NONE;
	#ifdef __cplusplus
	/* Check Pin State */ if (engine->GetKey(olc::UP).bPressed && tetromino->y >= 1) tetromino->y--, input = BUTTON_UP;
	/* Check Pin State */ if (engine->GetKey(olc::DOWN).bPressed && tetromino->y < maxRows) tetromino->y++, input = BUTTON_DOWN;
	/* Check Pin State */ if (engine->GetKey(olc::LEFT).bPressed && tetromino->x >= 1) tetromino->x--, input = BUTTON_LEFT;
	/* Check Pin State */ if (engine->GetKey(olc::RIGHT).bPressed && tetromino->x < maxColumns) tetromino->x++, input = BUTTON_RIGHT;
	/* Check Pin State */ if (engine->GetKey(olc::SPACE).bPressed) input = BUTTON_ROTATE;
	//if (engine->GetKey(olc::G).bPressed) makeNewTile();
	//if (engine->GetKey(olc::D).bPressed) drawCurrentTile();
	#else
	/* Check Pin State */ if (read_key(INPUT_BUTTON_UP, PINC) && tetromino->y >= 1) ButtonSelect = 0, tetromino->y--, input = BUTTON_UP;
	/* Check Pin State */ if (read_key(INPUT_BUTTON_DOWN, PINC) && tetromino->y < maxRows) ButtonSelect = 0, tetromino->y++, input = BUTTON_DOWN;
	/* Check Pin State */ if (read_key(INPUT_BUTTON_LEFT, PINC) && tetromino->x >= 1) ButtonSelect = 0, tetromino->x--, input = BUTTON_LEFT;
	/* Check Pin State */ if (read_key(INPUT_BUTTON_RIGHT, PINC)  && tetromino->x < maxColumns)ButtonSelect = 0, tetromino->x++, input = BUTTON_RIGHT;
	/* Check Pin State */ if (read_key(INPUT_BUTTON_START, PINB)) input = BUTTON_RESET;
	/* Check Pin State */ if (read_key(INPUT_BUTTON_SELECT, PINB) && !ButtonSelect) ButtonSelect = 1, input = BUTTON_ROTATE;
	else if (!read_key(INPUT_BUTTON_SELECT, PINC) && ButtonSelect) ButtonSelect = 0;
	#endif
	return input;
}

Tetromino TetrisRotateTetromino(Tetromino tetromino)
{
	switch (tetromino)
	{
		case Type_I: tetromino = Type_I_Rotated_90; break;
		case Type_I_Rotated_90: tetromino = Type_I; break;
		case Type_T: tetromino = Type_T_Rotated_90; break;
		case Type_T_Rotated_90: tetromino = Type_T_Rotated_180; break;
		case Type_T_Rotated_180: tetromino = Type_T_Rotated_270; break;
		case Type_T_Rotated_270: tetromino = Type_T; break;
		case Type_O: break;
		case Type_L: tetromino = Type_L_Rotated_90; break;
		case Type_L_Rotated_90: tetromino = Type_L_Rotated_180; break;
		case Type_L_Rotated_180: tetromino = Type_L_Rotated_270; break;
		case Type_L_Rotated_270: tetromino = Type_L; break;
		case Type_J: tetromino = Type_J_Rotated_90; break;
		case Type_J_Rotated_90: tetromino = Type_J_Rotated_180; break;
		case Type_J_Rotated_180: tetromino = Type_J_Rotated_270; break;
		case Type_J_Rotated_270: tetromino = Type_J; break;
		case Type_S: tetromino = Type_S_Rotated_90; break;
		case Type_S_Rotated_90: tetromino = Type_S; break;
		case Type_Z: tetromino = Type_Z_Rotated_90; break;
		case Type_Z_Rotated_90: tetromino = Type_Z; break;
		default: break;
	}
	return tetromino;
}

collisionType TetrisCheckForCollision(struct Board* board, struct Tile* tetromino)
{
	for (unsigned row = 0; row < 4; row++)
		for (unsigned column = 0; column < 4; column++)
			if (Tetrominos[tetromino->Type][((row * 4) + column)] == '#' ||
				isTetrominoType(Tetrominos[tetromino->Type][((row * 4) + column)]))
			{
				switch (board->area[tetromino->y + row][tetromino->x + column])
				{
					case 'W': return COLLISION_WALL; break;
					case 'F': return COLLISION_FLOOR; break;
					case '#': return COLLISION_TETROMINO; break;
					case 'I': return COLLISION_TETROMINO; break;
					case 'T': return COLLISION_TETROMINO; break;
					case 'O': return COLLISION_TETROMINO; break;
					case 'L': return COLLISION_TETROMINO; break;
					case 'J': return COLLISION_TETROMINO; break;
					case 'S': return COLLISION_TETROMINO; break;
					case 'Z': return COLLISION_TETROMINO; break;
					default: break;
				}
			}
	return COLLISION_NONE;
}

int TetrisHandleCollision(struct Board* board, struct Tile* tetromino, ButtonType input)
{
	switch (TetrisCheckForCollision(board, tetromino))
	{
	case COLLISION_NONE: break;
	case COLLISION_WALL:
		if (input == BUTTON_LEFT) tetromino->x++;
		if (input == BUTTON_RIGHT) tetromino->x--;
		break;
	case COLLISION_FLOOR:
		tetromino->y--;
		return 1;
	case COLLISION_TETROMINO:
		if (input == BUTTON_LEFT) tetromino->x++;
		if (input == BUTTON_RIGHT) tetromino->x--;
		if (input == BUTTON_DOWN)
		{
			tetromino->y--;
			return 1;
		}
		break;
	default:
		break;
	}
	return 0;
}

void TetrisUpdateGameLogic(struct Board* board, struct Tile* tetromino, uint8_t * elapsedTimeSum)
{
	 //TODO base time not working
	 if (*elapsedTimeSum >= 2)
	 {
		tetromino->y++;
		*elapsedTimeSum = 0;
	}

	int indexOfRowToClear = 0;
	if (indexOfRowToClear = TetrisFindIndexOfFilledRow(board))
	{
		board->score += TetrisUpdateBoard(board, indexOfRowToClear);
		TetrisDrawMap(board);
	}
}

int TetrisFindIndexOfFilledRow(struct Board* board)
{
	int numberOfTilesInSingleRow = 0;
	for (unsigned int row = 0; row < board->rows; row++)
	{
		for (unsigned int column = 1; column <= board->columns; column++)
			if (board->area[row][column] != ' ') ++numberOfTilesInSingleRow;
		if (numberOfTilesInSingleRow == board->columns) return row;
		numberOfTilesInSingleRow = 0;
	}
	return 0;
}

int TetrisUpdateBoard(struct Board* board, int indexOfRowToBeRemoved)
{
	int numberOfMovedTetrominos = 0;
	if (indexOfRowToBeRemoved > 0)
		for (unsigned int row = indexOfRowToBeRemoved; row > 0; row--)
			for (unsigned int column = 1; column <= board->columns; column++)
				if ((board->area[row][column] = board->area[row - 1][column]) != ' ') ++numberOfMovedTetrominos;
	return numberOfMovedTetrominos;
}

void TetrisMapCurrentTileToArea(struct Board* board, struct Tile* tetromino)
{
	for (unsigned i = 0; i < 4; i++)
		for (unsigned j = 0; j < 4; j++)
		{
			if ((isTetrominoType(Tetrominos[tetromino->Type][((i * 4) + j)]))
				&& (tetromino->y + i) < board->rows
				&& (tetromino->x + j) > 0
				&& (tetromino->x + j) <= board->columns)
				board->area[tetromino->y + i][tetromino->x + j] = Tetrominos[tetromino->Type][((i * 4) + j)];
		}
}

// TODO optimize (draw backgound only at the beggining)
void TetrisDrawMap(/*olc::PixelGameEngine* engine, */ struct Board* board)
{
	for (unsigned int i = 0; i < board->rows + 1; i++)
		for (unsigned int j = 0; j <= (board->columns + 1); j++)
		{
			switch (board->area[i][j])
			{
				#ifdef __cplusplus
				case 'W': engine->FillRect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, olc::DARK_RED); break;
				case 'F': engine->FillRect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, olc::DARK_RED); break;
				case ' ': engine->FillRect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, olc::BLACK); break;
				case '#': engine->FillRect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, olc::BLUE); break;
				case 'I': engine->FillRect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, olc::WHITE); break;
				case 'T': engine->FillRect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, olc::MAGENTA); break;
				case 'O': engine->FillRect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, olc::GREEN); break;
				case 'L': engine->FillRect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, olc::GREY); break;
				case 'J': engine->FillRect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, olc::YELLOW); break;
				case 'S': engine->FillRect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, olc::BLUE); break;
				case 'Z': engine->FillRect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, olc::VERY_DARK_YELLOW); break;
				#else
				case 'W': Display_Draw_Fill_Rect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, 0xD000); break;
				case 'F': Display_Draw_Fill_Rect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, 0xD000); break;
				case ' ': Display_Draw_Fill_Rect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, 0x0000); break;
				case '#': Display_Draw_Fill_Rect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, 0x05BF); break;
				case 'I': Display_Draw_Fill_Rect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, 0xFFFF); break;
				case 'T': Display_Draw_Fill_Rect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, 0xF29D); break;
				case 'O': Display_Draw_Fill_Rect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, 0x3F0A); break;
				case 'L': Display_Draw_Fill_Rect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, 0x9CD3); break;
				case 'J': Display_Draw_Fill_Rect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, 0xEFE0); break;
				case 'S': Display_Draw_Fill_Rect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, 0x05BF); break;
				case 'Z': Display_Draw_Fill_Rect(j * CubeWidth, i * CubeHight, CubeWidth, CubeHight, 0x8CE0); break;
				#endif
				default: break;
			}
		}
}

// TODO clear bacground by getting x y info from buffer tetromino
void TetrisDrawCurrentTile(/*olc::PixelGameEngine* engine, */ struct Tile* tetromino, struct Tile* bufferTetromino, collisionType collision)
{
	#ifdef __cplusplus
	olc::Pixel color = olc::WHITE;
	for (unsigned row = 0; row < 4; row++)
		for (unsigned column = 0; column < 4; column++)
		{
			switch (tetromino->Type)
			{
				case Type_I:
				case Type_I_Rotated_90: color = olc::WHITE;
					break;
				case Type_T:
				case Type_T_Rotated_90:
				case Type_T_Rotated_180:
				case Type_T_Rotated_270: color = olc::MAGENTA;
					break;
				case Type_O: color = olc::GREEN;
					break;
				case Type_L:
				case Type_L_Rotated_90:
				case Type_L_Rotated_180:
				case Type_L_Rotated_270: color = olc::GREY;
					break;
				case Type_J:
				case Type_J_Rotated_90:
				case Type_J_Rotated_180:
				case Type_J_Rotated_270: color = olc::YELLOW;
					break;
				case Type_S:
				case Type_S_Rotated_90: color = olc::BLUE;
					break;
				case Type_Z:
				case Type_Z_Rotated_90: color = olc::VERY_DARK_YELLOW;
					break;
				default: color = olc::WHITE;
					break;
			}
			if (isTetrominoType(Tetrominos[tetromino->Type][((row * 4) + column)]))
				engine->FillRect((tetromino->x + column) * CubeWidth, (tetromino->y + row) * CubeHight, CubeWidth, CubeHight, color);
		}
	#else
	
	// Clear previus GRAM area
	if (!collision)
		for (unsigned row = 0; row < 4; row++)
			for (unsigned column = 0; column < 4; column++)
				if (isTetrominoType(Tetrominos[bufferTetromino->Type][((row * 4) + column)]))
					if ((bufferTetromino->x + column) > 0 && (bufferTetromino->x + column) <= 10 && (bufferTetromino->y + row) <= 19)
						Display_Draw_Fill_Rect((bufferTetromino->x + column) * CubeWidth, (bufferTetromino->y + row) * CubeHight, CubeWidth, CubeHight, 0x0000);
	
	uint16_t color = 0xFFFF;
	for (unsigned row = 0; row < 4; row++)
		for (unsigned column = 0; column < 4; column++)
		{
			switch (tetromino->Type)
			{
			case Type_I:
			case Type_I_Rotated_90: color = 0xFFFF;
				break;
			case Type_T:
			case Type_T_Rotated_90:
			case Type_T_Rotated_180:
			case Type_T_Rotated_270: color = 0xF29D;
				break;
			case Type_O: color = 0x3F0A;
				break;
			case Type_L:
			case Type_L_Rotated_90:
			case Type_L_Rotated_180:
			case Type_L_Rotated_270: color = 0x9CD3;
				break;
			case Type_J:
			case Type_J_Rotated_90:
			case Type_J_Rotated_180:
			case Type_J_Rotated_270: color = 0xEFE0;
				break;
			case Type_S:
			case Type_S_Rotated_90: color = 0x05BF;
				break;
			case Type_Z:
			case Type_Z_Rotated_90: color = 0x8CE0;
				break;
			default: color = 0xFFFF;
				break;
			}
			if (isTetrominoType(Tetrominos[tetromino->Type][((row * 4) + column)]) && tetromino->x < 10)
				Display_Draw_Fill_Rect((tetromino->x + column) * CubeWidth, (tetromino->y + row) * CubeHight, CubeWidth, CubeHight, color);
		}
		#endif
}

void TetrisDrawScore(uint16_t score)
{
	static char buffer[32] = {};
	sprintf(buffer, "Score: %5d    ", score), Display_Draw_Text(0, 208, buffer, consolas_font, 0xEFE0, 0x0000);
}

void TetrisHandleGameOver(struct Board* board, struct Tile* tetromino)
{
	static char buffer[32] = {};
	Display_Draw_Text_From_Progmem(0, 192, PSTR("Game Over!"), consolas_font, 0xD800, 0x0000);
	sprintf(buffer, "Final score: %5d", board->score), Display_Draw_Text(0, 208, buffer, consolas_font, 0xEFE0, 0x0000);
	for(uint8_t n = 0; n < 64; n++)
		for(uint16_t i = 0; i < 50000; i++) asm("nop"); // delay
	Display_Clear_Screen(0x0000);
	TetrisCleanBoard(board);
	TetrisDrawMap(/*engine,*/ board);
	TetrisMakeNewTile(tetromino);
	TetrisDrawScore(board->score);
}