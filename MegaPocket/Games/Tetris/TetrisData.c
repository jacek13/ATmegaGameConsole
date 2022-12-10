#include "TetrisData.h"

const char mapRow0[] PROGMEM	= "W          W";
const char mapRow1[] PROGMEM	= "W          W";
const char mapRow2[] PROGMEM	= "W          W";
const char mapRow3[] PROGMEM	= "W          W";
const char mapRow4[] PROGMEM	= "W          W";
const char mapRow5[] PROGMEM	= "W          W";
const char mapRow6[] PROGMEM	= "W          W";
const char mapRow7[] PROGMEM	= "W          W";
const char mapRow8[] PROGMEM	= "W          W";
const char mapRow9[] PROGMEM	= "W          W";
const char mapRow10[] PROGMEM	= "W          W";
const char mapRow11[] PROGMEM	= "W          W";
const char mapRow12[] PROGMEM	= "W          W";
const char mapRow13[] PROGMEM	= "W          W";
const char mapRow14[] PROGMEM	= "W          W";
const char mapRow15[] PROGMEM	= "W          W";
const char mapRow16[] PROGMEM	= "W          W";
const char mapRow17[] PROGMEM	= "W          W";
const char mapRow18[] PROGMEM	= "W          W";
const char mapRow19[] PROGMEM	= "W          W";
const char mapRow20[] PROGMEM	= "FFFFFFFFFFFF";

const char* const map[] PROGMEM =
{
	mapRow0,
	mapRow1,
	mapRow2,
	mapRow3,
	mapRow4,
	mapRow5,
	mapRow6,
	mapRow7,
	mapRow8,
	mapRow9,
	mapRow10,
	mapRow11,
	mapRow12,
	mapRow13,
	mapRow14,
	mapRow15,
	mapRow16,
	mapRow17,
	mapRow18,
	mapRow19,
	mapRow20
};

const char type_I_0[] PROGMEM =
" I  "
" I  "
" I  "
" I  ";

const char type_I_90[] PROGMEM =
"IIII"
"    "
"    "
"    ";

const char type_T_0[] PROGMEM =
"TTT "
" T  "
"    "
"    ";

const char type_T_90[] PROGMEM =
"  T "
" TT "
"  T "
"    ";

const char type_T_180[] PROGMEM =
"    "
" T  "
"TTT "
"    ";

const char type_T_270[] PROGMEM =
"T   "
"TT  "
"T   "
"    ";

const char type_O_0[] PROGMEM =
"OO  "
"OO  "
"    "
"    ";

const char type_L_0[] PROGMEM =
"L   "
"L   "
"LL  "
"    ";

const char type_L_90[] PROGMEM =
"LLL "
"L   "
"    "
"    ";

const char type_L_180[] PROGMEM =
" LL "
"  L "
"  L "
"    ";

const char type_L_270[] PROGMEM =
"  L "
"LLL "
"    "
"    ";

const char type_J_0[] PROGMEM =
" J  "
" J  "
"JJ  "
"    ";

const char type_J_90[] PROGMEM =
"J   "
"JJJ "
"    "
"    ";

const char type_J_180[] PROGMEM =
"JJ  "
"J   "
"J   "
"    ";

const char type_J_270[] PROGMEM =
"JJJ "
"  J "
"    "
"    ";

const char type_S_0[] PROGMEM =
" SS "
"SS  "
"    "
"    ";

const char type_S_90[] PROGMEM =
"S   "
"SS  "
" S  "
"    ";

const char type_Z_0[] PROGMEM =
"ZZ  "
" ZZ "
"    "
"    ";

const char type_Z_90[] PROGMEM =
" Z  "
"ZZ  "
"Z   "
"    ";

const char* const Tetrominos[] PROGMEM =
{
	type_I_0,
	type_I_90,
	type_T_0,
	type_T_90,
	type_T_180,
	type_T_270,
	type_O_0,
	type_L_0,
	type_L_90,
	type_L_180,
	type_L_270,
	type_J_0,
	type_J_90,
	type_J_180,
	type_J_270,
	type_S_0,
	type_S_90,
	type_Z_0,
	type_Z_90
};

const char* TetrominosTypes = "#ITOLJSZ";