#include "timer.h"

void TIME5_Int_Init(u32 arr,u16 psc)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period=arr;//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;//预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分割
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);
	TIM_ITConfig(TIM5, TIM_IT_Update,ENABLE);//使能定时器的更新中断
	

	NVIC_InitStruct.NVIC_IRQChannel=TIM5_IRQn;//通道号
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM5,ENABLE);//开启定时器6
	
}
void TIME6_Int_Init(u32 arr,u16 psc)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period=arr;//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;//预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分割
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);
	TIM_ITConfig(TIM6, TIM_IT_Update,ENABLE);//使能定时器的更新中断
	

	NVIC_InitStruct.NVIC_IRQChannel=TIM6_DAC_IRQn;//通道号
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM6,ENABLE);//开启定时器6
	
}

