# Door Locker Security System (AVR Embedded System)

**Objective:** A two-microcontroller, password-protected door lock system. One ECU (**HMI**) handles the keypad/LCD user interface; the other (**Control**) verifies passwords, manages persistent password storage, and drives the door motor and alarm. The two communicate over UART using a simple control-byte protocol.

## System Overview

```
 ┌─────────────────┐        UART (9600, 8N1)        ┌─────────────────┐
 │     HMI ECU      │ ─────────────────────────────► │   Control ECU    │
 │  (Keypad + LCD)  │ ◄───────────────────────────── │ (Motor/Buzzer/   │
 │                  │                                 │  EEPROM/PIR)     │
 └─────────────────┘                                 └─────────────────┘
```

- The **HMI ECU** collects password digits from a keypad, displays prompts/status on an LCD, and sends each digit to the Control ECU tagged with a control byte (`FIRST_PASS`, `SECOND_PASS`, or `OLD_PASS`) indicating which stage of entry it belongs to.
- The **Control ECU** receives these tagged digits, compares first/second password entries, stores a verified password in external EEPROM, and later checks an "old password" attempt against the stored value — reporting `CORRECT_PASS` or `WRONG_PASS` back to the HMI ECU, which drives the door motor/buzzer decisions on the HMI side accordingly.

## Hardware Used

**Shared across both ECUs:**
- **AVR microcontrollers** — driven via direct register access (`avr/io.h`). The exact part numbers aren't stated in the source files.
- **UART interface** between the two ECUs — 8 data bits, no parity, 1 stop bit, 9600 baud.

**HMI ECU specific:**
- **4×4 matrix keypad**, read via a row/column scanning driver.
- **Character LCD**, configured for **8-bit data mode**, displaying prompts, masked password entry (`*`), and status messages.

**Control ECU specific:**
- **DC motor** (door lock mechanism), controlled via 2 direction pins + 1 enable pin, with PWM speed control through Timer0.
- **Buzzer** — GPIO-driven on/off alarm.
- **PIR motion sensor** — digital input driver is present in the project (`PIR.c`/`PIR.h`), though it is not called anywhere in `Control_ECU.c`'s `main()` as provided.
- **External I2C EEPROM** (24Cxx-style) — persistent password storage, addressed via TWI/I2C with device address `0xA0` (plus address bits A8–A10 from the memory location).

## Software Architecture

Both ECUs share a common driver base:
- **`std_types.h`** — platform type abstraction (`uint8`, `uint16`, `boolean`, etc.)
- **`common_macros.h`** — bit-manipulation macros (`SET_BIT`, `CLEAR_BIT`, `GET_BIT`, etc.)
- **`gpio.c` / `gpio.h`** — generic pin/port direction, read, and write driver
- **`uart.c` / `uart.h`** — UART driver: configurable data bits, parity, stop bits, baud rate; byte/string send/receive
- **`Timer.c` / `Timer.h`** — generic driver for Timer0/Timer1/Timer2 (Normal/Compare modes, configurable prescaler, interrupt callback mechanism)

**HMI ECU adds:**
- **`keypad.c` / `keypad.h`** — 4×4 matrix keypad driver, mapping scanned positions to key values (digits 0–9, `*`, `#`/`=`, `+`, `-`)
- **`lcd.c` / `lcd.h`** — character LCD driver
- **`HMI_ECU.c`** — application logic implementing the user-facing state machine

**Control ECU adds:**
- **`twi.c` / `twi.h`** — TWI (I2C) driver: start/stop conditions, byte read/write, status reading
- **`external_eeprom.c` / `external_eeprom.h`** — byte-level read/write to external I2C EEPROM, built on the TWI driver
- **`PWM.c` / `PWM.h`** — starts Timer0 in Fast PWM mode (non-inverting on OC0) with a given duty cycle
- **`DC_MOTOR.c` / `DC_MOTOR.h`** — controls motor direction (CW/CCW/STOP) and speed via PWM
- **`BUZZER.c` / `BUZZER.h`** — buzzer on/off driver
- **`PIR.c` / `PIR.h`** — reads the digital state of a PIR motion sensor
- **`Control_ECU.c`** — application logic implementing password verification and door/alarm control

## How It Works

### HMI ECU — user-facing state machine (`HMI_ECU.c`)
1. **`ENTER_FIRST_PASS`** — prompts for a password, reads 5 keypad digits (each preceded by a `FIRST_PASS` byte sent over UART), masks entry with `*` on the LCD. On `=`, prompts to re-enter and moves to `RE_ENTER_PASS`.
2. **`RE_ENTER_PASS`** — reads a second 5-digit password (gated by `SECOND_PASS`). On `=`, waits for the Control ECU's `CORRECT_PASS`/`WRONG_PASS` response: success shows the main menu ("+: open door", "-: change pass") and moves to `MAIN_OPTIONS`; failure returns to `ENTER_FIRST_PASS`.
3. **`MAIN_OPTIONS`** — `+` prompts for a password and moves to `ENTER_OLD_PASS` with `flag = 1` (open door); `-` prompts for a password, sets `flag = 2` (change password), and calls `GetOldPass()` directly.
4. **`ENTER_OLD_PASS`** — reads 5 digits gated by `OLD_PASS`, then waits for the verification response:
   - `flag == 1`: on success, displays "Door is Unlocking"; on failure, re-prompts and stays in this state.
   - `flag == 2`: on success, resets `flag` and returns to `ENTER_FIRST_PASS` to set a new password; on failure, re-prompts and stays in this state.

### Control ECU — password verification (`Control_ECU.c`)
1. On startup, initializes the DC motor, buzzer, UART (8N1, 9600), TWI (address `0x01`, bit-rate setting `0x02`), and Timer0 (Normal mode, 1024 prescaler — no callback registered in the code shown).
2. In its main loop, it repeatedly:
   - Receives a 5-byte password (`key1`), capturing each byte only when preceded by the `FIRST_PASS` control byte.
   - Receives a second 5-byte password (`key2`), gated by `SECOND_PASS`.
   - Compares `key1`/`key2` byte-by-byte. Match → sends `CORRECT_PASS` and writes the password to EEPROM (at `PASS_ADDRESS`); mismatch → sends `WRONG_PASS`.
   - Receives a 5-byte "old password" attempt (`key3`), gated by `OLD_PASS`.
   - Reads the stored password back from EEPROM into `key4`.
   - Compares `key3`/`key4`; sends `CORRECT_PASS` or `WRONG_PASS` back over UART.
3. This cycle repeats indefinitely.

## Tools
Eclipse-based AVR toolchain (per the included `.project`/`.cproject` files, one set per ECU)
