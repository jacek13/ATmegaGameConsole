/*
 * demo.c
 *
 * Created: 29.10.2022 17:43:35
 *  Author: Michal
 */ 

#include "demo.h"
#include "../ILI/ili9341.h"
#include "../DS1307/rtc.h"
#include "../Data/bitmaps.h"
#include "../Data/fonts.h"
#include "../Data/notes.h"
#include "../LcdDisplay/display.h"
#include "../common/config.h"

inline void demoRandomDisplayBitmapRandom()
{
	static uint8_t i = 1;
	while(1)
	{
		uint16_t randomNumber = random();
		Display_Draw_Image_From_Progmem(randomNumber % (DISPLAY_WIDTH + 1 - 32), randomNumber % (DISPLAY_HEIGHT + 1 - 32), 32, 32, mario);
		if (!++i) Display_Clear_Screen(0x0000);
	}
}

inline void demoFillDisplayWithBitmaps()
{
	while(1)
	{
		for(uint8_t r = 0; r < 8; r++)
			for(uint8_t c = 0; c < 10; c++)
				Display_Draw_Image_From_Progmem((uint16_t)c * 32,(uint8_t)r * 32, 32, 32, mario);
		
		for(uint8_t r = 0; r < 8; r++)
			for(uint8_t c = 0; c < 10; c++)
				Display_Draw_Image_From_Progmem((uint16_t)c * 32,(uint8_t)r * 32, 32, 32, cili);
	}
}

inline void demoText()
{
	static uint8_t i = 1;
	while(1)
	{
		uint16_t randomNumber = random();
		Display_Draw_Text_From_Progmem(randomNumber % (DISPLAY_WIDTH + 1 - 16), randomNumber % (DISPLAY_HEIGHT + 1 - 16), PSTR("ZBUDOWALISMY GO!"), consolas_font, 0xFFFF, randomNumber);
		if (!++i) Display_Clear_Screen(0x0000), demoDisplaySetOfCharacters(), Display_Clear_Screen(0x0000);
	}
}

inline void demoPixels()
{
	static uint16_t i = 1;
	while(1)
	{
		uint16_t randomNumber = random();
		Display_Draw_Pixel(randomNumber % (DISPLAY_WIDTH + 1 - 16), randomNumber % (DISPLAY_HEIGHT + 1 - 16), randomNumber);
		if (!++i) Display_Clear_Screen(0x0000);
	}
}

inline void demoLines()
{
	static uint16_t x = DISPLAY_WIDTH;
	static uint8_t y = 1;
	
	while(1)
	{
		uint16_t randomNumber = random();
		if (y < DISPLAY_HEIGHT)
		{
			Display_Draw_Line(0, 0, DISPLAY_WIDTH - 1, y+=8, randomNumber);
		}
		else
		{
			Display_Draw_Line(0, 0, x-=8, DISPLAY_HEIGHT - 1, randomNumber);
		}
		if (x == 0) _delay_ms(2000), Display_Clear_Screen(0x0000), x = DISPLAY_WIDTH, y = 1;
	}
}

