/*
 * ultra_sonic.c
 *
 *  Created on: Oct 16, 2022
 *      Author: Youmna
 */
#include "ultra_sonic.h"

#include <util/delay.h>
#include <avr/io.h>
#include "../LIB/BIT_MATH.h" /* For GET_BIT Macro */
#include "../MCAL/icu.h"
#include "../MCAL/DIO_config.h"


f64 distance=0;
//f64 distance2=0;
//f64 distance3=0;
u8 g_edgeCount = 0;
//u8 g_edgeCount2 = 0;
//u8 g_edgeCount3 = 0;
u16 g_timeHigh=0;
//u16 g_timeHigh2=0;
//u16 g_timeHigh3=0;
void Ultrasonic_edgeProcessing(void)
{

	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		g_timeHigh = Icu_getInputCaptureValue();
		Icu_setEdgeDetectionType(RISING);
		g_edgeCount=0;
	}

}
/*
void Ultrasonic_edgeProcessing2(void)
{

	g_edgeCount2++;
	if(g_edgeCount2 == 1)
	{
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount2 == 2)
	{
		g_timeHigh2 = Icu_getInputCaptureValue();
		Icu_setEdgeDetectionType(RISING);
		g_edgeCount2=0;
	}

}
void Ultrasonic_edgeProcessing3(void)
{

	g_edgeCount3++;
	if(g_edgeCount3 == 1)
	{
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount3 == 2)
	{
		g_timeHigh3 = Icu_getInputCaptureValue();
		Icu_setEdgeDetectionType(RISING);
		g_edgeCount3=0;
	}

}
*/

void Ultrasonic_init(void)
{
	/* Create configuration structure for ICU driver */
	Icu_Clock Icu_Config_ultrasonic = {F_CPU_8,RISING};
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	Icu_init(&Icu_Config_ultrasonic);
	DIO_voidSetPinDirection(TRIG_PORT_ID, TRIG_PIN_ID, DIO_u8OUTPUT);
	DIO_voidSetPinValue(TRIG_PORT_ID, TRIG_PIN_ID,DIO_u8LOW);

}
/*
void Ultrasonic2_init(void)
{
	/* Create configuration structure for ICU driver */
/*
	Icu_Clock Icu_Config_ultrasonic2 = {F_CPU_8,RISING};
	Icu_setCallBack(Ultrasonic_edgeProcessing2);
	Icu_init(&Icu_Config_ultrasonic2);
	DIO_voidSetPinDirection(TRIG2_PORT_ID, TRIG2_PIN_ID, DIO_u8OUTPUT);
	DIO_voidSetPinValue(TRIG2_PORT_ID, TRIG2_PIN_ID,DIO_u8LOW);

}
void Ultrasonic3_init(void)
{
	/* Create configuration structure for ICU driver */
/*
	Icu_Clock Icu_Config_ultrasonic3 = {F_CPU_8,RISING};
	Icu_setCallBack(Ultrasonic_edgeProcessing3);
	Icu_init(&Icu_Config_ultrasonic3);
	DIO_voidSetPinDirection(TRIG3_PORT_ID, TRIG3_PIN_ID, DIO_u8OUTPUT);
	DIO_voidSetPinValue(TRIG3_PORT_ID, TRIG3_PIN_ID,DIO_u8LOW);

}
*/

void Ultrasonic_Trigger(void)
{
	DIO_voidSetPinValue(TRIG_PORT_ID, TRIG_PIN_ID,DIO_u8HIGH);
	_delay_us(10);
	DIO_voidSetPinValue(TRIG_PORT_ID, TRIG_PIN_ID,DIO_u8LOW);
}
/*
void Ultrasonic2_Trigger(void)
{
	DIO_voidSetPinValue(TRIG2_PORT_ID, TRIG2_PIN_ID,DIO_u8HIGH);
	_delay_us(10);
	DIO_voidSetPinValue(TRIG2_PORT_ID, TRIG2_PIN_ID,DIO_u8LOW);
}
void Ultrasonic3_Trigger(void)
{
	DIO_voidSetPinValue(TRIG3_PORT_ID, TRIG3_PIN_ID,DIO_u8HIGH);
	_delay_us(10);
	DIO_voidSetPinValue(TRIG3_PORT_ID, TRIG3_PIN_ID,DIO_u8LOW);
}
*/
 u16 Ultrasonic_readDistance(void)
 {

	 Ultrasonic_Trigger();
	 /*Calculation (distance in cm)
Sound velocity = 340.00 m/s = 34000 cm/s
The distance of Object (in cm) = 340000∗Time
2
 = 17000 * Time

Now, here we have selected an internal 8MHz oscillator frequency for ATmega16, with
Prescaler F_CPU/8 for timer frequency. Then time to execute 1 instruction is 1 us.
So, the timer gets incremented after 1 us time elapse.
= 17000 x (TIMER value) x 1 x 10^-6 cm
= 0.017 x (TIMER value) cm
= (TIMER value) / 58.8 cm
Note TIMER VALUE is the pulse width time calculated by the ICU
*/

	 distance=(float)((g_timeHigh/57.5));
	 _delay_ms(50);
	 Icu_DeInit();
	 return distance;

 }
/*
 u16 Ultrasonic2_readDistance(void)
  {

 	 Ultrasonic2_Trigger();
 	 /*Calculation (distance in cm)
 Sound velocity = 340.00 m/s = 34000 cm/s
 The distance of Object (in cm) = 340000∗Time
 2
  = 17000 * Time

 Now, here we have selected an internal 8MHz oscillator frequency for ATmega16, with
 Prescaler F_CPU/8 for timer frequency. Then time to execute 1 instruction is 1 us.
 So, the timer gets incremented after 1 us time elapse.
 = 17000 x (TIMER value) x 1 x 10^-6 cm
 = 0.017 x (TIMER value) cm
 = (TIMER value) / 58.8 cm
 Note TIMER VALUE is the pulse width time calculated by the ICU
 */
/*
 	 distance2=(float)((g_timeHigh2/57.5));
 	 _delay_ms(50);
 	Icu_DeInit();
 	 return distance2;

  }


 u16 Ultrasonic3_readDistance(void)
  {

 	 Ultrasonic3_Trigger();
 	 /*Calculation (distance in cm)
 Sound velocity = 340.00 m/s = 34000 cm/s
 The distance of Object (in cm) = 340000∗Time
 2
  = 17000 * Time

 Now, here we have selected an internal 8MHz oscillator frequency for ATmega16, with
 Prescaler F_CPU/8 for timer frequency. Then time to execute 1 instruction is 1 us.
 So, the timer gets incremented after 1 us time elapse.
 = 17000 x (TIMER value) x 1 x 10^-6 cm
 = 0.017 x (TIMER value) cm
 = (TIMER value) / 58.8 cm
 Note TIMER VALUE is the pulse width time calculated by the ICU
 */
/*
 	 distance3=(float)((g_timeHigh3/57.5));
 	 _delay_ms(50);
 	Icu_DeInit();
 	 return distance3;

  }

*/

