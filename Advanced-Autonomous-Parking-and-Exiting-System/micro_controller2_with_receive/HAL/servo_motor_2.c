#include "../MCAL/PWM0_interface.h"
#include "../LIB/STD_TYPES.h"

void Set_Angle_Servo_motor_2(u8 angle)
{
	if (angle == 0)
	{
		PWM0_voidInit(7);
	}
	else if(angle ==90)
	{
		PWM0_voidInit(18.7);
	}
}
