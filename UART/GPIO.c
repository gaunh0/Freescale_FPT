#include "GPIO.h"

#define LED_G 5
#define LED_R 29

void LED_init(void) 
{
	SIM->SCGC5 |= (1ul<<12) | (1ul<<13); /* Enable Clock for port D and E */
	PORTD->PCR[5] |= (1ul<<8); /* Pin D.5 as GPIO */
	PTD->PDDR |= (1ul<<5); /* Pin D.5 as output */
	PTD->PSOR |= (1ul<<5); /*Turn off LED*/
	
	PORTE->PCR[29] |= (1ul << 8);/* Pin E.29 as GPIO */
	PTE->PDDR |= (1ul<<29); /* Pin E.29 as output */
	PTE->PSOR |= (1ul<<29); /*Turn off LED*/
}
void LED_On(LED_Name LEDx)
{
	if(LEDx == LED_RED)
	{
		PTE->PCOR |= (1ul<<LED_R);
	}
	else if(LEDx == LED_GREEN)
	{
		PTD->PCOR |= (1ul<<LED_G);
	}
}

void LED_Off(LED_Name LEDx)
{
	if(LEDx == LED_RED)
	{
		PTE->PSOR |= (1ul<<LED_R);
	}
	else if(LEDx == LED_GREEN)
	{
		PTD->PSOR |= (1ul<<LED_G);
	}
}
void LED_Tgg(LED_Name LEDx)
{
		if(LEDx == LED_RED)
	{
		PTE->PTOR |= (1ul<<LED_R);
	}
	else if(LEDx == LED_GREEN)
	{
		PTD->PTOR |= (1ul<<LED_G);
	}
}
