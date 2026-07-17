/*
 * PWM.c
 *
 *  Created on: Oct 2, 2024
 *      Author: hp202
 */

#include "PWM.h"
#include "gpio.h"
#include <avr/io.h>


void PWM_Timer0_Start(uint8 duty_cycle)
{
	 TCCR0=(1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS02)|(1<<CS00);
	 TCNT0=0;
	 OCR0=duty_cycle;
	 GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);




}
