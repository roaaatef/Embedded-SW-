/*
 * Timer.c
 *
 *  Created on: Oct 28, 2024
 *      Author: hp202
 */

#include "Timer.h"
#include "avr/io.h"
#include <avr/interrupt.h>

//////////////////////////
static void (*g_timer0Callback)(void) = NULL_PTR;
static void (*g_timer1Callback)(void) =NULL_PTR;
static void (*g_timer2Callback)(void) = NULL_PTR;

//////////////////////
ISR(TIMER0_OVF_vect)
{
	if(g_timer0Callback != NULL_PTR)
		{

			(*g_timer0Callback)();
		}
}
ISR(TIMER0_COMP_vect)
{
	if(g_timer0Callback != NULL_PTR)
		{

			(*g_timer0Callback)();
		}
}
ISR(TIMER2_OVF_vect)
{
	if(g_timer2Callback != NULL_PTR)
		{

			(*g_timer2Callback)();
		}
}
ISR(TIMER2_COMP_vect)
{
	if(g_timer2Callback != NULL_PTR)
		{

			(*g_timer2Callback)();
		}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_timer1Callback != NULL_PTR)
		{

			(*g_timer1Callback)();
		}
}
ISR(TIMER1_OVF_vect)
{
	if(g_timer1Callback != NULL_PTR)
		{

			(*g_timer1Callback)();
		}
}
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID )
{
	switch(a_timer_ID)
	{
	case TIMER_0:
		g_timer0Callback=a_ptr;
		break;
	case TIMER_1:
		g_timer1Callback=a_ptr;
	break;
	case TIMER_2:
		g_timer2Callback=a_ptr;
		break;
	}
}
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
switch(Config_Ptr->timer_ID)
{
case TIMER_0:
	 TCNT0= Config_Ptr->timer_InitialValue;
	 if(Config_Ptr->timer_mode==COMPARE)
	 {
		 OCR0=Config_Ptr->timer_compare_MatchValue;
		 TIMSK |= (1<<OCIE0);
		 TCCR0=(1<<FOC0)| (1<<WGM01) | ( Config_Ptr->timer_clock);
	 }
	 else
	 {
		 TIMSK |= (1<<TOIE0);
		 TCCR0=(1<<FOC0)|( Config_Ptr->timer_clock);
	 }
	 break;
case TIMER_1:
	TCNT1 =Config_Ptr->timer_InitialValue;
	if(Config_Ptr->timer_mode==COMPARE)
	{
		OCR1A=Config_Ptr->timer_compare_MatchValue;
		 TIMSK = (1 << OCIE1A);
		 TCCR1A = (1 <<  FOC1A )|(1<<FOC1B);  // CTC mode
		     TCCR1B = (1 << WGM12) | (Config_Ptr->timer_clock);

	}
	else
	{
		 TIMSK = (1 <<  TOIE1);
				 TCCR1A = (1 <<  FOC1A )|(1<<FOC1B);  // CTC mode
				     TCCR1B =  (Config_Ptr->timer_clock);
	}
	break;
case TIMER_2:
	TCNT2=Config_Ptr->timer_InitialValue;
	if(Config_Ptr->timer_mode==COMPARE)
	{
		 OCR2=Config_Ptr->timer_compare_MatchValue;
		 TIMSK |= (1<<OCIE2);
				 TCCR2=(1<<FOC2)| (1<<WGM21) | ( Config_Ptr->timer_clock);
	}
	else
	{
		TIMSK |= (1<<TOIE2);
		 TCCR2=(1<<FOC2)|( Config_Ptr->timer_clock);
	}
	break;


}


}

void Timer_deInit(Timer_ID_Type timer_type)
{
switch(timer_type)
{
case TIMER_0:
	TCNT0=0;

		 OCR0=0;
				 TIMSK &=~ (1<<OCIE0);
				 TCCR0=0;


		 TIMSK &=~ (1<<TOIE0);



	break;
case TIMER_1:
	TCNT1=0;

			 OCR1A=0;
					 TIMSK &=~ (1<<OCIE1A);
					 TCCR1A=0;
					 TCCR1B=0;


			 TIMSK &=~ (1<<TOIE1);
	break;
case TIMER_2:
	TCNT2=0;

		 OCR2=0;
				 TIMSK &=~ (1<<OCIE2);
				 TCCR2=0;


		 TIMSK &=~ (1<<TOIE2);
	break;
}





}

