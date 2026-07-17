/*
 * LDR_sensor.c
 *
 *  Created on: Oct 2, 2024
 *      Author: hp202
 */

#include "LDR_sensor.h"
#include "adc.h"


uint16 LDR_getLightIntensity(void)
{
uint16 intensity_value=0;
uint16 ADC_value=0;
ADC_value=ADC_readChannel(SENSOR_CHANNEL_ID);
intensity_value = (uint16)(((uint32)ADC_value*SENSOR_MAX_INTENSITY*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));
return intensity_value;
}
