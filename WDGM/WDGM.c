/*
 * WDGM.c
 *
 *  Created on: Jun 17, 2024
 *  Author    : Rana Hany, Sarah Ibrahim, Salma Ashraf, Yasmin Tarek
 */

#include "WDGM.h"
#include "stdint.h"
#include "WDGDRV.h"

static uint16_t WDGTimer = 0;		 // Timer to manage the 100ms period
static uint8_t alivenessCounter = 0; // Counter for LEDM calls within 100ms
static WDGM_StatusType WDGStatus;	 // NOK = 1, OK = 0
int WDGMCallCount;

// Port B Data Register
#define PORTB_ADDRESS (*(volatile uint8_t *)(0x25))

// bits for PORTB
#define WDG_WDGM_TEST_PIN 4 // Test pin

void WDGM_Init()
{
	// Counter to keep track of 100ms periods
	WDGTimer = 0;
	// Initialize WDGM_MainFunction call counter
	WDGMCallCount = 0;
	// Initialize call counter
	alivenessCounter = 0;
	WDGStatus = NOK;
}

void WDGM_MainFunction()
{
	// Toggle the test pin
	PORTB_ADDRESS ^= (1 << WDG_WDGM_TEST_PIN);

	// Increment by 20ms (this function is called every 20ms)
	WDGTimer += 20;

	if (WDGTimer >= 100)
	{
		// Check the number of calls within 100ms period
		if (alivenessCounter >= 8 && alivenessCounter <= 12)
		{
			WDGStatus = OK;
		}
		else
		{
			WDGStatus = NOK;
		}
		// Reset LEDM_Manage call counter
		alivenessCounter = 0;
		// Reset timer for the next 100ms period
		WDGTimer = 0;
	}
	// Update the watchdog call counter to indicate this function is not stuck
	WDGMCallCount++;
}

WDGM_StatusType WDGM_PovideSuppervisionStatus()
{
	return WDGStatus;
}

void WDGM_AlivenessIndication()
{
	alivenessCounter++;
}
