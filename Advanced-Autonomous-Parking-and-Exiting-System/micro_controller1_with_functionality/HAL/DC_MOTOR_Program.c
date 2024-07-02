

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO_config.h"
#include "../MCAL/DIO_interface.h"
#include "DC_MOTOR_Config.h"
#include "DC_MOTOR_Interface.h"

//MOTOR 1 Functions 

void DC_MOTOR1_Init(void)
{
	DIO_voidSetPinDirection(DIO_u8PORTA,DC_MOTOR1_PIN0,DIO_u8OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTA,DC_MOTOR1_PIN1,DIO_u8OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_PIN7_ID,DIO_u8OUTPUT);/*PWM2 PIN IN MC (OC2) */
}

void DC_MOTOR1_voidRotateClockwise(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR1_PIN0 , DIO_u8LOW);

	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR1_PIN1 , DIO_u8HIGH);


}
void DC_MOTOR1_voidRotateAntiClockwise(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR1_PIN1 , DIO_u8LOW);
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR1_PIN0 , DIO_u8HIGH);


}
void DC_MOTOR1_voidStop(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR1_PIN0 , DIO_u8LOW);
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR1_PIN1 , DIO_u8LOW);

}

//MOTOR 2 Functions 

void DC_MOTOR2_Init(void)
{
	DIO_voidSetPinDirection(DIO_u8PORTA,DC_MOTOR2_PIN2,DIO_u8OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTA,DC_MOTOR2_PIN3,DIO_u8OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_PIN7_ID,DIO_u8OUTPUT);/*PWM2 PIN IN MC (OC2) */

}

void DC_MOTOR2_voidRotateClockwise(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR2_PIN2 , DIO_u8LOW);

	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR2_PIN3 , DIO_u8HIGH);


}
void DC_MOTOR2_voidRotateAntiClockwise(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR2_PIN3 , DIO_u8LOW);
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR2_PIN2 , DIO_u8HIGH);




}
void DC_MOTOR2_voidStop(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR2_PIN2 , DIO_u8LOW);
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR2_PIN3 , DIO_u8LOW);

}
//MOTOR 3 Functions 

void DC_MOTOR3_Init(void)
{
	DIO_voidSetPinDirection(DIO_u8PORTA,DC_MOTOR3_PIN4 ,DIO_u8OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTA,DC_MOTOR3_PIN5,DIO_u8OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_PIN7_ID,DIO_u8OUTPUT);/*PWM2 PIN IN MC (OC2) */

}

void DC_MOTOR3_voidRotateClockwise(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR3_PIN4 , DIO_u8LOW);

	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR3_PIN5 , DIO_u8HIGH);


}
void DC_MOTOR3_voidRotateAntiClockwise(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR3_PIN5 , DIO_u8LOW);
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR3_PIN4 , DIO_u8HIGH);


}
void DC_MOTOR3_voidStop(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR3_PIN4 , DIO_u8LOW);
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR3_PIN5 , DIO_u8LOW);

}

//MOTOR 4 Functions 

void DC_MOTOR4_Init(void)
{
	DIO_voidSetPinDirection(DIO_u8PORTA,DC_MOTOR4_PIN6 ,DIO_u8OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTA,DC_MOTOR4_PIN7,DIO_u8OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_PIN7_ID,DIO_u8OUTPUT);/*PWM2 PIN IN MC (OC2) */

}

void DC_MOTOR4_voidRotateClockwise(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR4_PIN6 , DIO_u8LOW);

	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR4_PIN7 , DIO_u8HIGH);


}
void DC_MOTOR4_voidRotateAntiClockwise(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR4_PIN7 , DIO_u8LOW);
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR4_PIN6 , DIO_u8HIGH);


}
void DC_MOTOR4_voidStop(void)
{
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR4_PIN6 , DIO_u8LOW);
	DIO_voidSetPinValue(DC_MOTOR_PORT , DC_MOTOR4_PIN7 , DIO_u8LOW);

}










