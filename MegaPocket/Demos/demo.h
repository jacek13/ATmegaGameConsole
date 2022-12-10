/*
 * demo.h
 *
 * Created: 29.10.2022 17:43:25
 *  Author: Michal
 */ 

#ifndef DEMO_H_
#define DEMO_H_

#include <avr/io.h>

uint8_t demoRandomDisplayBitmapRandom();

uint8_t demoFillDisplayWithBitmaps();

uint8_t demoText();

void demoPixels();

uint8_t demoLines();

uint8_t demoDisplaySetOfCharacters();

uint8_t demoDynamicText();

uint8_t demoRTC(uint8_t setCompileTime);

void demoGenerateTones();

uint8_t demoPlaySounds();

void demoBrightness();

void demoBaseTime();

uint8_t demoReadKeys();

#endif /* DEMO_H_ */