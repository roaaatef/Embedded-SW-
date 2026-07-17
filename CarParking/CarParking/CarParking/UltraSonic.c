/*
 * UltraSonic.c
 *
 *  Created on: Oct 10, 2024
 *      Author: hp202
 */
#include "UltraSonic.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>
//////////////////////
uint8 edge_count=0;
uint16 TimeHighValue=0;
void Ultrasonic_init(void)
{
	ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};
	ICU_init(&ICU_Configurations);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection( ULTRA_SONIC_SENSOR_TRIGGER_PORT , ULTRA_SONIC_SENSOR_TRIGGER_PIN , PIN_OUTPUT);

}
void Ultrasonic_Trigger(void)
{
	 GPIO_writePin(ULTRA_SONIC_SENSOR_TRIGGER_PORT, ULTRA_SONIC_SENSOR_TRIGGER_PIN ,LOGIC_HIGH);
	 _delay_us(15);
	 GPIO_writePin(ULTRA_SONIC_SENSOR_TRIGGER_PORT, ULTRA_SONIC_SENSOR_TRIGGER_PIN ,LOGIC_LOW);
}
uint16 Ultrasonic_readDistance(void)
{

Ultrasonic_Trigger();
while(TimeHighValue==0);
{
return (((float)TimeHighValue/117)+1);

}

}
void Ultrasonic_edgeProcessing(void)
{edge_count++;
	if(edge_count==1)

	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);

	}
	else if(edge_count==2)
	{
		TimeHighValue=ICU_getInputCaptureValue();
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(RAISING);
		edge_count=0;
	}
}

