#include "drv_key2.h"
#include "drv_systick.h"
#include "drv_bee.h"
#include "oled.h"

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
	GPIO_Init(GPIOE,&GPIO_InitStruct);

	GPIO_InitStructc.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructc.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructc.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructc.GPIO_PuPd=GPIO_PuPd_UP;
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
u8 LED1=0;
u8 LED2=0;
u8 BEE=0;
u8 currentpage=0;

u8 key1=0;
#include "oled.h"
void key_eventOled(void)
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == RESET)
	{
		drv_systick_delay_ms(30);
		while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == RESET);
		drv_systick_delay_ms(30);
		key1++;
		//GPIO_ToggleBits(GPIOE, GPIO_Pin_8);
		//LED1 = !LED1;
		//showpage2();
	}
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == RESET)
	{
		currentpage=2;
		drv_systick_delay_ms(30);
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == RESET);
		drv_systick_delay_ms(30);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16,1);//华
		OLED_ShowChinese(20,0,1,16,1);//清
		OLED_ShowChinese(40,0,2,16,1);//远
		OLED_ShowChinese(60,0,3,16,1);//见
		OLED_ShowChinese(80,0,4,16,1);//教
		OLED_ShowChinese(100,0,5,16,1);//育
		//LED状态
		OLED_ShowString(0,16,"LED1:",16,1);
		OLED_ShowString(0,32,"LED2:",16,1);
		OLED_ShowString(0,48,"Bee:",16,1); 
		if(LED1==0)OLED_ShowChinese(40,16,10,16,1);
		else OLED_ShowChinese(40,16,9,16,1);
		
		OLED_Refresh();
	}
}

