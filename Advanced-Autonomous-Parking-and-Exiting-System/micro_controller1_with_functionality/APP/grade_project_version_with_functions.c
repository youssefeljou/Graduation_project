/*
 * main_GP.c
 *
 *  Created on: Nov 25, 2023
 *      Author: pc
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO_config.h"
#include "../MCAL/DIO_interface.h"
#include "../MCAL/GIE_interface.h"
#include "../MCAL/PWM0_interface.h"
#include "../MCAL/PWM_interface.h"
#include "../HAL/DC_MOTOR_Interface.h"
#include "../HAL/ultra_sonic.h"

#include "../MCAL/UART_interface.h"
#include <util/delay.h>
#include <avr/io.h>


#include "../HAL/servo_motor_3.h"


// #define Global variables
#define PWM_SPEED_OF_MOTOR_TO_PARK	150 //cm
#define PWM_SPEED_OF_MOTOR_TO_CHECK 160 //cm
#define REAL_SPEED_OF_MOTOR			40
#define	BACK_ULTRASONIC_DISTANCE 1

/*Global variables*/
u8 flag=0;
u8 count;
u16 Width = 30 ,lenght = 40 ;
u16 SPEED_OF_MOTOR=150;
u16 SPEED_OF_MOTOR_detect=150;

u16 TimeForParking;
static u16 result_of_distance;
u16 Distance_Away;
u16 time_of_lengh_of_car;
u16 DistanceForParking;
u16 TimeToCheckParking;
u16 timedMoveBack;
f32 time_of_extra_space_for_parking_after_check;
f32 time_of_first_move_of_parallel_parking;
f32 time_of_second_move_of_parallel_parking;
f32 time_of_third_move_of_parallel_parking;
f32 time_of_fourth_move_of_parallel_parking;
f32 time_of_first_move_of_parallel_exit;
f32 time_of_second_move_of_parallel_exit;
f32 time_of_move_back_parallel_exit;
f32 time_of_move_back_perpindicular_park_count5;
f32 time_of_move_back_perpindicular_park_count6;
f32 time_of_move_back_perpindicular_exit_count7;
f32 time_of_move_perpindicular_park;
volatile u16 Ultra_Front_Dis1;
volatile u16 Ultra_Back_Dis2;
volatile u16 Ultra_Right_Dis3;

/*PROTO TYPES OF FUNCTIONS */
void Display_Distance(void);
void Display_Distance_exit(void);

void Check_Distance_exiting(void);//check and choose exiting function

void Check_Distance_Parallel(void);
void Parallel_Parking(void);

void DC_MOTORS_Init(void);
void MOVE_FORWARD(u8 Copy_u8Speed);
void MOVE_BACKWORD(u8 Copy_u8Speed);
void STOP_DC_MOTOR(void);
void ExitParallel(void);
void MOVE_FORWARD_1_perpindicular(u8 Copy_u8Speed);
void MOVE_FORWARD_2_perpindicular(u8 Copy_u8Speed);
void MOVE_BACKWORD_1_perpindicular(u8 Copy_u8Speed);
void MOVE_BACKWORD_2_perpindicular(u8 Copy_u8Speed);
int main()

