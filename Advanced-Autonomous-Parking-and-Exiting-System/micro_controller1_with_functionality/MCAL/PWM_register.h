/*
 * PWM_register.h
 *
 *  Created on: Sep 5, 2023
 *      Author: Active
 */

#ifndef PWM_REGISTER_H_
#define PWM_REGISTER_H_

#define TCCR2 		*((volatile u8*)(0x45))
#define TIMSK 		*((volatile u8*)(0x59))
#define TCNT2 		*((volatile u8*)(0x44))
#define OCR2 		*((volatile u8*)(0x43))
#define TIFR 		*((volatile u8*)(0x58))
#define ASSR        *((volatile u8*)(0x42))




#endif /* PWM_REGISTER_H_ */
