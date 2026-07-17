/*
 * LED.h
 *
 *  Created on: Oct 2, 2024
 *      Author: hp202
 */

#ifndef LED_H_
#define LED_H_

///////////////////////////////
#define RED_LED_PORT_ID   PORTB_ID
#define GREEN_LED_PORT_ID  PORTB_ID
#define BLUE_LED_PORT_ID  PORTB_ID
#define RED_LED_PIN_ID      PIN5_ID
#define GREEN_LED_PIN_ID      PIN6_ID
#define BLUE_LED_PIN_ID      PIN7_ID
#define POSITIVE_LOGIC         1
#define NEGATIVE_LOGIC         0 //turn on when in is zero
#define RED_LED_CONNECTION   POSITIVE_LOGIC
#define GREEN_LED_CONNECTION   POSITIVE_LOGIC
#define BLUE_LED_CONNECTION   POSITIVE_LOGIC

////////////////////////////////////////////////
typedef enum{
	RED_LED , GREEN_LED , BLUE_LED
} LED_ID;



//typedef enum{
	//TURN_ON,TURN_OFF
//}LED_NEGATIVE_LOGIC;

void LEDS_init(void);
void LED_on(LED_ID id);
void LED_off(LED_ID id);



#endif /* LED_H_ */
