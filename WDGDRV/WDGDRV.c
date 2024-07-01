/*
 * WDGDRV.c
 *
 *  Created on: Jun 17, 2024
 *  Author    : Rana Hany, Sarah Ibrahim, Salma Ashraf, Yasmin Tarek
 */

#include "WDGDRV.h"
#include "WDGM.h"
#include <avr/wdt.h>
#include "stdint.h"

// Status Register
#define SREG_ADDRESS (*(volatile uint8_t *)(0x5F))
// Bit positions in SREG
#define SREG_I_BIT 7

// Watchdog Timer Control Register
#define WDTCSR_ADDRESS (*(volatile uint8_t *)(0x60))

// Watchdog Timer bits
#define WDE_BIT  3
#define WDCE_BIT 4
#define WDP1_BIT 1
#define WDIE_BIT 6

// MCU Status Register
#define MCUSR_ADDRESS (*(volatile uint8_t *)(0x54))

// Watchdog Reset Flag bit
#define WDRF_BIT 3

// Port B Data Register
#define PORTB_ADDRESS (*(volatile uint8_t *)(0x25))

// bits for PORTB
#define WDG_REFRESH_TEST_PIN 2 // Test pin

void WDGDrv_Init()
{
    // Disable global interrupts
    SREG_ADDRESS &= ~(1 << SREG_I_BIT);

    // Reset Watchdog Timer
    wdt_reset();
    // Start timed sequence */
    WDTCSR_ADDRESS |= (1 << WDCE_BIT) | (1 << WDE_BIT);
    // Set new prescaler(time-out) value = 8K cycles (~64ms), enable interrupts using  | (1<<WDIE)
    WDTCSR_ADDRESS = (1 << WDE_BIT) | (1 << WDP1_BIT) | (1 << WDIE_BIT);

    // Enable global interrupts
    SREG_ADDRESS |= (1 << SREG_I_BIT);
}
