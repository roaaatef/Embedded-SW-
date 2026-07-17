/*
 * Control_ECU.c
 *
 *  Created on: Oct 28, 2024
 *      Author: hp202
 */
/*
 * control.c
 *
 *  Created on: Oct 31, 2024
 *      Author: Manar
 */

#include "uart.h"
#include "external_eeprom.h"
#include "twi.h"
#include <util/delay.h>
#include "DC_MOTOR.h"
#include "Timer.h"
#include "PIR.h"
////////////////////////////////////////
#define PASS_ADDRESS 0x0000
#define FIRST_PASS 0x00
#define SECOND_PASS 0x01
#define OLD_PASS 0x02
#define BZZER_ON 0x03
#define MOTOR_ON 0x04
#define CORRECT_PASS 0x05
#define WRONG_PASS 0x06
///////////////////////////////////////////////////////////////////
uint8 checkpass(uint8 *key1, uint8 size, uint8 *key2) {
	for (int i = 0; i < size; i++) {
		if (key1[i] != key2[i]) {
			return 0;
		}
	}
	return 1;
}
///////////////////////////////////////////////////////////////////
int main(void) {
	uint8 flag;
	uint8 key1[5];
	uint8 key2[5];
	uint8 key3[5];
	uint8 key4[5] ;
	////////////////////////////////////////////////////////////////
	DcMotor_Init();
	 Buzzer_init();
	UART_ConfigType UART = { EIGHT_BITS, NO_PARITY, ONE_BIT, 9600 };
	UART_init(&UART);
	TWI_ConfigType TWI = { 0x01, 0x02 };
	TWI_init(&TWI);
	Timer_ConfigType TIMER = { 0, 0, TIMER_0, PRESCALE_1024, NORMAL };
	Timer_init(&TIMER);
//////////////////////////////////////////////////////////////////////
	while (1) {


		for (int i = 0; i < 5; i++) {
			if(UART_recieveByte()==FIRST_PASS){
			key1[i] = UART_recieveByte();

			_delay_ms(200);
		}}

//////////////////////////////////////////////////////////

		for (int i = 0; i < 5; i++) {
			if(UART_recieveByte()==SECOND_PASS){
			key2[i] = UART_recieveByte();
               _delay_ms(200);
		}}
		//////////////////////////////////////////////////////////
		if (checkpass(key1, 5, key2) == 1) {

			UART_sendByte(CORRECT_PASS);
			//_delay_ms(200);
			for (int i = 0; i < 5; i++) {
				EEPROM_writeByte(PASS_ADDRESS + i, key1[i]);
				_delay_ms(10);
			}
		} else {
			UART_sendByte(WRONG_PASS);
		}
/////////////////////////////////////////////////////////

		for (int i = 0; i < 5; i++) {
			if(UART_recieveByte()==OLD_PASS){
			key3[i] = UART_recieveByte();

			_delay_ms(200);
		}}

		for (int i = 0; i < 5; i++) {
			flag = EEPROM_readByte(PASS_ADDRESS + i, &key4[i]);

			_delay_ms(10);
		}


		if (checkpass(key3, 5, key4) == 1) {
			_delay_ms(200);
			UART_sendByte(CORRECT_PASS);

			//Timer_init(&TIMER);
		} else {
			_delay_ms(200);
			UART_sendByte(WRONG_PASS);

						}



	}}
