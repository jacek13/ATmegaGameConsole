/*
 * bitManipulation.h
 *
 * Created: 15.10.2022 20:22:29
 *  Author: Michal
 */ 

#ifndef BITMANIPULATION_H_
#define BITMANIPULATION_H_

/** Macros for bit manipulation */
#define SBI(port, pin) (port) |= _BV(pin)
#define CBI(port, pin) (port) &= ~_BV(pin)
#define TBI(port, pin) (port) ^= _BV(pin)

#endif /* BITMANIPULATION_H_ */