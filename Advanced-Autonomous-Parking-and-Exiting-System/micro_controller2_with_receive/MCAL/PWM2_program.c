/*
 * PWM2_program.c
 *
 *  Created on: Nov 3, 2023
 *      Author: pc
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "PWM2_config.h"
#include "PWM2_interface.h"
#include "PWM2_private.h"
#include "DIO_interface.h"
#include "DIO_config.h"
#include "DIO_register.h"
#include <avr/io.h>
#include <avr/interrupt.h>
/*DEFINE  (MODE,PRESCALER) IN REGIESTER TCCR0*/
void PWM2_voidInit(u8 duty_cycle)
{
	u8 timer_value=((u16)(duty_cycle*255)/100);
	/*select the FASTPWM  mode */

	CLR_BIT(TCCR2,TCNT2);
	SET_BIT(TCCR2,WGM21);
	SET_BIT(TCCR2,WGM20);

	/*Clear OC0 on compare match, set OC0 at TOP (non inverted)*/

	CLR_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);



	/*select the PRESACLER divided by 256*/

	SET_BIT(TCCR2,CS22);
	SET_BIT(TCCR2,CS21);

	DIO_voidSetPinDirection(DIO_u8PORTD, DIO_PIN7_ID, DIO_u8OUTPUT);

	OCR2=timer_value;
}


