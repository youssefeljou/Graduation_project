/*
 * UART_interface.h
 *
 *  Created on: Sep 12, 2023
 *      Author: pc
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_voidInit(void);
void UART_voidSendData(u8 Copy_u8Data);
u8   UART_u8ReceiveData(void);
void UART_voidReceiverEnable(void);
void UART_voidReceiverDisable(void);
void UART_voidTransmitterEnable(void);
void UART_voidTransmitterDisable(void);





#endif /* UART_INTERFACE_H_ */
