# Guardian Blink: Supervised LED Operations with ATmega328P Watchdog

## Project Overview
This project involves implementing a LED blinking system supervised by a watchdog timer on an ATmega328P microcontroller. The LED blinking is managed by two software components: `LEDMgr` and `GPIO`. The watchdog management is handled by two components: `WDGDrv` and `WDGM`.

## Software Components
### LEDMgr
- `LED_Init`: Initializes the LED component internal variables.
- `LED_Manage`: Manages the LED blinking actions using the `GPIO_Write` function.

### GPIO
- `GPIO_Init`: Initializes GPIO configuration for the PIN that controls the LED.
- `GPIO_Write`: Writes a specific value (0 or 1) to that pin.

### WDGDrv
- `WDGDrv_Init`: Configures the watchdog driver to support the following features:
  - Set the Maximum timeout value to 64ms.
  - Activate the watchdog.

### WDGM
- `WDGM_Init`: Initializes the WDGM internal variables.
- `WDGM_MainFunction`: Checks the number of calls of the `LEDM_MainFunction` within a 100ms period.
- `WDGM_AlivenessIndication`: Detects the call of the `LEDM_Manage` function at the correct timing.
- `WDGM_ProvideSuppervisionStatus`: Provides the Status of the LEDM entity to the WDGDrv.

## Skills Used
- C Language
- AVR Architecture
- Understanding of ATmega328P Microcontrollers and Watchdog Timers