{

	UART_voidInit();
	//D0 set it input to recieve data (Rx)
	DIO_voidSetPinDirection(DIO_u8PORTD,0,DIO_u8INPUT);
	//D1 set it output to send data (Tx)
	DIO_voidSetPinDirection(DIO_u8PORTD,1,DIO_u8OUTPUT);
	/*INITIALIZATION LCD 4 PIN MODE & 4LINE MODE  AND CONFIGRATION (DATA PORT D pins(4,5,6,7)&& CONTROL PORT B PINS(0,2) */
	DDRB = DDRB & (~(1<<PB0)); // Configure pin 0 in PORTB as input pin
	PORTB |= (1<<PB0);         // Activate the internal pull up resistor at PB0

	DDRB = DDRB & (~(1<<PB1)); // Configure pin 1 in PORTB as input pin
	PORTB |= (1<<PB1);         // Activate the internal pull up resistor at PB1


	/*DEFINE PORT && PINS FOR EACH MOTOR (PORT A &PINS (0,1,4,5) && define PWM2 pin7) */
	DC_MOTORS_Init();

	/*DEFINE PORT && PINS FOR EACH MOTOR (PORT B &PIN 3)&& define PWM0 PIN 3 */
	//SERVOS_MOTORS_Init();

	/*INITALIZE THE PIN OF GLOBAL INTERRUPT ENABLE  */
	GIE_voidEnable();

	/*DEFINE PORT && PIN FOR TWO BUTTON (PORT D,PIN 2,3) */
	/*DEFINE PORT && PIN FOR TWO BUTTON (PORT A,PIN 2,3)*/
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_PIN2_ID, DIO_u8INPUT);
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_PIN3_ID, DIO_u8INPUT);
	DIO_voidSetPinDirection(DIO_u8PORTA,DIO_PIN2_ID, DIO_u8INPUT);
	DIO_voidSetPinDirection(DIO_u8PORTA,DIO_PIN3_ID, DIO_u8INPUT);
	DIO_voidSetPinDirection(DIO_u8PORTA,DIO_PIN6_ID, DIO_u8INPUT);
	/*DEFINE  (MODE,PRESCALER) IN REGIESTER TCCR0*/
	/*DEFINE  (MODE,PRESCALER) IN REGIESTER TCCR2*/
	DIO_voidSetPinDirection(DIO_u8PORTC,0,DIO_u8INPUT);
	DIO_voidSetPinValue(DIO_u8PORTC,0,DIO_u8HIGH);
	DIO_voidSetPinDirection(DIO_u8PORTC,1,DIO_u8INPUT);
	DIO_voidSetPinValue(DIO_u8PORTC,1,DIO_u8HIGH);
	PWM2_voidInit();

	//time that will take to detect length of the car only
	time_of_lengh_of_car=(lenght*10/REAL_SPEED_OF_MOTOR);
	DistanceForParking =(lenght +(lenght/4));


	//calculate time that i will take for detecting the distance that i will park on it
	TimeForParking=((DistanceForParking*10/REAL_SPEED_OF_MOTOR))*10;
	//TimeForParking=TimeForParking*10;
	//LCD_moveCursor1(2,11);
	//LCD_intgerToString1(TimeForParking*100);
	//5 is the number for checking of sensor in operation
	TimeToCheckParking=TimeForParking/5;
	//equation to calculate distance between sensor and sidewalk
	Distance_Away =Width +(Width/3);
	//calculate time that i will take while moving back to park
	timedMoveBack =((TimeForParking-time_of_lengh_of_car)*100/2);
	//LCD_moveCursor1(3,11);
	//LCD_intgerToString1(timedMoveBack);
	/*
	time_of_moving_parallel_with_SideWalk=(3/4)*lenght / REAL_SPEED_OF_MOTOR;
	time_of_moving_parallel_with_road=(1/4)*lenght / REAL_SPEED_OF_MOTOR;
	 */
	/*	our equation of parking and exit of parking	*/
		time_of_extra_space_for_parking_after_check=((f32)((lenght*300)/4)/REAL_SPEED_OF_MOTOR);//750
		time_of_first_move_of_parallel_parking=((f32)((lenght+((f32)2*lenght/5))*100)/REAL_SPEED_OF_MOTOR);//1400
		time_of_second_move_of_parallel_parking=((f32)((lenght+(lenght/10))*100)/REAL_SPEED_OF_MOTOR);//1100
		time_of_third_move_of_parallel_parking=((f32)((2*lenght+(2*lenght/10))*100)/REAL_SPEED_OF_MOTOR);//2200
		time_of_fourth_move_of_parallel_parking=((f32)(lenght*50)/REAL_SPEED_OF_MOTOR);//500
		time_of_first_move_of_parallel_exit=((f32)((lenght+((f32)lenght/2))*100)/REAL_SPEED_OF_MOTOR);
		//time_of_move_back_parallel_exit =((lenght-Ultra_Front_Dis1)*100)/REAL_SPEED_OF_MOTOR;//this equation is dynamic about the distance it written in bottom with function that calculate before exit
		time_of_move_back_perpindicular_park_count5=((f32)(lenght*100)/REAL_SPEED_OF_MOTOR);//250
		time_of_move_back_perpindicular_park_count6=((f32)(lenght*100+TimeToCheckParking*10)/REAL_SPEED_OF_MOTOR);//400
	//	time_of_move_back_perpindicular_exit_count7=((lenght*100/1.8)/REAL_SPEED_OF_MOTOR);//555
	    time_of_move_perpindicular_park=((Width+Width/6)*100)/REAL_SPEED_OF_MOTOR;




	Set_Angle_Servo_motor_3(0);

	while(1)
	{
		//80 =40cm
		//85 bte =37cm
		// calc speed
		/*
		MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_PARK);
		_delay_ms(1000);
		STOP_DC_MOTOR();
		_delay_ms(2000);
		MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_CHECK);
		_delay_ms(1000);
		STOP_DC_MOTOR();
		 */

		//Check_Distance_Parallel(); //done parallel parking
		//   Check_Distance_exiting();//check and choose exiting function done

		_delay_ms(500);
		if(DIO_u8GetPinValue(DIO_u8PORTC,0)==0)
		{
			_delay_ms(500);
			if(DIO_u8GetPinValue(DIO_u8PORTC,0)==0)
					{
				MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_PARK);
				_delay_ms(1000);
				STOP_DC_MOTOR();
				_delay_ms(2000);
				MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_CHECK);
				_delay_ms(1000);
				STOP_DC_MOTOR();
			//Check_Distance_Parallel(); //done parallel parking
			while (DIO_u8GetPinValue(DIO_u8PORTC,0)==0)
			{
				while (DIO_u8GetPinValue(DIO_u8PORTC,0)==0)
				{
					_delay_ms(250);
				}
				_delay_ms(1000);
			}
					}
		}
		else if(DIO_u8GetPinValue(DIO_u8PORTC,1)==0)
		{
			_delay_ms(500);
			if(DIO_u8GetPinValue(DIO_u8PORTC,1)==0)
					{
		   Check_Distance_exiting();//check and choose exiting function done
			while (DIO_u8GetPinValue(DIO_u8PORTC,1)==0)
			{
				while (DIO_u8GetPinValue(DIO_u8PORTC,1)==0)
				{
					_delay_ms(250);
				}
				_delay_ms(1000);
			}
					}
		}

		/*
		else if(DIO_u8GetPinValue(DIO_u8PORTC,1)==0)
		{
		   Check_Distance_exiting();//check and choose exiting function done
			while (DIO_u8GetPinValue(DIO_u8PORTC,0)==0)
			{

			}
		}

		 */


		/*
		if(DIO_u8GetPinValue(DIO_u8PORTC,0)==0)
		{
		   Check_Distance_Parallel(); //done parallel parking
		}
		else if(DIO_u8GetPinValue(DIO_u8PORTC,1)==0)
		{
		   Check_Distance_exiting();//check and choose exiting function done
		}
		 */
		// Check_Distance_exiting();//check and choose exiting function done

		//break;






	}
	return 0;

}

