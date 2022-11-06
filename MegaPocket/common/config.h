/*
 * config.h
 *
 * Created: 15.10.2022 20:32:54
 *  Author: Michal
 */ 

#ifndef CONFIG_H_
#define CONFIG_H_

//#define USE_HARDWARE_SPI
#define USE_USART_MSPIM

#ifdef USE_USART_MSPIM
#define USART_BAUDRATE 1000000
#define USART_CALCULATE_BAUDRATE (F_CPU/16/USART_BAUDRATE - 1)
#endif

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

#ifdef USE_HARDWARE_SPI
	#define ILI9341_PORT PORTB
	#define ILI9341_DIN PB3
	#define ILI9341_CLK PB5
	#define ILI9341_CS PB2
	#define ILI9341_DC PB0
	#define ILI9341_RST PB1
	//TODO ILI9341_BL
#else if USE_USART_MSPIM
	#define ILI9341_PORT PORTD
	#define ILI9341_DIN PD1
	#define ILI9341_CLK PD4
	#define ILI9341_CS PD2
	#define ILI9341_DC PD5
	#define ILI9341_RST PD6
	#define ILI9341_BL PD3
#endif

#endif /* CONFIG_H_ */