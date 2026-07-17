/*
 * SmartHome.c
 *
 *  Created on: Oct 2, 2024
 *      Author: hp202
 */

#include "BUZZER.h"
#include "DC_MOTOR.h"
#include "Flame_sensor.h"
#include "LDR_sensor.h"
#include "LED.h"
#include "lm35_sensor.h"
#include "SmartHome.h"
/////////////////////////
//functions definition
void PrintOnLcd (void)
{
	LCD_moveCursor(1,0);
	LCD_displayString("Temp=  C");
	LCD_displayString("LDR=   %");
}
////////////////////////////////
void ManageFlame(void)
{
	LCD_clearScreen();
	           LCD_displayString("Critical Alert!");

				Buzzer_on();
}
////////////////////////////////
void PrintIntensity(void)
{
	LCD_moveCursor(1,12);
	if(intensity>=100)
					{
						LCD_intgerToString(intensity);
					}
					else{
					LCD_intgerToString(intensity);
					LCD_displayCharacter(' ');
					}
}
//////////////////////////////////
void PrintTemperature(void)
{
	LCD_moveCursor(1,5);
	if(temp>=10)
					{
						LCD_intgerToString(temp);
					}
					else{
					LCD_intgerToString(temp);
					LCD_displayCharacter(' ');
					}
}
/////////////////////////////
int main(void)
{


   //initialize necessary drivers
	ADC_init();
	Buzzer_init();
	DcMotor_Init();
	FlameSensor_init();
	LCD_init();
	LEDS_init();
	//////////////////////////////////////////////
	PrintOnLcd();

	//////////////////////////////////////////////
	while(1)
	{
		 if(FlameSensor_getValue())
		    {
		ManageFlame();

			while(FlameSensor_getValue())
			{


}
			LCD_clearScreen();
			PrintOnLcd();
			Buzzer_off();
		    }



intensity=LDR_getLightIntensity();
PrintIntensity();
if(intensity<15)
{
	LED_on(red_led);
	LED_on(green_led);
	LED_on(blue_led);


}
else if ((intensity>=16)&&(intensity<=50))
{
	LED_on(red_led);
	LED_on(green_led);
	LED_off(blue_led);


}
else if ((intensity>50)&&(intensity<=70))
{
	LED_on(red_led);
	LED_off(green_led);
	LED_off(blue_led);

}
else
{
	LED_off(red_led);
	LED_off(green_led);
	LED_off(blue_led);

}

temp=LM35_getTemperature();
PrintTemperature();
if(temp>=40)
{    LCD_moveCursor(0,0);
     LCD_displayString("FAN IS ON ");
	 DcMotor_Rotate(CW,100);
}
else if((temp>=35)&&(temp<40))
{
	 LCD_moveCursor(0,0);
	 LCD_displayString("FAN IS ON ");
	 DcMotor_Rotate(CW,75);
}
else if ((temp>=30)&&(temp<35))
{
	 LCD_moveCursor(0,0);
	 LCD_displayString("FAN IS ON ");
	 DcMotor_Rotate(CW,50);
}
else if ((temp>=25)&&(temp<30))
{
	 LCD_moveCursor(0,0);
	 LCD_displayString("FAN IS ON ");
	 DcMotor_Rotate(CW,25);
}
else
{
	 LCD_moveCursor(0,0);
	 LCD_displayString("FAN IS OFF ");
	 DcMotor_Rotate(CW,0);
}
}
}

