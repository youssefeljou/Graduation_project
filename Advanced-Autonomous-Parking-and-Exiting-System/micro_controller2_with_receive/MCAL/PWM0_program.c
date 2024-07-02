/*
 * PWM0_program.c
 *
 *  Created on: Nov 3, 2023
 *      Author: pc
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "PWM0_config.h"
#include "PWM0_interface.h"
#include "PWM0_private.h"
#include "DIO_interface.h"
#include "DIO_config.h"
#include "DIO_register.h"
#include <avr/io.h>
#include <avr/interrupt.h>
/*DEFINE  (MODE,PRESCALER) IN REGIESTER TCCR0*/
void PWM0_voidInit(u8 duty_cycle)
{
	u8 timer_value=((u16)(duty_cycle*255)/100);
	/*select the FASTPWM  mode */

	CLR_BIT(TCCR0,TCNT0);

	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);


	/*Clear OC0 on compare match, set OC0 at TOP (non inverted)*/
	SET_BIT(TCCR0,COM01);



	/*select the PRESACLER divided by 256*/

	SET_BIT(TCCR0,CS02);

	DIO_voidSetPinDirection(DIO_u8PORTB, DIO_PIN3_ID, DIO_u8OUTPUT);

	OCR0=timer_value;
}


