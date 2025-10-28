#include "usart.h"
#include "drv_led.h"
#include "timer.h"
#include "drv_oled.h"
#include "AD.h"
#include "drv_systick.h"

//u16 ledOpwM=0;
//u8 dir=0;
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
	//u8 len,t;
	//u16 times=0;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/*drv_led_init();
	drv_bee_init();
	OLED_Init();
	EXITX_Init();
	OLED_ShowString(1, 1,"SDFSDF");*/
	/*drv_systick_init(168);
	TIM1_PWM_Init();//84M/84=1Mhz的计数频率，重装载值为500，所以PWM频率为 1M/500=2khz.
	
	while(1){//实现比较值从0-300递增，到300后从300-0递减，循环
		
		if(dir==0)ledOpwM++;//dir==0 ledOpwaval递增
		else ledOpwM--;//dir==1 ledopwaval递减
		if(ledOpwM>300)dir=1;//ledOpwaval到达300后，方向为递减
		if(ledOpwM==0)dir=0;//ledOpwaval递减到0后，方向为递增

		TIM_SetCompare1(TIM1,ledOpwM);//修改比较值（CCR），修改占空比 Duty=CCR/(ARR+1)
		drv_systick_delay_ms(10);
	}*/
	//u16 temp=0;
	//My_USART1_Init();
	//AD_init();
	TIME6_Int_Init(4999, 8399);
	drv_led_init();

	while(1){
		//temp=Get_Adc(ADC_Channel_10);
		//printf("%d\n",temp);
		//delay_ms(500);//systick的延时函数出问题了
	}
}

