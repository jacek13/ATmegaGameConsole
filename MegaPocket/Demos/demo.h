/*
 * demo.h
 *
 * Created: 29.10.2022 17:43:25
 *  Author: Michal
 */ 

#ifndef DEMO_H_
#define DEMO_H_

#include <avr/io.h>

void demoRandomDisplayBitmapRandom();

void demoFillDisplayWithBitmaps();

void demoText();

void demoPixels();

void demoLines();

void demoDisplaySetOfCharacters();

void demoDynamicText();

void demoRTC(uint8_t setCompileTime);

void demoGenerateTones();

void demoBrightness();

void demoBaseTime();

#endif /* DEMO_H_ */