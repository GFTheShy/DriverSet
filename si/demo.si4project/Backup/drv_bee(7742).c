#include "drv_bee.h"
void drv_bee_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//定义结构体变量
	//给GPIOE一个时钟，使之正常工作
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;//控制哪个引脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//设置模式为输出
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//设置上拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;//设置0 1电平翻转速度
	//对整个GPIO进行初始化
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOB, GPIO_Pin_10);

	
}
void drv_bee_open(void)
{	
	//GPIO_ResetBits是把某一位（引脚）变为低电平	
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
}
void drv_bee_close(void)
{
	//GPIO_SetBits是把某一位（引脚）变为高电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);

}

