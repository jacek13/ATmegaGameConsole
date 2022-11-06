/*
 * display.h
 *
 * Created: 15.10.2022 20:03:21
 *  Author: Michal
 */ 

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../ILI/ili9341.h"
#include "../common/bitManipulation.h"
#include "../common/config.h"

void Display_Draw_Pixel(uint16_t x, uint8_t y, uint16_t color);

void Display_Draw_Line(uint16_t xs, uint8_t ys, uint16_t xe, uint8_t ye, uint16_t color);

void Display_Draw_Fill_Rect(uint16_t x, uint8_t y, uint16_t w, uint16_t h, uint16_t color);

void Display_Clear_Screen(uint16_t color);

// draws image from flash (PROGMEM)
void Display_Draw_Image_From_Progmem(uint16_t x, uint8_t y, uint16_t w, uint16_t h, const uint16_t * img16);

void Display_Draw_Text(uint16_t x, uint8_t y, const char * text, const uint16_t * font, uint16_t fontColor, uint16_t backgroundColor);

void Display_Draw_Text_From_Progmem(uint16_t x, uint8_t y, const char * text, const uint16_t * font, uint16_t fontColor, uint16_t backgroundColor);

void Display_Set_Brightness(uint8_t  brightness);

#endif /* DISPLAY_H_ */