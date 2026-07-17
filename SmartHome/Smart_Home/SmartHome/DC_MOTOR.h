/*
 * DC_MOTOR.h
 *
 *  Created on: Oct 3, 2024
 *      Author: hp202
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"
//////////////////////////////////////
#define MOTOR_IN1_PORT_ID     PORTB_ID
#define MOTOR_IN2_PORT_ID     PORTB_ID
#define MOTOR_IN1_PIN_ID         PIN0_ID
#define MOTOR_IN2_PIN_ID         PIN1_ID
#define MOTOR_ENABLE_PORT_ID     PORTB_ID
#define MOTOR_ENABLE_PIN_ID       PIN3_ID
/////////////////////////////////////
typedef enum{
	STOP,CW,CCW
}DcMotor_State;
////////////////////////////////
void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state, uint8 speed);



#endif /* DC_MOTOR_H_ */
