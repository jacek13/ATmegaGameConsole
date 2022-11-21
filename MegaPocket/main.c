/*
 * ILI9341_SPI.c
 *
 * Created: 06.10.2022 19:01:38
 * Author : Michal
 */ 

#include <avr/io.h>

#include "ILI/ili9341.h"
#include "DS1307/rtc.h"
#include "LcdDisplay/display.h"
#include "common/config.h"
#include "Demos/demo.h"
#include "Games/Tetris/Tetris.h"

int main(void)
{
	uint8_t i = 1;
	
	SPI_init();
	ILI9341_init(4);
	Display_Clear_Screen(0x0000);
	
	//demoRTC(0);
	demoPlaySounds();
	//demoReadKeys();
	TetrisRun();
}
