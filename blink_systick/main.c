/*
[GST2016]
Name: Nguyen Thanh Khiem
Mssv: 13520395
Description:2.	Using SysTick to implement the code to blink two LEDs as the following:
RED LED blinks at 1Hz; Green LED blink at 2 Hz. ( No Interrupt)
*/
#include "MKL46Z4.h"

uint32_t flag,temp;
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
void config_SysTicks(uint32_t rlo)
{
	SysTick->CTRL = 5; /*CLKSOURCE and ENABLE*/
	SysTick->LOAD = rlo; /*Reload value - 1ms*/
	SysTick->VAL = 0; /*Current Value Register - clear FLAG*/
} 
void delay(uint32_t _time){
		temp =0; 
	  do {
		  flag = SysTick->CTRL >> 16ul; /*Get status FLAG*/
			if(flag == 1ul) {   /*If FLAG set to 1, increment temp*/
				temp++;
				SysTick->VAL = 0; /*clear FLAG*/
				}
		}while (temp != _time); /*Stop if temp = _time*/
}
int main(void){
	SystemCoreClockUpdate(); /*Get SystemCoreClock*/
	config_SysTicks(SystemCoreClock/1000);
	LED_init();
	/* 
	green led:  2Hz
	red led:   1Hz
	*/
	while(1){
			PTE->PCOR |= (1ul << 29); /* LRed on */
			PTD->PCOR |= (1ul << 5); /* LGreen on */
			delay(500);
			PTE->PSOR |= (1ul << 29); /*LRed off*/
			delay(500);
			PTE->PCOR |= (1ul << 29); /* LRed on */
			PTD->PSOR |= (1ul << 5); /* LGreen off */
			delay(500);
			PTE->PSOR |= (1ul << 29); /*LRed off*/
			delay(500);
		}
}
