/*
[GST2016]
Name: Nguyen Thanh Khiem
Mssv: 13520395
Description: Implement the code to control LEDs by buttons. Press button to turn on LED; Release button
to turn off LED
*/
#include <MKL46Z4.h>
#include <stdio.h>

void LED_init(void);
void SW1_init(void);


int main(void) {
	LED_init();
	SW1_init();
	while(1)
		{
		if (!(PTC->PDIR == (1ul << 3))) /*When SW is pressed*/
		{
				PTE->PCOR |= (1ul<<29); /*Clear PTE29, turns LED ON (Cathode connected to PTE29)*/
				while (!(PTC->PDIR == (1ul << 3))) {} /*When SW still pressed*/
		}
		else PTE->PSOR |= (1ul<<29); /*Set PTE29 = 1, turns LED OFF (Cathode connected to PTE29)*/
		}
}

void LED_init(void)
	{
		SIM->SCGC5 |= (1ul << 13); /* Enable Clock for port E */
		PORTE->PCR[29] |= (1ul << 8);/* Pin E.29 as GPIO */
		PTE->PDDR |= (1ul<<29); /* Pin E.29 as output */
		PTE->PSOR |= (1ul<<29); /*Turn off LED*/
	}
void SW1_init(void)
{	
		SIM->SCGC5 |= (1ul << 11);  /* Enable Clock for port C */
		PORTC->PCR[3] |= (1ul << 8) | (1UL << 1) | (1UL << 0); /* Pin C.3 as GPIO | Enable pullup resitor */
		PTC->PDDR |= (0ul<<3); /* Pin C.3 as input */
}
