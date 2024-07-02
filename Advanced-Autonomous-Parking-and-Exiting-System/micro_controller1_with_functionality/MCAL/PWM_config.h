/*
 * PWM_config.h
 *
 *  Created on: Sep 5, 2023
 *      Author: Active
 */

#ifndef PWM_CONFIG_H_
#define PWM_CONFIG_H_

#define    TIMER2_MODE              FAST_PWM

#define    TIMER2_OCRVAL            64

/* PINS IN REGIESTER TCCR2 USE IN DEFINE (MODE,PRESCALER)*/
#define      CS20            0
#define      CS21            1
#define      CS22            2
#define      WGM21           3
#define      COM20           4
#define      COM21           5
#define      WGM20           6
#define      FOC2            7

#endif /* PWM_CONFIG_H_ */
