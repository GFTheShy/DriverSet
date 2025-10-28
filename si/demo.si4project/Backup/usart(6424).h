#ifndef _USART_H__
#define _USART_H__
#include"stm32f4xx.h"
#include "stdio.h"
void My_USART1_Init(void);
void USART1_IRQHandler(void);
int fputc(int ch,FILE *fp);


#endif
