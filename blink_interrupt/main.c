#include <MKL46Z4.h>

volatile uint32_t delay_reg;
volatile uint32_t led_red_ms=500;
volatile uint32_t led_green_ms=500;
volatile uint32_t led_load_ms=500;

void LED_init(void) 
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK 
							| SIM_SCGC5_PORTE_MASK; /* Enable Clock for port D and E */
	PORTD->PCR[5] |= PORT_PCR_MUX(1); /* Pin D.5 as GPIO */
	PTD->PDDR |= (1ul<<5); /* Pin D.5 as output */
	
	PORTE->PCR[29] |= PORT_PCR_MUX(1);/* Pin E.29 as GPIO */
	PTE->PDDR |= (1ul<<29); /* Pin E.29 as output */
}
void SW_init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; /*Enable clock for port C*/
	
	PORTC->PCR[3] |= PORT_PCR_MUX(1) | (1UL << 1) | (1UL << 1); /* Pin C.3 as GPIO | Enable pullup resitor */
	PORTC->PCR[3] |= PORT_PCR_IRQC(10); /*1010 Interrupt on falling edge*/
	PTC->PDDR |= (0ul<<3); /* Pin C.3 as input */                    

	
	PORTC->PCR[12] |= PORT_PCR_MUX(1) | (1UL << 1) | (1UL << 1); /* Pin C.3 as GPIO | Enable pullup resitor */
	PORTC->PCR[12] |= PORT_PCR_IRQC(10); /*1010 Interrupt on falling edge*/
	PTC->PDDR |= (0ul<<12); /* Pin C.3 as input */                            
												
	NVIC_SetPriority(PORTC_PORTD_IRQn, 1);  /*Set priority*/
	NVIC_EnableIRQ(PORTC_PORTD_IRQn);  /*Enable*/
}
void config_SysTicks(uint32_t rlo)
{
	SysTick->CTRL = 7; /*CLKSOURCE and TICKINT, ENABLE systicks*/
	SysTick->LOAD = rlo; /*Reload value - 1ms*/
	SysTick->VAL = 0; /*Current Value Register - clear FLAG*/
	
	NVIC_SetPriority(SysTick_IRQn, 2);  /*Set Priority */ 
	NVIC_EnableIRQ(SysTick_IRQn); 	
	
} 
void SysTick_Handler()
{
	if(--led_red_ms == 0)
	{
		PTE->PTOR |= (1ul << 29);
		led_red_ms=500;
	}
	if(--led_green_ms == 0)
	{
		PTD->PTOR |= (1ul << 5);
		led_green_ms=led_load_ms;
	}
}

void PORTC_PORTD_IRQHandler(void)
{
	if(PORTC->PCR[3] & (1UL<<24))
		{
		led_load_ms *=2;
		led_green_ms=led_load_ms;
		PORTC->PCR[3] |= (1UL<<24);
		}	
	if(PORTC->PCR[12] & (1UL<<24))
		{
		led_load_ms /=2;
		led_green_ms=led_load_ms;
		PORTC->PCR[12] |= (1UL<<24);
		}	
}

int main(void)
{
	SystemCoreClockUpdate();
	LED_init();
	SW_init();
	config_SysTicks(SystemCoreClock/1000);
	while(1)
	{
		/*Do nothing :)*/
	}
}