/*
 * ili9341.c
 *
 * Created: 06.10.2022 19:24:55
 *  Author: Michal
 */ 

#include "ili9341.h"

inline void ILI9341_Reset()
{
	CBI(ILI9341_PORT, ILI9341_RST);
	_delay_us(20);
	SBI(ILI9341_PORT, ILI9341_RST);
	_delay_ms(200);
}

inline void ILI9341_Write_Command(uint8_t command)
{
	CBI(ILI9341_PORT, ILI9341_CS);
	CBI(ILI9341_PORT, ILI9341_DC);
	SPI_Send_Byte(command);
}

inline void ILI9341_Write_Command_With_Data_Word(uint8_t command, uint16_t data)
{
	ILI9341_Write_Command(command);
	SPI_Send_Byte((data >> 8) & 0xFF);	// HByte
	SPI_Send_Byte(data);				// LByte
	SBI(ILI9341_PORT, ILI9341_CS);
}

inline void ILI9341_Write_Data_Byte(uint8_t data)
{
	CBI(ILI9341_PORT, ILI9341_CS);
	SBI(ILI9341_PORT, ILI9341_DC);
	SPI_Send_Byte(data);
	SBI(ILI9341_PORT, ILI9341_CS);
}

inline void ILI9341_Write_Data_Word(uint16_t data)
{
	CBI(ILI9341_PORT, ILI9341_CS);
	SBI(ILI9341_PORT, ILI9341_DC);
	SPI_Send_Byte((data >> 8) & 0xFF);	// HByte
	SPI_Send_Byte(data);				// LByte
	SBI(ILI9341_PORT, ILI9341_CS);
}

inline void ILI9341_init(uint8_t brightness)
{
	if (brightness)
	{
		TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
		TCCR2B = (1 << WGM22) | (1 << CS21);
		OCR2A = brightness;
	}
	
	//ILI9341_Write_Command(ILI9341_RESET);
	ILI9341_Reset();
	ILI9341_Write_Command(ILI9341_SLEEP_OUT); //Sleep out
	
	ILI9341_Write_Command(ILI9341_POWER_CONTROL_B);
	ILI9341_Write_Data_Byte(ILI9341_NOP);
	ILI9341_Write_Data_Byte(ILI9341_POWER_CONTROL_2);
	ILI9341_Write_Data_Byte(ILI9341_PARTIAL_AREA);
	ILI9341_Write_Command(ILI9341_POWER_ON_SEQUENCE_CONTROL);
	ILI9341_Write_Data_Byte(0x64);
	ILI9341_Write_Data_Byte(0x03);
	ILI9341_Write_Data_Byte(0X12);
	ILI9341_Write_Data_Byte(0X81);
	ILI9341_Write_Command(ILI9341_DRIVER_TIMING_CONTROL_A);
	ILI9341_Write_Data_Byte(0x85);
	ILI9341_Write_Data_Byte(ILI9341_NOP);
	ILI9341_Write_Data_Byte(0x79);
	ILI9341_Write_Command(ILI9341_POWER_CONTROL_A);
	ILI9341_Write_Data_Byte(0x39);
	ILI9341_Write_Data_Byte(0x2C);
	ILI9341_Write_Data_Byte(ILI9341_NOP);
	ILI9341_Write_Data_Byte(0x34);
	ILI9341_Write_Data_Byte(0x02);
	ILI9341_Write_Command(ILI9341_PUMP_RATIO_CONTROL);
	ILI9341_Write_Data_Byte(0x20);
	ILI9341_Write_Command(ILI9341_DRIVER_TIMING_CONTROL_B);
	ILI9341_Write_Data_Byte(ILI9341_NOP);
	ILI9341_Write_Data_Byte(ILI9341_NOP);
	ILI9341_Write_Command(ILI9341_POWER_CONTROL_1); //Power control
	ILI9341_Write_Data_Byte(0x1D); //VRH[5:0]
	ILI9341_Write_Command(ILI9341_POWER_CONTROL_2); //Power control
	ILI9341_Write_Data_Byte(0x12); //SAP[2:0];BT[3:0]
	ILI9341_Write_Command(ILI9341_VCOM_CONTROL_1); //VCM control
	ILI9341_Write_Data_Byte(0x33);
	ILI9341_Write_Data_Byte(0x3F);
	ILI9341_Write_Command(ILI9341_VCOM_CONTROL_2); //VCM control
	ILI9341_Write_Data_Byte(0x92);
	ILI9341_Write_Command(ILI9341_PIXEL_FORMAT_SET); // Memory Access Control
	ILI9341_Write_Data_Byte(0x55);
	ILI9341_Write_Command(ILI9341_MEMORY_ACCESS_CONTROL); // Memory Access Control
	ILI9341_Write_Data_Byte(0xB8); // Bits set to '1' => MY, MV, ML, BGR => (0,0) in left upper corner, horizontal display mode
	ILI9341_Write_Command(ILI9341_FRAME_RATE_CONTROL_IN_NORMAL_MODE_FULL_COLORS);
	ILI9341_Write_Data_Byte(ILI9341_NOP);
	ILI9341_Write_Data_Byte(0x12);
	ILI9341_Write_Command(ILI9341_DISPLAY_FUNCTION_CONTROL); // Display Function Control
	ILI9341_Write_Data_Byte(0x0A);
	ILI9341_Write_Data_Byte(0xA2);

	ILI9341_Write_Command(ILI9341_SET_TEAR_SCANLINE);
	ILI9341_Write_Data_Byte(0x02);

	ILI9341_Write_Command(ILI9341_ENABLE_3G); // 3Gamma Function Disable
	ILI9341_Write_Data_Byte(ILI9341_NOP);
	ILI9341_Write_Command(ILI9341_GAMMA_SET); //Gamma curve selected
	ILI9341_Write_Data_Byte(0x01);
	ILI9341_Write_Command(ILI9341_POSITIVE_GAMMA_CORRECTION); //Set Gamma
	ILI9341_Write_Data_Byte(0x0F);
	ILI9341_Write_Data_Byte(0x22);
	ILI9341_Write_Data_Byte(0x1C);
	ILI9341_Write_Data_Byte(0x1B);
	ILI9341_Write_Data_Byte(0x08);
	ILI9341_Write_Data_Byte(0x0F);
	ILI9341_Write_Data_Byte(0x48);
	ILI9341_Write_Data_Byte(0xB8);
	ILI9341_Write_Data_Byte(0x34);
	ILI9341_Write_Data_Byte(0x05);
	ILI9341_Write_Data_Byte(0x0C);
	ILI9341_Write_Data_Byte(0x09);
	ILI9341_Write_Data_Byte(0x0F);
	ILI9341_Write_Data_Byte(0x07);
	ILI9341_Write_Data_Byte(ILI9341_NOP);
	ILI9341_Write_Command(ILI9341_NEGATIVE_GAMMA_CORRECTION); //Set Gamma
	ILI9341_Write_Data_Byte(ILI9341_NOP);
	ILI9341_Write_Data_Byte(0x23);
	ILI9341_Write_Data_Byte(0x24);
	ILI9341_Write_Data_Byte(0x07);
	ILI9341_Write_Data_Byte(0x10);
	ILI9341_Write_Data_Byte(0x07);
	ILI9341_Write_Data_Byte(0x38);
	ILI9341_Write_Data_Byte(0x47);
	ILI9341_Write_Data_Byte(0x4B);
	ILI9341_Write_Data_Byte(0x0A);
	ILI9341_Write_Data_Byte(0x13);
	ILI9341_Write_Data_Byte(0x06);
	ILI9341_Write_Data_Byte(ILI9341_PARTIAL_AREA);
	ILI9341_Write_Data_Byte(0x38);
	ILI9341_Write_Data_Byte(0x0F);
	ILI9341_Write_Command(ILI9341_DISPLAY_ON); //Display on
}

