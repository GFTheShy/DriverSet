#include "pwm.h"

void TIM14_PWM_Init(u32 arr,u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9,GPIO_AF_TIM14);

	TIM_TimeBaseInitStruct.TIM_Period=arr;//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;//预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);
	TIM_ITConfig(TIM14, TIM_IT_Update,ENABLE);//使能定时器的更新中断 

	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;//PWM模式2
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//比较输出使能
	//TIM_OCInitStruct.TIM_Pulse=100;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;//输出极性：TIM输出比较极性高
	TIM_OC1Init(TIM14,&TIM_OCInitStruct);//初始化通道1
	TIM_OC1PreloadConfig(TIM14,TIM_OCPreload_Enable);//使能TIM14在CCR1上的预装载处理器
	TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPE使能

	TIM_Cmd(TIM14,ENABLE);
	
}