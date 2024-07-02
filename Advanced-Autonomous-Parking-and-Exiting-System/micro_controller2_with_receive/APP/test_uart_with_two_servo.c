/*
 * test_uart_with_two_servo.c
 *
 *  Created on: Apr 26, 2024
 *      Author: youss
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO_config.h"
#include "../MCAL/DIO_interface.h"

#include "../MCAL/GIE_interface.h"

#include "../MCAL/PWM2_interface.h"
#include "../MCAL/PWM0_interface.h"
#include "../MCAL/PWM1_interface.h"

#include "../HAL/ultra_sonic.h"

//include servo driver
#include "../HAL/servo_motor_1.h"
#include "../HAL/servo_motor_2.h"
#include "../HAL/servo_motor_4.h"
//#include "../HAL/SERVO_MOTOR_Interface.h"

#include "../MCAL/UART_interface.h"

#include <avr/delay.h>
# define F_CPU 8000000UL
#define BACK_ULTRASONIC_DISTANCE	1

volatile u16 Ultra_Back_Dis2;
int main()
{
	GIE_voidEnable();
	//D0 set it input to recieve data (Rx)
	DIO_voidSetPinDirection(DIO_u8PORTD,0,DIO_u8INPUT);
	//D1 set it output to send data (Tx)
	DIO_voidSetPinDirection(DIO_u8PORTD,1,DIO_u8OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTA ,0,DIO_u8OUTPUT );
	UART_voidInit();
	UART_voidReceiverEnable();
	UART_voidTransmitterEnable();
	Set_Angle_Servo_motor_1(0);
	Set_Angle_Servo_motor_2(0);
	Set_Angle_Servo_motor_4(0);
	u8 count ,flag;

	while(1)
	{
		 flag=UART_u8ReceiveData();

		if (flag==45)
		{
			Set_Angle_Servo_motor_1(45);
			Set_Angle_Servo_motor_4(45);


		}
		else if(flag==0)
		{
			Set_Angle_Servo_motor_1(0);
			Set_Angle_Servo_motor_2(0);
			Set_Angle_Servo_motor_4(0);
		}
		else if (flag==135)
		{
			Set_Angle_Servo_motor_1(135);
			Set_Angle_Servo_motor_4(135);

		}
		else if (flag==90)
		{
			Set_Angle_Servo_motor_1(90);
			Set_Angle_Servo_motor_2(90);
			Set_Angle_Servo_motor_4(90);

		}
		else if(flag==BACK_ULTRASONIC_DISTANCE)
		{
			while(count<4)
			{
				Ultrasonic_init();
				_delay_ms(500);
				Ultra_Back_Dis2=Ultrasonic_readDistance();
				count++;
			}
			count =0;
			UART_voidSendData(Ultra_Back_Dis2);
		}
	}
}
