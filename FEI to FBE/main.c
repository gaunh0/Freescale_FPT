#include "MKL46Z4.h"

void MCG_FBE(void);

int main()
{
	SIM->SCGC5 = SIM_SCGC5_PORTC_MASK;
	SIM->SOPT2 = SIM_SOPT2_CLKOUTSEL(0x2); 
	PORTC->PCR[3] = (PORT_PCR_MUX(0x5)); 
	MCG_FBE();
	while(1)
		{
		}
}
void MCG_FBE(void)
{
	/* SIM->SCGC5: PORTA=1 */
	SIM->SCGC5 |= (1ul << 9);     /* Enable clock gate for ports to enable pin routing */
	/* SIM->CLKDIV1: OUTDIV1=0,,OUTDIV4=0, */
	SIM->CLKDIV1 = (uint32_t)0x00000000UL; /* Update system prescalers */
	/* PORTA->PCR18: ISF=0,MUX=0 */
	PORTA->PCR[18] &= (uint32_t)~0x01000700UL;
	/* PORTA->PCR19: ISF=0,MUX=0 */
	PORTA->PCR[19] &= (uint32_t)~0x01000700UL;
	
	/* Switch to FBE Mode */
	/* MCG->C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
	MCG->C2 = (uint8_t)0x24U;
	/* OSC0->CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=1,SC4P=0,SC8P=0,SC16P=0 */
	OSC0->CR = (uint8_t)0x80U;
	/* MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	MCG->C1 = (uint8_t)0x9AU;
	/* MCG->C4: DMX32=0,DRST_DRS=0 */
	MCG->C4 &= (uint8_t)~(uint8_t)0xE0U;
	/* MCG->C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0 */
	MCG->C5 = (uint8_t)0x00U;
	/* MCG->C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
	MCG->C6 = (uint8_t)0x00U;
	while((MCG->S & MCG_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
	}
	while((MCG->S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
	}	
} 