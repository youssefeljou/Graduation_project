/*
 * PWM0_regiester.h
 *
 *  Created on: Nov 3, 2023
 *      Author: pc
 */

#ifndef PWM0_REGIESTER_H_
#define PWM0_REGIESTER_H_

#define TCCR0  *((volatile u8*)(0x53))
#define TCNT0  *((volatile u8*)(0x52))
#define OCR0   *((volatile u8*)(0x5C))
#define TIMSK  *((volatile u8*)(0x59))
#define TIFR   *((volatile u8*)(0x58))

#endif /* PWM0_REGIESTER_H_ */
