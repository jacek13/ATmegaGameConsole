/*
 * rtc.c
 *
 * Created: 29.10.2022 15:54:11
 *  Author: Michal
 */ 

#include "rtc.h"

void DS1307_init(uint8_t controlRegister)
{
	// IIC must be enabled
	IIC_Start();
	IIC_Write_Byte(DS1307_DEVICE_ADDRESS_WRITE);
	IIC_Write_Byte(DS1307_CONTROL_REGISTER);
	IIC_Write_Byte(controlRegister);
	IIC_Stop();
}

void DS1307_Set_DateTime(DateTime * date)
{
	IIC_Start();
	IIC_Write_Byte(DS1307_DEVICE_ADDRESS_WRITE);
	IIC_Write_Byte(DS1307_ADDRESS_SECONDS);
	IIC_Write_Byte(date->Second);
	IIC_Write_Byte(date->Minute);
	IIC_Write_Byte(date->Hour);
	IIC_Write_Byte(date->DayOfWeek);
	IIC_Write_Byte(date->DayOfMonth);
	IIC_Write_Byte(date->Month);
	IIC_Write_Byte(date->Year);
	IIC_Stop();
}

void DS1307_Get_DateTime(DateTime * date)
{
	IIC_Start();
	IIC_Write_Byte(DS1307_DEVICE_ADDRESS_WRITE);
	IIC_Write_Byte(DS1307_ADDRESS_SECONDS);
	
	IIC_Start();
	IIC_Write_Byte(DS1307_DEVICE_ADDRESS_READ);
	date->Second = IIC_Read_Byte(ACK);
	date->Minute = IIC_Read_Byte(ACK);
	date->Hour = IIC_Read_Byte(ACK);
	date->DayOfWeek = IIC_Read_Byte(ACK);
	date->DayOfMonth = IIC_Read_Byte(ACK);
	date->Month = IIC_Read_Byte(ACK);
	date->Year = IIC_Read_Byte(NACK);
	IIC_Stop();
}

static inline uint8_t decToBCD(uint8_t dec) 
{ 
	return (((dec / 10) << 4) | (dec % 10));
}

static inline uint8_t GetMonthBCD()
{
	if(__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n') return 0x01;
	if(__DATE__[0] == 'F') return 0x02;
	if(__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r') return 0x03;
	if(__DATE__[0] == 'A' && __DATE__[1] == 'p') return 0x04;
	if(__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y') return 0x05;
	if(__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n') return 0x06;
	if(__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l') return 0x07;
	if(__DATE__[0] == 'A' && __DATE__[1] == 'u') return 0x08;
	if(__DATE__[0] == 'S') return 0x09;
	if(__DATE__[0] == 'O') return 0x10;
	if(__DATE__[0] == 'N') return 0x11;
	if(__DATE__[0] == 'D') return 0x12;
	return 0x01;
}

static inline uint8_t GetDayOfWeek()
{
	switch(__TIMESTAMP__[0])
	{
		case 'M': return 0x01; break;
		case 'T': return __TIMESTAMP__[1] == 'u' ? 0x02 : 0x04;
		case 'W': return 0x03;
		case 'F': return 0x05;
		case 'S': return __TIMESTAMP__[1] == 'a' ? 0x06 : 0x07;
	}
	return 0x01;
}

static inline uint8_t GetTimeData(DateTimeIndexes index)
{
	switch(index)
	{
		case SECOND: index = 6; break;
		case MINUTE: index = 3; break;
		case HOUR: index = 0; break;
		default: index = 0; break;
	}
	uint8_t dozens = (__TIME__[index] - '0') * 10;
	uint8_t units = (__TIME__[++index] - '0');
	return decToBCD(dozens + units);
}

static inline uint8_t GetDateData(DateTimeIndexes index)
{
	uint8_t dozens, units;
	
	switch(index)
	{
		case YEAR: index = 9; break;
		case DAY_OF_MONTH: index = 4; break;
		case MONTH: index = 0; break;
		default: index = 0; break;
	}
	
	if(index)
	{
		dozens =  __DATE__[index] != ' ' ? (__DATE__[index] - '0') * 10 : 0;
		units = (__DATE__[++index] - '0');
	}
	else
	{
		return GetMonthBCD();
	}
	return decToBCD(dozens + units);
}

void DS1307_FillDataWithCompileDateTime(DateTime * date)
{
	date->Second = GetTimeData(SECOND);
	date->Minute = GetTimeData(MINUTE);
	date->Hour = GetTimeData(HOUR);
	date->DayOfWeek = GetDayOfWeek();
	date->DayOfMonth = GetDateData(DAY_OF_MONTH);
	date->Month = GetDateData(MONTH);
	date->Year = GetDateData(YEAR);
}