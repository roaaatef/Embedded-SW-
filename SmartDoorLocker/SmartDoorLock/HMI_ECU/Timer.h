/*
 * Timer.h
 *
 *  Created on: Oct 28, 2024
 *      Author: hp202
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"
//////////////////////////////

////////////////////////////////////
typedef enum{
TIMER_0,TIMER_1,TIMER_2
}Timer_ID_Type;
typedef enum{
NO_CLK,PRESCALE_1,PRESCALE_8,PRESCALE_64,PRESCALE_256,PRESCALE_1024
}Timer_ClockType;
typedef enum{
NORMAL,COMPARE,PWM
}Timer_ModeType ;

typedef struct
{
uint16 timer_InitialValue;
uint16 timer_compare_MatchValue;     /*it will be used in compare mode only*/
Timer_ID_Type  timer_ID;
Timer_ClockType timer_clock;
Timer_ModeType  timer_mode;
}Timer_ConfigType;

void Timer_init(const Timer_ConfigType * Config_Ptr);
void Timer_deInit(Timer_ID_Type timer_type);
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID );


#endif /* TIMER_H_ */
