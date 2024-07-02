/*
 * ultra_sonic.h
 *
 *  Created on: Oct 16, 2022
 *      Author: Youmna
 */

#ifndef HAL_ULTRA_SONIC_H_
#define HAL_ULTRA_SONIC_H_
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO_interface.h"
#define TRIG_PORT_ID DIO_u8PORTB
#define TRIG_PIN_ID  DIO_PIN5_ID
/*
#define TRIG2_PORT_ID DIO_u8PORTB
#define TRIG2_PIN_ID  DIO_PIN5_ID

#define TRIG3_PORT_ID DIO_u8PORTB
#define TRIG3_PIN_ID  DIO_PIN6_ID
*/
#define ECO_PORT_ID DIO_u8PORTD
#define ECO_PIN_ID  DIO_PIN6_ID


void Ultrasonic_edgeProcessing(void);
//void Ultrasonic2_edgeProcessing(void);
//void Ultrasonic3_edgeProcessing(void);
void Ultrasonic_init(void);
//void Ultrasonic2_init(void);
//void Ultrasonic3_init(void);
void Ultrasonic_Trigger(void);
//void Ultrasonic2_Trigger(void);
//void Ultrasonic3_Trigger(void);
u16 Ultrasonic_readDistance(void);
//u16 Ultrasonic2_readDistance(void);
//u16 Ultrasonic3_readDistance(void);
#endif /* HAL_ULTRA_SONIC_H_ */
