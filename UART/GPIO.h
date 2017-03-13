#ifndef __GPIO_H
#define __GPIO_H
#include "stdio.h"

#include "MKL46Z4.h"
typedef enum {
	LED_GREEN, LED_RED
} LED_Name;
void LED_init(void);
void LED_Off(LED_Name LEDx);
void LED_On(LED_Name LEDx);
void LED_Tgg(LED_Name LEDx);
#endif
