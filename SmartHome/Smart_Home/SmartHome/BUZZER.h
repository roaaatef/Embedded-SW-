/*
 * BUZZER.h
 *
 *  Created on: Oct 2, 2024
 *      Author: hp202
 */

#ifndef BUZZER_H_
#define BUZZER_H_
///////////////////////////////////
#define BUZZER_PORT_ID     PORTD_ID
#define BUZZER_PIN_ID         PIN3_ID
/////////////////////////////////

void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);


#endif /* BUZZER_H_ */
