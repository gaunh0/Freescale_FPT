#ifndef __UART_H
#define __UART_H
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "MKL46Z4.h"

void UART_init(void);
void UART_putc(char c);
char UART_getc(void);
void print(char *ptr_str);
int fputc(int c, FILE *f);
int fgetc(FILE *f);
#endif
