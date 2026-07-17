/*
 * DC_MOTOR.c
 *
 *  Created on: Oct 3, 2024
 *      Author: hp202
 */
#include "DC_MOTOR.h"
#include "gpio.h"
#include "PWM.h"
/////////////////////////////////////////
//initialize the motor
void DcMotor_Init(void){
	GPIO_setupPinDirection(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection( MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID ,PIN_OUTPUT);
	GPIO_setupPinDirection( MOTOR_ENABLE_PORT_ID, MOTOR_ENABLE_PIN_ID ,PIN_OUTPUT);
	GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_ENABLE_PORT_ID, MOTOR_ENABLE_PIN_ID, LOGIC_HIGH);
	//motor initially stop
}

void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{uint8 duty_cycle;
duty_cycle = ((uint16)((speed * 255) / 100));

	PWM_Timer0_Start(duty_cycle);
switch(state)
{
case CW:
	GPIO_writePin(MOTOR_ENABLE_PORT_ID, MOTOR_ENABLE_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_HIGH);

		break;
case CCW:
	GPIO_writePin(MOTOR_ENABLE_PORT_ID, MOTOR_ENABLE_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;
case STOP:
	GPIO_writePin(MOTOR_ENABLE_PORT_ID, MOTOR_ENABLE_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;

}
}

