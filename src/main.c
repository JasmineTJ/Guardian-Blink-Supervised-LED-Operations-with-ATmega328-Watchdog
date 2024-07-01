/*
 * main.c
 *
 *  Created on: Jun 17, 2024
 *  Author    : Rana Hany, Sarah Ibrahim, Salma Ashraf, Yasmin Tarek
 */

#include "GPIO.h"
#include "LEDM.h"
#include "WDGM.h"
#include "WDGDRV.h"
#include "TIMER.h"
#include <util/delay.h>

static uint8_t WDGM_CallTimer = 0;
// Port B Data Register
#define PORTB_ADDRESS (*(volatile uint8_t *)(0x25))

// bits for PORTB
#define WDG_RESET_TEST_PIN 1 // Test pin

int main()
{
	LEDM_Init();

	PORTB_ADDRESS |= (1 << WDG_RESET_TEST_PIN); // Set data to the pin
	_delay_ms(400);
	PORTB_ADDRESS &= ~(0x1 << WDG_RESET_TEST_PIN); // Clear the pin

	// Initialize components
	WDGM_Init();
	TIMER_Init();
	WDGDrv_Init();

	// main loop
	while (1)
	{
		// Called every 10ms
		LEDM_Manage();
		// Standard delay function to manage timing
		_delay_ms(10);
		// Increment counter every 10ms
		WDGM_CallTimer += 10;
		if (WDGM_CallTimer == 20)
		{
			// Called every 20ms
			WDGM_MainFunction();
			// Reset counter after 20ms
			WDGM_CallTimer = 0;
		}
	}

	return 0;
}
