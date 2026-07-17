/*
 * BUZZER.c
 *
 *  Created on: Oct 2, 2024
 *      Author: hp202
 */


#include "BUZZER.h"
#include "gpio.h"

//initialize the buzzer
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID , BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID ,BUZZER_PIN_ID,LOGIC_LOW);
}
//turn on the buzzer
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID,LOGIC_HIGH);
}
//turn off the buzzer
void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID,LOGIC_LOW);
}