void Display_Distance(void)
{
	/*this code bellow should put into a function called Display distance and call this function here*/


	Ultrasonic_init();
	Ultra_Front_Dis1=Ultrasonic_readDistance();

	/*LCD_moveCursor(0, 0);
	LCD_intgerToString(Ultra_Front_Dis1);
	LCD_displayString(" ");
	 */
	Ultrasonic2_init();
	Ultra_Back_Dis2=Ultrasonic2_readDistance();

	/*
	LCD_moveCursor(1, 0);
	LCD_intgerToString(Ultra_Back_Dis2);
	LCD_displayString(" ");
	 */

	Ultrasonic3_init();
	Ultra_Right_Dis3=Ultrasonic3_readDistance();
	/*
	LCD_moveCursor(2, 0);
	LCD_intgerToString(Ultra_Right_Dis3);
	LCD_displayString(" ");
	 */


	//the end of function above
}
void Display_Distance_exit(void)
{
	Ultrasonic_init();
	Ultra_Front_Dis1=Ultrasonic_readDistance();

	//Ultrasonic2_init();
	//Ultra_Back_Dis2=Ultrasonic2_readDistance();

	Ultrasonic3_init();
	Ultra_Right_Dis3=Ultrasonic3_readDistance();
}




void Check_Distance_Parallel(void)
{

	//this code below is check fuction
	//moving my car with detecting
	count=0;
	result_of_distance=0;
	MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_PARK);
	while(count<7)
	{
		//MOVE_FORWARD(SPEED_OF_MOTOR);
		Display_Distance();
		MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_PARK);
		//check if sensors detected an empty space

		if (Ultra_Right_Dis3>Distance_Away)
		{
			//if(count==3)
			//{
			STOP_DC_MOTOR();
			_delay_ms(1000);

			//here we go ...lets check the space if it,s more than my car size

			//STOP_DC_MOTOR();
			Display_Distance();
			count++;
			MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_CHECK);
			_delay_ms(TimeToCheckParking*10);
		}
		//if the second check wasn,t enough go to loop again
		else if (count>= 5)
		{

			break;
		}
		else
		{

			count=0;

		}

	}
	if (count==7)
	{
		Parallel_Parking();
	}
	else if(count==5)
	{
		STOP_DC_MOTOR();
		MOVE_BACKWORD(PWM_SPEED_OF_MOTOR_TO_PARK);
		_delay_ms(time_of_move_back_perpindicular_park_count5*10);
		STOP_DC_MOTOR();
		Set_Angle_Servo_motor_3(90);
		_delay_ms(1000);
		UART_voidSendData(90);
		_delay_ms(5000);
		MOVE_BACKWORD_1_perpindicular(PWM_SPEED_OF_MOTOR_TO_PARK);
		MOVE_FORWARD_2_perpindicular(PWM_SPEED_OF_MOTOR_TO_PARK);
		_delay_ms(time_of_move_perpindicular_park*10);
		STOP_DC_MOTOR();
		Set_Angle_Servo_motor_3(0);
		_delay_ms(1000);
		UART_voidSendData(0);
		_delay_ms(1000);

	}
	else if(count==6)
	{
		STOP_DC_MOTOR();
		MOVE_BACKWORD(PWM_SPEED_OF_MOTOR_TO_PARK);
		_delay_ms(time_of_move_back_perpindicular_park_count6*10);
		STOP_DC_MOTOR();
		Set_Angle_Servo_motor_3(90);
		_delay_ms(1000);
		UART_voidSendData(90);
		_delay_ms(5000);
		MOVE_BACKWORD_1_perpindicular(PWM_SPEED_OF_MOTOR_TO_PARK);
		MOVE_FORWARD_2_perpindicular(PWM_SPEED_OF_MOTOR_TO_PARK);
		_delay_ms(time_of_move_perpindicular_park*10);
		STOP_DC_MOTOR();
		Set_Angle_Servo_motor_3(0);
		_delay_ms(1000);
		UART_voidSendData(0);
		_delay_ms(1000);


	}
