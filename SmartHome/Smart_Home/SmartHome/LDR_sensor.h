/*
 * LDR_sensor.h
 *
 *  Created on: Oct 2, 2024
 *      Author: hp202
 */

#ifndef LDR_SENSOR_H_
#define LDR_SENSOR_H_
#include"std_types.h"


#define SENSOR_CHANNEL_ID         0
#define SENSOR_MAX_VOLT_VALUE    2.56
#define SENSOR_MAX_INTENSITY   100




uint16 LDR_getLightIntensity(void);



#endif /* LDR_SENSOR_H_ */
