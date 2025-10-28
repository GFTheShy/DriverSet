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


int main(void)
{
	u8 len,t;
	//u16 times=0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/*drv_led_init();
	drv_bee_init();
	OLED_Init();
	EXITX_Init();
	OLED_ShowString(1, 1,"SDFSDF");*/
	drv_led_init();
	drv_systick_init(168);
	TIME3_Init(4999,8399);
	
	
	while(1){
		GPIO_ToggleBits(GPIOE,GPIO_Pin_9);
		drv_systick_delay_ms(50);
	}
	
}

