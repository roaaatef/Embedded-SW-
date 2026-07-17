/*
 * LED.c
 *
 *  Created on: Oct 2, 2024
 *      Author: hp202
 */
#include "LED.h"
#include "gpio.h"
#include "std_types.h"
//////////////////////////////
void LEDS_init(void){
	GPIO_setupPinDirection(RED_LED_PORT_ID , RED_LED_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(GREEN_LED_PORT_ID , GREEN_LED_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID , PIN_OUTPUT);
	/////////////////////////turn off the leds
#if ( RED_LED_CONNECTION ==  POSITIVE_LOGIC)
	GPIO_writePin(RED_LED_PORT_ID , RED_LED_PIN_ID, LOGIC_LOW);
#else
	GPIO_writePin(RED_LED_PORT_ID , RED_LED_PIN_ID, LOGIC_HIGH);
#endif
#if ( GREEN_LED_CONNECTION ==  POSITIVE_LOGIC)
	GPIO_writePin(GREEN_LED_PORT_ID , GREEN_LED_PIN_ID , LOGIC_LOW);
#else
	GPIO_writePin(GREEN_LED_PORT_ID , GREEN_LED_PIN_ID , LOGIC_HIGH);
#endif

#if ( BLUE_LED_CONNECTION ==  POSITIVE_LOGIC)
	GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID , LOGIC_LOW);
#else
	GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID , LOGIC_HIGH);
#endif


}

void LED_on(LED_ID id)
{
switch(id)
{
case RED_LED:
#if ( RED_LED_CONNECTION ==  POSITIVE_LOGIC)
	GPIO_writePin(RED_LED_PORT_ID , RED_LED_PIN_ID, LOGIC_HIGH);
#else
	GPIO_writePin(RED_LED_PORT_ID , RED_LED_PIN_ID, LOGIC_LOW);
#endif
	break;
case GREEN_LED:
#if ( GREEN_LED_CONNECTION ==  POSITIVE_LOGIC)
	GPIO_writePin(GREEN_LED_PORT_ID , GREEN_LED_PIN_ID , LOGIC_HIGH);
#else
	GPIO_writePin(GREEN_LED_PORT_ID , GREEN_LED_PIN_ID , LOGIC_LOW);
#endif
	break;
case BLUE_LED:
#if ( BLUE_LED_CONNECTION ==  POSITIVE_LOGIC)
	GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID , LOGIC_HIGH);
#else
	GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID , LOGIC_LOW);
#endif
	break;
}
}
void LED_off(LED_ID id)
{
	switch(id)
	{
	case RED_LED:
	#if ( RED_LED_CONNECTION ==  POSITIVE_LOGIC)
		GPIO_writePin(RED_LED_PORT_ID , RED_LED_PIN_ID, LOGIC_LOW);
	#else
		GPIO_writePin(RED_LED_PORT_ID , RED_LED_PIN_ID, LOGIC_HIGH);
	#endif
		break;
	case GREEN_LED:
	#if ( GREEN_LED_CONNECTION ==  POSITIVE_LOGIC)
		GPIO_writePin(GREEN_LED_PORT_ID , GREEN_LED_PIN_ID , LOGIC_LOW);
	#else
		GPIO_writePin(GREEN_LED_PORT_ID , GREEN_LED_PIN_ID , LOGIC_HIGH);
	#endif
		break;
	case BLUE_LED:
	#if ( BLUE_LED_CONNECTION ==  POSITIVE_LOGIC)
		GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID , LOGIC_LOW);
	#else
		GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID , LOGIC_HIGH);
	#endif
		break;
	}
}

