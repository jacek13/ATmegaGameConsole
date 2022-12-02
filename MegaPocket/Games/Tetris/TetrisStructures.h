#ifndef TETRISSTRUCTURES_H_
#define TETRISSTRUCTURES_H_

#define CubeWidth 8
#define CubeHight 8

typedef enum
{
	Type_I = 0,
	Type_I_Rotated_90,
	Type_T,
	Type_T_Rotated_90,
	Type_T_Rotated_180,
	Type_T_Rotated_270,
	Type_O,
	Type_L,
	Type_L_Rotated_90,
	Type_L_Rotated_180,
	Type_L_Rotated_270,
	Type_J,
	Type_J_Rotated_90,
	Type_J_Rotated_180,
	Type_J_Rotated_270,
	Type_S,
	Type_S_Rotated_90,
	Type_Z,
	Type_Z_Rotated_90,
	NumberOfTetrominos
} Tetromino;

typedef enum
{
	COLLISION_NONE = 0,
	COLLISION_WALL,
	COLLISION_FLOOR,
	COLLISION_TETROMINO,
	COLLISION_TETROMINO_LEFT,
	COLLISION_TETROMINO_RIGHT
} collisionType;

typedef enum
{
	BUTTON_NONE = 0,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_ROTATE,
	BUTTON_RESET
} ButtonType;

struct Tile
{
	unsigned int x, y;
	collisionType colision;
	Tetromino Type;
};

struct Board
{
	char** area;
	unsigned int rows, columns;
	long score;
};

#endif