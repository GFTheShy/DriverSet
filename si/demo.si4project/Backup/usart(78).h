#ifndef _USART_H__
#define _USART_H__
#include"stm32f4xx.h"
#include "stdio.h"
void My_USART1_Init(void);
void _USART1_IRQHandler(void);
int fputc(int ch,FILE *fp);
#define USART_REC_LEN  200
#define EN_USART1_RX
extern u8 USART_RX_BUF[USART_REC_LEN];
extern u16 USART_RX_STA;

#endif
