#include "usart.h"
#include "drv_led.h"
#include "timer.h"
#include "drv_oled.h"
#include "AD.h"
#include "drv_systick.h"
#include "pwm.h"
#include "DMA.h"
#include "stdio.h"
#include "drv_key.h"

#define SEND_BUF_SIZE 82

u8 SendBuf[SEND_BUF_SIZE];
const u8 TEST_TO_SEND[]={"88888888888888888888"};

u16 ledOpwM=0;
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
	//u8 len,t;
	//u16 times=0;
	//u8 i=0,j=0,t=0,mask=0;
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
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
	
	drv_led_init();
	drv_key_init();
	//My_USART1_Init();
	//My_DMA_Init(DMA2_Stream7,DMA_Channel_4, (u32)&USART1->DR, (u32)SendBuf, SEND_BUF_SIZE);

	/*j=sizeof(TEST_TO_SEND);
	for(i=0;i<SEND_BUF_SIZE;i++){
		if(t>=j){//加入换行符
			if(mask){
				SendBuf[i]=0x0a;
				t=0;
			}else{
				SendBuf[i]=0x0d;
				mask++;
			}
		}else{//复制TEST_TO_SEND
			mask=0;
			SendBuf[i]=TEST_TO_SEND[t];
			t++;
		}
	}*/
	
	//drv_led_open(8);
	while(1){
		/*temp=Get_Adc(ADC_Channel_10);
		printf("%d\n",temp);
		delay_ms(500);//systick的延时函数出问题了
		if(key_GETNUM()==1){
			printf("\r\nDMA DATA:\r\n");
			USART_DMACmd(USART1, USART_DMAReq_Tx,ENABLE);
			MY_DMA_Enable(DMA2_Stream7, SEND_BUF_SIZE);*/
			drv_led_open(8);
			drv_systick_delay_ms(100);
			drv_led_close(8);
			drv_systick_delay_ms(100);
		}
			
	
}

