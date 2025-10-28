#ifndef _AD_H__
#define _AD_H__
#include"stm32f4xx.h"
void AD_init(void);
void ADC2_init(void);//DHT11温度传感器	
u16 Get_Adc2_Average(void);

u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(void);

#endif