/*
	else if(count==6)
	{
		STOP_DC_MOTOR();
		MOVE_BACKWORD(PWM_SPEED_OF_MOTOR_TO_PARK);
		_delay_ms(time_of_move_back_perpindicular_exit_count7*10);
		STOP_DC_MOTOR();
		Set_Angle_Servo_motor_3(90);
		_delay_ms(1000);
		UART_voidSendData(90);
		_delay_ms(5000);
		// park 90 angle
		MOVE_BACKWORD_1_perpindicular(PWM_SPEED_OF_MOTOR_TO_PARK);
		MOVE_FORWARD_2_perpindicular(PWM_SPEED_OF_MOTOR_TO_PARK);
		_delay_ms(time_of_move_perpindicular_park*10);
		STOP_DC_MOTOR();
		Set_Angle_Servo_motor_3(0);
		_delay_ms(1000);
		UART_voidSendData(0);
		_delay_ms(1000);



	}
*/

}
void Check_Distance_exiting(void)//check and choose exiting function
{
	count=0;
	result_of_distance=0;
	while(count<4)
	{
		Display_Distance_exit();
		UART_voidSendData(BACK_ULTRASONIC_DISTANCE);
		Ultra_Back_Dis2=UART_u8ReceiveData();

		count++;

		//_delay_ms(3000);
		if((Ultra_Front_Dis1+Ultra_Back_Dis2)>40)
		{

			if (Ultra_Front_Dis1>40)
			{

				ExitParallel();
				break;
			}
			//if the second check wasn,t enough go to loop again
			else if (Ultra_Front_Dis1<40)
			{
				time_of_move_back_parallel_exit =((lenght-Ultra_Front_Dis1)*100)/REAL_SPEED_OF_MOTOR;
				MOVE_BACKWORD(PWM_SPEED_OF_MOTOR_TO_PARK);
				_delay_ms(time_of_move_back_parallel_exit*10);
				STOP_DC_MOTOR();
				ExitParallel();

				break;
			}
		}
	}
	if(count>=4)
	{
		Set_Angle_Servo_motor_3(90);
		UART_voidSendData(90);
		_delay_ms(5000);
		MOVE_FORWARD_1_perpindicular(PWM_SPEED_OF_MOTOR_TO_PARK);
		MOVE_BACKWORD_2_perpindicular(PWM_SPEED_OF_MOTOR_TO_PARK);
		_delay_ms(time_of_move_perpindicular_park*10);
		STOP_DC_MOTOR();
		UART_voidSendData(45);
		_delay_ms(1000);
		UART_voidSendData(0);
		//_delay_ms(1000);
		Set_Angle_Servo_motor_3(0);
		_delay_ms(1000);

	}


}


