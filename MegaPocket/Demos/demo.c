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
#include "../Input/input.h"
#include "../System/menu.h"
#include "../System/systemData.h"

uint8_t demoRandomDisplayBitmapRandom()
{
	static uint8_t i = 1;
	
	Display_Clear_Screen(0x0000);
	while(1)
	{
		uint16_t randomNumber = random();
		Display_Draw_Image_From_Progmem(randomNumber % (DISPLAY_WIDTH + 1 - 32), randomNumber % (DISPLAY_HEIGHT + 1 - 32), 32, 32, mario);
		if (!++i) Display_Clear_Screen(0x0000);
		if (read_key(INPUT_BUTTON_SELECT, PINB)) break;
	}
	return 0;
}

uint8_t demoFillDisplayWithBitmaps()
{
	Display_Clear_Screen(0x0000);
	while(1)
	{
		for(uint8_t r = 0; r < 8; r++)
			for(uint8_t c = 0; c < 10; c++)
				Display_Draw_Image_From_Progmem((uint16_t)c * 32,(uint8_t)r * 32, 32, 32, mario);
		
		for(uint8_t r = 0; r < 8; r++)
			for(uint8_t c = 0; c < 10; c++)
				Display_Draw_Image_From_Progmem((uint16_t)c * 32,(uint8_t)r * 32, 32, 32, cili);
		if (read_key(INPUT_BUTTON_SELECT, PINB)) break;
	}
	return 0;
}

uint8_t demoText()
{
	static uint8_t i = 1;
	Display_Clear_Screen(0x0000);
	while(1)
	{
		uint16_t randomNumber = random();
		Display_Draw_Text_From_Progmem(randomNumber % (DISPLAY_WIDTH + 1 - 16), randomNumber % (DISPLAY_HEIGHT + 1 - 16), PSTR("ZBUDOWALISMY GO!"), consolas_font, 0xFFFF, randomNumber);
		if (!++i) Display_Clear_Screen(0x0000), demoDisplaySetOfCharacters(), Display_Clear_Screen(0x0000);
		if (read_key(INPUT_BUTTON_SELECT, PINB)) break;
	}
	return 0;
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

uint8_t demoLines()
{
	static uint16_t x = DISPLAY_WIDTH;
	static uint8_t y = 1;
	
	Display_Clear_Screen(0x0000);
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
		if (read_key(INPUT_BUTTON_SELECT, PINB)) break;
	}
	Display_Clear_Screen(0x0000);
	return 0;
}

