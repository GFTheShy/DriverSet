#include"drv_key.h"
void delay_ms(uint32_t ms)
{
	uint32_t i;
    // 基于系统时钟的粗略延时函数
    for ( i = 0; i < (ms * 10000); ++i) {
        __NOP();
    }
}
void drv_key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//定义结构体变量

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6;//控制哪个引脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//设置模式为输出
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//设置上拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;//设置0 1电平翻转速度
	//对整个GPIO进行初始化
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	GPIO_SetBits(GPIOE, GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6);
	
}
uint8_t key_GETNUM(void)
{
	uint8_t keynumb=0;
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)==0)
	{
		delay_ms(20);//按下消抖
		while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)==0)//按键卡在这直到松手
		delay_ms(20);//松开消抖
		keynumb=1;

	}
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)==0)
	{
		delay_ms(20);//按下消抖
		while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)==0)//按键卡在这直到松手
		delay_ms(20);//松开消抖
		keynumb=2;

	}
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6)==0)
	{
		delay_ms(20);//按下消抖
		while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)==0)//按键卡在这直到松手
		delay_ms(20);//松开消抖
		keynumb=3;
		
	}
	return keynumb;
}
