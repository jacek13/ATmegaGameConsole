/*
 * display.c
 *
 * Created: 15.10.2022 20:03:32
 *  Author: Michal
 */ 

#include "display.h"

static const uint8_t mask2[] = 
{
	0b10000000,	
	0b01000000,	
	0b00100000,	
	0b00010000,	
	0b00001000,
	0b00000100,	
	0b00000010,	
	0b00000001
};

inline void Display_Draw_Pixel(uint16_t x, uint8_t y, uint16_t color)
{
	ILI9341_Set_Cursor_Optimized(x, y, x + 1, y + 1);
	ILI9341_Write_Data_Word(color);
}

inline void Display_Draw_Line(uint16_t xs, uint8_t ys, uint16_t xe, uint8_t ye, uint16_t color)
{
	int16_t dy, dx;
	int8_t stepx, stepy;
	
	if(ye > ys) { dy = ye - ys; stepy = 1; } else { dy = ys - ye; stepy = -1; }
	if(xe > xs) { dx = xe - xs; stepx = 1; } else { dx = xs - xe; stepx = -1; }
	dy <<= 1;
	dx <<= 1;
	Display_Draw_Pixel(xs, ys, color);

	if (dx > dy)
	{
		int fraction = dy - (dx >> 1);
		while (xs != xe)
		{
			if (fraction >= 0)
			{
				ys += stepy;
				fraction -= dx;
			}
			xs += stepx;
			fraction += dy;
			Display_Draw_Pixel(xs, ys, color);
		}
	} 
	else
	{
		int fraction = dx - (dy >> 1);
		while (ys != ye)
		{
			if (fraction >= 0)
			{
				xs += stepx;
				fraction -= dy;
			}
			ys += stepy;
			fraction += dx;
			Display_Draw_Pixel(xs, ys, color);
		}
	}
	SBI(ILI9341_PORT, ILI9341_CS);
}

inline void Display_Draw_Fill_Rect(uint16_t x, uint8_t y, uint16_t w, uint16_t h, uint16_t color)
{
	if(x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) return;
	if(x + w - 1 >= DISPLAY_WIDTH)  w = DISPLAY_WIDTH - x;
	if(y + h - 1 >= DISPLAY_HEIGHT) h = DISPLAY_HEIGHT - y;
	ILI9341_Set_Cursor_Optimized(x, y, x+w-1, y+h-1);

	uint32_t num = (uint32_t) w * h;
	if(num > 0xffff) 
	{
		ILI9341_Write_Word_Multiple_Times(color, 0xffff);
		ILI9341_Write_Word_Multiple_Times(color, num - 0xffff);
	} 
	else ILI9341_Write_Word_Multiple_Times(color,num);

	SBI(ILI9341_PORT, ILI9341_CS);//CS_IDLE;
	//SPI_END;
}

inline void Display_Clear_Screen(uint16_t color)
{
	Display_Draw_Fill_Rect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, color);
}

// draws image from flash (PROGMEM)
inline void Display_Draw_Image_From_Progmem(uint16_t x, uint8_t y, uint16_t w, uint16_t h, const uint16_t * img16)
{
	if(x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) return;
	ILI9341_Set_Cursor_Optimized(x, y, x + w - 1, y + h - 1);

	uint32_t num = (uint32_t) w * h;
	uint16_t num16 = num>>3;
	uint8_t *img = (uint8_t *)img16;
	while(num16--)
	{
		SPI_Send_Word_Array(img, 16);
		img+=16;
	}
	uint8_t num8 = num & 0x7;
	while(num8--) { SPI_Send_Byte(pgm_read_byte(img+1)); SPI_Send_Byte(pgm_read_byte(img+0)); img+=2; }

	SBI(ILI9341_PORT, ILI9341_CS);//CS_IDLE;
	//SPI_END; // W naszym przypadku tylko my korzystamy z magistrali SPI wiêc raczej nie trzeba jej wy³¹czaæ bo na p³ytce nie bêdzie innych elementów po³¹czonych z SPI
}

void Display_Draw_Text_From_Progmem(uint16_t x, uint8_t y, const char * text, const uint16_t * font, uint16_t fontColor, uint16_t backgroundColor)
{
	uint16_t * character = 0;
	uint8_t characterIndex = 0;
	char currentChar = ' ';
	while(currentChar = pgm_read_byte(text++))
	{
		character = pgm_read_word(&font[currentChar - ' ']);
	
		uint8_t sizeX = pgm_read_byte(character);
		uint8_t sizeY = pgm_read_word(character + 1);

		if(x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT || sizeX <= 0 || sizeY <= 0) return;
		ILI9341_Set_Cursor_Optimized(x + (characterIndex * sizeX), y, x + (characterIndex * sizeX) + sizeX - 1, y + sizeY - 1);
	
		for(uint8_t i = 2; i <= sizeY + 1; i++)
		{
			for(uint8_t j = 0; j < sizeX; j++)
			{
				if(mask2[j] & pgm_read_byte(character + i)) SPI_Send_Word(fontColor >> 8, fontColor);
				else SPI_Send_Word(backgroundColor >> 8, backgroundColor);
			}
		}
		++characterIndex;
	}
	SBI(ILI9341_PORT, ILI9341_CS);//CS_IDLE;
}

void Display_Draw_Text(uint16_t x, uint8_t y, const char * text, const uint16_t * font, uint16_t fontColor, uint16_t backgroundColor)
{
	uint16_t * character = 0;
	uint8_t characterIndex = 0;
	char currentChar = ' ';
	while(currentChar = *text++)
	{
		character = pgm_read_word(&font[currentChar - ' ']);
		
		uint8_t sizeX = pgm_read_byte(character);
		uint8_t sizeY = pgm_read_word(character + 1);

		if(x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT || sizeX <= 0 || sizeY <= 0) return;
		ILI9341_Set_Cursor_Optimized(x + (characterIndex * sizeX), y, x + (characterIndex * sizeX) + sizeX - 1, y + sizeY - 1);
		
		for(uint8_t i = 2; i <= sizeY + 1; i++)
		{
			for(uint8_t j = 0; j < sizeX; j++)
			{
				if(mask2[j] & pgm_read_byte(character + i)) SPI_Send_Word(fontColor >> 8, fontColor);
				else SPI_Send_Word(backgroundColor >> 8, backgroundColor);
			}
		}
		++characterIndex;
	}
	SBI(ILI9341_PORT, ILI9341_CS);//CS_IDLE;
}

void Display_Set_Brightness(uint8_t brightness)
{
	ILI9341_Set_Brihness(brightness);
}