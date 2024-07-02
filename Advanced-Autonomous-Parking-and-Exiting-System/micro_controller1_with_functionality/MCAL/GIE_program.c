/*
 * GIE_program.c
 *
 *  Created on: Aug 28, 2023
 *      Author: mostafa.mohammady
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "DIO_config.h"

#include "GIE_interface.h"
#include "GIE_register.h"


void GIE_voidEnable(void)
{
	SET_BIT(SREG , DIO_PIN7_ID);
}


void GIE_voidDisable(void)
{
	CLR_BIT(SREG , DIO_PIN7_ID);
}

