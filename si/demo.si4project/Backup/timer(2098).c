#include "timer.h"


void TIME3_Init(u16 arr,u16 psc)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	TIM_TimeBaseInitStruct.TIM_Period=arr;//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;//预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);//使能定时器的更新中断

	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;//定时器3中断
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
}
