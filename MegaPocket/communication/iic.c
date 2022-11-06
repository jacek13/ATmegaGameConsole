/*
 * iic.c
 *
 * Created: 29.10.2022 14:54:53
 *  Author: Michal
 */ 

#include "iic.h"

static inline void IIC_Wait_For_TWINT_Flag_Set()
{
	while(!( TWCR & (1 << TWINT) ));
}

static inline void IIC_Wait_For_TWSTO_Flag_Set()
{
	while( TWCR & (1 << TWSTO) );
}

void IIC_init(uint16_t speed)
{
	speed = (F_CPU / speed / 100 - 16) / 2; // speed = TWBR*4^TWPS
	uint8_t prescaler = 0;
	while( speed > 0xFF ) ++prescaler, speed /= 4;
	TWSR = (TWSR & ( (1 << TWPS1) | (1 << TWPS0) )) | prescaler;
	TWBR = speed;
}

void IIC_Start()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	IIC_Wait_For_TWINT_Flag_Set();
	// if( TW_STATUS != TW_START ) // TODO error handling
}

void IIC_Stop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	IIC_Wait_For_TWSTO_Flag_Set();
}

void IIC_Write_Byte(uint8_t byte)
{
	TWDR = byte;
	TWCR = (1 << TWINT) | (1 << TWEN);
	IIC_Wait_For_TWINT_Flag_Set();
}

uint8_t IIC_Read_Byte(uint8_t ack)
{
	TWCR = (1 << TWINT) | (ack << TWEA) | (1 << TWEN);
	IIC_Wait_For_TWINT_Flag_Set();
	return TWDR;
}

void IIC_Write_Byte_Array(uint8_t * array, uint8_t size, uint8_t slaveAddress, uint8_t memoryAddress)
{
	IIC_Start();
	IIC_Write_Byte(slaveAddress);
	IIC_Write_Byte(memoryAddress);
	while(size--) IIC_Write_Byte(*array++);
	IIC_Stop();
}

void IIC_Read_Byte_Array(uint8_t * array, uint8_t size, uint8_t slaveAddress, uint8_t memoryAddress)
{
	IIC_Start();
	IIC_Write_Byte(slaveAddress);
	IIC_Write_Byte(memoryAddress);
	IIC_Start();
	IIC_Write_Byte(slaveAddress | 0x01);
	while(size--) *array++ = IIC_Read_Byte( size ? ACK : NACK );
	IIC_Stop();
}