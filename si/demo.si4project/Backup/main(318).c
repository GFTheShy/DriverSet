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
#include "DHT11.h"

uint32_t buf[10]={0x11111111,0x22222222,0x33333333,0x44444444,0x22222222,
				  0x11111111,0x22222222,0x33333333,0x44444444,0x22222222};
uint32_t dma_buf[10]={0};

#define SEND_BUF_SIZE 82

u8 SendBuf[SEND_BUF_SIZE];
const u8 TEST_TO_SEND[]={"88888888888888888888"};

u32 ledOpwM=0,t;
u8 dir=0;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	My_USART1_Init();
	drv_systick_init(168);
	OLED_Init();
	//drv_key2_init();
	EXITX_Init();
	drv_led_init();
	drv_bee_init();//引脚电平反转也要进行引脚初始化
	AD_init();
	DHT11_init();
	showpage1();
	TIM1_PWM_Init();
	TIM2_PWM_Init();//84M/84=1Mhz的计数频率，重装载值为500，所以PWM频率为 1M/500=2khz.
	TIME6_Int_Init(2999, 8399);		
	//TIME5_Int_Init(9999, 8399);
	
	
	while(1){
		 TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
		if(currentpage==3){
		u8 temp_val,humi_val;
		DHT11_read_data(&humi_val, &temp_val);
		OLED_ShowNum(50,16,temp_val,2,16,1);
		OLED_ShowNum(50,32,humi_val,2,16,1);

		OLED_Refresh();
		}
		drv_systick_delay_ms(1000);
	}
}

