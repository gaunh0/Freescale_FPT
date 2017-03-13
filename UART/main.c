#include "MKL46Z4.h"
#include "uart.h"
#include "GPIO.h"
#include "stdio.h"
#include "SysTicks.h"
//***********************************//
int main()
{
	char ch;
	SystemCoreClockUpdate();
	LED_init();
	LED_On(LED_RED);
	UART_init();
	config_STicks(SystemCoreClock/1000);
	print("\nWelcome to Bluetooth :)\n");
	while(1)
	{
			ch =UART_getc();
			UART_putc(ch);
			if(ch == 0x31) // neu ch =1, bat den
			{
				LED_On(LED_GREEN);
			}
			if(ch == 0x32)// neu ch = 2, tat den
			{
				LED_Off(LED_GREEN);
			}
			if(ch == 0x33)// neu ch =3, cho led nhap nhay
			{
			LED_Tgg(LED_GREEN);
			delay(1000);
			}
	}
}

