/*
 * TIMER.c
 *
 *  Created on: Jun 17, 2024
 *  Author    : Rana Hany, Sarah Ibrahim, Salma Ashraf, Yasmin Tarek
 */

#include "TIMER.h"
#include "stdint.h"
#include "avr/interrupt.h"
#include "WDGDRV.h"
#include "WDGM.h"
#include "GPIO.h"
#include <avr/wdt.h>

// Status Register
#define SREG_ADDRESS (*(volatile uint8_t *)(0x5F))
// Bit positions in SREG
#define SREG_I_BIT 7

// Timer/Counter1 Control Register A
#define TCCR1A_ADDRESS (*(volatile uint8_t *)(0x80))
// Timer/Counter1 Control Register B
#define TCCR1B_ADDRESS (*(volatile uint8_t *)(0x81))
// Timer/Counter1 Output Compare Register A
#define OCR1A_ADDRESS (*(volatile uint16_t *)(0x88))
// Timer/Counter Interrupt Mask Register
#define TIMSK1_ADDRESS (*(volatile uint8_t *)(0x6F))

// Timer/Counter1 Output Compare Match A Interrupt Enable bit
#define OCIE1A_BIT 1
// Bit positions in TCCR1A
#define WGM12_BIT 3
// Bit positions in TCCR1B
#define CS10_BIT 0
#define CS11_BIT 1

// Port B Data Register
#define PORTB_ADDRESS (*(volatile uint8_t *)(0x25))

// bits for PORTB
#define WDG_REFRESH_TEST_PIN 2 // Test pin

int counter = 0;
extern int WDGMCallCount;

void TIMER_Init()
{
    // Disable global interrupts
    SREG_ADDRESS &= ~(1 << SREG_I_BIT);
    // CTC mode by setting the WGM12 bit in the TCCR1B register, prescaler 64
    TCCR1B_ADDRESS = (1 << WGM12_BIT) | (1 << CS11_BIT) | (1 << CS10_BIT);
    // Calculation for 50ms interval (1MHz * 0.05 / 64 - 1= 780ms)
    // Set compare value for 50ms interval  51.2MS for 800, 50.9ms for 795
    OCR1A_ADDRESS = 795;
    // Enable compare interrupt
    TIMSK1_ADDRESS = (1 << OCIE1A_BIT);
    // Enable global interrupts
    SREG_ADDRESS |= (1 << SREG_I_BIT);
}

// Timer1 Compare Match A ISR
ISR(TIMER1_COMPA_vect)
{
    // Increment the counter
    counter++;

    if (counter == 1)
    {
        // This block will be executed after the first 50ms
        if (WDGMCallCount >= 2)
        {
            // Set test pin to high
            GPIO_Write(WDG_REFRESH_TEST_PIN, 1);

            // Refresh the watchdog
            wdt_reset();

            // Set test pin to low
            GPIO_Write(WDG_REFRESH_TEST_PIN, 0);

            WDGMCallCount = 0;
        }
    }
    else if (counter == 2)
    {
        // This block will be executed after the next 50ms (or 100ms from the start)
        if ((WDGMCallCount >= 2) && (WDGM_PovideSuppervisionStatus() == OK))
        {
            // Set test pin to high
            GPIO_Write(WDG_REFRESH_TEST_PIN, 1);
            // Refresh the watchdog
            wdt_reset();
            // Set test pin to low
            GPIO_Write(WDG_REFRESH_TEST_PIN, 0);
            
            WDGMCallCount = 0;
        }
        // Reset the counter after it reaches 2
        counter = 0;
    }
}
