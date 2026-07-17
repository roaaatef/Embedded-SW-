/*
 * SmartHome.h
 *
 *  Created on: Oct 4, 2024
 *      Author: hp202
 */

#ifndef SMARTHOME_H_
#define SMARTHOME_H_
#include "std_types.h"
/////////////////////////////
//definition of variables
uint16 intensity;
 uint8 temp;
 uint8 red_led=0;
 uint8 green_led=1;
  uint8 blue_led=2;
////////////////////////////////////
//functions prototypes
void PrintOnLcd (void);
void ManageFlame(void);
void PrintIntensity(void);
void PrintTemperature(void);



#endif /* SMARTHOME_H_ */
