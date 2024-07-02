/*
 * PWM_program.c
 *
 *  Created on: Sep 5, 2023
 *      Author: Active
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "PWM_config.h"
#include "PWM_interface.h"
#include "PWM_private.h"
#include "PWM_register.h"
#include "DIO_interface.h"
#include "DIO_config.h"


/*DEFINE  (MODE,PRESCALER) IN REGIESTER TCCR2*/
void PWM2_voidInit(void)
{
	/*select the FASTPWM  mode */

	SET_BIT(TCCR2 , WGM20);
	SET_BIT(TCCR2 , WGM21);

	/*select the PRESCALER divided by 1024 */

	SET_BIT(TCCR2,CS20);
	CLR_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);

   /* Set the Compare Match Value */
   OCR2 = TIMER2_OCRVAL;

/* Clear on Compare Match, Set at Top for OC0 Pin */
    SET_BIT(TCCR2 , COM21);
    CLR_BIT(TCCR2 , COM20);
	DIO_voidSetPinDirection(DIO_u8PORTD, DIO_PIN7_ID, DIO_PORT_OUTPUT);
}


void PWM2_voidSetOcrValue(u16 Copy_u16OcrValue)
{

	u8 timer_value ;
	timer_value =((u16)(Copy_u16OcrValue*255)/100);
	CLR_BIT(TCCR2,TCNT2);
	CLR_BIT(TCCR2,7);
	TCCR2 |= (1 << WGM20) | (1 << WGM21) | (1 << COM21) | (1 << CS22);
    OCR2=Copy_u16OcrValue;

}




