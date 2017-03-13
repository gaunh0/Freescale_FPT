#include <MKL46Z4.h>
#include <stdio.h>

#define LED_G (1ul << 5)
#define LED_R (1ul << 29)
#define Period1s 23999999 /* 0x016E35FF*/


void LEDs_config(){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
	PORTD->PCR[5] |= PORT_PCR_MUX(1);
	PTD->PDDR |= LED_G;
	
	PORTE->PCR[29] |= PORT_PCR_MUX(1);
	PTE->PDDR |= LED_R;	
}
//47999999
void PIT_Timer(){
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; /*Enable clock for PIT module*/
	PIT->MCR &= PIT_MCR_MDIS_MASK; /*Reset MCR[MDIS]*/
	PIT->CHANNEL[0].LDVAL |= PIT_LDVAL_TSV(Period1s);
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
	
	PIT->CHANNEL[1].LDVAL = 9;
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_CHN_MASK; // set Timer 1 chain Timer 0
	
	NVIC_EnableIRQ(PIT_IRQn);
}
void PIT_IRQHandler()
{
	if(PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK)
	{
			PTD->PTOR |= LED_G;
			PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	}
	if(PIT->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK)
	{
			PTE->PTOR |= LED_R;
			PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
	}
}
int main(){
	SystemInit();
	SystemCoreClockUpdate(); // Setting Clock mode 1, Bus clock = 24Mhz
	LEDs_config();
	PIT_Timer();
	while(1){
	}
	return 0;
}

