#include"drv_led.h"

void drv_led_init(void)
{
	#if 1
	GPIO_InitTypeDef GPIO_InitStruct;//定义结构体变量
	//给GPIOE一个时钟，使之正常工作
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;//控制哪个引脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//设置模式为输出
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//设置上拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;//设置0 1电平翻转速度
	//对整个GPIO进行初始化
		GPIO_Init(GPIOE, &GPIO_InitStruct);
	GPIO_SetBits(GPIOE, GPIO_Pin_All);

	#else
	RCC->AHB1ENR |= (0X01<<1);

	/*GPIOE->MODER &= ~(0X03<<16);
	GPIOE->MODER |= (0X01<<16);
	GPIOE->ODR |= (0X01<<8);
	GPIOE->MODER &= ~(0X03<<18);
	GPIOE->MODER |= (0X01<<18);
	GPIOE->ODR |= (0X01<<9);
	GPIOE->MODER &= ~(0X03<<20);
	GPIOE->MODER |= (0X01<<20);

	GPIOE->ODR |= (0X01<<10);*/

	GPIOB->MODER &= ~(0X03<<20);
	GPIOB->MODER |= (0X01<<20);
	GPIOB->ODR |= (0X01<<10);
	#endif
	
	
}
void drv_led_open(int p)
{	
	#if 0
	//GPIO_ResetBits是把某一位（引脚）变为低电平	
	GPIO_ResetBits(GPIOE, GPIO_Pin);
	
	#else
	GPIOE->BSRRH |= (0X01<<p);
	#endif
}

void drv_led_close(int p)
{
	#if 0
	//GPIO_SetBits是把某一位（引脚）变为高电平
	GPIO_SetBits(GPIOE,GPIO_Pin);
	#else
	GPIOE->BSRRL |= (0X01<<p);
	#endif
}
void drv_led_closeall(void)
{
	//GPIO_SetBits是把某一位（引脚）变为高电平
	GPIO_SetBits(GPIOE,GPIO_Pin_All);
}

