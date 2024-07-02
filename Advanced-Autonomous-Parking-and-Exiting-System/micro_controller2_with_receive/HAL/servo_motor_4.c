#include "../MCAL/PWM2_interface.h"
#include "../LIB/STD_TYPES.h"

void Set_Angle_Servo_motor_4(u8 angle)
{
	if (angle == 0)
	{
		PWM2_voidInit(17);
	}
	else if(angle ==90)
	{
		PWM2_voidInit(4);
	}
	else if(angle ==45)
		{
			PWM2_voidInit(21);
		}
		else if(angle ==135)
		{
			PWM2_voidInit(12);
		}
}
