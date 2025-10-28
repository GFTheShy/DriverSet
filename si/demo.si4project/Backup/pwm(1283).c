 #include "pwm.h"

void TIM1_PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	//TIM_InternalClockConfig(TIM1);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9,GPIO_AF_TIM1);

	TIM_TimeBaseInitStruct.TIM_Period=500-1;//自动重装载值1
	TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
	//TIM_ITConfig(TIM1, TIM_IT_Update,ENABLE);//使能定时器的更新中断 

	//TIM_OCStructInit(&TIM_OCInitStruct); //初始化结构体

	TIM_OCInitStruct.TIM_OCIdleState= TIM_OCIdleState_Set;//空闲状态为高
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;//PWM模式1
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStruct.TIM_Pulse=0;	//比较初值ccr
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;//输出极性为低

	TIM_OCInitStruct.TIM_OCNIdleState=TIM_OCIdleState_Set;
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCPolarity_Low;
	TIM_OCInitStruct.TIM_OutputNState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM1,&TIM_OCInitStruct);//初始化通道1
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);//使能TIM14在CCR1上的影子寄存器 	
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);//使能装载的影子寄存器
	TIM_CtrlPWMOutputs(TIM1,ENABLE);//控制PWM的输出 

	TIM_Cmd(TIM1,ENABLE);
	
}
void TIM2_PWM_Init(void)//喇叭
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//TIM_InternalClockConfig(TIM1);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10,GPIO_AF_TIM2);

	TIM_TimeBaseInitStruct.TIM_Period=500-1;//自动重装载值1
	TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	//TIM_ITConfig(TIM1, TIM_IT_Update,ENABLE);//使能定时器的更新中断 

	//TIM_OCStructInit(&TIM_OCInitStruct); //初始化结构体

	TIM_OCInitStruct.TIM_OCIdleState= TIM_OCIdleState_Set;//空闲状态为高
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;//PWM模式1
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStruct.TIM_Pulse=300;	//比较初值ccr
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;//输出极性为低

	TIM_OCInitStruct.TIM_OCNIdleState=TIM_OCIdleState_Set;
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCPolarity_Low;
	TIM_OCInitStruct.TIM_OutputNState=TIM_OutputState_Enable;
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);//初始化通道1
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);//使能TIM14在CCR1上的影子寄存器 	
	
	TIM_ARRPreloadConfig(TIM2,ENABLE);//使能装载的影子寄存器
	TIM_CtrlPWMOutputs(TIM2,ENABLE);//控制PWM的输出 

	TIM_Cmd(TIM2,ENABLE);
	
}

void TIM12_PWM_Init(void)//风扇
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
	
	//TIM_InternalClockConfig(TIM1);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15,GPIO_AF_TIM12);

	TIM_TimeBaseInitStruct.TIM_Period=1000-1;//自动重装载值1
	TIM_TimeBaseInitStruct.TIM_Prescaler=700;//预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM12, &TIM_TimeBaseInitStruct);
	//TIM_ITConfig(TIM1, TIM_IT_Update,ENABLE);//使能定时器的更新中断 

	//TIM_OCStructInit(&TIM_OCInitStruct); //初始化结构体

	TIM_OCInitStruct.TIM_OCIdleState= TIM_OCIdleState_Set;//空闲状态为高
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;//PWM模式1
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStruct.TIM_Pulse=0;	//比较初值ccr
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;//输出极性为低

	TIM_OC2Init(TIM12,&TIM_OCInitStruct);//初始化通道3
	TIM_OC2PreloadConfig(TIM12,TIM_OCPreload_Enable);//使能TIM2在CCR3上的影子寄存器 	
	
	TIM_ARRPreloadConfig(TIM12,ENABLE);//使能装载的影子寄存器
	TIM_CtrlPWMOutputs(TIM12,ENABLE);//控制PWM的输出 

	TIM_Cmd(TIM12,ENABLE);
	
}


