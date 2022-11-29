/*
 * notes.h
 *
 * Created: 29.10.2022 21:39:24
 *  Author: Michal
 */ 


#ifndef NOTES_H_
#define NOTES_H_

#include <avr/io.h>

typedef enum
{
	C0 = 0,
	C0_D0,
	D0,
	D0_E0,
	E0,
	F0,
	F0_G0,
	G0,
	G0_A0,
	A0,
	A0_B0,
	B0,
	C1,
	C1_D1,
	D1,
	D1_E1,
	E1,
	F1,
	F1_G1,
	G1,
	G1_A1,
	A1,
	A1_B1,
	B1,
	C2,
	C2_D2,
	D2,
	D2_E2,
	E2,
	F2,
	F2_G2,
	G2,
	G2_A2,
	A2,
	A2_B2,
	B2,
	C3,
	C3_D3,
	D3,
	D3_E3,
	E3,
	F3,
	F3_G3,
	G3,
	G3_A3,
	A3,
	A3_B3,
	B3,
	C4,
	C4_D4,
	D4,
	D4_E4,
	E4,
	F4,
	F4_G4,
	G4,
	G4_A4,
	A4,
	A4_B4,
	B4,
	C5,
	C5_D5,
	D5,
	D5_E5,
	E5,
	F5,
	F5_G5,
	G5,
	G5_A5,
	A5,
	A5_B5,
	B5,
	C6,
	C6_D6,
	D6,
	D6_E6,
	E6,
	F6,
	F6_G6,
	G6,
	G6_A6,
	A6,
	A6_B6,
	B6,
	C7,
	C7_D7,
	D7,
	D7_E7,
	E7,
	F7,
	F7_G7,
	G7,
	G7_A7,
	A7,
	A7_B7,
	B7,
	C8,
	C8_D8,
	D8,
	D8_E8,
	E8,
	F8,
	F8_G8,
	G8,
	G8_A8,
	A8,
	A8_B8,
	B8,
	PAUSE
} NoteIndex;

typedef struct
{
	NoteIndex Index;
	uint8_t Duration;
} Note;

extern const uint16_t notes[];

extern const Note OldMcDonald[];

extern const Note OdaDoRadosci[];

#endif /* NOTES_H_ */