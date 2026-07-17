/*
 * stopwatch.c
 *
 *  Created on: Sep 12, 2024
 *      Author: hp202
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


unsigned  char pause =0; //check pause flag
unsigned char sec1 = 0, sec2 = 0; //first 2 7-segments
unsigned char min1 = 0, min2 = 0; //second 2 7-segments
unsigned char hr1 = 0, hr2 = 0;   //third 2 7-segments
unsigned char count_mode = 0;  // 0 for counting up, 1 for countdown mode
// interrupt 0 function
void INT0_init(void)
{
  MCUCR|=(1<<ISC01); //trigger INTO with falling edge
  MCUCR&=~(1<<ISC00);
  GICR|=(1<<INT0); //INT0 enable bit

 SREG|=(1<<7); //enable I-bit
}
//interrupt 1 function
void INT1_init(void)
{
  MCUCR|=(1<<ISC11)|(1<<ISC10); //INT1 SENSE CONTROL ,trigger INT1 with raising edge
  GICR|=(1<<INT1); // enable INT1 bit
  SREG|=(1<<7);
}
//interrupt 2 function
void INT2_init(void)
{
 MCUCSR&=~(1<<ISC2); //interrupt2 sense control ,trigger INT2 with falling edge
 GICR|=(1<<INT2); //enable bit
 SREG|=(1<<7);


}
// Function to display time on 7-segment display
void display_time(void) {
    PORTA |= (1 << 5);
    PORTC = (PORTC & 0xF0) | (sec1 & 0x0F);
    _delay_ms(1);
    PORTA &= ~(1 << 5);

    PORTA |= (1 << 4);
    PORTC = (PORTC & 0xF0) | (sec2 & 0x0F);
    _delay_ms(1);
    PORTA &= ~(1 << 4);

    PORTA |= (1 << 3);
    PORTC = (PORTC & 0xF0) | (min1 & 0x0F);
    _delay_ms(1);
    PORTA &= ~(1 << 3);

    PORTA |= (1 << 2);
    PORTC = (PORTC & 0xF0) | (min2 & 0x0F);
    _delay_ms(1);
    PORTA &= ~(1 << 2);

    PORTA |= (1 << 1);
    PORTC = (PORTC & 0xF0) | (hr1 & 0x0F);
    _delay_ms(1);
    PORTA &= ~(1 << 1);

    PORTA |= (1 << 0);
    PORTC = (PORTC & 0xF0) | (hr2 & 0x0F);
    _delay_ms(1);
    PORTA &= ~(1 << 0);
}
//function of timer 1
void timer1_init(void) {
    TCCR1A = (1 <<  FOC1A )|(1<<FOC1B);  // CTC mode
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);  // 1024 prescaler
    TCNT1 = 0; // start from 0
    OCR1A = 15624;  // compare value
    TIMSK = (1 << OCIE1A);  // Enable timer compare interrupt

}


//function of check condition of counting down
void check_condition_count_down(void) {
   if (sec1 == 0 && sec2 == 0 && min1 == 0 && min2 == 0 && hr1 == 0 && hr2 == 0) {
	   PORTD|=(1<<PD0);
       sec1 = sec2 = min1 = min2 = hr1 = hr2 = 0;
   } else {
       if (sec1 == 0) {
           sec1 = 9;
           if (sec2 == 0) {
               sec2 = 5;
               if (min1 == 0) {
                   min1 = 9;
                   if (min2 == 0) {
                       min2 = 5;
                       if (hr1 == 0) {
                           hr1 = 9;
                           hr2--;
                       } else {
                           hr1--;
                       }
                   } else {
                       min2--;
                   }
               } else {
                   min1--;
               }
           } else {
               sec2--;
           }
       } else {
           sec1--;
       }
   }
}

//function of checking condition of counting up
void check_condition_count_up(void) {
    if (sec1 == 10) {
        sec1 = 0;
        sec2++;
    }
    if (sec2 == 6) {
        sec2 = 0;
        min1++;
    }
    if (min1 == 10) {
        min1 = 0;
        min2++;
    }
    if (min2 == 6) {
        min2 = 0;
        hr1++;
    }
    if (hr1 == 10) {
        hr1 = 0;
        hr2++;
    }
    if (hr2 == 2 && hr1 == 4) {  // Reset after 24 hours
        hr1 = hr2 = min1 = min2 = sec1 = sec2 = 0;
    }
}


ISR(TIMER1_COMPA_vect) {
    if (count_mode) {
        check_condition_count_down();  // Count-down mode


    } else {
    	 sec1++;
    	 PORTD&=~(1<<PD0);
        check_condition_count_up();  // Count-up mode

    }
}


ISR(INT0_vect) {

    sec1 = sec2 = min1 = min2 = hr1 = hr2 = 0;
    TCCR1B=(1<<WGM12); //reset the timer
    _delay_ms(10);
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // resume the timer from zero again
}


ISR(INT1_vect) {
	PORTD&=~(1<<PD0);
	pause =1;
    TCCR1B =(1<<WGM12) ; //stop  the timer
}


ISR(INT2_vect) {
	pause =0;
   TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); //resume the timer clk
}

int main(void) {
    DDRB &= 0x00;  // For push buttons
    DDRD &= 0xF3;  // Reset and pause push buttons
    DDRD |= 0x31;  // Buzzer and LEDs
    DDRC |= 0x0F;  // 7-segment decoder
    DDRA |= 0x7F;  // 7-segment enable

    PORTB |= 0xFF;  // Enable  internal pull-up resistors
    PORTA |= 0x3F;  // Enable 7-segment
    PORTC &= 0xF0;  // Reset 7-segment data
    PORTD|=(1<<PD2); //internal pull-up push button

    timer1_init();
    INT0_init();
    INT1_init();
    INT2_init();

    PORTD |= (1 << PD4);  // LED for count-up mode
    PORTD &= ~(1 << PD5);  // LED for count-down mode

    while (1) {
        display_time();  // Continuously update the display

        // Toggle count mode on PB7 press
        if (!(PINB & (1 << PB7))) {
            count_mode ^= 1;  // Toggle mode
            PORTD ^= (1 << PD4);  // Toggle LEDs
            PORTD ^= (1 << PD5);
           while (!(PINB & (1 << PB7))){
              display_time();  // Wait for button release
            }
        }

          if(pause){ //check if pause button is pressed
             if (!(PINB & (1 << PB6))) //press on seconds button increment
            	 {
            	  if (sec1!=10) {sec1++;}
            	 if (sec1 == 10&&sec2!=6) {
            	           sec1 = 0;
            	            sec2++;
            	                          }
            	     if(sec2==6)
            	     {
            		 sec1=0;
            		 sec2=0;
            	     }

                while (!(PINB & (1 << PB6))) {
                      display_time(); //if you press the button you will display one time
                    }

                }
             if(!(PINB&(1<<PB4))) //press on minutes increment
             {
            	 if (min1!=10) {min1++;}
                    if (min1 == 10&&min2!=6) {
            	          min1 = 0;
            	         min2++;
            	            	  }
            	         if(min2==6)
            	          {
            	            min1=0;
            	            min2=0;
            	          }
                            while (!(PINB & (1 << PB4))) {
            	                       display_time();
            	                    }
                                     }
             if(!(PINB&(1<<PB1))) //press on hours increment
             {
            	 if (hr1!=10) {hr1++;}
           	   if (hr1 == 10) {
            	           hr1 = 0;
            	            hr2++;
            	            	   }
            	     if(hr2==2&&hr1==5)
            	            	  {
            	            hr1=0;
            	           hr2=0;
            	            	  }

                     while (!(PINB & (1 << PB1))) {
                          display_time();
                                   }
                                      }
             if(!(PINB&(1<<PB5))) //press on seconds decrement
             {
            	 if (sec1 != 0) {
            	        sec1--;
            	    } else {
            	        if (sec2 != 0) {
            	            sec1 = 9;
            	            sec2--;
            	        }
            	    }
            	        while (!(PINB & (1 << PB5))) {
            	            	        display_time();
            	            	            }
                                          }
             if(!(PINB&(1<<PB3))) //press on minutes decrement
             {
            	 if (min1 != 0) {
            	         min1--;
            	          }
            	 else {
            	        if (min2 != 0) {
            	             	   min1 = 9;
            	             	    min2--;
            	             	        }
            	             	    }
            	     while (!(PINB & (1 << PB3))) {
            	             display_time();
                                        }
                                          }
               if(!(PINB&(1<<PB0))) //press on hours decrement
                         {
                        	 if (hr1 != 0) {
                        	           hr1--;
                        	             }
                        	 else {
                        	     if (hr2 != 0) {
                        	            hr1 = 9;
                        	              hr2--;
                        	             	 }
                        	             	 }
                        	 while (!(PINB & (1 << PB0))) {
                        	      display_time();
                                           }
                                            }
                                               }
                                            }
                                           }






