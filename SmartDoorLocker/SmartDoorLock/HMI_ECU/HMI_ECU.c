/*
 * HMI_ECU.c
 *
 *  Created on: Oct 28, 2024
 *      Author: hp202
 */

/*
 * hmi.c
 *
 *  Created on: Oct 31, 2024
 *      Author: Manar
 */
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include <util/delay.h>
#include "Timer.h"
//////////////////////
#define FIRST_PASS 0x00
#define SECOND_PASS 0x01
#define OLD_PASS 0x02
#define BZZER_ON 0x03
#define MOTOR_ON 0x04
#define CORRECT_PASS 0x05
#define WRONG_PASS 0x06
///////////////////////////////////////
uint8 value;
uint8 key;
uint8 flag=0;

//////////////////////////////////////////////
typedef enum {
	ENTER_FIRST_PASS, RE_ENTER_PASS, MAIN_OPTIONS, ENTER_OLD_PASS
} State;
State currentState = ENTER_FIRST_PASS;
///////////////////////////////////////////
void GetFirstPass(void);
void GetSecondPass (void);
void GetOldPass (void);
void GetEnterKey (void);
void MainOptions (void);

////////////////////////////////////////////
void GetFirstPass(void)
{
	LCD_clearScreen();
	LCD_displayString(" PLZ enter pass:");
	LCD_moveCursor(1, 0);
	//UART_sendByte(FIRST_PASS);
	for (uint8 i = 0; i < 5; i++) {
		UART_sendByte(FIRST_PASS);
		key = KEYPAD_getPressedKey();
		if ((key >= 0) && (key <= 9)) {
			LCD_displayCharacter('*');
			UART_sendByte(key);
			_delay_ms(200);
		}
	}
	currentState = RE_ENTER_PASS;
	value = 1;
	GetEnterKey();
}
/////////////////////////////////////////////////
void GetSecondPass (void)
{
	value = 2;
	//UART_sendByte(SECOND_PASS);
		for (uint8 i = 0; i < 5; i++) {
			UART_sendByte(SECOND_PASS);

			key = KEYPAD_getPressedKey();
			if ((key >= 0) && (key <= 9)) {
				LCD_displayCharacter('*');
				UART_sendByte(key);
				_delay_ms(200);
			}
		}

		GetEnterKey();
}
///////////////////////////////////////////////
void GetOldPass (void)
{
	LCD_moveCursor(1, 0);
	//UART_sendByte(OLD_PASS);
		for (int i = 0; i < 5; i++) {
			UART_sendByte(OLD_PASS);
			key = KEYPAD_getPressedKey();
			if ((key >= 0) && (key <= 9)) {

				LCD_displayCharacter('*');
				UART_sendByte(key);
				_delay_ms(200);
			}

		}

		value = 3;
		GetEnterKey();
}
/////////////////////////////////////////////////
void MainOptions (void)
{

			key = KEYPAD_getPressedKey();
			if ((key == '+')) {
				LCD_clearScreen();
				LCD_displayString("plz enter pass:");
				LCD_moveCursor(1, 0);

				flag=1;
				currentState = ENTER_OLD_PASS;
			} else if (key == '-') {
				LCD_clearScreen();
				LCD_displayString("plz enter pass:");
				flag=2;
				currentState = ENTER_OLD_PASS;
GetOldPass();

}
}
///////////////////////////////////////////////
void GetEnterKey (void)
{
	key = KEYPAD_getPressedKey();
		if (key == '=') {

			switch (value) {

			case 1:
				_delay_ms(200);
				LCD_clearScreen();
				LCD_displayString("plz re-enter");
				LCD_moveCursor(1, 0);
				LCD_displayString("same pass:");

				break;
			case 2:
				_delay_ms(200);
				if (UART_recieveByte() == CORRECT_PASS) {
					LCD_clearScreen();
					LCD_displayString("+:open door");
					LCD_moveCursor(1, 0);
					LCD_displayString("-:change pass");

					currentState = MAIN_OPTIONS;


				} else {
					currentState = ENTER_FIRST_PASS;


				}
				break;
			case 3:
				_delay_ms(200);

			if(flag==1){
				_delay_ms(200);
			if (UART_recieveByte() == CORRECT_PASS) {

			LCD_clearScreen();
			LCD_displayString("Door is");
			LCD_moveCursor(1, 0);
			LCD_displayString("Unlocking");

			}
			else {
		LCD_clearScreen();
		LCD_displayString("pLZ enter pass");

		currentState=ENTER_OLD_PASS;

		}}

		else if(flag==2){
			_delay_ms(200);
		if (UART_recieveByte() == CORRECT_PASS) {
			//_delay_ms(200);
		currentState = ENTER_FIRST_PASS;
		 flag = 0;
		        //GetFirstPass();
			}
			else
		{
			LCD_clearScreen();
	       LCD_displayString("re_enter pass");

           currentState=ENTER_OLD_PASS;
							}
						}
			break;


}
}
}
//////////////////////////////////////////////////////
int main(void)
{
	Timer_ConfigType TIMER = { 0, 0, TIMER_1, PRESCALE_1024, NORMAL };
		Timer_init(&TIMER);

		LCD_init();
		UART_ConfigType UART = { EIGHT_BITS, NO_PARITY, ONE_BIT, 9600 };
		UART_init(&UART);
		while(1)
		{
			switch (currentState) {
					case ENTER_FIRST_PASS:
						GetFirstPass();

						break;
					case RE_ENTER_PASS:
						GetSecondPass();

						break;
					case MAIN_OPTIONS:
						MainOptions();

						break;
					case ENTER_OLD_PASS:
						GetOldPass();

						break;
					default :
						currentState = MAIN_OPTIONS;
						break;
					}
		}
}
