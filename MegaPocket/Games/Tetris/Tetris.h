#ifndef TETRIS_H_
#define TETRIS_H_

#include <stdio.h>

#include "TetrisStructures.h"
#ifdef __cplusplus
#include "olcPixelGameEngine.h"
#else
#include "../../LcdDisplay/display.h"
#include "../../Data/fonts.h"
#include "../../Input/input.h"
#endif

uint8_t TetrisRun();

void TetrisLoop(/*olc::PixelGameEngine* engine, */ struct Board* board, struct Tile* tetromino, struct Tile* bufferTetromino, uint8_t* elapsedTimeSum);

void TetrisInit(struct Board* board, struct Tile* tetromino);

void TetrisMakeNewBoard(struct Board* board);

void TetrisCleanBoard(struct Board* board);

void TetrisMakeNewTile(struct Tile* tetromino);

void TetrisFreeMemory(struct Board* board);

void TetrisUpdateGameLogic(struct Board* board, struct Tile* tetromino, uint8_t* elapsedTimeSum);

void TetrisMapCurrentTileToArea(struct Board* board, struct Tile* tetromino);

void TetrisDrawMap(/*olc::PixelGameEngine* engine,*/ struct Board* board);

void TetrisDrawCurrentTile(/*olc::PixelGameEngine* engine,*/ struct Tile* tetromino, struct Tile* bufferTetromino, collisionType collision);

void TetrisDrawScore(uint16_t score);

void TetrisHandleGameOver(struct Board* board, struct Tile* tetromino);

int isTetrominoType(char type);

int TetrisHandleCollision(struct Board* board, struct Tile* tetromino, ButtonType input);

int TetrisFindIndexOfFilledRow(struct Board* board);

int TetrisUpdateBoard(struct Board* board, int indexOfRowToBeRemoved);

Tetromino TetrisRotateTetromino(Tetromino tetromino);

Tetromino generateTile();

ButtonType TetrisHandleInput(/*olc::PixelGameEngine* engine,*/ struct Tile* tetromino, unsigned int maxRows, unsigned int maxColumns);

collisionType TetrisCheckForCollision(struct Board* board, struct Tile* tetromino);

#endif