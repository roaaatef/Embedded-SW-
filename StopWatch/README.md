AVR Stopwatch (Count-Up / Count-Down Timer)

Objective: A digital stopwatch built on an AVR microcontroller, displaying hours/minutes/seconds on multiplexed 7-segment displays, with support for reset, pause/resume, count-up/count-down mode toggling, and manual time adjustment via push buttons.

Hardware Used


AVR microcontroller — uses GICR, MCUCR, and MCUCSR registers for external interrupt configuration, which are specific to the ATmega16/ATmega32 family. The exact part number isn't stated in the source file — check your .cproject/Atmel Studio project settings to confirm it.
6× 7-segment displays, multiplexed (time-shared) via 6 enable lines on PORTA (bits 0–5), each digit fed the same BCD data lines on the lower nibble of PORTC.
BCD-to-7-segment decoder driving the displays from PORTC's lower nibble (the code writes 4-bit BCD values, not raw segment patterns, implying an external decoder IC such as a 7447/7448 sits between PORTC and the display segments).
Push buttons on PORTB (configured as inputs with internal pull-ups enabled): PB7 (mode toggle), PB6/PB5 (seconds inc/dec), PB4/PB3 (minutes inc/dec), PB1/PB0 (hours inc/dec).
Reset and Pause/Resume push buttons wired to external interrupt pins, using INT0, INT1, and INT2 (configured via MCUCR/MCUCSR/GICR).
Buzzer and 2 LEDs on PORTD: a buzzer/indicator on PD0, and two mode-indicator LEDs on PD4 (count-up) and PD5 (count-down).


How It Works

Timekeeping


Timer1 is configured in CTC mode with a 1024 prescaler and a compare value (OCR1A) of 15624, producing a 1-second interrupt tick (ISR(TIMER1_COMPA_vect)).
On each tick, depending on count_mode:

Count-up mode (count_mode == 0): increments seconds, then cascades the carry through seconds → minutes → hours via check_condition_count_up(), resetting to 00:00:00 after reaching 24:00:00.
Count-down mode (count_mode == 1): decrements seconds, cascading the borrow through seconds → minutes → hours via check_condition_count_down(). When the time reaches 00:00:00, PD0 (buzzer) is set high.





External Interrupts


INT0 (falling edge): resets all time digits to zero and restarts Timer1 from zero.
INT1 (rising edge): sets a pause flag, clears PD0, and stops Timer1 by removing the clock-select bits (keeping CTC mode configured).
INT2 (falling edge): clears the pause flag and restarts Timer1's clock (resume).


Display


display_time() multiplexes all 6 digits by enabling one PORTA pin at a time (with a 1 ms hold), writing the corresponding digit's value to PORTC's lower nibble, then disabling that digit before moving to the next — repeated continuously in the main loop.


Mode Toggle & Manual Adjustment


Pressing PB7 toggles between count-up and count-down mode and toggles the two mode-indicator LEDs (PD4/PD5), waiting (while still updating the display) until the button is released.
While pause is active, the six adjustment buttons (PB6/PB5, PB4/PB3, PB1/PB0) allow incrementing or decrementing seconds, minutes, and hours respectively, each with its own rollover/borrow handling and a release-wait loop that keeps the display updating.


Tools

Eclipse-based AVR toolchain (per the included .project/.cproject files)
