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
#include "pwm.h"

uint32_t buf[10]={0x11111111,0x22222222,0x33333333,0x44444444,0x22222222,
				  0x11111111,0x22222222,0x33333333,0x44444444,0x22222222};
uint32_t dma_buf[10]={0};

#define SEND_BUF_SIZE 82

u8 SendBuf[SEND_BUF_SIZE];
const u8 TEST_TO_SEND[]={"88888888888888888888"};

u32 ledOpwM=0,t;
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
	//EXITX_Init();
	drv_led_init();
	drv_bee_init();//引脚电平反转也要进行引脚初始化
	
	//showpage1();
	
	//TIME6_Int_Init(9999, 8399);	
	/*while(1)
	{
		
		
		

	}*/		
	TIM1_PWM_Init();//84M/84=1Mhz的计数频率，重装载值为500，所以PWM频率为 1M/500=2khz.
	
	while(1){//实现比较值从0-300递增，到300后从300-0递减，循环
		
		if(dir==0)ledOpwM++;//dir==0 ledOpwaval递增
		else ledOpwM--;//dir==1 ledopwaval递减
		if(ledOpwM>300)dir=1;//ledOpwaval到达300后，方向为递减
		if(ledOpwM==0)dir=0;//ledOpwaval递减到0后，方向为递增
		OLED_ShowString(0, 0, "ledOpwM",16, 1);
		TIM_SetCompare1(TIM1,ledOpwM);//修改比较值（CCR），修改占空比 Duty=CCR/(ARR+1)
		drv_systick_delay_ms(10);
	}
}

