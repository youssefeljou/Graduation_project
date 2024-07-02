/*
 * servo_motor_1.c
 *
 *  Created on: Apr 5, 2024
 *      Author: Youmna
 */
#include "../MCAL/PWM1_interface.h"
#include "../LIB/STD_TYPES.h"

void Set_Angle_Servo_motor_1(u8 angle)
{
	if (angle == 0)
	{
		PWM1_voidInit(185);
	}
	else if (angle == 90)
	{
		PWM1_voidInit(312);
	}
	else if (angle == 45)
		{
			PWM1_voidInit(250);
		}
	else if (angle == 135)
		{
			PWM1_voidInit(140);
		}
}
