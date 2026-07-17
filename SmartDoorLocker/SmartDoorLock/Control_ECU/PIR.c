/*
 * PIR.c
 *
 *  Created on: Oct 28, 2024
 *      Author: hp202
 */

#include "PIR.h"
#include "std_types.h"
#include "gpio.h"
void PIR_init(void)
{
	GPIO_setupPinDirection(PIR_SENSOR_PORT_ID , PIR_SENSOR_PIN_ID  , PIN_INPUT);
}
uint8 PIR_getState(void)
{
	uint8 value;
		value=GPIO_readPin(PIR_SENSOR_PORT_ID, PIR_SENSOR_PIN_ID);

		return value;
}
