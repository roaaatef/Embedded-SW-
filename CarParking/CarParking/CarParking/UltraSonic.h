/*
 * UltraSonic.h
 *
 *  Created on: Oct 10, 2024
 *      Author: hp202
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "std_types.h"
//////////////////////////////////
#define ULTRA_SONIC_SENSOR_TRIGGER_PORT     PORTD_ID
#define ULTRA_SONIC_SENSOR_TRIGGER_PIN     PIN7_ID
/////////////////////////////
//functions prototypes:
void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);







#endif /* ULTRASONIC_H_ */
