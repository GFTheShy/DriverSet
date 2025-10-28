#include "drv_led.h"
#include "drv_bee.h"
#include "drv_key.h"
#include "drv_oled.h"
#include "exit.h"
#include "drv_systick.h"
#include "drv_key2.h"
#include "drv_iwdog.h"
#include "usart.h"



int main(void)
{

	/*drv_led_init();
	drv_systick_init(168);
	drv_key2_init();
	drv_bee_init();


	drv_systick_delay_ms(500);

	drv_bee_open();

	
		drv_iwdog_init(4,1000);

	while (1)
	{
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==RESET){
			IWDG_ReloadCounter();
		}
		drv_systick_delay_ms(20);
	}*/
	My_USART1_Init();
	printf("hhhhhhhhhh\r\n");
	while(1)
	{

	}
	
}