inline void demoDisplaySetOfCharacters()
{
	Display_Draw_Text_From_Progmem(0, 0, PSTR("!#$%&'()*+,-./0123456789:;<=>?@[\]^_`{|}~"), consolas_font, 0xFFFF, 0x0000);
	Display_Draw_Text_From_Progmem(0, 16, PSTR("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), consolas_font, 0xFFFF, 0x0000);
	Display_Draw_Text_From_Progmem(0, 32, PSTR("abcdefghijklmnopqrstuvwxyz"), consolas_font, 0xFFFF, 0x0000);
	Display_Draw_Text_From_Progmem(0, 64, PSTR("Demo wyswietla:"), consolas_font, 0xC700, 0x8170);
	Display_Draw_Text_From_Progmem(0, 80, PSTR("* 255 razy bitmape 32x32 rgb565,"), consolas_font, 0xD800, 0x0000);
	Display_Draw_Text_From_Progmem(0, 96, PSTR("* 255 razy ciag 16 znakow,"), consolas_font, 0xD800, 0x0000);
	Display_Draw_Text_From_Progmem(0, 112, PSTR("* wypelnia ekran bitmapami 32x32."), consolas_font, 0xD800, 0x0000);
	_delay_ms(3500);
}

inline void demoDynamicText()
{
	static char buffer[32] = {};
	static char bufferRandomText[32] = {};
	static char animation[] = { '-', '\\', '|', '/' };
	static uint8_t i = 1;
	static uint8_t j = 0;
	static uint8_t k = 0;
	static uint8_t c = 0;
	uint16_t randomNumber = random();
	
	while(1)
	{
		sprintf(buffer, "Licznik I: %i   ", i), Display_Draw_Text(0, 0, buffer, consolas_font, 0xD800, 0x0000);
		sprintf(buffer, "Licznik J: %i   ", j), Display_Draw_Text(0, 16, buffer, consolas_font, 0xD800, 0x0000);
		sprintf(buffer, "Licznik K: %i   ", k), Display_Draw_Text(0, 32, buffer, consolas_font, 0xD800, 0x0000);
		sprintf(bufferRandomText, "Animacja: %c  ", animation[c++]), Display_Draw_Text(0, 48, bufferRandomText, consolas_font, 0xD800, 0x0000);
		sprintf(buffer, "Losowa liczba: %i   ", randomNumber), Display_Draw_Text(0, 64, buffer, consolas_font, 0xD800, 0x0000);
		
		if (!++i) ++j;
		if (j == 255) ++k;
		if (k == 255) i = 1, j = k = 0;
		if (c >= 4) c = 0;
		randomNumber = random();
	}
}

inline void demoRTC(uint8_t setCompileTime)
{
	static DateTime date;
	static char buffer[32] = {};
	
	IIC_init(IIC_SPEED);
	DS1307_init(0x00);
	if (setCompileTime)
	{
		DS1307_FillDataWithCompileDateTime(&date);
		DS1307_Set_DateTime(&date);		
	}
	
	while(1)
	{
		DS1307_Get_DateTime(&date);
		sprintf(buffer, "Komunikacja z DS1307 (I2C)"), Display_Draw_Text(0, 0, buffer, consolas_font, 0xD800, 0x0000);
		sprintf(buffer, "Godzina: %2x:%2x:%2x", date.Hour, date.Minute, date.Second), Display_Draw_Text(0, 16, buffer, consolas_font, 0xD800, 0x0000);
		sprintf(buffer, "Data: %2x.%2x.20%2x", date.DayOfMonth, date.Month, date.Year), Display_Draw_Text(0, 32, buffer, consolas_font, 0xD800, 0x0000);
		sprintf(buffer, "Dzien tygodnia: %2x", date.DayOfWeek), Display_Draw_Text(0, 48, buffer, consolas_font, 0xD800, 0x0000);
		sprintf(buffer, "Czas kompilacji: %s %s", __DATE__, __TIME__), Display_Draw_Text(0, 64, buffer, consolas_font, 0xD800, 0x0000);
	}
}

static inline uint16_t calculateOCRnA(uint16_t noteFrequency, uint8_t prescaler)
{
	return (F_CPU / (noteFrequency * prescaler * 2) - 1);
}

inline void demoGenerateTones()
{
	static char buffer[32] = {};
	sprintf(buffer, "Czas kompilacji: %s %s", __DATE__, __TIME__), Display_Draw_Text(0, 0, buffer, consolas_font, 0xD800, 0x0000);
	sprintf(buffer, "Generator dzwiekow"), Display_Draw_Text(0, 16, buffer, consolas_font, 0xD800, 0x0000);
	
	// Set OC1A as output pin
	DDRB = (1 << PB1);
	TCCR1A = (1 << COM1A0);
	TCCR1B = (1 << WGM12) | (1 << CS10);

	while(1)
	{
		//for(uint8_t note = C0; note <= B8; note++) 
		//{
		//	sprintf(buffer, "Dzwiek numer: %2d", note), Display_Draw_Text(0, 32, buffer, consolas_font, 0xD800, 0x0000);
		//	sprintf(buffer, "Czestotliwoscr: %2d", notes[note]), Display_Draw_Text(0, 48, buffer, consolas_font, 0xD800, 0x0000);
		//	//OCR1A = calculateOCRnA(notes[note], 8);
		//	_delay_ms(100);
		//}
		for(uint8_t index = 0; index < 48; index++)
		{
			sprintf(buffer, "Dzwiek numer: %2d  ", OdaDoRadosci[index].Index), Display_Draw_Text(0, 32, buffer, consolas_font, 0xD800, 0x0000);
			if(OdaDoRadosci[index].Index == PAUSE) OCR1A = 0;
			else OCR1A = calculateOCRnA(notes[OdaDoRadosci[index].Index], 8);
			//_delay_ms(100);
			for(uint8_t j = 0; j < OdaDoRadosci[index].Duration; j++) _delay_ms(1);
			OCR1A = 0;
			_delay_ms(100);
		}
	}
}

void demoBrightness()
{
	static uint8_t brightness = 1;
	static char buffer[32] = {};

	while(1)
	{
		sprintf(buffer, "Jasnosc ekranu: '%3.d'", brightness), Display_Draw_Text(0, 224, buffer, consolas_font, 0xD800, 0x0000);
		for(uint8_t xy = 0; xy < 15; xy++)
			Display_Draw_Text_From_Progmem(xy * 16, xy * 16, PSTR("Buzie widze, w tym tenczu."), consolas_font, 0x0000, 0xFFFF);
		//_delay_ms(1000);
		Display_Set_Brightness(brightness++);
	}
}

volatile uint16_t numberOfMiliseconds;
volatile uint16_t numberOfSeconds;
volatile uint8_t numberOfTimer0Interupts;

/************************************************************************/
/* Demo that displays bitmap and mesaure time with base of 200 ms		*/
/************************************************************************/
void demoBaseTime()
{
	static char buffer[32] = {};
	
	// set Timer0
	TCNT0 = 0x00;
	TCCR0B = (1 << CS02) | (1 << CS00); // set 1024 prescaler
	//TIMSK0 = (1 << TOIE0); // enable counter interupt
	//sei();
	
	while(1)
	{
		if ((TIFR0 & 0x01) == 1) ++numberOfTimer0Interupts,  TIFR0 = 0x00;
		uint16_t randomNumber = random();
		//cli();
		Display_Draw_Image_From_Progmem(randomNumber % (DISPLAY_WIDTH + 1 - 32), randomNumber % (DISPLAY_HEIGHT + 1 - 32), 32, 32, mario);
		sprintf(buffer, "Minelo: %5d,%1d [s]", numberOfSeconds, numberOfMiliseconds << 1), Display_Draw_Text(0, 0, buffer, consolas_font, 0xD800, 0x0000);
		//sei();
		if (numberOfTimer0Interupts >= 12) ++numberOfMiliseconds, numberOfTimer0Interupts = 0;
		if (numberOfMiliseconds >= 5) ++numberOfSeconds, numberOfMiliseconds = 0;
	}
}

//ISR(TIMER0_OVF_vect)
//{
//	++numberOfTimer0Interupts;
//	//TIFR0 = 0x01;
//}