#include "TetrisData.h"

const char* map[] =
{
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"W          W"},
	{"FFFFFFFFFFFF"}
};

const char* Tetrominos[] =
{
	{
		" I  "
		" I  "
		" I  "
		" I  "
	},
	{
		"IIII"
		"    "
		"    "
		"    "
	},
	{
		"TTT "
		" T  "
		"    "
		"    "
	},
	{
		"  T "
		" TT "
		"  T "
		"    "
	},
	{
		"    "
		" T  "
		"TTT "
		"    "
	},
	{
		"T   "
		"TT  "
		"T   "
		"    "
	},
	{
		"OO  "
		"OO  "
		"    "
		"    "
	},
	{
		"L   "
		"L   "
		"LL  "
		"    "
	},
	{
		"LLL "
		"L   "
		"    "
		"    "
	},
	{
		" LL "
		"  L "
		"  L "
		"    "
	},
	{
		"  L "
		"LLL "
		"    "
		"    "
	},
	{
		" J  "
		" J  "
		"JJ  "
		"    "
	},
	{
		"J   "
		"JJJ "
		"    "
		"    "
	},
	{
		"JJ  "
		"J   "
		"J   "
		"    "
	},
	{
		"JJJ "
		"  J "
		"    "
		"    "
	},
	{
		" SS "
		"SS  "
		"    "
		"    "
	},
	{
		"S   "
		"SS  "
		" S  "
		"    "
	},
	{
		"ZZ  "
		" ZZ "
		"    "
		"    "
	},
	{
		" Z  "
		"ZZ  "
		"Z   "
		"    "
	}
};

const char* TetrominosTypes = "#ITOLJSZ";