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
#define MOTOR_IN1_PORT_ID     PORTD_ID
#define MOTOR_IN2_PORT_ID     PORTD_ID
#define MOTOR_IN1_PIN_ID         PIN6_ID
#define MOTOR_IN2_PIN_ID         PIN7_ID
#define MOTOR_ENABLE_PORT_ID     PORTB_ID
#define MOTOR_ENABLE_PIN_ID       PIN3_ID
/////////////////////////////////////
typedef enum{
	STOP,CW,CCW
}DcMotor_State;
////////////////////////////////
void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint16 speed);



#endif /* DC_MOTOR_H_ */
