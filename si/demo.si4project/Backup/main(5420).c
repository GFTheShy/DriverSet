#include "drv_led.h"
#include "drv_bee.h"
#include "drv_key.h"
#include "drv_oled.h"
#include "exit.h"
#include "drv_systick.h"
#include "drv_key2.h"
#include "drv_iwdog.h"
#include "usart.h"
#include "string.h"
#include "timer.h"
#include "pwm.h"

int main(void)
{
	//u8 len,t;
	//u16 times=0;
	u16 ledOpwaval=0;
	u8 dir=1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/*drv_led_init();
	drv_bee_init();
	OLED_Init();
	EXITX_Init();
	OLED_ShowString(1, 1,"SDFSDF");*/
	drv_led_init();
	drv_bee_init();
	drv_systick_init(168);
	TIM14_PWM_Init(500-1,84-1);//84M/84=1Mhz的计数频率，重装载值为500，所以PWM频率为 1M/500=2khz.
	
	
	drv_led_open(8);
	while(1){//实现比较值从0-300递增，到300后从300-0递减，循环
		drv_systick_delay_ms(10);
		if(dir)ledOpwaval++;//dir==1 ledOpwaval递增
		else ledOpwaval--;//dir==0 ledopwaval递减
		if(ledOpwaval>300)dir=0;//ledOpwaval到达300后，方向为递减
		if(ledOpwaval==0)dir=1;//ledOpwaval递减到0后，方向为递增

		TIM_SetCompare1(TIM14,ledOpwaval);//修改比较值，修改占空比 
	}
	
}

