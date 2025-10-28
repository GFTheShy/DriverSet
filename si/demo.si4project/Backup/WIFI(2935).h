#ifndef _WIFI_H_
#define _WIFI_H_
#include "stm32f4xx.h"
#define USART_REC_LEN  200
#define EN_USART1_RX
extern u8 USART_RX_BUF[USART_REC_LEN];
extern u16 USART_RX_STA;

void WIFI_init(void);
void USART2_IRQHandler(void);
void usart_sendstr(USART_TypeDef * USARTx,char *str,int size);
void WIFI_connect(void);

#endif