inline void ILI9341_Write_Word_Multiple_Times(uint16_t color, uint16_t numberOfWords)
{
	while(numberOfWords--) SPI_Send_Word(color >> 8, color);
}

/** Sets cursor and after that, enables writing to gram*/
inline void ILI9341_Set_Cursor_Optimized(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
	// optimized version
	CBI(ILI9341_PORT, ILI9341_CS); //CS_ACTIVE;
	//SPI_START;
	CBI(ILI9341_PORT, ILI9341_DC); //DC_COMMAND;
	SPI_Send_Byte(ILI9341_COLUMN_ADDRESS_SET); // writeSPI(ILI9341_CASET);
	SBI(ILI9341_PORT, ILI9341_DC); //DC_DATA;
	SPI_Send_Word(xs >> 8, xs), SPI_Send_Word(xe >> 8, xe);

	CBI(ILI9341_PORT, ILI9341_DC); //DC_COMMAND;
	SPI_Send_Byte(ILI9341_PAGE_ADDRESS_SET); //	writeSPI(ILI9341_PASET);
	SBI(ILI9341_PORT, ILI9341_DC); //DC_DATA;
	SPI_Send_Word(ys >> 8, ys), SPI_Send_Word(ye >> 8, ye);

	CBI(ILI9341_PORT, ILI9341_DC); //DC_COMMAND;
	SPI_Send_Byte(ILI9341_MEMORY_WRITE); //writeSPI(ILI9341_RAMWR);

	SBI(ILI9341_PORT, ILI9341_DC); //DC_DATA;
	// no CS_IDLE + SPI_END, DC_DATA to save memory
}

void ILI9341_Set_Brihness(uint8_t brightness)
{
	OCR2A = brightness;
}