Car Parking Assistant (AVR Embedded System)

Objective: An embedded car parking sensor system that measures distance to an obstacle using an ultrasonic sensor and provides real-time visual (LCD + RGB LED) and audible (buzzer) feedback as a vehicle approaches an obstacle.

Hardware Used


AVR microcontroller — driven via direct register access (avr/io.h: DDRA/B/C/D, PORTA/B/C/D, PINA/B/C/D, TCCR1A/B, TIMSK, TCNT1, ICR1). The exact part number isn't stated in the source files — check your .cproject/Atmel Studio project settings to confirm it.
Ultrasonic distance sensor — driven by a trigger pin (GPIO output) and read via Timer1's Input Capture Unit (ICU) to time the echo pulse. The specific sensor model isn't named in the code.
Character LCD — driven by a custom GPIO-based driver, configurable for 4-bit or 8-bit data mode (LCD_DATA_BITS_MODE); this project's lcd.h sets it to 4-bit mode.
3 discrete LEDs, referred to in code as Red, Green, and Blue, each independently and individually controlled.
Buzzer — GPIO-driven on/off.

Software Architecture

The project is built on a layered, reusable AVR driver stack:


std_types.h — platform type abstraction (uint8, uint16, boolean, etc.)
common_macros.h — bit-manipulation macros (SET_BIT, CLEAR_BIT, GET_BIT, etc.)
gpio.c / gpio.h — generic pin/port direction, read, and write driver
icu.c / icu.h — Input Capture Unit driver (Timer1-based), used to time the ultrasonic echo pulse via interrupt callback
UltraSonic.c / UltraSonic.h — ultrasonic sensor driver: triggers a pulse, uses the ICU to capture rising/falling edge timestamps, and converts pulse width to distance in cm
lcd.c / lcd.h — character LCD driver (string/character/integer display, cursor positioning)
LED.c / LED.h — RGB LED driver, supporting positive/negative logic configuration per LED
BUZZER.c / BUZZER.h — simple buzzer on/off driver
CarParking.c — application logic (main) tying all drivers together


How It Works


On startup, all peripherals (LCD, ultrasonic sensor, LEDs, buzzer) are initialized, and global interrupts are enabled.
In an infinite loop, the system continuously:

Triggers the ultrasonic sensor and reads back the measured distance
Displays the distance (in cm) on the LCD
Adjusts LED and buzzer state based on proximity zones:

≤ 5 cm: "STOP" displayed, buzzer on, all 3 LEDs flash together
6–10 cm: Red + Green + Blue LEDs on (closest safe warning zone)
11–15 cm: Red + Green LEDs on
16–20 cm: Red LED only
> 20 cm: all LEDs off (safe distance)

Tools

Eclipse-based AVR toolchain (per the included .project/.cproject files)
