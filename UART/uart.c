#include "uart.h"

#define SBR 0x13
#define OSR 0x0F


void UART_init()
{

	/*Clock for UART and PORT A */
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	/*A[1] and A[2] as Tx Rx*/
	PORTA->PCR[1] = PORT_PCR_MUX(2);					
	PORTA->PCR[2] = PORT_PCR_MUX(2);
	
	/*Open Drain for UART 0*/
	SIM->SOPT5 |= SIM_SOPT5_UART0ODE_MASK;
	SIM->SOPT5 |= SIM_SOPT5_UART0TXSRC(0);

		/* UART clock */	
	SIM->SOPT2 &= (~SIM_SOPT2_PLLFLLSEL_MASK);
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	
	/* Baudrate = clock/((OSR + 1) x SBR[12:0])   
	 OSR = 15 (0x0F) , clock = 24MHz, baudrate = 115200
-> SBR = 0x13	
	 LBKDIE = 0, RXEDGIE = 0, SBNS = 0 */

	UART0->C4 = UART0_C4_OSR(OSR);
	UART0->BDH &= ~(UART0_BDH_LBKDIE_MASK|UART0_BDH_SBNS_MASK|UART0_BDH_RXEDGIE_MASK);
  UART0->BDL |= UART0_BDL_SBR(SBR);
	
	/*8 bit data*/
	UART0->C1 &= ~UART0_C1_M_MASK;
	
	/*Parity none*/
	UART0->C1 &= ~UART0_C1_PE_MASK;
	
	/*Data polarity*/
	UART0->S2 &= ~UART0_S2_MSBF_MASK;
	/**/
	//UART0->C2 |= UART0_C2_RIE_MASK;
	/* Enable UART0 transmit/receive */
  UART0->C2 |=  UART0_C2_RE_MASK
						|UART0_C2_TE_MASK;
	/**/
	//NVIC_EnableIRQ(UART0_IRQn);
	
}

void UART_putc(char c)
{
	while (!(UART0->S1 & UART0_S1_TDRE_MASK)); 		
	UART0->D = (uint8_t) c;		
}
char UART_getc(void)
{
	while (!(UART0->S1 & UART0_S1_RDRF_MASK)); 		
	return(UART0->D);
}
	void print(char *ptr_str)
{
	while(*ptr_str)
		UART_putc(*ptr_str++);
}
int fputc(int c, FILE *f)
{
  UART_putc(c);
	return (c & 0xFF);
}
int fgetc(FILE *f)
{
  return (UART_getc());
}
