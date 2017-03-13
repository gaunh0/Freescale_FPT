#include "SysTicks.h"

uint32_t flag,temp;

void config_STicks(uint32_t rlo)
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
