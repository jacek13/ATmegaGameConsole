/*
 * rtc.h
 *
 * Created: 29.10.2022 15:48:41
 *  Author: Michal
 */ 


#ifndef RTC_H_
#define RTC_H_

#include "../communication/iic.h"

#define DS1307_DEVICE_ADDRESS_READ 0xD1
#define DS1307_DEVICE_ADDRESS_WRITE 0xD0
#define DS1307_ADDRESS_SECONDS 0x00
#define DS1307_ADDRESS_MINUTES 0x01
#define DS1307_ADDRESS_HOURS 0x02
#define DS1307_ADDRESS_DAY 0x03
#define DS1307_ADDRESS_DATE 0x04
#define DS1307_ADDRESS_MONTH 0x05
#define DS1307_ADDRESS_YEAR 0x06
#define DS1307_CONTROL_REGISTER 0x07
#define DS1307_ADDRESS_START_OF_EXTRA_RAM 0x08

typedef enum
{
	SECOND = 0,
	MINUTE,
	HOUR,
	DAY_OF_WEEK,
	DAY_OF_MONTH,
	MONTH,
	YEAR
}  DateTimeIndexes;

typedef struct
{
	uint8_t Second,
			Minute,
			Hour,
			DayOfWeek,
			DayOfMonth,
			Month,
			Year;
} DateTime;

void DS1307_init(uint8_t controlRegister);

void DS1307_Set_DateTime(DateTime * date);

void DS1307_Get_DateTime(DateTime * date);

void DS1307_FillDataWithCompileDateTime(DateTime * date);

#endif /* RTC_H_ */