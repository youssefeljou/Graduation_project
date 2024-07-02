/*
 * DIO_interface.h
 *
 *  Created on: Aug 14, 2023
 *      Author: mostafa.mohammady
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "../LIB/STD_TYPES.h"

void DIO_voidSetPinDirection(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Direction);
void DIO_voidSetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Value);
void DIO_voidSetPortDirection(u8 Copy_u8Port , u8 Copy_u8Direction);
void DIO_voidSetPortValue(u8 Copy_u8Port , u8 Copy_u8Value);
u8 DIO_u8GetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin);





#endif /* DIO_INTERFACE_H_ */