uint8_t demoDisplaySetOfCharacters()
{

	while(1)
	{
		Display_Draw_Text_From_Progmem(0, 0, PSTR("!#$%&'()*+,-./0123456789:;<=>?@[\]^_`{|}~"), consolas_font, 0xFFFF, 0x0000);
		Display_Draw_Text_From_Progmem(0, 16, PSTR("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), consolas_font, 0xFFFF, 0x0000);
		Display_Draw_Text_From_Progmem(0, 32, PSTR("abcdefghijklmnopqrstuvwxyz"), consolas_font, 0xFFFF, 0x0000);
		Display_Draw_Text_From_Progmem(0, 64, PSTR("Demo wyswietla:"), consolas_font, 0xC700, 0x8170);
		Display_Draw_Text_From_Progmem(0, 80, PSTR("* 255 razy bitmape 32x32 rgb565,"), consolas_font, 0xD800, 0x0000);
		Display_Draw_Text_From_Progmem(0, 96, PSTR("* 255 razy ciag 16 znakow,"), consolas_font, 0xD800, 0x0000);
		Display_Draw_Text_From_Progmem(0, 112, PSTR("* wypelnia ekran bitmapami 32x32."), consolas_font, 0xD800, 0x0000);
		Display_Draw_Text_From_Progmem(0, 128, PSTR("Wcisnij klawisz START aby kontynuowac"), consolas_font, 0xD800, 0x0000);
		if (read_key(INPUT_BUTTON_START, PINB)) break;
	}
	return 0;
}

uint8_t demoDynamicText()
{
	static char buffer[32] = {};
	static char bufferRandomText[32] = {};
	static char animation[] = { '-', '\\', '|', '/' };
	static uint8_t i = 1;
	static uint8_t j = 0;
	static uint8_t k = 0;
	static uint8_t c = 0;
	uint16_t randomNumber = random();
	
	Display_Clear_Screen(0x0000);
	while(1)
	{
		sprintf(buffer, "Licznik I: %3i", i), Display_Draw_Text(0, 0, buffer, consolas_font, 0xD800, 0x0000);
		sprintf(buffer, "Licznik J: %3i", j), Display_Draw_Text(0, 16, buffer, consolas_font, 0xD800, 0x0000);
		sprintf(buffer, "Licznik K: %3i", k), Display_Draw_Text(0, 32, buffer, consolas_font, 0xD800, 0x0000);
		sprintf(bufferRandomText, "Animacja: %c", animation[c++]), Display_Draw_Text(0, 48, bufferRandomText, consolas_font, 0xD800, 0x0000);
		sprintf(buffer, "Losowa liczba: %3i", randomNumber), Display_Draw_Text(0, 64, buffer, consolas_font, 0xD800, 0x0000);
		
		if (!++i) ++j;
		if (j == 255) ++k;
		if (k == 255) i = 1, j = k = 0;
		if (c >= 4) c = 0;
		randomNumber = random();
		if (read_key(INPUT_BUTTON_SELECT, PINB)) break;
	}
	return 0;
}

inline uint8_t demoRTC(uint8_t setCompileTime)
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
	
	Display_Clear_Screen(0x0000);
	while(1)
	{
		DS1307_Get_DateTime(&date);
		Display_Draw_Text_From_Progmem(0, 0, PSTR("Komunikacja z DS1307 (I2C)"), consolas_font, 0xD800, 0x0000);
		Display_Draw_Text_From_Progmem(0, 16, PSTR("Godzina: "), consolas_font, 0xD800, 0x0000), sprintf(buffer, "%2x:%2x:%2x", date.Hour, date.Minute, date.Second), Display_Draw_Text(10, 16, buffer, consolas_font, 0xD800, 0x0000);
		Display_Draw_Text_From_Progmem(0, 32, PSTR("Data: "), consolas_font, 0xD800, 0x0000), sprintf(buffer, "%2x.%2x.20%2x", date.DayOfMonth, date.Month, date.Year), Display_Draw_Text(7, 32, buffer, consolas_font, 0xD800, 0x0000);
		Display_Draw_Text_From_Progmem(0, 48, PSTR("Dzien tygodnia: "), consolas_font, 0xD800, 0x0000), sprintf(buffer, "%2x", date.DayOfWeek), Display_Draw_Text(0, 48, buffer, consolas_font, 0xD800, 0x0000);
		Display_Draw_Text_From_Progmem(0, 64, PSTR(__TIMESTAMP__), consolas_font, 0xD800, 0x0000);
		if (read_key(INPUT_BUTTON_SELECT, PINB)) break;
	}
	return 0;
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
		if (read_key(INPUT_BUTTON_SELECT, PINB)) break;
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

uint8_t demoReadKeys()
{
	static char buffer[32] = {};

	uint8_t counterUP = 0;
	uint8_t counterDOWN = 0;
	uint8_t counterLEFT = 0;
	uint8_t counterRIGHT = 0;
	uint8_t counterSTART = 0;
	uint8_t counterSELECT = 0;
	struct Buttons systemButtons = {};
	
	sprintf(buffer, "UP FALLING_EDGE -> Licznik: '%3d'", counterUP), Display_Draw_Text(0, 0, buffer, consolas_font, 0xD800, 0x0000);
	sprintf(buffer, "DOWN RISING_EDGE  -> Licznik: '%3d'", counterDOWN), Display_Draw_Text(0, 16, buffer, consolas_font, 0xD800, 0x0000);
	sprintf(buffer, "LEFT PRESSED      -> Licznik: '%3d'", counterLEFT), Display_Draw_Text(0, 32, buffer, consolas_font, 0xD800, 0x0000);
	sprintf(buffer, "RIGHT RELEASED     -> Licznik: '%3d'", counterRIGHT), Display_Draw_Text(0, 48, buffer, consolas_font, 0xD800, 0x0000);
	sprintf(buffer, "START FALLING_EDGE -> Licznik: '%3d'", counterSTART), Display_Draw_Text(0, 64, buffer, consolas_font, 0xD800, 0x0000);
	sprintf(buffer, "SELECT RISING_EDGE  -> Licznik: '%3d'", counterSELECT), Display_Draw_Text(0, 80, buffer, consolas_font, 0xD800, 0x0000);
		
	while(1)
	{
		InputUpdateStates(&systemButtons);
		
		if (systemButtons.ButtonUp.currentState == BUTTON_FALLING_EDGE)
		{
			counterUP++;
			sprintf(buffer, "UP FALLING_EDGE -> Licznik: '%3d'", counterUP), Display_Draw_Text(0, 0, buffer, consolas_font, 0xD800, 0x0000);
		}
		if (systemButtons.ButtonDown.currentState == BUTTON_RISING_EDGE)
		{	
			counterDOWN++;
			sprintf(buffer, "DOWN RISING_EDGE  -> Licznik: '%3d'", counterDOWN), Display_Draw_Text(0, 16, buffer, consolas_font, 0xD800, 0x0000);
		}
		if (systemButtons.ButtonLeft.currentState == BUTTON_PRESSED)
		{
			counterLEFT++;
			sprintf(buffer, "LEFT PRESSED      -> Licznik: '%3d'", counterLEFT), Display_Draw_Text(0, 32, buffer, consolas_font, 0xD800, 0x0000);
		}
		if (systemButtons.ButtonRight.currentState == BUTTON_RELEASED)
		{
			counterRIGHT++;
			sprintf(buffer, "RIGHT RELEASED     -> Licznik: '%3d'", counterRIGHT), Display_Draw_Text(0, 48, buffer, consolas_font, 0xD800, 0x0000);
		}
		if (systemButtons.ButtonStart.currentState == BUTTON_FALLING_EDGE)	
		{
			counterSTART++;
			sprintf(buffer, "START FALLING_EDGE -> Licznik: '%3d'", counterSTART), Display_Draw_Text(0, 64, buffer, consolas_font, 0xD800, 0x0000);
		}
		if (systemButtons.ButtonSelect.currentState == BUTTON_RISING_EDGE)
		{
			counterSELECT++;
			sprintf(buffer, "SELECT RISING_EDGE  -> Licznik: '%3d'", counterSELECT), Display_Draw_Text(0, 80, buffer, consolas_font, 0xD800, 0x0000);
		}
	}
	return 0;
}

uint8_t demoPlaySounds()
{
	Buttons demoButtons = {};
	// Set OC1A as output pin
	DDRB = (1 << PB1);
	TCCR1A = (1 << COM1A0);
	TCCR1B = (1 << WGM12) | (1 << CS10);
	
	Display_Clear_Screen(0x0000);
	while(1)
	{
		InputUpdateStates(&demoButtons);
		
		Display_Draw_Text_From_Progmem(0, 0, PSTR("Current note: C"), consolas_font, 0xD800, demoButtons.ButtonUp.currentState == BUTTON_PRESSED ? 0xFE05 : 0x0000);
		Display_Draw_Text_From_Progmem(0, 16, PSTR("Current note: D"), consolas_font, 0xD800, demoButtons.ButtonDown.currentState == BUTTON_PRESSED ? 0xFE05 : 0x0000);
		Display_Draw_Text_From_Progmem(0, 32, PSTR("Current note: E"), consolas_font, 0xD800, demoButtons.ButtonLeft.currentState == BUTTON_PRESSED ? 0xFE05 : 0x0000);
		Display_Draw_Text_From_Progmem(0, 48, PSTR("Current note: F"), consolas_font, 0xD800, demoButtons.ButtonRight.currentState == BUTTON_PRESSED ? 0xFE05 : 0x0000);
		Display_Draw_Text_From_Progmem(0, 64, PSTR("Current note: G"), consolas_font, 0xD800, demoButtons.ButtonStart.currentState == BUTTON_PRESSED ? 0xFE05 : 0x0000);
		Display_Draw_Text_From_Progmem(0, 80, PSTR("Current note: H"), consolas_font, 0xD800, demoButtons.ButtonSelect.currentState == BUTTON_PRESSED ? 0xFE05 : 0x0000);
		
		if (demoButtons.ButtonStart.currentState == BUTTON_PRESSED && demoButtons.ButtonSelect.currentState == BUTTON_PRESSED)
		{
			OCR1A = 0;
			Display_Clear_Screen(0x0000);
			break;//OCR1A = calculateOCRnA(notes[A1], 8), continue;
		}
		if (demoButtons.ButtonUp.currentState == BUTTON_PRESSED)
		{
			OCR1A = calculateOCRnA(notes[C1], 8);
			continue;
		}
		if (demoButtons.ButtonUp.currentState == BUTTON_PRESSED)
		{
			OCR1A = calculateOCRnA(notes[C1], 8);
			continue;
		}
		if (demoButtons.ButtonDown.currentState == BUTTON_PRESSED)
		{
			OCR1A = calculateOCRnA(notes[D1], 8);
			continue;
		}
		if (demoButtons.ButtonLeft.currentState == BUTTON_PRESSED)
		{
			OCR1A = calculateOCRnA(notes[E1], 8);
			continue;
		}
		if (demoButtons.ButtonRight.currentState == BUTTON_PRESSED)
		{
			OCR1A = calculateOCRnA(notes[F1], 8);
			continue;
		}
		if (demoButtons.ButtonStart.currentState == BUTTON_PRESSED)
		{
			OCR1A = calculateOCRnA(notes[G1], 8);
			continue;
		}
		if (demoButtons.ButtonSelect.currentState == BUTTON_PRESSED)
		{
			OCR1A = calculateOCRnA(notes[A1], 8);
			continue;
		}
		OCR1A = 0;
	}
	return 0;
}