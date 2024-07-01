/*
 * LEDM.c
 *
 *  Created on: Jun 17, 2024
 *  Author    : Rana Hany, Sarah Ibrahim, Salma Ashraf, Yasmin Tarek
 */

#include "LEDM.h"
#include "GPIO.h"
#include "WDGM.h"
#include "stdint.h"

// Port B Data Register
#define PORTB_ADDRESS (*(volatile uint8_t *)(0x25))

// bits for PORTB
#define PORTB0_BIT 0        // LED pin
#define WDG_LEDM_TEST_PIN 3 // Test pin

// Define internal variables
static uint16_t LEDTimer;      // Timer to manage the 500ms period
static unsigned char LEDState; // 0 for off, 1 for on

void LEDM_Init(void)
{
    // Initialize led state and counter
    LEDTimer = 0; // Reset timer
    LEDState = 1; // Start with LED on
    GPIO_Init();
}

void LEDM_Manage(void)
{
    // Toggle the test pin
    PORTB_ADDRESS ^= (1 << WDG_LEDM_TEST_PIN);
    // Increment timer by 10ms
    LEDTimer += 10;
    // Check if 500ms has passed
    if (LEDTimer >= 500)
    {
        // Toggle LED state
        LEDState = !LEDState;
        // Write LED state
        GPIO_Write(PORTB0_BIT, LEDState);
        // Reset timer
        LEDTimer = 0;
    }
    // Indicate aliveness
    WDGM_AlivenessIndication();
}
