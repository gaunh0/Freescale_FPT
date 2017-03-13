/*
[GST2016]
Name: Nguyen Thanh Khiem
Mssv: 13520395
Description: Implement the code to blink two LEDs with different frequency
*/

#include "stdio.h"
#include "MKL46Z4.h"

void LED_init(void);

int main(void)
{
		uint32_t i;
		LED_init();
		while(1)
		{
			PTD->PCOR |= (1ul<<5); /*Turn on LED green*/
			for(i=0;i<=5000000;i++)
			{
			if(i==1500000)  
				PTE->PCOR |= (1ul<<29); /*Turn on LED red*/
			if(i==2500000) 					
				PTE->PSOR |= (1ul<<29);	/*Turn off LED red*/
			if(i==3500000) 
				PTD->PSOR |= (1ul<<5);	/*Turn off LED green*/
			}
		}
}
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
