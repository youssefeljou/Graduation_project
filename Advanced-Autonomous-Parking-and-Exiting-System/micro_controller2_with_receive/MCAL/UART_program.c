/*
 * UART_program.c
 *
 *  Created on: Sep 12, 2023
 *      Author: pc
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_regiester.h"


void UART_voidInit(void)
{    /*variable =register name */
	u8 Local_UCSRC=0b10000110;

	/*disable DOUPLE SPEED */
	CLR_BIT( UCSRA,1);

	/* Set character size */
	CLR_BIT(UCSRB,2);
	SET_BIT(Local_UCSRC,2);
	SET_BIT(Local_UCSRC,1);

	/*register select(UCSRC register */
	SET_BIT(Local_UCSRC,7);

	/*Asynchronous mode */
	CLR_BIT(Local_UCSRC,6);

	/*Disable Parity bit (no parity)*/
	CLR_BIT(Local_UCSRC,5);
	CLR_BIT(Local_UCSRC,4);

	/*stop bit (2bit)*/
	SET_BIT(Local_UCSRC,3);

	/*Assign The Value to the UCSRC Register*/
	UCSRC=Local_UCSRC;

	/*Set THE Baud rate to 9600 bps*/
	UBRRL=51;

	/*Enable receiver  */

	UART_voidReceiverEnable();

    /*Enable Transmitter  */

	UART_voidTransmitterEnable();

}
void UART_voidSendData(u8 Copy_u8Data)
{
	/*wait until the register be empty */

  while ((GET_BIT(UCSRA , 5)) !=1)
{
	  asm("NOP");

}
  /*Select Data*/
  UDR=Copy_u8Data;

}
u8   UART_u8ReceiveData(void)
{

	/*wait until the Receiving is completed */

	  while ((GET_BIT(UCSRA,7)) !=1)
	{
		  asm("NOP");

	}
	  /*read data */
	  return UDR;

}
void UART_voidReceiverEnable(void)
{
	SET_BIT(UCSRB,4);
}
void UART_voidReceiverDisable(void)
{
	CLR_BIT(UCSRB,4);
}
void UART_voidTransmitterEnable(void)
{
	SET_BIT(UCSRB,3);
}
void UART_voidTransmitterDisable(void)
{
	CLR_BIT(UCSRB,3);

}