void Parallel_Parking(void)
{

	count=0;
	STOP_DC_MOTOR();
	MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_PARK);
	_delay_ms(time_of_extra_space_for_parking_after_check*10);//equation done time_of_extra_space_for_parking_after_check
	STOP_DC_MOTOR();
	_delay_ms(1500);
	UART_voidSendData(45);//set servo 45
	_delay_ms(500);
	UART_voidSendData(45);//set servo 45
	_delay_ms(1000);
	MOVE_BACKWORD(PWM_SPEED_OF_MOTOR_TO_PARK);
	_delay_ms(time_of_first_move_of_parallel_parking*10);//equation done time_of_first_move_of_parallel_parking
	STOP_DC_MOTOR();
	UART_voidSendData(0);//set servo 0
	_delay_ms(1000);
	UART_voidSendData(0);//set servo 0
	_delay_ms(1000);
	UART_voidSendData(135);//set servo 135
	_delay_ms(1000);
	UART_voidSendData(135);//set servo 135
	_delay_ms(500);
	MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_PARK);
	_delay_ms(time_of_second_move_of_parallel_parking*10);//equation done time_of_second_move_of_parallel_parking
	STOP_DC_MOTOR();
	UART_voidSendData(0);//set servo 0
	_delay_ms(1000);
	UART_voidSendData(0);//set servo 0
	_delay_ms(500);
	UART_voidSendData(135);//set servo 135
	_delay_ms(1000);
	UART_voidSendData(135);//set servo 135
	_delay_ms(1000);
	MOVE_BACKWORD(PWM_SPEED_OF_MOTOR_TO_PARK);
	_delay_ms(time_of_third_move_of_parallel_parking*10);//equation done time_of_third _move_back_of_parallel_parking
	STOP_DC_MOTOR();
	UART_voidSendData(0);//set servo 0
	_delay_ms(1000);
	UART_voidSendData(0);//set servo 0
	_delay_ms(500);
	MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_PARK);
	_delay_ms(time_of_fourth_move_of_parallel_parking*10);//equation done time_of_fourth_move_back_of_parallel_parking
	STOP_DC_MOTOR();
}

