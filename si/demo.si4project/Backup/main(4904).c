#include "stdio.h"
#include "oled.h"
#include "bmp.h"
#include "drv_systick.h"
#include "AD.h"
#include "usart.h"
#include "drv_led.h"
#include "drv_bee.h"
#include "exit.h"
#include "timer.h"

uint32_t buf[10]={0x11111111,0x22222222,0x33333333,0x44444444,0x22222222,
				  0x11111111,0x22222222,0x33333333,0x44444444,0x22222222};
uint32_t dma_buf[10]={0};

#define SEND_BUF_SIZE 82

u8 SendBuf[SEND_BUF_SIZE];
const u8 TEST_TO_SEND[]={"88888888888888888888"};

u16 ledOpwM=0,t;
u8 dir=0;
void delay_ms(uint32_t ms)
{
	uint32_t i;
    // 基于系统时钟的粗略延时函数
    for ( i = 0; i < (ms * 10000); ++i) {
        __NOP();
    }
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//My_USART1_Init();
	drv_systick_init(168);
	OLED_Init();
	//drv_key2_init();*/
	EXITX_Init();
	drv_led_init();
	drv_bee_init();//引脚电平反转也要进行引脚初始化

	
	

	/*OLED_ShowChinese(0,16,0,16,1);//华
	OLED_ShowChinese(20,16,1,16,1);//清
	OLED_ShowChinese(40,16,2,16,1);//远
	OLED_ShowChinese(60,16,3,16,1);//见
	OLED_ShowChinese(80,16,4,16,1);//教
	OLED_ShowChinese(100,16,5,16,1);//育
	//OLED_ShowChinese(120,16,5,16,1);//欢
	//OLED_ShowChinese(140,16,5,16,1);//迎
	//OLED_ShowChinese(160,16,5,16,1);//您
	//OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
	//OLED_ShowString(20,32,"2014/05/01",16,1);
	OLED_Refresh();
	//OLED_ScrollDisplay(10,4,1);*/
	TIME6_Int_Init(4999, 8399);	
	while(1)
	{
		//key_eventOled();
		
		

	}		
	
}

