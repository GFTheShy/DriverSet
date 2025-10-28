#include"exit.h"
#include"drv_key.h"
#include"oled.h"

void EXITX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);//使能SYSCFG时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOC, ENABLE);
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//设置PE4映射到EXTI4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);

	EXTI_InitStruct.EXTI_Line=EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line13;//配置EXTI_Line4
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;//使能line4
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;//设置中断响应
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;//设置下降沿触发
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_IRQn;//外部中断4(通过这个参数找中断服务函数)
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//子优先级1
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_Init(&NVIC_InitStruct);
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_Init(&NVIC_InitStruct);
	
}


