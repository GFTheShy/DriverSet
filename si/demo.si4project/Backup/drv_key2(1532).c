#include "drv_key2.h"
#include"drv_systick.h"
void drv_key2_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitTypeDef GPIO_InitStructc;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;

	GPIO_InitStructc.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructc.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructc.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructc.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_Init(GPIOC,&GPIO_InitStructc);
}
void key_event(void)
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == RESET)
	{
		drv_systick_delay_ms(30);
		while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == RESET);
		drv_systick_delay_ms(30);
		GPIO_ToggleBits(GPIOE, GPIO_Pin_8);
	}
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) == RESET)
	{
		drv_systick_delay_ms(30);
		while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) == RESET);
		drv_systick_delay_ms(30);
		GPIO_ToggleBits(GPIOE, GPIO_Pin_9);
	}
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6) == RESET)
	{
		drv_systick_delay_ms(30);
		while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6) == RESET);
		drv_systick_delay_ms(30);
		GPIO_ToggleBits(GPIOE, GPIO_Pin_10);
	}
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == RESET)
	{
		drv_systick_delay_ms(30);
		while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6) == RESET);
		drv_systick_delay_ms(30);
		GPIO_ToggleBits(GPIOB, GPIO_Pin_10);
	}
}
