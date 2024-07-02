/*
 * PWM0_config.h
 *
 *  Created on: Nov 3, 2023
 *      Author: pc
 */

#ifndef PWM0_CONFIG_H_
#define PWM0_CONFIG_H_

#define    TIMER0_MODE              FAST_PWM

//#define    TIMER0_OCRVAL            256


/* PINS IN REGIESTER TCCR0 USE IN DEFINE (MODE,PRESCALER)*/
#define      CS00            0
#define      CS01            1
#define      CS02            2
#define      WGM01           3
#define      COM00           4
#define      COM01           5
#define      WGM00           6
#define      FOC0            7

#endif /* PWM0_CONFIG_H_ */
