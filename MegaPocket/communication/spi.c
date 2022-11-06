/*
 * spi.c
 *
 * Created: 15.10.2022 20:06:56
 *  Author: Michal
 */ 

#include "spi.h"

inline void SPI_init()
{
	#ifdef USE_HARDWARE_SPI
	DDRB = 0b00111111;// ustawienie kierunku portu B zgodnie ze schematem
	// PB7 = undefined
	// PB6 = undefined
	// PB5 = SPI_CLK	-> output
	// PB4 = BL			-> output (TODO ZMIANA NA PC0 bo tutaj BL bêdzie sterowane analogowo)
	// PB3 = SPI_MOSI	-> output
	// PB2 = SPI_SS		-> output
	// PB1 = RST		-> output
	// PB0 = DC			-> output LED
	
	//PORTB &= ~(1 << PB2); // CS set to low for activating ILI9341
	CBI(PORTB, ILI9341_CS);
	
	SPCR = (1 << SPE) | (1 << MSTR); // enable SPI and set MCU as Master for generating clock wave
	SPSR |= (1 << SPI2X); // enable fastest SPI transmision
	
	#else if USE_USART_MSPIM
	
	DDRD = _BV(ILI9341_RST) | _BV(ILI9341_DC) | _BV(ILI9341_CLK) | _BV(ILI9341_BL) | _BV(ILI9341_CS) | _BV(ILI9341_DIN);
	ILI9341_PORT |= _BV(ILI9341_CS);
	//DDRD |= _BV(PD2);
	
	UBRR0 = 0;								// Clear UBRRn register for UART init (as datasheet said)
	UCSR0C = _BV(UMSEL01) | _BV(UMSEL00);	// UART set to MSPIM
	UCSR0C &= ~(1 << UDORD0);				// MSB first
	UCSR0B = (1 << TXEN0);					// Enable only transmit
	UCSR0A |= _BV(U2X0);					// Double up transmission

	UBRR0 = USART_CALCULATE_BAUDRATE;		// Set Baud Rate
	CBI(ILI9341_PORT, ILI9341_CS);					// ILI9341 Chip select
	#endif
}

inline void SPI_Send_Byte(uint8_t byte)
{
	#ifdef USE_HARDWARE_SPI
	SPDR = byte;
	while(!(SPSR & (1 << SPIF)));
	#else if USE_USART_MSPIM
	UCSR0A = (1 << TXC0);
	while(!(UCSR0A & _BV(UDRE0)));
	UDR0 = byte;
	while(!(UCSR0A & (1 << TXC0)));
	#endif
}

inline void SPI_Send_Word(uint8_t MSByte, uint8_t LSByte)
{
	#ifdef USE_HARDWARE_SPI
	//TODO not implemented
	//SPDR = byte;
	//while(!(SPSR & (1 << SPIF)));
	#else if USE_USART_MSPIM
	UCSR0A = (1 << TXC0);
	while(!(UCSR0A & _BV(UDRE0)));
	UDR0 = MSByte;
	while(!(UCSR0A & _BV(UDRE0)));
	UDR0 = LSByte;
	while(!(UCSR0A & (1 << TXC0)));
	#endif
}

inline void SPI_Send_Byte_Array(uint8_t * array, uint16_t size)
{
	#ifdef USE_HARDWARE_SPI
	//TODO not implemented
	//SPDR = byte;
	//while(!(SPSR & (1 << SPIF)));
	#else if USE_USART_MSPIM
	
	// Clear TXC0 Flag
	UCSR0A = (1 << TXC0);
	
	while(size > 0)
	{
		while(!(UCSR0A & _BV(UDRE0)));
		UDR0 = pgm_read_byte(array++);
		--size;
	}
	
	while(!(UCSR0A & (1 << TXC0)));
	#endif
}

inline void SPI_Send_Word_Array(uint8_t * array, uint16_t size)
{
	#ifdef USE_HARDWARE_SPI
	//TODO not implemented
	//SPDR = byte;
	//while(!(SPSR & (1 << SPIF)));
	#else if USE_USART_MSPIM
	
	// Clear TXC0 Flag
	UCSR0A = (1 << TXC0);
	
	for(uint16_t i = 0; i < size; i += 2)
	{
		while(!(UCSR0A & _BV(UDRE0)));
		UDR0 = pgm_read_byte(array + 1);
		while(!(UCSR0A & _BV(UDRE0)));
		UDR0 = pgm_read_byte(array);
		array += 2;
	}
	
	while(!(UCSR0A & (1 << TXC0)));
	
	#endif
}