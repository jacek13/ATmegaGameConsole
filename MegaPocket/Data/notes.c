/*
 * notes.c
 *
 * Created: 29.11.2022 23:32:57
 *  Author: Michal
 */ 

#include "notes.h"

const uint16_t notes[] =
{
	16, 17, 18, 19, 20, 21, 23, 24, 25, 27, 29, 30,
	32, 34, 36, 38, 41, 43, 46, 49, 51, 55, 58, 61,
	65, 69, 73, 77, 82, 87, 92, 98, 103, 110, 116, 123,
	130, 138, 146, 155, 164, 174, 185, 196, 207, 220, 233, 247,
	261, 277, 293, 311, 329, 349, 369, 392, 415, 440, 466, 494,
	523, 554, 587, 622, 659, 698, 739, 784, 830, 880, 932, 987,
	1046, 1108, 1174, 1244, 1318, 1396, 1480, 1568, 1661, 1760, 1864, 1975,
	2093, 2217, 2349, 2489, 2637, 2793, 2960, 3136, 3322, 3520, 3729, 3951,
	4186, 4435, 4698, 4978, 5274, 5587, 5920, 6272, 6645, 7040, 7458, 7902
};

const Note OldMcDonald[] =
{
	{ .Index = G1, .Duration = 500 },
	{ .Index = G1, .Duration = 500 },
	{ .Index = G1, .Duration = 500 },
	{ .Index = D1, .Duration = 500 },
	
	{ .Index = E1, .Duration = 500 },
	{ .Index = E1, .Duration = 500 },
	{ .Index = D1, .Duration = 1000 },
	
	{ .Index = B1, .Duration = 500 },
	{ .Index = B1, .Duration = 500 },
	{ .Index = A1, .Duration = 500 },
	{ .Index = A1, .Duration = 500 },
	
	{ .Index = G1, .Duration = 1000 },
	{ .Index = PAUSE, .Duration = 500 },
	{ .Index = D1, .Duration = 500 },

	{ .Index = G1, .Duration = 500 },
	{ .Index = G1, .Duration = 500 },
	{ .Index = G1, .Duration = 500 },
	{ .Index = D1, .Duration = 500 },
	
	{ .Index = E1, .Duration = 500 },
	{ .Index = E1, .Duration = 500 },
	{ .Index = D1, .Duration = 1000 },
	
	{ .Index = B1, .Duration = 500 },
	{ .Index = B1, .Duration = 500 },
	{ .Index = A1, .Duration = 500 },
	{ .Index = A1, .Duration = 500 },
	
	{ .Index = G1, .Duration = 1000 },
	{ .Index = PAUSE, .Duration = 500 },
	{ .Index = D1, .Duration = 250 },
	{ .Index = D1, .Duration = 250 },
	
	{ .Index = G1, .Duration = 500 },
	{ .Index = G1, .Duration = 500 },
	{ .Index = G1, .Duration = 500 },
	{ .Index = D1, .Duration = 250 },
	{ .Index = D1, .Duration = 250 },
	
	{ .Index = G1, .Duration = 500 },
	{ .Index = G1, .Duration = 500 },
	{ .Index = G1, .Duration = 1000 },
	
	{ .Index = G1, .Duration = 250 },
	{ .Index = G1, .Duration = 250 },
	{ .Index = G1, .Duration = 250 },
	{ .Index = PAUSE, .Duration = 250 },
	{ .Index = G1, .Duration = 250 },
	{ .Index = G1, .Duration = 250 },
	{ .Index = G1, .Duration = 250 },
	{ .Index = PAUSE, .Duration = 250 },
	
	{ .Index = G1, .Duration = 250 },
	{ .Index = G1, .Duration = 250 },
	{ .Index = G1, .Duration = 250 },
	{ .Index = G1, .Duration = 250 },
	{ .Index = G1, .Duration = 500 },
	{ .Index = G1, .Duration = 500 }
};

const Note OdaDoRadosci[] =
{
	{ .Index = B0, .Duration = 500 },
	{ .Index = B0, .Duration = 500 },
	{ .Index = C1, .Duration = 500 },
	{ .Index = D1, .Duration = 500 },
	
	{ .Index = D1, .Duration = 500 },
	{ .Index = C1, .Duration = 500 },
	{ .Index = B0, .Duration = 500 },
	{ .Index = A0, .Duration = 500 },
	
	{ .Index = G0, .Duration = 500 },
	{ .Index = G0, .Duration = 500 },
	{ .Index = A0, .Duration = 500 },
	{ .Index = B0, .Duration = 500 },
	
	{ .Index = B0, .Duration = 750 },
	{ .Index = A0, .Duration = 250 },
	{ .Index = A0, .Duration = 1000 },
	
	{ .Index = B0, .Duration = 500 },
	{ .Index = B0, .Duration = 500 },
	{ .Index = C1, .Duration = 500 },
	{ .Index = D1, .Duration = 500 },
	
	{ .Index = D1, .Duration = 500 },
	{ .Index = C1, .Duration = 500 },
	{ .Index = B0, .Duration = 500 },
	{ .Index = A0, .Duration = 500 },
	
	{ .Index = G0, .Duration = 500 },
	{ .Index = G0, .Duration = 500 },
	{ .Index = A0, .Duration = 500 },
	{ .Index = B0, .Duration = 500 },
	
	{ .Index = B0, .Duration = 500 },
	{ .Index = A0, .Duration = 500 },
	{ .Index = G0, .Duration = 500 },
	{ .Index = F0, .Duration = 500 },

	{ .Index = D0, .Duration = 500 },
	{ .Index = D0, .Duration = 500 },
	{ .Index = F0, .Duration = 500 },
	{ .Index = D0, .Duration = 500 },
	
	{ .Index = D0, .Duration = 750 },
	{ .Index = D0, .Duration = 250 },
	{ .Index = D0, .Duration = 1000 },
	
	{ .Index = G0, .Duration = 500 },
	{ .Index = G0, .Duration = 500 },
	{ .Index = A0, .Duration = 500 },
	{ .Index = B0, .Duration = 500 },
	
	{ .Index = B0, .Duration = 500 },
	{ .Index = A0, .Duration = 500 },
	{ .Index = G0, .Duration = 500 },
	{ .Index = D0, .Duration = 500 },
	
	{ .Index = PAUSE, .Duration = 2000 }
};