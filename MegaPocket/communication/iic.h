/*
 * iic.h
 *
 * Created: 29.10.2022 14:54:40
 *  Author: Michal
 */ 

#ifndef IIC_H_
#define IIC_H_

#include <util/twi.h>

#define IIC_SPEED (50000/100)
#define NACK 0
#define ACK 1

void IIC_init(uint16_t speed);

void IIC_Start();

void IIC_Stop();

void IIC_Write_Byte(uint8_t byte);

uint8_t IIC_Read_Byte(uint8_t ack);

void IIC_Write_Byte_Array(uint8_t * array, uint8_t size, uint8_t slaveAddress, uint8_t memoryAddress);

void IIC_Read_Byte_Array(uint8_t * array, uint8_t size, uint8_t slaveAddress, uint8_t memoryAddress);

#endif /* IIC_H_ */