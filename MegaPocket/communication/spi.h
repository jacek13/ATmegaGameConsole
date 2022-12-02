/*
 * spi.h
 *
 * Created: 15.10.2022 20:06:42
 *  Author: Michal
 */ 

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "../common/bitManipulation.h"
#include "../common/config.h"

void SPI_init();

void SPI_Send_Byte(uint8_t byte);

void SPI_Send_Word(uint8_t MSByte, uint8_t LSByte);

void SPI_Send_Byte_Array(uint8_t * array, uint16_t size);

void SPI_Send_Word_Array(uint8_t * array, uint16_t size);

#endif /* SPI_H_ */