/*
 * Flame_sensor.c
 *
 *  Created on: Oct 3, 2024
 *      Author: hp202
 */

#include "Flame_sensor.h"
#include "gpio.h"


void FlameSensor_init(void)
{
	GPIO_setupPinDirection(FLAME_SENSOR_PORT_ID, FLAME_SENSOR_PIN_ID, PIN_INPUT);

}
//get the value from logic state
uint8 FlameSensor_getValue(void)
{uint8 value;
	value=GPIO_readPin(FLAME_SENSOR_PORT_ID, FLAME_SENSOR_PIN_ID);

	return value;
}