void MOVE_BACKWORD_2_perpindicular(u8 Copy_u8Speed)
{

	PWM2_voidSetOcrValue(Copy_u8Speed);
	DC_MOTOR2_voidRotateAntiClockwise();
	DC_MOTOR3_voidRotateAntiClockwise();
}
void STOP_DC_MOTOR(void)
{
	DC_MOTOR1_voidStop();
	DC_MOTOR2_voidStop();
	DC_MOTOR3_voidStop();
	DC_MOTOR4_voidStop();
}
void MOVE_FORWARD_2_perpindicular(u8 Copy_u8Speed)
{

	PWM2_voidSetOcrValue(Copy_u8Speed);
	DC_MOTOR2_voidRotateClockwise();
	DC_MOTOR3_voidRotateClockwise();
}
void MOVE_BACKWORD(u8 Copy_u8Speed)
{

	PWM2_voidSetOcrValue(Copy_u8Speed);
	DC_MOTOR1_voidRotateAntiClockwise();
	DC_MOTOR2_voidRotateAntiClockwise();
	DC_MOTOR3_voidRotateAntiClockwise();
	DC_MOTOR4_voidRotateAntiClockwise();
}
void MOVE_BACKWORD_1_perpindicular(u8 Copy_u8Speed)
{

	PWM2_voidSetOcrValue(Copy_u8Speed);
	DC_MOTOR1_voidRotateAntiClockwise();
	DC_MOTOR4_voidRotateAntiClockwise();
}
void MOVE_FORWARD(u8 Copy_u8Speed)
{

	PWM2_voidSetOcrValue(Copy_u8Speed);
	DC_MOTOR1_voidRotateClockwise();
	DC_MOTOR2_voidRotateClockwise();
	DC_MOTOR3_voidRotateClockwise();
	DC_MOTOR4_voidRotateClockwise();
}
void MOVE_FORWARD_1_perpindicular(u8 Copy_u8Speed)
{

	PWM2_voidSetOcrValue(Copy_u8Speed);
	DC_MOTOR1_voidRotateClockwise();
	DC_MOTOR4_voidRotateClockwise();
}
void DC_MOTORS_Init(void)
{
	DC_MOTOR1_Init();
	DC_MOTOR2_Init();
	DC_MOTOR3_Init();
	DC_MOTOR4_Init();
}




void ExitParallel(void)
{

	UART_voidSendData(135);//set servo 135
	_delay_ms(1500);
	MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_PARK);
	_delay_ms((time_of_first_move_of_parallel_parking*10));
	STOP_DC_MOTOR();
	UART_voidSendData(0);//set servo 0
	_delay_ms(1000);
	UART_voidSendData(0);//set servo 0
	_delay_ms(1000);
	UART_voidSendData(45);//set servo 45
	_delay_ms(1500);
	UART_voidSendData(45);//set servo 45
	_delay_ms(1500);
	MOVE_FORWARD(PWM_SPEED_OF_MOTOR_TO_PARK);
	_delay_ms((time_of_first_move_of_parallel_parking*10));//equation done time_of_first_move_of_parallel_parking
	STOP_DC_MOTOR();
	UART_voidSendData(0);//set servo 0
}


