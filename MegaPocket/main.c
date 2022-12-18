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
#include "System/system.h"
#include "Games/Tetris/Tetris.h"
#include "Games/Snake/SnakeLogic.h"

int main(void)
{
	uint8_t i = 1;
	
	SPI_init();
	ILI9341_init(2);
	Display_Clear_Screen(0x0000);
	
	// For final version (Noise problem)
	DDRD &= ~(1 << PD3);
	PORTD &= ~(1 << PD3);
	//demoRTC(1);
	systemRun();
}
