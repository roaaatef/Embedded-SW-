Smart Home Automation System (AVR Embedded System)

Objective: An embedded smart home controller that monitors temperature, light intensity, and flame presence, and automatically controls a cooling fan, RGB status LEDs, and a fire alarm buzzer based on sensor readings, with live status shown on an LCD.

Hardware Used


AVR microcontroller — the ADC driver's header comment explicitly identifies this as an ATmega16 target (adc.c: "Source file for the ATmega16 ADC driver"). Register usage (ADMUX, ADCSRA, TCCR0, OCR0) is consistent with the ATmega16/ATmega32 family.
LM35 analog temperature sensor — read via ADC channel 1, using the internal 2.56V reference, with a defined max sensor range of 150°C.
LDR (light-dependent resistor) sensor — read via ADC channel 0, using the internal 2.56V reference, scaled to a 0–100% intensity range.
Flame sensor — digital input, used to detect fire/flame presence.
DC motor (used as a cooling fan), driven via 2 direction-control GPIO pins and 1 enable pin, with PWM speed control through Timer0.
Buzzer — GPIO-driven on/off, used as a fire alarm.
3 discrete LEDs (Red, Green, Blue), used as light-intensity status indicators.
Character LCD, configured for 8-bit data mode, used to display live temperature, light intensity, and system status.


Software Architecture


std_types.h — platform type abstraction (uint8, uint16, boolean, etc.)
common_macros.h — bit-manipulation macros (SET_BIT, CLEAR_BIT, GET_BIT, etc.)
gpio.c / gpio.h — generic pin/port direction, read, and write driver
adc.c / adc.h — ADC driver, configured for internal 2.56V reference with a prescaler, used to read both analog sensors
lm35_sensor.c / lm35_sensor.h — converts the raw ADC reading on channel 1 into a temperature value (°C)
LDR_sensor.c / LDR_sensor.h — converts the raw ADC reading on channel 0 into a light intensity percentage
Flame_sensor.c / Flame_sensor.h — reads the digital flame sensor pin
PWM.c / PWM.h — starts Timer0 in Fast PWM mode (non-inverting on OC0) with a given duty cycle
DC_MOTOR.c / DC_MOTOR.h — controls motor direction (CW/CCW/STOP) via 2 direction pins and speed via PWM duty cycle
LED.c / LED.h — RGB LED driver, supporting positive/negative logic configuration per LED
BUZZER.c / BUZZER.h — simple buzzer on/off driver
lcd.c / lcd.h — character LCD driver (string/character/integer display, cursor positioning)
SmartHome.c / SmartHome.h — application logic (main) tying all drivers together, plus display-formatting helper functions


How It Works


On startup, the ADC, buzzer, DC motor, flame sensor, LCD, and LEDs are all initialized, and the static LCD labels ("Temp= C", "LDR= %") are printed once.
In the main loop, the system continuously:

Checks the flame sensor. If flame is detected, the LCD shows "Critical Alert!" and the buzzer turns on; the system waits (blocking) until the flame is no longer detected, then clears the alert, restores the normal display, and turns the buzzer off.
Reads light intensity from the LDR sensor and updates the LCD, then sets the 3 LEDs based on intensity thresholds:

< 15%: all 3 LEDs on
16–50%: Red + Green on, Blue off
51–70%: Red on only
> 70%: all LEDs off



Reads temperature from the LM35 sensor and updates the LCD, then controls the fan (DC motor, always rotating clockwise) with a speed that scales with temperature:

≥ 40°C: 100% speed
35–39°C: 75% speed
30–34°C: 50% speed
25–29°C: 25% speed
< 25°C: fan off (0% speed)








Tools

Eclipse-based AVR toolchain (per the included .project/.cproject files)
