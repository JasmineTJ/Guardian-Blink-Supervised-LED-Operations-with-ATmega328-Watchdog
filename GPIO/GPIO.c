/*
 * GPIO.c
 *
 *  Created on: Jun 17, 2024
 *  Author    : Rana Hany, Sarah Ibrahim, Salma Ashraf, Yasmin Tarek
 */

#include "GPIO.h"
#include "stdint.h"

// Port B Data Direction Register
#define DDRB_ADDRESS (*(volatile uint8_t *)(0x24))

// Port B Data Register
#define PORTB_ADDRESS (*(volatile uint8_t *)(0x25))

// Data Direction Register bit for PORTB0
#define DDB0_BIT 0
// Data Direction Register bit for PORTB1
#define DDB1_BIT 1
// Data Direction Register bit for PORTB2
#define DDB2_BIT 2
// Data Direction Register bit for PORTB3
#define DDB3_BIT 3
// Data Direction Register bit for PORTB4
#define DDB4_BIT 4

// bits for PORTB0
#define PORTB0_BIT 0 // LED pin

void GPIO_Init(void)
{
    // Initialize the GPIO pin for the LED
    DDRB_ADDRESS |= (1 << DDB0_BIT);    // Set PORTB0 as output
    DDRB_ADDRESS |= (1 << DDB1_BIT);    // Set PORTB1 as output
    DDRB_ADDRESS |= (1 << DDB2_BIT);    // Set PORTB2 as output
    DDRB_ADDRESS |= (1 << DDB3_BIT);    // Set PORTB3 as output
    DDRB_ADDRESS |= (1 << DDB4_BIT);    // Set PORTB4 as output
    // Set the LED pin
    PORTB_ADDRESS |= (1 << PORTB0_BIT);
}

void GPIO_Write(unsigned char PinId, unsigned char PinData)
{
    // Configure the pin on port B
    PORTB_ADDRESS &= ~(0x1 << PinId);    // Clear the pin
    PORTB_ADDRESS |= (PinData << PinId); // Set data to the pin
}
